/*
 * ���� ves.h
*/
#ifndef   VES_WIN_H
#define   VES_WIN_H
	      // ������ �������������
const int AUTO   =   1;     /* �������. ������������� */
const int MANUAL =   2;     /* ������ �������������   */

const int MAX_ITERATION=100;/* ����. ���������� ���p���� */
const int MAX_SAMPLES = 50; /* ����. ���������� �������� �� ������ */
const int MAX_LAYERS  = 6;  /* ����. ���������� ����� � ������ ������� */
const int MIN_LAYERS  = 1;  /* ���.  ���������� ����� � ������ ������� */
const int MAX_LAYERS_TC=8;  /* ����. ���������� ����� � ������ �������
                              ��� ������� ������������� ������ ��� */

const float   SCALE_MODUL =6.125;   /* ������ ��������������� �����  */
#define   B_SIGNATURE    "VEZBINFILE_" /* ������� ���������  VEZ-����� */
#define   T_SIGNATURE    "VEZFILE"     /* ������� ���������� VEZ-����� */

const float   MIN_RESIST =0.1;     // ����������� �������� ��. ����. ����, ���
const float   MAX_RESIST =100000;  // ������������ �������� ��. ����. ����
const float   DEF_RESIST =100;     // ������������ �������� ��. ����. ����
const float   MIN_THICK  =0.1;     // ����������� �������� �������� ����
const float   MAX_THICK  =1000;    // ������������ �������� �������� ����
const float   DEF_THICK  =1;       // ������������ �������� �������� ����

/*  ���� ������ */
// �������� ������
const int  F_NOT_OPEN = -2; // ������ �������� VEZ-�����
const int  F_TEXT_VEZ = -3; // ������� ���������� VEZ-�����
const int  F_NOT_VEZ  = -4; // ��� �� VEZ-����
const int  F_READ_ERR = -5; // ������ ������
const int  F_WRIT_ERR = -6; // ������ ������

#pragma pack(push,2)
typedef struct _MODEL {   // ��������� - ��������� ������ �������
  short n;                  // ����� �����
  float ro[MAX_LAYERS];     // ������ ������������� �����
  float h[MAX_LAYERS-1];    // ������ ��������� �����
  } MODEL;
#pragma pack(pop)

#pragma pack(push,2)
typedef struct _MODEL_TC { // ��������� - ��������� ������ �������
                             // ��� ������� ������������� ������
  short n;                   // ����� �����
  float ro[MAX_LAYERS_TC];   // ������ ������������� �����
  float h[MAX_LAYERS_TC-1];  // ������ ��������� �����
  } MODEL_TC;
#pragma pack(pop)

#pragma pack(push,2)
typedef struct _CURVE {   // ��������� - ��������� ������ ���
  short n;                  // ����� �������� �� ������
  float fRok[MAX_SAMPLES];  // ����. �������� �����.������������� ��*�
  float tRok[MAX_SAMPLES];  // �����.�������� �����.������������� ��*�
  float AB2[MAX_SAMPLES];   // �������� �������� ��/2 � ������
  } CURVE;
#pragma pack(pop)

#pragma pack(push,2)
typedef struct _LOGCURVE {  // ��������� - ��������� ���������� ������ ���
  short n;                  // ����� �������� �� ������
  short yf[MAX_SAMPLES];    // �������� ������. �p����� � ���. ��������
  short yt[MAX_SAMPLES];    // �������� ���p. �p�����   � ���. ��������
  short x[MAX_SAMPLES];     // �������� ������� � ���. ��������
  } LOGCURVE;
#pragma pack(pop)

#pragma pack(push,2)
typedef struct _VEZ {
  char  ID_curve[20];     // ������������ ������
  float X,Y,Z;            // ���������� ������
  MODEL model;            // �������������� �������
  CURVE curve;            // ������ ���
  float first_absc;       // ������ �������� �������������� ������ � �
  float RokMin;           // ����������� �������� �����. �������������
  float RokMax;           // ������������ �������� �����. �������������
  float AB2Min;           // ����������� �������� ������� ��/2
  float AB2Max;           // ������������ �������� ������� ��/2
  short   RokDecads;      // ����� ����� �� ��� �����. ������. ( ��� Y )
  short   AB2Decads;      // ����� ����� �� ��� �������� ��/2  ( ��� X )
  float OrgRok;           // ��������� �������� ���.���. ��������. ������
  float OrgAB2;           // ��������� �������� ��/2 ��������. ������
  float RMS;              // ������� ������������� ����������� �����
            		  // ����������� � ������������ ������� ���
  short q18;              // ���������� ����� ������ � ����� 1/8 ������
  short q16;              // ���������� ����� ������ � ����� 1/6 ������
  } VEZ;
