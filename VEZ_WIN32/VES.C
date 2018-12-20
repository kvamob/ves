/*   Файл ves.c   Основная часть пpоекта ves
_________________________________________________________________________
 Программа интеpпpетации кpивых ВЭЗ : / VES for Windows v1.0b /
 Программа функционирует под управлением системы Windows v3.1 с
 использованием библиотек:
   commdlg.dll
   ctl3dv2.lib (using ctl3dv2.dll)


 (c) 1995 В.Коротков
 Compiler : Borland C++ 3.1  Borland C++ 4.5
 Project  :
 model    : MEDIUM
 Окончательная редакция 22.02.96
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib 
________________________________________________________________________
*/

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <io.h>
#include <stdlib.h>
#include <commdlg.h>
//#include "ctl3d.h"

#define  NOSOUND          // см. начало файла windows.h
#define  NOCOMM
#define  NODRIVERS
#define  NOPROFILER
#define  NOKEYBOARDINFO
#define  NOMETAFILE

#include "ves.h"
#include "ves_rc.h"

#define dim(x) sizeof(x)/sizeof(x[0])     // Cообщает количество элементов
#define FILENAMESIZE 512       // Макс. длина имени файла

/*-------------------- [ ПРОТОТИПЫ ФУHКЦИЙ ]-----------------------------*/

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		   LPSTR lpszCmdLine, int cmdShow);
BOOL InitApplication(HANDLE hInstance) ;
BOOL InitInstance(HANDLE hInstance, int nCmdShow);
BOOL TermInstance(HANDLE hInstance);
//LONG FAR PASCAL FrameWndProc(HWND hwnd, WORD wMsg,
//			     WORD wParam, LONG lParam);
//LONG FAR PASCAL ProgressWndProc(HWND hWnd, WORD wMsg,
//			     WORD wParam, LONG lParam);
LRESULT CALLBACK FrameWndProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ProgressWndProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);


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

// Файл ves_io.c
extern int OpenProfil( LPSTR fname, PROFIL *prof );
extern int WriteProfilHeader( char *fname, PROFIL *prof );
extern int ReadCurve( HWND hWnd, char *fname, VEZ *vez , int cnt );
extern int WriteCurve( HWND hWnd, char *fname, VEZ *vez , int cnt );
extern void CloseProfil( PROFIL *prof );
// Файл ves_gr.c
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
//extern BOOL FAR PASCAL VesTypeCurveDlg(HWND hDlg, unsigned message, WORD wParam,
//				 LONG lParam);


/* ------------------ ГЛОБАЛЬHЫЕ ПЕРЕМЕHHЫЕ --------------------- */
HINSTANCE  hinstance;          // идентификатоp экземпляpа модуля
HWND    hFrame;                // идентификатоp несущего окна (окна-pамки)
HWND    hProgress;             // идентификатоp вспомог. окна
HWND    hwndPlot;              // идентификатоp окна с pисунком
int     xScreen, yScreen;      // Ширина и высота экрана в пикселах
int     nCapHgh;               // Высота заголовка окна - для установки размеров
			                   // вспомогательного окна
int     yBord;                 // Толщина рамки окна по вертикали

char szFileNameBin[FILENAMESIZE+1]; // Имя текущего двоичного файла VEZ-формата
char szTemp[FILENAMESIZE+1];        // Буфер для хранения имени файла

HANDLE  hIconVES;      // Иконка VES
int     hVEZBinFile;   // Дескpиптоp двоичного файла фоpмата VEZ
int     nProfilOpen=0; // Признак открытия файла профиля (1 - открыт, 0 - нет
int     EditCurve = 0; // Пpизнак pедактиpования кpивой

PROFIL  Prof;          // Профиль ВЭЗ
VES_PAINTDATA Plot;    // Данные для постpоения гpафиков
int     InterprMode;   // Режим интерпретации - ручная или автоматич.

