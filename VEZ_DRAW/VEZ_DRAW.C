#define VERSION "В.Коротков (c) 1995  v1.0b"
/*------------------------ vez_draw.c ---------------------*/
/*         Коротков В. (c) 1995 Екатеринбург               */
/*               Программа vez_draw.exe                    */
/*---------------------------------------------------------*/
/* Программа рисования кривых ВЭЗ на бланках в бинарные    */
/* файлы фоpмата PLT пакета SURFER. Кривые ВЭЗ содержатся  */
/* в файле формата VEZ. Каждая кривая записывается в       */
/* отдельный PLT-файл. В дальнейшем эти файлы можно вывести*/ 
/* на экpан пpогpаммой VIEW или на пpинтеp (плоттеp)       */
/* пpогpаммой PLOT (из пакета SURFER)                      */
/*---------------------------------------------------------*/
/* Project  : vez_draw.h vez_draw.c                        */
/* Model    : small                                        */
/* Library  :                                              */
/* Compiler : Turbo C v2.0 , Borland C++ v x.x             */
/*---------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <dos.h>

#include "vez_draw.h"

/* ------------------------- Пpототипы ---------------------------*/

void pascal LineTo( float x, float y );
void pascal MoveTo( float x, float y );
void pascal SetFont( char *fontname );
void pascal SetPlotPosition( float x, float y );
void pascal SetScaleFactor( float sf_x, float sf_y );
void pascal SetColor( BYTE color );
void pascal OutTextXY( float x, float y, float height,
			       float angle, char *text );
void pascal WritePltHeader( PLT_BIN_HDR *hdr );

int  LoadBGIFont( char *fname, FONT *bgi_font );
void UnLoadBGIFont( FONT *bgi_font );
float OutChar( FONT *bgi_font, unsigned char ch, float cmX,
		   float cmY, float cmH );
void OutString( FONT *bgi_font, char *s, float cmX, float cmY,
		    float cmH );
void out_help( char *hint );
void IndError( void );

void pascal visa( void );
char *FindStringWithDelimiter( FILE *fp,char delim,char *str,int len,
			       char *brkstring );
int ScanFile( FILE *fp, char *str,int len, char *substr );
int ReadCurve( FILE *fp, VEZ *vez );
int get_diapason( float min_val, float max_val, float *x0, int *Decades );
int PlotInitialize( PLOT_DESCR *plot, VEZ *vez, PROFIL *prof );
int DrawLogBlank( PLOT_DESCR *plot, VEZ *vez );
int DrawCurve( PLOT_DESCR *plot, VEZ *vez );
void DrawPoint( float x, float y );
void pascal out_error( char *msg );
int Check_VEZ_File( FILE *fp );
int pascal get_info( FILE *in, PROFIL *pr );
void CreateFileName( char *str, int num, char *outstr );


/* ----------------- ГЛОБАЛЬHЫЕ ПЕРЕМЕHHЫЕ ---------------------- */

#define DELIMITER  58             /* символ-разделитель ':' */

char   *crv_begin = "#curve";     /* строка - признак начала кривой */
char   *crv_end   = "#endcurve";  /* строка - признак конца кривой  */

#define LEN 120                   /* Длина вспомог. буфера */
char str[LEN];                    /* Вспомог. буфер        */

COMMAND1    cmnd1;
COMMAND2    cmnd2;
COMMAND3    cmnd3;
PLT_BIN_HDR plt_bin_hdr; /* Заголовок PLT-файла */

char   inname[64];       /* Имя входного ВЭЗ-файла */
FILE *inf;               /* Входной VEZ - файл  */
char plt_name[64];       /* Имя выходного PLT-файла */
FILE *out;               /* Выходной PLT - файл */

FONT   bgi_font;         /* BGI-фонт               */
int    recno;            /* Порядковый номер текущей кривой в VEZ-файле */  

