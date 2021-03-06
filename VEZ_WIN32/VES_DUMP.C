#define VERSION "�.���⪮� (c) 1995  v1.0b"
/*------------------------ ves_dump.c ---------------------*/
/*         ���⪮� �. (c) 1995 ����ਭ���               */
/*               �ணࠬ�� vez_dump.exe                    */
/*---------------------------------------------------------*/
/* �ணࠬ�� �뤠�� ���ଠ�� �� ������� 䠩��� �ଠ�  */
/* VES �஥�� VES for Windows                             */
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

/* ------------------------- �p��⨯� ---------------------------*/

void pascal visa( void );
void out_help( char *hint );
void IndError( void );
FILE *OpenProfil( char *fname, PROFIL *prof );
int ReadCurve( FILE *fp, VEZ *vez , int cnt );
void CreateFileName( char *instr, char *outstr );


/* ----------------- �������H�� ������HH�� ---------------------- */

char   inname[64];       /* ��� ����筮�� �室���� 䠩�� �ଠ� VES */
FILE *inf;               /* �室��� VEZ - 䠩�  */
char outname[64];        /* ��� ��室���� 䠩�� */
FILE *out;               /* ��室��� 䠩� */

int    recno;            /* ���浪��� ����� ⥪�饩 �ਢ�� � VEZ-䠩�� */

