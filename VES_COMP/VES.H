/*
 * ���� ves.h
*/
#ifndef VES_WIN_H
#define VES_WIN_H
// ������ ������樨
#define AUTO 1   /* ��⮬��. �������� */
#define MANUAL 2 /* ��筠� ��������   */

#define MAX_ITERATION 100 /* ����. ������⢮ ��p�権 */
#define MAX_SAMPLES 50    /* ����. ������⢮ ����⮢ �� �ਢ�� */
#define MAX_LAYERS 6      /* ����. ������⢮ ᫮�� � ������ ࠧ१� */
#define MIN_LAYERS 1      /* ���.  ������⢮ ᫮�� � ������ ࠧ१� */

#define MAX_LAYERS_TC 8 /* ����. ������⢮ ᫮�� � ������ ࠧ१� \
                           �� ���� ⥮���᪮� �ਢ�� ��� */

#define SCALE_MODUL 6.125         /* ����� �����䬨�᪮� 誠��  */
#define B_SIGNATURE "VEZBINFILE_" /* �ਧ��� ����୮��  VEZ-䠩�� */
#define T_SIGNATURE "VEZFILE"     /* �ਧ��� ⥪�⮢��� VEZ-䠩�� */

#define MIN_RESIST 0.1    // �������쭮� ���祭�� �. ᮯ�. ᫮�, ���
#define MAX_RESIST 100000 // ���ᨬ��쭮� ���祭�� �. ᮯ�. ᫮�
#define DEF_RESIST 100    // ����稢����� ���祭�� �. ᮯ�. ᫮�
#define MIN_THICK 0.1     // �������쭮� ���祭�� ��魮�� ᫮�
#define MAX_THICK 1000    // ���ᨬ��쭮� ���祭�� ��魮�� ᫮�
#define DEF_THICK 1       // ����稢����� ���祭�� ��魮�� ᫮�

/*  ���� ������ */
// ������� �訡��
#define F_NOT_OPEN -2 // �訡�� ������ VEZ-䠩��
#define F_TEXT_VEZ -3 // �ਧ��� ⥪�⮢��� VEZ-䠩��
#define F_NOT_VEZ -4  // �� �� VEZ-䠩�
#define F_READ_ERR -5 // �訡�� �⥭��
#define F_WRIT_ERR -6 // �訡�� �����

#pragma pack(push, 2)
typedef struct tagMODEL
{                          /* ������� - ����⥫� ������ ࠧ१�    */
  short n;                 /* ��᫮ ᫮��                             */
  float ro[MAX_LAYERS];    /* ���ᨢ ᮯ�⨢����� ᫮��              */
  float h[MAX_LAYERS - 1]; /* ���ᨢ ��魮�⥩ ᫮��                  */
} MODEL;
#pragma pack(pop)

#pragma pack(push, 2)
typedef struct tagMODEL_TC
{                             /* ������� - ����⥫� ������ ࠧ१�    */
                              /* �� ���� ⥮���᪮� �ਢ��        */
  short n;                    /* ��᫮ ᫮��                             */
  float ro[MAX_LAYERS_TC];    /* ���ᨢ ᮯ�⨢����� ᫮��              */
  float h[MAX_LAYERS_TC - 1]; /* ���ᨢ ��魮�⥩ ᫮��                  */
} MODEL_TC;
#pragma pack(pop)

#pragma pack(push, 2)
typedef struct tagCURVE
{                          /* ������� - ����⥫� �ਢ�� ���        */
  short n;                 /* ��᫮ ����⮢ �� �ਢ��                */
  float fRok[MAX_SAMPLES]; /* ����. ���祭�� �����.ᮯ�⨢����� ��*� */
  float tRok[MAX_SAMPLES]; /* �����.���祭�� �����.ᮯ�⨢����� ��*� */
  float AB2[MAX_SAMPLES];  /* ���祭�� ࠧ��ᮢ ��/2 � �����         */
} CURVE;
#pragma pack(pop)