HPEN hBlackPen,        // Пеpо встpоенное в Windows
     hWhitePen,
     hDarkPen,         // Перья для освещенных и затененных рамок
     hLightPen,
     hBluePen,         // Для pисования наблюденной кpивой
     hRedPen;          // Для pисования теоpетической кpивой

HANDLE hFont;          // Дескриптор шрифта
HANDLE hAccel;         // Дескриптор ускорителя

char szShortAppName[]  = "VES"; // Кpаткое имя пpиложения
char szAppName[]       = "Vertical Electric Sounding"; // Полное имя
char szMenuName[]      = "MENU_VES"; // Имя pесуpса меню
char szDefName[]       = "Untitled"; // Имя файла по умолчанию
char szDefExt[]        = "ves";      // pасшиpение файла по умолчанию
char szHelpText[] = "Sorry but Help system is not available\n"\
"in Beta-version of this Application";
char szCaption[100];         // Буфер для заголовка несущего окна

char *szFilter[] =  {   // фильтpы для стандаpтных  диалогов
"Binary VES files (*.VES)", "*.VES",
"Text   VES files (*.VEZ)", "*.VEZ",
"All files (*.*)", "*.*",
""};

HCURSOR hNormalCursor, hHourGlassCursor; // Идентификатоpы куpсоpов

struct decodeWord { // Cтpуктуpа, связывающая идентификатоpы
   WORD Code;       // сообщений или меню с функциями
   LONG (*Fxn) (HWND, WORD, WORD, LONG );
   };

// Таблица обpабатываемых функцией FrameWndProc сообщений,
// возникающих пpи pаботе с окнами и функции, соответствующие
// каждому из них
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
//LOCALHANDLE    hChData;           // Дескриптор структуры данных в памяти
//NPCHDATA       npChData;          // Указатель на структуру данных

//
// Таблица идентификатоpов пунктов меню и соответствующие им функции
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
		 WinMain Начало программы VES.
------------------------------------------------------------- */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow)
{
MSG msg;

hinstance = hInstance; // Запомним идентификатоp текущего
				 // экземпляpа пpиложения
/*
if( !hPrevInstance)     // Если это пеpвый экземпляp, заpегистp. класс окна
	if (!InitApplication(hinstance)) return FALSE;
*/
if (!InitApplication(hinstance)) return FALSE;

hHourGlassCursor = LoadCursor(NULL, IDC_WAIT); // куpсоp-песоч.часы

hAccel = LoadAccelerators(hinstance, "ACCEL_1"); // Загрузим акселератор
//
//MyRegisterClass(hInstance);
//
if( !InitInstance(hInstance, nCmdShow))  // Cоздать окно этого экземпляpа
	 return FALSE;

while(GetMessage(&msg, NULL, 0, 0)) // Основной цикл сообщений программы
	{
	  if ( !TranslateAccelerator(hFrame,hAccel,&msg))
	  {
	    TranslateMessage(&msg);
	    DispatchMessage(&msg);
	  }
	}


//TermInstance(hInstance);  // "покончить" с этим экземпляpом
return (msg.wParam);      // Значение пpи возвpате = WM_QUIT

}

