using System;
using System.IO;
//using System.IO.IsolatedStorage;
using System.Xml;
using System.Data;
using System.Globalization;

namespace VesExplore
{
	/// <summary>
	/// �����, ����������� ����������� ����������, �����������
	/// � ���������������� ����� � ������� XML
	/// ���� ���� VesExplore.config ����������� � �������� ����������,
	/// �� �� ��������� � ����������� ���������� �� ���������
	/// </summary>
	public class Settings
	{
		#region Constructor/Dispose
		
		/// <summary>
		/// �����������
		/// </summary>
		public Settings()
		{
			// ��������, ������� �� ���� � �����������
			FileInfo fi = new FileInfo(m_settingsFileName);
			if (fi.Exists == false)
				this.initSettings();
			else
				this.loadSettings();
		}

		#endregion

		#region Fields

		private string	m_settingsFileName	= "VesExplore.config";	// ��� ����� � �����������
		
		private string	m_areaName		= "������� []";
		private string	m_profName		= "�������";
		private string	m_curveName		= "���";
		private string	m_operName		= "";
		private string	m_calcName		= "";
		private string	m_deviceName	= "���-3";
		private string	m_mn2			= (0.5F).ToString();
		private string	m_I				= "10";
		private float	[] m_ab2Arr =   { 1, 1.5F, 2.2F,   3,   5,   7,   9, 15, 20, 
										   25,  40,  65, 100, 150, 220, 380, 500 };

		private DataTable m_ab2Table;		// ������� �������� ��������� ���

		#endregion

		#region Properties

		/// <summary>
		/// ��� �������
		/// </summary>
		public string AreaName
		{
			get
			{
				return m_areaName;
			}
			set
			{
				m_areaName = value;
			}
		}
		/// <summary>
		/// ��� �������
		/// </summary>
		public string ProfilName
		{
			get
			{
				return m_profName;
			}
			set
			{
				m_profName = value;
			}
		}
		/// <summary>
		/// ��� ������
		/// </summary>
		public string CurveName
		{
			get
			{
				return m_curveName;
			}
			set
			{
				m_curveName = value;
			}
		}
		/// <summary>
		/// ����������
		/// </summary>
		public string DeviceName
		{
			get
			{
				return m_deviceName;
			}
			set
			{
				m_deviceName = value;
			}
		}
		/// <summary>
		/// ��������
		/// </summary>
		public string OperatorName
		{
			get
			{
				return m_operName;
			}
			set
			{
				m_operName = value;
			}
		}
		/// <summary>
		/// �����������
		/// </summary>
		public string CalculatorName
		{
			get
			{
				return m_calcName;
			}
			set
			{
				m_calcName = value;
			}
		}

		/// <summary>
		/// ��� mA
		/// </summary>
		public string I
		{
			get
			{
				return m_I;
			}
			set
			{
				m_I = value;
			}
		}

		/// <summary>
		/// MN/2 �����
		/// </summary>
		public string MN2
		{
			get
			{
				return m_mn2;
			}
			set
			{
				m_mn2 = value;
			}
		}

		/// <summary>
		/// ������� �������� ��������� ���
		/// </summary>
		public DataTable TableAB2
		{
			get
			{
				return m_ab2Table;
			}
			set
			{
				m_ab2Table = value;
			}
		}


		#endregion

		#region Methods

