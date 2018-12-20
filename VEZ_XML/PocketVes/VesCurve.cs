using System;
using System.Data;
using System.Xml;
using System.ComponentModel;
using System.Globalization;
using System.Drawing;
using System.Drawing.Imaging;
using System.Diagnostics;

namespace PocketVes
{
	/// <summary>
	/// 
	/// </summary>
	public class VesCurve
	{
		#region Fields
		const int MAX_SAMPLES	= 100;
		const int MAX_LAYERS	= 10;

		private	XmlDocument	_xmlDoc;		// XML документ, в котором содержится экземпляр данной кривой
		private XmlNode	_curveXmlNode;		// XML узел, содержащий данную кривую

		private string	_areaName;			// Имя участка
		private string	_profilName;		// Имя профиля
		private string	_curveName;			// Имя кривой
		private string	_curveDescr;		// Наименование
		private string	_curveDate;			// Дата
		private float	_x;					// Координата x
		private float	_y;					// Координата y
		private float	_z;					// Координата z
		private float	_rms;				// Средняя относительная ошибка %
		private int		_nLayers;			// Кол-во слоев
		private string	_imageName;			// Имя файла с картинкой
		private string	_operName;			// Оператор
		private string	_calcName;			// Вычислитель
		private string	_weatherName;		// Погода
		private string	_deviceName;		// Аппаратура
		private DataTable _samplesTable;	// Отсчеты
		private DataTable _layersTable;		// Рез-ты интерпретации
		private int		_q16;				// Требуемое кол-во точек кривой с шагом 1/6 декады 
		private int		_q18;				// Требуемое кол-во точек кривой с шагом 1/8 декады 
		private float	_firstAbsc;			// Первая абсцисса рассчитываемой кривой в м

		// Параметры для рисования
		private int	_marginHoriz = 20;	// Отступы рамки от края рисунка по горизонтали, пикс
		private int	_marginVert  = 20;	// Отступы рамки от края рисунка по вертикали, пикс
		private int	_module      = 30;	// Модуль логарифмического масштаба, пикс
		private int		_RokDecads;			// Число декад по оси кажущ. сопрот. ( ось Y )
		private int		_AB2Decads;			// Число декад по оси разносов АВ/2  ( ось X )
		private float	_RokMin;			// Минимальное значение кажущ. сопротивления
		private float	_RokMax;			// Максимальное значение кажущ. сопротивления
		private float	_AB2Min;			// Минимальное значение разноса АВ/2
		private float	_AB2Max;			// Максимальное значение разноса АВ/2
		private float	_OrgRok;			// Начальное значение каж.соп. логарифм. бланка
		private float	_OrgAB2;			// Начальное значение АВ/2 логарифм. бланка
		#endregion

		#region Properties
		/// <summary>
		/// Таблица, содержащая значения отсчетов
		/// </summary>
		//		[Category("Tables"),Description("Отсчеты полевой кривой"),Browsable(true),ReadOnly(false)]
		public DataTable Samples
		{
			get
			{
				return _samplesTable;
			}
		}

		/// <summary>
		/// Таблица, содержащая значения рез-тов интерпретации
		/// </summary>
		public DataTable Layers
		{
			get
			{
				return _layersTable;
			}
		}

		/// <summary>
		/// XML документ, содержащий кривую
		/// </summary>
		public XmlDocument XmlDoc
		{
			get
			{
				return _xmlDoc;
			}
			set
			{
				_xmlDoc = value;
			}
		}

		/// <summary>
		/// Имя кривой
		/// </summary>
		public string CurveName
		{
			get
			{
				return _curveName;
			}
			set
			{
				_curveName = value;
				_curveXmlNode.Attributes.GetNamedItem("name").Value = value;
			}

		}
		/// <summary>
		/// Описание кривой
		/// </summary>
		public string Description
		{
			get
			{
				return _curveDescr;
			}
			set
			{
				_curveDescr = value;
//				_curveXmlNode.SelectSingleNode("curvedescr").InnerText = value;
				foreach (XmlNode cnode in _curveXmlNode.ChildNodes)
				{
					if ( cnode.LocalName == "curvedescr" )
					{
						cnode.InnerText = value;
						break;
					}
				}
			}
		}

		/// <summary>
		/// Имя оператора
		/// </summary>
		public string Operator
		{
			get
			{
				return _operName;
			}
			set
			{
				_operName = value;
				//				_curveXmlNode.SelectSingleNode("operator").InnerText = value;
				foreach (XmlNode cnode in _curveXmlNode.ChildNodes)
				{
					if ( cnode.LocalName == "operator" )
					{
						cnode.InnerText = value;
						break;
					}

				}
			}

		}
		/// <summary>
		/// Имя вычислителя
		/// </summary>
		public string Calculator
		{
			get
			{
				return _calcName;
			}
			set
			{
				_calcName = value;
//				_curveXmlNode.SelectSingleNode("calculator").InnerText = value;
				foreach (XmlNode cnode in _curveXmlNode.ChildNodes)
				{
					if ( cnode.LocalName == "calculator" )
					{
						cnode.InnerText = value;
						break;
					}
				}
			}
		}

		/// <summary>
		/// Погода
		/// </summary>
		public string Weather
		{
			get
			{
				return _weatherName;
			}
			set
			{
				_weatherName = value;
//				_curveXmlNode.SelectSingleNode("weather").InnerText = value;
				foreach (XmlNode cnode in _curveXmlNode.ChildNodes)
				{
					if ( cnode.LocalName == "weather" )
					{
						cnode.InnerText = value;
						break;
					}
				}
			}
		}

		/// <summary>
		/// Дата измерений
		/// </summary>
		public string Date
		{
			get
			{
				return _curveDate;
			}
			set
			{
				_curveDate = value;
				_curveXmlNode.Attributes.GetNamedItem("date").Value = value;
			}
		}

		/// <summary>
		/// Аппаратура
		/// </summary>
		public string Device
		{
			get
			{
				return _deviceName;
			}
			set
			{
				_deviceName = value;
//				_curveXmlNode.SelectSingleNode("device").InnerText = value;
				foreach (XmlNode cnode in _curveXmlNode.ChildNodes)
				{
					if ( cnode.LocalName == "device" )
					{
						cnode.InnerText = value;
						break;
					}
				}

			}
		}
		
		/// <summary>
		/// Кол-во слоев в модели
		/// </summary>
		public int NLayers
		{
			get
			{
				return _nLayers;
			}
			set
			{
				_nLayers = value;
			}
		}

