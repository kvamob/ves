// ���� ves_io.c : ����� ������� VES for Windows
// ������� ������ � ��������� ������� ������� VEZ

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


OFSTRUCT     ofs;         // ��������� ��� ������� OpenFile API Windows
extern int nProfilOpen;   // ������� �������� �������

//extern int   hVEZBinFile; // ����p����p ��������� ����� ��p���� VEZ

/* ----------------------------------------------------------------
   OpenProfil ��������� ���� �������, ��� �������� ������� � 
   ������ fname, ��������� ���� �� ������������ � ��������� 
   ����� ��������� prof. ����� ��������� ������ ���.
   ���� �����������.
   ��� �������� ���������� ���������� 0, ��� ������ - ��� ������.
-------------------------------------------------------------------*/
int OpenProfil( char *fname, PROFIL *prof )
{
int status;
int Cc = 0;
int hFile;

  // ������� ��� ������
 hFile = OpenFile( fname, (LPOFSTRUCT) &ofs, OF_READ);
 if ( hFile < 0 ) { Cc = F_NOT_OPEN; goto Exit; } // ������ �������� 
  
  // ������ ���������
 status = _lread( hFile, (LPSTR) &(prof->hdr), sizeof(HEADER));
 if ( status != sizeof(HEADER)) { Cc = F_READ_ERR; goto Exit; } // ������
  
  // ��������
 if ( lstrcmp( prof->hdr.signat, B_SIGNATURE )) // �� ������. ������� 
  {
   if (0 == _fstrncmp( prof->hdr.signat, T_SIGNATURE, 7 )) 
      Cc = F_TEXT_VEZ;   // ��������� ���-����
   else 
      Cc = F_NOT_VEZ;    // ������ �� ���-����
   } 
   else // ��� ��, ��� ����
   {
   OemToAnsi(prof->hdr.areaname,prof->hdr.areaname ); // �����������
   OemToAnsi(prof->hdr.profname,prof->hdr.profname ); // �����������
   }

Exit: 
 _lclose( hFile );
 return Cc;
}

/* ----------------------------------------------------------------
   WriteProfilHeader ���������� ��������� ������� �� ��������� prof 
   � �������� VEZ-���� � ������ fname
   ��� �������� ���������� ���������� 0, ��� ������ - ��� ������.
-------------------------------------------------------------------*/
int WriteProfilHeader( char *fname, PROFIL *prof )
{
 return 0;
}

/* ----------------------------------------------------------------
  ReadCurve ��������� ������ �� ��������� VEZ-����� � ������ fname, 
  ��������� ��������� vez
  hWnd - ���������� �������� ���� ���������
  cnt - ���������� ����� ������ (�� 1)
  ��� �������� ���������� ���������� 0, ��� ������ - ��� ������.
-------------------------------------------------------------------*/
int ReadCurve( HWND hWnd, char *fname, VEZ *vez , int cnt )
{
int status;  
int hFile;
long offs;
char buf[30];
int  Cc = 0;

  // ������� ��� ������
 hFile = OpenFile( fname, (LPOFSTRUCT) &ofs, OF_READ);
 if ( hFile < 0 )        // ���� �� ��������
    { nProfilOpen = 0;   // ������� �������
      MessageBox( hWnd, "File Not Open !","Read Curve", MB_OK | MB_ICONSTOP); 
      return F_NOT_OPEN; 
     } // ������ �������� 
 
 // ���� ������ ������           
 offs = ((long) cnt - 1L )*sizeof(VEZ) + sizeof(HEADER);
 _llseek( hFile, offs, SEEK_SET );
 // ������ ��
 status = _lread( hFile, (LPSTR) vez, sizeof(VEZ));
 if ( status != sizeof(VEZ)) 
   { nProfilOpen = 0;
     wsprintf( buf, "Error Reading Curve #%d", cnt );
     MessageBox( hWnd, (LPSTR)buf, "Read Curve", MB_OK | MB_ICONSTOP); 
     Cc = F_READ_ERR;  // ������ ������
    }
   else
   {
     if (vez->model.n == 0) FillDefData( vez ); // �������� ������
     OemToAnsi(vez->ID_curve, vez->ID_curve );  // �����������
   }
 _lclose( hFile );
 
InvalidateRect( hWnd, NULL, TRUE ); // �������� ��� ����
UpdateWindow( hWnd ); // ���������� ������� ���� �������� WM_PAINT
return Cc;
}    


/* ----------------------------------------------------------------
  WriteCurve ���������� ������ �� ��������� VEZ � �������� VEZ-���� 
  � ������ fname 
  hWnd - ���������� �������� ���� ���������
  cnt - ���������� ����� ������ (�� 1)
  ��� �������� ���������� ���������� 0, ��� ������ - ��� ������.
-------------------------------------------------------------------*/
int WriteCurve( HWND hWnd, char *fname, VEZ *vez , int cnt )
{
int status;  
int hFile;
long offs;
char buf[30];
int  Cc = 0;

  // ������� ��� ������-������
 hFile = OpenFile( fname, (LPOFSTRUCT) &ofs, OF_READWRITE);
 if ( hFile < 0 )        // ���� �� ��������
    { nProfilOpen = 0;   // ������� �������
      MessageBox( hWnd, "File Not Open !","Write Curve", MB_OK | MB_ICONSTOP); 
      return F_NOT_OPEN;
     } // ������ �������� 
 
 AnsiToOem(vez->ID_curve, vez->ID_curve );  // ����������� ����� �������
 // ���� ������ ������           
 offs = ((long) cnt - 1L )*sizeof(VEZ) + sizeof(HEADER);
 _llseek( hFile, offs, SEEK_SET );
 // ������� ��
 status = _lwrite( hFile, (LPSTR) vez, sizeof(VEZ));
 if ( status != sizeof(VEZ)) 
   { 
//     nProfilOpen = 0;
     wsprintf( buf, "Error Writing Curve #%d", cnt );
     MessageBox( hWnd, (LPSTR)buf, "Write Curve", MB_OK | MB_ICONSTOP); 
     Cc = F_WRIT_ERR;  // ������ ������
    }
 _lclose( hFile );

OemToAnsi(vez->ID_curve, vez->ID_curve ); // ����������� �������
 
InvalidateRect( hWnd, NULL, TRUE ); // �������� ��� ����
UpdateWindow( hWnd ); // ���������� ������� ���� �������� WM_PAINT
return Cc;
}


/* ----------------------------------------------------------------
   CloseProfil ��������� ���� ������� �� ��������� prof. 
-------------------------------------------------------------------*/
void CloseProfil( PROFIL *prof )
{
}

/* ----------------------------------------------------------------
   FillDefData ��������� ��������� ���� ��������� vez ����������
   �� ��������� (���� � ������ 0 �����)
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