/*
�������������������������������������������
�                                         �
�                M A I N                  �
�                                         �
�������������������������������������������
*/
int cdecl main( int argc, char *argv[] )
{
PROFIL  pr;         /* ���ᠭ�� ��䨫� ���   */
int     i;

 clrscr();
 visa();
 if ( argc < 2 )
    { IndError();
      out_help("�訡�� � ��������� ��ப� !");
      return -1;
  }
 strcpy( inname, argv[1] );  /* ��� ��.䠩�� - �� ��������� ��ப� */
 CreateFileName( inname, outname );  /* ᣥ����㥬  ��� ���. 䠩�� */
 if (NULL == ( out = fopen ( outname, "wt"))) /* ��஥� ��� */
   { IndError();
      printf("�訡�� ��p��� ���. 䠩�� %s!\n", outname);
      return 1; }

	  // ��஥� ��䨫�
 if ( NULL == (inf = OpenProfil( inname,(PROFIL *) &pr ))) return 1;

 for ( recno = 1; recno <= pr.hdr.npoints; recno ++ ) // 横� �� �ਢ�
  {
    if ( ReadCurve( inf, (VEZ *) &(pr.vez) , recno )) return 1; // �⠥�
    printf("\r�ਢ��  : %s               ", pr.vez.ID_curve );
    fprintf( out, "\n���⮪ : %s\n", pr.hdr.areaname );
    fprintf( out, "��䨫� : %s\n", pr.hdr.profname );
    fprintf( out, "�ਢ��  : %s  X=%.1f Y=%.1f Z=%.1f\n",
	    pr.vez.ID_curve, pr.vez.X, pr.vez.Y, pr.vez.Z );
    
    if ( pr.vez.model.n ) // ���� �����쭠� �ਢ�� 
      {
	for ( i = 0; i < pr.vez.model.n - 1; i ++ )
	  fprintf( out, "R = %.1f  h = %.1f\n", pr.vez.model.ro[i], 
					    pr.vez.model.h[i] );
	fprintf( out, "R = %.1f\n", pr.vez.model.ro[i] );
       }
    else
      {
	fprintf( out, "�ਢ�� �� ��ࠡ�⠭�\n");
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
"�����������������������������������������������������\n\r"
"� �ணࠬ�� �뤠� ���ଠ樨 �� �ਢ� �� ����筮���\n\r"
"�               䠩�� �ଠ� VES                   �\n\r"
"�                                                   �\n\r"
"�����������������������������������������������������\n\r";
cputs(cpyright);
}

/* ----------------------------------------------------------------
   OpenProfil ���뢠�� 䠩� ��䨫�, ��� ���ண� 㪠���� �
   ��ப� fname, �஢���� 䠩� �� ���४⭮��� � ��������
   ���� �������� prof.
   �� �ᯥ譮� �����襭�� �����頥� 㪠��⥫� �� ������
   䠩� ��䨫�, �� �訡�� - NULL.
-------------------------------------------------------------------*/
FILE *OpenProfil( char *fname, PROFIL *prof )
{
int bytes;
FILE *file;

  // ��஥� ��� �⥭��
 if (NULL == (file = fopen( fname, "rb" )))
   { printf("�� ���� ������ �室��� 䠩� %s\n", fname);
     return NULL;
   }

  // �⠥� ���������
 bytes = fread( &(prof->hdr), 1, sizeof(HEADER), file );
 if ( bytes != sizeof(HEADER))
   { printf("�訡�� �⥭�� ��������� �� 䠩�� %s\n", fname);
     return NULL;
   }

 if ( strcmp( prof->hdr.signat, B_SIGNATURE )) // �� �����. ���䠩�
   {
    printf("�訡��: �室��� 䠩� %s ����� ������ �ଠ�\n", fname);
    return NULL;
   }

 return file;
}


/* ----------------------------------------------------------------
  ReadCurve ���뢠�� �ਢ�� �� ����筮�� VEZ-䠩�� fp, ��������
  �������� vez
  cnt - ���浪��� ����� �ਢ�� (�� 1)
  �� �ᯥ譮� �����襭�� �����頥� 0, �� �訡�� - ��� �訡��.
-------------------------------------------------------------------*/
int ReadCurve( FILE *fp, VEZ *vez , int cnt )
{
int  bytes;
long offs;

 // �饬 �㦭�� �ਢ��
 offs = ((long) cnt - 1L )*sizeof(VEZ) + sizeof(HEADER);
 fseek( fp, offs, SEEK_SET );
 // ��⠥� ��
 bytes = fread( (char *)vez, 1, sizeof(VEZ), fp );
 if ( bytes != sizeof(VEZ))
   {
     printf( "�訡�� �⥭�� �ਢ�� #%d\n", cnt );
     return F_READ_ERR;  // �訡�� �⥭��
    }

return 0;
}



/* ------------------------------------------------------------
   out_error �뢮��� �� ��࠭ ᮮ�饭�� �� �訡��
---------------------------------------------------------------*/
void out_error( char *msg )
{
  gotoxy(24, 40 - strlen(msg) / 2);
  puts(msg);
  getch();
}

/* -------------------------------------------------------------------
   out_help �뢮��� ���᪠��� �� ��ப� hint � ᮧ���� 蠡��� �室����
   VEZ-䠩��
----------------------------------------------------------------------*/
void out_help( char *hint )
{
printf
 ("\7 %s\n\n"
  " �ᯮ�짮����� �ணࠬ�� : ves_dump.exe <VEZfile>\n"
  "  ��� VEZfile - ��� �室����  䠩�� �ଠ� VEZ,\n"
  "\n"
  " � १���� �㤥� ᮧ��� ������ 䠩� ��䨫� � ������ �室����\n"
  " � ���७��� .dmp\n"
  "\n", hint );

printf("\n\n H����� ���� ������� ...");
getch();    /* ����-� */
return;
}



/*--------------------------------------------
  IndError �뤠�� �������� �訡��
---------------------------------------------- */
void IndError( void )
{
textcolor(WHITE+128);
cprintf("\n\r****** ");
textcolor(LIGHTGRAY);
}

/* -------------------------------------------------------------------
   CreateFileName �㭪�� ᮧ���� ��� ��室���� 䠩��, �ᯮ����
   ���, ᮤ�ঠ饥�� � ��ப� instr. ��� ���७�� ��������� ��
   .dmp � १���� ����頥��� � ��ப� outstr
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