		/// <summary>
		/// Координата X кривой
		/// </summary>
		public  float X
		{
			get
			{
				return _x;
			}
			set
			{
				CultureInfo	en = new CultureInfo("en-US");	// Для правильного преобразования string в float
				_x = value;
				_curveXmlNode.Attributes.GetNamedItem("x").Value = value.ToString(en);
			}
		}

		/// <summary>
		/// Координата Y кривой
		/// </summary>
		public  float Y
		{
			get
			{
				return _y;
			}
			set
			{
				CultureInfo	en = new CultureInfo("en-US");	// Для правильного преобразования string в float
				_y = value;
				_curveXmlNode.Attributes.GetNamedItem("y").Value = value.ToString(en);
			}
		}

		/// <summary>
		/// Координата Z кривой
		/// </summary>
		public  float Z
		{
			get
			{
				return _z;
			}
			set
			{
				CultureInfo	en = new CultureInfo("en-US");	// Для правильного преобразования string в float
				_z = value;
				_curveXmlNode.Attributes.GetNamedItem("z").Value = value.ToString(en);
			}
		}


		#endregion

		#region Constructor/Dispose

		/// <summary>
		/// 
		/// </summary>
		/// <param name="xmlNode"></param>
		public VesCurve(XmlNode xmlNode, XmlDocument xmlDoc)
		{
			this._curveXmlNode = xmlNode;
			this._xmlDoc = xmlDoc;

			// Создать таблицы отсчетов и слоев
			this.createTables();

			// Загрузим данные из XML DOM в переменные класса
			this.parseXmlNode(xmlNode);
		}


		#endregion

		#region Methods

		/// <summary>
		/// Извлекает значения из узла XML в поля класса
		/// </summary>
		/// <param name="xmlNode"></param>
		private void parseXmlNode(XmlNode curveNode)
		{
			string	tmpStr;
			CultureInfo	en = new CultureInfo("en-US");	// Для правильного преобразования string в float
														// У нас разделитель - точка, поэтому используем
														// культуру en-US

//			XmlNode node = curveNode.SelectSingleNode("../..");
			XmlNode node = curveNode.ParentNode.ParentNode;
			_profilName = node.Attributes.GetNamedItem("name").Value;
//			 node = curveNode.SelectSingleNode("../../..");

//			 node = node.ParentNode;
			_areaName = node.Attributes.GetNamedItem("name").Value;

			if (curveNode.Attributes.GetNamedItem("name") != null)
				this._curveName = curveNode.Attributes.GetNamedItem("name").Value;
			
			if (curveNode.Attributes.GetNamedItem("date") != null)
				this._curveDate = curveNode.Attributes.GetNamedItem("date").Value;
			else
			{	// Создадим атрибут "date"
				XmlNode attr = _xmlDoc.CreateAttribute("date");
				attr.Value = "";
				_curveXmlNode.Attributes.SetNamedItem(attr);
			}
			
			if (curveNode.Attributes.GetNamedItem("x") != null)
				this._x = Convert.ToSingle(curveNode.Attributes.GetNamedItem("x").Value, en);
			if (curveNode.Attributes.GetNamedItem("y") != null)
				this._y = Convert.ToSingle(curveNode.Attributes.GetNamedItem("y").Value, en);
			if (curveNode.Attributes.GetNamedItem("z") != null)
				this._z = Convert.ToSingle(curveNode.Attributes.GetNamedItem("z").Value, en);

			if (curveNode.Attributes.GetNamedItem("layers") != null)
				this._nLayers = Convert.ToInt16(curveNode.Attributes.GetNamedItem("layers").Value);
			
			if (curveNode.Attributes.GetNamedItem("rms")!= null)
			{
				tmpStr = curveNode.Attributes.GetNamedItem("rms").Value;
				this._rms = Convert.ToSingle(tmpStr, en);
			}

//			this._curveDescr = curveNode.SelectSingleNode("curvedescr").InnerText;
//			this._operName = curveNode.SelectSingleNode("operator").InnerText;
//			this._calcName = curveNode.SelectSingleNode("calculator").InnerText;
//			this._weatherName = curveNode.SelectSingleNode("weather").InnerText;
//			this._deviceName = curveNode.SelectSingleNode("device").InnerText;
//			this._imageName = curveNode.SelectSingleNode("image").InnerText;

			foreach (XmlNode cnode in curveNode.ChildNodes)
			{
				switch (cnode.LocalName)
				{
					case "curvedescr" : this._curveDescr = cnode.InnerText; break;
					case "operator"   : this._operName   = cnode.InnerText; break;
					case "calculator" : this._calcName   = cnode.InnerText; break;
					case "weather"    : this._weatherName= cnode.InnerText; break;
					case "device"     : this._deviceName = cnode.InnerText; break;
					case "image"      : this._imageName  = cnode.InnerText; break;
				}
			}


			// Собственно значения отсчетов
			string ab2Text, roText, rotText;
			XmlNodeList childNodeList;

			_samplesTable.Clear();

//			childNodeList = curveNode.SelectNodes("samples/sample");

//			childNodeList = curveNode.ChildNodes;
			XmlElement elem = curveNode.OwnerDocument.DocumentElement;
			elem.InnerXml = curveNode.InnerXml;
			childNodeList = elem.GetElementsByTagName("sample");

			foreach (XmlNode sampleNode in childNodeList)
			{
				if (sampleNode.LocalName == "sample")
				{
					ab2Text = sampleNode.Attributes.GetNamedItem("ab2").Value;
					roText  = sampleNode.Attributes.GetNamedItem("ro").Value;
					if (sampleNode.Attributes.GetNamedItem("rt") != null)
						rotText  = sampleNode.Attributes.GetNamedItem("rt").Value;
					else
						rotText  = "0";

					DataRow	_dataRow = _samplesTable.NewRow();
				
					_dataRow["AB2"] = Convert.ToSingle(ab2Text, en);
					_dataRow["ROK"] = Convert.ToSingle(roText, en);
					_dataRow["TROK"] = Convert.ToSingle(rotText, en);
					_samplesTable.Rows.Add(_dataRow);
				}

			} // По отсчетам

			this._firstAbsc = (float) _samplesTable.Rows[0]["AB2"];

			// Значения результатов интерпретации
			string hText, rText;
			_layersTable.Clear();

//			childNodeList = curveNode.SelectNodes("layers/layer");
//			childNodeList = curveNode.ChildNodes;

			elem = curveNode.OwnerDocument.DocumentElement;
			elem.InnerXml = curveNode.InnerXml;
			childNodeList = elem.GetElementsByTagName("layer");

			int cnt = 0;
			foreach (XmlNode layerNode in childNodeList)
			{
				if (layerNode.LocalName == "layer")
				{
					if (layerNode.Attributes.GetNamedItem("h") != null)
						hText = layerNode.Attributes.GetNamedItem("h").Value;
					else	
						break;

					if (layerNode.Attributes.GetNamedItem("r") != null)
						rText  = layerNode.Attributes.GetNamedItem("r").Value;
					else	
						break;

					if ( hText == "INFINITY")
						hText = "10000000";

					if ( rText == "INFINITY")
						hText = "10000000";

					DataRow	_dataRow = _layersTable.NewRow();

					_dataRow["H"] = Convert.ToSingle(hText, en);
					_dataRow["RO"] = Convert.ToSingle(rText, en);
					_layersTable.Rows.Add(_dataRow);
					++ cnt;

				}
			} // По слоям
			this._nLayers = cnt; // Кол-во слоев 
		}

