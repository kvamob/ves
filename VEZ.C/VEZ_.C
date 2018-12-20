/* ----------------------------------------------------------------------
    vez_.c Программа АВТОМАТИЧЕСКОЙ интерпретации кривых ВЭЗ
	   По О.Куфуду
    
    Контрольный пример:
      GIVE ACCEPTABLE RELATIVE ERROR  -> 0.01
      GIVE FIRST ABCISSA              -> 10
      GIVE NUMBER OF SAMPLES          -> 11
      GIVE 11 SAMPLE VALUES
      160
      140
      128
      125
      150
      188
      240
      380
      420
      575
      700
      GIVE NUMBER OF LAYERS -> 3
      GIVE 2 LAYER THICKNESSES
      3
      15
      GIVE 3 LAYER RESISTIVITIES
      160
      100
      1000
      
      Результаты:
      RESISTIVITY THICKNESS
      210.21       4.79
      102.66       30.31
      1110.45
      R.M.S RELATIVE ERROR = 0.0428
      NUMBER OF TRIALS WAS  50     ( пpи кол-ве итеpаций MAX_ITERATION = 50 )
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#define MAX_ITERATION 100  /* Макс. количество итеpаций */
#define MAX_SAMPLES   40   /* Макс. количество отсчетов на кривой */
#define MAX_LAYERS    10   /* Макс. количество слоев в модели разреза */

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
int IC, IS, M, K, IK, NLayers, IT, IZ, NSamples, J, I, IW, IY, L, LB, JN, JM;

float RF[MAX_SAMPLES],  /* Массив отсчетов кривой в Омм с шагом 1/6 декады */
      P[2*MAX_LAYERS],  /* Массив : сначала идут мощности слоев в модели,  */
			/* от верхнего к нижнему, оставшиеся значения -    */ 
			/* сопротивления слоев ( их больше на 1 )          */
      PL[2*MAX_LAYERS], G[2*MAX_LAYERS], T[10], D[5][2*MAX_LAYERS];

      F = exp( log(10)/6 );    /* F = 1.467799 */

      printf("GIVE ACCEPTABLE RELATIVE ERROR  -> ");
      scanf("%f", &E );
      printf("GIVE FIRST ABCISSA              -> ");
      scanf("%f", &XA );
      printf("GIVE NUMBER OF SAMPLES          -> ");
      scanf("%d", &NSamples );

  do {
      printf("GIVE %3d  SAMPLE VALUES\n", NSamples );
      for ( J = 1; J <= NSamples; J ++ )
	 scanf("%f", &RF[J] );

      printf("CORRECT ? YES=0 -> ");
      scanf("%d", &M );
  } while ( M );
in:      
      printf("GIVE NUMBER OF LAYERS -> ");
      scanf("%d", &NLayers );
      IK = NLayers - 1;
      IT = IK + NLayers;
      printf("GIVE %3d LAYER THICKNESSES\n", IK );

  do  {
      
      for ( I = 1; I <= IK; I ++ )
	scanf("%f", &P[I] );

      printf("GIVE %3d LAYER RESISTIVITIES\n", NLayers );

      for ( I = NLayers; I <= IT; I ++ )
	scanf("%f", &P[I] );

      printf("CORRECT ? YES=0 -> ");
      scanf("%d", &M );
  } while ( M );

      QV = 99;
      ST = 0;      IC = 0;      IS = 0;

      printf("STEPLENGTH   R.M.S. ERRORS\n");

/* =======  COMPUTATION OF RESISTIVITY TRANSFORM ========= */
l_12: IC ++ ;
l_13: XR = XA;
      J = 1; Q = 0; BM = 0;
      for ( I = 1; I <= IT; I ++ )  G[I] = 0;
l_15: X = 0.0105 * XR;
      LB = 1;

      for ( L = 1; L <= 9; L ++ )
      {
	X = X * F * F;
l_16:   B = P[IT];

	if ( B > 100000 ) B -= 100000;
	BC = B;

	for ( K = 1; K <= IK; K ++ )
	 {
	   DW = P[NLayers - K];
	   RW = P[IT - K];
	   if( 100000 <= DW ) DW = DW - 100000;
	   if( 100000 <= RW ) RW = RW - 100000;

	   TH = tanh( DW/X );
	   B = (B + (TH * RW))/( 1 + (TH * B / RW));
	  }
	T[L] = B;
      } /* for */