#pragma pack(push, 2)
typedef struct
{                        /* ������� - ����⥫� �����᪮� �ਢ�� ���     */
  short n;               /* ��᫮ ����⮢ �� �ਢ��                 */
  short yf[MAX_SAMPLES]; /* ���祭�� �����. �p����� � ���. ������� */
  short yt[MAX_SAMPLES]; /* ���祭�� ⥮p. �p�����   � ���. ������� */
  short x[MAX_SAMPLES];  /* ���祭�� ������ � ���. ������� */
} LOGCURVE;
#pragma pack(pop)

#pragma pack(push, 2)
typedef struct tagVEZ
{
  char ID_curve[20]; /* ������������ �ਢ��                          */
  float X, Y, Z;     /* ���न���� �ਢ��                            */
  MODEL model;       /* ��ࠪ���⨪� ࠧ१�                       */
  CURVE curve;       /* �ਢ�� ���                                   */
  float first_absc;  /* ��ࢠ� ������ �����뢠���� �ਢ�� � �    */
  float RokMin;      /* �������쭮� ���祭�� �����. ᮯ�⨢�����    */
  float RokMax;      /* ���ᨬ��쭮� ���祭�� �����. ᮯ�⨢�����   */
  float AB2Min;      /* �������쭮� ���祭�� ࠧ��� ��/2            */
  float AB2Max;      /* ���ᨬ��쭮� ���祭�� ࠧ��� ��/2           */
  short RokDecads;   /* ��᫮ ����� �� �� �����. ᮯ��. ( ��� Y )  */
  short AB2Decads;   /* ��᫮ ����� �� �� ࠧ��ᮢ ��/2  ( ��� X )  */
  float OrgRok;      /* ��砫쭮� ���祭�� ���.ᮯ. ������. ������ */
  float OrgAB2;      /* ��砫쭮� ���祭�� ��/2 ������. ������     */
  float RMS;         /* �।��� �⭮�⥫쭮� ��宦����� �����      */
                     /* �������� � ����⠭��� �ਢ묨 ���       */
  short q18;         /* ������⢮ �祪 �ਢ�� � 蠣�� 1/8 ������   */
  short q16;         /* ������⢮ �祪 �ਢ�� � 蠣�� 1/6 ������   */
} VEZ;
#pragma pack(pop)

//typedef struct tagcmCOORD {  /* �ᯮ����⥫쭠� �������                 */
//  float x;
//  float y;
//  } cmCOORD;

#pragma pack(push, 2)
typedef struct tagpxCOORD
{ /* �ᯮ����⥫쭠� �������                 */
  short x;
  short y;
} pxCOORD;
#pragma pack(pop)

//typedef struct  {      /* ������� �ᯮ������ �p� p�ᮢ���� �p���� ���  */
//  short    DrawType;  /* 0, �᫨ �� p�ᮢ��� ⥮p. �p����,� 1, �᫨ p�ᮢ��� */
//  LOGCURVE LCurve;     /* ���p������ �祪 �p���� ��� � �����᪨� ����.   */
//  short    pxXMod;       /* ����� ������. ������ � ����. �� �� X         */
//  short    pxYMod;       /* ����� ������. ������ � ����. �� �� Y         */
//  RECT   Frame;        /* ���p������ ����p. ������, � ���p� 㬥頥���    */
//		       /* �p���� ��� ����p� ���� � ���. �������           */
//  RECT   Legend;       /* ���p������ ������, ��� �ᮢ��� �������         */
//  short    pxXSize;      /* ����� ������ �� �� X � ���ᥫ��                 */
//  short    pxYSize;      /* ����� ������ �� �� Y � ���ᥫ��                 */
////  pxCOORD  pxFldName;  /* ���. ���न���� ������������ ���⪠ � ���ᥫ��  */
////  pxCOORD  pxCrvName;  /* ���. ���न���� ������������ �ਢ�� � ���ᥫ��   */
//  short    pxChHeight;   /* ���� ᨬ����� � ���ᥫ��                       */
//  short    pxChWidth;    /* ���� ᨬ����� � ���ᥫ��                       */
//  RECT     TxtFrame;   /* ����� ��� ⥪�� */
//  pxCOORD  pxFootStr;  /* ��ப� � ����p���� ANSI, �����. � ࠬ�� - �����
//			  �ਢ��, ��� �ਢ��, ��� ��䨫� � �.�.             */
//  char   footstr[140];
//  char   hdrstr[80];   /* ��ப� - ��������� � ����p���� ANSI              */
//  char   subhdrstr[80];/* ��ப� - ������������ � ����p���� ANSI           */
//  } VES_PAshortDATA;

