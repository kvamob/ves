// ���� ves_dlg.c : ���� �஥�� VES for Windows
// �㭪樨 ��ࠡ�⪨ ���������� ����

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

/* ------------ �������� ��६���� --------------------*/
extern HANDLE hFont;
extern PROFIL Prof;
extern HANDLE hNormalCursor, hHourGlassCursor;
extern HWND   hFrame;
extern int     InterprMode;   // ����� ������樨 - ��筠� ��� ��⮬���.
extern char szTemp[]; // ���� ��� �࠭���� ����� 䠩��

/* -------------------------------------------------------
   AboutDlg �㭪�� �ࠢ����� ��������� ����� "About".
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
   InfoDlg �㭪�� �ࠢ����� ��������� ����� "Info"
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
   InitInfoDlg �㭪�� ���樠����樨 �ࠢ����� ������⮢
   ����������� ���� "Init".
 ------------------------------------------------------------ */
void InitInfoDlg(HWND hDlg)
{
HWND hwnd;
HANDLE hListBox; // ���p���p ���� ᯨ᪠ ������� ������
char temp[40];
int i;

//SetWindowText( hDlg, "VES Info");
 
 SetDlgItemText(hDlg, IDT_FNAME, szTemp );
 SetDlgItemText(hDlg, IDT_AREANAME, Prof.hdr.areaname);
 SetDlgItemText(hDlg, IDT_PROFNAME, Prof.hdr.profname);
 SetDlgItemText(hDlg, IDT_CURVENAME,Prof.vez.ID_curve );
 
 sprintf(temp,"%d", Prof.vez.curve.n);
 SetDlgItemText(hDlg, IDT_NSAMPLES, temp);
 
 if ( Prof.vez.model.n ) // ���� ����⠭��� �ਢ��
 {
   for ( i = 0; i < Prof.vez.model.n - 1; i ++ ) // ����襬 ���祭�� 
     {
       sprintf( temp, "%d", i + 1 );
       SetDlgItemText(hDlg, IDT_LAYER1 + i, temp ); // ����� ᫮�
       sprintf( temp, "%.1f", Prof.vez.model.ro[i] );
       SetDlgItemText(hDlg, IDT_RESIS1 + i, temp ); // ᮯ�⨢�����
       sprintf( temp, "%.1f", Prof.vez.model.h[i] );
       SetDlgItemText(hDlg, IDT_THICK1 + i, temp ); // ��魮���
     }
   i = Prof.vez.model.n - 1;
   sprintf( temp, "%d", i + 1 );
   SetDlgItemText(hDlg, IDT_LAYER1 + i, temp ); // ����� ��᫥��. ᫮�
   sprintf( temp, "%.1f", Prof.vez.model.ro[i] );
   SetDlgItemText(hDlg, IDT_RESIS1 + i, temp ); // ᮯ�. ���. ᫮�

   sprintf(temp,"RMS = %.1f\%", Prof.vez.RMS);
   SetDlgItemText(hDlg, IDT_RMS, temp);
 } else SetDlgItemText(hDlg, IDT_RMS, " " );
 
 sprintf(temp,"XYZ = %g, %g, %g", Prof.vez.X,Prof.vez.Y,Prof.vez.Z);
 SetDlgItemText(hDlg, IDT_COORD, temp );
    
    // �������� ᯨ᮪ ������� ������
 hListBox = GetDlgItem( hDlg, IDC_LB_FIELDDATA ); // ��p������ ��� ���p.
 SendMessage( hListBox, WM_SETREDRAW, FALSE, 0L ); // �⮡ �� ���쪠��
// strcpy( temp," AB/2  Resist.");
// SendMessage( hListBox, LB_ADDSTRING, 0, (LONG)temp );// ��p��� ��p���
 for ( i = 0; i < Prof.vez.curve.n; i ++ ) 
 { 
  sprintf( temp, " %6.1f %9.1f", Prof.vez.curve.AB2[i],Prof.vez.curve.fRok[i]);
  SendMessage( hListBox, LB_ADDSTRING, 0, (LONG) temp );
 }
 SendMessage( hListBox, WM_SETREDRAW, TRUE, 0L ); // �⮡p����� ᯨ᮪

 sprintf(temp," Curve \#%d of %d", Prof.hdr.count, Prof.hdr.npoints );
 SetDlgItemText(hDlg, IDT_NCURVE, temp );
}


