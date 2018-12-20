#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

int get_diapason( float min_val, float max_val, float *x0, int *Decades );

void main( void )
{
float mi, ma, x0;
int ndec, res;
do  {
  printf("\nmin значение ->");
  scanf("%f", &mi );
  printf("\nmax значение ->");
  scanf("%f", &ma );
  res = get_diapason( mi, ma, &x0, &ndec );
  printf("\n  res = %d   x0 = %f    Декад = %d", res, x0, ndec);
  } while ( 1==1 );

}

/* -------------------------------------------------------------------
   get_diapason Функция по заданному минимальному и максимальному
   значениям некоторой величины определяет количество логарифмических
   декад для отображения на логарифмическом бланке. Величина x0 - это
   точка отсчета логарифмической шкалы, кратная степени 10 ( 0.1, 1,
   10 и т.п.)
   При нормальном завершении функция возвращает 0, при ошибке 1.
   Ошибка - если значение min_val < 0.001 или max_val > 10**10
---------------------------------------------------------------------- */
int get_diapason( float min_val, float max_val, float *x0, int *Decades )
{
int p;
float v, a, b;

  if ( min_val < 0.001 ) return 1;
  if ( max_val > 1E10 )  return 1;

 /* *Decades = (int) ceil( log10( max_val / min_val ));*/

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
