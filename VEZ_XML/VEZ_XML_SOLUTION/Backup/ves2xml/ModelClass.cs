using System;

namespace ves2xml
{
	/// <summary>
	/// Класс, описывающий результат интерпретации
	/// </summary>
	public class ModelClass
	{
		/// <summary>
		/// Конструктор
		/// </summary>
		public ModelClass()
		{
			// 
			// TODO: Add constructor logic here
			//
		}

		/// <summary>
		/// Кол-во слоев в модели 
		/// </summary>
		public ushort nLayers;				// Кол-во слоев в модели 

		/// <summary>
		/// Массив сопротивлений слоев Омм
		/// </summary>
		public float [] Ro = new float[6];	// Массив сопротивлений слоев Омм

		/// <summary>
		/// Массив мощностей слоев м
		/// </summary>
		public float [] H  = new float[5];	// Массив мощностей слоев м
	}
}
