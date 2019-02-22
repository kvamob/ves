/* ----------------------------------------------------------------------
    vez_auto.c Программа АВТОМАТИЧЕСКОЙ интерпретации кривых ВЭЗ
	   По О.Куфуду
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#include "vez_auto.h"

/* ------------------------ Прототипы ---------------------- */
void Interpretation( VEZ *vez, float RMS, int max_iteration );
void Spline( float *x, float *y, int n, float *x_, float *y_, int n_ );

/* -------------- Глобальные переменные -------------------- */


/*******************************************************************
			    M A I N
********************************************************************/
int main(void)
{
float rms;
int   mi;
VEZ   vez;
int   j, M,IK,IT;
int   max_iteration = 100;

      printf("GIVE ACCEPTABLE RELATIVE ERROR  -> ");
      scanf("%f", &rms );
      printf("GIVE FIRST ABCISSA              -> ");
      scanf("%f", &(vez.first_absc));
      printf("GIVE NUMBER OF SAMPLES          -> ");
      scanf("%d", &(vez.curve.n));

 do {
      printf("Задайте парами %3d значений AB/2 и Rok\n", vez.curve.n );
      for ( j = 0; j < vez.curve.n; j ++ )
	 scanf("%f%f", &(vez.curve.AB2[j]), &(vez.curve.fRok[j]) );
      printf("CORRECT ? YES=0 -> ");
      scanf("%d", &M );
  } while ( M );


      printf("GIVE NUMBER OF LAYERS -> ");
      scanf("%d", &( vez.model.n ));
      IK = vez.model.n - 1;
      IT = IK + vez.model.n;

      printf("GIVE %3d LAYER THICKNESSES\n", IK );

  do  {

      for ( j = 0; j < IK; j ++ )
	scanf("%f", &( vez.model.h[j] ));

      printf("GIVE %3d LAYER RESISTIVITIES\n", vez.model.n );

      for ( j = 0; j < vez.model.n; j ++ )
	scanf("%f", &(vez.model.ro[j]) );

      printf("CORRECT ? YES=0 -> ");
      scanf("%d", &M );
  } while ( M );

  Interpretation( &vez, rms, max_iteration );

} /* main */

/* --------------------------------------------------------------------
   Interpretation Функция выполняет решение обратной задачи по кривой
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
void Interpretation( VEZ *vez, float RMS, int max_iteration )
{
float F;
float Q, QV;
float ST, XR, XA, X, B, BA, BM, BN, BC, DW, RW, TH, RM, GR, PA;
int IC, IS, M, K, IK, NLayers, IT, IZ, NSamples, J, I, IW, IY, L, LB, JN, JM;

float absc6[100];         /* Значения абсцисс(разносов) с шагом 1/6 декады */
float RF[MAX_SAMPLES+1],  /* Массив отсчетов кривой в Омм с шагом 1/6 декады */
      P[2*MAX_LAYERS+1],  /* Массив : сначала идут мощности слоев в модели,  */
			  /* от верхнего к нижнему, оставшиеся значения -    */
			  /* сопротивления слоев ( их больше на 1 )          */
      PL[2*MAX_LAYERS+1], G[2*MAX_LAYERS+1], T[11], D[5][2*MAX_LAYERS+1];

  F = exp( log(10)/6 );    /* F = 1.467799 */

    /* Требуемое кол-во точек кривой с шагом 1/6 декады */
  vez->q16 = (int) ceil (( 6*log( vez->curve.AB2[vez->curve.n - 1] /
	vez->curve.AB2[0] )) / log(10) ) + 1;

  absc6[0] = vez->first_absc; /* Заполним массив  absc6 */
  for ( J = 1; J < vez->q16; J ++ )  absc6[J] = absc6[J-1] * F;


/*
      printf("GIVE FIRST ABCISSA              -> ");
      scanf("%f", &XA );
*/
      XA = vez->first_absc;
/*
      printf("GIVE NUMBER OF SAMPLES          -> ");
      scanf("%d", &NSamples );
*/
      NSamples = vez->curve.n;

/*      printf("GIVE %3d  SAMPLE VALUES\n", NSamples ); */
/*************************************************/
/*а вот здесь надо использовать сплайн !!!!!!!!!!
      for ( J = 1; J <= NSamples; J ++ )
	 RF[J] = vez->curve.fRok;
*/

  Spline( &(vez->curve.AB2[0]), &(vez->curve.fRok[0]) , vez->curve.n,
	    absc6, &(RF[1]), vez->q16 );

/*      printf("GIVE NUMBER OF LAYERS -> ");
      scanf("%d", &NLayers );
*/
      NLayers = vez->model.n;
      IK = NLayers - 1;
      IT = IK + NLayers;

      for ( I = 1; I <= IK; I ++ )
	P[I] = vez->model.h[I-1];   /* мощности слоев */