		/// <summary>
		/// Решение обратной задачи по кривой ВЭЗ.
		/// Решение проводится методом наискорейшего спуска по О.Куфуду. 
		/// Результат заносится в соответствующие поля класса VezCurve. 
		/// Решение требует задания первого приближения для модели. 
		/// Данные о первом приближении перед вызовом функции должны
		///	быть занесены в поля таблицы _layersTable
		/// Результат интерпретации заносится в эти же поля.
		/// </summary>
		/// <param name="desiredRMS">Заданная отностительная погрешность интерпретации</param>
		/// <param name="maxIteration">Максимальное кол-во итераций</param>
		public void AutoInterp(float desiredRMS, int maxIteration )
		{
			float F;
			float Q, QV;
			float ST, XR, XA, X, B, BA, BM, BN=1, BC=1, DW, RW, TH, RM, GR, PA;
			int IC, IS, K, IK, IT, IZ, J, I, IW, IY, L=1, LB=1, JN=1, JM=1;

			float [] absc6 = new float[100];			// Значения абсцисс(разносов) с шагом 1/6 декады 
			float [] RF = new float[MAX_SAMPLES+1];		// Массив отсчетов кривой в Омм с шагом 1/6 декады 
			float [] P	= new float[2*MAX_LAYERS+1];	// Массив : сначала идут мощности слоев в модели,  
			// от верхнего к нижнему, оставшиеся значения - 
			// сопротивления слоев ( их больше на 1 )
			float [] PL		= new float [2*MAX_LAYERS+1];
			float [] G		= new float [2*MAX_LAYERS+1];
			float [] T		= new float [11]; 
			float [,] D		= new float [5, 2*MAX_LAYERS+1];
		
			bool	_goto_l_16 = false;					// Вспомогательные переменные для ветвлений по goto в тело цикла
			bool	_goto_l_25 = false;					// Вспомогательные переменные для ветвлений по goto в тело цикла
			int		_L = 0;								// Вспомогательные переменные для ветвлений по goto в тело цикла

			int nsamples = _samplesTable.Rows.Count;	// Колв-во отсчетов на полевой кривой
			float [] AB2	= new float [nsamples];		// Массив значений АВ/2 полевой кривой
			float [] ROK	= new float [nsamples];		// Массив значений Rok  полевой кривой
		
			// Перепишем значения из таблицы в массивы (так удобнее)
			int i = 0;
			foreach (DataRow cRow in _samplesTable.Rows)
			{
				AB2[i] = (float) cRow["AB2"];
				ROK[i] = (float) cRow["ROK"];
				++ i;
			}

			//		this._nLayers = _layersTable.Rows.Count;	// Откорректируем значение кол-ва слоев

			F = Convert.ToSingle(Math.Exp( Math.Log(10)/6)); // F = 1.467799 

			// Требуемое кол-во точек кривой с шагом 1/6 декады 
			this._q16 = Convert.ToInt16(Math.Ceiling(( 6*Math.Log(AB2[nsamples-1]/AB2[0])) / Math.Log(10) )) + 1;
		
			absc6[0] = this._firstAbsc; // Заполним массив  absc6
			for ( J = 1; J < this._q16; J ++ )  
				absc6[J] = absc6[J-1] * F;

			XA = this._firstAbsc;

			// Используем сплайн для получения отсчетов с шагом  1/6 декады 
			calcSpline( AB2, ROK , nsamples, absc6, RF, this._q16 );

			IK = this._nLayers - 1;
			IT = IK + this._nLayers;

			for ( I = 1; I <= IK; I ++ )
				P[I] = (float) this._layersTable.Rows[I-1]["H"];		// мощности слоев
			
			J = 0;
			for ( I = this._nLayers ; I <= IT; I ++, J ++ )
				P[I] = (float) this._layersTable.Rows[J]["RO"];		// сопротивления 

			QV = 99; 
			ST = 0; 
			IC = 0; 
			IS = 0;

			// =======  COMPUTATION OF RESISTIVITY TRANSFORM ========= 
			l_12: IC ++ ;
			l_13: XR = XA;
			J = 1; Q = 0; BM = 0;
			for ( I = 1; I <= IT; I ++ )  G[I] = 0;
			l_15: 
				X = 0.0105F * XR;
			LB = 1;

			l_16:
				for ( L = 1; L <= 9; L ++ )
				{
					if (_goto_l_16) { L=_L; _goto_l_16 = false; goto l_16_;} 
					X = X * F * F;
				l_16_:   
					B = P[IT];

					if ( B > 100000 ) B -= 100000;
					BC = B;

					for ( K = 1; K <= IK; K ++ )
					{
						DW = P[this._nLayers - K];
						RW = P[IT - K];
						if( 100000 <= DW ) DW = DW - 100000;
						if( 100000 <= RW ) RW = RW - 100000;

						TH = Convert.ToSingle(Math.Tanh( DW/X ));
						B = (B + (TH * RW))/( 1 + (TH * B / RW));
					}
					T[L] = B;
				} // for 
			// =======  COMPUTATION OF PARTIAL DERIVATES OF THE TRANSFORM =========

			X = 0.1F * X;
			L = 4;

			if ( LB > 1 ) { _L = L; _goto_l_25 = true; goto l_25; } // Заменим goto в тело цикла

			X = 0.1F * X;
			
			l_25: 
				for( L = LB; L <= 4; L ++ )
				{
					if ( _goto_l_25) {L = _L; _goto_l_25 = false; goto l_25_;}
				l_25_:   
					D[L,IT] = 1;
					B = BC;

					for ( K = 1; K <= IK; K ++ )
					{
						I =  this._nLayers - K;
						IW = IT - K;
						IY = IW + 1;
						DW = P[I];
						RW = P[IW];
						if( 100000 <= DW) DW -= 100000;
						if( 100000 <= RW) RW -= 100000;

						TH = Convert.ToSingle(Math.Tanh(DW/X));

						BA = 1 + B*TH/RW;
						PA = (1 - TH*TH)/(BA*BA);
						D[L,I]  = (RW - B*B/RW) / X;
						D[L,IW] = TH*(1 + B*B/(RW*RW) + 2*TH*B/RW)/(BA*BA);

						for( IZ = I; IZ <= IK ; IZ ++ )
							D[L,IZ] = PA * D[L,IZ];
						for( IZ = IY; IZ <= IT ; IZ ++ )
							D[L,IZ] = PA * D[L,IZ];

						B = (B + TH*RW)/(1 + TH*B/RW);
					} // for K 
					X = X*F*F;
				} // for L 

			// =======  APPLICATION OF LINEAR FILTERS =========
			RM = 0.0148F*T[1] - 0.0814F*T[2] + 0.4018F*T[3] - 1.5716F*T[4] + 1.972F*T[5];
			RM = RM + 0.1854F*T[6] + 0.1064F*T[7] - 0.0499F*T[8] + 0.0225F*T[9];

			for( L = 1; L <= 8; L ++ ) 
				T[L] = T[L+1];
			BA = 1 - RM/RF[J-1];

			for ( I = 1; I <= IT; I ++ )
			{
				if ( P[I] >= 100000 )  continue;
				B = 0.402F*D[1,I] - 1.571F*D[2,I] + 1.972F*D[3,I] + 0.186F*D[4,I];

				for( L = 1; L <= 3; L ++ ) D[L,I] = D[(L+1),I];

				G[I] = G[I] + 2*BA*B*P[I]/RM;
			}

			Q = Q + BA*BA;
			if( BM*BM < BA*BA )
			{
					BM = -BA;
				JM = J;
			}
			// ============= BRANCHING PROGRAM ============== 
			J += 2;
			L = 9;
			LB = 4;
			XR = XR*F*F;
			X = 10.5F*XR;
			
			if ( J <= nsamples ) // Заменим goto в тело цикла
			{
					_L = L; // Сохраним переменную цикла 
				_goto_l_16 = true; 
				goto l_16; 
			}
			
			if ( (J & 1) >= 1)  // проверка на четность, J нечетное 
			{
				XR = XA*F;         // next abscissa
				J = 2;
				goto l_15;
			}

			Q = Convert.ToSingle(Math.Sqrt( Q / (float) nsamples ));

			if ( QV <= Q)
			{
				IS = 1;
				for ( I = 1; I <= IT; I ++ )
					P[I] = 0.67F*PL[I] + 0.33F*P[I];
				ST = ST / 3;
				if ( 0.003 <= ST) goto l_13;
				else goto l_66;
			}
		
			if (  desiredRMS >= Q )   goto l_70;
			if ( IC >= maxIteration ) goto l_70;

			B = 0;
			// =====  COMPUTATION OF GRADIENT,STEPLENGTH AND ADJUSTEMENT
			// =====  OF THE LAYER PARAMETERS

			for ( I = 1; I <= IT; I ++ )
			{
				G[I] = G[I] / nsamples;
				B = B + G[I]*G[I];
			}

			GR = Convert.ToSingle(Math.Sqrt( B ));

			if ( IS <= 0 )
			{
				ST = (Q*Q - 0.9F*desiredRMS*desiredRMS) / GR;
				if ( ST > 0.5F ) ST = 0.5F;
			}

			for ( I = 1; I <= IT; I ++ )
			{
				PL[I] = P[I];
				P[I] = P[I]*(1 + ST*G[I] / GR);
			}

			for ( I = 1; I <= IK; I ++ )
			{
				if ( 100000 <= P[I] )
				{
					P[I] = 0;
					DW = 0;
					for ( K = 1; K <= I; K ++ )
						DW = DW + PL[K] - P[K];
					P[I] = DW;
				}
			}

			QV = Q;
			BN = BM;
			JN = JM;

			goto  l_12;
			// =========== OUTPRINT OF RESULTS =============== 
			l_66:
				for ( I = 1; I <= IT; I ++ )
					P[I] = PL[I];

			Q = QV;
			BM = BN;
			JM = JN;
			l_70:

				for ( I = 1, J = 0; I <= IK; I ++ , J ++ )
				{
					DW = P[I];
					RW = P[I + IK];
					if ( 100000 <= DW ) DW -= 100000;
					if ( 100000 <= RW ) RW -= 100000;
					this._layersTable.Rows[J]["RO"] = RW;
					this._layersTable.Rows[J]["H"]  = DW;
				}

			RW = P[IT];
			if ( 100000 <= RW) RW -= 100000;
			this._layersTable.Rows[this._nLayers-1]["RO"] = RW;

			this._rms = Q;

			// А теперь вычислим теоретическую кривую 
			// сколько надо точек с шагом 1/8 декады 
			this._q18 = Convert.ToInt16(Math.Ceiling(( 8*Math.Log( AB2[nsamples - 1] /AB2[0] )) / Math.Log(10) )) + 1;

			calcModelCurve();
 
		}

