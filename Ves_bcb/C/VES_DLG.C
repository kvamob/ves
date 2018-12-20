// Файл ves_dlg.c : часть проекта VES for Windows
// Функции обработки диалоговых окон

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "ves.h"
#include "ves_rc.h"


BOOL FAR PASCAL AboutDlg(HWND hDlg, unsigned message, WORD wParam, 
			 LONG lParam);
BOOL FAR PASCAL InfoDlg(HWND hDlg, unsigned message, WORD wParam, 
			 LONG lParam);
BOOL FAR PASCAL VesInterprDlg(HWND hDlg, unsigned message, WORD wParam,
			    LONG lParam);

void InitInterprDlg(HWND hDlg);
int _IsHandler( HANDLE *pHandle, int len, int handle );
void SetControlsVisib( HANDLE *phCtrl, int hSize, int n );
void SetVESControls(HWND hDlg);
//float get_step( float val );
void InitInfoDlg(HWND hDlg);

extern void AutoInterpr( VEZ *vez, float RMS, int max_iteration );
extern void solve_type_curve( VEZ *data );
extern LONG DoMenuCurveNext(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
extern LONG DoMenuCurvePrev(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
extern LONG DoMenuCurveSave(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);

/* ------------ Глобальные переменные --------------------*/
extern HANDLE hFont;
extern PROFIL Prof;
extern HANDLE hNormalCursor, hHourGlassCursor;
extern HWND   hFrame;
extern int     InterprMode;   // Режим интерпретации - ручная или автоматич.
extern char szTemp[]; // Буфер для хранения имени файла

/* -------------------------------------------------------
   AboutDlg Функция управления диалоговым окном "About".
 -------------------------------------------------------- */
BOOL FAR PASCAL AboutDlg(HWND hDlg, unsigned message, WORD wParam, 
			 LONG lParam)
{
	 switch(message)
	{
	case WM_INITDIALOG:
//               Ctl3dAutoSubclassDlg(hDlg, CTL3D_ALL );
		 SendMessage( hDlg, WM_SETFONT, hFont, 0L );
		 return TRUE;
	case WM_COMMAND:
	    if(wParam == IDOK || wParam == IDCANCEL)
		{
		EndDialog(hDlg, TRUE);
		return TRUE;
		}
	    break;
	}
    return FALSE;
}

/* -------------------------------------------------------
   InfoDlg Функция управления диалоговым окном "Info"
 -------------------------------------------------------- */
BOOL FAR PASCAL InfoDlg(HWND hDlg, unsigned message, WORD wParam, 
			 LONG lParam)
{
    switch(message)
	{
	case WM_INITDIALOG:
//               Ctl3dAutoSubclassDlg(hDlg, CTL3D_ALL );
		 InitInfoDlg(hDlg);
		 return TRUE;
	case WM_COMMAND:
	    if(wParam == IDOK || wParam == IDCANCEL)
		{
		EndDialog(hDlg, TRUE);
		return TRUE;
		}
	    break;
	}
    return FALSE;
}

/* ----------------------------------------------------------
   InitInfoDlg Функция инициализации управляющих элементов
   диалогового окна "Init".
 ------------------------------------------------------------ */
void InitInfoDlg(HWND hDlg)
{
HWND hwnd;
HANDLE hListBox; // дескpиптоp окна списка полевых данных
char temp[40];
int i;

//SetWindowText( hDlg, "VES Info");
 
 SetDlgItemText(hDlg, IDT_FNAME, szTemp );
 SetDlgItemText(hDlg, IDT_AREANAME, Prof.hdr.areaname);
 SetDlgItemText(hDlg, IDT_PROFNAME, Prof.hdr.profname);
 SetDlgItemText(hDlg, IDT_CURVENAME,Prof.vez.ID_curve );
 
 sprintf(temp,"%d", Prof.vez.curve.n);
 SetDlgItemText(hDlg, IDT_NSAMPLES, temp);
 
 if ( Prof.vez.model.n ) // Есть рассчитанная кривая
 {
   for ( i = 0; i < Prof.vez.model.n - 1; i ++ ) // Напишем значения 
     {
       sprintf( temp, "%d", i + 1 );
       SetDlgItemText(hDlg, IDT_LAYER1 + i, temp ); // номер слоя
       sprintf( temp, "%.1f", Prof.vez.model.ro[i] );
       SetDlgItemText(hDlg, IDT_RESIS1 + i, temp ); // сопротивление
       sprintf( temp, "%.1f", Prof.vez.model.h[i] );
       SetDlgItemText(hDlg, IDT_THICK1 + i, temp ); // мощность
     }
   i = Prof.vez.model.n - 1;
   sprintf( temp, "%d", i + 1 );
   SetDlgItemText(hDlg, IDT_LAYER1 + i, temp ); // номер последн. слоя
   sprintf( temp, "%.1f", Prof.vez.model.ro[i] );
   SetDlgItemText(hDlg, IDT_RESIS1 + i, temp ); // сопр. посл. слоя

   sprintf(temp,"RMS = %.1f\%", Prof.vez.RMS);
   SetDlgItemText(hDlg, IDT_RMS, temp);
 } else SetDlgItemText(hDlg, IDT_RMS, " " );
 
 sprintf(temp,"XYZ = %g, %g, %g", Prof.vez.X,Prof.vez.Y,Prof.vez.Z);
 SetDlgItemText(hDlg, IDT_COORD, temp );
    
    // Заполним список полевых данных
 hListBox = GetDlgItem( hDlg, IDC_LB_FIELDDATA ); // опpеделим его дескp.
 SendMessage( hListBox, WM_SETREDRAW, FALSE, 0L ); // чтоб не мелькало
// strcpy( temp," AB/2  Resist.");
// SendMessage( hListBox, LB_ADDSTRING, 0, (LONG)temp );// пеpвая стpока
 for ( i = 0; i < Prof.vez.curve.n; i ++ ) 
 { 
  sprintf( temp, " %6.1f %9.1f", Prof.vez.curve.AB2[i],Prof.vez.curve.fRok[i]);
  SendMessage( hListBox, LB_ADDSTRING, 0, (LONG) temp );
 }
 SendMessage( hListBox, WM_SETREDRAW, TRUE, 0L ); // Отобpазить список

 sprintf(temp," Curve \#%d of %d", Prof.hdr.count, Prof.hdr.npoints );
 SetDlgItemText(hDlg, IDT_NCURVE, temp );
}


//_________________________________________________________________
//_   Глобальные переменные, используемые функциями, связанными   _
//_             с диалоговым окном "Interpretation".              _
//_________________________________________________________________

static HWND phSBRes[MAX_LAYERS], // Массив дескрипторов линеек прокрутки 
				 // сопротивлений слоев  
	    phEBRes[MAX_LAYERS],  
	phSBThick[MAX_LAYERS-1], // Массив дескрипторов линеек прокрутки
				 // мощностей слоев
	phEBThick[MAX_LAYERS-1];
				 
static HWND hSBNlayers;          // Дескриптор линейки прокрутки числа слоев
static HWND hCBInterpr;      // Дескриптор переключтаеля режима интерпр.

static HDC hDC;
static VEZ svez; // Структура, где хранятся данные на время работы
		 // с диалоговым окном

/* ------------------------------------------------------------
   VesInterprDlg Функция управления диалоговым окном 
   "Interpr".
 ------------------------------------------------------------- */
BOOL FAR PASCAL VesInterprDlg(HWND hDlg, unsigned message, WORD wParam,
			    LONG lParam)
{
HWND hwnd;
char temp[12];          // Вспомог. буфер
int  i;
int res_pos, thick_pos; // Положение движков полос прокрутки
			// сопротивлений и мощностей слоев
float step;    

switch(message)
    {
	 case WM_INITDIALOG:
/* Инициализация управляющих окон диалогового окна. */
	InitInterprDlg(hDlg);
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
//          , dirlpos, dirrpos;

//            hChData = GetWindowWord(hwndActive, 0);
//            npChData = (NPCHDATA) LocalLock(hChData);

   /* Определение источника сообщения WM_HSCROLL. */
	if( hsb = HIWORD(lParam) )   // получим дескриптор источника
	{   
	 if (hsb == hSBNlayers) // это линейка прокрутки числа слоев
	 {
	   if(wParam == SB_LINEUP && Prof.vez.model.n
	      > 0 ) Prof.vez.model.n -= 1;
	   if(wParam == SB_LINEDOWN && Prof.vez.model.n
	      < MAX_LAYERS ) Prof.vez.model.n += 1;
		sprintf(temp,"%d", Prof.vez.model.n );
		// обновить органы управления сопротивлениями слоев
		SetDlgItemText(hDlg, IDC_EB_NLAYERS, temp);
		// Установим видимость оpганов упpавления 
		// сопpотивлениями и мощностями слоев
//              SetControlsVisib( phSBRes, MAX_LAYERS, Prof.vez.model.n );
//              SetControlsVisib( phSBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);
//              SetControlsVisib( phEBRes, MAX_LAYERS, Prof.vez.model.n );
//              SetControlsVisib( phEBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);
		SetVESControls( hDlg ); // Установим упавляющие оpганы
	 }
	 i = _IsHandler( phSBRes, MAX_LAYERS, hsb ); // Проверим
	  if ( i >= 0 )
	   {  // Это линейка прокрутки сопротивлений, i - номер слоя 
//           step = get_step(Prof.vez.model.ro[i]);
	     if(wParam == SB_LINEUP   ) Prof.vez.model.ro[i] -= 1;
	     if(wParam == SB_LINEDOWN ) Prof.vez.model.ro[i] += 1;
	     if(wParam == SB_PAGEDOWN ) Prof.vez.model.ro[i] += 10;
	     if(wParam == SB_PAGEUP   ) Prof.vez.model.ro[i] -= 10;
	     if(wParam == SB_THUMBPOSITION || wParam == SB_THUMBTRACK)
		  Prof.vez.model.ro[i] = pow(10,LOWORD(lParam));
	     if ( Prof.vez.model.ro[i] < MIN_RESIST ) 
			   Prof.vez.model.ro[i] = MIN_RESIST;
	     if ( Prof.vez.model.ro[i] > MAX_RESIST ) 
			   Prof.vez.model.ro[i] = MAX_RESIST;

	     sprintf(temp,"%.1f", Prof.vez.model.ro[i] );
	     res_pos = log10(Prof.vez.model.ro[i]);
	     // обновить органы управления сопротивлениями слоев
	     SetDlgItemText(hDlg, IDC_EB_RESIS1 + i, temp);
	     /* Установка положения указателя линйки прокрутки. */
	     SetScrollPos(phSBRes[i], SB_CTL, res_pos, TRUE);
	  }
	  
	  i = _IsHandler( phSBThick, MAX_LAYERS-1, hsb );
	  if ( i >= 0 )
	    {  // Это линейка прокрутки мощностей, i - номер слоя 
//           step = get_step(Prof.vez.model.h[i]);
	     if(wParam == SB_LINEUP   ) Prof.vez.model.h[i] -= 1;
	     if(wParam == SB_LINEDOWN ) Prof.vez.model.h[i] += 1;
	     if(wParam == SB_PAGEDOWN ) Prof.vez.model.h[i] += 5;
	     if(wParam == SB_PAGEUP   ) Prof.vez.model.h[i] -= 5;
	     if(wParam == SB_THUMBPOSITION || wParam == SB_THUMBTRACK)
		  Prof.vez.model.h[i] = pow(10,(LOWORD(lParam))); 
	     if ( Prof.vez.model.h[i] < MIN_THICK ) 
			   Prof.vez.model.h[i] = MIN_THICK;
	     if ( Prof.vez.model.h[i] > MAX_THICK ) 
			   Prof.vez.model.h[i] = MAX_THICK;
		    
	     sprintf(temp,"%.1f", Prof.vez.model.h[i] );
	     thick_pos = log10(Prof.vez.model.h[i]); 
	     // обновить органы управления мощностями слоев
	     SetDlgItemText(hDlg, IDC_EB_THICK1 + i, temp);
	     /* Установка положения указателя линйки прокрутки. */
	     SetScrollPos(phSBThick[i], SB_CTL, thick_pos, TRUE);
	   }
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
	  case IDC_EB_NLAYERS:
	    /* Строка-редактор числа слоев модели */
	    if ( wNotif == EN_KILLFOCUS ) // Потерян фокус ввода
	     {
//                  hChData = GetWindowWord(hwndActive, 0);
//                  npChData = (NPCHDATA) LocalLock(hChData);
	       GetDlgItemText(hDlg, IDC_EB_NLAYERS, (LPSTR) temp, 11 );
	       sscanf( temp,"%d", &n );
	       if ( n < 0 ) n = 0;
	       if ( n > MAX_LAYERS ) n = MAX_LAYERS;
	       Prof.vez.model.n = n;
	       sprintf( temp,"%d", n );
	       SetDlgItemText(hDlg, wParam, (LPSTR)temp);
	       // <><><<><><><><><><><><><><><
	       // Установим видимость оpганов упpавления 
	       // сопpотивлениями и мощностями слоев
	       SetControlsVisib( phSBRes, MAX_LAYERS, Prof.vez.model.n );
	       SetControlsVisib( phSBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);
	       SetControlsVisib( phEBRes, MAX_LAYERS, Prof.vez.model.n );
	       SetControlsVisib( phEBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);
	      }
	      
	      break;

	  case IDC_EB_RESIS1:  // Окна редактирования сопротивлений слоев
	  case IDC_EB_RESIS2: 
	  case IDC_EB_RESIS3:
	  case IDC_EB_RESIS4:
	  case IDC_EB_RESIS5:
	  case IDC_EB_RESIS6:
	    if ( wNotif == EN_KILLFOCUS ) // Потерян фокус ввода
	     {
	       i = wParam - IDC_EB_RESIS1; // Номер слоя
	       GetDlgItemText( hDlg, wParam, (LPSTR)temp, 11 );
	       sscanf( temp, "%f", &v );
	       if ( v < MIN_RESIST ) v = MIN_RESIST;
	       if ( v > MAX_RESIST ) v = MAX_RESIST;
	       Prof.vez.model.ro[i] = v;
	       sprintf( temp, "%.1f", v );
	       SetDlgItemText(hDlg, wParam, (LPSTR)temp);
	       res_pos = log10(Prof.vez.model.ro[i]);
	       SetScrollPos(phSBRes[i], SB_CTL, res_pos, TRUE);
	     }
	     break;
	  
	  case IDC_EB_THICK1:
	  case IDC_EB_THICK2:
	  case IDC_EB_THICK3:
	  case IDC_EB_THICK4:
	  case IDC_EB_THICK5:
	    if ( wNotif == EN_KILLFOCUS ) // Потерян фокус ввода
	     {
	       i = wParam - IDC_EB_THICK1; // Номер слоя
	       GetDlgItemText( hDlg, wParam, (LPSTR)temp, 11 );
	       sscanf( temp, "%f", &v );
	       if ( v < MIN_THICK ) v = MIN_THICK;
	       if ( v > MAX_THICK ) v = MAX_THICK;
	       Prof.vez.model.h[i] = v;
	       sprintf( temp, "%.1f", v );
	       SetDlgItemText(hDlg, wParam, (LPSTR)temp );
	       thick_pos = log10(Prof.vez.model.h[i]);
	       SetScrollPos(phSBThick[i], SB_CTL, thick_pos, TRUE);
	     }
	     break;
		
	  case IDC_CB_INTERPR :
	     switch(InterprMode) {
		case AUTO   :
		  SetWindowText( hDlg, "Model Data : Manual Interpretation");
		  InterprMode = MANUAL;
		  break;
		case MANUAL : 
		  SetWindowText( hDlg, "Model Data : Automatic Interpretation");
		  InterprMode = AUTO;
		  break; 
	      }
	     break; 
	     
		case IDC_BU_NEXT :
	       /* Пользователь нажал кнопку "Next". */
		 DoMenuCurveNext( hFrame, 0, 0, 0 );
		 SetVESControls( hDlg ); // Инициализируем органы управления
		break;
		
		case IDC_BU_PREV :
	       /* Пользователь нажал кнопку "Prev". */
		 DoMenuCurvePrev( hFrame, 0, 0, 0 );
		 SetVESControls( hDlg ); // Инициализируем органы управления
		break;
		
		case IDC_BU_SAVE :
	       /* Пользователь нажал кнопку "Save". */
		 DoMenuCurveSave( hDlg, 0, 0, 0 );
		break;
		
		case IDCANCEL:
	       /* Пользователь нажал кнопку "Cancel". */
		      EndDialog(hDlg,TRUE);
		break;

		case IDOK:          /*  save current settings  */
	       /* Пользователь нажал кнопку "OK". */
		    if (Prof.vez.model.n == 0) return TRUE;

		    SetCursor( hHourGlassCursor ); // Курсор - ожидание
		    // Вызовем процедуру интерпретации кривой
		    if ( InterprMode == AUTO ) 
		    {
		      AutoInterpr( &(Prof.vez), 0.01, MAX_ITERATION );
		      SetVESControls(hDlg); // Переустановим окно диалога
		    }
		    else
		      solve_type_curve( &(Prof.vez) );

		    SetCursor( hNormalCursor );
		    InvalidateRect(hFrame,NULL,TRUE); // Перерисуем график
		    UpdateWindow(hFrame);

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
   InitInterprDlg Функция инициализации управляющих элементов
   диалогового окна "Interpr".
 ------------------------------------------------------------ */
void InitInterprDlg(HWND hDlg)
{
HWND hwnd;
char temp[12];
int i;

 svez = Prof.vez; // Сохраним данные
//SendMessage( hDlg, WM_SETFONT, hFont, TRUE );
    
 hCBInterpr = GetDlgItem( hDlg, IDC_CB_INTERPR );

 switch ( InterprMode )  {
  case AUTO   : 
		     // установим переключатель режима интерпр.
//   if (! SendMessage( hCBInterpr, BM_GETCHECK, 0, 0L ))
   SendMessage( hCBInterpr, BM_SETCHECK, TRUE, 0L );
		     //  заголовок диалогового окна
   SetWindowText( hDlg, "Model Data : Automatic Interpretation");
   break;
  
  case MANUAL :
   
   SendMessage( hCBInterpr, BM_SETCHECK, FALSE, 0L );
   
   SetWindowText( hDlg, "Model Data : Manual Interpretation");
   break;
 }
    
    
//    if ( InterprMode == AUTO )   // Заголовок диалогового окна
//     {
//      SendMessage( GetDlgItem(), BM_SETCHECK, TRUE, 0L );
//      if (! SendMessage( hCBInterpr, BM_GETCHECK, TRUE, 0L ))
	      ;
//      SetWindowText( hDlg, "Model Data : Automatic Interpretation");
//     }
//    else
//      SetWindowText( hDlg, "Model Data : Manual Interpretation");

    // Определим дескриптор линейки прокрутки числа слоев
    hSBNlayers = GetDlgItem( hDlg, IDC_SB_NLAYERS );
    
    for ( i = 0; i < MAX_LAYERS ; i ++ )
    {
      /* Определение идентификаторов окон линеек прокрутки. */
      phSBRes[i] = GetDlgItem(hDlg, IDC_SB_RESIS1 + i );
      /* Определение идентификаторов окон pедактиpования */
      phEBRes[i] = GetDlgItem(hDlg, IDC_EB_RESIS1 + i );
      /* Установка диапазонов линеек прокрутки. */
      SetScrollRange(phSBRes[i],SB_CTL,(int)log10(MIN_RESIST),(int)log10(MAX_RESIST),TRUE);
// SendMessage( phEBRes[i], WM_SETFONT, hFont, TRUE );
//      SetScrollRange(phSBRes[i],SB_CTL,0,4,TRUE);
    }
    for ( i = 0; i < MAX_LAYERS - 1; i ++ )
    {
      /* Определение идентификаторов окон линеек прокрутки. */
      phSBThick[i] = GetDlgItem( hDlg, IDC_SB_THICK1 + i );
      /* Определение идентификаторов окон pедактиpования */
      phEBThick[i] = GetDlgItem( hDlg, IDC_EB_THICK1 + i );
      /* Установка диапазонов линеек прокрутки. */
      SetScrollRange(phSBThick[i],SB_CTL,log10(MIN_THICK),log10(MAX_THICK),TRUE);
    }
    
    // Установим видимость оpганов упpавления сопpот. и мощностями слоев
//    SetControlsVisib( phSBRes, MAX_LAYERS, Prof.vez.model.n );
//    SetControlsVisib( phSBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);
//    SetControlsVisib( phEBRes, MAX_LAYERS, Prof.vez.model.n );
//    SetControlsVisib( phEBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);

    SetVESControls( hDlg ); // Инициализируем органы управления
}

/* ----------------------------------------------------------------------
   _IsHandler Функция просматривает массив дескрипторов pHandle длиной
   len на предмет обнаружения в нем дескриптора handle. Если он обнаружен,
   возвращается его порядковый номер в массиве ( от 0).
   Если нет, возвращается -1
 ---------------------------------------------------------------------- */
int _IsHandler( HANDLE *pHandle, int len, int handle )
{
int i;
for ( i = 0; i < len; i ++ ) if ( pHandle[i] == handle ) return i;
return -1;
}

/* -----------------------------------------------------------------------
    SetControlsVisib
    Функция устанавливает видимость элементов упpавления, дескpиптоpы
    котоpых находятся в массиве phCtrl. Пеpвые n элементов становятся
    видимыми, остальные невидимыми(недоступными). hSize - количество
    элементов в массиве phCtrl.
 ---------------------------------------------------------------------- */
void SetControlsVisib( HANDLE *phCtrl, int hSize, int n )
{
int i, visibl;    

 for ( i = 0; i < hSize; i ++ )
  {
//      visibl = ( i >= n ) ? SW_HIDE : SW_SHOW;
//      ShowWindow( phCtrl[i], visibl );
//      ShowWindow( phCtrl[i], visibl );
      visibl = ( i >= n ) ? FALSE : TRUE;
      EnableWindow(phCtrl[i], visibl);
      EnableWindow(phCtrl[i], visibl);
  }
}


/* ----------------------------------------------------------
   SetVESControls Функция устанавливает органы управления
   в окне диалога интерпретации кривых ВЭЗ с идентификатором
   hDlg, используются некоторые глобальные переменные.
 ------------------------------------------------------------ */
void SetVESControls(HWND hDlg)
{
HWND hwnd;
char temp[12];
int i;
    
    /* Вывод данных в окна редактирования. */
    sprintf(temp,"%d", Prof.vez.model.n);
    SetDlgItemText(hDlg, IDC_EB_NLAYERS, temp );
    SetDlgItemText(hDlg, IDT_CURVE_ID, Prof.vez.ID_curve );

    // Установим видимость оpганов упpавления сопpот. и мощностями слоев
    SetControlsVisib( phSBRes, MAX_LAYERS, Prof.vez.model.n );
    SetControlsVisib( phSBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);
    SetControlsVisib( phEBRes, MAX_LAYERS, Prof.vez.model.n );
    SetControlsVisib( phEBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);

    for ( i = 0; i < Prof.vez.model.n ; i ++ )
    {
      // Выводим значения в окна редактирования
      sprintf(temp,"%.1f", Prof.vez.model.ro[i] );
      SetDlgItemText(hDlg, IDC_EB_RESIS1 + i, temp );
//      /* Установка диапазонов линеек прокрутки. */
//      SetScrollRange(phSBRes[i],SB_CTL,(int)log10(MIN_RESIST),(int)log10(MAX_RESIST),TRUE);
      /* Установка положения указателей линеек прокрутки. */
      SetScrollPos(phSBRes[i],SB_CTL,(int)log10(Prof.vez.model.ro[i]),TRUE);
    }
    for ( i = 0; i < Prof.vez.model.n - 1; i ++ )
    {
      // Выводим значения в окна редактирования
      sprintf(temp,"%.1f", Prof.vez.model.h[i] );
      SetDlgItemText(hDlg, IDC_EB_THICK1 + i, temp );
//      /* Установка диапазонов линеек прокрутки. */
//      SetScrollRange(phSBThick[i],SB_CTL,log10(MIN_THICK),log10(MAX_THICK),TRUE);
      /* Установка положения указателей линеек прокрутки. */
      SetScrollPos(phSBThick[i],SB_CTL,(int)log10(Prof.vez.model.h[i]),TRUE);
    }
}

///* -------------------------------------------------------------------
//   get_step Возвращает шаг изменения параметра, зависящий от величины 
//   этого параметра
//   val - значение параметра
//----------------------------------------------------------------------*/
//float get_step( float val )
//{
//float rez;

//rez = pow( 10, floor( log10( val )));
//return rez;
//}
