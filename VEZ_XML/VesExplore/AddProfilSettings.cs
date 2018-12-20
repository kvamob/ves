using System;
using System.Collections;

namespace VesExplore
{
	/// <summary>
	/// 
	/// </summary>
	public class AddProfilSettings
	{
		#region Fields
		private string _name	= "Профиль";
		private string _descr	= "";
		private string _type	= "profil";
		private	ArrayList _types;
		#endregion

		#region Constructor/Dispose
		/// <summary>
		/// Вспомогательный класс, используемый для добавления нового профиля ВЭЗ
		/// Свойства этого класса прикрепляются (bind) к элементам управления формы,
		/// вызываемой при создании нового профиля (см. метод Bindings() класса AddProfilForm)
		/// </summary>
		public AddProfilSettings()
		{
			// Типы профилей
			_types = new ArrayList();
			_types.Add( new ProfilTypeMap("profil", "Профиль"));
			_types.Add( new ProfilTypeMap("curves", "Отдельные кривые"));

			// Загрузить значения по умолчанию из настроек программы
			this.loadDefaults();	

		}

		#endregion

		#region Properties
		public string Name
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

		public string Description
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

		public string Type
		{
			get
			{
				return _type;
			}
			set
			{
				_type = value;
			}
		}

		public ArrayList Types
		{
			get
			{
				return _types;
			}
//			set
//			{
//				_types = value;
//			}
		}

		#endregion

		#region Methods

		/// <summary>
		/// Загрузить значения по умолчанию из настроек программы
		/// </summary>
		private void loadDefaults()
		{
			Settings defaults = new Settings();
			_name = defaults.ProfilName;
		}

		#endregion

	}
}
