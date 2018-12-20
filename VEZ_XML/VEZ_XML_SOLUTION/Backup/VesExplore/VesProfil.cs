using System;
using System.Xml;
using System.ComponentModel;
using System.Globalization;

namespace VesExplore
{
	/// <summary>
	/// 
	/// </summary>
	public class VesProfil
	{
		#region Constructor/Dispose
		/// <summary>
		/// Конструктор
		/// <param name="xmlNode">Узел XML, содержащий данные участка</param>
		public VesProfil(XmlNode xmlNode)
		{
			_profilXmlNode = xmlNode;
			parseXmlNode( xmlNode );
		}

		#endregion

		#region Fields

		private string _name;
		private string _description;
		private string _type;
		
		#endregion

		#region Properties

		/// <summary>
		/// Наименование профиля
		/// </summary>
		[Category("Common"),Description("Наименование профиля"),Browsable(true),ReadOnly(false)]
		public string Name
		{
			get
			{
				return _name;
			}
			set
			{
				_name = value;
				_profilXmlNode.Attributes.GetNamedItem("name").Value = value;
			}
		}

		/// <summary>
		/// Описание профиля
		/// </summary>
		[Category("Common"),Description("Описание профиля"),Browsable(true),ReadOnly(false)]
		public string ProfilDescription
		{
			get
			{
				return _description;
			}
			set
			{
				_description = value;
				_profilXmlNode.SelectSingleNode("profildescr").InnerText = value;
			}
		}

		/// <summary>
		/// Тип профиля
		/// </summary>
		[Category("Common"),Description("Тип профиля"),Browsable(true),ReadOnly(false)]
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

		
		#endregion

		#region Methods
		private	XmlNode	_profilXmlNode;
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
			if (node.Attributes.GetNamedItem("type") != null)
				this._type = node.Attributes.GetNamedItem("type").Value;
			
			this._description = node.SelectSingleNode("profildescr").InnerText;

		}

		#endregion
	}
}
