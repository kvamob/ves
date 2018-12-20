//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <math.h>
#include "about.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutForm *AboutForm;
//---------------------------------------------------------------------------
__fastcall TAboutForm::TAboutForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAboutForm::OKButtonClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

void __fastcall TAboutForm::FormShow(TObject *Sender)
{
MEMORYSTATUS ms;
char buf1[48];
char buf2[48];

//typedef struct _MEMORYSTATUS { // mst
//    DWORD dwLength;        // sizeof(MEMORYSTATUS)
//    DWORD dwMemoryLoad;    // percent of memory in use
//    DWORD dwTotalPhys;     // bytes of physical memory
//    DWORD dwAvailPhys;     // free physical memory bytes
//    DWORD dwTotalPageFile; // bytes of paging file
//    DWORD dwAvailPageFile; // free bytes of paging file
//    DWORD dwTotalVirtual;  // user bytes of address space
//    DWORD dwAvailVirtual;  // free user bytes

 ms.dwLength = sizeof(MEMORYSTATUS);
 GlobalMemoryStatus( &ms ); // узнаем про память
 int ml = ms.dwMemoryLoad;
        // В мегабайтах
 int mt = ceil( (float) ms.dwTotalPhys/(1024*1024));
        //
//     ml = ms.dwAvailPhys;
wsprintf(buf1, "Доступная физическая память: %d Мб", mt);
wsprintf(buf2, "Системные ресурсы: свободно %d %%", 100-ml);
MemoryLabel->Caption = buf1;
PercLabel->Caption = buf2;
}
//---------------------------------------------------------------------------

void __fastcall TAboutForm::FormCreate(TObject *Sender)
{
DWORD h;
     // Получим информацию о версии с помощью GetFileVersionInfoSize
DWORD Size = GetFileVersionInfoSize(Application->ExeName.c_str(), &h );
if( Size == 0 ) return;    // нельзя получить информацию о версии

char *buf;
buf = (char*) GlobalAlloc(GMEM_FIXED, Size);

if (GetFileVersionInfo(Application->ExeName.c_str(), h, Size, buf)!=0 )
 {
  char *ValueBuf;
  UINT Len;
//  if( VerQueryValue(buf,"\\StringFileInfo\\040904E4\\ProductName",
//                   &(void*)ValueBuf, &Len)!=0)
//      AppName->Caption=ValueBuf;
   if(VerQueryValue(buf,
                        "\\StringFileInfo\\041904E3\\FileVersion",
                        &(void*)ValueBuf,
                        &Len)!=0 )
    VersionLabel->Caption=ValueBuf;
//    if(VerQueryValue(buf,
//                        "\\StringFileInfo\\040904E4\\LegalCopyright",
//                        &(void*)ValueBuf,
//                        &Len)!=0)
//           Copyright->Caption=ValueBuf;
//     if(VerQueryValue(buf,
//                        "\\StringFileInfo\\040904E4\\CompanyName",
//                        &(void*)ValueBuf,
//                        &Len)!=0)
//           Company->Caption=ValueBuf;
    }
   GlobalFree(buf);

OSVERSIONINFO osvi; // структура с информацией о версии ОС
//typedef struct _OSVERSIONINFO{
//    DWORD dwOSVersionInfoSize;
//    DWORD dwMajorVersion;
//    DWORD dwMinorVersion;
//    DWORD dwBuildNumber;
//    DWORD dwPlatformId;
//    TCHAR szCSDVersion[ 128 ];
//} OSVERSIONINFO;

osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

String str = "Microsoft ";

int mjv,   // Major version
    mnv,   // Minor version
    build; // Build number

if ( GetVersionEx( &osvi )) // получим информ. о версии ОС
{
   switch( osvi.dwPlatformId )
    {
      case VER_PLATFORM_WIN32s :
                str += "Windows 3.1 ";
                break;

      case VER_PLATFORM_WIN32_WINDOWS :
                 build = LOWORD(osvi.dwBuildNumber);
                 mjv   = HIBYTE(HIWORD(osvi.dwBuildNumber));
                 mnv   = LOBYTE(HIWORD(osvi.dwBuildNumber));
                 if (build == 1998 ) str += "Windows 98 ";
                    else str += "Windows 95 ";
                 break;

      case VER_PLATFORM_WIN32_NT      :
                 str += "Windows NT ";
                 mjv = osvi.dwMajorVersion;
                 mnv = osvi.dwMinorVersion;
                 build = osvi.dwBuildNumber;
                 break;
    } // swtch
    
    str += "Build ";
    str += IntToStr( mjv );
    str += ".";
    str += IntToStr( mnv );
    str += ".";
    str += IntToStr( build );
    str += " ";
    str += osvi.szCSDVersion;

    OSVersionLabel->Caption = str;

} // end if


}
//---------------------------------------------------------------------------

