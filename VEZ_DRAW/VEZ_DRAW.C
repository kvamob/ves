#define VERSION "�.���⪮� (c) 1995  v1.0b"
/*------------------------ vez_draw.c ---------------------*/
/*         ���⪮� �. (c) 1995 ����ਭ���               */
/*               �ணࠬ�� vez_draw.exe                    */
/*---------------------------------------------------------*/
/* �ணࠬ�� �ᮢ���� �ਢ�� ��� �� ������� � ������    */
/* 䠩�� �p��� PLT ����� SURFER. �ਢ� ��� ᮤ�ঠ���  */
/* � 䠩�� �ଠ� VEZ. ������ �ਢ�� �����뢠���� �       */
/* �⤥��� PLT-䠩�. � ���쭥�襬 �� 䠩�� ����� �뢥��*/ 
/* �� ��p�� �p��p����� VIEW ��� �� �p���p (�����p)       */
/* �p��p����� PLOT (�� ����� SURFER)                      */
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

/* ------------------------- �p��⨯� ---------------------------*/

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


/* ----------------- �������H�� ������HH�� ---------------------- */

#define DELIMITER  58             /* ᨬ���-ࠧ����⥫� ':' */

char   *crv_begin = "#curve";     /* ��ப� - �ਧ��� ��砫� �ਢ�� */
char   *crv_end   = "#endcurve";  /* ��ப� - �ਧ��� ���� �ਢ��  */

#define LEN 120                   /* ����� �ᯮ���. ���� */
char str[LEN];                    /* �ᯮ���. ����        */

COMMAND1    cmnd1;
COMMAND2    cmnd2;
COMMAND3    cmnd3;
PLT_BIN_HDR plt_bin_hdr; /* ��������� PLT-䠩�� */

char   inname[64];       /* ��� �室���� ���-䠩�� */
FILE *inf;               /* �室��� VEZ - 䠩�  */
char plt_name[64];       /* ��� ��室���� PLT-䠩�� */
FILE *out;               /* ��室��� PLT - 䠩� */

