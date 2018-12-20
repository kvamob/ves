// Файл ves_dlg1.c : часть проекта VES for Windows
// Функции обработки диалогового окна решения прямой задачи ВЭЗ

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "ves.h"
#include "ves_rc.h"


BOOL FAR PASCAL VesTypeCurveDlg(HWND hDlg, unsigned message, WORD wParam,
				 LONG lParam);

void InitVesTypeCurveDlg(HWND hDlg);
extern int _IsHandler( HANDLE *pHandle, int len, int handle );
void SetVTCControlsVisib( HANDLE *phCtrl, int hSize, int n );
void SetVTCControls(HWND hDlg);
//float get_step( float val );

extern int _IsHandler( HANDLE *pHandle, int len, int handle );
extern void solve_type_curve( VEZ *data );

/* ------------ Глобальные переменные --------------------*/
extern HANDLE hFont;
extern HPEN   hRedPen;
extern HANDLE hNormalCursor, hHourGlassCursor;
extern HWND   hFrame;
// extern char szTemp[]; // Буфер для хранения имени файла
MODEL_TC   model;


//_________________________________________________________________
//_   Глобальные переменные, используемые функциями, связанными   _
//_             с диалоговым окном "VESTypeCurve".                   _
//_________________________________________________________________

static  phEBRes[MAX_LAYERS_TC],  // Массив дескрипторов окон редактирования
				 // сопротивлений слоев
	phEBThick[MAX_LAYERS_TC-1]; // Массив дескрипторов окон редактирования
					 // мощностей слоев

static HWND hSBNlayers;      // Дескриптор линейки прокрутки числа слоев

static HDC hDC;

//static VEZ svez; // Структура, где хранятся данные на время работы
		 // с диалоговым окном

/* ------------------------------------------------------------
	VesInterprDlg Функция управления диалоговым окном
	"Interpr".
 ------------------------------------------------------------- */
