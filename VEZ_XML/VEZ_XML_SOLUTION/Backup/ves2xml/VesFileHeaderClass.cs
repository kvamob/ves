using System;
using System.IO;


// *************** Формат двоичного VEZ-файла  ***************************************
// Файл формата VEZ содержит данные о кривых ВЭЗ по ОДНОМУ профилю.
// Файл состоит из заголовка и идущих одна за другой записей о кривых
// фиксированного размера
//                        ЗАГОЛОВОК
//    char  signat[6];   /* Сигнатура файла - символы VEZBINFILE
//    int   npoints;     /* Число точек ВЭЗ на пpофиле
//    float h_scale;     /* Знаменатель гоpиз. масштаба pисунка
//    char  areaname[40];/* Имя участка
//    char  profname[20];/* Имя профиля
//    int   count;       /* Порядковый номер текущей кривой от 1
//                      ЗАПИСЬ О КРИВОЙ
//  char  ID_curve[20]; /* Наименование кривой
//  float X,Y,Z;        /* Координаты кривой
//  MODEL model;        /* Характеристики разреза
//  CURVE curve;        /* Кривая ВЭЗ
//  float first_absc;   /* Первая абсцисса рассчитываемой кривой в м
//  float RokMin;       /* Минимальное значение кажущ. сопротивления
//  float RokMax;       /* Максимальное значение кажущ. сопротивления
//  float AB2Min;       /* Минимальное значение разноса АВ/2
//  float AB2Max;       /* Максимальное значение разноса АВ/2
//  int   RokDecads;    /* Число декад по оси кажущ. сопрот. ( ось Y )
//  int   AB2Decads;    /* Число декад по оси разносов АВ/2  ( ось X )
//  float OrgRok;       /* Начальное значение каж.соп. логарифм. бланка
//  float OrgAB2;       /* Начальное значение АВ/2 логарифм. бланка
//  float RMS;          /* Среднее относительное расхождение между
//                      /* наблюденной и рассчитанной кривыми ВЭЗ
//  int   q18;          /* Количество точек кривой с шагом 1/8 декады
//  int   q16;          /* Количество точек кривой с шагом 1/6 декады
//************************************************************************************

//typedef struct _MODEL 
//		{   // Структура - описатель модели разреза
//			short n;                  // Число слоев
//			float ro[MAX_LAYERS];     // Массив сопротивлений слоев
//			float h[MAX_LAYERS-1];    // Массив мощностей слоев
//		} MODEL;
//
//typedef struct _CURVE 
//		{   // Структура - описатель кривой ВЭЗ
//			short n;                  // Число отсчетов на кривой
//			float fRok[MAX_SAMPLES];  // Набл. значения кажущ.сопротивления Ом*м
//			float tRok[MAX_SAMPLES];  // Рассч.значения кажущ.сопротивления Ом*м
//			float AB2[MAX_SAMPLES];   // Значения разносов АВ/2 в метрах
//		} CURVE;

namespace ves2xml
{
	/// <summary>
	/// Класс заголовка VES-файла
	/// </summary>
	public class VesFileHeaderClass
	{
		/// <summary>
		/// Конструктор
		/// </summary>
		public VesFileHeaderClass()
		{
			// 
			// TODO: Add constructor logic here
			//
		}

		char [] fileSignature = new char[12];		// Сигнатура файла - символы VEZBINFILE_

		/// <summary>
		/// Число точек ВЭЗ на пpофиле
		/// </summary>
		public short  nPoints;						// Число точек ВЭЗ на пpофиле
		float h_scale;								// Знаменатель гоpиз. масштаба pисунка
		
		/// <summary>
		/// Имя участка
		/// </summary>
		public	string  areaName;					// Имя участка

		/// <summary>
		/// Имя профиля
		/// </summary>
		public	string	profName;					// Имя профиля
		
		short   count;								// Порядковый номер текущей кривой от 1

		/// <summary>
		///  Загрузить заголовок двоичного файла VES из потока<br />
		///  Метод вызывается из метода <b>Load()</b>
		/// </summary>
		/// <param name="stream">Входной поток</param>
		private void loadFromBinFile(FileStream stream)
		{
			// Весь текст в исходном файле в кодировке 866
			System.Text.Encoding enc866  = System.Text.Encoding.GetEncoding(866);
			BinaryReader binRead = new BinaryReader(stream, enc866);

			fileSignature = binRead.ReadChars(12);
			nPoints = binRead.ReadInt16();
			h_scale = binRead.ReadSingle();

			char []  _areaname = new char[40];			// Имя участка
			_areaname = binRead.ReadChars(40);			// Читать из файла в буфер
			string _str1 = new string(_areaname);		//
            areaName = _str1.Replace("\0"," ").Trim();	// Удалить нулевые символы
			
			char []  _profname = new char[20];			// Имя профиля
			_profname = binRead.ReadChars(20);			// Читать из файла в буфер
			string _str2 = new string(_profname);		//
			profName = _str2.Replace("\0"," ").Trim();	// Удалить нулевые символы

			count = binRead.ReadInt16();				// Кол-во кривых на профиле
		}

//		/// <summary>
//		/// Идентификатор участка
//		/// </summary>
//		string areaID;							

//		/// <summary>
//		/// Идентификатор профиля
//		/// </summary>
//		string profilID;

		/// <summary>
		///  Загрузить заголовок файла VES из потока. <br />
		///  Поток должен быть уже открыт: <br />
		///  <example>
		///  <code>
		///	// Откроем поток<br />
		/// FileStream vesFile = new FileStream("evez.ves", FileMode.Open, FileAccess.Read);<br />
		/// // Загрузить заголовок<br />
		/// hdrVES.Load(vesFile);<br />
		/// </code>
		///  </example>
		/// </summary>
		/// <param name="stream">Входной поток</param>
		public void Load(FileStream stream)
		{
			loadFromBinFile(stream);
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="reader"></param>
		public void Load(StreamReader reader)
		{
			loadFromTxtFile(reader);
		}

		/// <summary>
		///  Загрузить заголовок текстового файла VEZS из потока<br />
		///  Метод вызывается из метода <b>Load()</b>
		/// </summary>
		/// <param name="sr">Входной поток</param>
		private void loadFromTxtFile(StreamReader sr)
		{
			// Подсчитаем кол-во кривых ВЗЗ в файле
			nPoints  = (short) TextVezFileParserClass.CountCurves( sr );

//			sr.BaseStream.Position = 0;
			sr.BaseStream.Seek(0, SeekOrigin.Begin);
			areaName = TextVezFileParserClass.ParseParam(sr);
			profName = TextVezFileParserClass.ParseParam(sr);
		}
	}
}
