//#define _VERSION_ "�.�������� (c) 1995-2000  v1.1b"
/*------------------------ ves_comp.c ---------------------*/
/*         �������� �. (c) 1995 ������������               */
/*               ��������� vez_comp.exe                    */
/*---------------------------------------------------------*/
/* ��������� ����������� ��������� ����� VEZ-������� (���� */
/* ��� ��� �������� vez_draw.exe, vez_asom.exe � ��������  */
/* ����� ������� VES ��� ������� VES for Windows           */
/*---------------------------------------------------------*/
/* Project  : ves.h ves_comp.c                             */
/* Model    : small                                        */
/* Library  :                                              */
/* Compiler : Turbo C v2.0 ,Borland C++ v x.x, C++ Builder */
/*---------------------------------------------------------*/

#pragma  hdrstop

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <dos.h>
//#include <dir.h>
#include <io.h>

//#include <windows.h>
#include "ves.h"

/* ------------------------- �p������� ---------------------------*/

void pascal visa( void );
char *FindStringWithDelimiter( FILE *fp,char delim,char *str,int len,
			       char *brkstring );
int ScanFile( FILE *fp, char *str,int len, char *substr );
int txt_OpenProfil( FILE *in, PROFIL *pr );
int _WriteCurve( FILE *out, VEZ *vez );
int _WriteProfilHdr( FILE *fp, PROFIL *pr );
int txt_ReadCurve( FILE *fp, VEZ *vez );
int Check_VEZ_File( FILE *fp );

short get_diapason( float min_val, float max_val, float *x0, int *Decades );

//void out_error( char *msg );
void out_help( char *hint );
void CreateFileName( char *instr, char *outstr );
void IndError( void );


/* ----------------- �������H�� ������HH�� ---------------------- */

#define DELIMITER  58             /* ������-����������� ':' */

char   *crv_begin = "#curve";     /* ������ - ������� ������ ������ */
char   *crv_end   = "#endcurve";  /* ������ - ������� ����� ������  */

#define LEN 120          /* ����� �������. ������ */
char str[LEN];           /* �������. �����        */

char   inname[64];       /* ��� �������� ���-����� */
FILE *inf;               /* ������� VEZ - ����  */
char outname[64];        /* ��� ��������� VES-����� */
FILE *out;               /* �������� VES - ���� */

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

 clrscr();
 visa();
 if ( argc < 2 )
    { IndError();
      out_help("������ � ��������� ������ !");
      return -1;
  }
  strcpy( inname, argv[1] );  /* ��� ��.����� - �� ��������� ������ */
  printf("\n ���� %s\n", inname);

 if (NULL == ( inf = fopen ( inname, "rt")))
   { IndError();
     puts("������ ���p���� ��. ����� !\n"); return 1; }
 if ( Check_VEZ_File( inf ))
   { IndError();
     printf("\7������� ���� %s �� �������� VEZ-������!\n", inname);
     out_help( "" );
     return 1; }

  CreateFileName( inname, outname );  /* �����������  ��� ���. ����� */
  if ( ! access(outname, 0 ))         /* ��������, ���� �� ��� ����� ���� */
   { IndError();
     printf("\7���� %s ��� ���������� !\n", outname);
     return -1;
    }

  if (NULL == ( out = fopen ( outname, "wb+"))) /* ������� ��� */
    { IndError();
      printf("������ ���p���� ���. ����� %s!\n", outname);
      return 1; }

 if( txt_OpenProfil(  inf, &pr ))   /* �p������� ��������� VEZ-����� */
       return 1;
 
 if( _WriteProfilHdr( out, &pr ))   /* �������� ��������� VES-����� */
    {  IndError();
       puts("\7\7������ ������ �� ���� !");
       return 1; 
     }
 
 clrscr();
 recno = 0;
 while( ! txt_ReadCurve( inf, &(pr.vez))) // ������ ������
  {
    ++  recno;
  if( _WriteCurve( out, &(pr.vez) ))   /* �������� ��������� VES-����� */
    {  IndError();
       puts("\7\7������ ������ �� ���� !");
       return 1; 
     }
//     printf("\nPress Any Key ...");
//     getch();
  }
 
 /* �������� ����������. ��������� VES-����� */  
 pr.hdr.npoints = recno; // ���-�� ������
 if( _WriteProfilHdr( out, &pr ))  
    {  IndError();
       puts("\7\7������ ������ �� ���� !");
       return 1; 
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
"_ ��������� ����������� ��������� ����� VEZ-������� _\n\r"
"_ (������� ��� �������� vez_draw.exe, vez_asom.exe) _\n\r"
"_ �  ��������  �����  �������  VES  ���  �������    _\n\r"
"_                VES for Windows                    _\n\r"
"_____________________________________________________\n\r";
cputs(cpyright);
}

