// Файл ves_solv.c : Составная часть проекта VES for Windows
// Функции решения прямой и обратной задачи ВЭЗ

#include <windows.h>
#include <math.h>

#include "ves.h"
#include "ves_rc.h"

/* ------------------------ Прототипы ---------------------- */
void AutoInterpr(VEZ *vez, float RMS, int max_iteration);
void Spline(float *x, float *y, int n, float *x_, float *y_, int n_);
void solve_type_curve(VEZ *data);
float SolveRMS(VEZ *vez);

/* -------------- Глобальные переменные -------------------- */
extern HANDLE hinstance;     // идентификатоp экземпляpа модуля
extern HWND hProgress;       // идентификатоp вспомог. окна
extern int xScreen, yScreen; // размеры экрана
extern int nCapHgh;          // Высота заголовка окна - для установки размеров
                             // вспомогательного окна

/* --------------------------------------------------------------------
   AutoInterpr Функция выполняет решение обратной задачи по кривой
   ВЭЗ, находящейся в структуре vez. Решение проводится методом
   наискорейшего спуска по О.Куфуду. Результат заносится в соответству-
   ющие поля структуры vez. Решение требует задание первого приближения
   для модели. Данные о первом приближении перед вызовом функции должны
   быть занесены в поля по адресу, содержащемуся в указателе model
   структуры vez. Результат интерпретации заносится в эти же поля.
   Другие параметры :
   RMS - заданная отностительная погрешность интерпретации.
   max_iteration - максимальное кол-во итераций.
------------------------------------------------------------------------*/
void AutoInterpr(VEZ *vez, float RMS, int max_iteration)
{
  float F;
  float Q, QV;
  float ST, XR, XA, X, B, BA, BM, BN, BC, DW, RW, TH, RM, GR, PA;
  int IC, IS, M, K, IK, NLayers, IT, IZ, NSamples, J, I, IW, IY, L, LB, JN, JM;

  float absc6[100];                 /* Значения абсцисс(разносов) с шагом 1/6 декады */
  static float RF[MAX_SAMPLES + 1], /* Массив отсчетов кривой в Омм с шагом 1/6 декады */
      P[2 * MAX_LAYERS + 1],        /* Массив : сначала идут мощности слоев в модели,  */
                                    /* от верхнего к нижнему, оставшиеся значения -    */
                                    /* сопротивления слоев ( их больше на 1 )          */
      PL[2 * MAX_LAYERS + 1], G[2 * MAX_LAYERS + 1], T[11], D[5][2 * MAX_LAYERS + 1];

  int xSize, ySize; // Размеры вспомог. окна

  xSize = 2 * MAX_ITERATION + 4 * nCapHgh;
  ySize = 6 * nCapHgh;

  hProgress = CreateWindow(                         // Создание вспомогательного окна
      "Progress",                                   // имя класса окна
      "Automatic Interpretation Processing",        // текст заголовка
      WS_POPUP | WS_CAPTION,                        // Cтиль окна
      (xScreen - xSize) / 2, (yScreen - ySize) / 2, // позиция окна
      xSize, ySize,                                 //  Размеры окна
      NULL,                                         // окно без пpедка
      NULL,                                         // пpименить меню класса, использ. по умолч.
      hinstance,                                    // Владелец окна
      NULL);                                        // неиспользуемый указатель
  if (!hProgress)
    return;
  ShowWindow(hProgress, SW_SHOWNORMAL); // Показать вспомог. окно
  UpdateWindow(hProgress);              // Перерисовать вспомог. окно

  F = exp(log(10) / 6); /* F = 1.467799 */

  /* Требуемое кол-во точек кривой с шагом 1/6 декады */
  vez->q16 = (int)ceil((6 * log(vez->curve.AB2[vez->curve.n - 1] /
                                vez->curve.AB2[0])) /
                                log(10)) + 1;

  absc6[0] = vez->first_absc; /* Заполним массив  absc6 */
  for (J = 1; J < vez->q16; J++)
    absc6[J] = absc6[J - 1] * F;

  XA = vez->first_absc;
  NSamples = vez->curve.n;
  /* Используем сплайн для получения отсчетов с шагом  1/6 декады */
  Spline(&(vez->curve.AB2[0]), &(vez->curve.fRok[0]), vez->curve.n,
         absc6, &(RF[1]), vez->q16);

  NLayers = vez->model.n;
  IK = NLayers - 1;
  IT = IK + NLayers;

  for (I = 1; I <= IK; I++)
    P[I] = vez->model.h[I - 1]; /* мощности слоев */

  for (I = NLayers, J = 0; I <= IT; I++, J++)
    P[I] = vez->model.ro[J]; /* сопротивления */

  QV = 99;
  ST = 0;
  IC = 0;
  IS = 0;

//  printf("STEPLENGTH   R.M.S. ERRORS\n");

/* =======  COMPUTATION OF RESISTIVITY TRANSFORM ========= */
l_12:
  IC++;
l_13:
  XR = XA;
  J = 1;
  Q = 0;
  BM = 0;
  for (I = 1; I <= IT; I++)
    G[I] = 0;
l_15:
  X = 0.0105 * XR;
  LB = 1;

  for (L = 1; L <= 9; L++)
  {
    X = X * F * F;
  l_16:
    B = P[IT];

    if (B > 100000)
      B -= 100000;
    BC = B;

    for (K = 1; K <= IK; K++)
    {
      DW = P[NLayers - K];
      RW = P[IT - K];
      if (100000 <= DW)
        DW = DW - 100000;
      if (100000 <= RW)
        RW = RW - 100000;

      TH = tanh(DW / X);
      B = (B + (TH * RW)) / (1 + (TH * B / RW));
    }
    T[L] = B;
  } /* for */
    /* =======  COMPUTATION OF PARTIAL DERIVATES OF THE TRANSFORM ========= */

  X = 0.1 * X;
  L = 4;

  if (LB > 1)
    goto l_25;

  X = 0.1 * X;

  for (L = LB; L <= 4; L++)
  {
  l_25:
    D[L][IT] = 1;
    B = BC;
    for (K = 1; K <= IK; K++)
    {
      I = NLayers - K;
      IW = IT - K;
      IY = IW + 1;
      DW = P[I];
      RW = P[IW];
      if (100000 <= DW)
        DW -= 100000;
      if (100000 <= RW)
        RW -= 100000;

      TH = tanh(DW / X);

      BA = 1 + B * TH / RW;
      PA = (1 - TH * TH) / (BA * BA);
      D[L][I] = (RW - B * B / RW) / X;
      D[L][IW] = TH * (1 + B * B / (RW * RW) + 2 * TH * B / RW) / (BA * BA);

      for (IZ = I; IZ <= IK; IZ++)
        D[L][IZ] = PA * D[L][IZ];

      for (IZ = IY; IZ <= IT; IZ++)
        D[L][IZ] = PA * D[L][IZ];

      B = (B + TH * RW) / (1 + TH * B / RW);
    } /* for K */
    X = X * F * F;
  } /* for L */

  /* =======  APPLICATION OF LINEAR FILTERS =========*/
  RM = 0.0148 * T[1] - 0.0814 * T[2] + 0.4018 * T[3] - 1.5716 * T[4] + 1.972 * T[5];
  RM = RM + 0.1854 * T[6] + 0.1064 * T[7] - 0.0499 * T[8] + 0.0225 * T[9];

  for (L = 1; L <= 8; L++)
    T[L] = T[L + 1];
  BA = 1 - RM / RF[J];

  for (I = 1; I <= IT; I++)
  {
    if (P[I] >= 100000)
      continue;
    B = 0.402 * D[1][I] - 1.571 * D[2][I] + 1.972 * D[3][I] + 0.186 * D[4][I];

    for (L = 1; L <= 3; L++)
      D[L][I] = D[(L + 1)][I];

    G[I] = G[I] + 2 * BA * B * P[I] / RM;
  }

  Q = Q + BA * BA;
  if (BM * BM < BA * BA)
  {
    BM = -BA;
    JM = J;
  }
  /* ============= BRANCHING PROGRAM ============== */
  J += 2;
  L = 9;
  LB = 4;
  XR = XR * F * F;
  X = 10.5 * XR;
  if (J <= NSamples)
    goto l_16;
  if (J & 1) /* проверка на четность, J нечетное */
  {
    XR = XA * F; /* next abscissa */
    J = 2;
    goto l_15;
  }

  Q = sqrt(Q / (float)NSamples);

  if (QV <= Q)
  {
    IS = 1;
    for (I = 1; I <= IT; I++)
      P[I] = 0.67 * PL[I] + 0.33 * P[I];
    ST = ST / 3;

    if (0.003 <= ST)
      goto l_13;
    else
      goto l_66;
  }

  if (RMS >= Q)
    goto l_70;
  if (IC >= max_iteration)
    goto l_70;

  //      printf("%10.4f %10.4f\n", ST, Q );

  B = 0;
  /* =====  COMPUTATION OF GRADIENT,STEPLENGTH AND ADJUSTEMENT
	OF THE LAYER PARAMETERS                            ======== */

  for (I = 1; I <= IT; I++)
  {
    G[I] = G[I] / NSamples;
    B = B + G[I] * G[I];
  }

  GR = sqrt(B);

  if (IS <= 0)
  {
    ST = (Q * Q - 0.9 * RMS * RMS) / GR;
    if (ST > 0.5)
      ST = 0.5;
  }

  for (I = 1; I <= IT; I++)
  {
    PL[I] = P[I];
    P[I] = P[I] * (1 + ST * G[I] / GR);
  }

  for (I = 1; I <= IK; I++)
  {
    if (100000 <= P[I])
    {
      P[I] = 0;
      DW = 0;
      for (K = 1; K <= I; K++)
        DW = DW + PL[K] - P[K];
      P[I] = DW;
    }
  }

  QV = Q;
  BN = BM;
  JN = JM;

  //      InvalidateRect( hProgress, NULL, TRUE ); // Изменить все окно
  //      UpdateWindow( hProgress );
  // Пошлем сообщение вспомогательному окну
  SendMessage(hProgress, WM_PROGRESS, (WORD)NULL, (LONG)NULL);

  goto l_12;

  /* =========== OUTPRINT OF RESULTS =============== */

l_66:
  for (I = 1; I <= IT; I++)
    P[I] = PL[I];

  Q = QV;
  BM = BN;
  JM = JN;
l_70:

  //      printf("\n Q  = %f\n", Q);
  //      printf(" ST = %f\n", ST);

  //      printf(" MODEL DATA\n");
  //      printf(" RESISTIVITY THICKNESS\n");

  for (I = 1, J = 0; I <= IK; I++, J++)
  {
    DW = P[I];
    RW = P[I + IK];
    if (100000 <= DW)
      DW -= 100000;
    if (100000 <= RW)
      RW -= 100000;
    vez->model.ro[J] = RW;
    vez->model.h[J] = DW;
    //        printf("%10.2f %10.2f\n", RW, DW );
  }

  RW = P[IT];
  if (100000 <= RW)
    RW -= 100000;
  vez->model.ro[NLayers - 1] = RW; // Последний слой
                                   //      printf("%10.2f\n", RW );

  //      printf("\n R.M.S RELATIVE ERROR = %8.4f\n", Q );
  vez->RMS = Q;
  //      printf(" MAXIMUM RELATIVE ERROR = %8.4f AT SAMPLE %3d\n", BM, JM );
  //      printf(" NUMBER OF TRIALS WAS %4d\n", IC );

  //      printf("Press any key ...");
  //      bioskey(0);

  /* А ТЕПЕРЬ ВЫЧИСЛИМ ТЕОРЕТИЧЕСКУЮ КРИВУЮ */
  /* сколько надо точек с шагом 1/8 декады */
  vez->q18 = (int)ceil((8 * log(vez->curve.AB2[vez->curve.n - 1] /
                                vez->curve.AB2[0])) /
                       log(10)) +
             1;
  solve_type_curve(vez);

  DestroyWindow(hProgress); // Убрать вспомог. окно
}

