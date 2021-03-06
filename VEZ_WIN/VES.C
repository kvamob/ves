/*   ���� ves.c   �᭮���� ���� �p���� ves
_________________________________________________________________________
 �ணࠬ�� ���p�p��樨 �p���� ��� : / VES for Windows v1.0b /
 �ணࠬ�� �㭪樮����� ��� �ࠢ������ ��⥬� Windows v3.1 �
 �ᯮ�짮������ ������⥪:
   commdlg.dll
   ctl3dv2.lib (using ctl3dv2.dll)


 (c) 1995 �.���⪮�
 Compiler : Borland C++ 3.1  Borland C++ 4.5
 Project  :
 model    : MEDIUM
 �����⥫쭠� ।���� 22.02.96
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

#define  NOSOUND          // �. ��砫� 䠩�� windows.h
#define  NOCOMM
#define  NODRIVERS
#define  NOPROFILER
#define  NOKEYBOARDINFO
#define  NOMETAFILE

#include "ves.h"
#include "ves_rc.h"

#define dim(x) sizeof(x)/sizeof(x[0])     // C���頥� ������⢮ ������⮢
#define FILENAMESIZE 256       // ����. ����� ����� 䠩��

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
HANDLE  hinstance;             // �����䨪��p ��������p� �����
HWND    hFrame;                // �����䨪��p ����饣� ���� (����-p����)
HWND    hProgress;             // �����䨪��p �ᯮ���. ����
HWND    hwndPlot;              // �����䨪��p ���� � p��㭪��
int     xScreen, yScreen;      // ��ਭ� � ���� ��࠭� � ���ᥫ��
int     nCapHgh;               // ���� ��������� ���� - ��� ��⠭���� ࠧ��஢
			       // �ᯮ����⥫쭮�� ����
int     yBord;                 // ���騭� ࠬ�� ���� �� ���⨪���

char szFileNameBin[FILENAMESIZE+1]; // ��� ⥪�饣� ����筮�� 䠩�� VEZ-�ଠ�
char szTemp[FILENAMESIZE+1];        // ���� ��� �࠭���� ����� 䠩��

HANDLE  hIconVES;      // ������ VES
int     hVEZBinFile;   // ���p���p ����筮�� 䠩�� �p��� VEZ
int     nProfilOpen=0; // �ਧ��� ������ 䠩�� ��䨫� (1 - �����, 0 - ���
int     EditCurve = 0; // �p����� p�����p������ �p����

PROFIL  Prof;          // ��䨫� ���
VES_PAINTDATA Plot;    // ����� ��� ����p����� �p�䨪��
int     InterprMode;   // ����� ������樨 - ��筠� ��� ��⮬���.

HPEN hBlackPen,        // ��p� ���p������ � Windows
     hWhitePen,
     hDarkPen,         // ����� ��� �ᢥ饭��� � ��⥭����� ࠬ��
     hLightPen,
     hBluePen,         // ��� p�ᮢ���� �������� �p����
     hRedPen;          // ��� p�ᮢ���� ⥮p���᪮� �p����

HANDLE hFont;          // ���ਯ�� ����
HANDLE hAccel;         // ���ਯ�� �᪮�⥫�

char szShortAppName[]  = "VES"; // �p�⪮� ��� �p��������
char szAppName[]       = "Vertical Electric Sounding"; // ������ ���
char szMenuName[]      = "MENU_VES"; // ��� p���p� ����
char szDefName[]       = "Untitled"; // ��� 䠩�� �� 㬮�砭��
char szDefExt[]        = "ves";      // p���p���� 䠩�� �� 㬮�砭��
char szHelpText[] = "Sorry but Help system is not available\n"\
"in Beta-version of this Application";
char szCaption[100];         // ���� ��� ��������� ����饣� ����

char *szFilter[] =  {   // 䨫��p� ��� �⠭��p���  ��������
"Bynary VES files (*.VES)", "*.VES",
"Text   VES files (*.VEZ)", "*.VEZ",
"All files (*.*)", "*.*",
""};

HCURSOR hNormalCursor, hHourGlassCursor; // �����䨪��p� ��p�p��

struct decodeWord { // C�p���p�, ��뢠��� �����䨪��p�
   WORD Code;       // ᮮ�饭�� ��� ���� � �㭪�ﬨ
   LONG (*Fxn) (HWND, WORD, WORD, LONG );
   };

// ������ ��p����뢠���� �㭪樥� FrameWndProc ᮮ�饭��,
// ���������� �p� p���� � ������ � �㭪樨, ᮮ⢥�����騥
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
//LOCALHANDLE    hChData;           // ���ਯ�� �������� ������ � �����
//NPCHDATA       npChData;          // �����⥫� �� �������� ������

//
// ������ �����䨪��p�� �㭪⮢ ���� � ᮮ⢥�����騥 �� �㭪樨
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
		 WinMain ��砫� �ணࠬ�� VES.
------------------------------------------------------------- */
int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow)
{
MSG msg;

hinstance = hInstance; // �������� �����䨪��p ⥪�饣�
				 // ��������p� �p��������
if( !hPrevInstance)     // �᫨ �� ��p�� ��������p, ��p�����p. ����� ����
	if (!InitApplication(hinstance)) return FALSE;

hHourGlassCursor = LoadCursor(NULL, IDC_WAIT); // ��p�p-����.���

hAccel = LoadAccelerators(hinstance, "ACCEL_1"); // ����㧨� ��ᥫ����

if( !InitInstance(hInstance, nCmdShow))  // C������ ���� �⮣� ��������p�
	 return FALSE;

Ctl3dRegister(hInstance);
Ctl3dAutoSubclass( hInstance );

while(GetMessage(&msg, NULL, 0, 0)) // �᭮���� 横� ᮮ�饭�� �ணࠬ��
	{
	  if ( !TranslateAccelerator(hFrame,hAccel,&msg))
	  {
	 TranslateMessage(&msg);
	 DispatchMessage(&msg);
		}
	}

Ctl3dUnregister(hInstance);

//TermInstance(hInstance);  // "��������" � �⨬ ��������p��
return (msg.wParam);      // ���祭�� �p� ����p�� = WM_QUIT

}

