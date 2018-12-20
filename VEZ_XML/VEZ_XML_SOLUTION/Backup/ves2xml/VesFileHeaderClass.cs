using System;
using System.IO;


// *************** ������ ��������� VEZ-�����  ***************************************
// ���� ������� VEZ �������� ������ � ������ ��� �� ������ �������.
// ���� ������� �� ��������� � ������ ���� �� ������ ������� � ������
// �������������� �������
//                        ���������
//    char  signat[6];   /* ��������� ����� - ������� VEZBINFILE
//    int   npoints;     /* ����� ����� ��� �� �p�����
//    float h_scale;     /* ����������� ��p��. �������� p������
//    char  areaname[40];/* ��� �������
//    char  profname[20];/* ��� �������
//    int   count;       /* ���������� ����� ������� ������ �� 1
//                      ������ � ������
//  char  ID_curve[20]; /* ������������ ������
//  float X,Y,Z;        /* ���������� ������
//  MODEL model;        /* �������������� �������
//  CURVE curve;        /* ������ ���
//  float first_absc;   /* ������ �������� �������������� ������ � �
//  float RokMin;       /* ����������� �������� �����. �������������
//  float RokMax;       /* ������������ �������� �����. �������������
//  float AB2Min;       /* ����������� �������� ������� ��/2
//  float AB2Max;       /* ������������ �������� ������� ��/2
//  int   RokDecads;    /* ����� ����� �� ��� �����. ������. ( ��� Y )
//  int   AB2Decads;    /* ����� ����� �� ��� �������� ��/2  ( ��� X )
//  float OrgRok;       /* ��������� �������� ���.���. ��������. ������
//  float OrgAB2;       /* ��������� �������� ��/2 ��������. ������
//  float RMS;          /* ������� ������������� ����������� �����
//                      /* ����������� � ������������ ������� ���
//  int   q18;          /* ���������� ����� ������ � ����� 1/8 ������
//  int   q16;          /* ���������� ����� ������ � ����� 1/6 ������
//************************************************************************************

//typedef struct _MODEL 
//		{   // ��������� - ��������� ������ �������
//			short n;                  // ����� �����
//			float ro[MAX_LAYERS];     // ������ ������������� �����
//			float h[MAX_LAYERS-1];    // ������ ��������� �����
//		} MODEL;
//
//typedef struct _CURVE 
//		{   // ��������� - ��������� ������ ���
//			short n;                  // ����� �������� �� ������
//			float fRok[MAX_SAMPLES];  // ����. �������� �����.������������� ��*�
//			float tRok[MAX_SAMPLES];  // �����.�������� �����.������������� ��*�
//			float AB2[MAX_SAMPLES];   // �������� �������� ��/2 � ������
//		} CURVE;

namespace ves2xml
{
	/// <summary>
	/// ����� ��������� VES-�����
	/// </summary>
	public class VesFileHeaderClass
	{
		/// <summary>
		/// �����������
		/// </summary>
		public VesFileHeaderClass()
		{
			// 
			// TODO: Add constructor logic here
			//
		}

		char [] fileSignature = new char[12];		// ��������� ����� - ������� VEZBINFILE_

		/// <summary>
		/// ����� ����� ��� �� �p�����
		/// </summary>
		public short  nPoints;						// ����� ����� ��� �� �p�����
		float h_scale;								// ����������� ��p��. �������� p������
		
		/// <summary>
		/// ��� �������
		/// </summary>
		public	string  areaName;					// ��� �������

		/// <summary>
		/// ��� �������
		/// </summary>
		public	string	profName;					// ��� �������
		
		short   count;								// ���������� ����� ������� ������ �� 1

		/// <summary>
		///  ��������� ��������� ��������� ����� VES �� ������<br />
		///  ����� ���������� �� ������ <b>Load()</b>
		/// </summary>
		/// <param name="stream">������� �����</param>
		private void loadFromBinFile(FileStream stream)
		{
			// ���� ����� � �������� ����� � ��������� 866
			System.Text.Encoding enc866  = System.Text.Encoding.GetEncoding(866);
			BinaryReader binRead = new BinaryReader(stream, enc866);

			fileSignature = binRead.ReadChars(12);
			nPoints = binRead.ReadInt16();
			h_scale = binRead.ReadSingle();

			char []  _areaname = new char[40];			// ��� �������
			_areaname = binRead.ReadChars(40);			// ������ �� ����� � �����
			string _str1 = new string(_areaname);		//
            areaName = _str1.Replace("\0"," ").Trim();	// ������� ������� �������
			
			char []  _profname = new char[20];			// ��� �������
			_profname = binRead.ReadChars(20);			// ������ �� ����� � �����
			string _str2 = new string(_profname);		//
			profName = _str2.Replace("\0"," ").Trim();	// ������� ������� �������

			count = binRead.ReadInt16();				// ���-�� ������ �� �������
		}

//		/// <summary>
//		/// ������������� �������
//		/// </summary>
//		string areaID;							

//		/// <summary>
//		/// ������������� �������
//		/// </summary>
//		string profilID;

		/// <summary>
		///  ��������� ��������� ����� VES �� ������. <br />
		///  ����� ������ ���� ��� ������: <br />
		///  <example>
		///  <code>
		///	// ������� �����<br />
		/// FileStream vesFile = new FileStream("evez.ves", FileMode.Open, FileAccess.Read);<br />
		/// // ��������� ���������<br />
		/// hdrVES.Load(vesFile);<br />
		/// </code>
		///  </example>
		/// </summary>
		/// <param name="stream">������� �����</param>
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
		///  ��������� ��������� ���������� ����� VEZS �� ������<br />
		///  ����� ���������� �� ������ <b>Load()</b>
		/// </summary>
		/// <param name="sr">������� �����</param>
		private void loadFromTxtFile(StreamReader sr)
		{
			// ���������� ���-�� ������ ��� � �����
			nPoints  = (short) TextVezFileParserClass.CountCurves( sr );

//			sr.BaseStream.Position = 0;
			sr.BaseStream.Seek(0, SeekOrigin.Begin);
			areaName = TextVezFileParserClass.ParseParam(sr);
			profName = TextVezFileParserClass.ParseParam(sr);
		}
	}
}
