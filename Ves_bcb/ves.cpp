//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>

#pragma hdrstop
// #pragma pack(2)

#include "ves.h"
#include "about.h"
#include "modelfrm.h"
#include "infofrm.h"
#include "interpr.h"
#include "ednamfrm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------

// --------------------------------------------------------------------------
// ����������� ������ ����������
// --------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
  nProfilOpen=0; // ������� �������� ����� ������� (1 - ������, 0 - ���
  EditCurve = 0; // �p����� p������p������ �p����
  Application->OnHint = DisplayHint; // ������������� ����������
}

// ------------------------------------------------------------------
// ---  ���������� OnHint                                         ---
// ------------------------------------------------------------------
void __fastcall TMainForm::DisplayHint(TObject* Sender)
{
  ViewToolBar->Hint =
   (ViewToolBar->Checked) ? "������ ������ ������������" :
                            "���������� ������ ������������";
  ViewStatusBar->Hint =
   (ViewStatusBar->Checked) ? "������ ������ ���������" :
                            "���������� ������ ���������";

  StatusBar->Panels->Items[2]->Text = Application->Hint;
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::HelpAboutClick(TObject *Sender)
{
	AboutForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileExitClick(TObject *Sender)
{
  Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileOpenClick(TObject *Sender)
{
//TFileName CurrFileName;     // ��� �������� �����

if (OpenDialog->Execute())  // ���� ��� ������
 {
  CurrFileName = OpenDialog->FileName;
  Caption = "������������� ������ ��� - " + CurrFileName;

  if ( OpenProfil(CurrFileName, &Prof ) == 0);  // ������� �������
  {
    // �������� ��������� ������ ����
    EnableMenuItems( true );

    // -----------------------------------------------
    // � ����� �������� TreeView ���������� �����
    // �������� ������� � ����� ����� ���
    TTreeNode *ProfNode; // �������� ���� - ��� �������
    TreeView->Items->Clear(); // ������� ������
//      TreeView->Items->Add(NULL, "�������: 1-� ��������"); // ������� ������
    String str = Prof.hdr.profname;
    str = "������� : " + str;
    TreeView->Items->Add(NULL, str ); // ������� ������
    ProfNode = TreeView->Items->Item[0]; // ��������� �� ������
    ProfNode->ImageIndex = 1;
// ������� ��� ������������ ������� � �������� ���� TreeView
//      TreeView->Items->Item[0]->Text = "�������: 1-� ��������";
    int i;
    TTreeNode* pItem;
    for ( i = 0; i < Prof.hdr.npoints; i ++ )
     {
      if (ReadCurve( CurrFileName, (VEZ *) &Prof.vez , i ) == 0)
       {
        pItem = TreeView->Items->AddChild( ProfNode, Prof.vez.ID_curve );
        if ( Prof.vez.model.n > 0 )   // ������ ������������������� ?
           pItem->ImageIndex = 3; // �������� ������
        else
           pItem->ImageIndex = 2; // �������� ������
       }
       else
       { // �� ������ ��������� ������
         TreeView->Items->Clear(); // ������� ������
         TreeView->Items->Add(NULL, "�������: [�� ��������]"); // ������� ������
         EnableMenuItems( false ); // �������� � ���� ���-���
         break;
       }
    }

          // "��������" ������
   TreeView->FullExpand();
          // ������� ������ ������ - ��� �������
   TreeView->Selected = TreeView->Items->GetFirstNode();
//      TreeView->Selected->ImageIndex = 1;
          // ������� ������ ������ �� �������
// *** ��� ��� ���������� � TreeViewChange ***
//      TTreeNode* CurrNode = TreeView->Selected->GetNext();
//      if (CurrNode) TreeView->Selected = CurrNode;
          // ������� TreeView ��������
   MainForm->ActiveControl = TreeView;

      // -----------------------------------------------
   } // if OpenProfil
 }
 else //###### ���� �� ������� #########
 {
  TreeView->Items->Clear(); // ������� ������
  TreeView->Items->Add(NULL, "������� [�� ��������]"); // ������� ������
  EnableMenuItems( false ); // �������� � ���� ���-���
 }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ToolsSolveClick(TObject *Sender)
{
   ModelCrvForm->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FormCreate(TObject *Sender)
{
AnsiString  IniFileName;  // ��� Ini-�����

 sProgramFilePath = ExtractFilePath(ParamStr(0)); // ������ �������
 IniFileName = sProgramFilePath + "VES4Win.ini";

// =========================================================================
  // ������ TIniFile, ����� ������ � ����������� FormDestroy
 pVES4WinIni = new TIniFile (IniFileName);
 // ... ����� ����� ��������� ��������� ��������� ���������
 //
 if ( pVES4WinIni->ReadBool("Options", "ShowToolBar", false) == false)
   { ToolBar->Visible = false;
     ViewToolBar->Checked = false;
   }
 if (pVES4WinIni->ReadBool("Options", "ShowStatusBar", false) == false)
   { StatusBar->Visible = false;
     ViewStatusBar->Checked = false;
   }
// =========================================================================

 OpenDialog->InitialDir = sProgramFilePath;
 SaveDialog->InitialDir = sProgramFilePath;
  // ������� �������, ��� ���� ���������� ��������� ������������
  // ������� drag-n-drop �����
 DragAcceptFiles( Handle, TRUE );
// ============================================================
 int i = ParamCount(); // ���-�� ���������� � ��������� ������
 if ( i > 0 ) MainForm->Caption = ParamStr(1); // ����
 // ����� ���� �������� ����� �������� ������� �  �������� ������!
// ============================================================

 }

// ---------------------------------------------------------------------
// �������, �������������� ��������� WM_DROPFILES - ��� ���������, �����
// �� ���� ��������� ������� drag-and-drop ��������� �����
// ---------------------------------------------------------------------
void __fastcall TMainForm::HandleDropFiles(TMessage& Msg)
{
HDROP hDropInfo = (HANDLE)Msg.WParam; // ���������� � ������������
char szFileName[MAX_PATH];

     // ���-�� ������
int  nFiles = DragQueryFile(hDropInfo, (DWORD)-1, (LPSTR)NULL, 0);
     // ����� ������ ������ ����
DragQueryFile(hDropInfo, 0, szFileName, MAX_PATH);
Application->MessageBox(szFileName, "TEST", IDOK );
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CurveInfoClick(TObject *Sender)
{
   InfoForm->ShowModal();
}
//---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// ���������� ������ ���� � ���� TreeView
// ---------------------------------------------------------------------------
void __fastcall TMainForm::TreeViewMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  // ���� �������� ����� �� �� �������� ����
if (TreeView->Selected != TreeView->Items->Item[0])
 {   // ����
//     Label1->Caption = StrToInt(TreeView->Selected->Index); // ����� ����
   Label1->Caption = TreeView->Items->Item[0]->Text; // ��� �������
   Label2->Caption = TreeView->Selected->Text; // ��� ������

 }
}
//---------------------------------------------------------------------------
// ������� ������ �������� Enable ��������� ������� ����
// � ������ �� ������
// value - ��������, ������� ������������� ����� ��������
//--------------------------------------------------------
void __fastcall TMainForm::EnableMenuItems( bool value)
{
    // ������ ����
    CurveNext->Enabled = value;
    CurvePrev->Enabled = value;
    CurveFirst->Enabled = value;
    CurveLast->Enabled = value;
    CurveSave->Enabled = value;
    CurveInfo->Enabled = value;
    InterpretManual->Enabled = value;
    InterpretAuto->Enabled = value;
    FileSave->Enabled = value;
    FileSaveAs->Enabled = value;
    // PopUp menu
    RenamePopUp->Enabled = value;
    InfoPopUp->Enabled = value;

    // ������� ������
    FirstCrvToolButton->Enabled = value;
    PrevCrvToolButton->Enabled = value;
    NextCrvToolButton->Enabled = value;
    LastCrvToolButton->Enabled = value;
    AutoIntToolButton->Enabled = value;
    ManIntToolButton->Enabled = value;
    FileSaveToolButton->Enabled = value;
}

//---------------------------------------------------------------------------

// --------------------------------------------------------------------------
// ����� ������ ������ �� �������
// --------------------------------------------------------------------------
void __fastcall TMainForm::CurveFirstClick(TObject *Sender)
{
   // "��������" ������
 TreeView->FullExpand();
   // ������� ������ ������ - ��� �������
 TreeView->Selected = TreeView->Items->GetFirstNode();
   // ������� ������ ������ �� �������
 TTreeNode* CurrNode = TreeView->Selected->GetNext();
 if (CurrNode) TreeView->Selected = CurrNode;

   // ������� TreeView ��������
 MainForm->ActiveControl = TreeView;

}
//---------------------------------------------------------------------------

// --------------------------------------------------------------------------
// ����� ��������� ������ �� �������
// --------------------------------------------------------------------------
void __fastcall TMainForm::CurveLastClick(TObject *Sender)
{
   // "��������" ������
 TreeView->FullExpand();
   // ������� ������ ������ - ��� �������
 TreeView->Selected = TreeView->Items->GetFirstNode();

   // ������� ��������� ������ �� �������
 TTreeNode *CurItem = TreeView->Items->GetFirstNode();
 while (CurItem)
  {
   CurItem = CurItem->GetNext();
   if ( CurItem )  TreeView->Selected = CurItem;
  }

   // ������� TreeView ��������
 MainForm->ActiveControl = TreeView;
}
//---------------------------------------------------------------------------


// --------------------------------------------------------------------------
// ����� ��������� ������ �� �������
// --------------------------------------------------------------------------
void __fastcall TMainForm::CurveNextClick(TObject *Sender)
{
   // "��������" ������
 TreeView->FullExpand();
   // ������� ������ ������ - ��� �������
// TreeView->Selected = TreeView->Items->GetFirstNode();
   // ������� ��������� ������ �� �������
 TTreeNode* NextNode = TreeView->Selected->GetNext();
 if (NextNode) TreeView->Selected = NextNode;

   // ������� TreeView ��������
 MainForm->ActiveControl = TreeView;
}

//---------------------------------------------------------------------------

// --------------------------------------------------------------------------
// ����� ���������� ������ �� �������
// --------------------------------------------------------------------------
void __fastcall TMainForm::CurvePrevClick(TObject *Sender)
{
   // "��������" ������
 TreeView->FullExpand();
// ������� ������ ������ - ��� �������
// TreeView->Selected = TreeView->Items->GetFirstNode();
   // ������� ������ ������ �� �������
 TTreeNode* FirstNode = TreeView->Items->GetFirstNode();
 TTreeNode* PrevNode = TreeView->Selected->GetPrev();
 if (PrevNode && PrevNode != FirstNode) TreeView->Selected = PrevNode;

   // ������� TreeView ��������
 MainForm->ActiveControl = TreeView;

}
//---------------------------------------------------------------------------



void __fastcall TMainForm::FileSaveClick(TObject *Sender)
{
int iFileHandle;
char *str = "Test";

if ( SaveDialog->Execute() )
 {
  iFileHandle = FileCreate( SaveDialog->FileName);
  FileWrite( iFileHandle, str, 4);
  FileClose( iFileHandle );
 };

}
//---------------------------------------------------------------------------

// ##########################################################################
// ������ �����-������ �� ������ ����. �������
// ##########################################################################

/* ----------------------------------------------------------------
   OpenProfil ��������� ���� �������, ��� �������� ������� �
   ������ fname, ��������� ���� �� ������������ � ���������
   ����� ��������� prof. ����� ��������� ������ ���.
   ���� �����������.
   ��� �������� ���������� ���������� 0, ��� ������ - ��� ������.
-------------------------------------------------------------------*/
int __fastcall TMainForm::OpenProfil( System::AnsiString fname, PROFIL *prof )
{
int status;
int Cc = 0;
int hFile;

  // ������� ��� ������
 hFile = Sysutils::FileOpen(fname, fmOpenRead);
 if ( hFile == -1 )
 {
  nProfilOpen = 0;
  Application->MessageBox("�� ���� ������� ����!","�������� �������", IDOK );
  return F_NOT_OPEN;
 }
  // ������ ���������
 status = FileRead( hFile, (LPSTR) &(prof->hdr), sizeof(HEADER));
 if ( status != sizeof(HEADER))
 {
  nProfilOpen = 0;
  Application->MessageBox("������ ������ ���������!","�������� �������", IDOK );
  return F_READ_ERR;
 }

  // ��������
 if ( lstrcmp( prof->hdr.signat, B_SIGNATURE )) // �� ������. �������
  {
  if ( 0 == _fstrncmp( prof->hdr.signat, T_SIGNATURE, 7 ) )
     Cc = F_TEXT_VEZ;   // ��������� ���-����
  else
     Cc = F_NOT_VEZ;    // ������ �� ���-����
  }
  else // ��� ��, ��� ����
  {
   OemToAnsi(prof->hdr.areaname,prof->hdr.areaname ); // �����������
   OemToAnsi(prof->hdr.profname,prof->hdr.profname ); // �����������
  }

 FileClose( hFile );
 return Cc;
}

/* ----------------------------------------------------------------
   WriteProfilHeader ���������� ��������� ������� �� ��������� prof
   � �������� VEZ-���� � ������ fname
   ��� �������� ���������� ���������� 0, ��� ������ - ��� ������.
-------------------------------------------------------------------*/
int __fastcall TMainForm::WriteProfilHeader( AnsiString fname, PROFIL *prof )
{
 return 0;
}

/* ----------------------------------------------------------------
  ReadCurve ��������� ������ �� ��������� VEZ-����� � ������ fname,
  ��������� ��������� vez
  cnt - ���������� ����� ������ (�� 0)
  ��� �������� ���������� ���������� 0, ��� ������ - ��� ������.
-------------------------------------------------------------------*/
int __fastcall TMainForm::ReadCurve( AnsiString fname, VEZ *vez , int cnt )
{
int status;
int hFile;
int offs;
char buf[30];
int  Cc = 0;

  // ������� ��� ������
 hFile = Sysutils::FileOpen( fname, fmOpenRead);
 if ( hFile == -1 )
 { nProfilOpen = 0;     // ������� �������
   Application->MessageBox("�� ���� ������� ����!","������ ������ ���", IDOK );
   return F_NOT_OPEN;
 }

 // ���� ������ ������
 offs = ((int) cnt )*sizeof(VEZ) + sizeof(HEADER);
 FileSeek( hFile, offs, 0);

 // ������ ��
 status = FileRead( hFile, (LPSTR) vez, sizeof(VEZ));
 if ( status != sizeof(VEZ))
  { nProfilOpen = 0; // ������� �������
    wsprintf( buf, "������ ������ ������ N %d", cnt );
    Application->MessageBox( (LPSTR)buf, "������ ������ ���", IDOK);
    Cc = F_READ_ERR;  // ������ ������
  }
 else
 {
  if (vez->model.n == 0) FillDefData( vez ); // �������� ������
  OemToAnsi(vez->ID_curve, vez->ID_curve );  // �����������
 }

 FileClose( hFile );
 MainForm->Update();

 return Cc;
}


/* ----------------------------------------------------------------
  WriteCurve ���������� ������ �� ��������� VEZ � �������� VEZ-����
  � ������ fname
  cnt - ���������� ����� ������ (�� 1)
  ��� �������� ���������� ���������� 0, ��� ������ - ��� ������.
-------------------------------------------------------------------*/
int __fastcall TMainForm::WriteCurve( AnsiString fname, VEZ *vez , int cnt )
{
int status;
int hFile;
int offs;
char buf[30];
int  Cc = 0;

  // ������� ��� ������-������
 hFile = Sysutils::FileOpen( fname, fmOpenReadWrite);
 if ( hFile == -1 )
  {
   nProfilOpen = 0;   // ������� �������
   Application->MessageBox( "�� ���� ������� ����!", "������ ������ ���", IDOK );
   return F_NOT_OPEN;
  }

 AnsiToOem(vez->ID_curve, vez->ID_curve );  // ����������� ����� �������

 // ���� ������ ������
 offs = ((int) cnt )*sizeof(VEZ) + sizeof(HEADER);
 FileSeek(hFile, offs, 0);

 // ������� ��
 status = FileWrite( hFile, (LPSTR) vez, sizeof(VEZ));
 if ( status != sizeof(VEZ))
   {
     nProfilOpen = 0;
     wsprintf( buf, "������ ������ ������ N %d", cnt );
     Application->MessageBox( (LPSTR)buf, "������ ������ ���", IDOK);
     Cc = F_WRIT_ERR;  // ������ ������
    }
   FileClose( hFile );

 OemToAnsi(vez->ID_curve, vez->ID_curve ); // ����������� �������
 MainForm->Update();

 return Cc;
}


/* ----------------------------------------------------------------
   CloseProfil ��������� ���� ������� �� ��������� prof.
-------------------------------------------------------------------*/
void __fastcall TMainForm::CloseProfil( PROFIL *prof )
{
 return;
}

/* ----------------------------------------------------------------
   FillDefData ��������� ��������� ���� ��������� vez ����������
   �� ��������� (���� � ������ 0 �����)
-------------------------------------------------------------------*/
void __fastcall TMainForm::FillDefData( VEZ *vez )
{
int i;
 for ( i = 0; i < MAX_LAYERS; i ++ )
 {
  vez->model.ro[i] = DEF_RESIST;
 }
 for ( i = 0; i < MAX_LAYERS - 1; i ++ )
 {
  vez->model.h[i] = DEF_THICK;
 }

}

// ##########################################################################
// ����� ������� �����-������
// ##########################################################################

// --------------------------------------------------------------------------
// ��� ��������� �������� ���� ���������� ��������� �������
// --------------------------------------------------------------------------


void __fastcall TMainForm::TreeViewChange(TObject *Sender, TTreeNode *Node)
{
  // ���� �� �������� ����
if (TreeView->Selected != TreeView->Items->Item[0])
 {   // ����
  Label1->Caption = TreeView->Items->Item[0]->Text; // ��� �������
  Label2->Caption = TreeView->Selected->Text; // ��� ������
 }
 else
 {
   // ������� ������ ������ - ��� �������
  TreeView->Selected = TreeView->Items->GetFirstNode();
   // ������� ������ ������ �� �������
  TTreeNode* CurrNode = TreeView->Selected->GetNext();
  if (CurrNode) TreeView->Selected = CurrNode;
 }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::InterpretManualClick(TObject *Sender)
{
 InterprForm->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ToolButton1Click(TObject *Sender)
{
HDC hDC;
int i,x=100,y=100;
float AB2 = 1.0;
char str[100];

//  Image->Update();
//  Image->Canvas->Pen->Color = clRed;
//  Image->Canvas->MoveTo(0,0);
//  Image->Canvas->LineTo(Image->Width, Image->Height);

//MainForm->Canvas->Pen->Color = clRed;
//MainForm->Canvas->MoveTo(Panel->ClientRect.Left, Panel->ClientRect.Top);
//MainForm->Canvas->LineTo(Panel->ClientRect.Right, Panel->ClientRect.Bottom);

PaintBox->Canvas->Pen->Color = clRed;
PaintBox->Canvas->MoveTo(PaintBox->ClientRect.Left, PaintBox->ClientRect.Top);
PaintBox->Canvas->LineTo(PaintBox->ClientRect.Right, PaintBox->ClientRect.Bottom);
PaintBox->Canvas->Pen->Color = clBlue;
PaintBox->Canvas->MoveTo(PaintBox->ClientRect.Right, PaintBox->ClientRect.Top);
PaintBox->Canvas->LineTo(PaintBox->ClientRect.Left, PaintBox->ClientRect.Bottom);
hDC = PaintBox->Canvas->Handle;

  SetTextAlign( hDC, TA_BASELINE | TA_TOP );
  PaintBox->Canvas->MoveTo( x-10, y );
  PaintBox->Canvas->LineTo( x+10, y );
  PaintBox->Canvas->MoveTo( x, y-10 );
  PaintBox->Canvas->LineTo( x, y+10 );
  PaintBox->Canvas->MoveTo( x, y );
  PaintBox->Canvas->TextOut( x, y, "100" );
//  TextOut( hDC, x, y, "100", 3 );

//  for( i = 0; i <= 3; i ++, x += 50, AB2 *= 10 )
//   { PaintBox->Canvas->MoveTo( x, y );
//     PaintBox->Canvas->LineTo( x, 200 );
//     PaintBox->Canvas->TextOut( x, y + 5, "100" );
//   }


}
//---------------------------------------------------------------------------



void __fastcall TMainForm::RenamePopUpClick(TObject *Sender)
{
   RenameForm->AreaNameEdit->Text = Prof.hdr.areaname;
   RenameForm->ProfNameEdit->Text = Prof.hdr.profname;
   RenameForm->CurveNameEdit->Text = Prof.vez.ID_curve;
   RenameForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ViewToolBarClick(TObject *Sender)
{
 ViewToolBar->Checked = !ViewToolBar->Checked;
 ToolBar->Visible = ViewToolBar->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ViewStatusBarClick(TObject *Sender)
{
 ViewStatusBar->Checked = !ViewStatusBar->Checked;
 StatusBar->Visible = ViewStatusBar->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormDestroy(TObject *Sender)
{

// ����� ������������ ����� ������� ��������� � INI-����,
// ��������� ������ pVES4WinIni (��� TIniFile)
 pVES4WinIni->WriteBool("Options", "ShowToolBar", ToolBar->Visible );
 pVES4WinIni->WriteBool("Options", "ShowStatusBar", StatusBar->Visible );
 delete pVES4WinIni;  // ������ ��������� �� TIniFile

}
//---------------------------------------------------------------------------