/* --------------------------------------------------------------
	InitApplication ��� ��饩 ���樠����樨 ��� ������ �p��p����
-----------------------------------------------------------------*/
BOOL InitApplication(HANDLE hInstance)
{
WNDCLASS wc;
	 /* ��������� ����� ����饣� ����. */
 wc.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;  // C⨫� �����
 wc.lpfnWndProc   = FrameWndProc;    // �p�ᮥ�������� �㭪�� �����
 wc.cbClsExtra    = 0;               // �������⥫�� ����� ��� �����
 wc.cbWndExtra    = 0;               // �������⥫�� ����� ��� ����
 wc.hInstance     = hInstance;       // �����䨪��p �������� �����
 wc.hIcon         = LoadIcon(hInstance,(LPSTR)"ICON_VES"); // ������ �� 㬮��.
 wc.hCursor       = LoadCursor(NULL,IDC_ARROW);    // ��p�p �� 㬮��.
// wc.hbrBackground = COLOR_APPWORKSPACE+1;          // ���� 䮭� �� 㬮��.
// wc.hbrBackground = COLOR_WINDOW;          // ���� 䮭� �� 㬮��.
 wc.hbrBackground = GetStockObject(LTGRAY_BRUSH); // ���� 䮭� �� 㬮��.
 wc.lpszMenuName  = szMenuName;      // ��� p���p� ����
 wc.lpszClassName = szShortAppName;  // ��� ����� ����

 hNormalCursor = wc.hCursor;
 hIconVES      = wc.hIcon;

 if ( !RegisterClass(&wc) ) return FALSE; // ��p�����p�p����� �����

  /* ��������� ����� �ᯮ����⥫쭮�� ����. */
 wc.style         = CS_OWNDC;        // C⨫� �����
 wc.lpfnWndProc   = ProgressWndProc; // �p�ᮥ�������� �㭪�� �����
 wc.cbClsExtra    = 0;               // �������⥫�� ����� ��� �����
 wc.cbWndExtra    = 0;               // �������⥫�� ����� ��� ����
 wc.hInstance     = hInstance;       // �����䨪��p �������� �����
// wc.hIcon         = LoadIcon(hInstance,(LPSTR)"ICON_VES"); // ������ �� 㬮��.
// wc.hCursor       = LoadCursor(NULL,IDC_ARROW);    // ��p�p �� 㬮��.
// wc.hbrBackground = COLOR_APPWORKSPACE+1;          // ���� 䮭� ���
// wc.hbrBackground = COLOR_WINDOW;          // ���� 䮭� �� 㬮��.
 wc.hbrBackground = GetStockObject(LTGRAY_BRUSH); // ���� 䮭� �� 㬮��.

 wc.lpszMenuName  = NULL;      // ��� p���p� ����
 wc.lpszClassName = "Progress";  // ��� ����� ����

 if ( !RegisterClass(&wc) ) return FALSE; // ��p�����p�p����� �����

 return TRUE; // ��p�����p�p����� �����
}

