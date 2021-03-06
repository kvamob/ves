// ���� ves_gr.c ����� �p���� VES for Windows
// ����� ᮤ�p����� �㭪樨 p�ᮢ����

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <math.h>

#include "ves.h"

// ----------------- ���������  -------------------------------
void PlotInitialize( HWND hWnd, HDC hDC, VES_PAINTDATA *plot, PROFIL *prof );
void DrawLogBlank( HDC hDC, VES_PAINTDATA *plot, VEZ *vez );
void DrawCurve( HDC hDC, VES_PAINTDATA *plot );
void DrawMarker_( HDC hDC, int x, int y );
void DrawSelectLine( HDC hDC, VES_PAINTDATA *Plot, int x );
void EditCurveByMouse( HWND hWnd, PROFIL *prof, VES_PAINTDATA *plot, 
		       POINT pt );
int GetNearestPoint( LOGCURVE *lc, int x );

extern float SolveRMS( VEZ *vez );

extern HPEN hBlackPen, hWhitePen, hDarkPen, hLightPen,
	    hRedPen, hBluePen; // ��p��
extern HANDLE hFont;  // �p���
extern int EditCurve; // �p����� p�����p������ �p����
extern int yBord;     // ���騭� ࠬ�� ���� �� ���⨪���

/* ------------------------------------------------------------
   PlotInitialize ��������� ���� �������� plot, �ᯮ����
   ���ଠ�� �� �������� prof (���ᠭ�� �p�䨫�)
   hWnd - ���p���p ����, � ���p�� �㤥� �p����������� p�ᮢ����
   hDC - ���⥪��, � ���p�� �㤥� �p����������� p�ᮢ����
---------------------------------------------------------------*/
void PlotInitialize( HWND hWnd, HDC hDC, VES_PAINTDATA *plot, PROFIL *prof )
{
int    x, y, xLMargin, xRMargin, yTopMargin, yBotMargin;
TEXTMETRIC tm;
RECT   Rect;

 GetClientRect( hWnd, &Rect ); // ����稬 ࠧ���� ����
// SelectObject( hDC, hFont );   // ���p㧨� 䮭�

 GetTextMetrics( hDC, &tm );   // �����p� �p���

 plot->pxChWidth  = tm.tmAveCharWidth; // ��p��� ᨬ�����
 plot->pxChHeight = tm.tmHeight;       // ���� ᨬ�����

 xLMargin = tm.tmAveCharWidth*7; // ����� ���� �� �� x
 xRMargin = tm.tmAveCharWidth*12; // �ࠢ�� ���� �� �� x

 yTopMargin = tm.tmHeight + 3*yBord;
 yBotMargin = tm.tmHeight*3;

 plot->Frame.left = Rect.left + xLMargin;
 plot->Frame.bottom = Rect.bottom - yBotMargin;
	  
	  /* ��।���� ����� */
 x =  (Rect.right - Rect.left - xLMargin - xRMargin)/prof->vez.AB2Decads;
 y =  (Rect.bottom - Rect.top - yTopMargin - yBotMargin)/ prof->vez.RokDecads;
 plot->pxXMod = min(x,y);
 
 plot->pxYMod = plot->pxXMod;
 plot->pxXSize = ( plot->pxXMod * prof->vez.AB2Decads ); /* ࠧ���� */
 plot->pxYSize = ( plot->pxYMod * prof->vez.RokDecads ); /* ࠧ���� */
 plot->Frame.right = plot->Frame.left + plot->pxXSize;
 plot->Frame.top = plot->Frame.bottom - plot->pxYSize;

 
 plot->pxFootStr.x = plot->pxChWidth;
 plot->pxFootStr.y = Rect.bottom - yBord*4;
 x = sprintf( plot->footstr,"%3d:%3d  Crv:%-19.19s Pr:%-19.19s Ar:%-39.39s",
	    prof->hdr.count, prof->hdr.npoints, prof->vez.ID_curve,
	    prof->hdr.profname, prof->hdr.areaname );
 plot->TxtFrame.left  = yBord * 2;
 plot->TxtFrame.right = Rect.right - plot->TxtFrame.left;
 plot->TxtFrame.top = plot->pxFootStr.y - plot->pxChHeight - yBord*3;
 plot->TxtFrame.bottom = plot->pxFootStr.y + 2 * yBord;

    // ������� ��� �������
 plot->Legend.left = plot->Frame.right + plot->pxChWidth;
 plot->Legend.right = plot->Legend.left + 10*plot->pxChWidth;
 plot->Legend.top = plot->Frame.top;
 plot->Legend.bottom = plot->Legend.top + 4*plot->pxChHeight;

}

