//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Infofrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TInfoForm *InfoForm;
//---------------------------------------------------------------------------
__fastcall TInfoForm::TInfoForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TInfoForm::OKButtonClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TInfoForm::FormShow(TObject *Sender)
{
 DataStringGrid->Cells[0][0] = "AB/2";
 DataStringGrid->Cells[1][0] = "���. ����.";
 DataStringGrid->Cells[2][0] = "���. ����.";
 DataStringGrid->Cells[3][0] = "������";

 ModelStringGrid->Cells[0][0] = "����";
 ModelStringGrid->Cells[1][0] = "��.������.";
 ModelStringGrid->Cells[2][0] = "��������";

}
//---------------------------------------------------------------------------