/* --------------------------------------------------------------
   InitInstance ��� ���樠����樨 ��������p� ������� �p��������
-----------------------------------------------------------------*/
BOOL InitInstance(HANDLE hInstance, WORD nCmdShow)
{
hFrame = CreateWindow(    // �������� ����饣� ���� �ணࠬ��
	 szShortAppName,  // ��� ����� ����
	 szAppName,       // ⥪�� ���������
	 WS_OVERLAPPEDWINDOW, // C⨫� ����
	 CW_USEDEFAULT, CW_USEDEFAULT, // ������ �� 㬮�砭��
	 CW_USEDEFAULT, CW_USEDEFAULT, // p����p� �� 㬮�砭��
	 NULL,     // ���� ��� �p����
	 NULL,     // �p������� ���� �����, �ᯮ��. �� 㬮��.
	 hInstance,// �������� ����
	 NULL );   // ���ᯮ��㥬� 㪠��⥫�
if(!hFrame) return FALSE;

ShowWindow(hFrame, nCmdShow); // C������ ����饥 ���� ������
UpdateWindow(hFrame);         // ��᫠�� ᮮ��. WM_PAINT

xScreen = GetSystemMetrics(SM_CXSCREEN); // ����稬 ࠧ���� ��࠭�
yScreen = GetSystemMetrics(SM_CYSCREEN);
yBord   = GetSystemMetrics(SM_CYBORDER); // ���騭� ࠬ��
nCapHgh = GetSystemMetrics(SM_CYCAPTION); // ����稬 ࠧ��� ���������

return TRUE;
}

/* --------------------------------------------------------------
   TermInstance ��� �������樨 ��������p� ������� �p��������
-----------------------------------------------------------------*/
BOOL TermInstance(HANDLE hInstance)
{
return TRUE;
}

/* ---------------------------------------------------------------
   FrameWndProc �㭪�� ����饣� ����. ��ࠡ��뢠�� �� ᮮ�饭��,
   ����㯠�騥 � ���� ����饣� ���� �ணࠬ��.
 ----------------------------------------------------------------*/
LONG FAR PASCAL FrameWndProc(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
int i;
for ( i = 0; i < dim(messages); i ++ ) // ����஢��� ᮮ�饭�� ���� �
   {                                   // �맢��� ᮮ�. �㭪��
     if ( wMsg == messages[i].Code )
       return (( *messages[i].Fxn)(hWnd,wMsg,wParam,lParam));
   }
return (DefWindowProc(hWnd,wMsg,wParam,lParam));
}