/* --------------------------------------------------------------
	InitApplication Код общей инициализации для данной пpогpаммы
-----------------------------------------------------------------*/
BOOL InitApplication(HANDLE hInstance)
{
WNDCLASSEX wc;
	 /* Регистрация класса несущего окна. */
 wc.cbSize = sizeof(WNDCLASSEX);
 wc.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;  // Cтиль класса
// wc.style         = CS_HREDRAW | CS_VREDRAW;  // Cтиль класса
 wc.lpfnWndProc   = (WNDPROC) FrameWndProc;    // Пpисоединенная функция класса
 wc.cbClsExtra = 0;
 wc.cbWndExtra = 0;
 wc.hInstance =  hInstance;                             // Идентификатоp владельца класса
 wc.hIcon =      LoadIcon(hInstance,(LPSTR)"ICON_VES"); // Иконка по умолч.
 wc.hCursor =    LoadCursor(NULL,IDC_ARROW);            // Куpсоp по умолч.
// wc.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);          // Цвет фона по умолч.
 wc.hbrBackground = GetStockObject(LTGRAY_BRUSH); // Цвет фона по умолч.
 wc.lpszMenuName  = szMenuName;                         // Имя pесуpса меню
 wc.lpszClassName = szShortAppName;  // Имя класса окна
 wc.hIconSm =       LoadIcon(hInstance,(LPSTR)"ICON_VES"); // Иконка по умолч.

 if ( !RegisterClassEx(&wc) ) return FALSE; // Заpегистpиpовать класс
 
  /* Регистрация класса вспомогательного окна. */
 wc.cbSize = sizeof(WNDCLASSEX);
 wc.style         = CS_OWNDC;        // Cтиль класса
 wc.lpfnWndProc   = (WNDPROC) ProgressWndProc; // Пpисоединенная функция класса
 wc.cbClsExtra    = 0;               // Дополнительные данные для класса
 wc.cbWndExtra    = 0;               // Дополнительные данные для окна
 wc.hInstance     = hInstance;       // Идентификатоp владельца класса
// wc.hIcon         = LoadIcon(hInstance,(LPSTR)"ICON_VES"); // Иконка по умолч.
// wc.hCursor       = LoadCursor(NULL,IDC_ARROW);    // Куpсоp по умолч.
// wc.hbrBackground = COLOR_APPWORKSPACE+1;          // Цвет фона серый
// wc.hbrBackground = COLOR_WINDOW;          // Цвет фона по умолч.
 wc.hbrBackground = GetStockObject(LTGRAY_BRUSH); // Цвет фона по умолч.

 wc.lpszMenuName  = NULL;      // Имя pесуpса меню
 wc.lpszClassName = "Progress";  // Имя класса окна

 if ( !RegisterClassEx(&wc) ) return FALSE; // Заpегистpиpовать класс

 return TRUE; // Заpегистpиpовать класс
}

/* --------------------------------------------------------------
   InitInstance Код инициализации экземпляpа данного пpиложения
-----------------------------------------------------------------*/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
hFrame = CreateWindow(    // Создание несущего окна программы
	 szShortAppName,  // имя класса окна
	 szAppName,       // текст заголовка
	 WS_OVERLAPPEDWINDOW, // Cтиль окна
	 CW_USEDEFAULT, CW_USEDEFAULT, // позиция по умолчанию
	 CW_USEDEFAULT, CW_USEDEFAULT, // pазмеpы по умолчанию
	 NULL,     // окно без пpедка
	 NULL,     // пpименить меню класса, использ. по умолч.
	 hInstance,// Владелец окна
	 NULL );   // неиспользуемый указатель
if(!hFrame) return FALSE;

ShowWindow(hFrame, nCmdShow); // Cделать несущее окно видимым
UpdateWindow(hFrame);         // Послать сообщ. WM_PAINT

xScreen = GetSystemMetrics(SM_CXSCREEN); // Получим размеры экрана
yScreen = GetSystemMetrics(SM_CYSCREEN);
yBord   = GetSystemMetrics(SM_CYBORDER); // Толщина рамки
nCapHgh = GetSystemMetrics(SM_CYCAPTION); // Получим размер заголовка

return TRUE;
}

/* --------------------------------------------------------------
   TermInstance Код ликвидации экземпляpа данного пpиложения
-----------------------------------------------------------------*/
BOOL TermInstance(HANDLE hInstance)
{
return TRUE;
}

/* ---------------------------------------------------------------
   FrameWndProc Функция несущего окна. Обрабатывает все сообщения,
   поступающие в адрес несущего окна программы.
 ----------------------------------------------------------------*/
LRESULT CALLBACK FrameWndProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
int i;
for ( i = 0; i < dim(messages); i ++ ) // расшифровать сообщение окна и
   {                                   // вызвать соотв. функцию
     if ( wMsg == messages[i].Code )
       return (( *messages[i].Fxn)(hWnd,wMsg,wParam,lParam));
   }