//_________________________________________________________________
//_   �������� ��६����, �ᯮ��㥬� �㭪�ﬨ, �易��묨   _
//_             � ��������� ����� "Interpretation".              _
//_________________________________________________________________

static HWND phSBRes[MAX_LAYERS], // ���ᨢ ���ਯ�஢ ������ �ப��⪨ 
				 // ᮯ�⨢����� ᫮��  
	    phEBRes[MAX_LAYERS],  
	phSBThick[MAX_LAYERS-1], // ���ᨢ ���ਯ�஢ ������ �ப��⪨
				 // ��魮�⥩ ᫮��
	phEBThick[MAX_LAYERS-1];
				 
static HWND hSBNlayers;          // ���ਯ�� ������� �ப��⪨ �᫠ ᫮��
static HWND hCBInterpr;      // ���ਯ�� ��४���⠥�� ०��� �����.

static HDC hDC;
static VEZ svez; // �������, ��� �࠭���� ����� �� �६� ࠡ���
		 // � ��������� �����

/* ------------------------------------------------------------
   VesInterprDlg �㭪�� �ࠢ����� ��������� ����� 
   "Interpr".
 ------------------------------------------------------------- */
BOOL FAR PASCAL VesInterprDlg(HWND hDlg, unsigned message, WORD wParam,
			    LONG lParam)
{
HWND hwnd;
char temp[12];          // �ᯮ���. ����
int  i;
int res_pos, thick_pos; // ��������� ������� ����� �ப��⪨
			// ᮯ�⨢����� � ��魮�⥩ ᫮��
float step;    

switch(message)
    {
	 case WM_INITDIALOG:
/* ���樠������ �ࠢ����� ���� ����������� ����. */
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
   /* ����饭�� ��ਧ��⠫��� ������ �ப��⪨. */
    {
      HWND hsb;       // ���ਯ�� ������ �ப��⪨
//          , dirlpos, dirrpos;

//            hChData = GetWindowWord(hwndActive, 0);
//            npChData = (NPCHDATA) LocalLock(hChData);

   /* ��।������ ���筨�� ᮮ�饭�� WM_HSCROLL. */
	if( hsb = HIWORD(lParam) )   // ����稬 ���ਯ�� ���筨��
	{   
	 if (hsb == hSBNlayers) // �� ������� �ப��⪨ �᫠ ᫮��
	 {
	   if(wParam == SB_LINEUP && Prof.vez.model.n
	      > 0 ) Prof.vez.model.n -= 1;
	   if(wParam == SB_LINEDOWN && Prof.vez.model.n
	      < MAX_LAYERS ) Prof.vez.model.n += 1;
		sprintf(temp,"%d", Prof.vez.model.n );
		// �������� �࣠�� �ࠢ����� ᮯ�⨢����ﬨ ᫮��
		SetDlgItemText(hDlg, IDC_EB_NLAYERS, temp);
		// ��⠭���� ��������� �p����� �p������� 
		// ᮯp�⨢����ﬨ � ��魮��ﬨ ᫮��
//              SetControlsVisib( phSBRes, MAX_LAYERS, Prof.vez.model.n );
//              SetControlsVisib( phSBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);
//              SetControlsVisib( phEBRes, MAX_LAYERS, Prof.vez.model.n );
//              SetControlsVisib( phEBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);
		SetVESControls( hDlg ); // ��⠭���� 㯠����騥 �p����
	 }
	 i = _IsHandler( phSBRes, MAX_LAYERS, hsb ); // �஢�ਬ
	  if ( i >= 0 )
	   {  // �� ������� �ப��⪨ ᮯ�⨢�����, i - ����� ᫮� 
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
	     // �������� �࣠�� �ࠢ����� ᮯ�⨢����ﬨ ᫮��
	     SetDlgItemText(hDlg, IDC_EB_RESIS1 + i, temp);
	     /* ��⠭���� ��������� 㪠��⥫� ������ �ப��⪨. */
	     SetScrollPos(phSBRes[i], SB_CTL, res_pos, TRUE);
	  }
	  
	  i = _IsHandler( phSBThick, MAX_LAYERS-1, hsb );
	  if ( i >= 0 )
	    {  // �� ������� �ப��⪨ ��魮�⥩, i - ����� ᫮� 
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
	     // �������� �࣠�� �ࠢ����� ��魮��ﬨ ᫮��
	     SetDlgItemText(hDlg, IDC_EB_THICK1 + i, temp);
	     /* ��⠭���� ��������� 㪠��⥫� ������ �ப��⪨. */
	     SetScrollPos(phSBThick[i], SB_CTL, thick_pos, TRUE);
	   }
	 }    /* end if(hsb = ... )  */
       }      /* end case WM_HSCROLL */
       return TRUE;

    case WM_COMMAND:   /* ����饭��, ����㯨�訥 �� ������. */
     {
      WORD wNotif;  // ��� ᮮ�饭��
      int n;     // �ᯮ���. ��६����
      float v;
      int  i;

      wNotif = HIWORD( lParam );        // ��� ᮮ�饭��

       switch(wParam)  {
	  case IDC_EB_NLAYERS:
	    /* ��ப�-।���� �᫠ ᫮�� ������ */
	    if ( wNotif == EN_KILLFOCUS ) // ����� 䮪�� �����
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
	       // ��⠭���� ��������� �p����� �p������� 
	       // ᮯp�⨢����ﬨ � ��魮��ﬨ ᫮��
	       SetControlsVisib( phSBRes, MAX_LAYERS, Prof.vez.model.n );
	       SetControlsVisib( phSBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);
	       SetControlsVisib( phEBRes, MAX_LAYERS, Prof.vez.model.n );
	       SetControlsVisib( phEBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);
	      }
	      
	      break;

	  case IDC_EB_RESIS1:  // ���� ।���஢���� ᮯ�⨢����� ᫮��
	  case IDC_EB_RESIS2: 
	  case IDC_EB_RESIS3:
	  case IDC_EB_RESIS4:
	  case IDC_EB_RESIS5:
	  case IDC_EB_RESIS6:
	    if ( wNotif == EN_KILLFOCUS ) // ����� 䮪�� �����
	     {
	       i = wParam - IDC_EB_RESIS1; // ����� ᫮�
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
	    if ( wNotif == EN_KILLFOCUS ) // ����� 䮪�� �����
	     {
	       i = wParam - IDC_EB_THICK1; // ����� ᫮�
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
	       /* ���짮��⥫� ����� ������ "Next". */
		 DoMenuCurveNext( hFrame, 0, 0, 0 );
		 SetVESControls( hDlg ); // ���樠�����㥬 �࣠�� �ࠢ�����
		break;
		
		case IDC_BU_PREV :
	       /* ���짮��⥫� ����� ������ "Prev". */
		 DoMenuCurvePrev( hFrame, 0, 0, 0 );
		 SetVESControls( hDlg ); // ���樠�����㥬 �࣠�� �ࠢ�����
		break;
		
		case IDC_BU_SAVE :
	       /* ���짮��⥫� ����� ������ "Save". */
		 DoMenuCurveSave( hDlg, 0, 0, 0 );
		break;
		
		case IDCANCEL:
	       /* ���짮��⥫� ����� ������ "Cancel". */
		      EndDialog(hDlg,TRUE);
		break;

		case IDOK:          /*  save current settings  */
	       /* ���짮��⥫� ����� ������ "OK". */
		    if (Prof.vez.model.n == 0) return TRUE;

		    SetCursor( hHourGlassCursor ); // ����� - ��������
		    // �맮��� ��楤��� ������樨 �ਢ��
		    if ( InterprMode == AUTO ) 
		    {
		      AutoInterpr( &(Prof.vez), 0.01, MAX_ITERATION );
		      SetVESControls(hDlg); // �����⠭���� ���� �������
		    }
		    else
		      solve_type_curve( &(Prof.vez) );

		    SetCursor( hNormalCursor );
		    InvalidateRect(hFrame,NULL,TRUE); // �����㥬 ��䨪
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
   InitInterprDlg �㭪�� ���樠����樨 �ࠢ����� ������⮢
   ����������� ���� "Interpr".
 ------------------------------------------------------------ */
void InitInterprDlg(HWND hDlg)
{
HWND hwnd;
char temp[12];
int i;

 svez = Prof.vez; // ���࠭�� �����
//SendMessage( hDlg, WM_SETFONT, hFont, TRUE );
    
 hCBInterpr = GetDlgItem( hDlg, IDC_CB_INTERPR );

 switch ( InterprMode )  {
  case AUTO   : 
		     // ��⠭���� ��४���⥫� ०��� �����.
//   if (! SendMessage( hCBInterpr, BM_GETCHECK, 0, 0L ))
   SendMessage( hCBInterpr, BM_SETCHECK, TRUE, 0L );
		     //  ��������� ����������� ����
   SetWindowText( hDlg, "Model Data : Automatic Interpretation");
   break;
  
  case MANUAL :
   
   SendMessage( hCBInterpr, BM_SETCHECK, FALSE, 0L );
   
   SetWindowText( hDlg, "Model Data : Manual Interpretation");
   break;
 }
    
    
//    if ( InterprMode == AUTO )   // ��������� ����������� ����
//     {
//      SendMessage( GetDlgItem(), BM_SETCHECK, TRUE, 0L );
//      if (! SendMessage( hCBInterpr, BM_GETCHECK, TRUE, 0L ))
	      ;
//      SetWindowText( hDlg, "Model Data : Automatic Interpretation");
//     }
//    else
//      SetWindowText( hDlg, "Model Data : Manual Interpretation");

    // ��।���� ���ਯ�� ������� �ப��⪨ �᫠ ᫮��
    hSBNlayers = GetDlgItem( hDlg, IDC_SB_NLAYERS );
    
    for ( i = 0; i < MAX_LAYERS ; i ++ )
    {
      /* ��।������ �����䨪��஢ ���� ������ �ப��⪨. */
      phSBRes[i] = GetDlgItem(hDlg, IDC_SB_RESIS1 + i );
      /* ��।������ �����䨪��஢ ���� p�����p������ */
      phEBRes[i] = GetDlgItem(hDlg, IDC_EB_RESIS1 + i );
      /* ��⠭���� ���������� ������ �ப��⪨. */
      SetScrollRange(phSBRes[i],SB_CTL,(int)log10(MIN_RESIST),(int)log10(MAX_RESIST),TRUE);
// SendMessage( phEBRes[i], WM_SETFONT, hFont, TRUE );
//      SetScrollRange(phSBRes[i],SB_CTL,0,4,TRUE);
    }
    for ( i = 0; i < MAX_LAYERS - 1; i ++ )
    {
      /* ��।������ �����䨪��஢ ���� ������ �ப��⪨. */
      phSBThick[i] = GetDlgItem( hDlg, IDC_SB_THICK1 + i );
      /* ��।������ �����䨪��஢ ���� p�����p������ */
      phEBThick[i] = GetDlgItem( hDlg, IDC_EB_THICK1 + i );
      /* ��⠭���� ���������� ������ �ப��⪨. */
      SetScrollRange(phSBThick[i],SB_CTL,log10(MIN_THICK),log10(MAX_THICK),TRUE);
    }
    
    // ��⠭���� ��������� �p����� �p������� ᮯp��. � ��魮��ﬨ ᫮��
//    SetControlsVisib( phSBRes, MAX_LAYERS, Prof.vez.model.n );
//    SetControlsVisib( phSBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);
//    SetControlsVisib( phEBRes, MAX_LAYERS, Prof.vez.model.n );
//    SetControlsVisib( phEBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);

    SetVESControls( hDlg ); // ���樠�����㥬 �࣠�� �ࠢ�����
}

/* ----------------------------------------------------------------------
   _IsHandler �㭪�� ��ᬠ�ਢ��� ���ᨢ ���ਯ�஢ pHandle ������
   len �� �।��� �����㦥��� � ��� ���ਯ�� handle. �᫨ �� �����㦥�,
   �����頥��� ��� ���浪��� ����� � ���ᨢ� ( �� 0).
   �᫨ ���, �����頥��� -1
 ---------------------------------------------------------------------- */
int _IsHandler( HANDLE *pHandle, int len, int handle )
{
int i;
for ( i = 0; i < len; i ++ ) if ( pHandle[i] == handle ) return i;
return -1;
}

/* -----------------------------------------------------------------------
    SetControlsVisib
    �㭪�� ��⠭�������� ��������� ������⮢ �p�������, ���p���p�
    ���p�� ��室���� � ���ᨢ� phCtrl. ��p�� n ������⮢ �⠭������
    �����묨, ��⠫�� �������묨(������㯭묨). hSize - ������⢮
    ������⮢ � ���ᨢ� phCtrl.
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
   SetVESControls �㭪�� ��⠭�������� �࣠�� �ࠢ�����
   � ���� ������� ������樨 �ਢ�� ��� � �����䨪��஬
   hDlg, �ᯮ������� ������� �������� ��६����.
 ------------------------------------------------------------ */
void SetVESControls(HWND hDlg)
{
HWND hwnd;
char temp[12];
int i;
    
    /* �뢮� ������ � ���� ।���஢����. */
    sprintf(temp,"%d", Prof.vez.model.n);
    SetDlgItemText(hDlg, IDC_EB_NLAYERS, temp );
    SetDlgItemText(hDlg, IDT_CURVE_ID, Prof.vez.ID_curve );

    // ��⠭���� ��������� �p����� �p������� ᮯp��. � ��魮��ﬨ ᫮��
    SetControlsVisib( phSBRes, MAX_LAYERS, Prof.vez.model.n );
    SetControlsVisib( phSBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);
    SetControlsVisib( phEBRes, MAX_LAYERS, Prof.vez.model.n );
    SetControlsVisib( phEBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);

    for ( i = 0; i < Prof.vez.model.n ; i ++ )
    {
      // �뢮��� ���祭�� � ���� ।���஢����
      sprintf(temp,"%.1f", Prof.vez.model.ro[i] );
      SetDlgItemText(hDlg, IDC_EB_RESIS1 + i, temp );
//      /* ��⠭���� ���������� ������ �ப��⪨. */
//      SetScrollRange(phSBRes[i],SB_CTL,(int)log10(MIN_RESIST),(int)log10(MAX_RESIST),TRUE);
      /* ��⠭���� ��������� 㪠��⥫�� ������ �ப��⪨. */
      SetScrollPos(phSBRes[i],SB_CTL,(int)log10(Prof.vez.model.ro[i]),TRUE);
    }
    for ( i = 0; i < Prof.vez.model.n - 1; i ++ )
    {
      // �뢮��� ���祭�� � ���� ।���஢����
      sprintf(temp,"%.1f", Prof.vez.model.h[i] );
      SetDlgItemText(hDlg, IDC_EB_THICK1 + i, temp );
//      /* ��⠭���� ���������� ������ �ப��⪨. */
//      SetScrollRange(phSBThick[i],SB_CTL,log10(MIN_THICK),log10(MAX_THICK),TRUE);
      /* ��⠭���� ��������� 㪠��⥫�� ������ �ப��⪨. */
      SetScrollPos(phSBThick[i],SB_CTL,(int)log10(Prof.vez.model.h[i]),TRUE);
    }
}

///* -------------------------------------------------------------------
//   get_step �����頥� 蠣 ��������� ��ࠬ���, ������騩 �� ����稭� 
//   �⮣� ��ࠬ���
//   val - ���祭�� ��ࠬ���
//----------------------------------------------------------------------*/
//float get_step( float val )
//{
//float rez;

//rez = pow( 10, floor( log10( val )));
//return rez;
//}
