using System;
using System.Xml;
//using System.Text.RegularExpressions;
using System.Globalization;

namespace PocketVes
{
	/// <summary>
	/// Класс работы с данными ВЭЗ, представленными в виде XML документа
	/// </summary>
	public class VesXml
	{
		#region Fields

		private XmlDocument	m_xmlDoc;
		private string		m_xmlFile;
		
		#endregion

		#region Properties
		/// <summary>
		/// XML документ
		/// </summary>
		public XmlDocument XmlDoc
		{
			get
			{
				return m_xmlDoc;
			}
		}

		#endregion

		#region Constructors/Dispose

		/// <summary>
		/// Конструктор
		/// </summary>
		public VesXml(Settings settings)
		{
			m_xmlDoc = new XmlDocument();
			this.initNewDocument(settings);
		}
		
		
		/// <summary>
		/// Конструктор
		/// </summary>
		/// <param name="FileName"></param>
		public VesXml(string FileName)
		{
			m_xmlDoc = new XmlDocument();
			m_xmlFile = FileName;
			m_xmlDoc.Load(m_xmlFile);
		}

		
		#endregion

		#region Methods

		/// <summary>
		/// Создать новый XML документ, содержащий данные из полей вспомогательного
		/// класса defaults
		/// </summary>
		/// <param name="defaults"></param>
		private void initNewDocument(Settings settings)
		{
			CultureInfo	en = new CultureInfo("en-US");	// Для правильного преобразования string в float

//			int nProfiles	= Convert.ToInt16(settings.NProfiles);
			int nProfiles	= 1;

//			int nCurves		= Convert.ToInt16(settings.NCurves);
//			int nCurves		= 0;


//			float dx		= Convert.ToSingle(settings.DX);
//			float dy		= Convert.ToSingle(settings.DY);

			// Получить список AB/2
//			string str		= settings.AB2String.Trim();

			// Удалим лишние пробелы!
//			Regex r = new Regex(@"\s+");
//			str = r.Replace(str," ");

			// Распарсим строку в массив 
//			string [] ab2List = str.Split(" ".ToCharArray());

			// Текущее время
			DateTime	dt = DateTime.Now;
			string		genStr;
			genStr = String.Format(
						"<generated app=\"{0}\" ver=\"{1}\" src=\"\" date=\"{2}\" culture=\"en-US\"/>",
						MainForm.AppName, MainForm.Version, dt.ToString() );


			m_xmlDoc.LoadXml("<?xml version=\"1.0\" encoding=\"windows-1251\" ?>"+
						   "<area name=\"" + settings.AreaName + "\">" +
						   "<areadescr>" + settings.AreaDescr + "</areadescr>" +
						   genStr +
					       "</area>");

			XmlNode root = m_xmlDoc.DocumentElement;
			// Профили
//			float y = 0;
			for (int i = 0; i < nProfiles; i ++)
			{
				string name;
				if (settings.ProfilType)
					name = String.Format("{0} {1}", settings.ProfilName, i);
				else
					name = String.Format(" {0}", i);

				XmlElement elem = m_xmlDoc.CreateElement("profil");
				elem.SetAttribute("name", name );
				
				string type = (settings.ProfilType) ? "profil" : "curve";
				elem.SetAttribute("type", type );
				XmlNode prof = root.AppendChild(elem);

				elem = m_xmlDoc.CreateElement("profildescr");
				prof.AppendChild(elem);
				elem = m_xmlDoc.CreateElement("curves");
				XmlNode curves = prof.AppendChild(elem);

				// Кривые
//				float  x = 0;
//				for (int j = 0; j < nCurves; j ++)
//				{
//					name = String.Format("{0} {1}", settings.CurveName, j);
//					elem = m_xmlDoc.CreateElement("curve");
//					elem.SetAttribute("name", name );
//					elem.SetAttribute("date", DateTime.Now.ToShortDateString());
//					elem.SetAttribute("x", x.ToString(en) );
//					elem.SetAttribute("y", y.ToString(en) );
//					elem.SetAttribute("z", "0" );
//					elem.SetAttribute("rms", "100" );
//					elem.SetAttribute("layers", "0" );
//					XmlNode curve = curves.AppendChild(elem);
//
//					elem = m_xmlDoc.CreateElement("curvedescr");
//					curve.AppendChild(elem);
//					elem = m_xmlDoc.CreateElement("operator");
//					elem.InnerText = settings.OperatorName;
//					curve.AppendChild(elem);
//					elem = m_xmlDoc.CreateElement("calculator");
//					elem.InnerText = settings.CalculatorName;
//					curve.AppendChild(elem);
//					elem = m_xmlDoc.CreateElement("weather");
//					curve.AppendChild(elem);
//					elem = m_xmlDoc.CreateElement("device");
//					elem.InnerText = settings.DeviceName;
//					curve.AppendChild(elem);
//					elem = m_xmlDoc.CreateElement("image");
//					curve.AppendChild(elem);
//
//					elem = m_xmlDoc.CreateElement("samples");
//					XmlNode samples = curve.AppendChild(elem);
//					// Отсчеты
////					for (int k = 0; k < ab2List.Length; k ++ )
////					{
////                        elem = m_xmlDoc.CreateElement("sample");
////						elem.SetAttribute("ab2",  Convert.ToSingle(ab2List[k]).ToString(en));
////						elem.SetAttribute("mn2",  Convert.ToSingle(settings.MN2).ToString(en) );
////						elem.SetAttribute("i",    Convert.ToSingle(settings.I).ToString(en) );
////						elem.SetAttribute("u",  "1" );
////						elem.SetAttribute("diap",  "100" );
////						elem.SetAttribute("ro",  "100" );
////						elem.SetAttribute("rt",  "100" );
////						elem.SetAttribute("note",  "" );
////						samples.AppendChild(elem);
////					}
//
//					// модель
//					elem = m_xmlDoc.CreateElement("layers");
//					XmlNode layers = curve.AppendChild(elem);
//					elem = m_xmlDoc.CreateElement("layer");
//					elem.SetAttribute("id",  "1" );
//					elem.SetAttribute("h",   "1" );
//					elem.SetAttribute("r",   "1" );
//					layers.AppendChild(elem);
//
//					x += dx;
//				}
//				y += dy;
			}
			
//			xmlDoc.Save("new.xml");
		}