/*-------------------------------------------------------------------------
   FindStringWithDelimiter ������� ���� � ����� fp ������,
   ���������� ������-����������� delim. ��� ���� ������ ����������
   � ������� ������� � ���� �����. ������ ����������� �� �������
   ����� str �������� len ����. ����� ������� ����������� ������������
   ��������� ������ ��������� ������ ����� ������� ������ �������� ';'
   (������������) ������� ��������. ����� �������������, ���� �����������
   ���������. � ���� ������ ������� ���������� ��������� �� ������ �
   c�����, ������ ����� �� ������������. ��� ���������� ����� ����� ���
   ��� ������ ������������ NULL. ���� � ������ ���������� ���������,
   ��������� � brkstring, �� ���������� ����������� ������ � �����
   � ����� NULL
---------------------------------------------------------------------------*/
char *FindStringWithDelimiter( FILE *fp,char delim,char *str,int len,
			       char *brkstring )
{
char *ptr;

  do {
   str[0] = 0;
   fgets( str, len, fp );      /* ������ ������ */
   str[strlen(str) - 1] = 0;   /* ���p�� ������ ��p����� ��p��� 0xA */
   ptr = strchr( str, ';' );   /* ���� ������ ������ ����������� */
   if ( ptr ) *ptr = 0;        /* ��������� ������ ���� ����� ������ */
   ptr = strchr( str, delim ); /* ���� ������ - ����������� */
   if ( ptr ) return ++ ptr;   /* ���� ���� -����� */
   if ( strstr( str, brkstring )) return NULL;
   } while ( (! feof(fp)) && (!ferror(fp)) );
   return NULL;    /* ������ ��� ����� ����� */
}

/* ------------------------------------------------------------
   txt_OpenProfil �p������� �������������� ���������� VEZ-����� in
   � ��������� ����� ��p����p� pr.
   ����p����� 1 �p� ������, ����� 0
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
		 /* ����  ��� �������  */
  if ( NULL ==
	(ptr = FindStringWithDelimiter( in,DELIMITER,str,LEN,crv_begin )))
    { IndError(); puts("\7��� ������� �� ������� !\n"); return 1; }
  strncpy( pr->hdr.areaname, ptr, 39 ); /* ��� ������� */
  printf(" ������� : %s\n", pr->hdr.areaname);
  puts("--------------------------------------------------------------------");
		 /* ����  ��� �������  */
  if ( NULL ==
	(ptr = FindStringWithDelimiter( in,DELIMITER,str,LEN,crv_begin )))
    { IndError(); puts("\7��� ������� �� ������� !\n"); return 1; }
  strncpy( pr->hdr.profname, ptr, 19 ); /* ��� �p����� */
  printf(" ������� : %s\n", pr->hdr.profname);

  return 0;
}

/*-------------------------------------------------------------------------
   ScanFile ������� ������������� ������ ����� fp ������, ������� � �������
   �������, �� ������� ����������� ��������� substr. ������ ����������� ��
   ������� ����� str �������� len ����. ����� ������� ������������
   ��������� ������ ��������� ������ ����� ������� ������ �������� ';'
   (������������) ������� ��������. ����� �������������, ���� ���������
   ����������. � ���� ������ ������� ���������� 0. ��� ���������� �����
   ����� ��� ��� ������ ������������ 1.
---------------------------------------------------------------------------*/
int ScanFile( FILE *fp, char *str,int len, char *substr )
{
char *ptr;

 do {
   str[0] = 0;
   fgets( str, len, fp );      /* ������ ������ */
   ptr = strchr( str, ';' );   /* ���� ������ ������ ����������� */
   if ( ptr ) *ptr = 0;        /* ��������� ������ ���� ����� ������ */
   if ( strstr( str, substr )) return 0; /* ��������� ������� ! */
   } while ( (! feof(fp)) && (!ferror(fp)) );
   return 1;    /* ������ ��� ����� ����� */
}