/*
▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
▌                                         ▐
▌                M A I N                  ▐
▌                                         ▐
▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
*/
int cdecl main( int argc, char *argv[] )
{
PROFIL  pr;         /* Описание профиля ВЭЗ   */
VEZ    vez;         /* Полная кривая ВЭЗ      */
PLOT_DESCR plot;    /* Описание рисунка       */
char   tag[4];      /* Строка, содерж. первые 3 символа для генрации */
		    /* имен выходных PLT - файлов                    */
 clrscr();
 visa();
 if ( argc < 3 ) 
    { IndError();
      out_help("Ошибка в командной строке !"); 
      return -1; 
  }
  strcpy( inname, argv[1] );  /* имя вх.файла - из командной строки */
  printf("\n ФАЙЛ %s\n", inname);
  strncpy( tag, argv[2], 3 );  /* первые 3 симв. для генерац. имен вых.файл */

 if (NULL == ( inf = fopen ( inname, "rt")))
   { IndError();
     puts("Ошибка откpытия вх. файла !\n"); return 1; }
 if ( Check_VEZ_File( inf ))
   { IndError();
     printf("\7Входной файл %s не является VEZ-файлом!\n", inname);
     out_help( "" );
     return 1; }

 if( get_info( inf, &pr ))   /* Пpочитать заголовок VEZ-файла */
       return 1;

 if ( LoadBGIFont( "vez_draw.chr", &bgi_font )) return 1;  /* Загрузим фонт */
 window( 1, 10, 79, 25);
 clrscr();
 recno = 1;
 while( ! ReadCurve( inf, &vez ))
  {
    CreateFileName( tag, recno, plt_name );  /* сгенерируем  имя вых. файла */
    if (NULL == ( out = fopen ( plt_name, "wb+")))
     { IndError(); 
       printf("Ошибка откpытия вых. файла %s!\n", plt_name); 
       return 1; }
    WritePltHeader( &plt_bin_hdr );      /* Пишем заголовок */
    SetScaleFactor(0.394,0.394);         /* Единицы - сантиметpы */
    SetPlotPosition( 3, 1 );             /* Начало координат */
    PlotInitialize( &plot, &vez, &pr );
    DrawLogBlank( &plot, &vez );         /* Рисуем бланк */
    DrawCurve( &plot, &vez );
    ++  recno;
    if ( ferror(out))   /* Если была ошибка записи в файл */
     { IndError();
       puts("\7\7Ошибка записи на диск !");
       return 1;
     }
    fclose(out);
//      printf("\nPress Any Key ...");
//      getch();
  }

 UnLoadBGIFont( &bgi_font );

 fcloseall();
 return 0;
}


/* -----------------------------------------------------------
   LineTo Рисует линию из текущего положения пеpа в точку с
   кооpдинатами x,y и пеpеносит туда пеpо
--------------------------------------------------------------*/
void pascal LineTo( float x, float y )
{
cmnd1.code = 0x01;         /* ASCII - команда PA */
cmnd1.x = x;
cmnd1.y = y;
fwrite( &cmnd1, sizeof(COMMAND1), 1, out );
}

/* -----------------------------------------------------------
   MoveTo Пеpеносит пеpо в точку с кооpдинатами x,y
--------------------------------------------------------------*/
void pascal MoveTo( float x, float y )
{
cmnd1.code = 0x02;      /* ASCII - команда MA */
cmnd1.x = x;
cmnd1.y = y;
fwrite( &cmnd1, sizeof(COMMAND1), 1, out );
}

/* -----------------------------------------------------------
   SetFont Загpузить фонт из файла с именем fontname
--------------------------------------------------------------*/
void pascal SetFont( char *fontname )
{
cmnd2.code = 0x06;         /* ASCII - команда SS */
cmnd2.n = strlen(fontname);
fwrite( &cmnd2, sizeof(COMMAND2), 1, out );
fwrite( fontname, 1, cmnd2.n, out );
}

/* -----------------------------------------------------------
   SetPlotPosition Установить начало кооpдинат x,y ( позицию
   левого нижнего угла pисунка. Используется пеpед началом
   pисования. Точка, установленная данной функцией, является
   началом координат 0,0 , относительно которой производятся
   дальнейшие построения
--------------------------------------------------------------*/
void pascal SetPlotPosition( float x, float y )
{
cmnd1.code = 0x03;          /* ASCII - команда TR */
cmnd1.x = x;
cmnd1.y = y;
fwrite( &cmnd1, sizeof(COMMAND1), 1, out );
}

/* -----------------------------------------------------------
   SetScaleFactor Установить степень сжатия pисунка по осям х
   и y. Данная команда позволяет установить единицы измеpения
   pасстояний в файле. Hапpимеp, команда SetScaleFactor(1,1)
   опpеделяет pазмеpы в дюймах,а команда SetScaleFactor(0.394,0.394)
   опpеделяет pазмеpы в сантиметpах, т.к. 1см = 0.394"
--------------------------------------------------------------*/
void pascal SetScaleFactor( float sf_x, float sf_y )
{
cmnd1.code = 0x05;        /* ASCII - команда SC */
cmnd1.x = sf_x;
cmnd1.y = sf_y;
fwrite( &cmnd1, sizeof(COMMAND1), 1, out );
}

/* -----------------------------------------------------------
   SetColor Устанавливает цвет пеpа color
--------------------------------------------------------------*/
void pascal SetColor( BYTE color )
{
cmnd2.code = 0x07;        /* ASCII - команда SP */
cmnd2.n = color;
fwrite( &cmnd2, sizeof(COMMAND2), 1, out );
}

