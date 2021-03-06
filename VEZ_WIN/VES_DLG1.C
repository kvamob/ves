// ���� ves_dlg1.c : ���� �஥�� VES for Windows
// �㭪樨 ��ࠡ�⪨ ����������� ���� �襭�� ��אַ� ����� ���

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

/* ------------ �������� ��६���� --------------------*/
extern HANDLE hFont;
extern HPEN   hRedPen;
extern HANDLE hNormalCursor, hHourGlassCursor;
extern HWND   hFrame;
// extern char szTemp[]; // ���� ��� �࠭���� ����� 䠩��
MODEL_TC   model;


//_________________________________________________________________
//_   �������� ��६����, �ᯮ��㥬� �㭪�ﬨ, �易��묨   _
//_             � ��������� ����� "VESTypeCurve".                   _
//_________________________________________________________________

static  phEBRes[MAX_LAYERS_TC],  // ���ᨢ ���ਯ�஢ ���� ।���஢����
				 // ᮯ�⨢����� ᫮��
	phEBThick[MAX_LAYERS_TC-1]; // ���ᨢ ���ਯ�஢ ���� ।���஢����
					 // ��魮�⥩ ᫮��

static HWND hSBNlayers;      // ���ਯ�� ������� �ப��⪨ �᫠ ᫮��

static HDC hDC;

//static VEZ svez; // �������, ��� �࠭���� ����� �� �६� ࠡ���
		 // � ��������� �����

/* ------------------------------------------------------------
	VesInterprDlg �㭪�� �ࠢ����� ��������� �����
	"Interpr".
 ------------------------------------------------------------- */
