#define VERSION "В.Коротков (c) 1995  v1.0b"
/*------------------------ ves_dump.c ---------------------*/
/*         Коротков В. (c) 1995 Екатеринбург               */
/*               Программа vez_dump.exe                    */
/*---------------------------------------------------------*/
/* Программа выдает информацию из двоичных файлов формата  */
/* VES проекта VES for Windows                             */
/*---------------------------------------------------------*/
/* Project  : ves.h ves_dump.c                             */
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
#include <dir.h>
#include <io.h>

#include <windows.h>
#include "ves.h"

/* ------------------------- Пpототипы ---------------------------*/

void pascal visa( void );
void out_help( char *hint );
void IndError( void );
FILE *OpenProfil( char *fname, PROFIL *prof );
int ReadCurve( FILE *fp, VEZ *vez , int cnt );
void CreateFileName( char *instr, char *outstr );


/* ----------------- ГЛОБАЛЬHЫЕ ПЕРЕМЕHHЫЕ ---------------------- */

char   inname[64];       /* Имя двоичного входного файла формата VES */
FILE *inf;               /* Входной VEZ - файл  */
char outname[64];        /* Имя выходного файла */
FILE *out;               /* Выходной файл */

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
int     i;

 clrscr();
 visa();
 if ( argc < 2 )
    { IndError();
      out_help("Ошибка в командной строке !");
      return -1;
  }
 strcpy( inname, argv[1] );  /* имя вх.файла - из командной строки */
 CreateFileName( inname, outname );  /* сгенерируем  имя вых. файла */
 if (NULL == ( out = fopen ( outname, "wt"))) /* Откроем его */
   { IndError();
      printf("Ошибка откpытия вых. файла %s!\n", outname);
      return 1; }

	  // откроем профиль
 if ( NULL == (inf = OpenProfil( inname,(PROFIL *) &pr ))) return 1;

 for ( recno = 1; recno <= pr.hdr.npoints; recno ++ ) // цикл по кривым
  {
    if ( ReadCurve( inf, (VEZ *) &(pr.vez) , recno )) return 1; // читаем
    printf("\rКривая  : %s               ", pr.vez.ID_curve );
    fprintf( out, "\nУчасток : %s\n", pr.hdr.areaname );
    fprintf( out, "Профиль : %s\n", pr.hdr.profname );
    fprintf( out, "Кривая  : %s  X=%.1f Y=%.1f Z=%.1f\n",
	    pr.vez.ID_curve, pr.vez.X, pr.vez.Y, pr.vez.Z );
    
    if ( pr.vez.model.n ) // есть модельная кривая 
      {
	for ( i = 0; i < pr.vez.model.n - 1; i ++ )
	  fprintf( out, "R = %.1f  h = %.1f\n", pr.vez.model.ro[i], 
					    pr.vez.model.h[i] );
	fprintf( out, "R = %.1f\n", pr.vez.model.ro[i] );
       }
    else
      {
	fprintf( out, "Кривая не обработана\n");
      }
  }

 fcloseall();
 return 0;
}



/* -----------------------------------------------------------
   visa
--------------------------------------------------------------*/
void pascal visa( void )
{
char *cpyright =
"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n\r"
"▌ Программа выдачи информации по кривым из двоичного▐\n\r"
"▌               файла формата VES                   ▐\n\r"
"▌                                                   ▐\n\r"
"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n\r";
cputs(cpyright);
}

/* ----------------------------------------------------------------
   OpenProfil Открывает файл профиля, имя которого указано в
   строке fname, проверяет файл на корректность и заполняет
   часть структуры prof.
   При успешном завершении возвращает указатель на открытый
   файл профиля, при ошибке - NULL.
-------------------------------------------------------------------*/
FILE *OpenProfil( char *fname, PROFIL *prof )
{
int bytes;
FILE *file;

  // откроем для чтения
 if (NULL == (file = fopen( fname, "rb" )))
   { printf("Не могу открыть входной файл %s\n", fname);
     return NULL;
   }

  // читаем заголовок
 bytes = fread( &(prof->hdr), 1, sizeof(HEADER), file );
 if ( bytes != sizeof(HEADER))
   { printf("Ошибка чтения заголовка из файла %s\n", fname);
     return NULL;
   }

 if ( strcmp( prof->hdr.signat, B_SIGNATURE )) // не двоичн. ВЭЗфайл
   {
    printf("Ошибка: входной файл %s имеет неверный формат\n", fname);
    return NULL;
   }

 return file;
}


/* ----------------------------------------------------------------
  ReadCurve считывает кривую из двоичного VEZ-файла fp, заполняет
  структуру vez
  cnt - порядковый номер кривой (от 1)
  При успешном завершении возвращает 0, при ошибке - код ошибки.
-------------------------------------------------------------------*/
int ReadCurve( FILE *fp, VEZ *vez , int cnt )
{
int  bytes;
long offs;

 // ищем нужную кривую
 offs = ((long) cnt - 1L )*sizeof(VEZ) + sizeof(HEADER);
 fseek( fp, offs, SEEK_SET );
 // Читаем ее
 bytes = fread( (char *)vez, 1, sizeof(VEZ), fp );
 if ( bytes != sizeof(VEZ))
   {
     printf( "Ошибка чтения кривой #%d\n", cnt );
     return F_READ_ERR;  // ошибка чтения
    }

return 0;
}



/* ------------------------------------------------------------
   out_error Выводит на экран сообщение об ошибке
---------------------------------------------------------------*/
void out_error( char *msg )
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
printf
 ("\7 %s\n\n"
  " Использование программы : ves_dump.exe <VEZfile>\n"
  "  где VEZfile - имя входного  файла формата VEZ,\n"
  "\n"
  " В результате будет создан двоичный файл профиля с именем входного\n"
  " и расширением .dmp\n"
  "\n", hint );

printf("\n\n Hажмите любую клавишу ...");
getch();    /* Ждем-с */
return;
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

/* -------------------------------------------------------------------
   CreateFileName Функция создает имя выходного файла, используя
   имя, содержащееся в строке instr. Его расширение изменяется на
   .dmp и результат помещается в строку outstr
---------------------------------------------------------------------- */
void CreateFileName( char *instr, char *outstr )
{
char drive[MAXDRIVE];
char dir[MAXDIR];
char file[MAXFILE];
char ext[MAXEXT];
char newext[] = ".dmp";

  fnsplit( instr, drive, dir, file, ext);
  fnmerge( outstr,drive, dir, file,newext);
}