		/// <summary>
		/// Интерполяция кубическим сплайном. Коэффициенты вычисляются по всей 
		/// входной последовательности узлов.
		/// </summary>
		/// <param name="x">указатель на массив абсцисс узлов интерполяции</param>
		/// <param name="y">указатель на массив ординат узлов интерполяции</param>
		/// <param name="n">число узлов интерполяции</param>
		/// <param name="x_">массив абсцисс точек, в которых надо определить значения</param>
		/// <param name="y_">искомые значения</param>
		/// <param name="n_">число этих точек</param>
		private void calcSpline(float[] x, float[] y, int n, float[] x_, float [] y_, int n_)
		{
			float [] l = new float[MAX_SAMPLES];
			float [] m = new float[MAX_SAMPLES];
			float [] r = new float[MAX_SAMPLES];
			float [] s = new float[MAX_SAMPLES];
			int    i,j,k,cnt;
			float   d,e,p,f,h,rez,r1;
			// Вычисление коэффициентов сплайна 
			d = x[1]-x[0];
			e =(y[1]-y[0])/d;
			for ( k = 1;  k < n-1 ; k ++ )
			{ 
				h = d;
				d = x[k+1]-x[k];
				f = e;
				e = (y[k+1]-y[k])/d;
				l[k] = d/(d+h);
				r[k] = 1-l[k];
				s[k] = 6*(e-f)/(h+d);
			}
			s[0] = 0;
			l[0] = 0;

			for ( k = 1 ; k < n-1; k ++ )
			{
				p = 1/(r[k]*l[k-1]+2);
				l[k] = -l[k]*p;
				s[k] = (s[k]-r[k]*s[k-1])*p;
			}

			m[n-1] = 0;
			l[n-2] = s[n-2];
			m[n-2] = l[n-2];
			for ( k = n - 3; k >= 0 ; k -- )
			{
				l[k] = l[k]*l[k+1]+s[k];
				m[k] = l[k];
			}
			// Вычисление интерполированных значений 
			for ( cnt = 0; cnt < n_ ; cnt ++ )
			{
				i = 0;
				if ( x_[cnt]-x[n-1] > 0 )
				{ 
					d = x[n-1]-x[n-2];
					rez = d*m[n-2]/6+(y[n-1]-y[n-2])/d;
					rez = rez*(x_[cnt]-x[n-1])+y[n-1];
				}
				else
				{
					if (x_[cnt]-x[0] <=0 )
					{
						d = x[1]-x[0];
						rez = d*m[1]/6+(y[1]-y[0])/d;
						rez = rez*(x_[cnt]-x[0])+y[0];
					}
					else
					{
						while (( x_[cnt]-x[i]) > 0)  ++ i;
						j = i-1;
						d = x[i]-x[j];
						h = x_[cnt]-x[j];
						r1 = x[i]-x_[cnt];
						p = d*d/6;
						rez = (m[j]*r1*r1*r1+m[i]*h*h*h)/6/d;
						rez = rez+((y[j]-m[j]*p)*r1+(y[i]-m[i]*p)*h)/d;
					}
				} // for
				y_[cnt] = rez;
			}
		}