/* =======  COMPUTATION OF PARTIAL DERIVATES OF THE TRANSFORM ========= */

      X = 0.1 * X;
      L = 4;

      if ( LB > 1 ) goto l_25;

      X = 0.1 * X;

      for( L = LB; L <= 4; L ++ )
      {
l_25:    D[L][IT] = 1;
	 B = BC;
	for ( K = 1; K <= IK; K ++ )
	 {
	   I =  NLayers - K;
	   IW = IT - K;
	   IY = IW + 1;
	   DW = P[I];
	   RW = P[IW];
	  if( 100000 <= DW) DW -= 100000;
	  if( 100000 <= RW) RW -= 100000;

	  TH = tanh(DW/X);

	  BA = 1 + B*TH/RW;
	  PA = (1 - TH*TH)/(BA*BA);
	  D[L][I]  = (RW - B*B/RW) / X;
	  D[L][IW] = TH*(1 + B*B/(RW*RW) + 2*TH*B/RW)/(BA*BA);
	  
	  for( IZ = I; IZ <= IK ; IZ ++ )
	     D[L][IZ] = PA * D[L][IZ];

	  for( IZ = IY; IZ <= IT ; IZ ++ )
	     D[L][IZ] = PA * D[L][IZ];

	   B = (B + TH*RW)/(1 + TH*B/RW);
	  } /* for K */
	 X = X*F*F;
      } /* for L */

/* =======  APPLICATION OF LINEAR FILTERS =========*/
      RM = 0.0148*T[1] - 0.0814*T[2] + 0.4018*T[3] - 1.5716*T[4] + 1.972*T[5];
      RM = RM + 0.1854*T[6] + 0.1064*T[7] - 0.0499*T[8] + 0.0225*T[9];
      
      for( L = 1; L <= 8; L ++ ) T[L] = T[L+1];
      BA = 1 - RM/RF[J];

      for ( I = 1; I <= IT; I ++ )
      {
	if ( P[I] >= 100000 )  continue;
	B = 0.402*D[1][I] - 1.571*D[2][I] + 1.972*D[3][I] + 0.186*D[4][I];

	for( L = 1; L <= 3; L ++ ) D[L][I] = D[(L+1)][I];

	G[I] = G[I] + 2*BA*B*P[I]/RM;
      }

      Q = Q + BA*BA;
      if( BM*BM < BA*BA )
       { BM = -BA;
	 JM = J;
       }
/* ============= BRANCHING PROGRAM ============== */
      J += 2;
      L = 9;
      LB = 4;
      XR = XR*F*F;
      X = 10.5*XR;
      if ( J <= NSamples ) goto l_16;
      if ( J & 1 )  /* проверка на четность, J нечетное */
	{
	  XR = XA*F;         /* next abscissa */
	  J = 2;
	  goto l_15;
	}

       Q = sqrt( Q / (float) NSamples );

      if ( QV <= Q)
       {
	 IS = 1;
	 for ( I = 1; I <= IT; I ++ )
	    P[I] = 0.67*PL[I] + 0.33*P[I];
	 ST = ST / 3;

	 if ( 0.003 <= ST) goto l_13;
			     else goto l_66;
       }

      if ( E >= Q )   goto l_70;
      if ( IC >= MAX_ITERATION ) goto l_70;

      printf("%10.4f %10.4f\n", ST, Q );

      B = 0;
/* =====  COMPUTATION OF GRADIENT,STEPLENGTH AND ADJUSTEMENT
	OF THE LAYER PARAMETERS                            ======== */

      for ( I = 1; I <= IT; I ++ )
      {
	G[I] = G[I] / NSamples;
	B = B + G[I]*G[I];
      }

      GR = sqrt( B );

      if ( IS <= 0 )
      {
	 ST = (Q*Q - 0.9*E*E) / GR;
	 if ( ST > 0.5 ) ST = 0.5;
      }
      
      for ( I = 1; I <= IT; I ++ )
      {
	 PL[I] = P[I];
	 P[I] = P[I]*(1 + ST*G[I] / GR);
      }

      for ( I = 1; I <= IK; I ++ )
      {
	if ( 100000 <= P[I] )
	  {
	     P[I] = 0;
	     DW = 0;
	     for ( K = 1; K <= I; K ++ )
	       DW = DW + PL[K] - P[K];
	     P[I] = DW;
	  }
      }

      QV = Q;
      BN = BM;
      JN = JM;
      goto  l_12;

/* =========== OUTPRINT OF RESULTS =============== */

l_66:
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

      printf(" MODEL DATA\n");
      printf(" RESISTIVITY THICKNESS\n");

      for ( I = 1; I <= IK; I ++ )
      {
	DW = P[I];
	RW = P[I + IK];
	if ( 100000 <= DW ) DW -= 100000;
	if ( 100000 <= RW ) RW -= 100000;
      
      printf("%10.2f %10.2f\n", RW, DW );
      }

      RW = P[IT];

      if ( 100000 <= RW) RW -= 100000;
      printf("%10.2f\n", RW );
      printf("\n R.M.S RELATIVE ERROR = %8.4f\n", Q );
      printf(" MAXIMUM RELATIVE ERROR = %8.4f AT SAMPLE %3d\n", BM, JM );
      printf(" NUMBER OF TRIALS WAS %4d\n", IC );
      getch();
      goto in;
}
