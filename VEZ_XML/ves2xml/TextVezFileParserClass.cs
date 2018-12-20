using System;
using System.IO;

namespace ves2xml
{
	/// <summary>
	/// ��������������� ����� ��� ������ � ���������� ������� VEZ
	/// </summary>
	public class TextVezFileParserClass
	{
		/// <summary>
		/// �����������
		/// </summary>
		public TextVezFileParserClass()
		{
			// 
			// TODO: Add constructor logic here
			//
		}

		/// <summary>
		/// ���� � ������ ������ ���� <b>param : value</b> � ���������� �������� value
		/// </summary>
		/// <param name="sr">��������� �����</param>
		/// <returns>�������� ���������</returns>
		public static string ParseParam(StreamReader sr)
		{
			string str;
			string delim   = ":";
			string comment = ";";
			string [] strArr = new string[3];
			// ��������� ������ ������
			do 
			{
				str = sr.ReadLine();
			} while (str.IndexOf(delim) == -1);
			
			strArr = str.Split(delim.ToCharArray(),2);
			str = strArr[1].Trim();
			// ������ �����������
			strArr = str.Split(comment.ToCharArray(),2);
			return strArr[0].Trim();
		}

		/// <summary>
		/// ������������ ���-�� ������ ��� � ������, ��������� ������
		/// �� ����������.
		/// </summary>
		/// <param name="stream"></param>
		/// <returns>���-�� ������ ��� � ������</returns>
		public static int CountCurves(FileStream stream)
		{
			int		cnt = 0;
			string	str;
			long	pos = stream.Position;	// �������� ������� ��������� ������
			
			StreamReader sr = new StreamReader(stream);
			
			while( (str=sr.ReadLine()) != null )
			{
				if (str.IndexOf("#curve") >= 0)  ++ cnt;
			}

			stream.Position = pos;	// ����������� ������� ��������� ������

			return cnt;
		}
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="sr"></param>
		/// <returns></returns>
		public static int CountCurves(StreamReader sr)
		{
			int		cnt = 0;
			string	str;
			long	pos = sr.BaseStream.Position;	// �������� ������� ��������� ������
			
//			StreamReader sr = new StreamReader(stream);
			
			while( (str=sr.ReadLine()) != null )
			{
				if (str.IndexOf("#curve") >= 0)  ++ cnt;
			}

			sr.BaseStream.Position = pos;	// ����������� ������� ��������� ������

			return cnt;
		}
	}
}			

	