/* ------------------------------------------------------------
   txt_ReadCurve �p������� ��������� ������ �� ���������� 
   ���-����� fp � ��������� ��������� vez. ��� ������ ���������� 
   ��� ������.
   ��� ����������  ����� ����� ���������� 1.
   ��� �������� ���������� ���������� 0.
---------------------------------------------------------------*/
int txt_ReadCurve( FILE *fp, VEZ *vez )
{
int  code, cnt;
long oldpos;
char *ptr;
float a, r, rmin, rmax;
static int already = 0;
static int recno = 0;    /* ����� ������ */

 if ( !already ) {
   rewind(fp);  already = 1; }

 memset( vez, 0, sizeof(VEZ) ); // ������� ��������� vez

 ++ recno ;
 clrscr();
// vez->ID_curve[19] = 0;
 rmin = 10000000;
 rmax = 0;
 code = ScanFile( fp, str, LEN, crv_begin ); /* ���� ������� ������ ������ */
 if ( code )   {  puts("\n <><> ������ ������ ��� ... <><>\n"); return 1; }
 oldpos = ftell( fp );  /* �������� ��������� */

 code = ScanFile( fp, str, LEN, crv_end ); /* ���� ������� ����� ������ */
 if ( code )
  {  IndError(); puts("\7������� ����� ������ �� ������ ...\n"); return 1; }
 fseek( fp, oldpos, SEEK_SET ); /* �������� */

	      /* ���� ��� ������ */
  if ( NULL ==
	(ptr = FindStringWithDelimiter( fp,DELIMITER,str,LEN,crv_end )))
    { IndError(); puts("\7��� ������ �� ������� !\n"); return 1; }
  strncpy( vez->ID_curve, ptr, 19 ); /* ��� ������ */
  printf(" ������ #%3d,  ��� : %s\n", recno, vez->ID_curve );
	      /* ���� ���������� */
  if ( NULL ==
	(ptr = FindStringWithDelimiter( fp,DELIMITER,str,LEN,crv_end )))
    { IndError(); puts("\7���������� ������ �� ������� !\n"); return 1; }
  sscanf( ptr, "%f%f%f", &(vez->X), &(vez->Y), &(vez->Z) );
  printf("���������� : %8.1f %8.1f %8.1f\n", vez->X, vez->Y, vez->Z );

	     /* ������ ���� ������� */
  cnt = 0;   /* ������� �������� */
  do {
   str[0] = 0;
   fgets( str, LEN, fp );    /* ������ ������ */
   ptr = strchr( str, ';' ); /* ���� ������ ������ ����������� */
   if ( ptr ) *ptr = 0;      /* ��������� ������ ���� ����� ������ */
             // ������� ��� ������� � ������ �� �����
   ptr = str;
   while (ptr) { if (ptr = strchr(str,',')) *ptr = '.';}

   if ( strstr( str, crv_end )) break; /* ����� ������ ������ ! */
   code = sscanf( str, "%f%f%f%f%f%f%f", &a, &r, &r, &r, &r, &r, &r ); /* ������ */
   if ( code == 7 )
//   code = sscanf( str, "%f%f", &a, &r ); /* ������ */
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
  vez->RMS = 0;     // ���� �� ���������
  vez->model.n = 0; // ������ ���� ���

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
char *fname = "ves_comp.hlp";
FILE *out;

printf
 ("\7 %s\n\n"
  " ������������� ��������� : ves_comp.exe <VEZfile>\n"
  "  ��� VEZfile - ��� ��������  ����� ������� VEZ,\n"
  "\n"
  " � ���������� ����� ������ �������� ���� ������� � ������ ��������\n"
  " � ����������� .ves\n"
  "\n"
  " ������ ���������� ���������� ����� ������� VEZ �������� � ����� %s\n",
    hint, fname);

if ( NULL == ( out = fopen( fname, "wt")))  /* ������� ���� */
      { IndError(); printf("\7������ �������� ����� %s ��� ������!\n", fname );
	return;
      }
fprintf( out,
"VEZFILE\n"
";=========================================================================\n"
"; ��������� ���������� ����� ������� VEZ\n"
";-------------------------------------------------------------------------\n"
"; ������ ������� 7 ��������� � ����� ������� VEZ (vez-�����) ������ ����\n"
"; ��������� �������: VEZFILE � ����� ��������.\n"
"; ������� ������� ������ ������� ������������ - ��� �������\n"
"; ������ ��� � �� ����� ������ ������������. ������ ������ �����������.\n"
";   VEZ-���� ������ ��������� ������ ��� ������ ������� � ������ �������\n"
"; ����� ������� � ������� ������ ���� ������ � ������ �����.\n"
";-------------------------------------------------------------------------\n"
"Area   : ������ - ����������� ; �������\n"
"Profil : �������. 1           ; �������\n"
";-------------------------------------------------------------------------\n"
"; ����� ���� �������� ������ - ����� ������, ������������ #curve\n"
"; � ��������������� #endcurve. � ������ ����� ������� �������� ���\n"
"; ������ (�� ����� 20 ����. �� ':' �� ����� ������, ����� ����������\n"
"; ������ X Y Z (3 ����� ���� float), ����� �������� ���� �������� AB/2 �\n"
"; ���. ���������. ��������������, ������ ������ ���� ������ ����������\n"
"; � ����� ������. \n"
"; ���������� : ������� ����������� ������ �������� � ������� �����������\n"
"; �������� !\n"
";-------------------------------------------------------------------------\n"
"#curve\n"
"������ : 1-1\n"
"�����. X Y Z : 0 0 0\n"
"1.5  100\n"
"3    110\n"
"5    160\n"
"7    200\n"
"#endcurve\n\n"
"#curve\n"
"������ : 1-2\n"
"�����. X Y Z : 100 0 0 \n"
"1.5  120\n"
"3    140\n"
"5    170\n"
"7    210\n"
"#endcurve\n");

fclose(out);
printf("\n\n H������ ����� ������� ...");
getch();    /* ����-� */
return;
}

/* -------------------------------------------------------------------
   Check_VEZ_File ��������� VEZ-���� �� ������������ � ���������� �� 0,
   ���� ���� ����� ������������ ���������.
   fp - ��������� �� ����������� VEZ-����.
   ���  �������� ���������� ���������� 0
----------------------------------------------------------------------*/
int Check_VEZ_File( FILE *fp )
{
char signature[8];

rewind(fp);
signature[7] = 0;
fread( signature, 7, 1, fp ); /* ������ 7 �������� - ��������� */
strupr( signature );
return strncmp( signature, "VEZFILE", 7 ); /* ��������� VEZFILE */
}

/* -------------------------------------------------------------------
   get_diapason ������� �� ��������� ������������ � �������������
   ��������� ��������� �������� ���������� ���������� ���������������
   ����� ��� ����������� �� ��������������� ������. �������� x0 - ���
   ����� ������� ��������������� �����, ������� ������� 10 ( 0.1, 1,
   10 � �.�.)
   ��� ���������� ���������� ������� ���������� 0, ��� ������ 1.
   ������ - ���� �������� min_val < 0.001 ��� max_val > 10**10
---------------------------------------------------------------------- */
short get_diapason( float min_val, float max_val, float *x0, int *Decades )
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
   CreateFileName ������� ������� ��� ��������� �����, ���������
   ���, ������������ � ������ instr. ��� ���������� ���������� ��
   .ves � ��������� ���������� � ������ outstr
---------------------------------------------------------------------- */
void CreateFileName( char *instr, char *outstr )
{
char drive[MAXDRIVE];
char dir[MAXDIR];
char file[MAXFILE];
char ext[MAXEXT];
char newext[] = ".ves";

  fnsplit( instr, drive, dir, file, ext);
  fnmerge( outstr,drive, dir, file,newext);
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

/* --------------------------------------------------------------
_WriteProfilHdr �������� ��������� ������� � �������� VES-����
   ��� ���������� ���������� ������� ���������� 0, ��� ������ 1.
-----------------------------------------------------------------*/
int _WriteProfilHdr( FILE *fp, PROFIL *pr )
{
  pr->hdr.count = 1; // ���� ������ ������ 
  strcpy( pr->hdr.signat, B_SIGNATURE ); // ���������
  fseek( fp, 0L, SEEK_SET );
  fwrite( &(pr->hdr), sizeof(HEADER), 1, fp );
  return ferror(fp);
}

/* --------------------------------------------------------------
  _WriteCurve  �������� ������ �� ��������� vez � �������� 
   VES-���� out
   ��� ���������� ���������� ������� ���������� 0, ��� ������ 1.
-----------------------------------------------------------------*/
int _WriteCurve( FILE *out, VEZ *vez )
{
  fwrite( vez, sizeof(VEZ), 1, out );
  return ferror(out);
}

