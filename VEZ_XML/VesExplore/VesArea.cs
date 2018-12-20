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
		/// ������������ �������
		/// </summary>
		[Category("Common"),Description("������������ �������"),Browsable(true),ReadOnly(false)]
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
		/// �������� �������
		/// </summary>
		[Category("Common"),Description("�������� �������"),Browsable(true),ReadOnly(false)]
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
		/// ��������� �������� �� ���� XML � ���� ������
		/// </summary>
		/// <param name="node">�������� ����</param>
		private void parseXmlNode(XmlNode node)
		{
			CultureInfo	en = new CultureInfo("en-US");	// ��� ����������� �������������� string � float
			// � ��� ����������� - �����, ������� ����������
			// �������� en-US

			if (node.Attributes.GetNamedItem("name") != null)
				this._name = node.Attributes.GetNamedItem("name").Value;
			
			this._description = node.SelectSingleNode("areadescr").InnerText;
		}


		#endregion
		
		#region Constructor/Dispose
		/// <summary>
		/// �����������
		/// </summary>
		/// <param name="xmlNode">���� XML, ���������� ������ �������</param>
		public VesArea(XmlNode xmlNode)
		{
			_areaXmlNode = xmlNode;
			parseXmlNode(xmlNode);
		}

		#endregion

	}
}
