//---------------------------------------------------------------------------
#ifndef interprH
#define interprH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Mask.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TInterprForm : public TForm
{
__published:	// IDE-managed Components
    TToolBar *ToolBar;
    TToolButton *SaveToolButton;
    TToolButton *PrintToolButton;
    TToolButton *FirstToolButton;
    TToolButton *PrevToolButton;
    TToolButton *NextToolButton;
    TToolButton *LastToolButton;
    TToolButton *FindToolButton;
    TToolButton *HelpToolButton;
    TToolButton *ToolButton11;
    TToolButton *ToolButton12;
    TToolButton *ToolButton13;
    TToolButton *ToolButton15;
    TImageList *ImageList;
    TGroupBox *GroupBox1;
    TTrackBar *TrackBar1;
    TMaskEdit *MaskEdit1;
    TUpDown *UpDown1;
    TTrackBar *TrackBar2;
    TUpDown *UpDown2;
    TMaskEdit *MaskEdit2;
    TTrackBar *TrackBar3;
    TUpDown *UpDown3;
    TMaskEdit *MaskEdit3;
    TTrackBar *TrackBar4;
    TUpDown *UpDown4;
    TMaskEdit *MaskEdit4;
    TTrackBar *TrackBar5;
    TUpDown *UpDown5;
    TMaskEdit *MaskEdit5;
    TTrackBar *TrackBar6;
    TUpDown *UpDown6;
    TMaskEdit *MaskEdit6;
    TGroupBox *GroupBox2;
    TTrackBar *TrackBar7;
    TMaskEdit *MaskEdit7;
    TUpDown *UpDown7;
    TTrackBar *TrackBar8;
    TUpDown *UpDown8;
    TMaskEdit *MaskEdit8;
    TTrackBar *TrackBar9;
    TUpDown *UpDown9;
    TMaskEdit *MaskEdit9;
    TTrackBar *TrackBar10;
    TUpDown *UpDown10;
    TMaskEdit *MaskEdit10;
    TTrackBar *TrackBar11;
    TUpDown *UpDown11;
    TMaskEdit *MaskEdit11;
    TCheckBox *CheckBox1;
    TUpDown *NLayerUpDown;
    TToolButton *ToolButton1;
    TComboBox *NLayerComboBox;
    TToolButton *ToolButton2;
    TBitBtn *RunButton;
    TToolButton *UndoToolButton;
    void __fastcall ExitToolButtonClick(TObject *Sender);
    
    
    void __fastcall PrevToolButtonClick(TObject *Sender);
    void __fastcall FirstToolButtonClick(TObject *Sender);
    void __fastcall NextToolButtonClick(TObject *Sender);
    void __fastcall LastToolButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TInterprForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInterprForm *InterprForm;
//---------------------------------------------------------------------------
#endif
