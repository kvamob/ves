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
// Конструктор класса приложения
// --------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
  nProfilOpen=0; // Признак открытия файла профиля (1 - открыт, 0 - нет
  EditCurve = 0; // Пpизнак pедактиpования кpивой
  Application->OnHint = DisplayHint; // Переопределим обработчик
}

// ------------------------------------------------------------------
// ---  Обработчик OnHint                                         ---
// ------------------------------------------------------------------
void __fastcall TMainForm::DisplayHint(TObject* Sender)
{
  ViewToolBar->Hint =
   (ViewToolBar->Checked) ? "Убрать панель инструментов" :
                            "Отобразить панель инструментов";
  ViewStatusBar->Hint =
   (ViewStatusBar->Checked) ? "Убрать строку состояния" :
                            "Отобразить строку состояния";

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
//TFileName CurrFileName;     // Имя текущего файла

if (OpenDialog->Execute())  // Файл был выбран
 {
  CurrFileName = OpenDialog->FileName;
  Caption = "Интерпретация кривых ВЭЗ - " + CurrFileName;

  if ( OpenProfil(CurrFileName, &Prof ) == 0);  // Открыть профиль
  {
    // Разрешим некоторые пункты меню
    EnableMenuItems( true );

    // -----------------------------------------------
    // В узлах элемента TreeView содержатся имена
    // текущего профиля и имена точек ВЭЗ
    TTreeNode *ProfNode; // корневой узел - имя профиля
    TreeView->Items->Clear(); // Очистим дерево
//      TreeView->Items->Add(NULL, "Профиль: 1-й широтный"); // создали корень
    String str = Prof.hdr.profname;
    str = "Профиль : " + str;
    TreeView->Items->Add(NULL, str ); // создали корень
    ProfNode = TreeView->Items->Item[0]; // указатель на корень
    ProfNode->ImageIndex = 1;
// Запишем имя загруженного профиля в корневой узел TreeView
//      TreeView->Items->Item[0]->Text = "Профиль: 1-й широтный";
    int i;
    TTreeNode* pItem;
    for ( i = 0; i < Prof.hdr.npoints; i ++ )
     {
      if (ReadCurve( CurrFileName, (VEZ *) &Prof.vez , i ) == 0)
       {
        pItem = TreeView->Items->AddChild( ProfNode, Prof.vez.ID_curve );
        if ( Prof.vez.model.n > 0 )   // кривая проинтерпретирована ?
           pItem->ImageIndex = 3; // Присвоим иконки
        else
           pItem->ImageIndex = 2; // Присвоим иконки
       }
       else
       { // не смогли загрузить кривую
         TreeView->Items->Clear(); // Очистим дерево
         TreeView->Items->Add(NULL, "Профиль: [не загружен]"); // создали корень
         EnableMenuItems( false ); // запретим в меню кое-что
         break;
       }
    }

          // "Раскроем" дерево
   TreeView->FullExpand();
          // Выделим корень списка - имя профиля
   TreeView->Selected = TreeView->Items->GetFirstNode();
//      TreeView->Selected->ImageIndex = 1;
          // Выделим первую кривую на профиле
// *** это уже обработано в TreeViewChange ***
//      TTreeNode* CurrNode = TreeView->Selected->GetNext();
//      if (CurrNode) TreeView->Selected = CurrNode;
          // Сделать TreeView активным
   MainForm->ActiveControl = TreeView;

      // -----------------------------------------------
   } // if OpenProfil
 }
 else //###### файл не выбрали #########
 {
  TreeView->Items->Clear(); // Очистим дерево
  TreeView->Items->Add(NULL, "Профиль [не загружен]"); // создали корень
  EnableMenuItems( false ); // запретим в меню кое-что
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
AnsiString  IniFileName;  // Имя Ini-файла

 sProgramFilePath = ExtractFilePath(ParamStr(0)); // откуда вызвали
 IniFileName = sProgramFilePath + "VES4Win.ini";

// =========================================================================
  // Объект TIniFile, будет удален в обработчике FormDestroy
 pVES4WinIni = new TIniFile (IniFileName);
 // ... Здесь можно прочитать некоторые параметры программы
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
  // сообщим системе, что наше приложение принимает перетащенные
  // методом drag-n-drop файлы
 DragAcceptFiles( Handle, TRUE );
// ============================================================
 int i = ParamCount(); // кол-во параметров в командной строке
 if ( i > 0 ) MainForm->Caption = ParamStr(1); // Тест
 // здесь надо вставить вызов открытия профиля и  загрузки кривой!
// ============================================================

 }

// ---------------------------------------------------------------------
// Функция, обрабатывающая сообщение WM_DROPFILES - оно возникает, когда
// на окно программы методом drag-and-drop бросаются файлы
// ---------------------------------------------------------------------
void __fastcall TMainForm::HandleDropFiles(TMessage& Msg)
{
HDROP hDropInfo = (HANDLE)Msg.WParam; // информация о перетащенном
char szFileName[MAX_PATH];

     // кол-во файлов
int  nFiles = DragQueryFile(hDropInfo, (DWORD)-1, (LPSTR)NULL, 0);
     // Берем только первый файл
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
// Обработчик щелчка мыши в окне TreeView
// ---------------------------------------------------------------------------
void __fastcall TMainForm::TreeViewMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  // Если щелкнули мышью НЕ на корневом узле
if (TreeView->Selected != TreeView->Items->Item[0])
 {   // Тест
//     Label1->Caption = StrToInt(TreeView->Selected->Index); // номер узла
   Label1->Caption = TreeView->Items->Item[0]->Text; // Имя профиля
   Label2->Caption = TreeView->Selected->Text; // Имя кривой

 }
}
//---------------------------------------------------------------------------
// Функция меняет свойство Enable некоторых пунктов меню
// и кнопок на панели
// value - значение, которое присваивается этому свойству
//--------------------------------------------------------
void __fastcall TMainForm::EnableMenuItems( bool value)
{
    // пункты меню
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

    // быстрые кнопки
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
// Выбор первой кривой на профиле
// --------------------------------------------------------------------------
void __fastcall TMainForm::CurveFirstClick(TObject *Sender)
{
   // "Раскроем" дерево
 TreeView->FullExpand();
   // Выделим корень списка - имя профиля
 TreeView->Selected = TreeView->Items->GetFirstNode();
   // Выделим первую кривую на профиле
 TTreeNode* CurrNode = TreeView->Selected->GetNext();
 if (CurrNode) TreeView->Selected = CurrNode;

   // Сделать TreeView активным
 MainForm->ActiveControl = TreeView;

}
//---------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Выбор последней кривой на профиле
// --------------------------------------------------------------------------
void __fastcall TMainForm::CurveLastClick(TObject *Sender)
{
   // "Раскроем" дерево
 TreeView->FullExpand();
   // Выделим корень списка - имя профиля
 TreeView->Selected = TreeView->Items->GetFirstNode();

   // Выделим последнюю кривую на профиле
 TTreeNode *CurItem = TreeView->Items->GetFirstNode();
 while (CurItem)
  {
   CurItem = CurItem->GetNext();
   if ( CurItem )  TreeView->Selected = CurItem;
  }

   // Сделать TreeView активным
 MainForm->ActiveControl = TreeView;
}
//---------------------------------------------------------------------------


// --------------------------------------------------------------------------
// Выбор следующей кривой на профиле
// --------------------------------------------------------------------------
void __fastcall TMainForm::CurveNextClick(TObject *Sender)
{
   // "Раскроем" дерево
 TreeView->FullExpand();
   // Выделим корень списка - имя профиля
// TreeView->Selected = TreeView->Items->GetFirstNode();
   // Выделим следующую кривую на профиле
 TTreeNode* NextNode = TreeView->Selected->GetNext();
 if (NextNode) TreeView->Selected = NextNode;

   // Сделать TreeView активным
 MainForm->ActiveControl = TreeView;
}

//---------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Выбор предыдущей кривой на профиле
// --------------------------------------------------------------------------
void __fastcall TMainForm::CurvePrevClick(TObject *Sender)
{
   // "Раскроем" дерево
 TreeView->FullExpand();
// Выделим корень списка - имя профиля
// TreeView->Selected = TreeView->Items->GetFirstNode();
   // Выделим первую кривую на профиле
 TTreeNode* FirstNode = TreeView->Items->GetFirstNode();
 TTreeNode* PrevNode = TreeView->Selected->GetPrev();
 if (PrevNode && PrevNode != FirstNode) TreeView->Selected = PrevNode;

   // Сделать TreeView активным
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
// Методы ввода-вывода из файлов спец. формата
// ##########################################################################

/* ----------------------------------------------------------------
   OpenProfil Открывает файл профиля, имя которого указано в
   строке fname, проверяет файл на корректность и заполняет
   часть структуры prof. Затем считывает кривую ВЭЗ.
   Файл закрывается.
   При успешном завершении возвращает 0, при ошибке - код ошибки.
-------------------------------------------------------------------*/
int __fastcall TMainForm::OpenProfil( System::AnsiString fname, PROFIL *prof )
{
int status;
int Cc = 0;
int hFile;

  // откроем для чтения
 hFile = Sysutils::FileOpen(fname, fmOpenRead);
 if ( hFile == -1 )
 {
  nProfilOpen = 0;
  Application->MessageBox("Не могу открыть файл!","Открытие профиля", IDOK );
  return F_NOT_OPEN;
 }
  // читаем заголовок
 status = FileRead( hFile, (LPSTR) &(prof->hdr), sizeof(HEADER));
 if ( status != sizeof(HEADER))
 {
  nProfilOpen = 0;
  Application->MessageBox("Ошибка чтения заголовка!","Открытие профиля", IDOK );
  return F_READ_ERR;
 }

  // Проверка
 if ( lstrcmp( prof->hdr.signat, B_SIGNATURE )) // не двоичн. ВЭЗфайл
  {
  if ( 0 == _fstrncmp( prof->hdr.signat, T_SIGNATURE, 7 ) )
     Cc = F_TEXT_VEZ;   // текстовый ВЭЗ-файл
  else
     Cc = F_NOT_VEZ;    // вообще не ВЭЗ-файл
  }
  else // Это то, что надо
  {
   OemToAnsi(prof->hdr.areaname,prof->hdr.areaname ); // Преобразуем
   OemToAnsi(prof->hdr.profname,prof->hdr.profname ); // Преобразуем
  }

 FileClose( hFile );
 return Cc;
}

/* ----------------------------------------------------------------
   WriteProfilHeader записывает заголовок профиля из структуры prof
   в двоичный VEZ-файл с именем fname
   При успешном завершении возвращает 0, при ошибке - код ошибки.
-------------------------------------------------------------------*/
int __fastcall TMainForm::WriteProfilHeader( AnsiString fname, PROFIL *prof )
{
 return 0;
}

/* ----------------------------------------------------------------
  ReadCurve считывает кривую из двоичного VEZ-файла с именем fname,
  заполняет структуру vez
  cnt - порядковый номер кривой (от 0)
  При успешном завершении возвращает 0, при ошибке - код ошибки.
-------------------------------------------------------------------*/
int __fastcall TMainForm::ReadCurve( AnsiString fname, VEZ *vez , int cnt )
{
int status;
int hFile;
int offs;
char buf[30];
int  Cc = 0;

  // откроем для чтения
 hFile = Sysutils::FileOpen( fname, fmOpenRead);
 if ( hFile == -1 )
 { nProfilOpen = 0;     // Закрыть профиль
   Application->MessageBox("Не могу открыть файл!","Чтение кривой ВЭЗ", IDOK );
   return F_NOT_OPEN;
 }

 // ищем нужную кривую
 offs = ((int) cnt )*sizeof(VEZ) + sizeof(HEADER);
 FileSeek( hFile, offs, 0);

 // Читаем ее
 status = FileRead( hFile, (LPSTR) vez, sizeof(VEZ));
 if ( status != sizeof(VEZ))
  { nProfilOpen = 0; // Закрыть профиль
    wsprintf( buf, "Ошибка чтения кривой N %d", cnt );
    Application->MessageBox( (LPSTR)buf, "Чтение кривой ВЭЗ", IDOK);
    Cc = F_READ_ERR;  // ошибка чтения
  }
 else
 {
  if (vez->model.n == 0) FillDefData( vez ); // Заполним модель
  OemToAnsi(vez->ID_curve, vez->ID_curve );  // Преобразуем
 }

 FileClose( hFile );
 MainForm->Update();

 return Cc;
}


/* ----------------------------------------------------------------
  WriteCurve записывает кривую из структуры VEZ в двоичный VEZ-файл
  с именем fname
  cnt - порядковый номер кривой (от 1)
  При успешном завершении возвращает 0, при ошибке - код ошибки.
-------------------------------------------------------------------*/
int __fastcall TMainForm::WriteCurve( AnsiString fname, VEZ *vez , int cnt )
{
int status;
int hFile;
int offs;
char buf[30];
int  Cc = 0;

  // откроем для записи-чтения
 hFile = Sysutils::FileOpen( fname, fmOpenReadWrite);
 if ( hFile == -1 )
  {
   nProfilOpen = 0;   // Закрыть профиль
   Application->MessageBox( "Не могу открыть файл!", "Запись кривой ВЭЗ", IDOK );
   return F_NOT_OPEN;
  }

 AnsiToOem(vez->ID_curve, vez->ID_curve );  // Преобразуем перед записью

 // ищем нужную кривую
 offs = ((int) cnt )*sizeof(VEZ) + sizeof(HEADER);
 FileSeek(hFile, offs, 0);

 // Запишем ее
 status = FileWrite( hFile, (LPSTR) vez, sizeof(VEZ));
 if ( status != sizeof(VEZ))
   {
     nProfilOpen = 0;
     wsprintf( buf, "Ошибка записи кривой N %d", cnt );
     Application->MessageBox( (LPSTR)buf, "Запись кривой ВЭЗ", IDOK);
     Cc = F_WRIT_ERR;  // ошибка записи
    }
   FileClose( hFile );

 OemToAnsi(vez->ID_curve, vez->ID_curve ); // Преобразуем обратно
 MainForm->Update();

 return Cc;
}


/* ----------------------------------------------------------------
   CloseProfil Закрывает файл профиля из структуры prof.
-------------------------------------------------------------------*/
void __fastcall TMainForm::CloseProfil( PROFIL *prof )
{
 return;
}

/* ----------------------------------------------------------------
   FillDefData Заполняет некоторые поля структуры vez значениями
   по умолчанию (если в модели 0 слоев)
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
// Конец методов ввода-вывода
// ##########################################################################

// --------------------------------------------------------------------------
// При изменении размеров окна установить некоторые пределы
// --------------------------------------------------------------------------


void __fastcall TMainForm::TreeViewChange(TObject *Sender, TTreeNode *Node)
{
  // Если не корневой узел
if (TreeView->Selected != TreeView->Items->Item[0])
 {   // Тест
  Label1->Caption = TreeView->Items->Item[0]->Text; // Имя профиля
  Label2->Caption = TreeView->Selected->Text; // Имя кривой
 }
 else
 {
   // Выделим корень списка - имя профиля
  TreeView->Selected = TreeView->Items->GetFirstNode();
   // Выделим первую кривую на профиле
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

// Перед уничтожением формы сбросим настройки в INI-файл,
// используя объект pVES4WinIni (тип TIniFile)
 pVES4WinIni->WriteBool("Options", "ShowToolBar", ToolBar->Visible );
 pVES4WinIni->WriteBool("Options", "ShowStatusBar", StatusBar->Visible );
 delete pVES4WinIni;  // Удалим указатель на TIniFile

}
//---------------------------------------------------------------------------