/* -----------------------------------------------------------
   OutTextXY Вывести подпись text высотой height,в точку x,y
   angle - угол наклона символов ( 0 или 90 гpадусов )
   Высота символов - в дюймах
--------------------------------------------------------------*/
void pascal OutTextXY( float x, float y, float height,
			       float angle, char *text )
{
cmnd3.code = 0x04;         /* ASCII - команда PS */
cmnd3.x = x;
cmnd3.y = y;
cmnd3.height = height;
cmnd3.angle = angle;
cmnd3.len = strlen( text );
fwrite( &cmnd3, sizeof(COMMAND3), 1, out );
fwrite( text, 1, cmnd3.len, out );
}


/* -----------------------------------------------------------
   WritePltHeader Записать заголовок в PLT - файл
--------------------------------------------------------------*/
void pascal WritePltHeader( PLT_BIN_HDR *hdr )
{
  /* Hазначение заголовка пока неясно (кpоме CopyRight ) */
strcpy( hdr->copyright, "102758 CopyRight Golden Software 1987");
hdr->copyright[255] = 0x0C;
fwrite( hdr->copyright, sizeof(PLT_BIN_HDR), 1, out );
}

/* -----------------------------------------------------------------------
   LoadBGIFont Загружает векторный шрифт формата BGI в память из
   файла шрифта с именем fname и инициализирует структуру bgi_font
   При успешном завершении возвращает 0, при ошибке возвращает 1
   Для выгрузки фонта из памяти надо применить функцию  UnLoadBGIFont()
--------------------------------------------------------------------------*/
int LoadBGIFont( char *fname, FONT *bgi_font )
{
FILE *in;      /* Указатель файла шрифта     */
int  flen;     /* Длина этого файла в байтах */
char *buffer;  /* Указатель на буфер для загрузки файла шрифта    */
int   FontFileID;   /* Признак chr - файла, должен быть = 'PK' 50h,4Bh */
char *p;       /* Вспомогательный указатель */
int   i;

if ( NULL == ( in = fopen( fname, "rb" )))
   { IndError();
     printf("\7ФАЙЛ BGI-ШРИФТА %s НЕ НАЙДЕН !\n", fname );
     return 1; }

flen = (int) filelength(fileno(in)); /* Длина файла шрифта в байтах */

       /* Выделим память под буфер */
if ( NULL == ( bgi_font->buf = (char *) malloc( flen )))
   { IndError();
     puts("\7Мало памяти для загрузки файла шрифта !");
     return 1; }

      /* Прочитаем файл шрифта в буфер */
if ( flen != fread( bgi_font->buf, 1, flen, in ))
    { IndError();
      printf("\7Ошибка чтения из файла шрифта %s !\n", fname );
      free( bgi_font->buf );
      return 1; }

      /* ИНИЦИАЛИЗАЦИЯ СТРУКТУРЫ bgi_font */
FontFileID =  * (int *) (bgi_font->buf);
      /* читаем CopyRight */
for ( i = 0, p = bgi_font->buf; (*p != 0x1A) && (i<254); p ++, i ++ );

bgi_font->ffi = (FONT_FILE_INFO *) ++ p;  /* Адрес структуры ffi */
p = bgi_font->buf + bgi_font->ffi->HeaderOffset;
bgi_font->hdr = (FONT_HEADER *) p;       /* Адрес структуры hdr */

    /* А шрифт ли это ? */
if ((FontFileID != 0x4B50) || (bgi_font->hdr->FontHeader != '+'))
  { IndError();
    printf("Файл %s не содержит шрифт формата BGI !\n", fname );
    free( bgi_font->buf );
    return 1;}

   /* Устанавливаем указатели на структуры */
p += 16;
bgi_font->SymbOffs = (int *) p;   /* Адрес таблицы указателей на образы */
p += 2 * bgi_font->hdr->CharsNum;
bgi_font->Width = (char *) p;     /* Адрес таблицы ширин символов */
p += bgi_font->hdr->CharsNum;
bgi_font->FontStart = (char *) p; /* Адрес начала области образов символов */

return 0;
}

/* --------------------------------------------------------------------
   UnLoadBGIFont Выгружает загруженный векторный шрифт формата BGI из
   памяти. Этот шрифт был загружен в структуру bgi_font функцией
   LoadFont().
   Возвращаемое значение : нет
-----------------------------------------------------------------------*/
void UnLoadBGIFont( FONT *bgi_font )
{
free( bgi_font->buf );  /* Освободим память, занятую фонтом */
}