/* ------------------------------------------------------------
   DrawLogBlank H�p�ᮢ��� �����䬨�᪨� �����,  �ᯮ����
   �������� plot � prof.
   hDC - ���⥪�� ���p���⢠, ��� �㤥� �p����������� p�ᮢ����
---------------------------------------------------------------*/
void DrawLogBlank( HDC hDC, VES_PAINTDATA *plot, VEZ *vez )
{
int  i;
int  x, y, x_, y_;
float AB2, Rok;
char str[30]; /* ⥪�⮢�� �।�⠢����� AB/2 � Rok */
int nLen;  

  SelectObject( hDC, hBlackPen);  // ��p��� ��p�
  SetROP2( hDC, R2_COPYPEN );

  x = plot->Frame.left, y = plot->Frame.bottom;   /* ���⨪. ����� */
  y_ = y + 2 * yBord;
  AB2 = vez->OrgAB2;
  SetTextAlign( hDC, TA_CENTER | TA_TOP );  // ��⠭���� ��ࠢ�������
  for( i = 0; i <= vez->AB2Decads; i ++, x += plot->pxXMod, AB2 *= 10 )
   { MoveTo( hDC, x, y );
     LineTo( hDC, x, plot->Frame.top );
     nLen = sprintf( str,"%g", AB2); /* �����襬 �᫠ AB/2 */
     TextOut( hDC, x, y_, str, nLen );
   }
	      /* ��ਧ. ����� */ 
  x = plot->Frame.left; 
  x_ = x - plot->pxChWidth;
  y = plot->Frame.bottom;   
  Rok = vez->OrgRok;
  
  SetTextAlign( hDC, TA_RIGHT | TA_BASELINE );  // ��⠭���� ��ࠢ�������
  for( i = 0; i <= vez->RokDecads; i ++, y -= plot->pxYMod, Rok *= 10 )
   { MoveTo( hDC, x, y );
     LineTo( hDC, plot->Frame.right, y );
     nLen = sprintf( str,"%8g", Rok); /* �����襬 �᫠ Rok */
     TextOut( hDC, x_, y, str, nLen );
   }
   
   // ������� ࠬ�� "��㪫��" - ����㥬 ���譨� ����� ���� 梥⮬
// SelectObject( hDC, hLightPen);
// MoveTo(hDC, plot->Frame.left-1, plot->Frame.bottom + 1);
// LineTo(hDC, plot->Frame.left-1, plot->Frame.top - 1);
// LineTo(hDC, plot->Frame.right + 2, plot->Frame.top - 1);
// SelectObject( hDC, hDarkPen);
// MoveTo(hDC, plot->Frame.right + 2, plot->Frame.top + 2);
// LineTo(hDC, plot->Frame.right + 2, plot->Frame.bottom + 2);
// LineTo(hDC, plot->Frame.left - 1, plot->Frame.bottom + 2);
  
 SelectObject( hDC, hLightPen);
 MoveTo(hDC, plot->Frame.left, plot->Frame.bottom);
 LineTo(hDC, plot->Frame.left, plot->Frame.top);
 LineTo(hDC, plot->Frame.right + 1, plot->Frame.top);
 SelectObject( hDC, hDarkPen);
 MoveTo(hDC, plot->Frame.right + 1, plot->Frame.top + 2);
 LineTo(hDC, plot->Frame.right + 1, plot->Frame.bottom + 1);
 LineTo(hDC, plot->Frame.left + 1, plot->Frame.bottom + 1);
  

  // �����襬 ��㭮�
 SetTextAlign( hDC, TA_LEFT | TA_BOTTOM );  // ��⠭���� ��ࠢ�������
 TextOut( hDC, plot->pxFootStr.x,plot->pxFootStr.y,plot->footstr,
		strlen(plot->footstr));
   // ������� ࠬ�� "��㪫��" - ����㥬 ���譨� ����� ���� 梥⮬
 SelectObject( hDC, hLightPen);
 MoveTo(hDC, plot->TxtFrame.left, plot->TxtFrame.bottom );
 LineTo(hDC, plot->TxtFrame.left, plot->TxtFrame.top);
 LineTo(hDC, plot->TxtFrame.right, plot->TxtFrame.top);
 SelectObject( hDC, hDarkPen);
 LineTo(hDC, plot->TxtFrame.right, plot->TxtFrame.bottom);
 LineTo(hDC, plot->TxtFrame.left, plot->TxtFrame.bottom);


 SetTextAlign( hDC, TA_LEFT | TA_BOTTOM );  // ��⠭���� ��ࠢ�������
	   /* �������� �ᥩ */
 TextOut( hDC, plot->Frame.left, plot->Frame.top - 2*yBord,
	     "Rok Omm", 7 );
 TextOut( hDC, plot->Frame.right + plot->pxChWidth, 
	  plot->Frame.bottom, "AB/2, m", 7 );
 
  /* C������� �������� �ਢ��  */
 
 if ( vez->curve.tRok[0] ) // �᫨ ���� ⥮p���᪠� �p���� 
    plot->DrawType = 1;    // p�ᮢ��� ��
  else
    plot->DrawType = 0;
 
 plot->LCurve.n = vez->curve.n; // �᫮ ����⮢
 for ( i = 0; i < vez->curve.n; i ++ )
  {   
    plot->LCurve.x[i] = plot->Frame.left + 
       ( log10( vez->curve.AB2[i] / vez->OrgAB2 ))*plot->pxXMod;
    plot->LCurve.yf[i] = plot->Frame.bottom -
       ( log10( vez->curve.fRok[i] / vez->OrgRok))*plot->pxYMod;
    if (plot->DrawType)  // �᫨ p�ᮢ��� ⥮p. �p����
       plot->LCurve.yt[i] = plot->Frame.bottom -
	  ( log10( vez->curve.tRok[i] / vez->OrgRok))*plot->pxYMod;
  }
	   // �����襬 RMS
nLen = sprintf(str, "RMS = %.1f \%", SolveRMS( vez ));
TextOut( hDC, plot->Frame.right - plot->pxChWidth*nLen, 
	 plot->Frame.top - 2*yBord, str, nLen );

  // ����㥬 �������
// SetTextAlign( hDC, TA_LEFT | TA_BASELINE );  // ��⠭���� ��ࠢ�������
// SetROP2( hDC, R2_COPYPEN );
// SelectObject( hDC, hLightPen);
// MoveTo(hDC, plot->Legend.left, plot->Legend.bottom);
// LineTo(hDC, plot->Legend.left, plot->Legend.top);
// LineTo(hDC, plot->Legend.right,plot->Legend.top);
// SelectObject( hDC, hDarkPen);
// LineTo(hDC, plot->Legend.right, plot->Legend.bottom);
// LineTo(hDC, plot->Legend.left, plot->Legend.bottom); // ����� ���ᮢ��

 SelectObject( hDC, hBluePen);
 SetROP2( hDC, R2_NOTXORPEN );   // ������ ⥪��
 MoveTo(hDC, plot->Legend.left + plot->pxChWidth, plot->Legend.top + plot->pxChHeight);
 LineTo(hDC, plot->Legend.left + 3*plot->pxChWidth,
		  plot->Legend.top + plot->pxChHeight);
 TextOut( hDC, plot->Legend.left + 4*plot->pxChWidth,
	  plot->Legend.top + plot->pxChHeight, "Field", 5 );
 SelectObject( hDC, hRedPen);
 MoveTo(hDC, plot->Legend.left + plot->pxChWidth, plot->Legend.top + 3*plot->pxChHeight);
 LineTo(hDC, plot->Legend.left + 3*plot->pxChWidth,
		  plot->Legend.top + 3*plot->pxChHeight);
 TextOut( hDC, plot->Legend.left + 4*plot->pxChWidth,
	  plot->Legend.top + 3*plot->pxChHeight, "Model", 5 );

}