/* ---------------------------------------------------------------------
   Spline   Функция интерполяции кубическим сплайном. Коэффициенты
   вычисляются по всей входной последовательности узлов.
   x и y - указатели на массивы абсцисс и ординат узлов интерполяции
   n - число узлов интерполяции
   x_ - массив абсцисс точек, в которых надо определить значения
   n_ - число этих точек
   y_ - искомые значения
-----------------------------------------------------------------------*/
void Spline(float *x, float *y, int n, float *x_, float *y_, int n_)
{
  static float l[MAX_SAMPLES], m[MAX_SAMPLES],
      r[MAX_SAMPLES], s[MAX_SAMPLES];
  int i, j, k, cnt;
  float d, e, p, f, h, rez, r1;
  /* ВЫЧИСЛЕНИЕ КОЭФФИЦИЕНТОВ СПЛАЙНА */
  d = x[1] - x[0];
  e = (y[1] - y[0]) / d;
  for (k = 1; k < n - 1; k++)
  {
    h = d;
    d = x[k + 1] - x[k];
    f = e;
    e = (y[k + 1] - y[k]) / d;
    l[k] = d / (d + h);
    r[k] = 1 - l[k];
    s[k] = 6 * (e - f) / (h + d);
  }
  s[0] = 0;
  l[0] = 0;

  for (k = 1; k < n - 1; k++)
  {
    p = 1 / (r[k] * l[k - 1] + 2);
    l[k] = -l[k] * p;
    s[k] = (s[k] - r[k] * s[k - 1]) * p;
  }

  m[n - 1] = 0;
  l[n - 2] = s[n - 2];
  m[n - 2] = l[n - 2];
  for (k = n - 3; k >= 0; k--)
  {
    l[k] = l[k] * l[k + 1] + s[k];
    m[k] = l[k];
  }
  /* Вычисление интерполированных значений */
  for (cnt = 0; cnt < n_; cnt++)
  {
    i = 0;
    if (x_[cnt] - x[n - 1] > 0)
    {
      d = x[n - 1] - x[n - 2];
      rez = d * m[n - 2] / 6 + (y[n - 1] - y[n - 2]) / d;
      rez = rez * (x_[cnt] - x[n - 1]) + y[n - 1];
    }
    else
    {
      if (x_[cnt] - x[0] <= 0)
      {
        d = x[1] - x[0];
        rez = d * m[1] / 6 + (y[1] - y[0]) / d;
        rez = rez * (x_[cnt] - x[0]) + y[0];
      }
      else
      {
        while ((x_[cnt] - x[i]) > 0)
          ++i;
        j = i - 1;
        d = x[i] - x[j];
        h = x_[cnt] - x[j];
        r1 = x[i] - x_[cnt];
        p = d * d / 6;
        rez = (m[j] * r1 * r1 * r1 + m[i] * h * h * h) / 6 / d;
        rez = rez + ((y[j] - m[j] * p) * r1 + (y[i] - m[i] * p) * h) / d;
      }
    }
    y_[cnt] = rez;
  }
}

