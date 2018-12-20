using System;
using System.IO;

namespace ves2xml
{
	/// <summary>
	/// Вспомогательный класс для работы с текстовыми файлами VEZ
	/// </summary>
	public class TextVezFileParserClass
	{
		/// <summary>
		/// Конструктор
		/// </summary>
		public TextVezFileParserClass()
		{
			// 
			// TODO: Add constructor logic here
			//
		}

		/// <summary>
		/// Ищет в потоке строку вида <b>param : value</b> и возвращает значение value
		/// </summary>
		/// <param name="sr">Текстовый поток</param>
		/// <returns>Значение параметра</returns>
		public static string ParseParam(StreamReader sr)
		{
			string str;
			string delim   = ":";
			string comment = ";";
			string [] strArr = new string[3];
			// Пропустим лишние строки
			do 
			{
				str = sr.ReadLine();
			} while (str.IndexOf(delim) == -1);
			
			strArr = str.Split(delim.ToCharArray(),2);
			str = strArr[1].Trim();
			// Уберем комментарии
			strArr = str.Split(comment.ToCharArray(),2);
			return strArr[0].Trim();
		}

		/// <summary>
		/// Подсчитывает кол-во кривых ВЭЗ в потоке, указатель потока
		/// не сдвигается.
		/// </summary>
		/// <param name="stream"></param>
		/// <returns>Кол-во кривых ВЭЗ в потоке</returns>
		public static int CountCurves(FileStream stream)
		{
			int		cnt = 0;
			string	str;
			long	pos = stream.Position;	// Запомним позицию указателя потока
			
			StreamReader sr = new StreamReader(stream);
			
			while( (str=sr.ReadLine()) != null )
			{
				if (str.IndexOf("#curve") >= 0)  ++ cnt;
			}

			stream.Position = pos;	// Восстановим позицию указателя потока

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
			long	pos = sr.BaseStream.Position;	// Запомним позицию указателя потока
			
//			StreamReader sr = new StreamReader(stream);
			
			while( (str=sr.ReadLine()) != null )
			{
				if (str.IndexOf("#curve") >= 0)  ++ cnt;
			}

			sr.BaseStream.Position = pos;	// Восстановим позицию указателя потока

			return cnt;
		}
	}
}			

	