/* ---------------------------------------------------------------
   DoCreate ��ࠡ��뢠�� ᮮ�饭�� WM_CREATE
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoCreate(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
LOGFONT lf;  // C�p���p� �����᪮�� �p���
HDC     hDC; // ���⥪�� ���p���⢠
COLORREF _RED, _LTGRAY, _BLUE;

// C������� �p���
memset( &lf, 0, sizeof(LOGFONT));  // ���㫨� lf
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
hRedPen  = CreatePen( PS_SOLID, 2,_RED);  // �p�᭮� ��p�
hBluePen = CreatePen( PS_SOLID, 2,_BLUE); // C���� ��p�
//hDarkPen  = CreatePen( PS_SOLID, 2,RGB(90,90,90));
hDarkPen  = CreatePen( PS_SOLID, 2,RGB(40,40,40));
hLightPen = CreatePen( PS_SOLID, 2,RGB(250,250,250));

 SelectObject( hDC, hFont );       // ���p㧨� �p���
 SetTextColor( hDC, RGB(0,0,0) );  // ��⠭���� 梥� ⥪��
 SetBkMode( hDC, TRANSPARENT );    // �p��p��� 䮭 ⥪��

ReleaseDC( hWnd, hDC );

return 0L;
}

/* ---------------------------------------------------------------
   DoDestroy ��ࠡ��뢠�� ᮮ�饭�� WM_DESTROY
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoDestroy(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
DeleteObject(hFont);       // �᢮����� ��ꥪ�� GDI
DeleteObject(hRedPen);
DeleteObject(hBluePen);
DeleteObject(hDarkPen);
DeleteObject(hLightPen);

PostQuitMessage(0);
return 0L;
}

/* ---------------------------------------------------------------
   DoLButtonDown ��ࠡ��뢠�� ᮮ�饭�� WM_LBUTTONDOWN
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoLButtonDown(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
POINT pt;

if ( !nProfilOpen ) return 0L;  // �p�䨫� �� ��p�� - ��室
 pt.x = LOWORD(lParam);  // ���p����� ���
 pt.y = HIWORD(lParam);
 EditCurveByMouse( hWnd, &Prof, &Plot, pt ); // �맮��� �㭪�� ।����.
return 0L;
}

/* ---------------------------------------------------------------
   DoRButtonDown ��ࠡ��뢠�� ᮮ�饭�� WM_RBUTTONDOWN
   �� ����⨨ �ࠢ�� ������ ��� �⬥����� ०�� ।���஢����
   �ਢ��
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoRButtonDown(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
POINT pt;

if ( !nProfilOpen ) return 0L;  // �p�䨫� �� ��p�� - ��室
 pt.x = 0;  // ���ᨬ ���p������ ���
 pt.y = 0;
 EditCurveByMouse( hWnd, &Prof, &Plot, pt ); // �맮��� �㭪�� ।����.

return 0L;
}


/* ---------------------------------------------------------------
  DoPaint ��ࠡ��뢠�� ᮮ�饭�� WM_PAINT ��� ����饣� ����,
  ���஥ ��室��, ����� ��뢠���� �㭪�� UpdateWindow ���
  ����� �ந�室�� ��������� ࠧ��஢ ����, ��� ��६��. ���
  ��४��⨥.
  �� ���⨦���� ࠧ��஢ ���� ����� �।�����
  ࠧ��� ���� ��⠭���������� ࠢ�� �।���� ���祭��.
 --------------------------------------------------------------- */
