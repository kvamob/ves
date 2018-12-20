using System;

namespace PocketVes
{
	/// <summary>
	/// ����� ���� hash �������
	/// ������ ��� ����������� ����� ��������
	/// </summary>
	public class ProfilTypeMap
	{
		#region Fields
		private string _key;
		private string _val;
		#endregion
		
		#region Condtructor/Dispose
		public ProfilTypeMap(string key, string val )
		{
			_key = key;
			_val = val;
		}
		#endregion

		#region Proporties
		public string Type
		{
			get
			{
				return _key;
			}
			set
			{
				_key = value;
			}
		}

		public string Name
		{
			get
			{
				return _val;
			}
			set
			{
				_val = value;
			}
		}

		#endregion

	}
}
