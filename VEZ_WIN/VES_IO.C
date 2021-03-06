// ���� ves_io.c : ���� �஥�� VES for Windows
// �㭪樨 ࠡ��� � �����묨 䠩���� �ଠ� VEZ

//    ��������� 
#include <windows.h>
#include <stdio.h>
#include <string.h>

#include "ves.h"

int OpenProfil( char *fname, PROFIL *prof );
int OpenProfil( char *fname, PROFIL *prof );
int WriteProfilHeader( char *fname, PROFIL *prof );
int ReadCurve( HWND hWnd, char *fname, VEZ *vez , int cnt );
int WriteCurve( HWND hWnd, char *fname, VEZ *vez , int cnt );
void CloseProfil( PROFIL *prof );
void FillDefData( VEZ *vez );


OFSTRUCT     ofs;         // ������� ��� �㭪樨 OpenFile API Windows
extern int nProfilOpen;   // �ਧ��� ������ ��䨫�

//extern int   hVEZBinFile; // ���p���p ����筮�� 䠩�� �p��� VEZ

/* ----------------------------------------------------------------
   OpenProfil ���뢠�� 䠩� ��䨫�, ��� ���ண� 㪠���� � 
   ��ப� fname, �஢���� 䠩� �� ���४⭮��� � �������� 
   ���� �������� prof. ��⥬ ���뢠�� �ਢ�� ���.
   ���� ����뢠����.
   �� �ᯥ譮� �����襭�� �����頥� 0, �� �訡�� - ��� �訡��.
-------------------------------------------------------------------*/
int OpenProfil( char *fname, PROFIL *prof )
{
int status;
int Cc = 0;
int hFile;

  // ��஥� ��� �⥭��
 hFile = OpenFile( fname, (LPOFSTRUCT) &ofs, OF_READ);
 if ( hFile < 0 ) { Cc = F_NOT_OPEN; goto Exit; } // �訡�� ������ 
  
  // �⠥� ���������
 status = _lread( hFile, (LPSTR) &(prof->hdr), sizeof(HEADER));
 if ( status != sizeof(HEADER)) { Cc = F_READ_ERR; goto Exit; } // �訡��
  
  // �஢�ઠ
 if ( lstrcmp( prof->hdr.signat, B_SIGNATURE )) // �� �����. ���䠩� 
  {
   if (0 == _fstrncmp( prof->hdr.signat, T_SIGNATURE, 7 )) 
      Cc = F_TEXT_VEZ;   // ⥪�⮢� ���-䠩�
   else 
      Cc = F_NOT_VEZ;    // ����� �� ���-䠩�
   } 
   else // �� �, �� ����
   {
   OemToAnsi(prof->hdr.areaname,prof->hdr.areaname ); // �८�ࠧ㥬
   OemToAnsi(prof->hdr.profname,prof->hdr.profname ); // �८�ࠧ㥬
   }

Exit: 
 _lclose( hFile );
 return Cc;
}

/* ----------------------------------------------------------------
   WriteProfilHeader �����뢠�� ��������� ��䨫� �� �������� prof 
   � ������ VEZ-䠩� � ������ fname
   �� �ᯥ譮� �����襭�� �����頥� 0, �� �訡�� - ��� �訡��.
-------------------------------------------------------------------*/
int WriteProfilHeader( char *fname, PROFIL *prof )
{
 return 0;
}

