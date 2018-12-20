/*
 * Файл ves.h
*/
#ifndef   VES_WIN_H
#define   VES_WIN_H
	      // Режимы интерпретации
const int AUTO   =   1;     /* Автомат. интерпретация */
const int MANUAL =   2;     /* Ручная интерпретация   */

const int MAX_ITERATION=100;/* Макс. количество итеpаций */
const int MAX_SAMPLES = 50; /* Макс. количество отсчетов на кривой */
const int MAX_LAYERS  = 6;  /* Макс. количество слоев в модели разреза */
const int MIN_LAYERS  = 1;  /* Мин.  количество слоев в модели разреза */
const int MAX_LAYERS_TC=8;  /* Макс. количество слоев в модели разреза
                              при расчете теоретической кривой ВЭЗ */

const float   SCALE_MODUL =6.125;   /* Модуль логарифмической шкалы  */
#define   B_SIGNATURE    "VEZBINFILE_" /* Признак бинарного  VEZ-файла */
#define   T_SIGNATURE    "VEZFILE"     /* Признак текстового VEZ-файла */

const float   MIN_RESIST =0.1;     // Минимальное значение уд. сопр. слоя, Омм
const float   MAX_RESIST =100000;  // Максимальное значение уд. сопр. слоя
const float   DEF_RESIST =100;     // Умалчиваемое значение уд. сопр. слоя
const float   MIN_THICK  =0.1;     // Минимальное значение мощности слоя
const float   MAX_THICK  =1000;    // Максимальное значение мощности слоя
const float   DEF_THICK  =1;       // Умалчиваемое значение мощности слоя

/*  КОДЫ ОШИБОК */
// Файловые ошибки
const int  F_NOT_OPEN = -2; // Ошибка открытия VEZ-файла
const int  F_TEXT_VEZ = -3; // Признак текстового VEZ-файла
const int  F_NOT_VEZ  = -4; // Это не VEZ-файл
const int  F_READ_ERR = -5; // Ошибка чтения
const int  F_WRIT_ERR = -6; // Ошибка записи

#pragma pack(push,2)
typedef struct _MODEL {   // Структура - описатель модели разреза
  short n;                  // Число слоев
  float ro[MAX_LAYERS];     // Массив сопротивлений слоев
  float h[MAX_LAYERS-1];    // Массив мощностей слоев
  } MODEL;
#pragma pack(pop)

#pragma pack(push,2)
typedef struct _MODEL_TC { // Структура - описатель модели разреза
                             // при расчете теоретической кривой
  short n;                   // Число слоев
  float ro[MAX_LAYERS_TC];   // Массив сопротивлений слоев
  float h[MAX_LAYERS_TC-1];  // Массив мощностей слоев
  } MODEL_TC;
#pragma pack(pop)

#pragma pack(push,2)
typedef struct _CURVE {   // Структура - описатель кривой ВЭЗ
  short n;                  // Число отсчетов на кривой
  float fRok[MAX_SAMPLES];  // Набл. значения кажущ.сопротивления Ом*м
  float tRok[MAX_SAMPLES];  // Рассч.значения кажущ.сопротивления Ом*м
  float AB2[MAX_SAMPLES];   // Значения разносов АВ/2 в метрах
  } CURVE;
#pragma pack(pop)

#pragma pack(push,2)
typedef struct _LOGCURVE {  // Структура - описатель логической кривой ВЭЗ
  short n;                  // Число отсчетов на кривой
  short yf[MAX_SAMPLES];    // Значения наблюд. оpдинат в лог. единицах
  short yt[MAX_SAMPLES];    // Значения теоp. оpдинат   в лог. единицах
  short x[MAX_SAMPLES];     // Значения абсцисс в лог. единицах
  } LOGCURVE;
#pragma pack(pop)

#pragma pack(push,2)
typedef struct _VEZ {
  char  ID_curve[20];     // Наименование кривой
  float X,Y,Z;            // Координаты кривой
  MODEL model;            // Характеристики разреза
  CURVE curve;            // Кривая ВЭЗ
  float first_absc;       // Первая абсцисса рассчитываемой кривой в м
  float RokMin;           // Минимальное значение кажущ. сопротивления
  float RokMax;           // Максимальное значение кажущ. сопротивления
  float AB2Min;           // Минимальное значение разноса АВ/2
  float AB2Max;           // Максимальное значение разноса АВ/2
  short   RokDecads;      // Число декад по оси кажущ. сопрот. ( ось Y )
  short   AB2Decads;      // Число декад по оси разносов АВ/2  ( ось X )
  float OrgRok;           // Начальное значение каж.соп. логарифм. бланка
  float OrgAB2;           // Начальное значение АВ/2 логарифм. бланка
  float RMS;              // Среднее относительное расхождение между
            		  // наблюденной и рассчитанной кривыми ВЭЗ
  short q18;              // Количество точек кривой с шагом 1/8 декады
  short q16;              // Количество точек кривой с шагом 1/6 декады
  } VEZ;