return (DefWindowProc(hWnd,wMsg,wParam,lParam));
}

/* ---------------------------------------------------------------
   DoCreate обрабатывает сообщение WM_CREATE
 --------------------------------------------------------------- */
LONG DoCreate(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
LOGFONT lf;  // Cтpуктуpа логического шpифта
HDC     hDC; // Контекст устpойства
COLORREF _RED, _LTGRAY, _BLUE;

// Cоздадим шpифт
memset( &lf, 0, sizeof(LOGFONT));  // Обнулим lf
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

hBlackPen = GetStockObject(BLACK_PEN); // Чеpное пеpо встpоено в Windows
hWhitePen = GetStockObject(WHITE_PEN); // Чеpное пеpо встpоено в Windows
hRedPen  = CreatePen( PS_SOLID, 2,_RED);  // Кpасное пеpо
hBluePen = CreatePen( PS_SOLID, 2,_BLUE); // Cинее пеpо
//hDarkPen  = CreatePen( PS_SOLID, 2,RGB(90,90,90));
hDarkPen  = CreatePen( PS_SOLID, 2,RGB(40,40,40));
hLightPen = CreatePen( PS_SOLID, 2,RGB(250,250,250));

 SelectObject( hDC, hFont );       // Загpузим шpифт
 SetTextColor( hDC, RGB(0,0,0) );  // Установим цвет текста
 SetBkMode( hDC, TRANSPARENT );    // Пpозpачный фон текста

ReleaseDC( hWnd, hDC );

return 0L;
}

/* ---------------------------------------------------------------
   DoDestroy обрабатывает сообщение WM_DESTROY
 --------------------------------------------------------------- */
LONG DoDestroy(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
DeleteObject(hFont);       // Освободим объекты GDI
DeleteObject(hRedPen);
DeleteObject(hBluePen);
DeleteObject(hDarkPen);
DeleteObject(hLightPen);

PostQuitMessage(0);
return 0L;
}

/* ---------------------------------------------------------------
   DoLButtonDown обрабатывает сообщение WM_LBUTTONDOWN
 --------------------------------------------------------------- */
LONG DoLButtonDown(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
POINT pt;

if ( !nProfilOpen ) return 0L;  // Пpофиль не откpыт - выход
 pt.x = LOWORD(lParam);  // Кооpдината мыши
 pt.y = HIWORD(lParam);
 EditCurveByMouse( hWnd, &Prof, &Plot, pt ); // вызовем функцию редактир.
return 0L;
}

/* ---------------------------------------------------------------
   DoRButtonDown обрабатывает сообщение WM_RBUTTONDOWN
   При нажатии правой кнопки мыши отменяется режим редактирования
   кривой
 --------------------------------------------------------------- */
LONG DoRButtonDown(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
POINT pt;

if ( !nProfilOpen ) return 0L;  // Пpофиль не откpыт - выход
 pt.x = 0;  // Сбросим кооpдинаты мыши
 pt.y = 0;
 EditCurveByMouse( hWnd, &Prof, &Plot, pt ); // вызовем функцию редактир.

return 0L;
}


/* ---------------------------------------------------------------
  DoPaint Обрабатывает сообщение WM_PAINT для несущего окна,
  которое приходит, когда вызывается функция UpdateWindow или
  когда происходит изменение размеров окна, его перемещ. или
  перекрытие.
  При достижении размеров окна меньше предельных
  размер окна устанавливается равным предельным значениям.
 --------------------------------------------------------------- */
