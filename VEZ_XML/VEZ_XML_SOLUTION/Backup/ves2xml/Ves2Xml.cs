//
// Приложение конвертации двоичных и текстовых файлов формата VES(VEZ) в файлы XML
// и рисования кривых ВЭЗ в графических файлах (по одному файлу на кривую)
// Коротков В.А. 2002 г.
//
using System;
using System.IO;
using System.Xml;
using System.Windows.Forms;
using System.Globalization;

namespace ves2xml
{
	/// <summary>
	/// Приложение конвертации двоичных и текстовых файлов формата VES(VEZ) в файлы XML
	/// и рисования кривых ВЭЗ в графических файлах (по одному файлу на кривую)
	/// </summary>
	class Ves2XmlClass
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			string		inputFile;		// Имя входного файла
			string		outputXmlFile;	// Имя выходного XML файла
			string		gifFile;        // Имя файла GIF
			VesFileType	fileType;		// Тип файла (bin или text)
 
			// Имя exe файла приложения
			System.Diagnostics.Process proc = System.Diagnostics.Process.GetCurrentProcess();
			_appName = proc.MainModule.FileName.ToString();
			_appName = Path.GetFileName(_appName);
			// Версия сборки
			_version = System.Reflection.AssemblyName.GetAssemblyName(_appName).Version.ToString();

			PrintGreeting(_appName,_version);		//

			if (args.Length < 1)	// Имя входного файла в командной строке
			{
				string msg = String.Format("Не задано имя входного файла!\n\nИспользование: {0} <filename>",_appName);
				MessageBox.Show(msg,"Ошибка");
				return;
			}
			else
			inputFile = args[0];

			outputXmlFile = inputFile + ".xml";
				
			// Заголовок VES-файла
			VesFileHeaderClass hdrVES = new VesFileHeaderClass();

			// Определим тип файла
			fileType = GetFileType(inputFile);		// Тип ВЭЗ-файла
			if (fileType == VesFileType.NotValid)
			{
				MessageBox.Show("Входной файл имеет неверный формат!","Ошибка формата");
				return;
			}

			// Откроем поток
			FileStream fs = new FileStream(inputFile, FileMode.Open, FileAccess.Read);

			// Весь текст в исходном файле в кодировке 866
			System.Text.Encoding enc866  = System.Text.Encoding.GetEncoding(866);
			BinaryReader binReader = new BinaryReader(fs,enc866);
			StreamReader txtReader = new StreamReader(fs,enc866);

			// Загрузить заголовок
			switch (fileType)
			{
				case VesFileType.Binary : hdrVES.Load(fs); break;
				case VesFileType.Text   : hdrVES.Load(txtReader); break;
			}

			Console.WriteLine("Участок: {0}", hdrVES.areaName );
			Console.WriteLine("Профиль: {0}", hdrVES.profName );
			Console.WriteLine("Кривых на профиле: {0}", hdrVES.nPoints );

			// Начать экспорт в XML
			XmlTextWriter xmlWriter = new XmlTextWriter(outputXmlFile, System.Text.Encoding.GetEncoding(1251));
			xmlWriter.Formatting = Formatting.Indented;
			xmlWriter.WriteStartDocument();
			xmlWriter.WriteStartElement("area");
//			xmlWriter.WriteAttributeString("id","bel001");
			xmlWriter.WriteAttributeString("name", hdrVES.areaName);
			xmlWriter.WriteStartElement("areadescr");
			xmlWriter.WriteEndElement();
			xmlWriter.WriteStartElement("generated");
			xmlWriter.WriteAttributeString("app", _appName);
			xmlWriter.WriteAttributeString("ver", _version);
			xmlWriter.WriteAttributeString("src", inputFile);
			CultureInfo en	= new CultureInfo("en-US"); // Весь вывод будет в американском формате
			xmlWriter.WriteAttributeString("culture", en.ToString() );
			DateTime dt = DateTime.Now;
			xmlWriter.WriteAttributeString( "date", dt.ToString(en) ); // В американском формате
			xmlWriter.WriteEndElement();

			xmlWriter.WriteStartElement("profil");
//			xmlWriter.WriteAttributeString("id","bel001prof");
			xmlWriter.WriteAttributeString("name", hdrVES.profName);
			xmlWriter.WriteAttributeString("type","profil"); // !!!!!!!!!!!!!!!!!!!!!!!
			xmlWriter.WriteStartElement("profildescr");
			xmlWriter.WriteEndElement();
	
			// Загрузить кривые ВЭЗ
			CurveClass currCurve = new CurveClass();
			xmlWriter.WriteStartElement("curves");
			for ( int i = 0; i < hdrVES.nPoints; i ++ )
			{
				switch (fileType)
				{
					case VesFileType.Binary : currCurve.Load(fs); break;
					case VesFileType.Text   : currCurve.Load(txtReader); break;
				}

				currCurve.areaName = hdrVES.areaName;
				currCurve.profName = hdrVES.profName;
				
				gifFile = String.Format("{0}-{1}.tif",inputFile,i);
				Console.WriteLine("#{0,15} Curve : name={1} Samples={2}", currCurve.hashCode, currCurve.curveName, currCurve.nSamples );
				currCurve.Draw( gifFile );

				// Экспортируем в XML
				currCurve.ExportToXml(xmlWriter,gifFile);
			}

			// Завершаем экспорт в XML
			xmlWriter.WriteEndElement(); // curves
			xmlWriter.WriteEndElement(); // profil
			xmlWriter.WriteEndElement(); // area
			xmlWriter.Close();
		}

		/// <summary>
		/// Выводит на экран информацио о приложении
		/// </summary>
		/// <param name="appname">Имя exe-файла приложения</param>
		/// <param name="version">Версия приложения</param>
		public static void PrintGreeting(string appname, string version)
		{	
			Console.WriteLine("===================================================================");
			Console.WriteLine(" {0} v{1}", appname, version);
			Console.WriteLine(" Программа конвертации файла  VES(VEZ) в файл формата XML");
			Console.WriteLine(" Каждая кривая ВЭЗ рисуется в отдельном файле формата GIF");
			Console.WriteLine(" (c)Коротков В.А. 2002");
			Console.WriteLine("===================================================================");
		}

		/// <summary>
		/// Определяет тип файла ВЭЗ - двоичный, текстовый или неверный формат
		/// </summary>
		/// <param name="fileName">Имя файла ВЭЗ</param>
		/// <returns>Тип файла</returns>
		public static VesFileType GetFileType(string fileName)
		{
			VesFileType ft = VesFileType.NotValid;

			// Откроем поток
			FileStream stream = new FileStream(fileName, FileMode.Open, FileAccess.Read);
			BinaryReader binRead = new BinaryReader(stream);
			
			char [] buf = new char[7];
			buf = binRead.ReadChars(7);
			string str = new string(buf);

			if (str == "VEZFILE")  ft = VesFileType.Text;
			else
			if (str == "VEZBINF")  ft = VesFileType.Binary;

			stream.Close();
			return ft;
		}

		/// <summary>
		/// Версия сборки
		/// </summary>
		public string Version
		{
			get
			{
				return _version;
			}
		}

		/// <summary>
		/// Имя файла сборки
		/// </summary>
		public string AppName
		{
			get
			{
				return _appName;
			}
		}

		private static string _appName;
		private static string _version;
	}
}
