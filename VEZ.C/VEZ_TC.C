/* ----------------------------------------------------------------------
    vez_.c Программа АВТОМАТИЧЕСКОЙ интерпретации кривых ВЭЗ
	   По О.Куфуду
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

//DIMENSION RF(19),P(19),PL(19),G(19),T(9),D(4,19)
//C============= INRODUCTION OF INFORMATION ================

/* ------------------------ Прототипы ---------------------- */
void process( void );

/* -------------- Глобальные переменные -------------------- */

void main( void )
{
process();
}

void process( void )
{
float F, E ;
float Q, QV;
float ST, XR, XA, X, B, BA, BM, BN, BC, DW, RW, TH, RM, GR, PA;
int IC, IS, M, K, IK, IL, IT, IZ, JZ, J, I, IW, IY, L, LB, JN, JM;

float RF[20], P[20], PL[20], G[20], T[10], D[5][20];

//      F = exp(ALOG(10.)/6.);
      F = exp( log(10)/6 );    /* F = 1.467799 */
      QV = 99;
      ST = 0;      IC = 0;      IS = 0;
//***************************************************
      goto l_9999;
//***************************************************

      printf("GIVE ACCEPTABLE RELATIVE ERROR  -> ");
      scanf("%f", &E );
      printf("GIVE FIRST ABCISSA              -> ");
      scanf("%f", &XA );
      printf("GIVE NUMBER OF SAMPLES          -> ");
      scanf("%d", &JZ );

  do {
      printf("GIVE %3d  SAMPLE VALUES\n", JZ );
      for ( J = 1; J <= JZ; J ++ )
	 scanf("%f", &RF[J] );

//      PRINT 89
      printf("CORRECT ? YES=0 -> ");
      scanf("%d", &M );
  } while ( M );
      printf("GIVE NUMBER OF LAYERS -> ");
      scanf("%d", &IL );
      IK = IL - 1;
      IT = IK + IL;
      printf("GIVE %3d LAYER THICKNESSES\n", IK );

   do  {
//8     PRINT 91,IK
//      DO 9 I=1,IK
//9     READ(*,*) P(I)
      for ( I = 1; I <= IK; I ++ )
	scanf("%f", &P[I] );

      printf("GIVE %3d LAYER RESISTIVITIES\n", IL );

//      DO 10 I=IL,IT
//10    READ(*,*) P(I)
      for ( I = IL; I <= IT; I ++ )
	scanf("%f", &P[I] );

      printf("CORRECT ? YES=0 -> ");
      scanf("%d", &M );
  } while ( M );
/*********************************************************
l_9999:
      E = 0.01;
      XA = 10;
      JZ = 11;
      RF[1]=160;
      RF[2]=140;
      RF[3]=128;
      RF[4]=125;
      RF[5]=150;
      RF[6]=188;
      RF[7]=240;
      RF[8]=380;
      RF[9]=420;
      RF[10]=575;
      RF[11]=700;
      IL = 3;
      IK = IL - 1;
      IT = IK + IL;
      P[1] = 3;
      P[2] = 15;
      P[3] = 160;
      P[4] = 100;
      P[5] = 1000;
/*********************************************************

      printf("STEPLENGTH   R.M.S. ERRORS\n");

/* =======  COMPUTATION OF RESISTIVITY TRANSFORM ========= */
l_12: IC ++ ;
l_13: XR = XA;
      J = 1; Q = 0; BM = 0;
      for ( I = 1; I <= IT; I ++ )  G[I] = 0;
l_15: X = 0.0105 * XR;
      LB = 1;

//      DO 23 L=1,9
      for ( L = 1; L <= 9; L ++ )
      {
	X = X * F * F;
l_16:   B = P[IT];

	if ( B > 100000 ) B -= 100000;
l_77:   BC = B;

//      DO 22 K=1,IK
	for ( K = 1; K <= IK; K ++ )
	 {
	   DW = P[IL - K];
	   RW = P[IT - K];
	   if( 100000 <= DW ) DW = DW - 100000;
l_18:      if( 100000 <= RW ) RW = RW - 100000;

l_20:      TH = tanh( DW/X );
l_22:      B = (B + (TH * RW))/( 1 + (TH * B / RW));
	  }
l_23:   T[L] = B;
      } /* for */
/* =======  COMPUTATION OF PARTIAL DERIVATES OF THE TRANSFORM ========= */

      X = 0.1 * X;
      L = 4;

//      IF(LB-1) 24,24,25          ! ???????????????
      if ( LB > 1 ) goto l_25;

l_24: X = 0.1 * X;

//      DO 34 L=LB,4
      for( L = LB; L <= 4; L ++ )
      {
l_25:    D[L][IT] = 1;
	 B = BC;
//      DO 33 K=1,IK
	for ( K = 1; K <= IK; K ++ )
	 {
	   I =  IL - K;
	   IW = IT - K;
	   IY = IW + 1;
	   DW = P[I];
	   RW = P[IW];
	  if( 100000 <= DW) DW = DW - 100000;
	  if( 100000 <= RW) RW = RW - 100000;

l_29:     TH = tanh(DW/X);

	  BA = 1 + B*TH/RW;
	  PA = (1 - TH*TH)/(BA*BA);
	  D[L][I]  = (RW - B*B/RW) / X;
	  D[L][IW] = TH*(1 + B*B/(RW*RW) + 2*TH*B/RW)/(BA*BA);
//          DO 30 IZ=I,IK
//30    D(L,IZ)=PA*D(L,IZ)
	  for( IZ = I; IZ <= IK ; IZ ++ )
	     D[L][IZ] = PA * D[L][IZ];

//      DO 31 IZ=IY,IT
//31    D(L,IZ)=PA*D(L,IZ)
	  for( IZ = IY; IZ <= IT ; IZ ++ )
	     D[L][IZ] = PA * D[L][IZ];

l_33:      B = (B + TH*RW)/(1 + TH*B/RW);
	  } /* for K */
l_34:    X = X*F*F;
      } /* for L */

/* =======  APPLICATION OF LINEAR FILTERS =========*/
      RM = 0.0148*T[1] - 0.0814*T[2] + 0.4018*T[3] - 1.5716*T[4] + 1.972*T[5];
      RM = RM + 0.1854*T[6] + 0.1064*T[7] - 0.0499*T[8] + 0.0225*T[9];
//      DO 35 L=1,8
//35    T(L)=T(L+1)
      for( L = 1; L <= 8; L ++ ) T[L] = T[L+1];
      BA = 1 - RM/RF[J];

//      DO 40 I=1,IT
      for ( I = 1; I <= IT; I ++ )
      {
//        IF(P(I)-100000.) 36,40,40
	if ( P[I] >= 100000 )  continue;
	B = 0.402*D[1][I] - 1.571*D[2][I] + 1.972*D[3][I] + 0.186*D[4][I];

//        DO 37 L=1,3
//37        D(L,I) = D((L+1),I)
	for( L = 1; L <= 3; L ++ ) D[L][I] = D[(L+1)][I];

	G[I] = G[I] + 2*BA*B*P[I]/RM;
//40    CONTINUE
      }

      Q = Q + BA*BA;
      if( (BM*BM - BA*BA) < 0 )
       { BM = -BA;
	 JM = J;
       }
/* ============= BRANCHING PROGRAM ============== */
//l_44:
      J += 2;
      L = 9;
      LB = 4;
      XR = XR*F*F;
      X = 10.5*XR;
      if ( J <= JZ ) goto l_16;
//48    IF((J/2)*2-J) 50,51,50  проверка на четность
      if ( J & 1 )  /* J нечетное */
	{
//50
	  XR = XA*F;         /* next abscissa */
	  J = 2;
//      GOTO 15 !???????????????????????
	  goto l_15;
	}

//51    Q=SQRT(Q/FLOAT(JZ))
       Q = sqrt( Q / (float) JZ );

      if ( QV <= Q)
       {
l_52:    IS = 1;
//         DO 53  I=1,IT
//53    P(I)=.67*PL(I)+.33*P(I)
	 for ( I = 1; I <= IT; I ++ )
	    P[I] = 0.67*PL[I] + 0.33*P[I];
	 ST = ST / 3;
      if ( 0.003 <= ST) goto l_13;
	  else goto l_66;
       }

//54    IF(E-Q) 55,70,70
      if ( E >= Q )   goto l_70;
//55    IF(IC-50) 56,70,70
      if ( IC >= 50 ) goto l_70;

//56    PRINT 101,ST,Q
//101   FORMAT(2F10.4)

      printf("%10.4f %10.4f\n", ST, Q );

       B = 0;
/* =====  COMPUTATION OF GRADIENT,STEPLENGTH AND ADJUSTEMENT
	OF THE LAYER PARAMETERS                            ======== */

//      DO 57 I=1,IT
//      G(I)=G(I)/FLOAT(JZ)
//57    B=B+G(I)*G(I)
      for ( I = 1; I <= IT; I ++ )
      {
	G[I] = G[I] / JZ;
	B = B + G[I]*G[I];
      }

      GR = sqrt( B );

      if ( IS <= 0 )
      {
	 ST = (Q*Q - 0.9*E*E) / GR;
	 if ( ST > 0.5 ) ST = 0.5;
      }
//60    DO 61 I=1,IT
//      PL(I)=P(I)
//61    P(I)=P(I)*(1.+ST*G(I)/GR)
      for ( I = 1; I <= IT; I ++ )
      {
	 PL[I] = P[I];
	 P[I] = P[I]*(1 + ST*G[I] / GR);
      }

//      DO 65 I=1,IK
      for ( I = 1; I <= IK; I ++ )
      {
	if ( 100000 <= P[I] )
	  {
	     P[I] = 0;
	     DW = 0;
//      DO 63 K=1,I
//63    DW=DW+PL(K)-P(K)
	     for ( K = 1; K <= I; K ++ )
	       DW = DW + PL[K] - P[K];
	     P[I] = DW;
	  }
//65    CONTINUE
      }

      QV = Q;
      BN = BM;
      JN = JM;
      goto  l_12;

/* =========== OUTPRINT OF RESULTS =============== */

l_66:
//      DO 67 I=1,IT
//67    P(I)=PL(I)
      for ( I = 1; I <= IT; I ++ )
	 P[I] = PL[I];

      Q = QV;
      BM = BN;
      JM = JN;
l_70:
      printf("\nPress any key ...");
      getch();

      printf("\n Q  = %f\n", Q);
      printf(" ST = %f\n", ST);

//      PRINT 93
//      PRINT 94
      printf(" MODEL DATA\n");
      printf(" RESISTIVITY THICKNESS\n");

//      DO 74 I=1,IK
      for ( I = 1; I <= IK; I ++ )
      {
	DW = P[I];
	RW = P[I + IK];
	if ( 100000 <= DW ) DW = DW - 100000;
	if ( 100000 <= RW ) RW = RW - 100000;
//74    PRINT 95,RW,DW
      printf("%10.2f %10.2f\n", RW, DW );
      }

      RW = P[IT];

      if ( 100000 <= RW) RW=RW-100000;
//      PRINT 96,RW
      printf("%10.2f\n", RW );
      printf("\n R.M.S RELATIVE ERROR = %8.4f\n", Q );
      printf(" MAXIMUM RELATIVE ERROR = %8.4f AT SAMPLE %3d\n", BM, JM );
      printf(" NUMBER OF TRIALS WAS %4d\n", IC );
}