/* ------------------------------------------------------------
   DrawCurve H�p�ᮢ��� �������� �ਢ�� ���, �ᯮ���� 
   �������� plot.
---------------------------------------------------------------*/
void DrawCurve( HDC hDC, VES_PAINTDATA *plot )
{
int x, y;
int i;

   SelectObject( hDC, hBluePen);  // C���� ��p�
   SetROP2( hDC, R2_NOTXORPEN );

	 /* ���㥬 �������� �ਢ��  */
   x = plot->LCurve.x[0];
   y = plot->LCurve.yf[0];
   DrawMarker_( hDC, x, y );

   for ( i = 1; i < plot->LCurve.n; i ++ )
    {
     MoveTo( hDC, x, y );
     x = plot->LCurve.x[i];
     y = plot->LCurve.yf[i];
     LineTo( hDC, x, y );
     DrawMarker_( hDC, x, y );
    }
	 /* ���㥬 ⥮������ �ਢ��  */
 if ( plot->DrawType ) // �᫨ ��� ����  
 {
   SelectObject( hDC, hRedPen);  // �p�᭮� ��p�
   x = plot->LCurve.x[0];
   y = plot->LCurve.yt[0];
   DrawMarker_( hDC, x, y );
   for ( i = 1; i < plot->LCurve.n; i ++ )
    {
     MoveTo( hDC, x, y );
     x = plot->LCurve.x[i];
     y = plot->LCurve.yt[i];
     LineTo( hDC, x, y );
     DrawMarker_( hDC, x, y );
    }
 }

}