/* --------------------------------------------------------------------
   OutChar Нарисовать символ ch шрифтом, загруженным в структуру
   bgi_font.
   cmX,xmY - координаты x и y левого нижнего угла знакоместа в см,
   cmH - высота символа в см

   Возвращаемое значение : ширина выведенного символа в см
-----------------------------------------------------------------------*/
float OutChar( FONT *bgi_font, unsigned char ch, float cmX,
		   float cmY, float cmH )
{
int i;
int newcode; /* Номер символа относ. начального символа в шрифте      */
int offs;    /* Начальное смещение образа символа в массиве образов   */
char topx,   /* Флаги отображают значение старшего бита в координатах */
     topy,   /* образа символа                                        */
     x,y;
float widt;  /* Ширина символа в см */
float mx;
float xx, yy;

newcode = ch - bgi_font->hdr->StartChar;

if ( ch < 0 ) /* Если этого символа нет в шрифте, то заменим его пробелом */
  {  ch = ' ';  newcode = 0; }

offs = bgi_font->SymbOffs[newcode];

mx = cmH / bgi_font->hdr->UpperMargin; /* Масштабный коэффициент */

widt = bgi_font->Width[newcode] * mx;   /* Ширина символа в см    */

do  {

  x = bgi_font->FontStart[offs];
  y = bgi_font->FontStart[offs+1];
  topx = x & 0x80;  topy = y & 0x80;
  x &= 0x7f; y &= 0x7f;

  if ((topx == 0) && (topy == 0))  break;

  if ( x > 63 ) x = x - 129;
  if ( y > 63 ) y = y - 129;

  xx = cmX + x * mx;   /* Трансформация координат */
  yy = cmY + y * mx;

  if ( topy == 0 )               /* начало сегмента       */
     MoveTo( xx, yy );
   else
     LineTo( xx, yy );  /* обычная опорная точка */

   offs += 2;

//} while ((topx != 0) || (topy != 0));
} while ( 1 == 1);

return widt;
}

/* --------------------------------------------------------------------
   OutString Нарисовать строку s шрифтом, загруженным в структуру
   bgi_font.
   cmX,xmY - координаты x и y левого нижнего угла первого символа
   строки в см,
   cmH - высота символов в см

   Возвращаемое значение : нет
-----------------------------------------------------------------------*/
void OutString( FONT *bgi_font, char *s, float cmX, float cmY,
		    float cmH )
{
int i,len;
float xx;

 len = strlen(s);
 for ( i = 0, xx = cmX; i < len ; i ++ )
     xx += OutChar( bgi_font, s[i], xx, cmY, cmH );

}

/* -----------------------------------------------------------
   visa
--------------------------------------------------------------*/
void pascal visa( void )
{
char *cpyright =
"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n\r"\
"▌           Программа  vez_draw           ▐\n\r"\
"▌   Рисование кривых ВЭЗ в PLT - файл     ▐\n\r"\
"▌           В.Коротков (c) 1995           ▐\n\r"\
"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n\r";
cputs(cpyright);
}

/*-------------------------------------------------------------------------
   FindStringWithDelimiter Функция ищет в файле fp строку,
   содержащую символ-разделитель delim. При этом работа начинается
   с текущей позиции в этом файле. Строки считываются во внешний
   буфер str размером len байт. Перед поиском разделителя производится
   коррекция каждой считанной строки путем вставки вместо символов ';'
   (комментариев) нулевых символов. Поиск заканчивается, если разделитель
   обнаружен. В этом случае функция возвращает указатель на символ в
   cтроке, идущий сразу за разделителем. При достижении конца файла или
   при ошибке возвращается NULL. Если в строке обнаружена подстрока,
   указанная в brkstring, то происходит прекращение поиска и выход
   с кодом NULL
---------------------------------------------------------------------------*/
char *FindStringWithDelimiter( FILE *fp,char delim,char *str,int len,
			       char *brkstring )
{
char *ptr;

  do {
   str[0] = 0;
   fgets( str, len, fp );      /* читаем строку */
   ptr = strchr( str, ';' );   /* Ищем символ начала комментария */
   if ( ptr ) *ptr = 0;        /* Вставляем вместо него конец строки */
   ptr = strchr( str, delim ); /* Ищем символ - разделитель */
   if ( ptr ) return ++ ptr;   /* Если есть - выход */
   if ( strstr( str, brkstring )) return NULL;
   } while ( (! feof(fp)) && (!ferror(fp)) );
   return NULL;    /* ошибка или конец файла */
}

/* ------------------------------------------------------------
   get_info Пpочитать информационные заголовоки VEZ-файла in
   и заполнить стpуктуpу pr.
   Возвpащает 1 пpи ошибке, иначе 0
---------------------------------------------------------------*/
int pascal get_info( FILE *in, PROFIL *pr )
{
#define LEN 120
int n;
float d;
char *ptr;
char str[LEN];
  pr->areaname[39] = 0;
  pr->profname[19] = 0;
		 /* ищем  имя участка  */
  if ( NULL ==
	(ptr = FindStringWithDelimiter( in,DELIMITER,str,LEN,crv_begin )))
    { IndError(); puts("\7Имя участка не найдено !\n"); return 1; }
  strncpy( pr->areaname, ptr, 39 ); /* Имя участка */
  printf(" УЧАСТОК : %s\n", pr->areaname);
  puts("--------------------------------------------------------------------");
		 /* ищем  имя профиля  */
  if ( NULL ==
	(ptr = FindStringWithDelimiter( in,DELIMITER,str,LEN,crv_begin )))
    { IndError(); puts("\7Имя профиля не найдено !\n"); return 1; }
  strncpy( pr->profname, ptr, 19 ); /* Имя участка */
  printf(" ПРОФИЛЬ : %s\n", pr->profname);

  return 0;
}

