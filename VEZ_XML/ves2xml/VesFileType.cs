using System;

namespace ves2xml
{
	/// <summary>
	/// Тип входного файла 
	/// </summary>
	public enum VesFileType
	{	
		/// <summary>
		/// Двоичный файл формата VES
		/// </summary>
		Binary,		// Двоичный

		/// <summary>
		/// Текстовый файл формата VEZ
		/// </summary>
		Text,		// Текстовый

		/// <summary>
		/// Неверная сигнатура - файл не содержит кривых ВЭЗ
		/// </summary>
		NotValid	// Это не файл с кривыми ВЭЗ
	}
}
