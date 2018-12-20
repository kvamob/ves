//---------------------------------------------------------------------------
#ifndef InfofrmH
#define InfofrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TInfoForm : public TForm
{
__published:	// IDE-managed Components
    TButton *OKButton;
    TButton *PrintButton;
    TStatusBar *StatusBar;
    TStringGrid *ModelStringGrid;
    TStringGrid *DataStringGrid;
    THeaderControl *ModelHeaderControl;
    TStatusBar *FnameStatusBar;
    TStatusBar *AreaStatusBar;
    TStatusBar *ProfStatusBar;
    TStatusBar *CurveIDStatusBar;
    void __fastcall OKButtonClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TInfoForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInfoForm *InfoForm;
//---------------------------------------------------------------------------
#endif