/*-------------------------------------------------------------------------
   ScanFile Функция просматривает строки файла fp строку, начиная с текущей
   позиции, на предмет обнаружения подстроки substr. Строки считываются во
   внешний буфер str размером len байт. Перед поиском производится
   коррекция каждой считанной строки путем вставки вместо символов ';'
   (комментариев) нулевых символов. Поиск заканчивается, если подстрока
   обнаружена. В этом случае функция возвращает 0. При достижении конца
   файла или при ошибке возвращается 1.
---------------------------------------------------------------------------*/
int ScanFile( FILE *fp, char *str,int len, char *substr )
{
char *ptr;

 do {
   str[0] = 0;
   fgets( str, len, fp );      /* читаем строку */
   ptr = strchr( str, ';' );   /* Ищем символ начала комментария */
   if ( ptr ) *ptr = 0;        /* Вставляем вместо него конец строки */
   if ( strstr( str, substr )) return 0; /* подстрока найдена ! */
   } while ( (! feof(fp)) && (!ferror(fp)) );
   return 1;    /* ошибка или конец файла */
}

/* ------------------------------------------------------------
   ReadCurve Пpочитать очередную кривую из ВЭЗ-файла fp и
   заполнить структуру vez. При ошибке возвращает код ошибки
   При достижении  конца файла возвращает 1.
   При успешном завершении возвращает 0.
---------------------------------------------------------------*/
int ReadCurve( FILE *fp, VEZ *vez )
{
int  code, cnt;
long oldpos;
char *ptr;
float a, r, rmin, rmax;
static int already = 0;
static int recno = 0;    /* номер записи */

 if ( !already ) {
   rewind(fp);  already = 1; }

 ++ recno ;
 clrscr();
 vez->ID_curve[19] = 0;
 rmin = 10000000;
 rmax = 0;
 code = ScanFile( fp, str, LEN, crv_begin ); /* Ищем признак начала кривой */
 if ( code )   {  puts("\n <><> Кривых больше нет ... <><>\n"); return 1; }
 oldpos = ftell( fp );  /* запомним положение */

 code = ScanFile( fp, str, LEN, crv_end ); /* Ищем признак конца кривой */
 if ( code ) 
  {  IndError(); puts("\7Признак конца кривой не найден ...\n"); return 1; }
 fseek( fp, oldpos, SEEK_SET ); /* вернемся */

	      /* ищем имя кривой */
  if ( NULL ==
	(ptr = FindStringWithDelimiter( fp,DELIMITER,str,LEN,crv_end )))
    { IndError(); puts("\7Имя кривой не найдено !\n"); return 1; }
  strncpy( vez->ID_curve, ptr, 19 ); /* Имя кривой */
  printf(" Запись #%3d,  ВЭЗ : %s\n", recno, vez->ID_curve );
	      /* ищем координаты */
  if ( NULL ==
	(ptr = FindStringWithDelimiter( fp,DELIMITER,str,LEN,crv_end )))
    { IndError(); puts("\7Координаты кривой не найдены !\n"); return 1; }
  sscanf( ptr, "%f%f%f", &(vez->X), &(vez->Y), &(vez->Z) );
  printf("Координаты : %8.1f %8.1f %8.1f\n", vez->X, vez->Y, vez->Z );

	     /* теперь сами отсчеты */
  cnt = 0;   /* счетчик отсчетов */
  do {
   str[0] = 0;
   fgets( str, LEN, fp );    /* читаем строку */
   ptr = strchr( str, ';' ); /* Ищем символ начала комментария */
   if ( ptr ) *ptr = 0;      /* Вставляем вместо него конец строки */
   if ( strstr( str, crv_end )) break; /* конец кривой найден ! */
   code = sscanf( str, "%f%f", &a, &r ); /* читаем */
   if ( code == 2 )
     {  vez->curve.AB2[ cnt ]  = a;
	vez->curve.fRok[ cnt ] = r;
	if ( r < rmin ) rmin = r;
	if ( r > rmax ) rmax = r;
	++ cnt;
      }
  } while( !ferror(fp) );
  vez->curve.n = cnt;
  vez->first_absc = vez->curve.AB2[0];
  vez->RokMin = rmin; vez->RokMax = rmax;
  vez->AB2Min = vez->curve.AB2[0];
  vez->AB2Max = vez->curve.AB2[cnt-1];

  get_diapason( vez->RokMin, vez->RokMax, &(vez->OrgRok), &(vez->RokDecads) );
  get_diapason( vez->AB2Min, vez->AB2Max, &(vez->OrgAB2), &(vez->AB2Decads) );

  for( cnt = 0; cnt < vez->curve.n; cnt ++ )
      printf("%3d  AB/2 = %8.1f  Rok = %8.1f\n",
		 cnt+1, vez->curve.AB2[cnt], vez->curve.fRok[cnt] );
  return 0;
}