LONG DoPaint(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
{

int nWidth; int nHeigh;  // ������� ����
RECT rect;

GetWindowRect(hWnd, &rect );      // ����稬 ࠧ���� ����
nWidth = rect.right - rect.left;
nHeigh = rect.bottom - rect.top;

if ( nWidth < 400 || nHeigh < 350 )  // �஢�ઠ �� �।���� ���. ���祭��
 {
  nWidth = (nWidth < 400 ) ? 400 : nWidth;
  nHeigh = (nHeigh < 350 ) ? 350 : nHeigh;
             // ��⠭���� ���� ࠧ����
  SetWindowPos( hWnd, NULL, 0, 0, nWidth, nHeigh, SWP_NOMOVE | SWP_NOZORDER );
 }

  InvalidateRect( hWnd, NULL, TRUE ); // �������� �� ����
  PaintVES( hWnd );  // ��ᮢ��� � ����
  return 0L;
}

/* ---------------------------------------------------------------
   DoSize ��ࠡ��뢠�� ᮮ�饭�� WM_SIZE ��� ����饣� ����,
   ���஥ ��室��, ����� ����� �ந�室�� ��������� ࠧ��஢
   ����.
   �� ���⨦���� ࠧ��஢ ���� ����� �।�����
   ࠧ��� ���� ��⠭���������� ࠢ�� �।���� ���祭��.
 --------------------------------------------------------------- */
//LONG DoSize(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
//#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
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

//  InvalidateRect( hWnd, NULL, TRUE ); // �������� �� ����
//  PaintVES( hWnd );  // ��ᮢ��� � ����
//  return 0L;
//}


/* ---------------------------------------------------------------
	PaintVES ����� � ���� hWnd ���. �����, � �ਢ� ���
--------------------------------------------------------------- */
VOID PaintVES( HWND hWnd )
{
HDC hDC;         // ���⥪�� ���ன�⢠
PAINTSTRUCT ps;
RECT   Rect;
HANDLE hPen, hOldPen;

  EditCurve = 0;  // ��ᨬ 䫠� ।���஢���� �ਢ��
  hDC = BeginPaint( hWnd, &ps ); // ��������� � ����祭�� ᮮ�饭�� WM_PAINT

//  SetTextColor( hDC, RGB(0,0,0) );
//  SetBkMode( hDC, TRANSPARENT ); // �p��p��� 䮭 ⥪��
//  SelectObject( hDC, hFont );

  GetClientRect( hWnd, &Rect ); // ����稬 ࠧ���� ����
  if ( ! nProfilOpen)    // �᫨ ��䨫� �� ����㦥�, ������ 䮭 ����
//      FillRect( hDC, (LPRECT)&Rect, GetStockObject(LTGRAY_BRUSH));
      FillRect( hDC, (LPRECT)&Rect, GetStockObject(WHITE_BRUSH));
   else
   {
//     OutInfo( hWnd, hDC );
     PlotInitialize( hWnd, hDC, &Plot, &Prof );      // ���樠������
     DrawLogBlank( hDC, &Plot, (VEZ *) &(Prof.vez) );// ��ᮢ��� �����
     DrawCurve( hDC, &Plot );   // ��ᮢ��� �p����
   }
     EndPaint( hWnd, &ps );
}


/* ---------------------------------------------------------------
   DoInitMenu ��ࠡ��뢠�� ᮮ�饭�� WM_INITMENU � ᮮ⢥��⢨�
   � ⥬, ����� �� ��䨫� ���. �᫨ �� �����, �㭪�� ���� File
   Save � Save As ࠧ������. �᫨ �� �����, � ��� ����訢.
   ��� 梥⮬
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoInitMenu(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
WORD status, status1, status2;

 if ( nProfilOpen )  // ��䨫� �����
  { status = MF_ENABLED;
    if ( Prof.hdr.count == Prof.hdr.npoints )  // �᫨ �� ��᫥���� �ਢ��
	status1 = MF_GRAYED;
     else
	status1 = MF_ENABLED;

    if ( Prof.hdr.count == 1 )  // �᫨ �� ��p��� �ਢ��
	status2 = MF_GRAYED;
     else
	status2 = MF_ENABLED;
  }
 else  // �p�䨫� �� ��p��
   { status = MF_GRAYED; status1 = MF_GRAYED; status2 = MF_GRAYED; }

   EnableMenuItem( wParam, IDM_SAVE, status );     // ��⠭���� �����
   EnableMenuItem( wParam, IDM_SAVE_AS, status );
   EnableMenuItem( wParam, IDM_AUTO, status );
   EnableMenuItem( wParam, IDM_MANUAL, status );

   EnableMenuItem( wParam, IDM_NEXT, status1 ); // ��⠭���� �����
   EnableMenuItem( wParam, IDM_LAST, status1 ); // ��⠭���� �����
   EnableMenuItem( wParam, IDM_PREV, status2 ); // ��⠭���� �����
   EnableMenuItem( wParam, IDM_FIRST,status2 ); // ��⠭���� �����
   EnableMenuItem( wParam, IDM_SAVECURVE, status );
   EnableMenuItem( wParam, IDM_INFO, status );

 return 0;
}

/* ---------------------------------------------------------------
   DoCommand ��ࠡ��뢠�� ᮮ�饭�� WM_COMMAND ��� ����饣� ����,
   ��।���� �㭪� ���� � ������� ���ᨢ� menuitems, ��⥬ ���-
   ���� ᮮ�. �㭪�� ��� �믮������ �������
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoCommand(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
int i;

for ( i = 0; i < dim(menuitems); i ++ ) // ����஢��� ������� ���� �
   {                                    // �맢��� ᮮ�. �㭪��
     if ( wParam == menuitems[i].Code )
       return (( *menuitems[i].Fxn)(hWnd,wMsg,wParam,lParam));
   }
return (DefWindowProc(hWnd,wMsg,wParam,lParam));
}


/* ---------------------------------------------------------------
   DoMenuOpen ��ࠡ��뢠�� ������� File-Open �� ���� � �ᯮ�짮��-
   ���� �⠭���⭮�� ������� �� commdlg.dll
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoMenuOpen(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
OPENFILENAME ofn;
static char szFname[14];

szTemp[0] = '\0';      // ����. ���� ��� ����� 䠩��

ofn.lStructSize = sizeof(OPENFILENAME); // ����� ��������
ofn.hwndOwner = hWnd;          // ����-��������
ofn.lpstrFilter = szFilter[0]; // ���� ᯨ᪠ 䨫��஢
ofn.lpstrCustomFilter = NULL;  // ���� ���� 䨫���, ��।. ���짮��⥫��
ofn.nFilterIndex = 1;          // �ᯮ�짮���� 䨫��� (*.VES)
ofn.lpstrFile = szTemp;        // ���� ��� ������� ����� �-��
ofn.nMaxFile = FILENAMESIZE;   // ����� ����
//ofn.lpstrFileTitle = NULL;     // ���� ⮫쪮 ��� ����� 䠩��
ofn.lpstrFileTitle = (LPSTR) szFname; // ���� ⮫쪮 ��� ����� 䠩��
ofn.lpstrInitialDir = NULL;    // ���. �����⠫��
ofn.lpstrTitle = NULL;         // ��������� ���� �������
ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
ofn.lpstrDefExt = NULL;       // ���७�� �� 㬮�砭��

//nProfilOpen = 0;
if (GetOpenFileName( &ofn ))  // ������ ������ Open
 {
     // ������ 䠩� ��䨫�.
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
     SetWindowText( hWnd, szCaption ); // �뢥��� ���������
      // ��⠥� ⥪���� �p����
      ReadCurve( hWnd, szTemp, (VEZ *)&(Prof.vez), Prof.hdr.count );
    }
  else
   SetWindowText( hWnd, szAppName ); // �뢥��� ���������


// InvalidateRect( hWnd, NULL, TRUE ); // �������� �� ����
 UpdateWindow( hWnd ); // �����㥬 ����饥 ����

return 0;
}

/* ---------------------------------------------------------------
   DoMenuExit ��ࠡ��뢠�� ������� File-Exit �� ����
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoMenuExit(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
SendMessage( hWnd, WM_CLOSE, 0, 0L ); // ��᫠�� ���� ᮮ�饭�� close
return 0;
}

/* ---------------------------------------------------------------
   DoMenuHelpIndex ��ࠡ��뢠�� ������� Index �� ���� Help
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoMenuHelpIndex(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{

// MessageBox( hWnd, szHelpText, szAppName, MB_OK | MB_ICONASTERISK);
 WinHelp(hWnd, "veshelp.hlp", HELP_CONTENTS, 0); //�맢��� WinHelp
return 0;
}

/* ---------------------------------------------------------------
   DoMenuUsingHelp ��ࠡ��뢠�� ������� Using Help �� ���� Help
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoMenuUsingHelp(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{

// MessageBox( hWnd, szHelpText, szAppName, MB_OK | MB_ICONASTERISK);
 WinHelp(hWnd, "veshelp.hlp", HELP_HELPONHELP, 0); //�맢��� WinHelp
return 0;
}

/* ---------------------------------------------------------------
   DoMenuCurveNext ��ࠡ��뢠�� ������� Curve-Next
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoMenuCurveNext(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
if ( Prof.hdr.count == Prof.hdr.npoints ) return 0L;
++ Prof.hdr.count;
return ReadCurve( hWnd, szTemp, (VEZ *)&(Prof.vez), Prof.hdr.count );
}

/* ---------------------------------------------------------------
   DoMenuCurvePrev ��ࠡ��뢠�� ������� Curve-Prev
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoMenuCurvePrev(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
if ( Prof.hdr.count == 1 ) return 0L;
-- Prof.hdr.count;
return ReadCurve( hWnd, szTemp, (VEZ *)&(Prof.vez), Prof.hdr.count );
}

/* ---------------------------------------------------------------
   DoMenuCurveFirst ��ࠡ��뢠�� ������� Curve-First
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoMenuCurveFirst(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
Prof.hdr.count = 1;
return ReadCurve( hWnd, szTemp, (VEZ *)&(Prof.vez), Prof.hdr.count );
}

/* ---------------------------------------------------------------
   DoMenuCurveLast ��ࠡ��뢠�� ������� Curve-Last
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoMenuCurveLast(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
Prof.hdr.count = Prof.hdr.npoints;
return ReadCurve( hWnd, szTemp, (VEZ *)&(Prof.vez), Prof.hdr.count );
}

/* ---------------------------------------------------------------
   DoMenuCurveLast ��ࠡ��뢠�� ������� Curve-Save
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoMenuCurveSave(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{

if( IDOK == MessageBox( hWnd, "Save current curve ?",
		       "VES", MB_OKCANCEL | MB_ICONQUESTION ))
WriteCurve( hWnd, szTemp, (VEZ *)&(Prof.vez), Prof.hdr.count );

return 0L;
}

/* ---------------------------------------------------------------
   DoMenuInfo ��ࠡ��뢠�� ������� Curve-Info
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoMenuInfo(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
FARPROC lpProcInfo; // ���� ��楤���
/* �뢮� �� ��࠭ ����������� ���� Info */

lpProcInfo = MakeProcInstance(InfoDlg, hinstance);
DialogBox(hinstance, "DLG_INFO", hWnd, lpProcInfo);
FreeProcInstance(lpProcInfo);

return 0L;
}


