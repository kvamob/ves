//
// ���������� ����������� �������� � ��������� ������ ������� VES(VEZ) � ����� XML
// � ��������� ������ ��� � ����������� ������ (�� ������ ����� �� ������)
// �������� �.�. 2002 �.
//
using System;
using System.IO;
using System.Xml;
using System.Windows.Forms;
using System.Globalization;

namespace ves2xml
{
	/// <summary>
	/// ���������� ����������� �������� � ��������� ������ ������� VES(VEZ) � ����� XML
	/// � ��������� ������ ��� � ����������� ������ (�� ������ ����� �� ������)
	/// </summary>
	class Ves2XmlClass
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			string		inputFile;		// ��� �������� �����
			string		outputXmlFile;	// ��� ��������� XML �����
			string		gifFile;        // ��� ����� GIF
			VesFileType	fileType;		// ��� ����� (bin ��� text)
 
			// ��� exe ����� ����������
			System.Diagnostics.Process proc = System.Diagnostics.Process.GetCurrentProcess();
			_appName = proc.MainModule.FileName.ToString();
			_appName = Path.GetFileName(_appName);
			// ������ ������
			_version = System.Reflection.AssemblyName.GetAssemblyName(_appName).Version.ToString();

			PrintGreeting(_appName,_version);		//

			if (args.Length < 1)	// ��� �������� ����� � ��������� ������
			{
				string msg = String.Format("�� ������ ��� �������� �����!\n\n�������������: {0} <filename>",_appName);
				MessageBox.Show(msg,"������");
				return;
			}
			else
			inputFile = args[0];

			outputXmlFile = inputFile + ".xml";
				
			// ��������� VES-�����
			VesFileHeaderClass hdrVES = new VesFileHeaderClass();

			// ��������� ��� �����
			fileType = GetFileType(inputFile);		// ��� ���-�����
			if (fileType == VesFileType.NotValid)
			{
				MessageBox.Show("������� ���� ����� �������� ������!","������ �������");
				return;
			}

			// ������� �����
			FileStream fs = new FileStream(inputFile, FileMode.Open, FileAccess.Read);

			// ���� ����� � �������� ����� � ��������� 866
			System.Text.Encoding enc866  = System.Text.Encoding.GetEncoding(866);
			BinaryReader binReader = new BinaryReader(fs,enc866);
			StreamReader txtReader = new StreamReader(fs,enc866);

			// ��������� ���������
			switch (fileType)
			{
				case VesFileType.Binary : hdrVES.Load(fs); break;
				case VesFileType.Text   : hdrVES.Load(txtReader); break;
			}

			Console.WriteLine("�������: {0}", hdrVES.areaName );
			Console.WriteLine("�������: {0}", hdrVES.profName );
			Console.WriteLine("������ �� �������: {0}", hdrVES.nPoints );

			// ������ ������� � XML
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
			CultureInfo en	= new CultureInfo("en-US"); // ���� ����� ����� � ������������ �������
			xmlWriter.WriteAttributeString("culture", en.ToString() );
			DateTime dt = DateTime.Now;
			xmlWriter.WriteAttributeString( "date", dt.ToString(en) ); // � ������������ �������
			xmlWriter.WriteEndElement();

			xmlWriter.WriteStartElement("profil");
//			xmlWriter.WriteAttributeString("id","bel001prof");
			xmlWriter.WriteAttributeString("name", hdrVES.profName);
			xmlWriter.WriteAttributeString("type","profil"); // !!!!!!!!!!!!!!!!!!!!!!!
			xmlWriter.WriteStartElement("profildescr");
			xmlWriter.WriteEndElement();
	
			// ��������� ������ ���
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

				// ������������ � XML
				currCurve.ExportToXml(xmlWriter,gifFile);
			}

			// ��������� ������� � XML
			xmlWriter.WriteEndElement(); // curves
			xmlWriter.WriteEndElement(); // profil
			xmlWriter.WriteEndElement(); // area
			xmlWriter.Close();
		}

		/// <summary>
		/// ������� �� ����� ���������� � ����������
		/// </summary>
		/// <param name="appname">��� exe-����� ����������</param>
		/// <param name="version">������ ����������</param>
		public static void PrintGreeting(string appname, string version)
		{	
			Console.WriteLine("===================================================================");
			Console.WriteLine(" {0} v{1}", appname, version);
			Console.WriteLine(" ��������� ����������� �����  VES(VEZ) � ���� ������� XML");
			Console.WriteLine(" ������ ������ ��� �������� � ��������� ����� ������� GIF");
			Console.WriteLine(" (c)�������� �.�. 2002");
			Console.WriteLine("===================================================================");
		}

		/// <summary>
		/// ���������� ��� ����� ��� - ��������, ��������� ��� �������� ������
		/// </summary>
		/// <param name="fileName">��� ����� ���</param>
		/// <returns>��� �����</returns>
		public static VesFileType GetFileType(string fileName)
		{
			VesFileType ft = VesFileType.NotValid;

			// ������� �����
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
		/// ������ ������
		/// </summary>
		public string Version
		{
			get
			{
				return _version;
			}
		}

		/// <summary>
		/// ��� ����� ������
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