/* ----------------------------------------------------------------
  ReadCurve ���뢠�� �ਢ�� �� ����筮�� VEZ-䠩�� � ������ fname, 
  �������� �������� vez
  hWnd - ���ਯ�� ����饣� ���� �ணࠬ��
  cnt - ���浪��� ����� �ਢ�� (�� 1)
  �� �ᯥ譮� �����襭�� �����頥� 0, �� �訡�� - ��� �訡��.
-------------------------------------------------------------------*/
int ReadCurve( HWND hWnd, char *fname, VEZ *vez , int cnt )
{
int status;  
int hFile;
long offs;
char buf[30];
int  Cc = 0;

  // ��஥� ��� �⥭��
 hFile = OpenFile( fname, (LPOFSTRUCT) &ofs, OF_READ);
 if ( hFile < 0 )        // ���� �� ������
    { nProfilOpen = 0;   // ������� ��䨫�
      MessageBox( hWnd, "File Not Open !","Read Curve", MB_OK | MB_ICONSTOP); 
      return F_NOT_OPEN; 
     } // �訡�� ������ 
 
 // �饬 �㦭�� �ਢ��           
 offs = ((long) cnt - 1L )*sizeof(VEZ) + sizeof(HEADER);
 _llseek( hFile, offs, SEEK_SET );
 // ��⠥� ��
 status = _lread( hFile, (LPSTR) vez, sizeof(VEZ));
 if ( status != sizeof(VEZ)) 
   { nProfilOpen = 0;
     wsprintf( buf, "Error Reading Curve #%d", cnt );
     MessageBox( hWnd, (LPSTR)buf, "Read Curve", MB_OK | MB_ICONSTOP); 
     Cc = F_READ_ERR;  // �訡�� �⥭��
    }
   else
   {
     if (vez->model.n == 0) FillDefData( vez ); // �������� ������
     OemToAnsi(vez->ID_curve, vez->ID_curve );  // �८�ࠧ㥬
   }
 _lclose( hFile );
 
InvalidateRect( hWnd, NULL, TRUE ); // �������� �� ����
UpdateWindow( hWnd ); // �����㥬 ����饥 ���� ���뫪�� WM_PAINT
return Cc;
}    


/* ----------------------------------------------------------------
  WriteCurve �����뢠�� �ਢ�� �� �������� VEZ � ������ VEZ-䠩� 
  � ������ fname 
  hWnd - ���ਯ�� ����饣� ���� �ணࠬ��
  cnt - ���浪��� ����� �ਢ�� (�� 1)
  �� �ᯥ譮� �����襭�� �����頥� 0, �� �訡�� - ��� �訡��.
-------------------------------------------------------------------*/
int WriteCurve( HWND hWnd, char *fname, VEZ *vez , int cnt )
{
int status;  
int hFile;
long offs;
char buf[30];
int  Cc = 0;

  // ��஥� ��� �����-�⥭��
 hFile = OpenFile( fname, (LPOFSTRUCT) &ofs, OF_READWRITE);
 if ( hFile < 0 )        // ���� �� ������
    { nProfilOpen = 0;   // ������� ��䨫�
      MessageBox( hWnd, "File Not Open !","Write Curve", MB_OK | MB_ICONSTOP); 
      return F_NOT_OPEN;
     } // �訡�� ������ 
 
 AnsiToOem(vez->ID_curve, vez->ID_curve );  // �८�ࠧ㥬 ��। �������
 // �饬 �㦭�� �ਢ��           
 offs = ((long) cnt - 1L )*sizeof(VEZ) + sizeof(HEADER);
 _llseek( hFile, offs, SEEK_SET );
 // ����襬 ��
 status = _lwrite( hFile, (LPSTR) vez, sizeof(VEZ));
 if ( status != sizeof(VEZ)) 
   { 
//     nProfilOpen = 0;
     wsprintf( buf, "Error Writing Curve #%d", cnt );
     MessageBox( hWnd, (LPSTR)buf, "Write Curve", MB_OK | MB_ICONSTOP); 
     Cc = F_WRIT_ERR;  // �訡�� �����
    }
 _lclose( hFile );

OemToAnsi(vez->ID_curve, vez->ID_curve ); // �८�ࠧ㥬 ���⭮
 
InvalidateRect( hWnd, NULL, TRUE ); // �������� �� ����
UpdateWindow( hWnd ); // �����㥬 ����饥 ���� ���뫪�� WM_PAINT
return Cc;
}


/* ----------------------------------------------------------------
   CloseProfil ����뢠�� 䠩� ��䨫� �� �������� prof. 
-------------------------------------------------------------------*/
void CloseProfil( PROFIL *prof )
{
}

/* ----------------------------------------------------------------
   FillDefData �������� ������� ���� �������� vez ���祭�ﬨ
   �� 㬮�砭�� (�᫨ � ������ 0 ᫮��)
-------------------------------------------------------------------*/
void FillDefData( VEZ *vez )
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