BOOL FAR PASCAL VesTypeCurveDlg(HWND hDlg, unsigned message, WORD wParam,
				 LONG lParam)
{
HWND hwnd;

RECT  r1;
RECT  r2;
int   x,y;
int   bh;               // Высота заголовка окна в пикселах


char temp[12];          // Вспомог. буфер

int   i;

float first_absc;        // Абсцисса первой точки теоретической кривой

//int res_pos, thick_pos; // Положение движков полос прокрутки
			// сопротивлений и мощностей слоев

switch(message)
    {
		case WM_INITDIALOG:
/* Инициализация управляющих окон диалогового окна. */
	InitVesTypeCurveDlg(hDlg);
	return TRUE;

//      case WM_PAINT:
//          PostMessage(hDlg,WM_WSM_DLGPAINT,0,0L);
//          return TRUE;

//      case WM_WSM_DLGPAINT:
//          SetTextColor(hDC, RGB(fRed,fGreen,fBlue));
//          SetBkColor(hDC, RGB(bRed,bGreen,bBlue));
//          TextOut(hDC, 0,0,(LPSTR)text, lstrlen(text));
//          return TRUE;

    case WM_HSCROLL:
   /* Сообщения горизонтальных линеек прокрутки. */
    {
      HWND hsb;       // дескриптор полосы прокрутки

   /* Определение источника сообщения WM_HSCROLL. */
	if( hsb = HIWORD(lParam) )   // получим дескриптор источника
	{
	 if (hsb == hSBNlayers) // это линейка прокрутки числа слоев
	 {
	   if(wParam == SB_LINEUP && model.n > 1 ) model.n -= 1;
	   if(wParam == SB_LINEDOWN && model.n < MAX_LAYERS_TC ) model.n += 1;
	   sprintf(temp,"%d", model.n );
	   // обновить органы управления сопротивлениями слоев
	    SetDlgItemText(hDlg, IDC_EB_NLAYERS_TC, temp);
	   // Установим видимость оpганов упpавления 
	   // сопpотивлениями и мощностями слоев
	    SetVTCControls( hDlg ); // Установим упавляющие оpганы
	 }
//         i = _IsHandler( phSBRes, MAX_LAYERS_TC, hsb ); // Проверим
//          if ( i >= 0 )
//           {  // Это линейка прокрутки сопротивлений, i - номер слоя 
//           step = get_step(Prof.vez.model.ro[i]);
//             if(wParam == SB_LINEUP   ) Prof.vez.model.ro[i] -= 1;
//             if(wParam == SB_LINEDOWN ) Prof.vez.model.ro[i] += 1;
//             if(wParam == SB_PAGEDOWN ) Prof.vez.model.ro[i] += 10;
//             if(wParam == SB_PAGEUP   ) Prof.vez.model.ro[i] -= 10;
//             if(wParam == SB_THUMBPOSITION || wParam == SB_THUMBTRACK)
//                  Prof.vez.model.ro[i] = pow(10,LOWORD(lParam));
//             if ( Prof.vez.model.ro[i] < MIN_RESIST )
//                           Prof.vez.model.ro[i] = MIN_RESIST;
//             if ( Prof.vez.model.ro[i] > MAX_RESIST ) 
//                           Prof.vez.model.ro[i] = MAX_RESIST;

//             sprintf(temp,"%.1f", Prof.vez.model.ro[i] );
//             res_pos = log10(Prof.vez.model.ro[i]);
//             // обновить органы управления сопротивлениями слоев
//             SetDlgItemText(hDlg, IDC_EB_RESIS1 + i, temp);
//             /* Установка положения указателя линйки прокрутки. */
//             SetScrollPos(phSBRes[i], SB_CTL, res_pos, TRUE);
//            }
	  
//          i = _IsHandler( phSBThick, MAX_LAYERS_TC-1, hsb );
//          if ( i >= 0 )
//            {  // Это линейка прокрутки мощностей, i - номер слоя 
//           step = get_step(Prof.vez.model.h[i]);
//             if(wParam == SB_LINEUP   ) Prof.vez.model.h[i] -= 1;
//             if(wParam == SB_LINEDOWN ) Prof.vez.model.h[i] += 1;
//             if(wParam == SB_PAGEDOWN ) Prof.vez.model.h[i] += 5;
//             if(wParam == SB_PAGEUP   ) Prof.vez.model.h[i] -= 5;
//             if(wParam == SB_THUMBPOSITION || wParam == SB_THUMBTRACK)
//                  Prof.vez.model.h[i] = pow(10,(LOWORD(lParam)));
//             if ( Prof.vez.model.h[i] < MIN_THICK ) 
//                           Prof.vez.model.h[i] = MIN_THICK;
//             if ( Prof.vez.model.h[i] > MAX_THICK ) 
//                           Prof.vez.model.h[i] = MAX_THICK;
		    
//             sprintf(temp,"%.1f", Prof.vez.model.h[i] );
//             thick_pos = log10(Prof.vez.model.h[i]); 
//             // обновить органы управления мощностями слоев
//             SetDlgItemText(hDlg, IDC_EB_THICK1 + i, temp);
//             /* Установка положения указателя линйки прокрутки. */
//             SetScrollPos(phSBThick[i], SB_CTL, thick_pos, TRUE);
//           }
	 }    /* end if(hsb = ... )  */
       }      /* end case WM_HSCROLL */
      return TRUE;

    case WM_COMMAND:   /* Сообщения, поступившие от кнопок. */
     {
      WORD wNotif;  // Код сообщения
      int n;     // Вспомог. переменные
      float v;
		int  i;

      wNotif = HIWORD( lParam );        // Код сообщения

       switch(wParam)  {
	  case IDC_EB_NLAYERS_TC:
	    /* Строка-редактор числа слоев модели */
	    if ( wNotif == EN_KILLFOCUS ) // Потерян фокус ввода
	     {
	       GetDlgItemText(hDlg, IDC_EB_NLAYERS_TC, (LPSTR) temp, 11 );
	       sscanf( temp,"%d", &n );
			 if ( n < 1 ) n = 1;
	       if ( n > MAX_LAYERS_TC ) n = MAX_LAYERS_TC;
	       model.n = n;
	       sprintf( temp,"%d", n );
	       SetDlgItemText(hDlg, wParam, (LPSTR)temp);
	       // <><><<><><><><><><><><><><><
	       // Установим видимость оpганов упpавления 
	       // сопpотивлениями и мощностями слоев
//               SetVTCControlsVisib( phSBRes, MAX_LAYERS_TC, model.n );
//               SetVTCControlsVisib( phSBThick, MAX_LAYERS_TC - 1, model.n - 1);
		 SetVTCControlsVisib( phEBRes, MAX_LAYERS_TC, model.n );
		 SetVTCControlsVisib( phEBThick, MAX_LAYERS_TC - 1, model.n - 1);
	      }
	      
	  break;

	  case IDC_R1:  // Окна редактирования сопротивлений слоев
	  case IDC_R2: 
	  case IDC_R3:
	  case IDC_R4:
	  case IDC_R5:
	  case IDC_R6:
	  case IDC_R7:
	  case IDC_R8:
	    if ( wNotif == EN_KILLFOCUS ) // Потерян фокус ввода
	     {
	       i = wParam - IDC_R1; // Номер слоя
	       GetDlgItemText( hDlg, wParam, (LPSTR)temp, 11 );
	       sscanf( temp, "%f", &v );
	       if ( v < MIN_RESIST ) v = MIN_RESIST;
	       if ( v > MAX_RESIST ) v = MAX_RESIST;
	       model.ro[i] = v;
	       sprintf( temp, "%.1f", v );
			 SetDlgItemText(hDlg, wParam, (LPSTR)temp);
//               res_pos = log10(Prof.vez.model.ro[i]);
//               SetScrollPos(phSBRes[i], SB_CTL, res_pos, TRUE);
	     }
	     break;
	  
	  case IDC_H1:
	  case IDC_H2:
	  case IDC_H3:
	  case IDC_H4:
	  case IDC_H5:
	  case IDC_H6:
	  case IDC_H7:
	    if ( wNotif == EN_KILLFOCUS ) // Потерян фокус ввода
	     {
	       i = wParam - IDC_EB_THICK1; // Номер слоя
	       GetDlgItemText( hDlg, wParam, (LPSTR)temp, 11 );
	       sscanf( temp, "%f", &v );
	       if ( v < MIN_THICK ) v = MIN_THICK;
	       if ( v > MAX_THICK ) v = MAX_THICK;
	       model.h[i] = v;
	       sprintf( temp, "%.1f", v );
			 SetDlgItemText(hDlg, wParam, (LPSTR)temp );
//               thick_pos = log10(Prof.vez.model.h[i]);
//               SetScrollPos(phSBThick[i], SB_CTL, thick_pos, TRUE);
	     }
	     break;
		
//          case IDC_CB_INTERPR :
//             switch(InterprMode) {
//                case AUTO   :
//                  SetWindowText( hDlg, "Model Data : Manual Interpretation");
//                  InterprMode = MANUAL;
//                  break;
//                case MANUAL : 
//                  SetWindowText( hDlg, "Model Data : Automatic Interpretation");
//                  InterprMode = AUTO;
//                  break; 
//              }
//             break; 
		
		case IDCANCEL:
	       /* Пользователь нажал кнопку "Cancel". */
		      EndDialog(hDlg,TRUE);
		break;

		case IDOK:          /*  save current settings  */
	       /* Пользователь нажал кнопку "OK". */
//                    if (Prof.vez.model.n == 0) return TRUE;
//
//                    SetCursor( hHourGlassCursor ); // Курсор - ожидание
//                    // Вызовем процедуру интерпретации кривой
//                    if ( InterprMode == AUTO ) 
//                    {
//                      AutoInterpr( &(Prof.vez), 0.01, MAX_ITERATION );
//                      SetVESControls(hDlg); // Переустановим окно диалога
//                    }
//                   else
//                      solve_type_curve( &(Prof.vez) );
//
//                    SetCursor( hNormalCursor );
//                    InvalidateRect(hFrame,NULL,TRUE); // Перерисуем график
//                    UpdateWindow(hFrame);

//////////////////////////////////////////////////////////////
hDC = GetDC( hDlg );

GetWindowRect( hDlg, &r1);
GetWindowRect( GetDlgItem( hDlg, IDC_FRAME ), &r2 );
bh = GetSystemMetrics( SM_CYCAPTION );  // высота заголовка окна

x = r2.left - r1.left - 1;
y = r2.top - r1.top - bh  - 1;


SetROP2( hDC, R2_NOTXORPEN );
SelectObject( hDC, hRedPen);  // Кpасное пеpо

MoveTo( hDC,  x, y );
LineTo( hDC,  r2.right - r1.left - 2, r2.bottom - r1.top - bh - 2  );
// LineTo( hDC,  10, 100 );

ReleaseDC( hDlg, hDC );
//////////////////////////////////////////////////////////////
		return (TRUE);
		default:
		    break;
	       }          /* end switch( wParam ) */

	       break;
	 }                /* end case WM_COMMAND  */
     }                    /* end switch(message)  */

     return (FALSE);
}