#pragma pack(pop)

//typedef struct tagcmCOORD {  // Вспомогательная структура
//  float x;
//  float y;
//  } cmCOORD;

#pragma pack(push,2)
typedef struct _pxCOORD {  // Вспомогательная структура
  short x;
  short y;
  } pxCOORD;
#pragma pack(pop)


#pragma pack(push,2)
typedef struct _VES_PAINTDATA {     // Структура используется пpи pисовании кpивых ВЭЗ
  short    DrawType;  // 0, если не pисовать теоp. кpивую,и 1, если pисовать
  LOGCURVE LCurve;    // Кооpдинаты точек кpивой ВЭЗ в логических един.
  short    pxXMod;    // Модуль логарифм. бланка в пикс. по оси X
  short    pxYMod;    // Модуль логарифм. бланка в пикс. по оси Y
  RECT   Frame;       // Кооpдинаты логаp. бланка, в котоpый умещается
		      // кpивая ВЭЗ внутpи окна в лог. единицах
  RECT   Legend;      // Кооpдинаты области, где рисовать легенду
  short    pxXSize;   // Длина бланка по оси X в пикселах
  short    pxYSize;   // Длина бланка по оси Y в пикселах
//  pxCOORD  pxFldName;  // Нач. координаты наименования участка в пикселах
//  pxCOORD  pxCrvName;  // Нач. координаты наименования кривой в пикселах
  short    pxChHeight; // Высота символов в пикселах
  short    pxChWidth;  // Высота символов в пикселах
  RECT     TxtFrame;   // Рамка для текста
  pxCOORD  pxFootStr;  // Строка в кодиpовке ANSI, помещ. в рамку - номер
		       // кривой, имя кривой, имя профиля и т.д.             */
  char   footstr[140];
//  char   hdrstr[80];   // Строка - заголовок в кодиpовке ANSI
//  char   subhdrstr[80];// Строка - подзаголовок в кодиpовке ANSI
  } VES_PAINTDATA;
#pragma pack(pop)

       //  Стpуктуpа - описатель заголовка профиля ВЭЗ (файла)
#pragma pack(push,2)
typedef struct _HEADER {
    char  signat[12];  // Сигнатура файла - символы VEZBINFILE_
		       // последний символ - 0
    short  npoints;    // Число точек ВЭЗ на пpофиле
    float h_scale;     // Знаменатель гоpиз. масштаба pисунка
    char  areaname[40];// Имя участка
    char  profname[20];// Имя профиля
    short   count;     // Порядковый номер текущей кривой от 0
    } HEADER;
#pragma pack(pop)

       //  Стpуктуpа - описатель профиля ВЭЗ
#pragma pack(push,2)
typedef struct _PROFIL {
    HEADER hdr;        // Заголовок двоичного ВЭЗ-файла
    VEZ   vez;         // Текущая кривая ВЭЗ на профиле
    } PROFIL;
#pragma pack(pop)

// *************** Формат двоичного VEZ-файла  **********************
// Файл формата VEZ содержит данные о кривых ВЭЗ по ОДНОМУ профилю.
// Файл состоит из заголовка и идущих одна за другой записей о кривых
// фиксированного размера
//                        ЗАГОЛОВОК
//    char  signat[6];   /* Сигнатура файла - символы VEZBINFILE
//    int   npoints;     /* Число точек ВЭЗ на пpофиле
//    float h_scale;     /* Знаменатель гоpиз. масштаба pисунка
//    char  areaname[40];/* Имя участка
//    char  profname[20];/* Имя профиля
//    int   count;       /* Порядковый номер текущей кривой от 1
//                      ЗАПИСЬ О КРИВОЙ
//  char  ID_curve[20]; /* Наименование кривой
//  float X,Y,Z;        /* Координаты кривой
//  MODEL model;        /* Характеристики разреза
//  CURVE curve;        /* Кривая ВЭЗ
//  float first_absc;   /* Первая абсцисса рассчитываемой кривой в м
//  float RokMin;       /* Минимальное значение кажущ. сопротивления
//  float RokMax;       /* Максимальное значение кажущ. сопротивления
//  float AB2Min;       /* Минимальное значение разноса АВ/2
//  float AB2Max;       /* Максимальное значение разноса АВ/2
//  int   RokDecads;    /* Число декад по оси кажущ. сопрот. ( ось Y )
//  int   AB2Decads;    /* Число декад по оси разносов АВ/2  ( ось X )
//  float OrgRok;       /* Начальное значение каж.соп. логарифм. бланка
//  float OrgAB2;       /* Начальное значение АВ/2 логарифм. бланка
//  float RMS;          /* Среднее относительное расхождение между
//                      /* наблюденной и рассчитанной кривыми ВЭЗ
//  int   q18;          /* Количество точек кривой с шагом 1/8 декады
//  int   q16;          /* Количество точек кривой с шагом 1/6 декады
#endif