		/// <summary>
		/// Расчет кривой сопротивления. Кривая вычисляется с помощью фильтра Гоша в точках с шагом 
		/// по абсциссе(разносам) в 1/8 декады. 
		/// Затем для вычисления значений каж. сопротивления в точках с абсциссами, равными разносам 
		/// наблюденной кривой, вызывается метод calcSpline()
		/// </summary>
		private void calcModelCurve()
		{
			float [] t = new float [36];				// Коэффициенты фильтра
			float [] r = new float[this._nLayers];		// Массивы сопрот и мощностей
			float [] d = new float[this._nLayers];

			float [] absc8 = new float[MAX_SAMPLES];	// Значения абсцисс(разносов) с шагом 1/8 декады
			float [] ordn8 = new float[MAX_SAMPLES];	// Значения ординат(сопротив) с шагом 1/8 декады

			float f,x1,y,b,s,u,a1,a2;
			int   i9,i,j,m,n,k;
			float stp;
			int nsamples = this._samplesTable.Rows.Count;	// Кол-во отсчетов на кривой
			float [] AB2	= new float [nsamples];			// Массив значений АВ/2 полевой кривой
			float [] tROK	= new float [nsamples];			// Массив вычисленных значений Rok

			// Перепишем значения из таблицы отсчетов в массивы (так удобнее)
			i = 0;
			foreach (DataRow cRow in _samplesTable.Rows)
			{
				AB2[i] = (float) cRow["AB2"];
				tROK[i] = (float) cRow["TROK"];
				++ i;
			}
			// Перепишем значения из таблицы слоев в массивы (так удобнее)
			i = 0;
			foreach (DataRow lRow in _layersTable.Rows)
			{
				r[i] = (float) lRow["RO"];
				d[i] = (float) lRow["H"];
				++ i;
			}

			f = Convert.ToSingle(Math.Exp( Math.Log(10)/8));

			i9 = this._nLayers;			// Число слоев
			x1 = this._firstAbsc;		//  Первая абсцисса 
			this._q18 = Convert.ToInt16(Math.Ceiling(( 8* Math.Log( AB2[nsamples-1]/AB2[0] )) / Math.Log(10))) + 1;

			n = this._q18;				// Число точек кривой с шагом 1/8 декады
			y = x1/822.8F;
       
			for ( j = 1; j <= 34; j ++ )
			{
				// SUBR
				b = r[i9 - 1];                              
				for ( k = 2 ; k <= i9; k ++ )               
				{ 
					i = i9 - k;                             
					u = d[i] / y;                           
					if ( (5-u)>0 )                          
					{ 
						a1 = Convert.ToSingle(Math.Exp(u));                         
						a2 = (a1 - 1/a1)/(a1 + 1/a1);        
						b = (b + a2*r[i])/(1 + (a2*b)/r[i]); 
					}
					else b = r[i];
				} // SUBR

				t[j] = b;
				y = y*f;
			}
			stp = x1;
			for ( m = 0; m < n; m ++ )
			{
				// SUBR
				b = r[i9 - 1];                              
				for ( k = 2 ; k <= i9; k ++ )               
				{ 
					i = i9 - k;                             
					u = d[i] / y;                           
					if ( (5-u)>0 )                          
					{ 
						a1 = Convert.ToSingle(Math.Exp(u));                         
						a2 = (a1 - 1/a1)/(a1 + 1/a1);        
						b = (b + a2*r[i])/(1 + (a2*b)/r[i]); 
					}
					else b = r[i];
				} // SUBR

				t[35] = b;
				y = y*f;
				absc8[m] = stp;
				stp *= f;
				s = 42*t[1]-103*t[3]+144*t[5]-211*t[7]+330*t[9]-574*t[11];
				s = s+1184*t[13]-3162*t[15]+10219*t[17]-24514*t[19];
				s = s+18192*t[21]+6486*t[23]+1739*t[25]+79*t[27]+200*t[29];
				s = (s-106*t[31]+93*t[33]-38*t[35])/10000;
				for ( j = 1; j <= 34 ; j ++ ) 
					t[j] = t[j+1];
				ordn8[m] = s;  // Значение кажущ. сопр. с шагом 1/8 дек.
			}
			// Вычислить значения сопротивл. в точках, соответств. разносам 
			calcSpline( absc8, ordn8, this._q18, AB2, tROK, nsamples );
			
			// Переписать из массивов в таблицы
			// Отсчеты
			i = 0;
			foreach (DataRow cRow in _samplesTable.Rows)
			{
				cRow["TROK"] = (float) tROK[i];
				++ i;
			}
		}