		/// <summary>
		/// ������� ������� �������� ��������� ���
		/// </summary>
		private void createTable()
		{
			// �������� �������
			// ������� AB/2
			this.m_ab2Table = new DataTable();
			
			DataColumn	_dataColumn;

			// AB/2
			_dataColumn = new DataColumn("AB2");
			_dataColumn.DataType = System.Type.GetType("System.Single");
			_dataColumn.DefaultValue = 10;
			m_ab2Table.Columns.Add(_dataColumn);

			// MN/2
			_dataColumn = new DataColumn("MN2");
			_dataColumn.DataType = System.Type.GetType("System.Single");
			_dataColumn.DefaultValue = 0.5;
			m_ab2Table.Columns.Add(_dataColumn);
		}
		
		
		/// <summary>
		/// ��������� � ������� �������� �������� �� ���������
		/// </summary>
		private void initTable()
		{
			// �������� �������
			for ( int i = 0; i < m_ab2Arr.Length; i ++ )
			{
				DataRow	_dataRow = m_ab2Table.NewRow();
				_dataRow["AB2"] = (float) m_ab2Arr[i];
				_dataRow["MN2"] = 0.5F;
				this.m_ab2Table.Rows.Add(_dataRow);
			}

		}
		
		
		/// <summary>
		/// ��������� ��������� �� ����������������� �����
		/// ���� ������ ������������
		/// </summary>
		private void loadSettings()
		{
			CultureInfo	en = new CultureInfo("en-US");	// ��� ����������� �������������� string � float

			this.createTable();

			StreamReader sr = new StreamReader(m_settingsFileName, System.Text.Encoding.GetEncoding("windows-1251"));
			XmlTextReader xmlReader = new XmlTextReader(sr);
			while (xmlReader.Read())
			{
				switch (xmlReader.Name)
				{
					case "area":		m_areaName = xmlReader.ReadString(); break;
					case "profil":		m_profName = xmlReader.ReadString(); break;
					case "curve":		m_curveName = xmlReader.ReadString(); break;
					case "operator":	m_operName = xmlReader.ReadString(); break;
					case "calculator":	m_calcName = xmlReader.ReadString(); break;
					case "device":		m_deviceName = xmlReader.ReadString(); break;
					case "i":			m_I = xmlReader.ReadString(); 
										m_I = Convert.ToSingle(m_I, en).ToString();
										break;
					case "mn2":			m_mn2 = xmlReader.ReadString(); 
										m_mn2 = Convert.ToSingle(m_mn2, en).ToString();
										break;
					case "sample":		string strAB2 = xmlReader.GetAttribute("ab2");
										string strMN2 = xmlReader.GetAttribute("mn2");

										DataRow	_dataRow = m_ab2Table.NewRow();
										_dataRow["AB2"] = Convert.ToSingle(strAB2, en);
										_dataRow["MN2"] = Convert.ToSingle(strMN2, en);
										this.m_ab2Table.Rows.Add(_dataRow);
										break;
				}
			}
			
			sr.Close();
		}
		

		/// <summary>
		/// ������� � ��������� ��������� �� ���������
		/// </summary>
		private void initSettings()
		{
			this.createTable();
			this.initTable();
			this.saveSettings();
		}
		

		/// <summary>
		/// ��������� ��������� � ���������������� �����
		/// </summary>
		private void saveSettings()
		{
			CultureInfo	en = new CultureInfo("en-US");	// ��� ����������� �������������� string � float

			FileStream fileStream = new FileStream(m_settingsFileName, FileMode.Create);
			XmlTextWriter writer = new XmlTextWriter(fileStream, System.Text.Encoding.GetEncoding("windows-1251"));
			
			writer.Formatting = Formatting.Indented;
			
			writer.WriteStartDocument();
			writer.WriteStartElement("settings");
			
			writer.WriteStartElement("area");
			writer.WriteString(m_areaName);
			writer.WriteEndElement();
			writer.WriteStartElement("profil");
			writer.WriteString(m_profName);
			writer.WriteEndElement();
			writer.WriteStartElement("curve");
			writer.WriteString(m_curveName);
			writer.WriteEndElement();
			writer.WriteStartElement("operator");
			writer.WriteString(m_operName);
			writer.WriteEndElement();
			writer.WriteStartElement("calculator");
			writer.WriteString(m_calcName);
			writer.WriteEndElement();
			writer.WriteStartElement("device");	// ����������
			writer.WriteString(m_deviceName);
			writer.WriteEndElement();
			writer.WriteStartElement("i");		// ��� mA
			writer.WriteString(Convert.ToSingle(m_I).ToString(en));
			writer.WriteEndElement();
			writer.WriteStartElement("mn2");	// MN/2 �����
			writer.WriteString( Convert.ToSingle(m_mn2).ToString(en) );
			writer.WriteEndElement();
			
			writer.WriteStartElement("samples");
			for (int i = 0; i < m_ab2Table.Rows.Count; i ++)
			{
				writer.WriteStartElement("sample");
				float v = (float) m_ab2Table.Rows[i]["AB2"];
				writer.WriteAttributeString("ab2", v.ToString(en));
				v = (float) m_ab2Table.Rows[i]["MN2"];
				writer.WriteAttributeString("mn2", v.ToString(en));
				writer.WriteEndElement();
			}
			writer.WriteEndElement(); // samples

			writer.WriteEndElement(); // settings
			
			writer.WriteEndDocument();

			writer.Flush();
			writer.Close();

			fileStream.Close();

		}
		

		/// <summary>
		/// ��������� ��������� � ���������������� �����
		/// </summary>
		public void Save()
		{
			this.saveSettings();
		}
		
		
		#endregion

	}
}