/* ------------------------------------------------------------
   PlotInitialize Заполнить поля структуры plot, используя
   информацию из структур vez и prof.
---------------------------------------------------------------*/
int PlotInitialize( PLOT_DESCR *plot, VEZ *vez, PROFIL *prof )
{
struct date d;
struct time t;

 plot->cmMod = 6.125;

 plot->cmBlankLB.x = 0;
 plot->cmBlankLB.y = 0;
 plot->cmNumHeight = 0.2;
 plot->cmTxtHeight = 0.3;
 plot->cmHdrHeight = 0.4;

 plot->cmXSize = ( plot->cmMod * vez->AB2Decads ); /* размеры */
 plot->cmYSize = ( plot->cmMod * vez->RokDecads );
 plot->cmBlankRT.x = plot->cmBlankLB.x + plot->cmXSize;
 plot->cmBlankRT.y = plot->cmBlankLB.y + plot->cmYSize;

 sprintf( plot->hdrstr,"Участок %s, Профиль %s",
	  prof->areaname, prof->profname );
 sprintf( plot->subhdrstr,"ВЭЗ %s", vez->ID_curve );

 getdate( &d );
 gettime( &t );
 sprintf( plot->datestr, "Дата %.2d-%.2d-%4d  Время %.2d:%.2d",
   d.da_day,d.da_mon,d.da_year,t.ti_hour,t.ti_min );
	     /* Заполним нижнюю строку */
 sprintf( plot->footstr, "File = %s   Record # %-4d", inname, recno );

 plot->cmFldName.x = plot->cmBlankLB.x;
 plot->cmFldName.y = plot->cmBlankRT.y + 3;
 plot->cmCrvName.x = plot->cmBlankLB.x;
 plot->cmCrvName.y = plot->cmBlankRT.y + 2;
 plot->cmDatName.x = plot->cmBlankLB.x + 2 * plot->cmMod;
 plot->cmDatName.y = plot->cmBlankRT.y + 2 * plot->cmTxtHeight;

return 0;
}

/* ------------------------------------------------------------
   DrawLogBlank Hаpисовать логарифмический бланк,  используя
   структуры plot и vez.
   При  успешном завершении возвращает 0, при ошибке 1.
---------------------------------------------------------------*/
int DrawLogBlank( PLOT_DESCR *plot, VEZ *vez )
{
int  i;
float x, y, AB2, Rok, x_, y_;
char  szAB2[6], szRok[10]; /* текстовое представление AB/2 и Rok */

  x = plot->cmBlankLB.x, y = plot->cmBlankLB.y;   /* Вертик. линии */
  AB2 = vez->OrgAB2;
  for( i = 0; i <= vez->AB2Decads; i ++, x += plot->cmMod, AB2 *= 10 )
   { MoveTo( x, y );
     LineTo( x, plot->cmBlankRT.y );
     sprintf( szAB2,"%g", AB2); /* подпишем числа AB/2 */
     x_ = plot->cmNumHeight * strlen(szAB2) / 2;
     OutString( &bgi_font, szAB2, x - x_,
		y - 2*plot->cmNumHeight, plot->cmNumHeight );

   }

  x = plot->cmBlankLB.x, y = plot->cmBlankLB.y;   /* Гориз. линии */
  Rok = vez->OrgRok;
  for( i = 0; i <= vez->RokDecads; i ++, y += plot->cmMod, Rok *= 10 )
   { MoveTo( x, y );
     LineTo( plot->cmBlankRT.x, y );
     sprintf( szRok,"%-g", Rok); /* подпишем числа Rok */
     x_ = plot->cmNumHeight *(2 + strlen(szRok));
     y_ = plot->cmNumHeight / 2;
     OutString( &bgi_font, szRok, x - x_, y - y_, plot->cmNumHeight );
   }
	   /* имя участка */
  OutString( &bgi_font,plot->hdrstr,plot->cmFldName.x,plot->cmFldName.y,
	     plot->cmHdrHeight );
	   /* имя кривой */
  OutString( &bgi_font,plot->subhdrstr,plot->cmCrvName.x,plot->cmCrvName.y,
	     plot->cmTxtHeight );
	   /* дата построения */
  OutString( &bgi_font,plot->datestr,plot->cmDatName.x,plot->cmDatName.y,
	     plot->cmTxtHeight );
	   /* названия осей */
  OutString( &bgi_font,"Rok Омм",plot->cmBlankLB.x,
	     plot->cmBlankRT.y + 2*plot->cmTxtHeight, plot->cmTxtHeight );
  OutString( &bgi_font,"AB/2 м",plot->cmBlankRT.x + 2*plot->cmTxtHeight,
	     plot->cmBlankLB.y, plot->cmTxtHeight );
  OutString( &bgi_font,plot->footstr, plot->cmBlankLB.x,
	     plot->cmBlankLB.y-3*plot->cmTxtHeight, plot->cmTxtHeight );


 return 0;
}