		/// <summary>
		/// Вычисляет и возвращает среднее относительное расхождение 
		/// между практической и рассчитанной кривыми ВЭЗ
		///	Кроме того, помещает результат в поле this._rms
		/// </summary>
		/// <returns>среднее относительное расхождение между практической и рассчитанной кривыми ВЭЗ</returns>
		private float calcRms()
		{
			float rms;
			int   i;

			int nsamples = _samplesTable.Rows.Count;	// Колв-во отсчетов на полевой кривой
			float [] AB2	= new float [nsamples];		// Массив значений АВ/2 полевой кривой
			float [] ROK	= new float [nsamples];		// Массив значений Rok  полевой кривой
			float [] tROK	= new float [nsamples];		// Массив значений Rok  полевой кривой
		
			// Перепишем значения из таблицы в массивы (так удобнее)
			i = 0;
			foreach (DataRow cRow in _samplesTable.Rows)
			{
				AB2[i] = (float) cRow["AB2"];
				ROK[i] = (float) cRow["ROK"];
				tROK[i] = (float) cRow["TROK"];
				++ i;
			}
			
			if ( this._nLayers > 0 ) 
			{
				for ( i = 0, rms = 0; i < nsamples; i ++ )
				{
					rms += 100*(Math.Abs((ROK[i] - tROK[i])/((ROK[i] + tROK[i])/2)) );
				}
				rms /= nsamples;
			}
			else rms = 100;
			this._rms = rms;
			return rms;
	
		}

		/// <summary>
		/// Нарисовать кривую ВЭЗ
		/// </summary>
		/// <param name="clientDC">Контекст устройства контрола, на котором будем рисовать</param>
		/// <param name="width">Ширина области рисования в пикселах</param>
		/// <param name="height">Высота области рисования в пикселах</param>
		public void Draw(Graphics clientDC, int width, int height)
		{
			int nsamples = this._samplesTable.Rows.Count;
			float [] AB2  = new float [nsamples];	// Массив значений AB/2
			float [] fRok = new float [nsamples];	// Массив измер. значений каж. сопр.
			float [] tRok = new float [nsamples];	// Массив вычисл. значений каж. сопр.

			_AB2Min = 1000000;
			_AB2Max = -1;
			_RokMin = 1000000;
			_RokMax = -1;
			// Перепишем значения из таблицы в массивы
			int i = 0;
			foreach(DataRow cRow in _samplesTable.Rows)
			{
				AB2[i]  = (float) cRow["AB2"];
				fRok[i] = (float) cRow["ROK"];
				tRok[i] = (float) cRow["TROK"];
				if (AB2[i] > _AB2Max)	_AB2Max = AB2[i];
				if (AB2[i] < _AB2Min)	_AB2Min = AB2[i];
				if (fRok[i] > _RokMax)	_RokMax = fRok[i];
				if (fRok[i] < _RokMin)	_RokMin = fRok[i];

				if (this.NLayers > 1)
				{
					if (tRok[i] > _RokMax)	_RokMax = tRok[i];
					if (tRok[i] < _RokMin)	_RokMin = tRok[i];
				}

				++ i;
			}

			_OrgAB2 = Convert.ToSingle(Math.Pow(10,Math.Floor( Math.Log10(Convert.ToDouble(_AB2Min)))));
			_OrgRok = Convert.ToSingle(Math.Pow(10,Math.Floor( Math.Log10(Convert.ToDouble(_RokMin)))));
			_RokDecads = Convert.ToUInt16(Math.Floor(Math.Log10(_RokMax/_OrgRok))) + 1;
			_AB2Decads = Convert.ToUInt16(Math.Floor(Math.Log10(_AB2Max/_OrgAB2))) + 1;


			_module = (int) Math.Min((width - 2*_marginHoriz)/_AB2Decads, (height - 2*_marginVert)/_RokDecads);

			// Чтобы не "мерцало" изображение, рисовать будем в битмапе
//			Bitmap		bmp = new Bitmap(width, height);
//			Graphics	g =  Graphics.FromImage(bmp);
			Graphics	g =  clientDC;

			drawLogBlank(g);
			drawVesCurve(g, AB2, fRok, tRok, nsamples);

			// А теперь битмап перепишем в клиентскую область рисования
//			clientDC.DrawImage(bmp,0,0);

		}

