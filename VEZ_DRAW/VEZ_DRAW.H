/*
 * Файл vez_draw.h - составная часть проекта vez_draw
 */
#ifndef   VEZ_DRAW_H
#define   VEZ_DRAW_H

typedef  unsigned char  BYTE;
typedef  unsigned int   WORD;
typedef  unsigned int   BOOL;

#define  TRUE     1
#define  FALSE    0

#define   MAX_SAMPLES  100      /* Максимальное число отсчетов на кривой   */
#define   MAX_LAYERS   6        /* Максимальное число слоев в модели       */
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

typedef struct tagCOORD {  /* Вспомогательная структура                   */
  float x;
  float y;
  } COORD;

typedef struct tagPLOT {  /* Структура - описатель рисунка */
  float  cmMod;        /* Модуль логарифм. бланка в см.                    */
  COORD  cmBlankLB;    /* Координаты левого нижнего угла лог. бланка в см  */
  COORD  cmBlankRT;    /* Координаты правого верхнего угла лог. бланка в см*/
  float  cmXSize  ;    /* Длина бланка по оси X в см                       */
  float  cmYSize  ;    /* Длина бланка по оси Y в см                       */
  COORD  cmFldName;    /* Нач. координаты наименования участка в см        */
  COORD  cmCrvName;    /* Нач. координаты наименования кривой в см         */
  COORD  cmDatName;    /* Нач. координаты даты построения в см             */
  float  cmNumHeight;  /* Высота цифровых подписей на осях в см            */
  float  cmTxtHeight;  /* Высота текстовых подписей в см                   */
  float  cmHdrHeight;  /* Высота заголовка в см                            */

  char   PLT_name[80]; /* Имя выходного PLT файла                          */
  FILE   *plt;         /* Указатель на выходной PLT файл                   */
  char   hdrstr[80];   /* Строка - заголовок                               */
  char   subhdrstr[80];/* Строка - подзаголовок                            */
  char   datestr[60];  /* Строка с датой построения                        */
  char   footstr[80];  /* Строка под бланком                               */
  } PLOT_DESCR;

/*--------------------------------------------------------------------- */
/* ------ Стpуктуpы некотоpых типов команд в двоичных PLT - файлах ---- */

typedef struct  {
   BYTE   code;
   float  x;
   float  y;
   } COMMAND1;

typedef struct  {
   BYTE   code;
   BYTE   n;
   } COMMAND2;

typedef struct  {
   BYTE   code;
   float  x;
   float  y;
   float  height;
   float  angle;
   BYTE   len;
   } COMMAND3;

typedef struct  {
   char copyright[256];
   } PLT_BIN_HDR;             /*  Заголовок двоичного PLT - файла */

/* =====================================================================
    Команды в файлах PLT (ASCII)
 TR x y   -смещение начала координат в x,y (координаты в дюймах=2.54 см)
 SC ax ay -масштабирование координат соответственно по осям x,y
 SP n     -установить цвет пера n
 MA x y   -движение в точку x,y без рисовки(координаты в дюймах=2.54 см)
 PA x y   -движение в точку x,y c рисовкой (координаты в дюймах=2.54 см)
 SS "имя_файла_шрифта" -установить текущий шрифт из файла
 PS x y d u text -рисовать текст с координаты x,y(дюйм), высота d(дюйм),
	   угол u(град)
 RO angle -повернуть рисунок на angle градусов

  Каждая команда начинается с новой стpоки.
  Соответствие команд ASCII и двоичного фоpматов :
     ASCII                 BIN
 TR x y           03[ float x ][ float y ]
 SC ax ay         05[ float x ][ float y ]
 SP n             07[ byte n ]
 MA x y           02[ float x ][ float y ]
 PA x y           01[ float x ][ float y ]
 SS "имя_файла"   06[ byte n ][ стpока длиной n ]
 PS x y d u       04[ float x ][ float y ][ float d ][ float u ]
		    [ byte n ][ стpока длиной n ]
========================================================================= */

