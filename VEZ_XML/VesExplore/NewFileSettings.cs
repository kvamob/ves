using System;
using System.Globalization;

namespace VesExplore
{
	/// <summary>
	/// Вспомогательный класс, используемый для создания нового XML файла данных ВЭЗ
	/// Свойства этого класса прикрепляются (bind) к элементам управления формы,
	/// вызываемой при создании нового файла (см. метод Bindings() класса NewFileForm)
	/// <seealso cref="метод Bindings() класса NewFileForm"/>
	/// </summary>
	public class NewFileSettings
	{
		#region Constructor/Dispose
		public NewFileSettings()
		{
			// Загрузить значения по умолчанию из настроек программы
			this.loadDefaults();	
		}

		#endregion

		#region Fields
		private string	_areaName;			// Имя участка
		private string	_areaDescr;			// Описание участка
		private string	_profName;			// Имя профиля
		private bool	_profTypeIsProfil;	// Тип профиля. Если true - то profil, иначе - curves
		private string	_nProfiles;			// Кол-во профилей
		private string	_curveName;			// Имя кривой
		private string	_nCurves;			// Кол-во кривых
		private string	_operator;			// Оператор
		private string	_calculator;		// Вычислитель
		private string	_device;			// Аппаратура
		private string	_mn2;				// MN/2 метры
		private string	_i;					// Ток mA
		private string	_ab2String;			// Строка, содержащая значения разносов AB/2 через пробелы
		private string	_dy;				// Шаг между профилями, м
		private string	_dx;				// Шаг между точками по профилю, м
		private DateTime _date;				// Дата наблюдений

		#endregion

		#region Properties

		public string AreaName
		{
			get
			{
				return _areaName;
			}
			set
			{
				_areaName = value;
			}
		}

		public string AreaDescr
		{
			get
			{
				return _areaDescr;
			}
			set
			{
				_areaDescr = value;
			}
		}

		public string ProfName
		{
			get
			{
				return _profName;
			}
			set
			{
				_profName = value;
			}
		}

		/// <summary>
		/// Тип профиля. Если true - то profil, иначе - curves
		/// </summary>
		public bool TypeProf
		{
			get
			{
				return _profTypeIsProfil;
			}
			set
			{
				_profTypeIsProfil = value;
			}
		}

		public decimal NProfiles
		{
			get
			{
				return Convert.ToDecimal(_nProfiles);
			}
			set
			{
				_nProfiles = value.ToString();
			}
		}

		public string CurveName
		{
			get
			{
				return _curveName;
			}
			set
			{
				_curveName = value;
			}
		}

		public string NCurves
		{
			get
			{
				return _nCurves;
			}
			set
			{
				_nCurves = value;
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

		public string DeviceName
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

		public string MN2
		{
			get
			{
				return _mn2;
			}
			set
			{
				_mn2 = value;
			}
		}

		public string I
		{
			get
			{
				return _i;
			}
			set
			{
				_i = value;
			}
		}

		public string AB2String
		{
			get
			{
				return _ab2String;
			}
			set
			{
				_ab2String = value;
			}
		}

		public string DY
		{
			get
			{
				return _dy;
			}
			set
			{
				_dy = value;
			}
		}	
		
		public string DX
		{
			get
			{
				return _dx;
			}
			set
			{
				_dx = value;
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


		#endregion

		#region Methods
		
		/// <summary>
		/// Загрузить значения по умолчанию из настроек программы
		/// </summary>
		/// <returns></returns>
		private void loadDefaults()
		{
			// Для правильного преобразования string в float
//			CultureInfo	en = new CultureInfo("en-US");	

			Settings defaults = new Settings();

			_areaName	= defaults.AreaName;
			_areaDescr	= "";
			_profName	= defaults.ProfilName;
			_nProfiles	= "1";
			_profTypeIsProfil = true;
			_curveName	= defaults.CurveName;
			_nCurves	= "10";
			_operator	= defaults.OperatorName;
			_calculator	= defaults.CalculatorName;
			_device		= defaults.DeviceName;
			_mn2		= defaults.MN2;
			_i			= defaults.I;
			_dy			= "20";
			_dx			= "10";
			_date		= DateTime.Now;

//			_ab2String	= "1 1.5 2.2 3 5 7 9 15 20 25 40 65 100 150 220 380 500";
			_ab2String = "";
			for (int i = 0; i < defaults.TableAB2.Rows.Count; i ++)
			{
				float  v = (float) defaults.TableAB2.Rows[i]["AB2"];
//				string str = String.Format("{0} ", v.ToString(en));
				string str = String.Format("{0} ", v.ToString() );
				_ab2String += str;
			}

		}

		#endregion

	}
}
