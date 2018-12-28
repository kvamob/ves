#define _VERSION_ "�.���⪮� (c) 1995-2000,2018  v1.2"
/*------------------------ ves_comp.c ---------------------*/
/*         ���⪮� �. (c) 1995, 2018 ����ਭ���         */
/*               �ணࠬ�� vez_comp.exe                    */
/*---------------------------------------------------------*/
/* �ணࠬ�� ���������� ⥪�⮢� 䠩�� VEZ-�ଠ� (�室 */
/* �� ��� �ணࠬ� vez_draw.exe, vez_asom.exe � ������  */
/* 䠩�� �ଠ� VES ��� �஥�� VES for Windows           */
/*---------------------------------------------------------*/
/* Project  : ves.h ves_comp.c                             */
/* Model    : small                                        */
/* Library  :                                              */
/* Compiler : mingw-w64                                    */
/*---------------------------------------------------------*/

#pragma  hdrstop

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <dos.h>
#include <dir.h>
#include <io.h>

//#include <windows.h>
#include "ves.h"

/* ------------------------- �p��⨯� ---------------------------*/

void visa( void );
char *FindStringWithDelimiter( FILE *fp,char delim,char *str,int len,
			       char *brkstring );
int ScanFile( FILE *fp, char *str,int len, char *substr );
int txt_OpenProfil( FILE *in, PROFIL *pr );
int _WriteCurve( FILE *out, VEZ *vez );
int _WriteProfilHdr( FILE *fp, PROFIL *pr );
int txt_ReadCurve( FILE *fp, VEZ *vez );
int Check_VEZ_File( FILE *fp );

short get_diapason( float min_val, float max_val, float *x0, short int *Decades );

//void out_error( char *msg );
void out_help( char *hint );
void CreateFileName( char *instr, char *outstr );
void IndError( void );


/* ----------------- �������H�� ������HH�� ---------------------- */

#define DELIMITER  58             /* ᨬ���-ࠧ����⥫� ':' */

char   *crv_begin = "#curve";     /* ��ப� - �ਧ��� ��砫� �ਢ�� */
char   *crv_end   = "#endcurve";  /* ��ப� - �ਧ��� ���� �ਢ��  */

#define LEN 120          /* ����� �ᯮ���. ���� */
char str[LEN];           /* �ᯮ���. ����        */

char   inname[64];       /* ��� �室���� ���-䠩�� */
FILE *inf;               /* �室��� VEZ - 䠩�  */
char outname[64];        /* ��� ��室���� VES-䠩�� */
FILE *out;               /* ��室��� VES - 䠩� */

int    recno;            /* ���浪��� ����� ⥪�饩 �ਢ�� � VEZ-䠩�� */

