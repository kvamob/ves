#define VERSION "�.�������� (c) 1995  v1.0b"
/*------------------------ ves_dump.c ---------------------*/
/*         �������� �. (c) 1995 ������������               */
/*               ��������� vez_dump.exe                    */
/*---------------------------------------------------------*/
/* ��������� ������ ���������� �� �������� ������ �������  */
/* VES ������� VES for Windows                             */
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

/* ------------------------- �p������� ---------------------------*/

void pascal visa( void );
void out_help( char *hint );
void IndError( void );
FILE *OpenProfil( char *fname, PROFIL *prof );
int ReadCurve( FILE *fp, VEZ *vez , int cnt );
void CreateFileName( char *instr, char *outstr );


/* ----------------- �������H�� ������HH�� ---------------------- */

char   inname[64];       /* ��� ��������� �������� ����� ������� VES */
FILE *inf;               /* ������� VEZ - ����  */
char outname[64];        /* ��� ��������� ����� */
FILE *out;               /* �������� ���� */

int    recno;            /* ���������� ����� ������� ������ � VEZ-����� */

/*
___________________________________________
_                                         _
_                M A I N                  _
_                                         _
___________________________________________
*/
int cdecl main( int argc, char *argv[] )
{
PROFIL  pr;         /* �������� ������� ���   */
int     i;

 clrscr();
 visa();
 if ( argc < 2 )
    { IndError();
      out_help("������ � ��������� ������ !");
      return -1;
  }
 strcpy( inname, argv[1] );  /* ��� ��.����� - �� ��������� ������ */
 CreateFileName( inname, outname );  /* �����������  ��� ���. ����� */
 if (NULL == ( out = fopen ( outname, "wt"))) /* ������� ��� */
   { IndError();
      printf("������ ���p���� ���. ����� %s!\n", outname);
      return 1; }

	  // ������� �������
 if ( NULL == (inf = OpenProfil( inname,(PROFIL *) &pr ))) return 1;

 for ( recno = 1; recno <= pr.hdr.npoints; recno ++ ) // ���� �� ������
  {
    if ( ReadCurve( inf, (VEZ *) &(pr.vez) , recno )) return 1; // ������
    printf("\r������  : %s               ", pr.vez.ID_curve );
    fprintf( out, "\n������� : %s\n", pr.hdr.areaname );
    fprintf( out, "������� : %s\n", pr.hdr.profname );
    fprintf( out, "������  : %s  X=%.1f Y=%.1f Z=%.1f\n",
	    pr.vez.ID_curve, pr.vez.X, pr.vez.Y, pr.vez.Z );
    
    if ( pr.vez.model.n ) // ���� ��������� ������ 
      {
	for ( i = 0; i < pr.vez.model.n - 1; i ++ )
	  fprintf( out, "R = %.1f  h = %.1f\n", pr.vez.model.ro[i], 
					    pr.vez.model.h[i] );
	fprintf( out, "R = %.1f\n", pr.vez.model.ro[i] );
       }
    else
      {
	fprintf( out, "������ �� ����������\n");
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
"_____________________________________________________\n\r"
"_ ��������� ������ ���������� �� ������ �� ���������_\n\r"
"_               ����� ������� VES                   _\n\r"
"_                                                   _\n\r"
"_____________________________________________________\n\r";
cputs(cpyright);
}

/* ----------------------------------------------------------------
   OpenProfil ��������� ���� �������, ��� �������� ������� �
   ������ fname, ��������� ���� �� ������������ � ���������
   ����� ��������� prof.
   ��� �������� ���������� ���������� ��������� �� ��������
   ���� �������, ��� ������ - NULL.
-------------------------------------------------------------------*/
FILE *OpenProfil( char *fname, PROFIL *prof )
{
int bytes;
FILE *file;

  // ������� ��� ������
 if (NULL == (file = fopen( fname, "rb" )))
   { printf("�� ���� ������� ������� ���� %s\n", fname);
     return NULL;
   }

  // ������ ���������
 bytes = fread( &(prof->hdr), 1, sizeof(HEADER), file );
 if ( bytes != sizeof(HEADER))
   { printf("������ ������ ��������� �� ����� %s\n", fname);
     return NULL;
   }

 if ( strcmp( prof->hdr.signat, B_SIGNATURE )) // �� ������. �������
   {
    printf("������: ������� ���� %s ����� �������� ������\n", fname);
    return NULL;
   }

 return file;
}


/* ----------------------------------------------------------------
  ReadCurve ��������� ������ �� ��������� VEZ-����� fp, ���������
  ��������� vez
  cnt - ���������� ����� ������ (�� 1)
  ��� �������� ���������� ���������� 0, ��� ������ - ��� ������.
-------------------------------------------------------------------*/
int ReadCurve( FILE *fp, VEZ *vez , int cnt )
{
int  bytes;
long offs;

 // ���� ������ ������
 offs = ((long) cnt - 1L )*sizeof(VEZ) + sizeof(HEADER);
 fseek( fp, offs, SEEK_SET );
 // ������ ��
 bytes = fread( (char *)vez, 1, sizeof(VEZ), fp );
 if ( bytes != sizeof(VEZ))
   {
     printf( "������ ������ ������ #%d\n", cnt );
     return F_READ_ERR;  // ������ ������
    }

return 0;
}



/* ------------------------------------------------------------
   out_error ������� �� ����� ��������� �� ������
---------------------------------------------------------------*/
void out_error( char *msg )
{
  gotoxy(24, 40 - strlen(msg) / 2);
  puts(msg);
  getch();
}

/* -------------------------------------------------------------------
   out_help ������� ��������� �� ������ hint � ������� ������ ��������
   VEZ-�����
----------------------------------------------------------------------*/
void out_help( char *hint )
{
printf
 ("\7 %s\n\n"
  " ������������� ��������� : ves_dump.exe <VEZfile>\n"
  "  ��� VEZfile - ��� ��������  ����� ������� VEZ,\n"
  "\n"
  " � ���������� ����� ������ �������� ���� ������� � ������ ��������\n"
  " � ����������� .dmp\n"
  "\n", hint );

printf("\n\n H������ ����� ������� ...");
getch();    /* ����-� */
return;
}



/*--------------------------------------------
  IndError ������ ��������� ������
---------------------------------------------- */
void IndError( void )
{
textcolor(WHITE+128);
cprintf("\n\r****** ");
textcolor(LIGHTGRAY);
}

/* -------------------------------------------------------------------
   CreateFileName ������� ������� ��� ��������� �����, ���������
   ���, ������������ � ������ instr. ��� ���������� ���������� ��
   .dmp � ��������� ���������� � ������ outstr
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