/* ----------------------------------------------------------
   InitVesTypeCurveDlg Функция инициализации управляющих
   элементов диалогового окна "TypeCurve" (расчет крив. ВЭЗ)
 ------------------------------------------------------------ */
void InitVesTypeCurveDlg(HWND hDlg)
{
HWND hwnd;
char temp[12];
int i;

// svez = Prof.vez; // Сохраним данные

model.n = 1;

// Определим дескриптор линейки прокрутки числа слоев
hSBNlayers = GetDlgItem( hDlg, IDC_SB_NLAYERS_TC );
    
for ( i = 0; i < MAX_LAYERS_TC ; i ++ )
 {
//  /* Определение идентификаторов окон линеек прокрутки. */
//   phSBRes[i] = GetDlgItem(hDlg, IDC_SB_RESIS1 + i );

  /* Определение идентификаторов окон pедактиpования */
  phEBRes[i] = GetDlgItem(hDlg, IDC_R1 + i );

//  /* Установка диапазонов линеек прокрутки. */
//      SetScrollRange(phSBRes[i],SB_CTL,(int)log10(MIN_RESIST),(int)log10(MAX_RESIST),TRUE);
// SendMessage( phEBRes[i], WM_SETFONT, hFont, TRUE );
//      SetScrollRange(phSBRes[i],SB_CTL,0,4,TRUE);

 }

for ( i = 0; i < MAX_LAYERS_TC - 1; i ++ )
 {
//     /* Определение идентификаторов окон линеек прокрутки. */
//     phSBThick[i] = GetDlgItem( hDlg, IDC_SB_THICK1 + i );
//      /* Определение идентификаторов окон pедактиpования */

      phEBThick[i] = GetDlgItem( hDlg, IDC_H1 + i );
      /* Установка диапазонов линеек прокрутки. */
//      SetScrollRange(phSBThick[i],SB_CTL,log10(MIN_THICK),log10(MAX_THICK),TRUE);
  }
    
    // Установим видимость оpганов упpавления сопpот. и мощностями слоев
//    SetControlsVisib( phSBRes, MAX_LAYERS, Prof.vez.model.n );
//    SetControlsVisib( phSBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);

    SetVTCControlsVisib( phEBRes, MAX_LAYERS_TC, model.n );
    SetVTCControlsVisib( phEBThick, MAX_LAYERS_TC - 1, model.n - 1);

    SetVTCControls( hDlg ); // Инициализируем органы управления
}