/* ----------------------------------------------------------------------
   solve_type_curve   расчет кривой сопротивления. Кривая вычисляется
   с помощью фильтра Гоша в точках с шагом по абсциссе(разносам) в 1/8
   декады. Затем для вычисления значений каж. сопротивления в точках с
   абсциссами, равными разносам наблюденной кривой, вызывается функция
   Spline()
------------------------------------------------------------------------*/
void solve_type_curve(VEZ *data)
/* n - кол-во точек кривой с шагом 1/8 декады */
{
  static float t[36]; /* Коэффициенты фильтра */

  static float *r, *d;             /* Массивы сопрот и мощностей */
  static float absc8[MAX_SAMPLES]; /* Значения абсцисс(разносов) с шагом 1/8 декады */
  static float ordn8[MAX_SAMPLES]; /* Значения ординат(сопротив) с шагом 1/8 декады */

  float f, x1, y, b, s, u, a1, a2;
  int i9, i, j, m, n, k;
  float stp;

#define SUBR                                         \
  {                                                  \
    b = r[i9 - 1];                                   \
    for (k = 2; k <= i9; k++)                        \
    {                                                \
      i = i9 - k;                                    \
      u = d[i] / y;                                  \
      if ((5 - u) > 0)                               \
      {                                              \
        a1 = exp(u);                                 \
        a2 = (a1 - 1 / a1) / (a1 + 1 / a1);          \
        b = (b + a2 * r[i]) / (1 + (a2 * b) / r[i]); \
      }                                              \
      else                                           \
        b = r[i];                                    \
    }                                                \
  }

  f = exp(log(10) / 8);

  i9 = data->model.n;    /* Число слоев   */
  r = data->model.ro;    /* Сопротивления слоев */
  d = data->model.h;     /* Мощности слоев  */
  x1 = data->first_absc; /* Первая абсцисса */
  data->q18 = (int)ceil((8 * log(data->curve.AB2[data->curve.n - 1] /
                                 data->curve.AB2[0])) /
                                 log(10)) + 1;
  n = data->q18; /* Число точек кривой с шагом 1/8 декады */
  y = x1 / 822.8;

  for (j = 1; j <= 34; j++)
  {
    SUBR;
    t[j] = b;
    y = y * f;
  }
  stp = x1;
  for (m = 0; m < n; m++)
  {
    SUBR;
    t[35] = b;
    y = y * f;
    absc8[m] = stp;
    stp *= f;
    s = 42 * t[1] - 103 * t[3] + 144 * t[5] - 211 * t[7] + 330 * t[9] - 574 * t[11];
    s = s + 1184 * t[13] - 3162 * t[15] + 10219 * t[17] - 24514 * t[19];
    s = s + 18192 * t[21] + 6486 * t[23] + 1739 * t[25] + 79 * t[27] + 200 * t[29];
    s = (s - 106 * t[31] + 93 * t[33] - 38 * t[35]) / 10000;
    for (j = 1; j <= 34; j++)
      t[j] = t[j + 1];
    //          printf("N %d H= %-.4g ROK= %-.4g\n",m,absc8[m],s );
    ordn8[m] = s; /* Значение кажущ. сопр. с шагом 1/8 дек. */
  }
  /* ВЫЧИСЛИТЬ ЗНАЧЕНИЯ СОПРОТИВЛ. В ТОЧКАХ, СООТВЕТСТВ. РАЗНОСАМ */
  Spline(absc8, ordn8, data->q18, data->curve.AB2,
         data->curve.tRok, data->curve.n);
}

/* ----------------------------------------------------------------------
   SolveRMS Вычисляет и возвращает среднее относительное расхождение 
   между практической и рассчитанной кривыми ВЭЗ, находящимися в 
   структуре vez. Кроме того, помещает результат в поле vez->RMS
------------------------------------------------------------------------*/
float SolveRMS(VEZ *vez)
{
  float rms;
  int i;

  if (vez->model.n)
  {
    for (i = 0, rms = 0; i < vez->curve.n; i++)
    {
      rms += 100 * (fabs((vez->curve.fRok[i] - vez->curve.tRok[i]) /
                         ((vez->curve.fRok[i] + vez->curve.tRok[i]) / 2)));
    }
    rms /= vez->curve.n;
  }
  else
    rms = 100;
  vez->RMS = rms;

  return rms;
}