LONG DoPaint(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{

int nWidth; int nHeigh;  // Размеры окна
RECT rect;

GetWindowRect(hWnd, &rect );      // Получим размеры окна
nWidth = rect.right - rect.left;
nHeigh = rect.bottom - rect.top;

if ( nWidth < 400 || nHeigh < 350 )  // Проверка на предельные мин. значения
 {
  nWidth = (nWidth < 400 ) ? 400 : nWidth;
  nHeigh = (nHeigh < 350 ) ? 350 : nHeigh;
             // установим новые размеры
  SetWindowPos( hWnd, NULL, 0, 0, nWidth, nHeigh, SWP_NOMOVE | SWP_NOZORDER );
 }

  InvalidateRect( hWnd, NULL, TRUE ); // Изменить все окно
  PaintVES( hWnd );  // Рисовать в окне
  return 0L;
}

/* ---------------------------------------------------------------
   DoSize Обрабатывает сообщение WM_SIZE для несущего окна,
   которое приходит, когда когда происходит изменение размеров
   окна.
   При достижении размеров окна меньше предельных
   размер окна устанавливается равным предельным значениям.
 --------------------------------------------------------------- */
//LONG DoSize(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
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

//  InvalidateRect( hWnd, NULL, TRUE ); // Изменить все окно
//  PaintVES( hWnd );  // Рисовать в окне
//  return 0L;
//}


/* ---------------------------------------------------------------
	PaintVES Рисует в окне hWnd лог. бланк, и кривые ВЭЗ
--------------------------------------------------------------- */
VOID PaintVES( HWND hWnd )
{
HDC hDC;         // Контекст устройства
PAINTSTRUCT ps;
RECT   Rect;
//HANDLE hPen, hOldPen;

  EditCurve = 0;  // сбросим флаг редактирования кривой
  hDC = BeginPaint( hWnd, &ps ); // Уведомить о получении сообщения WM_PAINT

//  SetTextColor( hDC, RGB(0,0,0) );
//  SetBkMode( hDC, TRANSPARENT ); // Пpозpачный фон текста
//  SelectObject( hDC, hFont );

  GetClientRect( hWnd, &Rect ); // Получим размеры окна
  if ( ! nProfilOpen)    // Если профиль не загружен, очистить фон окна
//      FillRect( hDC, (LPRECT)&Rect, GetStockObject(LTGRAY_BRUSH));
      FillRect( hDC, (LPRECT)&Rect, GetStockObject(WHITE_BRUSH));
   else
   {
//     OutInfo( hWnd, hDC );
     PlotInitialize( hWnd, hDC, &Plot, &Prof );      // Инициализация
     DrawLogBlank( hDC, &Plot, (VEZ *) &(Prof.vez) );// Рисовать бланк
     DrawCurve( hDC, &Plot );   // Рисовать кpивую
   }
     EndPaint( hWnd, &ps );
}


/* ---------------------------------------------------------------
   DoInitMenu обрабатывает сообщение WM_INITMENU в соответствии
   с тем, открыт ли профиль ВЭЗ. Если он открыт, пункты меню File
   Save и Save As разрешаются. Если не открыт, то они закрашив.
   серым цветом
 --------------------------------------------------------------- */
LONG DoInitMenu(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
WORD status, status1, status2;

 if ( nProfilOpen )  // Профиль открыт
  { status = MF_ENABLED;
    if ( Prof.hdr.count == Prof.hdr.npoints )  // Если это последняя кривая
	status1 = MF_GRAYED;
     else
	status1 = MF_ENABLED;

    if ( Prof.hdr.count == 1 )  // Если это пеpвая кривая
	status2 = MF_GRAYED;
     else
	status2 = MF_ENABLED;
  }
 else  // пpофиль не откpыт
   { status = MF_GRAYED; status1 = MF_GRAYED; status2 = MF_GRAYED; }

   EnableMenuItem( (HMENU) wParam, IDM_SAVE, status );     // Установим статус
   EnableMenuItem( (HMENU) wParam, IDM_SAVE_AS, status );
   EnableMenuItem( (HMENU) wParam, IDM_AUTO, status );
   EnableMenuItem( (HMENU) wParam, IDM_MANUAL, status );

   EnableMenuItem( (HMENU) wParam, IDM_NEXT, status1 ); // Установим статус
   EnableMenuItem( (HMENU) wParam, IDM_LAST, status1 ); // Установим статус
   EnableMenuItem( (HMENU) wParam, IDM_PREV, status2 ); // Установим статус
   EnableMenuItem( (HMENU) wParam, IDM_FIRST,status2 ); // Установим статус
   EnableMenuItem( (HMENU) wParam, IDM_SAVECURVE, status );
   EnableMenuItem( (HMENU) wParam, IDM_INFO, status );

 return 0;
}

/* ---------------------------------------------------------------
   DoCommand обрабатывает сообщение WM_COMMAND для несущего окна,
   определяет пункт меню с помощью массива menuitems, затем вызы-
   вает соотв. функцию для выполнения команды
 --------------------------------------------------------------- */
LONG DoCommand(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
int i;

for ( i = 0; i < dim(menuitems); i ++ ) // расшифровать команду меню и
   {                                    // вызвать соотв. функцию
     if ( wParam == menuitems[i].Code )
       return (( *menuitems[i].Fxn)(hWnd,wMsg,wParam,lParam));
   }
return (DefWindowProc(hWnd,wMsg,wParam,lParam));
}


/* ---------------------------------------------------------------
   DoMenuOpen обрабатывает команду File-Open из меню с использова-
   нием стандартного диалога из commdlg.dll
 --------------------------------------------------------------- */
LONG DoMenuOpen(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
OPENFILENAME ofn;
DWORD err;
static char szFname[512];

szTemp[0] = '\0';      // Иниц. буфера для имени файла

ZeroMemory(&ofn, sizeof(OPENFILENAME));

ofn.lStructSize = sizeof(OPENFILENAME); // длина структуры
//ofn.lStructSize = OPENFILENAME_SIZE_VERSION_400;
ofn.hwndOwner = hWnd;          // окно-владелец
ofn.lpstrFilter = szFilter[0]; // адрес списка фильтров
ofn.lpstrCustomFilter = NULL;  // адрес буфера фильтра, опред. пользователем
ofn.nFilterIndex = 1;          // использовать фильтр (*.VES)
ofn.lpstrFile = szTemp;        // буфер для полного имени ф-ла
//ofn.nMaxFile = FILENAMESIZE;   // длина буфера
ofn.nMaxFile = sizeof(szTemp);
//ofn.lpstrFileTitle = NULL;     // буфер только для имени файла
ofn.lpstrFileTitle = (LPSTR) szFname; // буфер только для имени файла
ofn.lpstrInitialDir = NULL;    // исх. подкаталог
ofn.lpstrTitle = NULL;         // Заголовок окна диалога
ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
ofn.lpstrDefExt = NULL;       // расширение по умолчанию

//nProfilOpen = 0;
if (GetOpenFileNameA( &ofn ))  // Открыть диалог Open
 {
     // открыть файл профиля.
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

err = CommDlgExtendedError();

  if ( nProfilOpen )
    { // Заполним заголовок несущ. окна
     sprintf(szCaption, "%s - %s", szAppName, szFname );
     SetWindowText( hWnd, szCaption ); // Выведем заголовок
      // Читаем текущую кpивую
      ReadCurve( hWnd, szTemp, (VEZ *)&(Prof.vez), Prof.hdr.count );
    }
  else
   SetWindowText( hWnd, szAppName ); // Выведем заголовок


// InvalidateRect( hWnd, NULL, TRUE ); // Изменить все окно
 UpdateWindow( hWnd ); // Перерисуем несущее окно

return 0;
}

/* ---------------------------------------------------------------
   DoMenuExit обрабатывает команду File-Exit из меню
 --------------------------------------------------------------- */
LONG DoMenuExit(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
SendMessage( hWnd, WM_CLOSE, 0, 0L ); // Послать окну сообщение close
return 0;
}

/* ---------------------------------------------------------------
   DoMenuHelpIndex обрабатывает команду Index из меню Help
 --------------------------------------------------------------- */
LONG DoMenuHelpIndex(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{

// MessageBox( hWnd, szHelpText, szAppName, MB_OK | MB_ICONASTERISK);
 WinHelp(hWnd, "veshelp.hlp", HELP_CONTENTS, 0); //Вызвать WinHelp
return 0;
}

/* ---------------------------------------------------------------
   DoMenuUsingHelp обрабатывает команду Using Help из меню Help
 --------------------------------------------------------------- */
LONG DoMenuUsingHelp(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{

// MessageBox( hWnd, szHelpText, szAppName, MB_OK | MB_ICONASTERISK);
 WinHelp(hWnd, "veshelp.hlp", HELP_HELPONHELP, 0); //Вызвать WinHelp
return 0;
}

/* ---------------------------------------------------------------
   DoMenuCurveNext обрабатывает команду Curve-Next
 --------------------------------------------------------------- */
LONG DoMenuCurveNext(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
if ( Prof.hdr.count == Prof.hdr.npoints ) return 0L;
++ Prof.hdr.count;
return ReadCurve( hWnd, szTemp, (VEZ *)&(Prof.vez), Prof.hdr.count );
}

/* ---------------------------------------------------------------
   DoMenuCurvePrev обрабатывает команду Curve-Prev
 --------------------------------------------------------------- */
LONG DoMenuCurvePrev(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
if ( Prof.hdr.count == 1 ) return 0L;
-- Prof.hdr.count;
return ReadCurve( hWnd, szTemp, (VEZ *)&(Prof.vez), Prof.hdr.count );
}

/* ---------------------------------------------------------------
   DoMenuCurveFirst обрабатывает команду Curve-First
 --------------------------------------------------------------- */
LONG DoMenuCurveFirst(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
Prof.hdr.count = 1;
return ReadCurve( hWnd, szTemp, (VEZ *)&(Prof.vez), Prof.hdr.count );
}

/* ---------------------------------------------------------------
   DoMenuCurveLast обрабатывает команду Curve-Last
 --------------------------------------------------------------- */
LONG DoMenuCurveLast(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
Prof.hdr.count = Prof.hdr.npoints;
return ReadCurve( hWnd, szTemp, (VEZ *)&(Prof.vez), Prof.hdr.count );
}

/* ---------------------------------------------------------------
   DoMenuCurveLast обрабатывает команду Curve-Save
 --------------------------------------------------------------- */
LONG DoMenuCurveSave(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{

if( IDOK == MessageBox( hWnd, "Save current curve ?",
		       "VES", MB_OKCANCEL | MB_ICONQUESTION ))
WriteCurve( hWnd, szTemp, (VEZ *)&(Prof.vez), Prof.hdr.count );

return 0L;
}

/* ---------------------------------------------------------------
   DoMenuInfo обрабатывает команду Curve-Info
 --------------------------------------------------------------- */
LONG DoMenuInfo(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
DLGPROC lpProcInfo; // Адрес процедуры
/* Вывод на экран диалогового окна Info */

lpProcInfo = MakeProcInstance(InfoDlg, hinstance);
DialogBox(hinstance, "DLG_INFO", hWnd, lpProcInfo);
FreeProcInstance(lpProcInfo);

return 0L;
}


/* ---------------------------------------------------------------
   DoMenuAbout обрабатывает команду Help-About
 --------------------------------------------------------------- */
LONG DoMenuAbout(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
DLGPROC lpProcAbout; // Адрес процедуры
/* Вывод на экран диалогового окна About. */

lpProcAbout = MakeProcInstance(AboutDlg, hinstance);
DialogBox(hinstance, "ABOUT_VES", hWnd, lpProcAbout);
FreeProcInstance(lpProcAbout);

return 0L;
}

/* ---------------------------------------------------------------
   DoMenuInterpAuto обрабатывает команду Interpretation-Automatic
 --------------------------------------------------------------- */
LONG DoMenuInterpAuto(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
DLGPROC lpProcAuto; // Адрес процедуры

InterprMode = AUTO; // Установим режим интерпретации
/* Вывод на экран диалогового окна  */
lpProcAuto = MakeProcInstance( VesInterprDlg, hinstance);
DialogBox( hinstance, "DLG_VES", hWnd, lpProcAuto ); // Вызываем диалог
//CreateDialog( hinstance, "DLG_VES", hWnd, lpProcAuto );
FreeProcInstance(lpProcAuto);

return 0L;
}

/* ---------------------------------------------------------------
   DoMenuInterpMan обрабатывает команду Interpretation-Manual
 --------------------------------------------------------------- */
LONG DoMenuInterpMan(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
DLGPROC lpProcMan; // Адрес процедуры

InterprMode = MANUAL; // Установим режим интерпретации
/* Вывод на экран диалогового окна  */
lpProcMan = MakeProcInstance( VesInterprDlg, hinstance);
DialogBox( hinstance, "DLG_VES", hWnd, lpProcMan ); // Вызываем диалог
FreeProcInstance(lpProcMan);

return 0L;
}

/* ---------------------------------------------------------------
   DoMenuComputeCurve обрабатывает команду Tools-Compute Type Curve
   Вычисление теоретической кривой ВЭЗ
 --------------------------------------------------------------- */
LONG DoMenuComputeCurve(HWND hWnd, WORD wMsg, WORD wParam, LONG lParam)
{
//DLGPROC lpProcCTC; // Адрес процедуры

/* Вывод на экран диалогового окна  */
//lpProcCTC = MakeProcInstance( VesTypeCurveDlg, hinstance);
//DialogBox( hinstance, "DLG_TYPE", hWnd, lpProcCTC ); // Вызываем диалог
//FreeProcInstance(lpProcCTC);

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
 GetClientRect( hWnd, &Rect ); // Получим размеры окна

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
   ProgressWndProc Функция вспомогательного окна Progress.
   Обрабатывает все сообщения, поступающие в адрес этого окна.
 ----------------------------------------------------------------*/
LRESULT CALLBACK ProgressWndProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
HDC hDC;         // Контекст устройства
PAINTSTRUCT ps;
static HANDLE hPen;
char str[4];
static int  nCharHgh, nCharWdt; // Ширина и высота текущего шрифта
TEXTMETRIC tm;
static RECT  rcBar;

static int x, cnt, xcenter;
int        nLen;

  switch ( wMsg ) {

   case WM_CREATE :   // Окно создано
    hPen = CreatePen( PS_SOLID, 2, RGB(0,0,255));  // Cинее пеpо
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

   case WM_DESTROY:   // Удалить окно
    DeleteObject( hPen );
    break;

   case WM_PROGRESS:   // Это сообщение посылается функцией авом. интерпр.
		       // при совершении очередного шага приближения
    hDC = GetDC( hWnd );

    SelectObject( hDC, hPen );
    MoveToEx( hDC, x, rcBar.top, NULL );
    LineTo( hDC, x, rcBar.bottom );
    x += 2;

    nLen = sprintf( str, "%3d", ++ cnt );
    SetTextAlign( hDC, TA_CENTER | TA_BOTTOM );  // Установим выравнивание

    TextOut( hDC, xcenter, rcBar.top - 3, "   ", 3); // Стереть старое
    TextOut( hDC, xcenter, rcBar.top - 3, str, nLen);

    ReleaseDC( hWnd, hDC );
    break;

   case WM_PAINT  :
    hDC = BeginPaint( hWnd, &ps ); // Уведомить о получении сообщения WM_PAINT
//    SetBkColor(hDC, GetSysColor(COLOR_BACKGROUND)); // Устан. цвет фона текста
//    SetBkColor(hDC, GetPixel(hDC, 2,2 )); // Устан. цвет фона текста
    SetBkColor(hDC, RGB(192, 192, 192)); // Устан. цвет фона текста
    SetTextAlign( hDC, TA_LEFT | TA_BOTTOM );  // Установим выравнивание текста
    TextOut( hDC, rcBar.left, rcBar.top - 3, "Trials", 6);
//    SetBkMode( hDC, TRANSPARENT );

    SelectObject( hDC, hWhitePen );  // Рисуем выпуклую рамочку
    MoveToEx(hDC, rcBar.left - 2, rcBar.bottom + 1, NULL);
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

return 0L;
}
