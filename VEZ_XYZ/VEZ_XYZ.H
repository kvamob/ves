/*
 * Файл vez_xyz.h
 */
#ifndef   VEZ_AUTO_H
#define   VEZ_AUTO_H

typedef  unsigned char  BYTE;
typedef  unsigned int   WORD;
typedef  unsigned int   BOOL;

#define  TRUE     1
#define  FALSE    0

#define MAX_ITERATION 100  /* Макс. количество итеpаций */
#define MAX_SAMPLES   50   /* Макс. количество отсчетов на кривой */
#define MAX_LAYERS    10   /* Макс. количество слоев в модели разреза */

#define   SCALE_MODUL  6.125    /* Модуль логарифмической шкалы            */

/*  КОДЫ ОШИБОК */
#define   NOT_OPEN     1        /* Ошибка открытия файла                   */
#define   FILE_END     2        /* Ошибка открытия файла                   */
#define   SEEK_ERR     3        /* Ошибка позиционир. файлового указателя  */
#define   WRONG_PARAM  4        /* Ошибочный параметр                      */


typedef struct tagMODEL {       /* Структура - описатель модели разреза    */
  int n;                        /* Число слоев                             */
  float ro[MAX_LAYERS];         /* Массив сопротивлений слоев              */
  float h[MAX_LAYERS-1];        /* Массив мощностей слоев                  */
  } MODEL;

typedef struct tagCURVE {       /* Структура - описатель кривой ВЭЗ        */
  int n;                        /* Число отсчетов на кривой                */
  float fRok[MAX_SAMPLES];      /* Набл. значения кажущ.сопротивления Ом*м */
  float tRok[MAX_SAMPLES];      /* Рассч.значения кажущ.сопротивления Ом*м */
  float AB2[MAX_SAMPLES];       /* Значения разносов АВ/2 в метрах         */
  } CURVE;

typedef struct tagVEZ {
  char  ID_curve[20];     /* Наименование кривой                          */
  float X,Y,Z;            /* Координаты кривой                            */
  MODEL model;            /* Характеристики разреза                       */
  CURVE curve;            /* Кривая ВЭЗ                                   */
  float first_absc;       /* Первая абсцисса рассчитываемой кривой в м    */
  float RokMin;           /* Минимальное значение кажущ. сопротивления    */
  float RokMax;           /* Максимальное значение кажущ. сопротивления   */
  float AB2Min;           /* Минимальное значение разноса АВ/2            */
  float AB2Max;           /* Максимальное значение разноса АВ/2           */
  int   RokDecads;        /* Число декад по оси кажущ. сопрот. ( ось Y )  */
  int   AB2Decads;        /* Число декад по оси разносов АВ/2  ( ось X )  */
  float OrgRok;           /* Начальное значение каж.соп. логарифм. бланка */
  float OrgAB2;           /* Начальное значение АВ/2 логарифм. бланка     */
  float RMS;              /* Среднее относительное расхождение между      */
			  /* наблюденной и рассчитанной кривыми ВЭЗ       */
  int   q18;              /* Количество точек кривой с шагом 1/8 декады   */
  int   q16;              /* Количество точек кривой с шагом 1/6 декады   */
  } VEZ;

		       /*  Стpуктуpа - описатель профиля ВЭЗ (файла) */
typedef struct  {
    WORD  npoints;     /* Число точек на пpофиле                 */
    float h_scale;     /* Знаменатель гоpиз. масштаба pисунка    */
    char  fname[64];   /* Имя файла профиля                      */
    char  areaname[40];/* Имя участка                            */
    char  profname[20];/* Имя профиля                            */
    } PROFIL;

/* ----------------------- ПРОТОТИПЫ ФУНКЦИЙ ---------------------------- */
#endif












