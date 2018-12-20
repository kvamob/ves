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
		private string _name	= "�������";
		private string _descr	= "";
		private string _type	= "profil";
		private	ArrayList _types;
		#endregion

		#region Constructor/Dispose
		/// <summary>
		/// ��������������� �����, ������������ ��� ���������� ������ ������� ���
		/// �������� ����� ������ ������������� (bind) � ��������� ���������� �����,
		/// ���������� ��� �������� ������ ������� (��. ����� Bindings() ������ AddProfilForm)
		/// </summary>
		public AddProfilSettings()
		{
			// ���� ��������
			_types = new ArrayList();
			_types.Add( new ProfilTypeMap("profil", "�������"));
			_types.Add( new ProfilTypeMap("curves", "��������� ������"));

			// ��������� �������� �� ��������� �� �������� ���������
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
		/// ��������� �������� �� ��������� �� �������� ���������
		/// </summary>
		private void loadDefaults()
		{
			Settings defaults = new Settings();
			_name = defaults.ProfilName;
		}

		#endregion

	}
}