/* ---------------------------------------------------------------
   DoMenuAbout ��ࠡ��뢠�� ������� Help-About
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoMenuAbout(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
FARPROC lpProcAbout; // ���� ��楤���
/* �뢮� �� ��࠭ ����������� ���� About. */

lpProcAbout = MakeProcInstance(AboutDlg, hinstance);
DialogBox(hinstance, "ABOUT_VES", hWnd, lpProcAbout);
FreeProcInstance(lpProcAbout);

return 0L;
}

/* ---------------------------------------------------------------
   DoMenuInterpAuto ��ࠡ��뢠�� ������� Interpretation-Automatic
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoMenuInterpAuto(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
FARPROC lpProcAuto; // ���� ��楤���

InterprMode = AUTO; // ��⠭���� ०�� ������樨
/* �뢮� �� ��࠭ ����������� ����  */
lpProcAuto = MakeProcInstance( VesInterprDlg, hinstance);
DialogBox( hinstance, "DLG_VES", hWnd, lpProcAuto ); // ��뢠�� ������
//CreateDialog( hinstance, "DLG_VES", hWnd, lpProcAuto );
FreeProcInstance(lpProcAuto);

return 0L;
}

/* ---------------------------------------------------------------
   DoMenuInterpMan ��ࠡ��뢠�� ������� Interpretation-Manual
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoMenuInterpMan(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
FARPROC lpProcMan; // ���� ��楤���

InterprMode = MANUAL; // ��⠭���� ०�� ������樨
/* �뢮� �� ��࠭ ����������� ����  */
lpProcMan = MakeProcInstance( VesInterprDlg, hinstance);
DialogBox( hinstance, "DLG_VES", hWnd, lpProcMan ); // ��뢠�� ������
FreeProcInstance(lpProcMan);

