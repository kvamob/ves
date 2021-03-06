/*
 * ���� vez_draw.h - ��⠢��� ���� �஥�� vez_draw
 */
#ifndef   VEZ_DRAW_H
#define   VEZ_DRAW_H

typedef  unsigned char  BYTE;
typedef  unsigned int   WORD;
typedef  unsigned int   BOOL;

#define  TRUE     1
#define  FALSE    0

#define   MAX_SAMPLES  100      /* ���ᨬ��쭮� �᫮ ����⮢ �� �ਢ��   */
#define   MAX_LAYERS   6        /* ���ᨬ��쭮� �᫮ ᫮�� � ������       */
#define   SCALE_MODUL  6.125    /* ����� �����䬨�᪮� 誠��            */

/*  ���� ������ */
#define   NOT_OPEN     1        /* �訡�� ������ 䠩��                   */
#define   FILE_END     2        /* �訡�� ������ 䠩��                   */
#define   SEEK_ERR     3        /* �訡�� ����樮���. 䠩������ 㪠��⥫�  */
#define   WRONG_PARAM  4        /* �訡��� ��ࠬ���                      */



typedef struct tagMODEL {       /* ������� - ����⥫� ������ ࠧ१�    */
  int n;                        /* ��᫮ ᫮��                             */
  float ro[MAX_LAYERS];         /* ���ᨢ ᮯ�⨢����� ᫮��              */
  float h[MAX_LAYERS-1];        /* ���ᨢ ��魮�⥩ ᫮��                  */
  } MODEL;

typedef struct tagCURVE {       /* ������� - ����⥫� �ਢ�� ���        */
  int n;                        /* ��᫮ ����⮢ �� �ਢ��                */
  float fRok[MAX_SAMPLES];      /* ����. ���祭�� �����.ᮯ�⨢����� ��*� */
  float tRok[MAX_SAMPLES];      /* �����.���祭�� �����.ᮯ�⨢����� ��*� */
  float AB2[MAX_SAMPLES];       /* ���祭�� ࠧ��ᮢ ��/2 � �����         */
  } CURVE;

typedef struct tagVEZ {
  char  ID_curve[20];     /* ������������ �ਢ��                          */
  float X,Y,Z;            /* ���न���� �ਢ��                            */
  MODEL model;            /* ��ࠪ���⨪� ࠧ१�                       */
  CURVE curve;            /* �ਢ�� ���                                   */
  float first_absc;       /* ��ࢠ� ������ �����뢠���� �ਢ�� � �    */
  float RokMin;           /* �������쭮� ���祭�� �����. ᮯ�⨢�����    */
  float RokMax;           /* ���ᨬ��쭮� ���祭�� �����. ᮯ�⨢�����   */
  float AB2Min;           /* �������쭮� ���祭�� ࠧ��� ��/2            */
  float AB2Max;           /* ���ᨬ��쭮� ���祭�� ࠧ��� ��/2           */
  int   RokDecads;        /* ��᫮ ����� �� �� �����. ᮯ��. ( ��� Y )  */
  int   AB2Decads;        /* ��᫮ ����� �� �� ࠧ��ᮢ ��/2  ( ��� X )  */
  float OrgRok;           /* ��砫쭮� ���祭�� ���.ᮯ. ������. ������ */
  float OrgAB2;           /* ��砫쭮� ���祭�� ��/2 ������. ������     */
  float RMS;              /* �।��� �⭮�⥫쭮� ��宦����� �����      */
			  /* �������� � ����⠭��� �ਢ묨 ���       */
  int   q18;              /* ������⢮ �祪 �ਢ�� � 蠣�� 1/8 ������   */
  int   q16;              /* ������⢮ �祪 �ਢ�� � 蠣�� 1/6 ������   */
  } VEZ;

typedef struct tagCOORD {  /* �ᯮ����⥫쭠� �������                   */
  float x;
  float y;
  } COORD;

typedef struct tagPLOT {  /* ������� - ����⥫� ��㭪� */
  float  cmMod;        /* ����� ������. ������ � �.                    */
  COORD  cmBlankLB;    /* ���न���� ������ ������� 㣫� ���. ������ � �  */
  COORD  cmBlankRT;    /* ���न���� �ࠢ��� ���孥�� 㣫� ���. ������ � �*/
  float  cmXSize  ;    /* ����� ������ �� �� X � �                       */
  float  cmYSize  ;    /* ����� ������ �� �� Y � �                       */
  COORD  cmFldName;    /* ���. ���न���� ������������ ���⪠ � �        */
  COORD  cmCrvName;    /* ���. ���न���� ������������ �ਢ�� � �         */
  COORD  cmDatName;    /* ���. ���न���� ���� ����஥��� � �             */
  float  cmNumHeight;  /* ���� ��஢�� �����ᥩ �� ���� � �            */
  float  cmTxtHeight;  /* ���� ⥪�⮢�� �����ᥩ � �                   */
  float  cmHdrHeight;  /* ���� ��������� � �                            */

  char   PLT_name[80]; /* ��� ��室���� PLT 䠩��                          */
  FILE   *plt;         /* �����⥫� �� ��室��� PLT 䠩�                   */
  char   hdrstr[80];   /* ��ப� - ���������                               */
  char   subhdrstr[80];/* ��ப� - ������������                            */
  char   datestr[60];  /* ��ப� � ��⮩ ����஥���                        */
  char   footstr[80];  /* ��ப� ��� �������                               */
  } PLOT_DESCR;

/*--------------------------------------------------------------------- */
/* ------ ��p���p� �����p�� ⨯�� ������ � ������� PLT - 䠩��� ---- */

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
   } PLT_BIN_HDR;             /*  ��������� ����筮�� PLT - 䠩�� */