/*      printf("GIVE %3d LAYER RESISTIVITIES\n", NLayers ); */

      for ( I = NLayers, J = 0 ; I <= IT; I ++, J ++ )
	P[I] = vez->model.ro[J];   /* сопротивления */

      QV = 99;
      ST = 0;      IC = 0;      IS = 0;

      printf("STEPLENGTH   R.M.S. ERRORS\n");

/* =======  COMPUTATION OF RESISTIVITY TRANSFORM ========= */
l_12: IC ++ ;
l_13: XR = XA;
      J = 1; Q = 0; BM = 0;
      for ( I = 1; I <= IT; I ++ )  G[I] = 0;
l_15: X = 0.0105 * XR;
      LB = 1;

      for ( L = 1; L <= 9; L ++ )
      {
	X = X * F * F;
l_16:   B = P[IT];

	if ( B > 100000 ) B -= 100000;
	BC = B;

	for ( K = 1; K <= IK; K ++ )
	 {
	   DW = P[NLayers - K];
	   RW = P[IT - K];
	   if( 100000 <= DW ) DW = DW - 100000;
	   if( 100000 <= RW ) RW = RW - 100000;

	   TH = tanh( DW/X );
	   B = (B + (TH * RW))/( 1 + (TH * B / RW));
	  }
	T[L] = B;
      } /* for */
/* =======  COMPUTATION OF PARTIAL DERIVATES OF THE TRANSFORM ========= */

      X = 0.1 * X;
      L = 4;

      if ( LB > 1 ) goto l_25;

      X = 0.1 * X;

      for( L = LB; L <= 4; L ++ )
      {
l_25:    D[L][IT] = 1;
	 B = BC;
	for ( K = 1; K <= IK; K ++ )
	 {
	   I =  NLayers - K;
	   IW = IT - K;
	   IY = IW + 1;
	   DW = P[I];
	   RW = P[IW];
	  if( 100000 <= DW) DW -= 100000;
	  if( 100000 <= RW) RW -= 100000;

	  TH = tanh(DW/X);

	  BA = 1 + B*TH/RW;
	  PA = (1 - TH*TH)/(BA*BA);
	  D[L][I]  = (RW - B*B/RW) / X;
	  D[L][IW] = TH*(1 + B*B/(RW*RW) + 2*TH*B/RW)/(BA*BA);

	  for( IZ = I; IZ <= IK ; IZ ++ )
	     D[L][IZ] = PA * D[L][IZ];

	  for( IZ = IY; IZ <= IT ; IZ ++ )
	     D[L][IZ] = PA * D[L][IZ];

	   B = (B + TH*RW)/(1 + TH*B/RW);
	  } /* for K */
	 X = X*F*F;
      } /* for L */

/* =======  APPLICATION OF LINEAR FILTERS =========*/
      RM = 0.0148*T[1] - 0.0814*T[2] + 0.4018*T[3] - 1.5716*T[4] + 1.972*T[5];
      RM = RM + 0.1854*T[6] + 0.1064*T[7] - 0.0499*T[8] + 0.0225*T[9];

      for( L = 1; L <= 8; L ++ ) T[L] = T[L+1];
      BA = 1 - RM/RF[J];

      for ( I = 1; I <= IT; I ++ )
      {
	if ( P[I] >= 100000 )  continue;
	B = 0.402*D[1][I] - 1.571*D[2][I] + 1.972*D[3][I] + 0.186*D[4][I];

	for( L = 1; L <= 3; L ++ ) D[L][I] = D[(L+1)][I];

	G[I] = G[I] + 2*BA*B*P[I]/RM;
      }

      Q = Q + BA*BA;
      if( BM*BM < BA*BA )
       { BM = -BA;
	 JM = J;
       }
/* ============= BRANCHING PROGRAM ============== */
      J += 2;
      L = 9;
      LB = 4;
      XR = XR*F*F;
      X = 10.5*XR;
      if ( J <= NSamples ) goto l_16;
      if ( J & 1 )  /* проверка на четность, J нечетное */
	{
	  XR = XA*F;         /* next abscissa */
	  J = 2;
	  goto l_15;
	}

       Q = sqrt( Q / (float) NSamples );

      if ( QV <= Q)
       {
	 IS = 1;
	 for ( I = 1; I <= IT; I ++ )
	    P[I] = 0.67*PL[I] + 0.33*P[I];
	 ST = ST / 3;

	 if ( 0.003 <= ST) goto l_13;
			     else goto l_66;
       }

      if ( RMS >= Q )   goto l_70;
      if ( IC >= max_iteration ) goto l_70;

      printf("%10.4f %10.4f\n", ST, Q );

      B = 0;