/* ------------------------------------------------------------
   DrawMarker_ H�p�ᮢ��� ��� �� ��䨪� � ���� "���⨪�"
   x, y - ���न���� 業�� "���⨪�" � ᠭ⨬����
   hDC - ���⥪�� ���p���⢠, ��� �㤥� p�ᮢ���
---------------------------------------------------------------*/
void DrawMarker_( HDC hDC, int x, int y )
{
#define STROKE  3      /* ����� ����  */

 MoveTo( hDC,  x, y + STROKE );
 LineTo( hDC,  x, y - STROKE );
 MoveTo( hDC,  x - STROKE, y );
 LineTo( hDC,  x + STROKE, y );

}

/* ------------------------------------------------------------
   EditCurveByMouse ������஢���� �ਢ�� ��� � ������� ���.
   �᫨ ��⠭����� ����� ������ ������ ��� � ������ ����� ������
   ���, � �������� �� �� X �窠 �ਢ�� ��� �㤥� �뤥����
   ���⨪��쭮� ������ (�㤥� ����祭 ०�� ।���஢����)
   �᫨ ��⠭����� ����� ��� � ��㣮� ��������� ����� ������
   � ������ ᭮�� ����� ������, � �न��� �뤥������ �窨 
   �ਢ�� �㤥� �������� �� �न���� ⥪�饣� ��������� ����� 
   ���. �⮡� �⬥���� ०�� ।���஢����, �㦭� 饫�����
   ����� ����� ����, �� ��� �����䬨�᪮�� ������.
   hWnd - ���ਯ�� ���� � �ਢ��
   prof - �����⥫� �� ��䨫� 
   plot - ����� ��� �ᮢ����
   pt   - ���न���� ����� ���, ��।������ �� ᮮ�饭�� 
	  WM_LBUTTONDOWN
 ������ �㭪�� ��뢠���� ��ࠡ��稪�� ᮮ�饭�� WM_LBUTTONDOWN
---------------------------------------------------------------*/
void EditCurveByMouse( HWND hWnd, PROFIL *prof, VES_PAINTDATA *plot, 
		       POINT pt )
{
HDC hDC;
static int oldX, i;

hDC = GetDC( hWnd );
SetROP2( hDC, R2_NOTXORPEN );
SelectObject( hDC, hRedPen);  // �p�᭮� ��p�

if ( PtInRect((LPRECT) &(plot->Frame), pt) ) // ��p�p ����p� ������ ?
  {               // �� 
   if (EditCurve) 
    {             // ����� p�����p������ �� ����祭
      DrawSelectLine( hDC, plot, oldX );      // ��p��� ����� �뤥�����
      DrawCurve( hDC, plot ); // C�p��� �p���� ���
      plot->LCurve.yf[i] = pt.y; // ������ �窨 �� 㪠������ �����
      prof->vez.curve.fRok[i] = prof->vez.OrgRok * 
	pow(10,(float)(plot->Frame.bottom - pt.y)/plot->pxYMod); // �८�ࠧ. ���न�.
      DrawCurve( hDC, plot ); // ���㥬 �p���� ���
      EditCurve = 0;    // �몫���� ०�� ।���஢����
    }
    else 
    {
      i = GetNearestPoint( &(plot->LCurve), pt.x ); // ������ �������. ���
      pt.x = plot->LCurve.x[i];                     // ������� 
      oldX = pt.x;       // �������� ��������� ��p�p�
      DrawSelectLine( hDC, plot, pt.x ); // p��㥬 ����� �뤥�����
      EditCurve = 1;      // ������� ०�� ।���஢����
    }
  }
else
  {
   if (EditCurve) // ����� p�����p������ �� ����祭
    {
      DrawSelectLine( hDC, plot, oldX ); // ��p��� ����� �뤥�����
      EditCurve = 0;
    }
  }
ReleaseDC( hWnd, hDC );
}

/* ------------------------------------------------------------
   DrawSelectLine 
---------------------------------------------------------------*/
void DrawSelectLine( HDC hDC, VES_PAINTDATA *Plot, int x )
{
SelectObject( hDC, hRedPen);  // �p�᭮� ��p�
MoveTo( hDC, x, Plot->Frame.bottom);
LineTo( hDC, x, Plot->Frame.top);
}

/* --------------------------------------------------------------
   GetNearestPoint  ������� ������ ������襩 �� �� ������
   �窨 �����᪮� �p���� � �������� �窥. 
   x - ������ �������� �窨 � �����᪨� ���p������
------------------------------------------------------------------*/
int GetNearestPoint( LOGCURVE *lc, int x )
{
int i, imin;
int dx, mindx = 10000;

for ( i = 0; i < lc->n; i ++ )
 {
  dx = abs( x - lc->x[i]);
  if ( dx < mindx ) { mindx = dx; imin = i; }
 }
return imin;
}