/*
___________________________________________
_                                         _
_                M A I N                  _
_                                         _
___________________________________________
*/
int main( int argc, char *argv[] )
{
PROFIL  pr;         /* ���ᠭ�� ��䨫� ���   */

// clrscr();
 visa();
 if ( argc < 2 )
    { IndError();
      out_help("�訡�� � ��������� ��ப� !");
      return -1;
  }
  strcpy( inname, argv[1] );  /* ��� ��.䠩�� - �� ��������� ��ப� */
  printf("\n ���� %s\n", inname);

 if (NULL == ( inf = fopen ( inname, "rt")))
   { IndError();
     puts("�訡�� ��p��� ��. 䠩�� !\n"); return 1; }
 if ( Check_VEZ_File( inf ))
   { IndError();
     printf("\7�室��� 䠩� %s �� ���� VEZ-䠩���!\n", inname);
     out_help( "" );
     return 1; }

  CreateFileName( inname, outname );  /* ᣥ����㥬  ��� ���. 䠩�� */
  if ( ! access(outname, 0 ))         /* �஢�ਬ, ���� �� 㦥 ⠪�� 䠩� */
   { IndError();
     printf("\7���� %s 㦥 ������� !\n", outname);
     return -1;
    }

  if (NULL == ( out = fopen ( outname, "wb+"))) /* ��஥� ��� */
    { IndError();
      printf("�訡�� ��p��� ���. 䠩�� %s!\n", outname);
      return 1; }

 if( txt_OpenProfil(  inf, &pr ))   /* �p����� ��������� VEZ-䠩�� */
       return 1;
 
 if( _WriteProfilHdr( out, &pr ))   /* ������� ��������� VES-䠩�� */
    {  IndError();
       puts("\7\7�訡�� ����� �� ��� !");
       return 1; 
     }
 
 recno = 0;
 while( ! txt_ReadCurve( inf, &(pr.vez))) // ���� �ਢ��
  {
    ++  recno;
  if( _WriteCurve( out, &(pr.vez) ))   /* ������� ��������� VES-䠩�� */
    {  IndError();
       puts("\7\7�訡�� ����� �� ��� !");
       return 1; 
     }
//     printf("\nPress Any Key ...");
//     getch();
  }
 
 /* ������� ᪮�४��. ��������� VES-䠩�� */  
 pr.hdr.npoints = recno; // ���-�� �ਢ��
 if( _WriteProfilHdr( out, &pr ))  
    {  IndError();
       puts("\7\7�訡�� ����� �� ��� !");
       return 1; 
     }

// fcloseall();
 _fcloseall();
// fclose(inf);
// fclose(out);
 return 0;
}



/* -----------------------------------------------------------
   visa
--------------------------------------------------------------*/
void visa( void )
{
char *cpyright =
"_____________________________________________________\n\r"
"_ �ணࠬ�� ���������� ⥪�⮢� 䠩�� VEZ-�ଠ� _\n\r"
"_ (�室�� ��� �ணࠬ� vez_draw.exe, vez_asom.exe) _\n\r"
"_ �  ������  䠩��  �ଠ�  VES  ���  �஥��    _\n\r"
"_                VES for Windows                    _\n\r"
"_____________________________________________________\n\r";
puts(cpyright);
puts(_VERSION_);
}

/*-------------------------------------------------------------------------
   FindStringWithDelimiter �㭪�� ��� � 䠩�� fp ��ப�,
   ᮤ�ঠ��� ᨬ���-ࠧ����⥫� delim. �� �⮬ ࠡ�� ��稭�����
   � ⥪�饩 ����樨 � �⮬ 䠩��. ��ப� ���뢠���� �� ���譨�
   ���� str ࠧ��஬ len ����. ��। ���᪮� ࠧ����⥫� �ந��������
   ���४�� ������ ��⠭��� ��ப� ��⥬ ��⠢�� ����� ᨬ����� ';'
   (�������ਥ�) �㫥��� ᨬ�����. ���� �����稢�����, �᫨ ࠧ����⥫�
   �����㦥�. � �⮬ ��砥 �㭪�� �����頥� 㪠��⥫� �� ᨬ��� �
   c�ப�, ���騩 �ࠧ� �� ࠧ����⥫��. �� ���⨦���� ���� 䠩�� ���
   �� �訡�� �����頥��� NULL. �᫨ � ��ப� �����㦥�� �����ப�,
   㪠������ � brkstring, � �ந�室�� �४�饭�� ���᪠ � ��室
   � ����� NULL
---------------------------------------------------------------------------*/
char *FindStringWithDelimiter( FILE *fp,char delim,char *str,int len,
			       char *brkstring )
{
char *ptr;

  do {
   str[0] = 0;
   fgets( str, len, fp );      /* �⠥� ��ப� */
   str[strlen(str) - 1] = 0;   /* ���p�� ᨬ��� ��p����� ��p��� 0xA */
   ptr = strchr( str, ';' );   /* �饬 ᨬ��� ��砫� ��������� */
   if ( ptr ) *ptr = 0;        /* ��⠢�塞 ����� ���� ����� ��ப� */
   ptr = strchr( str, delim ); /* �饬 ᨬ��� - ࠧ����⥫� */
   if ( ptr ) return ++ ptr;   /* �᫨ ���� -��室 */
   if ( strstr( str, brkstring )) return NULL;
   } while ( (! feof(fp)) && (!ferror(fp)) );
   return NULL;    /* �訡�� ��� ����� 䠩�� */
}