#pragma pack(pop)

//typedef struct tagcmCOORD {  // ��������������� ���������
//  float x;
//  float y;
//  } cmCOORD;

#pragma pack(push,2)
typedef struct _pxCOORD {  // ��������������� ���������
  short x;
  short y;
  } pxCOORD;
#pragma pack(pop)


#pragma pack(push,2)
typedef struct _VES_PAINTDATA {     // ��������� ������������ �p� p�������� �p���� ���
  short    DrawType;  // 0, ���� �� p������� ���p. �p����,� 1, ���� p�������
  LOGCURVE LCurve;    // ���p������ ����� �p���� ��� � ���������� ����.
  short    pxXMod;    // ������ ��������. ������ � ����. �� ��� X
  short    pxYMod;    // ������ ��������. ������ � ����. �� ��� Y
  RECT   Frame;       // ���p������ ����p. ������, � ����p�� ���������
		      // �p���� ��� ����p� ���� � ���. ��������
  RECT   Legend;      // ���p������ �������, ��� �������� �������
  short    pxXSize;   // ����� ������ �� ��� X � ��������
  short    pxYSize;   // ����� ������ �� ��� Y � ��������
//  pxCOORD  pxFldName;  // ���. ���������� ������������ ������� � ��������
//  pxCOORD  pxCrvName;  // ���. ���������� ������������ ������ � ��������
  short    pxChHeight; // ������ �������� � ��������
  short    pxChWidth;  // ������ �������� � ��������
  RECT     TxtFrame;   // ����� ��� ������
  pxCOORD  pxFootStr;  // ������ � ����p���� ANSI, �����. � ����� - �����
		       // ������, ��� ������, ��� ������� � �.�.             */
  char   footstr[140];
//  char   hdrstr[80];   // ������ - ��������� � ����p���� ANSI
//  char   subhdrstr[80];// ������ - ������������ � ����p���� ANSI
  } VES_PAINTDATA;
#pragma pack(pop)

       //  ��p����p� - ��������� ��������� ������� ��� (�����)
#pragma pack(push,2)
typedef struct _HEADER {
    char  signat[12];  // ��������� ����� - ������� VEZBINFILE_
		       // ��������� ������ - 0
    short  npoints;    // ����� ����� ��� �� �p�����
    float h_scale;     // ����������� ��p��. �������� p������
    char  areaname[40];// ��� �������
    char  profname[20];// ��� �������
    short   count;     // ���������� ����� ������� ������ �� 0
    } HEADER;
#pragma pack(pop)

       //  ��p����p� - ��������� ������� ���
#pragma pack(push,2)
typedef struct _PROFIL {
    HEADER hdr;        // ��������� ��������� ���-�����
    VEZ   vez;         // ������� ������ ��� �� �������
    } PROFIL;
#pragma pack(pop)

// *************** ������ ��������� VEZ-�����  **********************
// ���� ������� VEZ �������� ������ � ������ ��� �� ������ �������.
// ���� ������� �� ��������� � ������ ���� �� ������ ������� � ������
// �������������� �������
//                        ���������
//    char  signat[6];   /* ��������� ����� - ������� VEZBINFILE
//    int   npoints;     /* ����� ����� ��� �� �p�����
//    float h_scale;     /* ����������� ��p��. �������� p������
//    char  areaname[40];/* ��� �������
//    char  profname[20];/* ��� �������
//    int   count;       /* ���������� ����� ������� ������ �� 1
//                      ������ � ������
//  char  ID_curve[20]; /* ������������ ������
//  float X,Y,Z;        /* ���������� ������
//  MODEL model;        /* �������������� �������
//  CURVE curve;        /* ������ ���
//  float first_absc;   /* ������ �������� �������������� ������ � �
//  float RokMin;       /* ����������� �������� �����. �������������
//  float RokMax;       /* ������������ �������� �����. �������������
//  float AB2Min;       /* ����������� �������� ������� ��/2
//  float AB2Max;       /* ������������ �������� ������� ��/2
//  int   RokDecads;    /* ����� ����� �� ��� �����. ������. ( ��� Y )
//  int   AB2Decads;    /* ����� ����� �� ��� �������� ��/2  ( ��� X )
//  float OrgRok;       /* ��������� �������� ���.���. ��������. ������
//  float OrgAB2;       /* ��������� �������� ��/2 ��������. ������
//  float RMS;          /* ������� ������������� ����������� �����
//                      /* ����������� � ������������ ������� ���
//  int   q18;          /* ���������� ����� ������ � ����� 1/8 ������
//  int   q16;          /* ���������� ����� ������ � ����� 1/6 ������
#endif
