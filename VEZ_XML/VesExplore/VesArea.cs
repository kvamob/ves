using System;
using System.Xml;
using System.ComponentModel;
using System.Globalization;

namespace VesExplore
{
	/// <summary>
	/// 
	/// </summary>
	public class VesArea
	{

		#region Fields
		private string		_name;
		private string		_description;
		private XmlNode		_areaXmlNode;
		#endregion

		#region Properties
		/// <summary>
		/// Наименование участка
		/// </summary>
		[Category("Common"),Description("Наименование участка"),Browsable(true),ReadOnly(false)]
		public string AreaName
		{
			get
			{
				return _name;
			}
			set
			{
				_name = value;
				_areaXmlNode.Attributes.GetNamedItem("name").Value = value;
			}
		}

		/// <summary>
		/// Описание участка
		/// </summary>
		[Category("Common"),Description("Описание участка"),Browsable(true),ReadOnly(false)]
		public string Description
		{
			get
			{
				return _description;
			}
			set
			{
				_description = value;
				_areaXmlNode.SelectSingleNode("areadescr").InnerText = value;
			}
		}

		#endregion
		
		#region Methods
		/// <summary>
		/// Извлекает значения из узла XML в поля класса
		/// </summary>
		/// <param name="node">Исходный узел</param>
		private void parseXmlNode(XmlNode node)
		{
			CultureInfo	en = new CultureInfo("en-US");	// Для правильного преобразования string в float
			// У нас разделитель - точка, поэтому используем
			// культуру en-US

			if (node.Attributes.GetNamedItem("name") != null)
				this._name = node.Attributes.GetNamedItem("name").Value;
			
			this._description = node.SelectSingleNode("areadescr").InnerText;
		}


		#endregion
		
		#region Constructor/Dispose
		/// <summary>
		/// Конструктор
		/// </summary>
		/// <param name="xmlNode">Узел XML, содержащий данные участка</param>
		public VesArea(XmlNode xmlNode)
		{
			_areaXmlNode = xmlNode;
			parseXmlNode(xmlNode);
		}

		#endregion

	}
}