/* ----------------------------------------------------------------------
   _IsHandler Функция просматривает массив дескрипторов pHandle длиной
   len на предмет обнаружения в нем дескриптора handle. Если он обнаружен,
   возвращается его порядковый номер в массиве ( от 0).
   Если нет, возвращается -1
 ---------------------------------------------------------------------- */
//int _IsHandler( HANDLE *pHandle, int len, int handle )
//{
//int i;
//for ( i = 0; i < len; i ++ ) if ( pHandle[i] == handle ) return i;
//return -1;
//}

/* -----------------------------------------------------------------------
   SetVTCControlsVisib
   Функция устанавливает видимость элементов упpавления, дескpиптоpы
   котоpых находятся в массиве phCtrl. Пеpвые n элементов становятся
   видимыми, остальные невидимыми(недоступными). hSize - количество
   элементов в массиве phCtrl.
 ---------------------------------------------------------------------- */
void SetVTCControlsVisib( HANDLE *phCtrl, int hSize, int n )
{
int i, visibl;

 for ( i = 0; i < hSize; i ++ )
  {
      visibl = ( i >= n ) ? SW_HIDE : SW_SHOW;
      ShowWindow( phCtrl[i], visibl );
      ShowWindow( phCtrl[i], visibl );

//        visibl = ( i >= n ) ? FALSE : TRUE;
//        EnableWindow(phCtrl[i], visibl);
//        EnableWindow(phCtrl[i], visibl);
  }
}


/* ----------------------------------------------------------
	SetVTCControls Функция устанавливает органы управления
	в окне диалога расчета кривых ВЭЗ с идентификатором
	hDlg, используются некоторые глобальные переменные.
 ------------------------------------------------------------ */
void SetVTCControls(HWND hDlg)
{
HWND hwnd;
char temp[12];
int i;

	 /* Вывод данных в окна редактирования. */
	 sprintf(temp,"%d", model.n);
	 SetDlgItemText(hDlg, IDC_EB_NLAYERS_TC, temp );
//    SetDlgItemText(hDlg, IDT_CURVE_ID, Prof.vez.ID_curve );

	 // Установим видимость оpганов упpавления сопpот. и мощностями слоев
//    SetControlsVisib( phSBRes, MAX_LAYERS, Prof.vez.model.n );
//    SetControlsVisib( phSBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);
	 SetVTCControlsVisib( phEBRes, MAX_LAYERS_TC, model.n );
	 SetVTCControlsVisib( phEBThick, MAX_LAYERS_TC - 1, model.n - 1);

	 for ( i = 0; i < model.n ; i ++ )
	 {
		// Выводим значения в окна редактирования
		sprintf(temp,"%.1f", model.ro[i] );
		SetDlgItemText(hDlg, IDC_EB_RESIS1 + i, temp );
//      /* Установка положения указателей линеек прокрутки. */
//      SetScrollPos(phSBRes[i],SB_CTL,(int)log10(Prof.vez.model.ro[i]),TRUE);
	 }
	 for ( i = 0; i < model.n - 1; i ++ )
	 {
		// Выводим значения в окна редактирования
		sprintf(temp,"%.1f", model.h[i] );
		SetDlgItemText(hDlg, IDC_EB_THICK1 + i, temp );
//      /* Установка положения указателей линеек прокрутки. */
//      SetScrollPos(phSBThick[i],SB_CTL,(int)log10(Prof.vez.model.h[i]),TRUE);
	 }
}