FONT   bgi_font;         /* BGI-䮭�               */
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
VEZ    vez;         /* ������ �ਢ�� ���      */
PLOT_DESCR plot;    /* ���ᠭ�� ��㭪�       */
char   tag[4];      /* ��ப�, ᮤ��. ���� 3 ᨬ���� ��� ����樨 */
		    /* ���� ��室��� PLT - 䠩���                    */
 clrscr();
 visa();
 if ( argc < 3 ) 
    { IndError();
      out_help("�訡�� � ��������� ��ப� !"); 
      return -1; 
  }
  strcpy( inname, argv[1] );  /* ��� ��.䠩�� - �� ��������� ��ப� */
  printf("\n ���� %s\n", inname);
  strncpy( tag, argv[2], 3 );  /* ���� 3 ᨬ�. ��� ������. ���� ���.䠩� */

 if (NULL == ( inf = fopen ( inname, "rt")))
   { IndError();
     puts("�訡�� ��p��� ��. 䠩�� !\n"); return 1; }
 if ( Check_VEZ_File( inf ))
   { IndError();
     printf("\7�室��� 䠩� %s �� ���� VEZ-䠩���!\n", inname);
     out_help( "" );
     return 1; }

 if( get_info( inf, &pr ))   /* �p����� ��������� VEZ-䠩�� */
       return 1;

 if ( LoadBGIFont( "vez_draw.chr", &bgi_font )) return 1;  /* ����㧨� 䮭� */
 window( 1, 10, 79, 25);
 clrscr();
 recno = 1;
 while( ! ReadCurve( inf, &vez ))
  {
    CreateFileName( tag, recno, plt_name );  /* ᣥ����㥬  ��� ���. 䠩�� */
    if (NULL == ( out = fopen ( plt_name, "wb+")))
     { IndError(); 
       printf("�訡�� ��p��� ���. 䠩�� %s!\n", plt_name); 
       return 1; }
    WritePltHeader( &plt_bin_hdr );      /* ��襬 ��������� */
    SetScaleFactor(0.394,0.394);         /* ������� - ᠭ⨬��p� */
    SetPlotPosition( 3, 1 );             /* ��砫� ���न��� */
    PlotInitialize( &plot, &vez, &pr );
    DrawLogBlank( &plot, &vez );         /* ���㥬 ����� */
    DrawCurve( &plot, &vez );
    ++  recno;
    if ( ferror(out))   /* �᫨ �뫠 �訡�� ����� � 䠩� */
     { IndError();
       puts("\7\7�訡�� ����� �� ��� !");
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
   LineTo ����� ����� �� ⥪�饣� ��������� ��p� � ��� �
   ���p����⠬� x,y � ��p����� �㤠 ��p�
--------------------------------------------------------------*/
void pascal LineTo( float x, float y )
{
cmnd1.code = 0x01;         /* ASCII - ������� PA */
cmnd1.x = x;
cmnd1.y = y;
fwrite( &cmnd1, sizeof(COMMAND1), 1, out );
}

/* -----------------------------------------------------------
   MoveTo ��p����� ��p� � ��� � ���p����⠬� x,y
--------------------------------------------------------------*/
void pascal MoveTo( float x, float y )
{
cmnd1.code = 0x02;      /* ASCII - ������� MA */
cmnd1.x = x;
cmnd1.y = y;
fwrite( &cmnd1, sizeof(COMMAND1), 1, out );
}

/* -----------------------------------------------------------
   SetFont ���p㧨�� 䮭� �� 䠩�� � ������ fontname
--------------------------------------------------------------*/
void pascal SetFont( char *fontname )
{
cmnd2.code = 0x06;         /* ASCII - ������� SS */
cmnd2.n = strlen(fontname);
fwrite( &cmnd2, sizeof(COMMAND2), 1, out );
fwrite( fontname, 1, cmnd2.n, out );
}

/* -----------------------------------------------------------
   SetPlotPosition ��⠭����� ��砫� ���p����� x,y ( ������
   ������ ������� 㣫� p��㭪�. �ᯮ������ ��p�� ��砫��
   p�ᮢ����. ��窠, ��⠭�������� ������ �㭪樥�, ����
   ��砫�� ���न��� 0,0 , �⭮�⥫쭮 ���ன �ந��������
   ���쭥�訥 ����஥���
--------------------------------------------------------------*/
void pascal SetPlotPosition( float x, float y )
{
cmnd1.code = 0x03;          /* ASCII - ������� TR */
cmnd1.x = x;
cmnd1.y = y;
fwrite( &cmnd1, sizeof(COMMAND1), 1, out );
}

/* -----------------------------------------------------------
   SetScaleFactor ��⠭����� �⥯��� ᦠ�� p��㭪� �� ��� �
   � y. ������ ������� �������� ��⠭����� ������� ����p����
   p����ﭨ� � 䠩��. H��p���p, ������� SetScaleFactor(1,1)
   ��p������ p����p� � ���,� ������� SetScaleFactor(0.394,0.394)
   ��p������ p����p� � ᠭ⨬��p��, �.�. 1� = 0.394"
--------------------------------------------------------------*/
void pascal SetScaleFactor( float sf_x, float sf_y )
{
cmnd1.code = 0x05;        /* ASCII - ������� SC */
cmnd1.x = sf_x;
cmnd1.y = sf_y;
fwrite( &cmnd1, sizeof(COMMAND1), 1, out );
}

/* -----------------------------------------------------------
   SetColor ��⠭�������� 梥� ��p� color
--------------------------------------------------------------*/
void pascal SetColor( BYTE color )
{
cmnd2.code = 0x07;        /* ASCII - ������� SP */
cmnd2.n = color;
fwrite( &cmnd2, sizeof(COMMAND2), 1, out );
}

/* -----------------------------------------------------------
   OutTextXY �뢥�� ������� text ���⮩ height,� ��� x,y
   angle - 㣮� ������� ᨬ����� ( 0 ��� 90 �p���ᮢ )
   ���� ᨬ����� - � ���
--------------------------------------------------------------*/
void pascal OutTextXY( float x, float y, float height,
			       float angle, char *text )
{
cmnd3.code = 0x04;         /* ASCII - ������� PS */
cmnd3.x = x;
cmnd3.y = y;
cmnd3.height = height;
cmnd3.angle = angle;
cmnd3.len = strlen( text );
fwrite( &cmnd3, sizeof(COMMAND3), 1, out );
fwrite( text, 1, cmnd3.len, out );
}


/* -----------------------------------------------------------
   WritePltHeader ������� ��������� � PLT - 䠩�
--------------------------------------------------------------*/
void pascal WritePltHeader( PLT_BIN_HDR *hdr )
{
  /* H����祭�� ��������� ���� ���᭮ (�p��� CopyRight ) */
strcpy( hdr->copyright, "102758 CopyRight Golden Software 1987");
hdr->copyright[255] = 0x0C;
fwrite( hdr->copyright, sizeof(PLT_BIN_HDR), 1, out );
}

/* -----------------------------------------------------------------------
   LoadBGIFont ����㦠�� ������ ���� �ଠ� BGI � ������ ��
   䠩�� ���� � ������ fname � ���樠������� �������� bgi_font
   �� �ᯥ譮� �����襭�� �����頥� 0, �� �訡�� �����頥� 1
   ��� ���㧪� 䮭� �� ����� ���� �ਬ����� �㭪��  UnLoadBGIFont()
--------------------------------------------------------------------------*/
int LoadBGIFont( char *fname, FONT *bgi_font )
{
FILE *in;      /* �����⥫� 䠩�� ����     */
int  flen;     /* ����� �⮣� 䠩�� � ����� */
char *buffer;  /* �����⥫� �� ���� ��� ����㧪� 䠩�� ����    */
int   FontFileID;   /* �ਧ��� chr - 䠩��, ������ ���� = 'PK' 50h,4Bh */
char *p;       /* �ᯮ����⥫�� 㪠��⥫� */
int   i;

if ( NULL == ( in = fopen( fname, "rb" )))
   { IndError();
     printf("\7���� BGI-������ %s �� ������ !\n", fname );
     return 1; }

flen = (int) filelength(fileno(in)); /* ����� 䠩�� ���� � ����� */

       /* �뤥��� ������ ��� ���� */
if ( NULL == ( bgi_font->buf = (char *) malloc( flen )))
   { IndError();
     puts("\7���� ����� ��� ����㧪� 䠩�� ���� !");
     return 1; }

      /* ���⠥� 䠩� ���� � ���� */
if ( flen != fread( bgi_font->buf, 1, flen, in ))
    { IndError();
      printf("\7�訡�� �⥭�� �� 䠩�� ���� %s !\n", fname );
      free( bgi_font->buf );
      return 1; }

      /* ������������� ��������� bgi_font */
FontFileID =  * (int *) (bgi_font->buf);
      /* �⠥� CopyRight */
for ( i = 0, p = bgi_font->buf; (*p != 0x1A) && (i<254); p ++, i ++ );

bgi_font->ffi = (FONT_FILE_INFO *) ++ p;  /* ���� �������� ffi */
p = bgi_font->buf + bgi_font->ffi->HeaderOffset;
bgi_font->hdr = (FONT_HEADER *) p;       /* ���� �������� hdr */

    /* � ���� �� �� ? */
if ((FontFileID != 0x4B50) || (bgi_font->hdr->FontHeader != '+'))
  { IndError();
    printf("���� %s �� ᮤ�ন� ���� �ଠ� BGI !\n", fname );
    free( bgi_font->buf );
    return 1;}

   /* ��⠭�������� 㪠��⥫� �� �������� */
p += 16;
bgi_font->SymbOffs = (int *) p;   /* ���� ⠡���� 㪠��⥫�� �� ��ࠧ� */
p += 2 * bgi_font->hdr->CharsNum;
bgi_font->Width = (char *) p;     /* ���� ⠡���� �ਭ ᨬ����� */
p += bgi_font->hdr->CharsNum;
bgi_font->FontStart = (char *) p; /* ���� ��砫� ������ ��ࠧ�� ᨬ����� */

return 0;
}

/* --------------------------------------------------------------------
   UnLoadBGIFont ���㦠�� ����㦥��� ������ ���� �ଠ� BGI ��
   �����. ��� ���� �� ����㦥� � �������� bgi_font �㭪樥�
   LoadFont().
   �����頥��� ���祭�� : ���
-----------------------------------------------------------------------*/
void UnLoadBGIFont( FONT *bgi_font )
{
free( bgi_font->buf );  /* �᢮����� ������, ������� 䮭⮬ */
}


/* --------------------------------------------------------------------
   OutChar ���ᮢ��� ᨬ��� ch ���⮬, ����㦥��� � ��������
   bgi_font.
   cmX,xmY - ���न���� x � y ������ ������� 㣫� ��������� � �,
   cmH - ���� ᨬ���� � �

   �����頥��� ���祭�� : �ਭ� �뢥������� ᨬ���� � �
-----------------------------------------------------------------------*/
float OutChar( FONT *bgi_font, unsigned char ch, float cmX,
		   float cmY, float cmH )
{
int i;
int newcode; /* ����� ᨬ���� �⭮�. ��砫쭮�� ᨬ���� � ����      */
int offs;    /* ��砫쭮� ᬥ饭�� ��ࠧ� ᨬ���� � ���ᨢ� ��ࠧ��   */
char topx,   /* ����� �⮡ࠦ��� ���祭�� ���襣� ��� � ���न���� */
     topy,   /* ��ࠧ� ᨬ����                                        */
     x,y;
float widt;  /* ��ਭ� ᨬ���� � � */
float mx;
float xx, yy;

newcode = ch - bgi_font->hdr->StartChar;

if ( ch < 0 ) /* �᫨ �⮣� ᨬ���� ��� � ����, � ������� ��� �஡���� */
  {  ch = ' ';  newcode = 0; }

offs = bgi_font->SymbOffs[newcode];

mx = cmH / bgi_font->hdr->UpperMargin; /* ����⠡�� �����樥�� */

widt = bgi_font->Width[newcode] * mx;   /* ��ਭ� ᨬ���� � �    */

do  {

  x = bgi_font->FontStart[offs];
  y = bgi_font->FontStart[offs+1];
  topx = x & 0x80;  topy = y & 0x80;
  x &= 0x7f; y &= 0x7f;

  if ((topx == 0) && (topy == 0))  break;

  if ( x > 63 ) x = x - 129;
  if ( y > 63 ) y = y - 129;

  xx = cmX + x * mx;   /* �࠭��ଠ�� ���न��� */
  yy = cmY + y * mx;

  if ( topy == 0 )               /* ��砫� ᥣ����       */
     MoveTo( xx, yy );
   else
     LineTo( xx, yy );  /* ���筠� ���ୠ� �窠 */

   offs += 2;

//} while ((topx != 0) || (topy != 0));
} while ( 1 == 1);

return widt;
}

/* --------------------------------------------------------------------
   OutString ���ᮢ��� ��ப� s ���⮬, ����㦥��� � ��������
   bgi_font.
   cmX,xmY - ���न���� x � y ������ ������� 㣫� ��ࢮ�� ᨬ����
   ��ப� � �,
   cmH - ���� ᨬ����� � �

   �����頥��� ���祭�� : ���
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
"�������������������������������������������\n\r"\
"�           �ணࠬ��  vez_draw           �\n\r"\
"�   ��ᮢ���� �ਢ�� ��� � PLT - 䠩�     �\n\r"\
"�           �.���⪮� (c) 1995           �\n\r"\
"�������������������������������������������\n\r";
cputs(cpyright);
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
   ptr = strchr( str, ';' );   /* �饬 ᨬ��� ��砫� ��������� */
   if ( ptr ) *ptr = 0;        /* ��⠢�塞 ����� ���� ����� ��ப� */
   ptr = strchr( str, delim ); /* �饬 ᨬ��� - ࠧ����⥫� */
   if ( ptr ) return ++ ptr;   /* �᫨ ���� - ��室 */
   if ( strstr( str, brkstring )) return NULL;
   } while ( (! feof(fp)) && (!ferror(fp)) );
   return NULL;    /* �訡�� ��� ����� 䠩�� */
}

