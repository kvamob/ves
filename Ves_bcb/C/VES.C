/*   ���� ves.c   �������� ����� �p����� ves
_________________________________________________________________________
 ��������� ����p�p������ �p���� ��� : / VES for Windows v1.0b /
 ��������� ������������� ��� ����������� ������� Windows v3.1 �
 �������������� ���������:
   commdlg.dll
   ctl3dv2.lib (using ctl3dv2.dll)


 (c) 1995 �.��������
 Compiler : Borland C++ 3.1  Borland C++ 4.5
 Project  :
 model    : MEDIUM
 ������������� �������� 22.02.96
________________________________________________________________________
*/

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <io.h>
#include <stdlib.h>
#include <commdlg.h>
#include "ctl3d.h"

#define  NOSOUND          // ��. ������ ����� windows.h
#define  NOCOMM
#define  NODRIVERS
#define  NOPROFILER
#define  NOKEYBOARDINFO
#define  NOMETAFILE

#include "ves.h"
#include "ves_rc.h"

#define dim(x) sizeof(x)/sizeof(x[0])     // C������� ���������� ���������
#define FILENAMESIZE 256       // ����. ����� ����� �����

/*-------------------- [ ��������� ��H���� ]-----------------------------*/

int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance,
		   LPSTR lpszCmdLine, int cmdShow);
BOOL InitApplication(HANDLE hInstance) ;
BOOL InitInstance(HANDLE hInstance, WORD nCmdShow);
BOOL TermInstance(HANDLE hInstance);
LONG FAR PASCAL FrameWndProc(HWND hwnd, WORD wMsg,
			     WORD wParam, LONG lParam);
LONG FAR PASCAL ProgressWndProc(HWND hWnd, WORD wMsg,
			     WORD wParam, LONG lParam);

