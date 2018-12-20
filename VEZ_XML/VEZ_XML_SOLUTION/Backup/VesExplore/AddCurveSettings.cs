using System;
using System.Data;
using System.Globalization;

namespace VesExplore
{
	/// <summary>
	/// ��������������� �����, ������������ ��� ���������� ����� ������ ���
	/// �������� ����� ������ ������������� (bind) � ��������� ���������� �����,
	/// ���������� ��� �������� ����� ������ (��. ����� Bindings() ������ AddCurveForm)
	/// </summary>
	public class AddCurveSettings
	{
		#region Constructors
		public AddCurveSettings()
		{
			// ��������� �����
			_date = DateTime.Now;
	
			// �������� �������� �� ��������� �� �������� ���������
			this.loadDefaults();	

		}

		#endregion

		#region Fields
		private string	_name		= "���";
		private string	_descr		= "";
		private string	_device		= "���-3";
		private string	_operator	= "";
		private string	_calculator	= "";
		private string	_weather	= "";
		private DateTime _date;
		private string	_x			= "0";
		private string	_y			= "0";
		private string	_z			= "0";
		private DataTable	_samplesTable;
		#endregion

		#region Properties
		public string CurveName
		{
			get
			{
				return _name;
			}
			set
			{
				_name = value;
			}
		}

		public string CurveDescr
		{
			get
			{
				return _descr;
			}
			set
			{
				_descr = value;
			}
		}

		public string Device
		{
			get
			{
				return _device;
			}
			set
			{
				_device = value;
			}
		}

		public string OperatorName
		{
			get
			{
				return _operator;
			}
			set
			{
				_operator = value;
			}
		}

		public string CalculatorName
		{
			get
			{
				return _calculator;
			}
			set
			{
				_calculator = value;
			}
		}

		public string Weather
		{
			get
			{
				return _weather;
			}
			set
			{
				_weather = value;
			}
		}

		public DateTime Date
		{
			get
			{
				return _date;
			}
			set
			{
				_date = value;
			}
		}

		public string X
		{
			get
			{
				return _x;
			}
			set
			{
				_x = value;
			}
		}

		public string Y
		{
			get
			{
				return _y;
			}
			set
			{
				_y = value;
			}
		}

		public string Z
		{
			get
			{
				return _z;
			}
			set
			{
				_z = value;
			}
		}

		public DataTable SamplesTable
		{
			get
			{
				return _samplesTable;
			}
//			set
//			{
//				_samplesTable = value;
//			}
		}

		#endregion

		#region Methods

		/// <summary>
		/// ������� ������� ��������
		/// </summary>
		private void createTable()
		{
			// �������� �������
			// �������
			this._samplesTable = new DataTable();
			
			DataColumn	_dataColumn;

			// AB/2
			_dataColumn = new DataColumn("AB2");
			_dataColumn.DataType = System.Type.GetType("System.Single");
			_dataColumn.DefaultValue = 10;
			_samplesTable.Columns.Add(_dataColumn);

			// MN/2
			_dataColumn = new DataColumn("MN2");
			_dataColumn.DataType = System.Type.GetType("System.Single");
			_dataColumn.DefaultValue = 0.5;
			_samplesTable.Columns.Add(_dataColumn);

			// �����. ���������
			_dataColumn = new DataColumn("K");
			_dataColumn.DataType = System.Type.GetType("System.Single");
			_dataColumn.Expression = "3.14159*(AB2*AB2 - MN2*MN2)/(2*MN2)";
			_samplesTable.Columns.Add(_dataColumn);

			// ������ ���-3
			_dataColumn = new DataColumn("U");
			_dataColumn.DataType = System.Type.GetType("System.Single");
			_dataColumn.DefaultValue = 50;
			_samplesTable.Columns.Add(_dataColumn);

			// �������� ���-3
			_dataColumn = new DataColumn("Diap");
			_dataColumn.DataType = System.Type.GetType("System.Single");
			_dataColumn.DefaultValue = 1;
			_samplesTable.Columns.Add(_dataColumn);

			// ��� mA
			_dataColumn = new DataColumn("I");
			_dataColumn.DataType = System.Type.GetType("System.Single");
			_dataColumn.DefaultValue = 10;
			_samplesTable.Columns.Add(_dataColumn);

			// ���. ������. ���
			_dataColumn = new DataColumn("ROK");
			_dataColumn.DataType = System.Type.GetType("System.Single");
			_dataColumn.Expression = "(K*((U*Diap)/100)/I)";
			_samplesTable.Columns.Add(_dataColumn);

			// ����������
			_dataColumn = new DataColumn("Note");
			_dataColumn.DataType = System.Type.GetType("System.String");
			_dataColumn.DefaultValue = "";
			_samplesTable.Columns.Add(_dataColumn);

		}

		/// <summary>
		/// ��������� �������� �� ��������� �� �������� ���������
		/// </summary>
		private void loadDefaults()
		{
			CultureInfo	en = new CultureInfo("en-US");	// ��� ����������� �������������� string � float

			Settings defaults = new Settings();
			
			_name = defaults.CurveName;
			_operator = defaults.OperatorName;
			_calculator = defaults.CalculatorName;
			_device = defaults.DeviceName;

			// �������� ������� �������� 
			this.createTable();

			// �������� �������
			this.createTable();
			
			// �������� ��
			for ( int i = 0; i < defaults.TableAB2.Rows.Count; i ++ )
			{
				DataRow	_dataRow = _samplesTable.NewRow();
				_dataRow["AB2"] = (float) defaults.TableAB2.Rows[i]["AB2"];
				_dataRow["MN2"] = (float) defaults.TableAB2.Rows[i]["MN2"];
				_dataRow["Diap"] = 100;
				_dataRow["U"] = 50;
				_dataRow["I"] = Convert.ToSingle(defaults.I, en);
				this._samplesTable.Rows.Add(_dataRow);
			}
		}

		
		#endregion
	}
}
