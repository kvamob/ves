//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "interpr.h"
#include "ves.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TInterprForm *InterprForm;
//---------------------------------------------------------------------------
__fastcall TInterprForm::TInterprForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TInterprForm::ExitToolButtonClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------



void __fastcall TInterprForm::PrevToolButtonClick(TObject *Sender)
{
  MainForm->CurvePrevClick(InterprForm);
}
//---------------------------------------------------------------------------

void __fastcall TInterprForm::FirstToolButtonClick(TObject *Sender)
{
  MainForm->CurveFirstClick(InterprForm);    
}
//---------------------------------------------------------------------------

void __fastcall TInterprForm::NextToolButtonClick(TObject *Sender)
{
  MainForm->CurveNextClick(InterprForm);
}
//---------------------------------------------------------------------------

void __fastcall TInterprForm::LastToolButtonClick(TObject *Sender)
{
  MainForm->CurveLastClick(InterprForm);
}
//---------------------------------------------------------------------------