LONG DoCreate(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
LONG DoDestroy(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
LONG DoCommand(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
LONG DoLButtonDown(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
LONG DoRButtonDown(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
LONG DoPaint(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
//LONG DoSize(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
LONG DoMenuOpen(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
LONG DoMenuExit(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
LONG DoInitMenu(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
LONG DoMenuHelpIndex(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
LONG DoMenuUsingHelp(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
LONG DoMenuAbout(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
LONG DoMenuInterpAuto(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
LONG DoMenuInterpMan(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);

LONG DoMenuCurveNext(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
LONG DoMenuCurvePrev(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
LONG DoMenuCurveLast(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
LONG DoMenuCurveFirst(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
LONG DoMenuCurveSave(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);
LONG DoMenuInfo(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);

LONG DoMenuComputeCurve(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam);

VOID PaintVES( HWND hWnd );
VOID OutInfo( HWND hWnd, HDC hDC );

// ���� ves_io.c
extern int OpenProfil( char *fname, PROFIL *prof );
extern int WriteProfilHeader( char *fname, PROFIL *prof );
extern int ReadCurve( HWND hWnd, char *fname, VEZ *vez , int cnt );
extern int WriteCurve( HWND hWnd, char *fname, VEZ *vez , int cnt );
extern void CloseProfil( PROFIL *prof );
// ���� ves_gr.c
extern void PlotInitialize( HWND hWnd, HDC hDC, VES_PAINTDATA *plot,
			    PROFIL *prof );
extern void DrawLogBlank( HDC hDC, VES_PAINTDATA *plot, VEZ *vez );
extern void DrawCurve( HDC hDC, VES_PAINTDATA *plot );
//extern void DrawMarker_( HDC hDC, int x, int y );
extern void EditCurveByMouse( HWND hWnd, PROFIL *prof, VES_PAINTDATA *plot,
		       POINT pt );


extern BOOL FAR PASCAL AboutDlg(HWND hDlg, unsigned message, WORD wParam,
			 LONG lParam);
extern BOOL FAR PASCAL VesInterprDlg(HWND hDlg, unsigned message, WORD wParam,
			    LONG lParam);
extern BOOL FAR PASCAL InfoDlg(HWND hDlg, unsigned message, WORD wParam,
			 LONG lParam);
extern BOOL FAR PASCAL VesTypeCurveDlg(HWND hDlg, unsigned message, WORD wParam,
				 LONG lParam);


/* ------------------ �������H�� ������HH�� --------------------- */
HANDLE  hinstance;             // ������������p ��������p� ������
HWND    hFrame;                // ������������p �������� ���� (����-p����)
HWND    hProgress;             // ������������p �������. ����
HWND    hwndPlot;              // ������������p ���� � p�������
int     xScreen, yScreen;      // ������ � ������ ������ � ��������
int     nCapHgh;               // ������ ��������� ���� - ��� ��������� ��������
			       // ���������������� ����
int     yBord;                 // ������� ����� ���� �� ���������

char szFileNameBin[FILENAMESIZE+1]; // ��� �������� ��������� ����� VEZ-�������
char szTemp[FILENAMESIZE+1];        // ����� ��� �������� ����� �����

HANDLE  hIconVES;      // ������ VES
int     hVEZBinFile;   // ����p����p ��������� ����� ��p���� VEZ
int     nProfilOpen=0; // ������� �������� ����� ������� (1 - ������, 0 - ���
int     EditCurve = 0; // �p����� p������p������ �p����

PROFIL  Prof;          // ������� ���
VES_PAINTDATA Plot;    // ������ ��� ����p����� �p������
int     InterprMode;   // ����� ������������� - ������ ��� ���������.

HPEN hBlackPen,        // ��p� ���p������ � Windows
     hWhitePen,
     hDarkPen,         // ����� ��� ���������� � ���������� �����
     hLightPen,
     hBluePen,         // ��� p�������� ����������� �p����
     hRedPen;          // ��� p�������� ���p��������� �p����

HANDLE hFont;          // ���������� ������
HANDLE hAccel;         // ���������� ����������

char szShortAppName[]  = "VES"; // �p����� ��� �p��������
char szAppName[]       = "Vertical Electric Sounding"; // ������ ���
char szMenuName[]      = "MENU_VES"; // ��� p���p�� ����
char szDefName[]       = "Untitled"; // ��� ����� �� ���������
char szDefExt[]        = "ves";      // p����p���� ����� �� ���������
char szHelpText[] = "Sorry but Help system is not available\n"\
"in Beta-version of this Application";
char szCaption[100];         // ����� ��� ��������� �������� ����

char *szFilter[] =  {   // �����p� ��� ������p����  ��������
"Bynary VES files (*.VES)", "*.VES",
"Text   VES files (*.VEZ)", "*.VEZ",
"All files (*.*)", "*.*",
""};

HCURSOR hNormalCursor, hHourGlassCursor; // ������������p� ��p��p��

struct decodeWord { // C�p����p�, ����������� ������������p�
   WORD Code;       // ��������� ��� ���� � ���������
   LONG (*Fxn) (HWND, WORD, WORD, LONG );
   };

// ������� ��p����������� �������� FrameWndProc ���������,
// ����������� �p� p����� � ������ � �������, ���������������
// ������� �� ���
struct decodeWord messages[] = {
 WM_CREATE,   DoCreate,
 WM_INITMENU, DoInitMenu,
 WM_LBUTTONDOWN, DoLButtonDown,
 WM_RBUTTONDOWN,   DoRButtonDown,
 WM_PAINT,    DoPaint,
// WM_SIZE,     DoSize,
 WM_DESTROY,  DoDestroy,
 WM_COMMAND,  DoCommand
};

//typedef CHDATA NEAR *NPCHDATA;
//LOCALHANDLE    hChData;           // ���������� ��������� ������ � ������
//NPCHDATA       npChData;          // ��������� �� ��������� ������

//
// ������� ������������p�� ������� ���� � ��������������� �� �������
//
struct decodeWord menuitems[] = {
// IDM_NEW,     DoMenuNew,
 IDM_OPEN,    DoMenuOpen,
// IDM_SAVE,    DoMenuSave,
// IDM_SAVE_AS, DoMenuSaveAs,
 IDM_EXIT,    DoMenuExit,

 IDM_NEXT,    DoMenuCurveNext,
 IDM_PREV,    DoMenuCurvePrev,
 IDM_LAST,    DoMenuCurveLast,
 IDM_FIRST,    DoMenuCurveFirst,
 IDM_SAVECURVE,DoMenuCurveSave,
 IDM_INFO,    DoMenuInfo,

 IDM_MANUAL,  DoMenuInterpMan,
 IDM_AUTO,    DoMenuInterpAuto,

// IDM_COMPILE, DoMenuCompile,
 IDM_COMPUTE_TYPE_CURVE, DoMenuComputeCurve,

 IDM_HELP,    DoMenuHelpIndex,
 IDM_USING_HELP, DoMenuUsingHelp,
 IDM_ABOUT,   DoMenuAbout
};


/*-----------------------------------------------------------
		 WinMain ������ ��������� VES.
------------------------------------------------------------- */
int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow)
{
MSG msg;

hinstance = hInstance; // �������� ������������p ��������
				 // ��������p� �p��������
if( !hPrevInstance)     // ���� ��� ��p��� ��������p, ��p�����p. ����� ����
	if (!InitApplication(hinstance)) return FALSE;

hHourGlassCursor = LoadCursor(NULL, IDC_WAIT); // ��p��p-�����.����

hAccel = LoadAccelerators(hinstance, "ACCEL_1"); // �������� �����������

if( !InitInstance(hInstance, nCmdShow))  // C������ ���� ����� ��������p�
	 return FALSE;

Ctl3dRegister(hInstance);
Ctl3dAutoSubclass( hInstance );

while(GetMessage(&msg, NULL, 0, 0)) // �������� ���� ��������� ���������
	{
	  if ( !TranslateAccelerator(hFrame,hAccel,&msg))
	  {
	 TranslateMessage(&msg);
	 DispatchMessage(&msg);
		}
	}

Ctl3dUnregister(hInstance);

//TermInstance(hInstance);  // "���������" � ���� ��������p��
return (msg.wParam);      // �������� �p� ����p��� = WM_QUIT

}

/* --------------------------------------------------------------
	InitApplication ��� ����� ������������� ��� ������ �p��p����
-----------------------------------------------------------------*/
BOOL InitApplication(HANDLE hInstance)
{
WNDCLASS wc;
	 /* ����������� ������ �������� ����. */
 wc.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;  // C���� ������
 wc.lpfnWndProc   = FrameWndProc;    // �p������������ ������� ������
 wc.cbClsExtra    = 0;               // �������������� ������ ��� ������
 wc.cbWndExtra    = 0;               // �������������� ������ ��� ����
 wc.hInstance     = hInstance;       // ������������p ��������� ������
 wc.hIcon         = LoadIcon(hInstance,(LPSTR)"ICON_VES"); // ������ �� �����.
 wc.hCursor       = LoadCursor(NULL,IDC_ARROW);    // ��p��p �� �����.
// wc.hbrBackground = COLOR_APPWORKSPACE+1;          // ���� ���� �� �����.
// wc.hbrBackground = COLOR_WINDOW;          // ���� ���� �� �����.
 wc.hbrBackground = GetStockObject(LTGRAY_BRUSH); // ���� ���� �� �����.
 wc.lpszMenuName  = szMenuName;      // ��� p���p�� ����
 wc.lpszClassName = szShortAppName;  // ��� ������ ����

 hNormalCursor = wc.hCursor;
 hIconVES      = wc.hIcon;

 if ( !RegisterClass(&wc) ) return FALSE; // ��p�����p�p����� �����

  /* ����������� ������ ���������������� ����. */
 wc.style         = CS_OWNDC;        // C���� ������
 wc.lpfnWndProc   = ProgressWndProc; // �p������������ ������� ������
 wc.cbClsExtra    = 0;               // �������������� ������ ��� ������
 wc.cbWndExtra    = 0;               // �������������� ������ ��� ����
 wc.hInstance     = hInstance;       // ������������p ��������� ������
// wc.hIcon         = LoadIcon(hInstance,(LPSTR)"ICON_VES"); // ������ �� �����.
// wc.hCursor       = LoadCursor(NULL,IDC_ARROW);    // ��p��p �� �����.
// wc.hbrBackground = COLOR_APPWORKSPACE+1;          // ���� ���� �����
// wc.hbrBackground = COLOR_WINDOW;          // ���� ���� �� �����.
 wc.hbrBackground = GetStockObject(LTGRAY_BRUSH); // ���� ���� �� �����.

 wc.lpszMenuName  = NULL;      // ��� p���p�� ����
 wc.lpszClassName = "Progress";  // ��� ������ ����

 if ( !RegisterClass(&wc) ) return FALSE; // ��p�����p�p����� �����

 return TRUE; // ��p�����p�p����� �����
}

/* --------------------------------------------------------------
   InitInstance ��� ������������� ��������p� ������� �p��������
-----------------------------------------------------------------*/
BOOL InitInstance(HANDLE hInstance, WORD nCmdShow)
{
hFrame = CreateWindow(    // �������� �������� ���� ���������
	 szShortAppName,  // ��� ������ ����
	 szAppName,       // ����� ���������
	 WS_OVERLAPPEDWINDOW, // C���� ����
	 CW_USEDEFAULT, CW_USEDEFAULT, // ������� �� ���������
	 CW_USEDEFAULT, CW_USEDEFAULT, // p����p� �� ���������
	 NULL,     // ���� ��� �p����
	 NULL,     // �p������� ���� ������, �������. �� �����.
	 hInstance,// �������� ����
	 NULL );   // �������������� ���������
if(!hFrame) return FALSE;

ShowWindow(hFrame, nCmdShow); // C������ ������� ���� �������
UpdateWindow(hFrame);         // ������� �����. WM_PAINT

xScreen = GetSystemMetrics(SM_CXSCREEN); // ������� ������� ������
yScreen = GetSystemMetrics(SM_CYSCREEN);
yBord   = GetSystemMetrics(SM_CYBORDER); // ������� �����
nCapHgh = GetSystemMetrics(SM_CYCAPTION); // ������� ������ ���������

return TRUE;
}

/* --------------------------------------------------------------
   TermInstance ��� ���������� ��������p� ������� �p��������
-----------------------------------------------------------------*/
BOOL TermInstance(HANDLE hInstance)
{
return TRUE;
}

/* ---------------------------------------------------------------
   FrameWndProc ������� �������� ����. ������������ ��� ���������,
   ����������� � ����� �������� ���� ���������.
 ----------------------------------------------------------------*/
LONG FAR PASCAL FrameWndProc(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
int i;
for ( i = 0; i < dim(messages); i ++ ) // ������������ ��������� ���� �
   {                                   // ������� �����. �������
     if ( wMsg == messages[i].Code )
       return (( *messages[i].Fxn)(hWnd,wMsg,wParam,lParam));
   }
return (DefWindowProc(hWnd,wMsg,wParam,lParam));
}

/* ---------------------------------------------------------------
   DoCreate ������������ ��������� WM_CREATE
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoCreate(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
LOGFONT lf;  // C�p����p� ����������� �p����
HDC     hDC; // �������� ���p������
COLORREF _RED, _LTGRAY, _BLUE;

// C������� �p���
memset( &lf, 0, sizeof(LOGFONT));  // ������� lf
lf.lfHeight = 14;
lf.lfWidth = 6;
lf.lfWeight = 6;
//lf.lfUnderline = 1;
//lstrcpy((LPSTR)&lf.lfFaceName[0], (LPSTR)"Fixedsys");
lstrcpy((LPSTR)&lf.lfFaceName[0], (LPSTR)"MS Sans Serif");
//lstrcpy((LPSTR)&lf.lfFaceName[0], (LPSTR)"MS Serif");
hFont = CreateFontIndirect( &lf );

hDC = GetDC( hWnd );
_LTGRAY = GetNearestColor( hDC, RGB(192,192,192));
_BLUE =   GetNearestColor( hDC, RGB(0,0,255)^_LTGRAY);
_RED  =   GetNearestColor( hDC, RGB(255,0,0)^_LTGRAY);

hBlackPen = GetStockObject(BLACK_PEN); // ��p��� ��p� ���p���� � Windows
hWhitePen = GetStockObject(WHITE_PEN); // ��p��� ��p� ���p���� � Windows
hRedPen  = CreatePen( PS_SOLID, 2,_RED);  // �p����� ��p�
hBluePen = CreatePen( PS_SOLID, 2,_BLUE); // C���� ��p�
//hDarkPen  = CreatePen( PS_SOLID, 2,RGB(90,90,90));
hDarkPen  = CreatePen( PS_SOLID, 2,RGB(40,40,40));
hLightPen = CreatePen( PS_SOLID, 2,RGB(250,250,250));

 SelectObject( hDC, hFont );       // ���p���� �p���
 SetTextColor( hDC, RGB(0,0,0) );  // ��������� ���� ������
 SetBkMode( hDC, TRANSPARENT );    // �p��p����� ��� ������

ReleaseDC( hWnd, hDC );

return 0L;
}

/* ---------------------------------------------------------------
   DoDestroy ������������ ��������� WM_DESTROY
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoDestroy(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
DeleteObject(hFont);       // ��������� ������� GDI
DeleteObject(hRedPen);
DeleteObject(hBluePen);
DeleteObject(hDarkPen);
DeleteObject(hLightPen);

PostQuitMessage(0);
return 0L;
}

/* ---------------------------------------------------------------
   DoLButtonDown ������������ ��������� WM_LBUTTONDOWN
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoLButtonDown(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
POINT pt;

if ( !nProfilOpen ) return 0L;  // �p����� �� ���p�� - �����
 pt.x = LOWORD(lParam);  // ���p������ ����
 pt.y = HIWORD(lParam);
 EditCurveByMouse( hWnd, &Prof, &Plot, pt ); // ������� ������� ��������.
return 0L;
}

/* ---------------------------------------------------------------
   DoRButtonDown ������������ ��������� WM_RBUTTONDOWN
   ��� ������� ������ ������ ���� ���������� ����� ��������������
   ������
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoRButtonDown(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
POINT pt;

if ( !nProfilOpen ) return 0L;  // �p����� �� ���p�� - �����
 pt.x = 0;  // ������� ���p������ ����
 pt.y = 0;
 EditCurveByMouse( hWnd, &Prof, &Plot, pt ); // ������� ������� ��������.

return 0L;
}


/* ---------------------------------------------------------------
  DoPaint ������������ ��������� WM_PAINT ��� �������� ����,
  ������� ��������, ����� ���������� ������� UpdateWindow ���
  ����� ���������� ��������� �������� ����, ��� �������. ���
  ����������.
  ��� ���������� �������� ���� ������ ����������
  ������ ���� ��������������� ������ ���������� ���������.
 --------------------------------------------------------------- */
LONG DoPaint(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
#pragma argsused   // �������� �������������� � ���������. ���.
{

int nWidth; int nHeigh;  // ������� ����
RECT rect;

GetWindowRect(hWnd, &rect );      // ������� ������� ����
nWidth = rect.right - rect.left;
nHeigh = rect.bottom - rect.top;

if ( nWidth < 400 || nHeigh < 350 )  // �������� �� ���������� ���. ��������
 {
  nWidth = (nWidth < 400 ) ? 400 : nWidth;
  nHeigh = (nHeigh < 350 ) ? 350 : nHeigh;
             // ��������� ����� �������
  SetWindowPos( hWnd, NULL, 0, 0, nWidth, nHeigh, SWP_NOMOVE | SWP_NOZORDER );
 }

  InvalidateRect( hWnd, NULL, TRUE ); // �������� ��� ����
  PaintVES( hWnd );  // �������� � ����
  return 0L;
}

/* ---------------------------------------------------------------
   DoSize ������������ ��������� WM_SIZE ��� �������� ����,
   ������� ��������, ����� ����� ���������� ��������� ��������
   ����.
   ��� ���������� �������� ���� ������ ����������
   ������ ���� ��������������� ������ ���������� ���������.
 --------------------------------------------------------------- */
//LONG DoSize(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
//#pragma argsused   // �������� �������������� � ���������. ���.
//{
//int nWidth;  //
//int nHeigh;

//nWidth = LOWORD(lParam);
//nHeigh = HIWORD(lParam);
//if ( nWidth < 350 || nHeigh < 300 )
// {
//  nWidth = (nWidth < 350 ) ? 350 : nWidth;
//  nHeigh = (nHeigh < 300 ) ? 300 : nHeigh;
//  SetWindowPos( hWnd, NULL, 0, 0, nWidth, nHeigh, SWP_NOMOVE | SWP_NOZORDER );
// }

//  InvalidateRect( hWnd, NULL, TRUE ); // �������� ��� ����
//  PaintVES( hWnd );  // �������� � ����
//  return 0L;
//}


/* ---------------------------------------------------------------
	PaintVES ������ � ���� hWnd ���. �����, � ������ ���
--------------------------------------------------------------- */
VOID PaintVES( HWND hWnd )
{
HDC hDC;         // �������� ����������
PAINTSTRUCT ps;
RECT   Rect;
HANDLE hPen, hOldPen;

  EditCurve = 0;  // ������� ���� �������������� ������
  hDC = BeginPaint( hWnd, &ps ); // ��������� � ��������� ��������� WM_PAINT

//  SetTextColor( hDC, RGB(0,0,0) );
//  SetBkMode( hDC, TRANSPARENT ); // �p��p����� ��� ������
//  SelectObject( hDC, hFont );

  GetClientRect( hWnd, &Rect ); // ������� ������� ����
  if ( ! nProfilOpen)    // ���� ������� �� ��������, �������� ��� ����
//      FillRect( hDC, (LPRECT)&Rect, GetStockObject(LTGRAY_BRUSH));
      FillRect( hDC, (LPRECT)&Rect, GetStockObject(WHITE_BRUSH));
   else
   {
//     OutInfo( hWnd, hDC );
     PlotInitialize( hWnd, hDC, &Plot, &Prof );      // �������������
     DrawLogBlank( hDC, &Plot, (VEZ *) &(Prof.vez) );// �������� �����
     DrawCurve( hDC, &Plot );   // �������� �p����
   }
     EndPaint( hWnd, &ps );
}


/* ---------------------------------------------------------------
   DoInitMenu ������������ ��������� WM_INITMENU � ������������
   � ���, ������ �� ������� ���. ���� �� ������, ������ ���� File
   Save � Save As �����������. ���� �� ������, �� ��� ��������.
   ����� ������
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoInitMenu(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
WORD status, status1, status2;

 if ( nProfilOpen )  // ������� ������
  { status = MF_ENABLED;
    if ( Prof.hdr.count == Prof.hdr.npoints )  // ���� ��� ��������� ������
	status1 = MF_GRAYED;
     else
	status1 = MF_ENABLED;

    if ( Prof.hdr.count == 1 )  // ���� ��� ��p��� ������
	status2 = MF_GRAYED;
     else
	status2 = MF_ENABLED;
  }
 else  // �p����� �� ���p��
   { status = MF_GRAYED; status1 = MF_GRAYED; status2 = MF_GRAYED; }

   EnableMenuItem( wParam, IDM_SAVE, status );     // ��������� ������
   EnableMenuItem( wParam, IDM_SAVE_AS, status );
   EnableMenuItem( wParam, IDM_AUTO, status );
   EnableMenuItem( wParam, IDM_MANUAL, status );

   EnableMenuItem( wParam, IDM_NEXT, status1 ); // ��������� ������
   EnableMenuItem( wParam, IDM_LAST, status1 ); // ��������� ������
   EnableMenuItem( wParam, IDM_PREV, status2 ); // ��������� ������
   EnableMenuItem( wParam, IDM_FIRST,status2 ); // ��������� ������
   EnableMenuItem( wParam, IDM_SAVECURVE, status );
   EnableMenuItem( wParam, IDM_INFO, status );

 return 0;
}

/* ---------------------------------------------------------------
   DoCommand ������������ ��������� WM_COMMAND ��� �������� ����,
   ���������� ����� ���� � ������� ������� menuitems, ����� ����-
   ���� �����. ������� ��� ���������� �������
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoCommand(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
int i;

for ( i = 0; i < dim(menuitems); i ++ ) // ������������ ������� ���� �
   {                                    // ������� �����. �������
     if ( wParam == menuitems[i].Code )
       return (( *menuitems[i].Fxn)(hWnd,wMsg,wParam,lParam));
   }
return (DefWindowProc(hWnd,wMsg,wParam,lParam));
}


/* ---------------------------------------------------------------
   DoMenuOpen ������������ ������� File-Open �� ���� � ����������-
   ���� ������������ ������� �� commdlg.dll
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoMenuOpen(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
OPENFILENAME ofn;
static char szFname[14];

szTemp[0] = '\0';      // ����. ������ ��� ����� �����

ofn.lStructSize = sizeof(OPENFILENAME); // ����� ���������
ofn.hwndOwner = hWnd;          // ����-��������
ofn.lpstrFilter = szFilter[0]; // ����� ������ ��������
ofn.lpstrCustomFilter = NULL;  // ����� ������ �������, �����. �������������
ofn.nFilterIndex = 1;          // ������������ ������ (*.VES)
ofn.lpstrFile = szTemp;        // ����� ��� ������� ����� �-��
ofn.nMaxFile = FILENAMESIZE;   // ����� ������
//ofn.lpstrFileTitle = NULL;     // ����� ������ ��� ����� �����
ofn.lpstrFileTitle = (LPSTR) szFname; // ����� ������ ��� ����� �����
ofn.lpstrInitialDir = NULL;    // ���. ����������
ofn.lpstrTitle = NULL;         // ��������� ���� �������
ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
ofn.lpstrDefExt = NULL;       // ���������� �� ���������

//nProfilOpen = 0;
if (GetOpenFileName( &ofn ))  // ������� ������ Open
 {
     // ������� ���� �������.
     switch ( OpenProfil( szTemp, &Prof ))  {
       case  0          :
	   nProfilOpen = 1; break;
       case  F_READ_ERR :
	   nProfilOpen = 0;
	   MessageBox( hWnd, "Error Reading File !","OpenProfil",
		       MB_OK | MB_ICONSTOP);
	   break;
       case  F_NOT_OPEN :
	   nProfilOpen = 0;
	   MessageBox( hWnd, "File Not Open !","OpenProfil",
		       MB_OK | MB_ICONSTOP);
	   break;
       case  F_NOT_VEZ  :
	   nProfilOpen = 0;
	   MessageBox( hWnd, "Wrong File Format !","OpenProfil",
		       MB_OK | MB_ICONSTOP);
	   break;
       case  F_TEXT_VEZ :
	   nProfilOpen = 0;
	   if( IDOK == MessageBox( hWnd, "File is a Text VEZ File Format. Compile ?",
		       "OpenProfil", MB_OKCANCEL | MB_ICONQUESTION ))
	       MessageBox( hWnd, "", "Compile", MB_OK | MB_ICONASTERISK );

	   break;
       } // switch()
  }
  else nProfilOpen = 0;

  if ( nProfilOpen )
    { // �������� ��������� �����. ����
     sprintf(szCaption, "%s - %s", szAppName, szFname );
     SetWindowText( hWnd, szCaption ); // ������� ���������
      // ������ ������� �p����
      ReadCurve( hWnd, szTemp, (VEZ *)&(Prof.vez), Prof.hdr.count );
    }
  else
   SetWindowText( hWnd, szAppName ); // ������� ���������


// InvalidateRect( hWnd, NULL, TRUE ); // �������� ��� ����
 UpdateWindow( hWnd ); // ���������� ������� ����

return 0;
}

/* ---------------------------------------------------------------
   DoMenuExit ������������ ������� File-Exit �� ����
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoMenuExit(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
SendMessage( hWnd, WM_CLOSE, 0, 0L ); // ������� ���� ��������� close
return 0;
}

/* ---------------------------------------------------------------
   DoMenuHelpIndex ������������ ������� Index �� ���� Help
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoMenuHelpIndex(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{

// MessageBox( hWnd, szHelpText, szAppName, MB_OK | MB_ICONASTERISK);
 WinHelp(hWnd, "veshelp.hlp", HELP_CONTENTS, 0); //������� WinHelp
return 0;
}

/* ---------------------------------------------------------------
   DoMenuUsingHelp ������������ ������� Using Help �� ���� Help
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoMenuUsingHelp(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{

// MessageBox( hWnd, szHelpText, szAppName, MB_OK | MB_ICONASTERISK);
 WinHelp(hWnd, "veshelp.hlp", HELP_HELPONHELP, 0); //������� WinHelp
return 0;
}

/* ---------------------------------------------------------------
   DoMenuCurveNext ������������ ������� Curve-Next
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoMenuCurveNext(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
if ( Prof.hdr.count == Prof.hdr.npoints ) return 0L;
++ Prof.hdr.count;
return ReadCurve( hWnd, szTemp, (VEZ *)&(Prof.vez), Prof.hdr.count );
}

/* ---------------------------------------------------------------
   DoMenuCurvePrev ������������ ������� Curve-Prev
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoMenuCurvePrev(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
if ( Prof.hdr.count == 1 ) return 0L;
-- Prof.hdr.count;
return ReadCurve( hWnd, szTemp, (VEZ *)&(Prof.vez), Prof.hdr.count );
}

/* ---------------------------------------------------------------
   DoMenuCurveFirst ������������ ������� Curve-First
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoMenuCurveFirst(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
Prof.hdr.count = 1;
return ReadCurve( hWnd, szTemp, (VEZ *)&(Prof.vez), Prof.hdr.count );
}

/* ---------------------------------------------------------------
   DoMenuCurveLast ������������ ������� Curve-Last
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoMenuCurveLast(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
Prof.hdr.count = Prof.hdr.npoints;
return ReadCurve( hWnd, szTemp, (VEZ *)&(Prof.vez), Prof.hdr.count );
}

/* ---------------------------------------------------------------
   DoMenuCurveLast ������������ ������� Curve-Save
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoMenuCurveSave(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{

if( IDOK == MessageBox( hWnd, "Save current curve ?",
		       "VES", MB_OKCANCEL | MB_ICONQUESTION ))
WriteCurve( hWnd, szTemp, (VEZ *)&(Prof.vez), Prof.hdr.count );

return 0L;
}

/* ---------------------------------------------------------------
   DoMenuInfo ������������ ������� Curve-Info
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoMenuInfo(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
FARPROC lpProcInfo; // ����� ���������
/* ����� �� ����� ����������� ���� Info */

lpProcInfo = MakeProcInstance(InfoDlg, hinstance);
DialogBox(hinstance, "DLG_INFO", hWnd, lpProcInfo);
FreeProcInstance(lpProcInfo);

return 0L;
}


/* ---------------------------------------------------------------
   DoMenuAbout ������������ ������� Help-About
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoMenuAbout(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
FARPROC lpProcAbout; // ����� ���������
/* ����� �� ����� ����������� ���� About. */

lpProcAbout = MakeProcInstance(AboutDlg, hinstance);
DialogBox(hinstance, "ABOUT_VES", hWnd, lpProcAbout);
FreeProcInstance(lpProcAbout);

return 0L;
}

/* ---------------------------------------------------------------
   DoMenuInterpAuto ������������ ������� Interpretation-Automatic
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoMenuInterpAuto(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
FARPROC lpProcAuto; // ����� ���������

InterprMode = AUTO; // ��������� ����� �������������
/* ����� �� ����� ����������� ����  */
lpProcAuto = MakeProcInstance( VesInterprDlg, hinstance);
DialogBox( hinstance, "DLG_VES", hWnd, lpProcAuto ); // �������� ������
//CreateDialog( hinstance, "DLG_VES", hWnd, lpProcAuto );
FreeProcInstance(lpProcAuto);

return 0L;
}

/* ---------------------------------------------------------------
   DoMenuInterpMan ������������ ������� Interpretation-Manual
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoMenuInterpMan(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
FARPROC lpProcMan; // ����� ���������

InterprMode = MANUAL; // ��������� ����� �������������
/* ����� �� ����� ����������� ����  */
lpProcMan = MakeProcInstance( VesInterprDlg, hinstance);
DialogBox( hinstance, "DLG_VES", hWnd, lpProcMan ); // �������� ������
FreeProcInstance(lpProcMan);

return 0L;
}

/* ---------------------------------------------------------------
   DoMenuComputeCurve ������������ ������� Tools-Compute Type Curve
   ���������� ������������� ������ ���
 --------------------------------------------------------------- */
#pragma argsused   // �������� �������������� � ���������. ���.
LONG DoMenuComputeCurve(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
FARPROC lpProcCTC; // ����� ���������

/* ����� �� ����� ����������� ����  */
lpProcCTC = MakeProcInstance( VesTypeCurveDlg, hinstance);
DialogBox( hinstance, "DLG_TYPE", hWnd, lpProcCTC ); // �������� ������
FreeProcInstance(lpProcCTC);

return 0L;
}


/* ---------------------------------------------------------------
   OutInfo
 --------------------------------------------------------------- */
VOID OutInfo( HWND hWnd, HDC hDC )
{
char str[200];
RECT Rect;
int x, y, i;
int nLen;

 SelectObject( hDC, hBlackPen);
 GetClientRect( hWnd, &Rect ); // ������� ������� ����

 Rectangle( hDC, Rect.left + 2, Rect.top + 2, Rect.right - 2, Rect.bottom - 2);
 x =  Rect.left + 5;
 y =  Rect.top  + 5,

 nLen = sprintf(str, "Area   : %s", Prof.hdr.areaname );
// OemToAnsi(str,str);
 TextOut( hDC, x, y, str, nLen);

 nLen = sprintf(str, "Profil : %s", Prof.hdr.profname );
// OemToAnsi(str,str);
 TextOut( hDC, x, y += 15, str, nLen);

 nLen = sprintf(str, "Points : %d", Prof.hdr.npoints );
 TextOut( hDC, x, y += 15, str, nLen );

 nLen = sprintf(str, "First curve # : %d", Prof.hdr.count );
 TextOut( hDC, x, y += 15, str, nLen );

 nLen = sprintf(str, "Curve ID : %s", Prof.vez.ID_curve );
// OemToAnsi(str,str);
 TextOut( hDC, x, y += 15, str, nLen);

 for ( i = 0, y += 15; i < Prof.vez.curve.n; i ++ , y += 15 )
  {
    nLen = sprintf(str, " %8.0f  %8.0f  %8.0f", Prof.vez.curve.AB2[i],
		   Prof.vez.curve.fRok[i], Prof.vez.curve.tRok[i] );
    TextOut( hDC, x, y, str, nLen );
  }

 TextOut( hDC, x, y += 15, "Model", 5);
 for ( i = 0, y += 15; i < Prof.vez.model.n - 1; i ++ , y += 15 )
  {
    nLen = sprintf(str, "Ro =  %8.0f  h = %8.0f", Prof.vez.model.ro[i],
		   Prof.vez.model.h[i] );
    TextOut( hDC, x, y, str, nLen );
  }

  nLen = sprintf(str, "Ro =  %8.0f", Prof.vez.model.ro[Prof.vez.model.n - 1]);
  TextOut( hDC, x, y, str, nLen );

}


/* ---------------------------------------------------------------
   ProgressWndProc ������� ���������������� ���� Progress.
   ������������ ��� ���������, ����������� � ����� ����� ����.
 ----------------------------------------------------------------*/
LONG FAR PASCAL ProgressWndProc(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
HDC hDC;         // �������� ����������
PAINTSTRUCT ps;
static HANDLE hPen;
char str[4];
static int  nCharHgh, nCharWdt; // ������ � ������ �������� ������
TEXTMETRIC tm;
static RECT  rcBar;

static int x, cnt, xcenter;
int   y, nLen;

  switch ( wMsg ) {

   case WM_CREATE :   // ���� �������
    hPen = CreatePen( PS_SOLID, 2, RGB(0,0,255));  // C���� ��p�
    x = 2*nCapHgh;
    cnt = 0;
    rcBar.left =  x;
    rcBar.right = x + MAX_ITERATION*2;
    rcBar.top = 2*nCapHgh;
    rcBar.bottom = rcBar.top + nCapHgh;
    xcenter = (rcBar.left + rcBar.right)/2;

    hDC = GetDC( hWnd );
    GetTextMetrics( hDC, &tm );
    nCharHgh = tm.tmHeight;
    nCharHgh = tm.tmAveCharWidth;
//    SetROP2( hDC, R2_COPYPEN );
//    SetROP2( hDC, R2_XORPEN );
    ReleaseDC( hWnd, hDC );
    break;

   case WM_DESTROY:   // ������� ����
    DeleteObject( hPen );
    break;

   case WM_PROGRESS:   // ��� ��������� ���������� �������� ����. �������.
		       // ��� ���������� ���������� ���� �����������
    hDC = GetDC( hWnd );

    SelectObject( hDC, hPen );
    MoveTo( hDC, x, rcBar.top );
    LineTo( hDC, x, rcBar.bottom );
    x += 2;

    nLen = sprintf( str, "%3d", ++ cnt );
    SetTextAlign( hDC, TA_CENTER | TA_BOTTOM );  // ��������� ������������

    TextOut( hDC, xcenter, rcBar.top - 3, "   ", 3); // ������� ������
    TextOut( hDC, xcenter, rcBar.top - 3, str, nLen);

    ReleaseDC( hWnd, hDC );
    break;

   case WM_PAINT  :
    hDC = BeginPaint( hWnd, &ps ); // ��������� � ��������� ��������� WM_PAINT
//    SetBkColor(hDC, GetSysColor(COLOR_BACKGROUND)); // �����. ���� ���� ������
//    SetBkColor(hDC, GetPixel(hDC, 2,2 )); // �����. ���� ���� ������
    SetBkColor(hDC, RGB(192, 192, 192)); // �����. ���� ���� ������
    SetTextAlign( hDC, TA_LEFT | TA_BOTTOM );  // ��������� ������������ ������
    TextOut( hDC, rcBar.left, rcBar.top - 3, "Trials", 6);
//    SetBkMode( hDC, TRANSPARENT );

    SelectObject( hDC, hWhitePen );  // ������ �������� �������
    MoveTo(hDC, rcBar.left - 2, rcBar.bottom + 1);
    LineTo(hDC, rcBar.left - 2, rcBar.top - 2);
    LineTo(hDC, rcBar.right + 2, rcBar.top - 2);
    SelectObject( hDC, hBlackPen );
    LineTo(hDC, rcBar.right + 2, rcBar.bottom + 1);
    LineTo(hDC, rcBar.left - 2, rcBar.bottom + 1);

//    SetROP2( hDC, R2_XORPEN );

    EndPaint( hWnd, &ps );
    break;

   default : return (DefWindowProc(hWnd,wMsg,wParam,lParam));
   }

return NULL;
}