/* =====================================================================
    ������� � 䠩��� PLT (ASCII)
 TR x y   -ᬥ饭�� ��砫� ���न��� � x,y (���न���� � ���=2.54 �)
 SC ax ay -����⠡�஢���� ���न��� ᮮ⢥��⢥��� �� ��� x,y
 SP n     -��⠭����� 梥� ��� n
 MA x y   -�������� � ��� x,y ��� �ᮢ��(���न���� � ���=2.54 �)
 PA x y   -�������� � ��� x,y c �ᮢ��� (���न���� � ���=2.54 �)
 SS "���_䠩��_����" -��⠭����� ⥪�騩 ���� �� 䠩��
 PS x y d u text -�ᮢ��� ⥪�� � ���न���� x,y(�), ���� d(�),
	   㣮� u(�ࠤ)
 RO angle -�������� ��㭮� �� angle �ࠤ�ᮢ

  ������ ������� ��稭����� � ����� ��p���.
  ���⢥��⢨� ������ ASCII � ����筮�� �p��⮢ :
     ASCII                 BIN
 TR x y           03[ float x ][ float y ]
 SC ax ay         05[ float x ][ float y ]
 SP n             07[ byte n ]
 MA x y           02[ float x ][ float y ]
 PA x y           01[ float x ][ float y ]
 SS "���_䠩��"   06[ byte n ][ ��p��� ������ n ]
 PS x y d u       04[ float x ][ float y ][ float d ][ float u ]
		    [ byte n ][ ��p��� ������ n ]
========================================================================= */

/* ============== �������� ��������� ������ ������� Borland (BGI) ======= */
typedef  struct   {    /* ��������� � �ࠪ���⨪��� CHR-䠩�� � 䮭⮬ */
   int HeaderOffset;   /* ���饭�� ���� FontHeader �⭮�⥫쭮 ��砫�
			  ���⮢��� 䠩��                                */
   char FontName[4];   /* ������������ 䮭�                              */
   int  FontSize;      /* ����� 䠩�� 䮭� �� ��⪨ FontHeader �� ����  */
   char FontVersion[3];/* ����� 䮭�                                    */
   } FONT_FILE_INFO;

typedef  struct   {    /* ���ଠ樮��� ��������� ���� ������ 16 ����  */
   char  FontHeader;   /* ��砫� ���ଠ樮����� ��������� ���� ,
			  ᮤ�ন� ᨬ��� '+'                             */
   int   CharsNum;     /* ��᫮ ᨬ����� � ����                         */
   char  Dummy1;       /* �� �ᯮ������                                 */
   char  StartChar;    /* ��砫�� ᨬ��� ����                         */
   int   DefOffset;    /* ���饭�� ��砫� ������ ��ࠧ�� ᨬ�����        */
		       /* �⭮�⥫쭮 ���� FontHeader                    */
   char  FillFlag;     /* ���� ������� �����஢ ᨬ����� (0 ���1)         */
   char  UpperMargin;  /* ���न��� y ���孥� �࠭��� ���� [-64,63]    */
   char  Dummy2;       /* �� �ᯮ������                                 */
   char  LowerMargin;  /* ���न��� x ������ �࠭��� ���� [-64,63]     */
   char  Dummy3;       /* �� �ᯮ������                                 */
   } FONT_HEADER;

typedef  struct   {
   FONT_FILE_INFO *ffi;/* ��������� � �ࠪ���⨪��� CHR-䠩�� � 䮭⮬ */
   FONT_HEADER    *hdr;/* ���ଠ樮��� ��������� ���� ������ 16 ����  */
   int   *SymbOffs;    /* �����⥫� �� ⠡����, � ���ன ᮤ�ন���      */
		       /* CharsNum ���塠�⮢�� ᬥ饭�� ��ࠧ�� ᨬ����� */
		       /* �⭮�⥫쭮  ��砫� ������ FontStart          */
   char  *Width;       /* �����⥫� �� ⠡���� �� CharsNum �������⮢��   */
		       /* ���祭�� �ਭ ᨬ�����                         */
   char  *FontStart;   /* �����⥫� �� ������� �����,��� �࠭���� ��ࠧ� */
		       /* ᨬ�����                                        */
   char  *buf;         /* �����⥫� �� ���� ��� ����㧪� 䠩�� ����    */
   } FONT;
/**************************************************************************/


		       /*  ��p���p� - ����⥫� ��䨫� ��� (䠩��) */
typedef struct  {
    WORD  npoints;     /* ��᫮ �祪 �� �p�䨫�                 */
    float h_scale;     /* �������⥫� ��p��. ����⠡� p��㭪�    */
    char  fname[64];   /* ��� 䠩�� ��䨫�                      */
    char  areaname[40];/* ��� ���⪠                            */
    char  profname[20];/* ��� ��䨫�                            */
    } PROFIL;

/* ---------------------------------------------------------------------- */

/* ----------------------- ��������� ������� ---------------------------- */
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

 ��� Y
 /|\         ��ᯮ������� ������ �� ���� �4
  |
  ���������������������������������������������������������������Ŀ
  �        �������� ���⪠ � ��䨫�                             �
  �        �ਢ�� ���                                             �
  �       Rok                    ��� ��ࠡ�⪨                   �
  �   1000 �����������������������������������Ŀ                  �
  �        �           �           �           �                  �
  �        �           �           �           �                  �
  �        �           �           �           �                  �
  �        �           �           �           �                  �
  �    100 �����������������������������������Ĵ                  �
  �        �           �           �           �                  �
  �        �           �           �           �                  �
  �        �           �           �           �                  �
  �        �           �           �           �                  �
  �    10  �������������������������������������                  �
  �        1          10          100           AB/2              �
  �                                                               �
  ����������������������������������������������������������������� --> ��� X
*/                                                      

#endif                                                  