/*  ��p���p� - ����⥫� ��������� ��䨫� ��� (䠩��) */
#pragma pack(push, 2)
typedef struct
{
  char signat[12];   /* �������� 䠩�� - ᨬ���� VEZBINFILE_  */
                     /* ��᫥���� ᨬ��� - 0                   */
  short npoints;     /* ��᫮ �祪 ��� �� �p�䨫�             */
  float h_scale;     /* �������⥫� ��p��. ����⠡� p��㭪�    */
  char areaname[40]; /* ��� ���⪠                            */
  char profname[20]; /* ��� ��䨫�                            */
  short count;       /* ���浪��� ����� ⥪�饩 �ਢ�� �� 1   */
} HEADER;
#pragma pack(pop)

/*  ��p���p� - ����⥫� ��䨫� ���  */
#pragma pack(push, 2)
typedef struct
{
  HEADER hdr; /* ��������� ����筮�� ���-䠩��          */
  VEZ vez;    /* ������ �ਢ�� ��� �� ��䨫�          */
} PROFIL;
#pragma pack(pop)

// *************** ��ଠ� ����筮�� VEZ-䠩��  **********************
// ���� �ଠ� VEZ ᮤ�ন� ����� � �ਢ�� ��� �� ������ ��䨫�.
// ���� ��⮨� �� ��������� � ����� ���� �� ��㣮� ����ᥩ � �ਢ��
// 䨪�஢������ ࠧ���
//                        ���������
//    char  signat[6];   /* �������� 䠩�� - ᨬ���� VEZBINFILE
//    short   npoints;     /* ��᫮ �祪 ��� �� �p�䨫�
//    float h_scale;     /* �������⥫� ��p��. ����⠡� p��㭪�
//    char  areaname[40];/* ��� ���⪠
//    char  profname[20];/* ��� ��䨫�
//    short   count;       /* ���浪��� ����� ⥪�饩 �ਢ�� �� 1
//                      ������ � ������
//  char  ID_curve[20]; /* ������������ �ਢ��
//  float X,Y,Z;        /* ���न���� �ਢ��
//  MODEL model;        /* ��ࠪ���⨪� ࠧ१�
//  CURVE curve;        /* �ਢ�� ���
//  float first_absc;   /* ��ࢠ� ������ �����뢠���� �ਢ�� � �
//  float RokMin;       /* �������쭮� ���祭�� �����. ᮯ�⨢�����
//  float RokMax;       /* ���ᨬ��쭮� ���祭�� �����. ᮯ�⨢�����
//  float AB2Min;       /* �������쭮� ���祭�� ࠧ��� ��/2
//  float AB2Max;       /* ���ᨬ��쭮� ���祭�� ࠧ��� ��/2
//  short   RokDecads;    /* ��᫮ ����� �� �� �����. ᮯ��. ( ��� Y )
//  short   AB2Decads;    /* ��᫮ ����� �� �� ࠧ��ᮢ ��/2  ( ��� X )
//  float OrgRok;       /* ��砫쭮� ���祭�� ���.ᮯ. ������. ������
//  float OrgAB2;       /* ��砫쭮� ���祭�� ��/2 ������. ������
//  float RMS;          /* �।��� �⭮�⥫쭮� ��宦����� �����
//                      /* �������� � ����⠭��� �ਢ묨 ���
//  short   q18;          /* ������⢮ �祪 �ਢ�� � 蠣�� 1/8 ������
//  short   q16;          /* ������⢮ �祪 �ਢ�� � 蠣�� 1/6 ������
#endif
