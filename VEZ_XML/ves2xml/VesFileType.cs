using System;

namespace ves2xml
{
	/// <summary>
	/// ��� �������� ����� 
	/// </summary>
	public enum VesFileType
	{	
		/// <summary>
		/// �������� ���� ������� VES
		/// </summary>
		Binary,		// ��������

		/// <summary>
		/// ��������� ���� ������� VEZ
		/// </summary>
		Text,		// ���������

		/// <summary>
		/// �������� ��������� - ���� �� �������� ������ ���
		/// </summary>
		NotValid	// ��� �� ���� � ������� ���
	}
}
