//---------------------------------------------------------------------------
#ifndef EdnamfrmH
#define EdnamfrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TRenameForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *AreaNameEdit;
        TEdit *ProfNameEdit;
        TEdit *CurveNameEdit;
        TButton *OKButton;
        TButton *CancelButton;
private:	// User declarations
public:		// User declarations
        __fastcall TRenameForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRenameForm *RenameForm;
//---------------------------------------------------------------------------
#endif