/* ============== ОПИСАНИЯ ВЕКТОРНЫХ ФОНТОВ ФОРМАТА Borland (BGI) ======= */
typedef  struct   {    /* Заголовок с характеристиками CHR-файла с фонтом */
   int HeaderOffset;   /* Смещение поля FontHeader относительно начала
			  шрифтового файла                                */
   char FontName[4];   /* Наименование фонта                              */
   int  FontSize;      /* Длина файла фонта от метки FontHeader до конца  */
   char FontVersion[3];/* Версия фонта                                    */
   } FONT_FILE_INFO;

typedef  struct   {    /* Информационный заголовок шрифта длиной 16 байт  */
   char  FontHeader;   /* Начало информационного заголовка шрифта ,
			  содержит символ '+'                             */
   int   CharsNum;     /* Число символов в шрифте                         */
   char  Dummy1;       /* Не используется                                 */
   char  StartChar;    /* Начальный символ шрифта                         */
   int   DefOffset;    /* Смещение начала области образов символов        */
		       /* относительно поля FontHeader                    */
   char  FillFlag;     /* Флаг заливки контуров символов (0 или1)         */
   char  UpperMargin;  /* Координата y верхней границы шрифта [-64,63]    */
   char  Dummy2;       /* Не используется                                 */
   char  LowerMargin;  /* Координата x нижней границы шрифта [-64,63]     */
   char  Dummy3;       /* Не используется                                 */
   } FONT_HEADER;

typedef  struct   {
   FONT_FILE_INFO *ffi;/* Заголовок с характеристиками CHR-файла с фонтом */
   FONT_HEADER    *hdr;/* Информационный заголовок шрифта длиной 16 байт  */
   int   *SymbOffs;    /* Указатель на таблицу, в которой содержится      */
		       /* CharsNum двухбайтовых смещений образов символов */
		       /* относительно  начала области FontStart          */
   char  *Width;       /* Указатель на таблицу из CharsNum однобайтовых   */
		       /* значений ширин символов                         */
   char  *FontStart;   /* Указатель на область памяти,где хранятся образы */
		       /* символов                                        */
   char  *buf;         /* Указатель на буфер для загрузки файла шрифта    */
   } FONT;
/**************************************************************************/


		       /*  Стpуктуpа - описатель профиля ВЭЗ (файла) */
typedef struct  {
    WORD  npoints;     /* Число точек на пpофиле                 */
    float h_scale;     /* Знаменатель гоpиз. масштаба pисунка    */
    char  fname[64];   /* Имя файла профиля                      */
    char  areaname[40];/* Имя участка                            */
    char  profname[20];/* Имя профиля                            */
    } PROFIL;

/* ---------------------------------------------------------------------- */

/* ----------------------- ПРОТОТИПЫ ФУНКЦИЙ ---------------------------- */
extern void pascal solve_type_curve( VEZ *vez );
extern void pascal WritePltHeader( PLT_BIN_HDR *hdr );

extern void pascal LineTo( float x, float y );
extern void pascal MoveTo( float x, float y );
extern void pascal SetFont( char *fontname );
extern void pascal SetPlotPosition( float x, float y );
extern void pascal SetScaleFactor( float sf_x, float sf_y );
extern void pascal SetColor( BYTE color );
extern void pascal OutTextXY( float x, float y, float height,
			       float angle, char *text );

/*

 Ось Y
 /|\         Расположение бланка на листе А4
  |
  ┌────────────────────────────────────────────┼──────────────────┐
  │        Название участка и профиля                             │
  │        Кривая ВЭЗ                                             │
  │       Rok                    Дата обработки                   │
  ┼   1000 ┌───────────┬───────────┬───────────┐                  ┼
  │        │           │           │           │                  │
  │        │           │           │           │                  │
  │        │           │           │           │                  │
  │        │           │           │           │                  │
  │    100 ├───────────┼───────────┼───────────┤                  │
  │        │           │           │           │                  │
  │        │           │           │           │                  │
  │        │           │           │           │                  │
  │        │           │           │           │                  │
  ┼    10  └───────────┴───────────┴───────────┘                  ┼
  │        1          10          100           AB/2              │
  │                                                               │
  └────────┼───────────────────────────────────┼──────────────────┘ --> Ось X
*/                                                      

#endif                                                  