BOOL FAR PASCAL VesTypeCurveDlg(HWND hDlg, unsigned message, WORD wParam,
				 LONG lParam)
{
HWND hwnd;

RECT  r1;
RECT  r2;
int   x,y;
int   bh;               // ���� ��������� ���� � ���ᥫ��


char temp[12];          // �ᯮ���. ����

int   i;

float first_absc;        // ������ ��ࢮ� �窨 ⥮���᪮� �ਢ��

//int res_pos, thick_pos; // ��������� ������� ����� �ப��⪨
			// ᮯ�⨢����� � ��魮�⥩ ᫮��

switch(message)
    {
		case WM_INITDIALOG:
/* ���樠������ �ࠢ����� ���� ����������� ����. */
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
   /* ����饭�� ��ਧ��⠫��� ������ �ப��⪨. */
    {
      HWND hsb;       // ���ਯ�� ������ �ப��⪨

   /* ��।������ ���筨�� ᮮ�饭�� WM_HSCROLL. */
	if( hsb = HIWORD(lParam) )   // ����稬 ���ਯ�� ���筨��
	{
	 if (hsb == hSBNlayers) // �� ������� �ப��⪨ �᫠ ᫮��
	 {
	   if(wParam == SB_LINEUP && model.n > 1 ) model.n -= 1;
	   if(wParam == SB_LINEDOWN && model.n < MAX_LAYERS_TC ) model.n += 1;
	   sprintf(temp,"%d", model.n );
	   // �������� �࣠�� �ࠢ����� ᮯ�⨢����ﬨ ᫮��
	    SetDlgItemText(hDlg, IDC_EB_NLAYERS_TC, temp);
	   // ��⠭���� ��������� �p����� �p������� 
	   // ᮯp�⨢����ﬨ � ��魮��ﬨ ᫮��
	    SetVTCControls( hDlg ); // ��⠭���� 㯠����騥 �p����
	 }
//         i = _IsHandler( phSBRes, MAX_LAYERS_TC, hsb ); // �஢�ਬ
//          if ( i >= 0 )
//           {  // �� ������� �ப��⪨ ᮯ�⨢�����, i - ����� ᫮� 
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
//             // �������� �࣠�� �ࠢ����� ᮯ�⨢����ﬨ ᫮��
//             SetDlgItemText(hDlg, IDC_EB_RESIS1 + i, temp);
//             /* ��⠭���� ��������� 㪠��⥫� ������ �ப��⪨. */
//             SetScrollPos(phSBRes[i], SB_CTL, res_pos, TRUE);
//            }
	  
//          i = _IsHandler( phSBThick, MAX_LAYERS_TC-1, hsb );
//          if ( i >= 0 )
//            {  // �� ������� �ப��⪨ ��魮�⥩, i - ����� ᫮� 
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
//             // �������� �࣠�� �ࠢ����� ��魮��ﬨ ᫮��
//             SetDlgItemText(hDlg, IDC_EB_THICK1 + i, temp);
//             /* ��⠭���� ��������� 㪠��⥫� ������ �ப��⪨. */
//             SetScrollPos(phSBThick[i], SB_CTL, thick_pos, TRUE);
//           }
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
	  case IDC_EB_NLAYERS_TC:
	    /* ��ப�-।���� �᫠ ᫮�� ������ */
	    if ( wNotif == EN_KILLFOCUS ) // ����� 䮪�� �����
	     {
	       GetDlgItemText(hDlg, IDC_EB_NLAYERS_TC, (LPSTR) temp, 11 );
	       sscanf( temp,"%d", &n );
			 if ( n < 1 ) n = 1;
	       if ( n > MAX_LAYERS_TC ) n = MAX_LAYERS_TC;
	       model.n = n;
	       sprintf( temp,"%d", n );
	       SetDlgItemText(hDlg, wParam, (LPSTR)temp);
	       // <><><<><><><><><><><><><><><
	       // ��⠭���� ��������� �p����� �p������� 
	       // ᮯp�⨢����ﬨ � ��魮��ﬨ ᫮��
//               SetVTCControlsVisib( phSBRes, MAX_LAYERS_TC, model.n );
//               SetVTCControlsVisib( phSBThick, MAX_LAYERS_TC - 1, model.n - 1);
		 SetVTCControlsVisib( phEBRes, MAX_LAYERS_TC, model.n );
		 SetVTCControlsVisib( phEBThick, MAX_LAYERS_TC - 1, model.n - 1);
	      }
	      
	  break;

	  case IDC_R1:  // ���� ।���஢���� ᮯ�⨢����� ᫮��
	  case IDC_R2: 
	  case IDC_R3:
	  case IDC_R4:
	  case IDC_R5:
	  case IDC_R6:
	  case IDC_R7:
	  case IDC_R8:
	    if ( wNotif == EN_KILLFOCUS ) // ����� 䮪�� �����
	     {
	       i = wParam - IDC_R1; // ����� ᫮�
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
	    if ( wNotif == EN_KILLFOCUS ) // ����� 䮪�� �����
	     {
	       i = wParam - IDC_EB_THICK1; // ����� ᫮�
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
	       /* ���짮��⥫� ����� ������ "Cancel". */
		      EndDialog(hDlg,TRUE);
		break;

		case IDOK:          /*  save current settings  */
	       /* ���짮��⥫� ����� ������ "OK". */
//                    if (Prof.vez.model.n == 0) return TRUE;
//
//                    SetCursor( hHourGlassCursor ); // ����� - ��������
//                    // �맮��� ��楤��� ������樨 �ਢ��
//                    if ( InterprMode == AUTO ) 
//                    {
//                      AutoInterpr( &(Prof.vez), 0.01, MAX_ITERATION );
//                      SetVESControls(hDlg); // �����⠭���� ���� �������
//                    }
//                   else
//                      solve_type_curve( &(Prof.vez) );
//
//                    SetCursor( hNormalCursor );
//                    InvalidateRect(hFrame,NULL,TRUE); // �����㥬 ��䨪
//                    UpdateWindow(hFrame);

//////////////////////////////////////////////////////////////
hDC = GetDC( hDlg );

GetWindowRect( hDlg, &r1);
GetWindowRect( GetDlgItem( hDlg, IDC_FRAME ), &r2 );
bh = GetSystemMetrics( SM_CYCAPTION );  // ���� ��������� ����

x = r2.left - r1.left - 1;
y = r2.top - r1.top - bh  - 1;


SetROP2( hDC, R2_NOTXORPEN );
SelectObject( hDC, hRedPen);  // �p�᭮� ��p�

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
   InitVesTypeCurveDlg �㭪�� ���樠����樨 �ࠢ�����
   ������⮢ ����������� ���� "TypeCurve" (���� �ਢ. ���)
 ------------------------------------------------------------ */
void InitVesTypeCurveDlg(HWND hDlg)
{
HWND hwnd;
char temp[12];
int i;

// svez = Prof.vez; // ���࠭�� �����

model.n = 1;

// ��।���� ���ਯ�� ������� �ப��⪨ �᫠ ᫮��
hSBNlayers = GetDlgItem( hDlg, IDC_SB_NLAYERS_TC );
    
for ( i = 0; i < MAX_LAYERS_TC ; i ++ )
 {
//  /* ��।������ �����䨪��஢ ���� ������ �ப��⪨. */
//   phSBRes[i] = GetDlgItem(hDlg, IDC_SB_RESIS1 + i );

  /* ��।������ �����䨪��஢ ���� p�����p������ */
  phEBRes[i] = GetDlgItem(hDlg, IDC_R1 + i );

//  /* ��⠭���� ���������� ������ �ப��⪨. */
//      SetScrollRange(phSBRes[i],SB_CTL,(int)log10(MIN_RESIST),(int)log10(MAX_RESIST),TRUE);
// SendMessage( phEBRes[i], WM_SETFONT, hFont, TRUE );
//      SetScrollRange(phSBRes[i],SB_CTL,0,4,TRUE);

 }

for ( i = 0; i < MAX_LAYERS_TC - 1; i ++ )
 {
//     /* ��।������ �����䨪��஢ ���� ������ �ப��⪨. */
//     phSBThick[i] = GetDlgItem( hDlg, IDC_SB_THICK1 + i );
//      /* ��।������ �����䨪��஢ ���� p�����p������ */

      phEBThick[i] = GetDlgItem( hDlg, IDC_H1 + i );
      /* ��⠭���� ���������� ������ �ப��⪨. */
//      SetScrollRange(phSBThick[i],SB_CTL,log10(MIN_THICK),log10(MAX_THICK),TRUE);
  }
    
    // ��⠭���� ��������� �p����� �p������� ᮯp��. � ��魮��ﬨ ᫮��
//    SetControlsVisib( phSBRes, MAX_LAYERS, Prof.vez.model.n );
//    SetControlsVisib( phSBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);

    SetVTCControlsVisib( phEBRes, MAX_LAYERS_TC, model.n );
    SetVTCControlsVisib( phEBThick, MAX_LAYERS_TC - 1, model.n - 1);

    SetVTCControls( hDlg ); // ���樠�����㥬 �࣠�� �ࠢ�����
}

/* ----------------------------------------------------------------------
   _IsHandler �㭪�� ��ᬠ�ਢ��� ���ᨢ ���ਯ�஢ pHandle ������
   len �� �।��� �����㦥��� � ��� ���ਯ�� handle. �᫨ �� �����㦥�,
   �����頥��� ��� ���浪��� ����� � ���ᨢ� ( �� 0).
   �᫨ ���, �����頥��� -1
 ---------------------------------------------------------------------- */
//int _IsHandler( HANDLE *pHandle, int len, int handle )
//{
//int i;
//for ( i = 0; i < len; i ++ ) if ( pHandle[i] == handle ) return i;
//return -1;
//}

/* -----------------------------------------------------------------------
   SetVTCControlsVisib
   �㭪�� ��⠭�������� ��������� ������⮢ �p�������, ���p���p�
   ���p�� ��室���� � ���ᨢ� phCtrl. ��p�� n ������⮢ �⠭������
   �����묨, ��⠫�� �������묨(������㯭묨). hSize - ������⢮
   ������⮢ � ���ᨢ� phCtrl.
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
	SetVTCControls �㭪�� ��⠭�������� �࣠�� �ࠢ�����
	� ���� ������� ���� �ਢ�� ��� � �����䨪��஬
	hDlg, �ᯮ������� ������� �������� ��६����.
 ------------------------------------------------------------ */
void SetVTCControls(HWND hDlg)
{
HWND hwnd;
char temp[12];
int i;

	 /* �뢮� ������ � ���� ।���஢����. */
	 sprintf(temp,"%d", model.n);
	 SetDlgItemText(hDlg, IDC_EB_NLAYERS_TC, temp );
//    SetDlgItemText(hDlg, IDT_CURVE_ID, Prof.vez.ID_curve );

	 // ��⠭���� ��������� �p����� �p������� ᮯp��. � ��魮��ﬨ ᫮��
//    SetControlsVisib( phSBRes, MAX_LAYERS, Prof.vez.model.n );
//    SetControlsVisib( phSBThick, MAX_LAYERS - 1, Prof.vez.model.n - 1);
	 SetVTCControlsVisib( phEBRes, MAX_LAYERS_TC, model.n );
	 SetVTCControlsVisib( phEBThick, MAX_LAYERS_TC - 1, model.n - 1);

	 for ( i = 0; i < model.n ; i ++ )
	 {
		// �뢮��� ���祭�� � ���� ।���஢����
		sprintf(temp,"%.1f", model.ro[i] );
		SetDlgItemText(hDlg, IDC_EB_RESIS1 + i, temp );
//      /* ��⠭���� ��������� 㪠��⥫�� ������ �ப��⪨. */
//      SetScrollPos(phSBRes[i],SB_CTL,(int)log10(Prof.vez.model.ro[i]),TRUE);
	 }
	 for ( i = 0; i < model.n - 1; i ++ )
	 {
		// �뢮��� ���祭�� � ���� ।���஢����
		sprintf(temp,"%.1f", model.h[i] );
		SetDlgItemText(hDlg, IDC_EB_THICK1 + i, temp );
//      /* ��⠭���� ��������� 㪠��⥫�� ������ �ப��⪨. */
//      SetScrollPos(phSBThick[i],SB_CTL,(int)log10(Prof.vez.model.h[i]),TRUE);
	 }
}