		/// <summary>
		/// Добавить профиль в дерево XML документа
		/// </summary>
		/// <param name="defaults">Парметры профиля</param>
		/// <returns>Добавленный узел XML</returns>
		public XmlNode AddProfil(AddProfilSettings settings)
		{
			// Корневой элемент
			XmlNode root = m_xmlDoc.DocumentElement;

			// Новый элемент
			XmlElement elem = m_xmlDoc.CreateElement("profil");
			elem.SetAttribute("name", settings.Name );
			elem.SetAttribute("type", settings.Type );
			XmlNode prof = root.AppendChild(elem);
			
			elem = m_xmlDoc.CreateElement("profildescr");
			elem.InnerText = settings.Description;
			prof.AppendChild(elem);

			elem = m_xmlDoc.CreateElement("curves");
			prof.AppendChild(elem);

			return prof;
		}

		/// <summary>
		/// Удалить узел
		/// </summary>
		/// <param name="node"></param>
		/// <returns>Узел, предшествующий удаляемому узлу</returns>
		public XmlNode DeleteNode(XmlNode node)
		{
			XmlNode prevNode = node.PreviousSibling;
			node.ParentNode.RemoveChild(node);
			return prevNode;
		}

		/// <summary>
		/// Добавить кривую ВЭЗ
		/// </summary>
		/// <param name="defaults">Параметры кривой</param>
		/// <param name="parentXmlNode">Выделенный узел в дереве</param>
		/// <returns>Добавленный узел  Xml</returns>
		public XmlNode AddCurve(Settings settings, XmlNode selectedXmlNode)
		{
			CultureInfo	en = new CultureInfo("en-US");	// Для правильного преобразования string в float
			XmlNode		parentXmlNode = null;			// Этот узел будет родительским для новой кривой

			// Определим родителя
			switch(selectedXmlNode.LocalName)
			{
				case "profil"	:	
//									parentXmlNode = selectedXmlNode.SelectSingleNode("curves"); 
									parentXmlNode = selectedXmlNode; 
									foreach (XmlNode cnode in selectedXmlNode.ChildNodes)
									{
										if (cnode.LocalName == "curves")
										{
											parentXmlNode = cnode;
											break;
										}
									}

									break;
				case "curve"	:	
									parentXmlNode = selectedXmlNode.ParentNode; 
									break;
			}

			XmlElement	elem;

			elem = m_xmlDoc.CreateElement("curve");
			elem.SetAttribute("name", settings.CurveName );
			elem.SetAttribute("date", DateTime.Now.ToShortDateString());
			elem.SetAttribute("x", Convert.ToSingle(settings.X).ToString(en) );
			elem.SetAttribute("y", Convert.ToSingle(settings.Y).ToString(en) );
			elem.SetAttribute("z", Convert.ToSingle(settings.Z).ToString(en) );
			elem.SetAttribute("rms", "100" );
			elem.SetAttribute("layers", "0" );
			XmlNode curve = parentXmlNode.AppendChild(elem);

			elem = m_xmlDoc.CreateElement("curvedescr");
			elem.InnerText = settings.CurveDescr;
			curve.AppendChild(elem);
			elem = m_xmlDoc.CreateElement("operator");
			elem.InnerText = settings.OperatorName;
			curve.AppendChild(elem);
			elem = m_xmlDoc.CreateElement("calculator");
			elem.InnerText = settings.CalculatorName;
			curve.AppendChild(elem);
			elem = m_xmlDoc.CreateElement("weather");
			elem.InnerText = settings.Weather;
			curve.AppendChild(elem);
			elem = m_xmlDoc.CreateElement("device");
			elem.InnerText = settings.DeviceName;
			curve.AppendChild(elem);
			elem = m_xmlDoc.CreateElement("image");
			curve.AppendChild(elem);

			elem = m_xmlDoc.CreateElement("samples");
			XmlNode samples = curve.AppendChild(elem);
			// Отсчеты
			float f;
			int nsamples = settings.SamplesTable.Rows.Count;
            for (int i = 0; i < nsamples; i ++ )
			{
				elem = m_xmlDoc.CreateElement("sample");
				f = (float) settings.SamplesTable.Rows[i]["AB2"];
				elem.SetAttribute("ab2", f.ToString(en) );

				f = (float) settings.SamplesTable.Rows[i]["MN2"];
				elem.SetAttribute("mn2", f.ToString(en) );

				f = (float) settings.SamplesTable.Rows[i]["I"];
				elem.SetAttribute("i",   f.ToString(en)   );

				f = (float) settings.SamplesTable.Rows[i]["U"];
				elem.SetAttribute("u",   f.ToString(en) );

				f = (float) settings.SamplesTable.Rows[i]["Diap"];
				elem.SetAttribute("diap",f.ToString(en) );

				f = (float) settings.SamplesTable.Rows[i]["ROK"];
				elem.SetAttribute("ro",  f.ToString(en) );

				elem.SetAttribute("rt",  "100" );
				
				elem.SetAttribute("note", settings.SamplesTable.Rows[i]["Note"].ToString() );
				samples.AppendChild(elem);
			}
			return curve;
		}

		
		#endregion

	}
}
