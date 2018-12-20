// Файл ves_io.c : часть проекта VES for Windows
// Функции работы с двоичными файлами формата VEZ

//    ПРОТОТИПЫ 
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


OFSTRUCT     ofs;         // Структура для функции OpenFile API Windows
extern int nProfilOpen;   // Признак открытия профиля

//extern int   hVEZBinFile; // Дескpиптоp двоичного файла фоpмата VEZ

/* ----------------------------------------------------------------
   OpenProfil Открывает файл профиля, имя которого указано в 
   строке fname, проверяет файл на корректность и заполняет 
   часть структуры prof. Затем считывает кривую ВЭЗ.
   Файл закрывается.
   При успешном завершении возвращает 0, при ошибке - код ошибки.
-------------------------------------------------------------------*/
int OpenProfil( char *fname, PROFIL *prof )
{
int status;
int Cc = 0;
int hFile;

  // откроем для чтения
 hFile = OpenFile( fname, (LPOFSTRUCT) &ofs, OF_READ);
 if ( hFile < 0 ) { Cc = F_NOT_OPEN; goto Exit; } // ошибка открытия 
  
  // читаем заголовок
 status = _lread( hFile, (LPSTR) &(prof->hdr), sizeof(HEADER));
 if ( status != sizeof(HEADER)) { Cc = F_READ_ERR; goto Exit; } // ошибка
  
  // Проверка
 if ( lstrcmp( prof->hdr.signat, B_SIGNATURE )) // не двоичн. ВЭЗфайл 
  {
   if (0 == _fstrncmp( prof->hdr.signat, T_SIGNATURE, 7 )) 
      Cc = F_TEXT_VEZ;   // текстовый ВЭЗ-файл
   else 
      Cc = F_NOT_VEZ;    // вообще не ВЭЗ-файл
   } 
   else // Это то, что надо
   {
   OemToAnsi(prof->hdr.areaname,prof->hdr.areaname ); // Преобразуем
   OemToAnsi(prof->hdr.profname,prof->hdr.profname ); // Преобразуем
   }

Exit: 
 _lclose( hFile );
 return Cc;
}

/* ----------------------------------------------------------------
   WriteProfilHeader записывает заголовок профиля из структуры prof 
   в двоичный VEZ-файл с именем fname
   При успешном завершении возвращает 0, при ошибке - код ошибки.
-------------------------------------------------------------------*/
int WriteProfilHeader( char *fname, PROFIL *prof )
{
 return 0;
}

/* ----------------------------------------------------------------
  ReadCurve считывает кривую из двоичного VEZ-файла с именем fname, 
  заполняет структуру vez
  hWnd - дескриптор несущего окна программы
  cnt - порядковый номер кривой (от 1)
  При успешном завершении возвращает 0, при ошибке - код ошибки.
-------------------------------------------------------------------*/
int ReadCurve( HWND hWnd, char *fname, VEZ *vez , int cnt )
{
int status;  
int hFile;
long offs;
char buf[30];
int  Cc = 0;

  // откроем для чтения
 hFile = OpenFile( fname, (LPOFSTRUCT) &ofs, OF_READ);
 if ( hFile < 0 )        // Файл не открылся
    { nProfilOpen = 0;   // Закрыть профиль
      MessageBox( hWnd, "File Not Open !","Read Curve", MB_OK | MB_ICONSTOP); 
      return F_NOT_OPEN; 
     } // ошибка открытия 
 
 // ищем нужную кривую           
 offs = ((long) cnt - 1L )*sizeof(VEZ) + sizeof(HEADER);
 _llseek( hFile, offs, SEEK_SET );
 // Читаем ее
 status = _lread( hFile, (LPSTR) vez, sizeof(VEZ));
 if ( status != sizeof(VEZ)) 
   { nProfilOpen = 0;
     wsprintf( buf, "Error Reading Curve #%d", cnt );
     MessageBox( hWnd, (LPSTR)buf, "Read Curve", MB_OK | MB_ICONSTOP); 
     Cc = F_READ_ERR;  // ошибка чтения
    }
   else
   {
     if (vez->model.n == 0) FillDefData( vez ); // Заполним модель
     OemToAnsi(vez->ID_curve, vez->ID_curve );  // Преобразуем
   }
 _lclose( hFile );
 
InvalidateRect( hWnd, NULL, TRUE ); // Изменить все окно
UpdateWindow( hWnd ); // Перерисуем несущее окно посылкой WM_PAINT
return Cc;
}    


/* ----------------------------------------------------------------
  WriteCurve записывает кривую из структуры VEZ в двоичный VEZ-файл 
  с именем fname 
  hWnd - дескриптор несущего окна программы
  cnt - порядковый номер кривой (от 1)
  При успешном завершении возвращает 0, при ошибке - код ошибки.
-------------------------------------------------------------------*/
int WriteCurve( HWND hWnd, char *fname, VEZ *vez , int cnt )
{
int status;  
int hFile;
long offs;
char buf[30];
int  Cc = 0;

  // откроем для записи-чтения
 hFile = OpenFile( fname, (LPOFSTRUCT) &ofs, OF_READWRITE);
 if ( hFile < 0 )        // Файл не открылся
    { nProfilOpen = 0;   // Закрыть профиль
      MessageBox( hWnd, "File Not Open !","Write Curve", MB_OK | MB_ICONSTOP); 
      return F_NOT_OPEN;
     } // ошибка открытия 
 
 AnsiToOem(vez->ID_curve, vez->ID_curve );  // Преобразуем перед записью
 // ищем нужную кривую           
 offs = ((long) cnt - 1L )*sizeof(VEZ) + sizeof(HEADER);
 _llseek( hFile, offs, SEEK_SET );
 // Запишем ее
 status = _lwrite( hFile, (LPSTR) vez, sizeof(VEZ));
 if ( status != sizeof(VEZ)) 
   { 
//     nProfilOpen = 0;
     wsprintf( buf, "Error Writing Curve #%d", cnt );
     MessageBox( hWnd, (LPSTR)buf, "Write Curve", MB_OK | MB_ICONSTOP); 
     Cc = F_WRIT_ERR;  // ошибка записи
    }
 _lclose( hFile );

OemToAnsi(vez->ID_curve, vez->ID_curve ); // Преобразуем обратно
 
InvalidateRect( hWnd, NULL, TRUE ); // Изменить все окно
UpdateWindow( hWnd ); // Перерисуем несущее окно посылкой WM_PAINT
return Cc;
}


/* ----------------------------------------------------------------
   CloseProfil Закрывает файл профиля из структуры prof. 
-------------------------------------------------------------------*/
void CloseProfil( PROFIL *prof )
{
}

/* ----------------------------------------------------------------
   FillDefData Заполняет некоторые поля структуры vez значениями
   по умолчанию (если в модели 0 слоев)
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

