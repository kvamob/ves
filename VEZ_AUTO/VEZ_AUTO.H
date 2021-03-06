/*
 * ���� vez_auto.h - ��⠢��� ���� �஥�� vez_auto
 */
#ifndef   VEZ_AUTO_H
#define   VEZ_AUTO_H

typedef  unsigned char  BYTE;
typedef  unsigned int   WORD;
typedef  unsigned int   BOOL;

#define  TRUE     1
#define  FALSE    0

#define MAX_ITERATION 100  /* ����. ������⢮ ��p�権 */
#define MAX_SAMPLES   50   /* ����. ������⢮ ����⮢ �� �ਢ�� */
#define MAX_LAYERS    10   /* ����. ������⢮ ᫮�� � ������ ࠧ१� */

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


/* ----------------------- ��������� ������� ---------------------------- */
#endif                                                  