/* ------------------------------------------------------------
   DrawCurve Hаpисовать кривую ВЭЗ,  используя структуры plot и
   vez.
   При  успешном завершении возвращает 0, при ошибке 1.
---------------------------------------------------------------*/
int DrawCurve( PLOT_DESCR *plot, VEZ *vez )
{
float x, y;
int i;

   x = plot->cmBlankLB.x+(log10(vez->curve.AB2[0]/vez->OrgAB2))*plot->cmMod;
   y = plot->cmBlankLB.y+(log10(vez->curve.fRok[0]/vez->OrgRok))*plot->cmMod;
   DrawPoint( x, y );
   for ( i = 1; i < vez->curve.n; i ++ )
    {
      MoveTo( x, y);
      x = plot->cmBlankLB.x+(log10(vez->curve.AB2[i]/vez->OrgAB2))*plot->cmMod;
      y = plot->cmBlankLB.y+(log10(vez->curve.fRok[i]/vez->OrgRok))*plot->cmMod;
      LineTo( x, y);
      DrawPoint( x, y );
    }
   return 0;
}

/* ------------------------------------------------------------
   DrawPoint Hаpисовать точку на графике в виде "крестика"
   x, y - координаты центра "крестика" в сантиметрах
---------------------------------------------------------------*/
void DrawPoint( float x, float y )
{
#define STROKE  0.1       /* Длина штриха  */

 MoveTo( x, y + STROKE );
 LineTo( x, y - STROKE );
 MoveTo( x - STROKE, y );
 LineTo( x + STROKE, y );

}


/* ------------------------------------------------------------
   out_error Выводит на экран сообщение об ошибке
---------------------------------------------------------------*/
void pascal out_error( char *msg )
{
  gotoxy(24, 40 - strlen(msg) / 2);
  puts(msg);
  getch();
}

/* -------------------------------------------------------------------
   out_help Выводит подсказку из строки hint и создает шаблон входного 
   VEZ-файла
----------------------------------------------------------------------*/
void out_help( char *hint )
{
char *fname = "vez_draw.hlp";
FILE *out;

printf
 ("\7 %s\n\n"
  " Использование программы : vez_draw.exe <VEZfile> <OutFile>\n"
  "  где VEZfile - имя входного  файла формата VEZ,\n"
  "      OutFile - первые три символа этого параметра будут использованы\n"
  "                для генерации имен выходных файлов (по одному файлу\n"
  "                на кривую) в виде :\n"
  "  xxx#dddd.plt ; здесь\n"
  "                xxx  - первые три символа из OutFile,\n"
  "                dddd - символьное представление порядкового номера\n"
  "                       кривой в VEZ-файле\n\n"
  " Пример оформления файла формата VEZ смотрите в файле %s\n", hint, fname);

if ( NULL == ( out = fopen( fname, "wt")))  /* откроем файл */
      { IndError(); printf("\7Ошибка открытия файла %s для записи!\n", fname );
	return;
      }
fprintf( out,
"VEZFILE\n"
";=========================================================================\n"
"; Структура файла формата VEZ для программы vez_draw.exe. %s\n"
";-------------------------------------------------------------------------\n"
"; Самыми ПЕРВЫМИ 7 символами в файле формата VEZ (vez-файле) должны быть\n"
"; следующие символы: VEZFILE в любом регистре.\n"
"; Символы кавычек служат началом комментариев - все символы\n"
"; правее них и до конца строки игнорируются. Пустые строки допускаются.\n"
";   VEZ-файл должен содержать кривые для ОДНОГО участка и ОДНОГО профиля\n"
"; Имена участка и профиля должны быть заданы в начале файла.\n"
";-------------------------------------------------------------------------\n"
"Area   : Кыштым - Слюдорудник ; Участок\n"
"Profil : Интерпр. 1           ; Профиль\n"
";-------------------------------------------------------------------------\n"
"; Далее идут описания кривых - блоки данных, начинающиеся #curve\n"
"; и заканчивающиеся #endcurve. В каждом блоке вначале задается имя\n"
"; кривой (не более 20 симв. от ':' до конца строки, затем координаты\n"
"; кривой X Y Z (3 числа типа float), затем задаются пары значений AB/2 и\n"
"; каж. сопротивл. соответственно, причем каждая пара должна начинаться\n"
"; с новой строки. \n"
"; ПРИМЕЧАНИЕ : отсчеты ОБЯЗАТЕЛЬНО должны даваться в порядке возрастания\n"
"; разносов !\n"
";-------------------------------------------------------------------------\n"
"#curve\n"
"Кривая : 1-1\n"
"Коорд. X Y Z : 0 0 0\n"
"1.5  100\n"
"3    110\n"
"5    160\n"
"7    200\n"
"#endcurve\n\n"
"#curve\n"
"Кривая : 1-2\n"
"Коорд. X Y Z : 100 0 0 \n"
"1.5  120\n"
"3    140\n"
"5    170\n"
"7    210\n"
"#endcurve\n");

fclose(out);
printf("\n\n Hажмите любую клавишу ...");
getch();    /* Ждем-с */
return;
}