/* ------------------------------------------------------------
   get_info �p����� ���ଠ樮��� ���������� VEZ-䠩�� in
   � ��������� ��p���p� pr.
   ����p�頥� 1 �p� �訡��, ���� 0
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
		 /* �饬  ��� ���⪠  */
  if ( NULL ==
	(ptr = FindStringWithDelimiter( in,DELIMITER,str,LEN,crv_begin )))
    { IndError(); puts("\7��� ���⪠ �� ������� !\n"); return 1; }
  strncpy( pr->areaname, ptr, 39 ); /* ��� ���⪠ */
  printf(" ������� : %s\n", pr->areaname);
  puts("--------------------------------------------------------------------");
		 /* �饬  ��� ��䨫�  */
  if ( NULL ==
	(ptr = FindStringWithDelimiter( in,DELIMITER,str,LEN,crv_begin )))
    { IndError(); puts("\7��� ��䨫� �� ������� !\n"); return 1; }
  strncpy( pr->profname, ptr, 19 ); /* ��� ���⪠ */
  printf(" ������� : %s\n", pr->profname);

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
   ReadCurve �p����� ��।��� �ਢ�� �� ���-䠩�� fp �
   ��������� �������� vez. �� �訡�� �����頥� ��� �訡��
   �� ���⨦����  ���� 䠩�� �����頥� 1.
   �� �ᯥ譮� �����襭�� �����頥� 0.
