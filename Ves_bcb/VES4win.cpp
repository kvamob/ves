//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("VES4win.res");
USEFORM("ves.cpp", MainForm);
USEFORM("about.cpp", AboutForm);
USEFORM("modelfrm.cpp", ModelCrvForm);
USEFORM("Infofrm.cpp", InfoForm);
USEFORM("interpr.cpp", InterprForm);
USEFORM("Ednamfrm.cpp", RenameForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
//        Application->Initialize();
        Application->Title = "VES for Windows";
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TAboutForm), &AboutForm);
                 Application->CreateForm(__classid(TModelCrvForm), &ModelCrvForm);
                 Application->CreateForm(__classid(TInfoForm), &InfoForm);
                 Application->CreateForm(__classid(TInterprForm), &InterprForm);
                 Application->CreateForm(__classid(TRenameForm), &RenameForm);
                 Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