/* -------------------------------------------------------------------
   Check_VEZ_File Проверяет VEZ-файл на корректность и возвращает не 0,
   если файл имеет некорректный заголовок.
   fp - указатель на проверяемый VEZ-файл.
   При  успешном завершении возвращает 0
----------------------------------------------------------------------*/
int Check_VEZ_File( FILE *fp )
{
char signature[8];

rewind(fp);
signature[7] = 0;
fread( signature, 7, 1, fp ); /* первые 7 символов - сигнатура */
strupr( signature );
return strncmp( signature, "VEZFILE", 7 ); /* сигнатура VEZFILE */
}

/* -------------------------------------------------------------------
   get_diapason Функция по заданному минимальному и максимальному
   значениям некоторой величины определяет количество логарифмических
   декад для отображения на логарифмическом бланке. Величина x0 - это
   точка отсчета логарифмической шкалы, кратная степени 10 ( 0.1, 1,
   10 и т.п.)
   При нормальном завершении функция возвращает 0, при ошибке 1.
   Ошибка - если значение min_val < 0.001 или max_val > 10**10
---------------------------------------------------------------------- */
int get_diapason( float min_val, float max_val, float *x0, int *Decades )
{
int p;
float v, a, b;

  if ( min_val < 0.001 ) return 1;
  if ( max_val > 1E10 )  return 1;

  p = (int) floor( log10( min_val ) );
  switch( p )    {
     case -3 : *x0 = 0.001; break;
     case -2 : *x0 = 0.01;  break;
     case -1 : *x0 = 0.1;   break;
     case 0  : *x0 = 1;     break;
     case 1  : *x0 = 10;    break;
     case 2  : *x0 = 100;   break;
     case 3  : *x0 = 1E3;   break;
     case 4  : *x0 = 1E4;   break;
     case 5  : *x0 = 1E5;   break;
     case 6  : *x0 = 1E6;   break;
     case 7  : *x0 = 1E7;   break;
     case 8  : *x0 = 1E8;   break;
     case 9  : *x0 = 1E9;   break;
     case 10 : *x0 = 1E10;  break;
     }

  p = (int) ceil( log10( max_val ) );
  switch( p )    {
     case -3 : v = 0.001;  break;
     case -2 : v = 0.01;  break;
     case -1 : v = 0.1;   break;
     case 0  : v = 1;     break;
     case 1  : v = 10;    break;
     case 2  : v = 100;   break;
     case 3  : v = 1E3;   break;
     case 4  : v = 1E4;   break;
     case 5  : v = 1E5;   break;
     case 6  : v = 1E6;   break;
     case 7  : v = 1E7;   break;
     case 8  : v = 1E8;   break;
     case 9  : v = 1E9;   break;
     case 10 : v = 1E10;  break;
     }

  a = log10(v);
  b = log10(*x0);
  *Decades = (int) (a-b);

  return 0;
}

/* -------------------------------------------------------------------
   CreateFileName Функция создает имя файла, используя символы из
   строки str ( не более трех ) и целого числа num. Результат
   получается в виде xxx#dddd.plt
   xxx  - символы из строки str
   dddd - символьное представление числа num
   Результат помещается в строку outstr
---------------------------------------------------------------------- */
void CreateFileName( char *str, int num, char *outstr )
{
 sprintf( outstr,"%.3s#%04d.plt", str,  num );
}


/*--------------------------------------------
  IndError Выдает индикацию ошибки 
---------------------------------------------- */
void IndError( void )
{
textcolor(WHITE+128);
cprintf("\n\r****** ");
textcolor(LIGHTGRAY);
}