return 0L;
}

/* ---------------------------------------------------------------
   DoMenuComputeCurve ��ࠡ��뢠�� ������� Tools-Compute Type Curve
   ���᫥��� ⥮���᪮� �ਢ�� ���
 --------------------------------------------------------------- */
#pragma argsused   // �⪫�稬 �।�०����� � ���ᯮ��. ��.
LONG DoMenuComputeCurve(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
FARPROC lpProcCTC; // ���� ��楤���

/* �뢮� �� ��࠭ ����������� ����  */
lpProcCTC = MakeProcInstance( VesTypeCurveDlg, hinstance);
DialogBox( hinstance, "DLG_TYPE", hWnd, lpProcCTC ); // ��뢠�� ������
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
 GetClientRect( hWnd, &Rect ); // ����稬 ࠧ���� ����

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
   ProgressWndProc �㭪�� �ᯮ����⥫쭮�� ���� Progress.
   ��ࠡ��뢠�� �� ᮮ�饭��, ����㯠�騥 � ���� �⮣� ����.
 ----------------------------------------------------------------*/
LONG FAR PASCAL ProgressWndProc(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
HDC hDC;         // ���⥪�� ���ன�⢠
PAINTSTRUCT ps;
static HANDLE hPen;
char str[4];
static int  nCharHgh, nCharWdt; // ��ਭ� � ���� ⥪�饣� ����
TEXTMETRIC tm;
static RECT  rcBar;

static int x, cnt, xcenter;
int   y, nLen;

  switch ( wMsg ) {

   case WM_CREATE :   // ���� ᮧ����
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

   case WM_PROGRESS:   // �� ᮮ�饭�� ���뫠���� �㭪樥� ����. �����.
		       // �� ᮢ��襭�� ��।���� 蠣� �ਡ�������
    hDC = GetDC( hWnd );

    SelectObject( hDC, hPen );
    MoveTo( hDC, x, rcBar.top );
    LineTo( hDC, x, rcBar.bottom );
    x += 2;

    nLen = sprintf( str, "%3d", ++ cnt );
    SetTextAlign( hDC, TA_CENTER | TA_BOTTOM );  // ��⠭���� ��ࠢ�������

    TextOut( hDC, xcenter, rcBar.top - 3, "   ", 3); // ����� ��஥
    TextOut( hDC, xcenter, rcBar.top - 3, str, nLen);

    ReleaseDC( hWnd, hDC );
    break;

   case WM_PAINT  :
    hDC = BeginPaint( hWnd, &ps ); // ��������� � ����祭�� ᮮ�饭�� WM_PAINT
//    SetBkColor(hDC, GetSysColor(COLOR_BACKGROUND)); // ��⠭. 梥� 䮭� ⥪��
//    SetBkColor(hDC, GetPixel(hDC, 2,2 )); // ��⠭. 梥� 䮭� ⥪��
    SetBkColor(hDC, RGB(192, 192, 192)); // ��⠭. 梥� 䮭� ⥪��
    SetTextAlign( hDC, TA_LEFT | TA_BOTTOM );  // ��⠭���� ��ࠢ������� ⥪��
    TextOut( hDC, rcBar.left, rcBar.top - 3, "Trials", 6);
//    SetBkMode( hDC, TRANSPARENT );

    SelectObject( hDC, hWhitePen );  // ���㥬 ��㪫�� ࠬ���
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