/* ------------------------------------------------------------
   txt_OpenProfil �p����� ���ଠ樮��� ���������� VEZ-䠩�� in
   � ��������� ���� ��p���p� pr.
   ����p�頥� 1 �p� �訡��, ���� 0
---------------------------------------------------------------*/
int txt_OpenProfil( FILE *in, PROFIL *pr )
{
#define LEN 120
int n;
float d;
char *ptr;
char str[LEN];
  pr->hdr.areaname[39] = 0;
  pr->hdr.profname[19] = 0;
		 /* �饬  ��� ���⪠  */
  if ( NULL ==
	(ptr = FindStringWithDelimiter( in,DELIMITER,str,LEN,crv_begin )))
    { IndError(); puts("\7��� ���⪠ �� ������� !\n"); return 1; }
  strncpy( pr->hdr.areaname, ptr, 39 ); /* ��� ���⪠ */
  printf(" ������� : %s\n", pr->hdr.areaname);
  puts("--------------------------------------------------------------------");
		 /* �饬  ��� ��䨫�  */
  if ( NULL ==
	(ptr = FindStringWithDelimiter( in,DELIMITER,str,LEN,crv_begin )))
    { IndError(); puts("\7��� ��䨫� �� ������� !\n"); return 1; }
  strncpy( pr->hdr.profname, ptr, 19 ); /* ��� �p�䨫� */
  printf(" ������� : %s\n", pr->hdr.profname);

  return 0;
}

/*-------------------------------------------------------------------------
   ScanFile �㭪�� ��ᬠ�ਢ��� ��ப� 䠩�� fp ��ப�, ��稭�� � ⥪�饩
   ����樨, �� �।��� �����㦥��� �����ப� substr. ��ப� ���뢠���� ��
   ���譨� ���� str ࠧ��஬ len ����. ��। ���᪮� �ந��������
   ���४�� ������ ��⠭��� ��ப� ��⥬ ��⠢�� ����� ᨬ����� ';'
   (�������ਥ�) �㫥��� ᨬ�����. ���� �����稢�����, �᫨ �����ப�
   �����㦥��. � �⮬ ��砥 �㭪�� �����頥� 0. �� ���⨦���� ����
   䠩�� ��� �� �訡�� �����頥��� 1.
---------------------------------------------------------------------------*/
int ScanFile( FILE *fp, char *str,int len, char *substr )
{
char *ptr;

 do {
   str[0] = 0;
   fgets( str, len, fp );      /* �⠥� ��ப� */
   ptr = strchr( str, ';' );   /* �饬 ᨬ��� ��砫� ��������� */
   if ( ptr ) *ptr = 0;        /* ��⠢�塞 ����� ���� ����� ��ப� */
   if ( strstr( str, substr )) return 0; /* �����ப� ������� ! */
   } while ( (! feof(fp)) && (!ferror(fp)) );
   return 1;    /* �訡�� ��� ����� 䠩�� */
}