---------------------------------------------------------------*/
int ReadCurve( FILE *fp, VEZ *vez )
{
int  code, cnt;
long oldpos;
char *ptr;
float a, r, rmin, rmax;
static int already = 0;
static int recno = 0;    /* ����� ����� */

 if ( !already ) {
   rewind(fp);  already = 1; }

 ++ recno ;
 clrscr();
 vez->ID_curve[19] = 0;
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
   if ( strstr( str, crv_end )) break; /* ����� �ਢ�� ������ ! */
   code = sscanf( str, "%f%f", &a, &r ); /* �⠥� */
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
   PlotInitialize ��������� ���� �������� plot, �ᯮ����
   ���ଠ�� �� ������� vez � prof.
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

 plot->cmXSize = ( plot->cmMod * vez->AB2Decads ); /* ࠧ���� */
 plot->cmYSize = ( plot->cmMod * vez->RokDecads );
 plot->cmBlankRT.x = plot->cmBlankLB.x + plot->cmXSize;
 plot->cmBlankRT.y = plot->cmBlankLB.y + plot->cmYSize;

 sprintf( plot->hdrstr,"���⮪ %s, ��䨫� %s",
	  prof->areaname, prof->profname );
 sprintf( plot->subhdrstr,"��� %s", vez->ID_curve );

 getdate( &d );
 gettime( &t );
 sprintf( plot->datestr, "��� %.2d-%.2d-%4d  �६� %.2d:%.2d",
   d.da_day,d.da_mon,d.da_year,t.ti_hour,t.ti_min );
	     /* �������� ������ ��ப� */
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
   DrawLogBlank H�p�ᮢ��� �����䬨�᪨� �����,  �ᯮ����
   �������� plot � vez.
   ��  �ᯥ譮� �����襭�� �����頥� 0, �� �訡�� 1.
---------------------------------------------------------------*/
int DrawLogBlank( PLOT_DESCR *plot, VEZ *vez )
{
int  i;
float x, y, AB2, Rok, x_, y_;
char  szAB2[6], szRok[10]; /* ⥪�⮢�� �।�⠢����� AB/2 � Rok */

  x = plot->cmBlankLB.x, y = plot->cmBlankLB.y;   /* ���⨪. ����� */
  AB2 = vez->OrgAB2;
  for( i = 0; i <= vez->AB2Decads; i ++, x += plot->cmMod, AB2 *= 10 )
   { MoveTo( x, y );
     LineTo( x, plot->cmBlankRT.y );
     sprintf( szAB2,"%g", AB2); /* �����襬 �᫠ AB/2 */
     x_ = plot->cmNumHeight * strlen(szAB2) / 2;
     OutString( &bgi_font, szAB2, x - x_,
		y - 2*plot->cmNumHeight, plot->cmNumHeight );

   }

  x = plot->cmBlankLB.x, y = plot->cmBlankLB.y;   /* ��ਧ. ����� */
  Rok = vez->OrgRok;
  for( i = 0; i <= vez->RokDecads; i ++, y += plot->cmMod, Rok *= 10 )
   { MoveTo( x, y );
     LineTo( plot->cmBlankRT.x, y );
     sprintf( szRok,"%-g", Rok); /* �����襬 �᫠ Rok */
     x_ = plot->cmNumHeight *(2 + strlen(szRok));
     y_ = plot->cmNumHeight / 2;
     OutString( &bgi_font, szRok, x - x_, y - y_, plot->cmNumHeight );
   }
	   /* ��� ���⪠ */
  OutString( &bgi_font,plot->hdrstr,plot->cmFldName.x,plot->cmFldName.y,
	     plot->cmHdrHeight );
	   /* ��� �ਢ�� */
  OutString( &bgi_font,plot->subhdrstr,plot->cmCrvName.x,plot->cmCrvName.y,
	     plot->cmTxtHeight );
	   /* ��� ����஥��� */
  OutString( &bgi_font,plot->datestr,plot->cmDatName.x,plot->cmDatName.y,
	     plot->cmTxtHeight );
	   /* �������� �ᥩ */
  OutString( &bgi_font,"Rok ���",plot->cmBlankLB.x,
	     plot->cmBlankRT.y + 2*plot->cmTxtHeight, plot->cmTxtHeight );
  OutString( &bgi_font,"AB/2 �",plot->cmBlankRT.x + 2*plot->cmTxtHeight,
	     plot->cmBlankLB.y, plot->cmTxtHeight );
  OutString( &bgi_font,plot->footstr, plot->cmBlankLB.x,
	     plot->cmBlankLB.y-3*plot->cmTxtHeight, plot->cmTxtHeight );


 return 0;
}

/* ------------------------------------------------------------
   DrawCurve H�p�ᮢ��� �ਢ�� ���,  �ᯮ���� �������� plot �
   vez.
   ��  �ᯥ譮� �����襭�� �����頥� 0, �� �訡�� 1.
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
   DrawPoint H�p�ᮢ��� ��� �� ��䨪� � ���� "���⨪�"
   x, y - ���न���� 業�� "���⨪�" � ᠭ⨬����
---------------------------------------------------------------*/
void DrawPoint( float x, float y )
{
#define STROKE  0.1       /* ����� ����  */

 MoveTo( x, y + STROKE );
 LineTo( x, y - STROKE );
 MoveTo( x - STROKE, y );
 LineTo( x + STROKE, y );

}


/* ------------------------------------------------------------
   out_error �뢮��� �� ��࠭ ᮮ�饭�� �� �訡��
---------------------------------------------------------------*/
void pascal out_error( char *msg )
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
char *fname = "vez_draw.hlp";
FILE *out;

printf
 ("\7 %s\n\n"
  " �ᯮ�짮����� �ணࠬ�� : vez_draw.exe <VEZfile> <OutFile>\n"
  "  ��� VEZfile - ��� �室����  䠩�� �ଠ� VEZ,\n"
  "      OutFile - ���� �� ᨬ���� �⮣� ��ࠬ��� ���� �ᯮ�짮����\n"
  "                ��� �����樨 ���� ��室��� 䠩��� (�� ������ 䠩��\n"
  "                �� �ਢ��) � ���� :\n"
  "  xxx#dddd.plt ; �����\n"
  "                xxx  - ���� �� ᨬ���� �� OutFile,\n"
  "                dddd - ᨬ���쭮� �।�⠢����� ���浪����� �����\n"
  "                       �ਢ�� � VEZ-䠩��\n\n"
  " �ਬ�� ��ଫ���� 䠩�� �ଠ� VEZ ᬮ��� � 䠩�� %s\n", hint, fname);

if ( NULL == ( out = fopen( fname, "wt")))  /* ��஥� 䠩� */
      { IndError(); printf("\7�訡�� ������ 䠩�� %s ��� �����!\n", fname );
	return;
      }
fprintf( out,
"VEZFILE\n"
";=========================================================================\n"
"; ������� 䠩�� �ଠ� VEZ ��� �ணࠬ�� vez_draw.exe. %s\n"
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
"; �ਢ�� X Y Z (3 �᫠ ⨯� float), ��⥬ �������� ���� ���祭�� AB/2 �\n"
"; ���. ᮯ�⨢�. ᮮ⢥��⢥���, ��祬 ������ ��� ������ ��稭�����\n"
"; � ����� ��ப�. \n"
"; ���������� : ������ ����������� ������ �������� � ���浪� �����⠭��\n"
"; ࠧ��ᮢ !\n"
";-------------------------------------------------------------------------\n"
"#curve\n"
"�ਢ�� : 1-1\n"
"����. X Y Z : 0 0 0\n"
"1.5  100\n"
"3    110\n"
"5    160\n"
"7    200\n"
"#endcurve\n\n"
"#curve\n"
"�ਢ�� : 1-2\n"
"����. X Y Z : 100 0 0 \n"
"1.5  120\n"
"3    140\n"
"5    170\n"
"7    210\n"
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
   CreateFileName �㭪�� ᮧ���� ��� 䠩��, �ᯮ���� ᨬ���� ��
   ��ப� str ( �� ����� ��� ) � 楫��� �᫠ num. �������
   ����砥��� � ���� xxx#dddd.plt
   xxx  - ᨬ���� �� ��ப� str
   dddd - ᨬ���쭮� �।�⠢����� �᫠ num
   ������� ����頥��� � ��ப� outstr
---------------------------------------------------------------------- */
void CreateFileName( char *str, int num, char *outstr )
{
 sprintf( outstr,"%.3s#%04d.plt", str,  num );
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