/* =====  COMPUTATION OF GRADIENT,STEPLENGTH AND ADJUSTEMENT
	OF THE LAYER PARAMETERS                            ======== */

      for ( I = 1; I <= IT; I ++ )
      {
	G[I] = G[I] / NSamples;
	B = B + G[I]*G[I];
      }

      GR = sqrt( B );

      if ( IS <= 0 )
      {
	 ST = (Q*Q - 0.9*RMS*RMS) / GR;
	 if ( ST > 0.5 ) ST = 0.5;
      }

      for ( I = 1; I <= IT; I ++ )
      {
	 PL[I] = P[I];
	 P[I] = P[I]*(1 + ST*G[I] / GR);
      }

      for ( I = 1; I <= IK; I ++ )
      {
	if ( 100000 <= P[I] )
	  {
	     P[I] = 0;
	     DW = 0;
	     for ( K = 1; K <= I; K ++ )
	       DW = DW + PL[K] - P[K];
	     P[I] = DW;
	  }
      }

      QV = Q;
      BN = BM;
      JN = JM;
      goto  l_12;

/* =========== OUTPRINT OF RESULTS =============== */

l_66:
      for ( I = 1; I <= IT; I ++ )
			    P[I] = PL[I];

      Q = QV;
      BM = BN;
      JM = JN;
l_70:

      printf("\n Q  = %f\n", Q);
      printf(" ST = %f\n", ST);

      printf(" MODEL DATA\n");
      printf(" RESISTIVITY THICKNESS\n");

      for ( I = 1, J = 0; I <= IK; I ++ , J ++ )
      {
	DW = P[I];
	RW = P[I + IK];
	if ( 100000 <= DW ) DW -= 100000;
	if ( 100000 <= RW ) RW -= 100000;
	vez->model.ro[J] = RW;
	vez->model.h[J] = DW;
	printf("%10.2f %10.2f\n", RW, DW );
      }

      RW = P[IT];
      if ( 100000 <= RW) RW -= 100000;
      vez->model.ro[IT-1] = RW;
      printf("%10.2f\n", RW );

      printf("\n R.M.S RELATIVE ERROR = %8.4f\n", Q );
      vez->RMS = Q;
      printf(" MAXIMUM RELATIVE ERROR = %8.4f AT SAMPLE %3d\n", BM, JM );
      printf(" NUMBER OF TRIALS WAS %4d\n", IC );
      printf("\nPress any key ...");
      getch();
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
void Spline( float *x, float *y, int n, float *x_, float *y_, int n_ )
{
float  l[MAX_SAMPLES],m[MAX_SAMPLES],
       r[MAX_SAMPLES],s[MAX_SAMPLES];
int    i,j,k,cnt;
float   d,e,p,f,h,rez,r1;
		     /* ВЫЧИСЛЕНИЕ КОЭФФИЦИЕНТОВ СПЛАЙНА */
d = x[1]-x[0];
e =(y[1]-y[0])/d;
for ( k = 1;  k < n-1 ; k ++ )
 { h = d;
   d = x[k+1]-x[k];
   f = e;
   e = (y[k+1]-y[k])/d;
   l[k] = d/(d+h);
   r[k] = 1-l[k];
   s[k] = 6*(e-f)/(h+d);
  }
s[0] = 0;
l[0] = 0;

for ( k = 1 ; k < n-1; k ++ )
  {
    p = 1/(r[k]*l[k-1]+2);
    l[k] = -l[k]*p;
    s[k] = (s[k]-r[k]*s[k-1])*p;
  }

m[n-1] = 0;
l[n-2] = s[n-2];
m[n-2] = l[n-2];
for ( k = n - 3; k >= 0 ; k -- )
  {
    l[k] = l[k]*l[k+1]+s[k];
    m[k] = l[k];
  }
	  /* Вычисление интерполированных значений */
for ( cnt = 0; cnt < n_ ; cnt ++ )
  {
	i = 0;
	if ( x_[cnt]-x[n-1] > 0 )
	 { d = x[n-1]-x[n-2];
	   rez = d*m[n-2]/6+(y[n-1]-y[n-2])/d;
	   rez = rez*(x_[cnt]-x[n-1])+y[n-1];
	 }
	 else
	 {
	   if (x_[cnt]-x[0] <=0 )
	    {
	      d = x[1]-x[0];
	      rez = d*m[1]/6+(y[1]-y[0])/d;
	      rez = rez*(x_[cnt]-x[0])+y[0];
	    }
	   else
	    {
	      while (( x_[cnt]-x[i]) > 0)  ++ i;
	      j = i-1;
	      d = x[i]-x[j];
	      h = x_[cnt]-x[j];
	      r1 = x[i]-x_[cnt];
	      p = d*d/6;
	      rez = (m[j]*r1*r1*r1+m[i]*h*h*h)/6/d;
	      rez = rez+((y[j]-m[j]*p)*r1+(y[i]-m[i]*p)*h)/d;
	     }
	  }
	 y_[cnt] = rez;
   }
}