/* ------------------------------------------------------------
   txt_ReadCurve �p����� ��।��� �ਢ�� �� ⥪�⮢��� 
   ���-䠩�� fp � ��������� �������� vez. �� �訡�� �����頥� 
   ��� �訡��.
   �� ���⨦����  ���� 䠩�� �����頥� 1.
   �� �ᯥ譮� �����襭�� �����頥� 0.
---------------------------------------------------------------*/
int txt_ReadCurve( FILE *fp, VEZ *vez )
{
int  code, cnt;
long oldpos;
char *ptr;
float a, r, rmin, rmax;
static int already = 0;
static int recno = 0;    /* ����� ����� */

 if ( !already ) {
   rewind(fp);  already = 1; }

 memset( vez, 0, sizeof(VEZ) ); // ���㫨� �������� vez

 ++ recno ;
// clrscr();
// vez->ID_curve[19] = 0;
 rmin = 10000000;
 rmax = 0;
 code = ScanFile( fp, str, LEN, crv_begin ); /* �饬 �ਧ��� ��砫� �ਢ�� */
 if ( code )   {  puts("\n <><> �ਢ�� ����� ��� ... <><>\n"); return 1; }
 oldpos = ftell( fp );  /* �������� ��������� */

 code = ScanFile( fp, str, LEN, crv_end ); /* �饬 �ਧ��� ���� �ਢ�� */
 if ( code )
  {  IndError(); puts("\7�ਧ��� ���� �ਢ�� �� ������ ...\n"); return 1; }
 fseek( fp, oldpos, SEEK_SET ); /* ��୥��� */

	      /* �饬 ��� �ਢ�� */
  if ( NULL ==
	(ptr = FindStringWithDelimiter( fp,DELIMITER,str,LEN,crv_end )))
    { IndError(); puts("\7��� �ਢ�� �� ������� !\n"); return 1; }
  strncpy( vez->ID_curve, ptr, 19 ); /* ��� �ਢ�� */
  printf(" ������ #%3d,  ��� : %s\n", recno, vez->ID_curve );
	      /* �饬 ���न���� */
  if ( NULL ==
	(ptr = FindStringWithDelimiter( fp,DELIMITER,str,LEN,crv_end )))
    { IndError(); puts("\7���न���� �ਢ�� �� ������� !\n"); return 1; }
  sscanf( ptr, "%f%f%f", &(vez->X), &(vez->Y), &(vez->Z) );
  printf("���न���� : %8.1f %8.1f %8.1f\n", vez->X, vez->Y, vez->Z );

	     /* ⥯��� ᠬ� ������ */
  cnt = 0;   /* ���稪 ����⮢ */
  do {
   str[0] = 0;
   fgets( str, LEN, fp );    /* �⠥� ��ப� */
   ptr = strchr( str, ';' ); /* �饬 ᨬ��� ��砫� ��������� */
   if ( ptr ) *ptr = 0;      /* ��⠢�塞 ����� ���� ����� ��ப� */
             // ������� �� ������ � ��ப� �� �窨
   ptr = str;
   while (ptr) { if (ptr = strchr(str,',')) *ptr = '.';}

   if ( strstr( str, crv_end )) break; /* ����� �ਢ�� ������ ! */
   code = sscanf( str, "%f%f%f%f%f%f%f", &a, &r, &r, &r, &r, &r, &r ); /* �⠥� */
   if ( code == 7 )
//   code = sscanf( str, "%f%f", &a, &r ); /* �⠥� */
//   if ( code == 2 )
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
  vez->RMS = 0;     // ���� �� 㬮�砭��
  vez->model.n = 0; // ������ ���� ���

  return 0;
}


/* ------------------------------------------------------------
   out_error �뢮��� �� �࠭ ᮮ�饭�� �� �訡��
---------------------------------------------------------------*/
void out_error( char *msg )
{
//  gotoxy(24, 40 - strlen(msg) / 2);
  puts(msg);
  getch();
}

/* -------------------------------------------------------------------
   out_help �뢮��� ���᪠��� �� ��ப� hint � ᮧ���� 蠡��� �室����
   VEZ-䠩��
----------------------------------------------------------------------*/
void out_help( char *hint )
{
char *fname = "ves_comp.hlp";
FILE *out;

printf
 ("\7 %s\n\n"
  " �ᯮ�짮����� �ணࠬ�� : ves_comp.exe <VEZfile>\n"
  "  ��� VEZfile - ��� �室����  䠩�� �ଠ� VEZ,\n"
  "\n"
  " � १���� �㤥� ᮧ��� ������ 䠩� ��䨫� � ������ �室����\n"
  " � ���७��� .ves\n"
  "\n"
  " �ਬ�� ��ଫ���� ⥪�⮢��� 䠩�� �ଠ� VEZ ᬮ��� � 䠩�� %s\n",
    hint, fname);

if ( NULL == ( out = fopen( fname, "wt")))  /* ��஥� 䠩� */
      { IndError(); printf("\7�訡�� ������ 䠩�� %s ��� �����!\n", fname );
	return;
      }
fprintf( out,
"VEZFILE\n"
";=========================================================================\n"
"; ������� ⥪�⮢��� 䠩�� �ଠ� VEZ\n"
";-------------------------------------------------------------------------\n"
"; ���묨 ������� 7 ᨬ������ � 䠩�� �ଠ� VEZ (vez-䠩��) ������ ����\n"
"; ᫥���騥 ᨬ����: VEZFILE � �� ॣ����.\n"
"; ������� ����祪 �㦠� ��砫�� �������ਥ� - �� ᨬ����\n"
"; �ࠢ�� ��� � �� ���� ��ப� �����������. ����� ��ப� ����᪠����.\n"
";   VEZ-䠩� ������ ᮤ�ঠ�� �ਢ� ��� ������ ���⪠ � ������ ��䨫�\n"
"; ����� ���⪠ � ��䨫� ������ ���� ������ � ��砫� 䠩��.\n"
";-------------------------------------------------------------------------\n"
"Area   : ����� - ���㤭�� ; ���⮪\n"
"Profil : �����. 1           ; ��䨫�\n"
";-------------------------------------------------------------------------\n"
"; ����� ���� ���ᠭ�� �ਢ�� - ����� ������, ��稭��騥�� #curve\n"
"; � �����稢��騥�� #endcurve. � ������ ����� ���砫� �������� ���\n"
"; �ਢ�� (�� ����� 20 ᨬ�. �� ':' �� ���� ��ப�, ��⥬ ���न����\n"
"; �ਢ�� X Y Z (3 �᫠ ⨯� float), ��⥬ �������� ���祭�� AB/2	MN/2	K	U	D	I	Rok\n"
"; ᮮ⢥��⢥���, ��祬 ������ ��� ������ ��稭����� � ����� ��ப�. \n"
"; ���������� : ������ ����������� ������ �������� � ���浪� �����⠭��\n"
"; ࠧ��ᮢ !\n"
";-------------------------------------------------------------------------\n"
"#curve\n"
"�ਢ�� :	1\n"
"����. X Y Z :	0 0 0\n"
";AB/2\tMN/2\tK\t\tU\tD\tI\tRok\n"
"1\t0,5\t2,3561925\t42\t1000\t10\t99\n"
"1,5\t0,5\t6,28318\t\t46\t300\t10\t87\n"
"2,2\t0,5\t14,4198981\t72\t100\t10\t104\n"
"3\t0,5\t27,4889125\t42\t100\t10\t115\n"
"5\t0,5\t77,7543525\t44\t30\t10\t103\n"
"#endcurve\n"
"#curve\n"
"�ਢ�� :	2\n"
"����. X Y Z :	0 0 0\n"
";AB/2\tMN/2\tK\t\tU\tD\tI\tRok\n"
"1\t0,5\t2,3561925\t50\t1000\t10\t118\n"
"1,5\t0,5\t6,28318\t\t65\t300\t10\t123\n"
"2,2\t0,5\t14,4198981\t41\t300\t10\t177\n"
"3\t0,5\t27,4889125\t78\t100\t10\t214\n"
"5\t0,5\t77,7543525\t34\t100\t10\t264\n"
"#endcurve\n");


fclose(out);
printf("\n\n H����� ���� ������� ...");
getch();    /* ����-� */
return;
}

/* -------------------------------------------------------------------
   Check_VEZ_File �஢���� VEZ-䠩� �� ���४⭮��� � �����頥� �� 0,
   �᫨ 䠩� ����� �����४�� ���������.
   fp - 㪠��⥫� �� �஢��塞� VEZ-䠩�.
   ��  �ᯥ譮� �����襭�� �����頥� 0
----------------------------------------------------------------------*/
int Check_VEZ_File( FILE *fp )
{
char signature[8];

rewind(fp);
signature[7] = 0;
fread( signature, 7, 1, fp ); /* ���� 7 ᨬ����� - ᨣ����� */
strupr( signature );
return strncmp( signature, "VEZFILE", 7 ); /* ᨣ����� VEZFILE */
}

/* -------------------------------------------------------------------
   get_diapason �㭪�� �� ��������� �������쭮�� � ���ᨬ��쭮��
   ���祭�� �����ன ����稭� ��।���� ������⢮ �����䬨�᪨�
   ����� ��� �⮡ࠦ���� �� �����䬨�᪮� ������. ����稭� x0 - ��
   �窠 ����� �����䬨�᪮� 誠��, ��⭠� �⥯��� 10 ( 0.1, 1,
   10 � �.�.)
   �� ��ଠ�쭮� �����襭�� �㭪�� �����頥� 0, �� �訡�� 1.
   �訡�� - �᫨ ���祭�� min_val < 0.001 ��� max_val > 10**10
---------------------------------------------------------------------- */
short get_diapason( float min_val, float max_val, float *x0, short int *Decades )
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
   CreateFileName �㭪�� ᮧ���� ��� ��室���� 䠩��, �ᯮ����
   ���, ᮤ�ঠ饥�� � ��ப� instr. ��� ���७�� ��������� ��
   .ves � १���� ����頥��� � ��ப� outstr
---------------------------------------------------------------------- */
void CreateFileName( char *instr, char *outstr )
{
//char drive[MAXDRIVE];
//char dir[MAXDIR];
//char file[MAXFILE];
//char ext[MAXEXT];
char drive[_MAX_DRIVE];
char dir[_MAX_DIR];
char file[_MAX_FNAME];
char ext[_MAX_EXT];

char newext[] = ".ves";

//  fnsplit(instr, drive, dir, file, ext);
//  fnmerge(outstr, drive, dir, file, newext);
  _splitpath(instr, drive, dir, file, ext);
  _makepath(outstr, drive, dir, file, newext);

}


/*--------------------------------------------
  IndError �뤠�� �������� �訡��
---------------------------------------------- */
void IndError( void )
{
//textcolor(WHITE+128);
printf("\n\r****** ");
//textcolor(LIGHTGRAY);
}

/* --------------------------------------------------------------
_WriteProfilHdr ������� ��������� ��䨫� � ������ VES-䠩�
   �� ��ଠ�쭮� �����襭�� �㭪�� �����頥� 0, �� �訡�� 1.
-----------------------------------------------------------------*/
int _WriteProfilHdr( FILE *fp, PROFIL *pr )
{
  pr->hdr.count = 1; // ���� ��ࢠ� �ਢ�� 
  strcpy( pr->hdr.signat, B_SIGNATURE ); // ��������
  fseek( fp, 0L, SEEK_SET );
  fwrite( &(pr->hdr), sizeof(HEADER), 1, fp );
  return ferror(fp);
}

/* --------------------------------------------------------------
  _WriteCurve  ������� �ਢ�� �� �������� vez � ������ 
   VES-䠩� out
   �� ��ଠ�쭮� �����襭�� �㭪�� �����頥� 0, �� �訡�� 1.
-----------------------------------------------------------------*/
int _WriteCurve( FILE *out, VEZ *vez )
{
  fwrite( vez, sizeof(VEZ), 1, out );
  return ferror(out);
}

