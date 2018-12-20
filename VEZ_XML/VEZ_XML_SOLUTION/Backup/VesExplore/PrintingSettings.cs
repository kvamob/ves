using System;

namespace VesExplore
{
	/// <summary>
	/// Настройки для печати
	/// </summary>
	public class PrintingSettings
	{

		#region Constructor/Dispose
		public PrintingSettings()
		{
			_topMargin		= 15;
			_botMargin		= 15;
			_leftMargin		= 15;
			_righMargin		= 15;
			_module			= 50;
			_resolution		= 300;
		}
		#endregion

		#region Fields

		// Единицы - миллиметры
		private float	_topMargin;
		private float	_botMargin;
		private float	_leftMargin;
		private float	_righMargin;
		private float	_resolution;
		private float	_module;

		#endregion
		
		#region Properties

		public float TopMargin
		{
			get
			{
				return _topMargin;
			}
			set
			{
				_topMargin = value;
			}
		}

		public float BotMargin
		{
			get
			{
				return _botMargin;
			}
			set
			{
				_botMargin = value;
			}
		}

		public float LeftMargin
		{
			get
			{
				return _leftMargin;
			}
			set
			{
				_leftMargin = value;
			}
		}

		public float RighMargin
		{
			get
			{
				return _righMargin;
			}
			set
			{
				_leftMargin = value;
			}
		}

		public float Module
		{
			get
			{
				return _module;
			}
			set
			{
				_module = value;
			}
		}

		public float Resolution
		{
			get
			{
				return _resolution;
			}
			set
			{
				_resolution = value;
			}
		}


		#endregion

	}
}