		/// <summary>
		/// Рисовать логарифмический бланк
		/// </summary>
		/// <param name="g"></param>
		private void drawLogBlank(Graphics g)
		{
			g.Clear(Color.White);
			Pen   penDot   = new Pen(Color.LightGray); 
//			penDot.DashStyle = DashStyle.Dot;
//			penDot.Color = 

			Pen   penSolid = new Pen(Color.Black); 
			
			//Размеры рамки 
//			SizeF  sizeBord = new SizeF(_module*_AB2Decads,_module*_RokDecads);
			Size  sizeBord = new Size(_module*_AB2Decads,_module*_RokDecads);

			// Левый верхний угол рамки
//			PointF ptOrig = new PointF(_marginHoriz, _marginVert );
			Point ptOrig = new Point(_marginHoriz, _marginVert );

			// Рамка
			g.DrawRectangle(penSolid, ptOrig.X, ptOrig.Y, sizeBord.Width, sizeBord.Height);

			SolidBrush brush = new SolidBrush(Color.Black);
			Font  font = new Font("Microsoft Sans Serif", 7, FontStyle.Regular);

			// Вертикальные линии
			Point	ptBott = new Point(ptOrig.X, ptOrig.Y + sizeBord.Height );
			Point	ptTop  = new Point(ptOrig.X, ptOrig.Y);

			double x0 = Math.Pow(10,Math.Floor( Math.Log10(Convert.ToDouble(_AB2Min))));
			int j = 1;
			int k = 0;
			double x = x0;
			while ( ptBott.X < (sizeBord.Width + ptOrig.X) )
			{
				++ j;
				x = x0*j;
				ptBott.X = ptOrig.X + Convert.ToInt16(Math.Log10(x/x0)*_module) + _module*k;
				ptTop.X  = ptBott.X;
				if ( j == 10 )
				{
					j = 1; 
					x0 *= 10; 
					++ k; 
					g.DrawLine(penSolid, ptBott.X, ptBott.Y, ptTop.X, ptTop.Y);
				}
				else
					g.DrawLine(penDot, ptBott.X, ptBott.Y, ptTop.X, ptTop.Y);
			}

			// Горизонтальные линии
			Point	ptLeft  = new Point(ptOrig.X, ptOrig.Y );
			Point	ptRight = new Point(ptOrig.X + sizeBord.Width, ptOrig.Y);
			double y0 = Math.Pow(10,Math.Floor( Math.Log10(Convert.ToDouble(_RokMin))));
			j = 1;
			k = 0;
			double y = y0;
			ptLeft.Y = ptOrig.Y + sizeBord.Height;
			while ( ptLeft.Y > ptOrig.Y )
			{
				++ j;
				y = y0*j;
				ptLeft.Y = ptOrig.Y + sizeBord.Height - Convert.ToInt16(Math.Log10(y/y0)*_module) - _module*k;
				ptRight.Y  = ptLeft.Y;
				if ( j == 10 )
				{
					j = 1; 
					y0 *= 10; 
					++ k; 
					g.DrawLine(penSolid, ptLeft.X, ptLeft.Y, ptRight.X, ptRight.Y); 
				}
				else
					g.DrawLine(penDot, ptLeft.X, ptLeft.Y, ptRight.X, ptRight.Y); 
			}

			//
			//  Подписи
			//
			SizeF stringSize = new SizeF();

			// Подписи по оси абсцисс (AB/2)
			ptBott.X = ptOrig.X; 
			ptBott.Y = ptOrig.Y + sizeBord.Height + 2;
			ptTop.X = ptOrig.X;
			ptTop.Y = ptOrig.Y;
			
			double f_ab2 = Math.Pow(10,Math.Floor( Math.Log10(Convert.ToDouble(_AB2Min))));
			string s_ab2 = f_ab2.ToString();
			stringSize = g.MeasureString(s_ab2, font);	// Измерим строку
			ptTop.Y -= (int) stringSize.Height;				// Подправим положение верхних подписей
			
//			StringFormat fmt = new StringFormat();
//			fmt.Alignment = StringAlignment.Center;

			for ( int i = 0 ; i <= _AB2Decads; i ++ )
			{
//				g.DrawString(s_ab2, font, brush, ptBott, fmt); // снизу
				g.DrawString(s_ab2, font, brush, ptBott.X, ptBott.Y);
				f_ab2 *= 10;
				s_ab2 = f_ab2.ToString();
				ptBott.X += _module;
				ptTop.X  += _module;
			}

			// Подписи по оси ординат (Rok)
			ptLeft.X  = ptOrig.X;
			ptLeft.Y  = ptOrig.Y + sizeBord.Height;
			ptRight.X = ptOrig.X + sizeBord.Width;
			ptRight.Y = ptOrig.Y + sizeBord.Height;
			
			double f_rok = Math.Pow(10,Math.Floor( Math.Log10(Convert.ToDouble(_RokMin))));
			string s_rok = f_rok.ToString();
			stringSize = g.MeasureString(Math.Ceiling(_RokMax*10).ToString(), font); // Измерим строку
			ptLeft.X -= (int) stringSize.Width;							// Подправим положение
			ptLeft.Y -= (int) stringSize.Height/2;						// Подправим положение

			for ( int i = 0 ; i <= _RokDecads; i ++ )
			{
				g.DrawString(s_rok, font, brush, ptLeft.X, ptLeft.Y);  // слева
				f_rok *= 10;
				s_rok = f_rok.ToString();
				ptLeft.Y -= _module;
				ptRight.Y  -= _module;
			}

			// Наименования Осей
			// Заголовок бланка
			Font  fontHdr = new Font("Microsoft Sans Serif",8, FontStyle.Regular);
			ptTop.X = _marginHoriz + sizeBord.Width/2;
			ptTop.Y = 2;
//			fmt.Alignment = StringAlignment.Center;
			//			string hdrStr = string.Format("Участок: {0}\nПрофиль: {1}\nКривая: {2}",
			//				areaName, profName, curveName);
			string hdrStr = string.Format("Кривая: {0}", _curveName);
//			g.DrawString(hdrStr, fontHdr, brush, ptTop, fmt);
			int offs = (int) g.MeasureString(hdrStr, fontHdr).Width;
			g.DrawString(hdrStr, fontHdr, brush, ptTop.X - offs/2, ptTop.Y);
			fontHdr.Dispose();
			
			// Описание осей
			Font  fontAxis = new Font("Microsoft Sans Serif",8, FontStyle.Regular);

			ptTop.X = 0;
			ptTop.Y = _marginVert + sizeBord.Height/2;
//			fmt.Alignment = StringAlignment.Center;
			//			fmt.FormatFlags = StringFormatFlags.DirectionVertical;
			// Под углом 90 градусов
//			g.TranslateTransform( ptTop.X,ptTop.Y );
//			g.RotateTransform(-90.0F);
			//			g.DrawString("Удельное эл. сопротивление, Омм", fontAxis, brush, ptTop, fmt);
//			g.DrawString("Удельное эл. сопротивление, Омм", fontAxis, brush, 0,0, fmt);
//			g.ResetTransform();

			ptTop.X = _marginHoriz + sizeBord.Width/2;
			ptTop.Y = _marginVert + sizeBord.Height + (int) fontAxis.Size*2;
//			fmt.Dispose();
//			fmt = new StringFormat();
//			fmt.Alignment = StringAlignment.Center;
			string strBot = "AB/2, метры";
			offs = (int) g.MeasureString(strBot, fontAxis).Width;
			g.DrawString(strBot, fontAxis, brush, ptTop.X - offs/2, ptTop.Y);

			// Уберем лишнее
			penDot.Dispose();
			penSolid.Dispose();
			brush.Dispose();
			font.Dispose();
		}

