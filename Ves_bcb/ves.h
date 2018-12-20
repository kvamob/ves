//---------------------------------------------------------------------------
#ifndef vesH
#define vesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>

#include <SysUtils.hpp>
#include <IniFiles.hpp>
#include <Shellapi.hpp>  // Drag-n-Drop

#include "ves_win.h"
#include <ImgList.hpp>


//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu;
    TMenuItem *File;
    TMenuItem *Curve;
    TMenuItem *Interpret;
    TMenuItem *Tools;
    TMenuItem *Help;
    TMenuItem *FileNew;
    TMenuItem *FileOpen;
    TMenuItem *FileSave;
    TMenuItem *FileSaveAs;
    TMenuItem *FileExit;
    TMenuItem *CurveNext;
    TMenuItem *CurvePrev;
    TMenuItem *CurveFirst;
    TMenuItem *CurveLast;
        TMenuItem *N2;
    TMenuItem *CurveSave;
        TMenuItem *N4;
    TMenuItem *CurveInfo;
    TMenuItem *InterpretManual;
    TMenuItem *InterpretAuto;
    TMenuItem *ToolsSolve;
    TMenuItem *ToolsCompile;
    TMenuItem *HelpIndex;
    TMenuItem *UsingHelp;
        TMenuItem *N6;
    TMenuItem *HelpAbout;
        TMenuItem *N1;
    TOpenDialog *OpenDialog;
    TStatusBar *StatusBar;
    TTreeView *TreeView;
    TSplitter *Splitter;
    TPanel *Panel1;
    TPaintBox *PaintBox;
    TSaveDialog *SaveDialog;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TImageList *ImageList1;
    TToolBar *ToolBar;
    TToolButton *NewFileToolButton;
    TToolButton *OpenFileToolButton;
    TToolButton *FileSaveToolButton;
    TToolButton *PrintToolButton;
    TToolButton *FirstCrvToolButton;
    TToolButton *PrevCrvToolButton;
    TToolButton *NextCrvToolButton;
    TToolButton *LastCrvToolButton;
    TToolButton *EditToolButton;
    TToolButton *AutoIntToolButton;
    TToolButton *ManIntToolButton;
    TToolButton *CalcModelToolButton;
    TToolButton *HelpToolButton;
    TToolButton *ExitToolButton;
    TImageList *ImageList2;
    TToolButton *ToolButton2;
    TToolButton *ToolButton3;
    TToolButton *ToolButton4;
    TToolButton *ToolButton1;
    TToolButton *ToolButton5;
        TPopupMenu *TVPopupMenu;
        TMenuItem *RenamePopUp;
        TMenuItem *InfoPopUp;
        TMenuItem *CurvePrint;
        TMenuItem *N3;
        TMenuItem *View;
        TMenuItem *ViewToolBar;
        TMenuItem *ViewStatusBar;
        TToolButton *ToolButton6;
        TToolButton *ToolButton7;
    void __fastcall HelpAboutClick(TObject *Sender);
    void __fastcall FileExitClick(TObject *Sender);
    void __fastcall FileOpenClick(TObject *Sender);
    void __fastcall ToolsSolveClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall CurveInfoClick(TObject *Sender);
    void __fastcall TreeViewMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall CurveFirstClick(TObject *Sender);
    void __fastcall CurveLastClick(TObject *Sender);
    void __fastcall CurveNextClick(TObject *Sender);
    void __fastcall CurvePrevClick(TObject *Sender);
    void __fastcall FileSaveClick(TObject *Sender);
    void __fastcall TreeViewChange(TObject *Sender, TTreeNode *Node);
    void __fastcall InterpretManualClick(TObject *Sender);
    
    void __fastcall ToolButton1Click(TObject *Sender);
        void __fastcall RenamePopUpClick(TObject *Sender);
        void __fastcall ViewToolBarClick(TObject *Sender);
        void __fastcall ViewStatusBarClick(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
// ############################################################
/* ------------------ �������H�� ������HH�� --------------------- */
//HANDLE  hinstance;             // ������������p ��������p� ������
//HWND    hFrame;                // ������������p �������� ���� (����-p����)
//HWND    hProgress;             // ������������p �������. ����
//HWND    hwndPlot;              // ������������p ���� � p�������
//int     xScreen, yScreen;      // ������ � ������ ������ � ��������
//int     nCapHgh;               // ������ ��������� ���� - ��� ��������� ��������
			       // ���������������� ����
//int     yBord;                 // ������� ����� ���� �� ���������

TFileName CurrFileName;     // ��� �������� �����
//char szFileNameBin[FILENAMESIZE+1]; // ��� �������� ��������� ����� VEZ-�������
//char szTemp[FILENAMESIZE+1];        // ����� ��� �������� ����� �����

//HANDLE  hIconVES;      // ������ VES
int     hVEZBinFile; // ����p����p ��������� ����� ��p���� VEZ
int     nProfilOpen; // ������� �������� ����� ������� (1 - ������, 0 - ���
int     EditCurve;   // �p����� p������p������ �p����

PROFIL  Prof;          // ������� ���
VES_PAINTDATA Plot;    // ������ ��� ����p����� �p������
int     InterprMode;   // ����� ������������� - ������ ��� ���������.

//HPEN hBlackPen,        // ��p� ���p������ � Windows
//     hWhitePen,
//     hDarkPen,         // ����� ��� ���������� � ���������� �����
//     hLightPen,
//     hBluePen,         // ��� p�������� ����������� �p����
//     hRedPen;          // ��� p�������� ���p��������� �p����

//HANDLE hFont;          // ���������� ������
//HANDLE hAccel;         // ���������� ����������

//char szShortAppName[]  = "VES"; // �p����� ��� �p��������
//char szAppName[]       = "Vertical Electric Sounding"; // ������ ���
//char szMenuName[]      = "MENU_VES"; // ��� p���p�� ����
//char szDefName[]       = "Untitled"; // ��� ����� �� ���������
//char szDefExt[]        = "ves";      // p����p���� ����� �� ���������
//"in Beta-version of this Application";
//char szCaption[100];         // ����� ��� ��������� �������� ����

   AnsiString       sProgramFilePath; // ���� � ��������, � ������� ���������
                                      // ����������
   TIniFile         *pVES4WinIni;     // ������ ��� ������ � INI-������                                       
// ############################################################
// ----- ������ �����-������ ------------------------------
    int __fastcall  OpenProfil( System::AnsiString fname, PROFIL *prof );
    int __fastcall  WriteProfilHeader( AnsiString fname, PROFIL *prof );
    int __fastcall  ReadCurve( AnsiString fname, VEZ *vez , int cnt );
    int __fastcall  WriteCurve( AnsiString fname, VEZ *vez , int cnt );
    void __fastcall CloseProfil( PROFIL *prof );
    void __fastcall FillDefData( VEZ *vez );
// --------------------------------------------------------
    void __fastcall EnableMenuItems( bool value ); // �������� ��-�� Enable �
                                                   // ���. ����. ����
    void __fastcall HandleDropFiles( TMessage& Msg ); // ����������
                                                      // ��������� WM_DROPFILES

public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);
    void __fastcall DisplayHint(TObject* Sender);  // ����������� �� ������ ���������
                                                   // ��������� ����
                // ����� ���������
BEGIN_MESSAGE_MAP
MESSAGE_HANDLER(WM_DROPFILES, TMessage, HandleDropFiles );
END_MESSAGE_MAP(TForm)

};

//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
