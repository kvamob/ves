using System;

namespace ves2xml
{
	/// <summary>
	/// �����, ����������� ��������� �������������
	/// </summary>
	public class ModelClass
	{
		/// <summary>
		/// �����������
		/// </summary>
		public ModelClass()
		{
			// 
			// TODO: Add constructor logic here
			//
		}

		/// <summary>
		/// ���-�� ����� � ������ 
		/// </summary>
		public ushort nLayers;				// ���-�� ����� � ������ 

		/// <summary>
		/// ������ ������������� ����� ���
		/// </summary>
		public float [] Ro = new float[6];	// ������ ������������� ����� ���

		/// <summary>
		/// ������ ��������� ����� �
		/// </summary>
		public float [] H  = new float[5];	// ������ ��������� ����� �
	}
}