		/// <summary>
		/// Рисует кривые на бланке
		/// </summary>
		/// <param name="g"></param>
		/// <param name="AB2">Массив значений AB/2</param>
		/// <param name="fRok">Массив измеренных значений сопротивления</param>
		/// <param name="tRok">Массив вычисленных значений сопротивления</param>
		/// <param name="nSamples">Кол-во отсчетов на кривой</param>
		private void drawVesCurve(Graphics g, float [] AB2, float [] fRok, float [] tRok, int nSamples)
		{
			//Размеры рамки 
			Size  sizeBord = new Size(_module*_AB2Decads,_module*_RokDecads);
			// Левый нижний угол рамки
			Point ptOrigLB = new Point(_marginHoriz, _marginVert + sizeBord.Height );
			// Значения Rok и AB/2 в левом нижнем углу рамки
			float ab2_0 = Convert.ToSingle( Math.Pow(10,Math.Floor( Math.Log10(Convert.ToDouble(_AB2Min)))) );
			float rok_0 = Convert.ToSingle( Math.Pow(10,Math.Floor( Math.Log10(Convert.ToDouble(_RokMin)))) );
			
			// Полевая кривая
			Pen   pen = new Pen(Color.Blue); //  перо
			int _ab2 = Convert.ToInt16( Math.Log10((AB2[0]/ab2_0))*_module );
			int _rok = Convert.ToInt16( Math.Log10((fRok[0]/rok_0))*_module );
			Point pt1 = new Point(ptOrigLB.X + _ab2, ptOrigLB.Y - _rok);
			Point pt2 = new Point();
			g.DrawEllipse(pen, pt1.X-2, pt1.Y-2, 4, 4);
			for ( int i = 1; i < nSamples; i ++ )
			{
				_ab2 = Convert.ToInt16( Math.Log10((AB2[i]/ab2_0))*_module );
				_rok = Convert.ToInt16( Math.Log10((fRok[i]/rok_0))*_module );
				pt2.X = ptOrigLB.X + _ab2;
				pt2.Y = ptOrigLB.Y - _rok;
				g.DrawLine(pen, pt1.X, pt1.Y, pt2.X, pt2.Y);
				pt1.X = pt2.X;
				pt1.Y = pt2.Y;
				g.DrawEllipse(pen,pt1.X-2,pt1.Y-2,4,4);
			}
			pen.Dispose();

			if (this._nLayers <= 1) return;

			// Вычисленная кривая
			Pen   pen1 = new Pen(Color.Red); // перо
//			Pen   pen2 = new Pen(Color.Red); // перо
//			pen1.DashStyle = DashStyle.Dot;
			_ab2 = Convert.ToInt16( Math.Log10((AB2[0]/ab2_0))*_module );
			_rok = Convert.ToInt16( Math.Log10((tRok[0]/rok_0))*_module );
			pt1.X = ptOrigLB.X + _ab2;
			pt1.Y = ptOrigLB.Y - _rok;
			g.DrawEllipse(pen1, pt1.X-2, pt1.Y-2, 4, 4);
			for ( int i = 1; i < nSamples; i ++ )
			{
				_ab2 = Convert.ToInt16( Math.Log10((AB2[i]/ab2_0))*_module );
				_rok = Convert.ToInt16( Math.Log10((tRok[i]/rok_0))*_module );
				pt2.X = ptOrigLB.X + _ab2;
				pt2.Y = ptOrigLB.Y - _rok;
				g.DrawLine(pen1,pt1.X, pt1.Y, pt2.X, pt2.Y);
				pt1.X = pt2.X;
				pt1.Y = pt2.Y;
				g.DrawEllipse(pen1,pt1.X-2,pt1.Y-2,4,4);
			}
			pen1.Dispose();
		}

		/// <summary>
		/// Обновить значения результатов интерпретации в XML документе
		/// </summary>
		public void UpdateLayersXml()
		{
			CultureInfo	en = new CultureInfo("en-US");	// Для правильного преобразования string в float
			// У нас разделитель - точка, поэтому используем
			// культуру en-US

			// К этому узлу будем добавлять элементы
//			XmlNode node = _curveXmlNode.SelectSingleNode("layers");
			XmlNode node = _curveXmlNode;
			foreach (XmlNode cnode in _curveXmlNode.ChildNodes)
			{
				if (cnode.LocalName == "layers")
				{
					node = cnode;
					break;
				}
			}

			node.RemoveAll();		// Удалим все дочерние узлы

			// Пройдем по таблице
			int nlayers = _layersTable.Rows.Count;
			for ( int i = 0; i < nlayers; i ++ )
			{
				// Новый элемент в документе
				XmlElement elem = _xmlDoc.CreateElement("layer");
				float h = (float) _layersTable.Rows[i]["H"];
				float r = (float) _layersTable.Rows[i]["RO"];
				// Установим его атрибуты
				elem.SetAttribute("h", h.ToString(en)); 
				elem.SetAttribute("r", r.ToString(en));
				// Добавим элемент к узлу
				node.AppendChild(elem);
			}
			_curveXmlNode.Attributes.GetNamedItem("layers").Value = nlayers.ToString();
		}

		/// <summary>
		/// Обновить значения отсчетов на кривой в XML документе
		/// </summary>
		public void UpdateSamplesXml()
		{
			CultureInfo	en = new CultureInfo("en-US");	// Для правильного преобразования string в float
			// У нас разделитель - точка, поэтому используем
			// культуру en-US

			// К этому узлу будем добавлять элементы
//			XmlNode node = _curveXmlNode.SelectSingleNode("samples");
			XmlNode node = _curveXmlNode;
			foreach (XmlNode cnode in _curveXmlNode.ChildNodes)
			{
				if (cnode.LocalName == "samples")
				{
					node = cnode;
					break;
				}
			}

			node.RemoveAll();		// Удалим все дочерние узлы

			// Пройдем по таблице
			int nsamples = _samplesTable.Rows.Count;
			for ( int i = 0; i < nsamples; i ++ )
			{
				// Новый элемент в документе
				XmlElement elem = _xmlDoc.CreateElement("sample");
				float ab2 = (float) _samplesTable.Rows[i]["AB2"];
				float ro =  (float) _samplesTable.Rows[i]["ROK"];
				float rt =  (float) _samplesTable.Rows[i]["TROK"];
				// Установим его атрибуты
				elem.SetAttribute("ab2", ab2.ToString(en)); 
				elem.SetAttribute("ro",  ro.ToString(en));
				elem.SetAttribute("rt",  rt.ToString(en));
				// Добавим элемент к узлу
				node.AppendChild(elem);
			}
		}

		/// <summary>
		/// Создать таблицы отсчетов и слоев(рез-тов интерпретации)
		/// </summary>
		private void createTables()
		{
			// Создадим таблицы
			// Отсчеты
			_samplesTable = new DataTable();
			
			DataColumn	_dataColumn;

			_dataColumn = new DataColumn("AB2");
			_dataColumn.DataType = System.Type.GetType("System.Single");
			_dataColumn.DefaultValue = 0;
			_samplesTable.Columns.Add(_dataColumn);
			_dataColumn = new DataColumn("ROK");
			_dataColumn.DefaultValue = 0;
			_dataColumn.DataType = System.Type.GetType("System.Single");
			_samplesTable.Columns.Add(_dataColumn);
			_dataColumn = new DataColumn("TROK");
			_dataColumn.DefaultValue = 0;
			_dataColumn.DataType = System.Type.GetType("System.Single");
			_samplesTable.Columns.Add(_dataColumn);

			// Результаты интерпретации
			_layersTable = new DataTable();
			
			_dataColumn = new DataColumn("H");
			_dataColumn.DataType = System.Type.GetType("System.Single");
			_dataColumn.DefaultValue = 0;
			_layersTable.Columns.Add(_dataColumn);
			_dataColumn = new DataColumn("RO");
			_dataColumn.DefaultValue = 10;
			_dataColumn.DataType = System.Type.GetType("System.Single");
			_layersTable.Columns.Add(_dataColumn);
	
		}
	

		#endregion
	}
}
