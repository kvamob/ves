using System;
using System.IO;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.Drawing.Text;
using System.Xml;
using System.Globalization;


namespace ves2xml
{
	/// <summary>
	/// Класс кривой ВЭЗ
	/// </summary>
	public class CurveClass
	{
		/// <summary>
		/// Конструктор
		/// </summary>
		public CurveClass()
		{
			// 
			// TODO: Add constructor logic here
			//
		}

		/// <summary>
		/// Кол-во отсчетов на кривой
		/// </summary>
		public ushort nSamples;					// Кол-во отсчетов на кривой

		/// <summary>
		/// Массив измеренных значений Омм
		/// </summary>
		public float [] fRok = new float[50];	// Массив измеренных значений Омм

		/// <summary>
		/// Массив вычисленных значений Омм
		/// </summary>
		public float [] tRok = new float[50];	// Массив вычисленных значений Омм

		/// <summary>
		/// Массив значений AB/2 метры
		/// </summary>
		public float [] AB2  = new float[50];	// Массив значений AB/2 метры
		
		/// <summary>
		/// Имя кривой
		/// </summary>
		public string curveName;                // Имя кривой

		/// <summary>
		/// Код
		/// </summary>
		public int hashCode;

		/// <summary> 
		/// Идентификатор кривой
		/// </summary>
		public string id;

		/// <summary>
		/// Наименование участка
		/// </summary>
		public string areaName;
		
		/// <summary>
		/// Наименование профиля
		/// </summary>
		public string profName;

		float X,Y,Z;        // Координаты кривой
		ModelClass model = new ModelClass();      // Характеристики разреза(результаты интерпретации)
		
		float first_absc; // Первая абсцисса рассчитываемой кривой в м
		float RokMin;     // Минимальное значение кажущ. сопротивления
		float RokMax;     // Максимальное значение кажущ. сопротивления
		float AB2Min;     // Минимальное значение разноса АВ/2
		float AB2Max;     // Максимальное значение разноса АВ/2
		int   RokDecads;  // Число декад по оси кажущ. сопрот. ( ось Y )
		int   AB2Decads;  // Число декад по оси разносов АВ/2  ( ось X )
		float OrgRok;     // Начальное значение каж.соп. логарифм. бланка
		float OrgAB2;     // Начальное значение АВ/2 логарифм. бланка
		float RMS;        // Среднее относительное расхождение между
		                  // наблюденной и рассчитанной кривыми ВЭЗ
		int   q18;        // Количество точек кривой с шагом 1/8 декады
		int   q16;        // Количество точек кривой с шагом 1/6 декады

		// Параметры для построения кривой на бланке
		// Множитель 2.835 - пересчет из мм в пикселы
//		float	marginHoriz = 15*2.835F; // Отступы рамки от края листа по горизонтали, мм
//		float	marginVert  = 15*2.835F; // Отступы рамки от края листа по вертикали, мм
//		float	module      = 50*2.835F; // Модуль логарифмического масштаба, мм
//		float	marginHoriz = 15*1F; // Отступы рамки от края листа по горизонтали, мм
//		float	marginVert  = 15*1F; // Отступы рамки от края листа по вертикали, мм
//		float	module      = 50*1F; // Модуль логарифмического масштаба, мм
//		float	marginHoriz = 15*8.5F; // Отступы рамки от края листа по горизонтали, мм
//		float	marginVert  = 15*8.5F; // Отступы рамки от края листа по вертикали, мм
//		float	module      = 50*8.5F; // Модуль логарифмического масштаба, мм
		float	marginHoriz = 15*7.874F; // Отступы рамки от края листа по горизонтали, мм
		float	marginVert  = 15*7.874F; // Отступы рамки от края листа по вертикали, мм
		float	module      = 50*7.874F; // Модуль логарифмического масштаба, мм

		/// <summary>
		/// Загрузить кривую из двоичного ВЭЗ файла (формат VES)<br />
		/// Метод вызывается из метода <b>Load()</b>
		/// </summary>
		/// <param name="stream">Входной поток</param>
		private void loadFromBinFile(FileStream stream)
		{
			// Весь текст в исходном файле в кодировке 866
			System.Text.Encoding enc866  = System.Text.Encoding.GetEncoding(866);
			BinaryReader binRead = new BinaryReader(stream, enc866);

			char  [] _curvename = new char[20];
			_curvename = binRead.ReadChars(20); // Читаем имя кривой

			string _str = new String(_curvename);
			curveName = _str.Replace("\0"," ").Trim(); // В имени убираем нулевые символы

			//
			hashCode = curveName.GetHashCode();

			id = System.Guid.NewGuid().ToString("N");
            hashCode = id.GetHashCode();
			//
			X = binRead.ReadSingle();
			Y = binRead.ReadSingle();
			Z = binRead.ReadSingle();
			model.nLayers = binRead.ReadUInt16();
			// Результат интерпретации
			for (int i = 0; i < 6; i ++) 
				model.Ro[i] = binRead.ReadSingle();
			for (int i = 0; i < 5; i ++) 
				model.H[i] = binRead.ReadSingle();
            // CURVE
			nSamples = binRead.ReadUInt16();
			for (int i = 0; i < 50; i ++) 
				fRok[i] = binRead.ReadSingle();
			for (int i = 0; i < 50; i ++) 
				tRok[i] = binRead.ReadSingle();
			for (int i = 0; i < 50; i ++) 
				AB2[i] = binRead.ReadSingle();
			
			first_absc = binRead.ReadSingle();
			RokMin = binRead.ReadSingle();
			RokMax = binRead.ReadSingle();
			AB2Min = binRead.ReadSingle();
			AB2Max = binRead.ReadSingle();
			RokDecads = binRead.ReadUInt16();
			AB2Decads = binRead.ReadUInt16();
			OrgRok = binRead.ReadSingle();
			OrgAB2 = binRead.ReadSingle();
			RMS    = binRead.ReadSingle();
			q18    = binRead.ReadUInt16();
			q16    = binRead.ReadUInt16();
		}

		/// <summary>
		/// Вывести кривую в файл формата GIF
		/// </summary>
		/// <param name="fileName">Имя выходного файла формата GIF</param>
		public void Draw( string fileName )
		{
			// 72  pixels/inch = 28,346 pixels/cm
			// 200 pixels/inch = 78,74  pixels/cm
			// 300 pixels/inch = 118,11 pixels/cm

			// Вычислим размер необходимого битмапа
//			int width  = Convert.ToInt16((AB2Decads*module + 2*marginHoriz)*7.874F);
//			int height = Convert.ToInt16((RokDecads*module + 2*marginVert)*7.874F);
			// Ед измерения pixel
//			int width  = Convert.ToInt16((AB2Decads*module + 2*marginHoriz));
//			int height = Convert.ToInt16((RokDecads*module + 2*marginVert));
			// Ед измерения document
//			int width  = Convert.ToInt16((AB2Decads*module + 2*marginHoriz))/3;
//			int height = Convert.ToInt16((RokDecads*module + 2*marginVert))/3;
			int width  = Convert.ToInt16((AB2Decads*module + 2*marginHoriz));
			int height = Convert.ToInt16((RokDecads*module + 2*marginVert));
			// Ед измерения mm
//			int width  = Convert.ToInt16((AB2Decads*module + 2*marginHoriz)*8F);
//			int height = Convert.ToInt16((RokDecads*module + 2*marginVert)*8F);

			Bitmap bmp = new Bitmap(width, height, PixelFormat.Format32bppArgb);
//			bmp.SetResolution(72,72); // Теперь 1 pixel = 1 мм
			bmp.SetResolution(200,200); // Теперь 1 pixel = 1 мм

			Graphics g = Graphics.FromImage(bmp); // Здесь будем рисовать
//			g.TextRenderingHint = TextRenderingHint.SystemDefault;
//			g.TextRenderingHint = TextRenderingHint.AntiAliasGridFit;
//			g.SmoothingMode = SmoothingMode.Default;

			// Единицы - миллиметры
//			g.PageUnit = GraphicsUnit.Millimeter;
//			g.PageScale = 1F;

			g.PageUnit = GraphicsUnit.Pixel;
//			g.PageUnit = GraphicsUnit.Document;
//			g.PageScale = 1F;

			drawLogBlank(g);
			drawVesCurve(g);

			// битмап в файл
			bmp.Save(fileName, ImageFormat.Tiff );

			g.Dispose();
			bmp.Dispose();
		}

		/// <summary>
		/// Рисовать логарифмический бланк
		/// </summary>
		private void drawLogBlank(Graphics g)
		{
			g.Clear(Color.White);
			Pen   penDot   = new Pen(Color.Black, 0.5F); 
			penDot.DashStyle = DashStyle.Dot;

			Pen   penSolid = new Pen(Color.Black, 0.5F); 
			
			//Размеры рамки 
			SizeF  sizeBord = new SizeF(module*AB2Decads,module*RokDecads);
			// Левый верхний угол рамки
			PointF ptOrig = new PointF(marginHoriz, marginVert );

			// Рамка
			g.DrawRectangle(penSolid, ptOrig.X, ptOrig.Y, sizeBord.Width, sizeBord.Height);

			SolidBrush brush = new SolidBrush(Color.Black);
			Font  font = new Font("Microsoft Sans Serif",7);
//			Font  font = new Font("Courier",10,GraphicsUnit.Point);

			// Вертикальные линии
			PointF	ptBott = new PointF(ptOrig.X, ptOrig.Y + sizeBord.Height );
			PointF	ptTop  = new PointF(ptOrig.X, ptOrig.Y);
			double x0 = Math.Pow(10,Math.Floor( Math.Log10(Convert.ToDouble(AB2Min))));
			int j = 1;
			int k = 0;
			double x = x0;
			while ( ptBott.X < (sizeBord.Width + ptOrig.X) )
			{
				++ j;
				x = x0*j;
				ptBott.X = ptOrig.X + Convert.ToSingle(Math.Log10(x/x0)*module) + module*k;
				ptTop.X  = ptBott.X;
				if ( j == 10 )
				{	j = 1; 
					x0 *= 10; 
					++ k; 
					g.DrawLine(penSolid, ptBott, ptTop);
				}
				else
					g.DrawLine(penDot, ptBott, ptTop);
			}

			// Горизонтальные линии
			PointF	ptLeft  = new PointF(ptOrig.X, ptOrig.Y );
			PointF	ptRight = new PointF(ptOrig.X + sizeBord.Width, ptOrig.Y);
			double y0 = Math.Pow(10,Math.Floor( Math.Log10(Convert.ToDouble(RokMin))));
			j = 1;
			k = 0;
			double y = y0;
			ptLeft.Y = ptOrig.Y + sizeBord.Height;
			while ( ptLeft.Y > ptOrig.Y )
			{
				++ j;
				y = y0*j;
				ptLeft.Y = ptOrig.Y + sizeBord.Height - Convert.ToSingle(Math.Log10(y/y0)*module) - module*k;
				ptRight.Y  = ptLeft.Y;
				if ( j == 10 )
				{	j = 1; 
					y0 *= 10; 
					++ k; 
					g.DrawLine(penSolid, ptLeft, ptRight); 
				}
				else
					g.DrawLine(penDot, ptLeft, ptRight); 
			}

			// =================== Подписи =================================================
			SizeF stringSize = new SizeF();

			// Подписи по оси абсцисс (AB/2)
			ptBott.X = ptOrig.X; 
			ptBott.Y = ptOrig.Y + sizeBord.Height + 2;
			ptTop.X = ptOrig.X;
			ptTop.Y = ptOrig.Y;
			
			double f_ab2 = Math.Pow(10,Math.Floor( Math.Log10(Convert.ToDouble(AB2Min))));
			string s_ab2 = f_ab2.ToString();
			stringSize = g.MeasureString(s_ab2, font); // Измерим строку
			ptTop.Y -= stringSize.Height; // Подправим положение верхних подписей
			
			StringFormat fmt = new StringFormat();
			fmt.Alignment = StringAlignment.Center;

			for ( int i = 0 ; i <= AB2Decads; i ++ )
			{
				g.DrawString(s_ab2, font, brush, ptBott, fmt); // снизу
				f_ab2 *= 10;
				s_ab2 = f_ab2.ToString();
				ptBott.X += module;
				ptTop.X  += module;
			}

			// Подписи по оси ординат (Rok)
			ptLeft.X  = ptOrig.X;
			ptLeft.Y  = ptOrig.Y + sizeBord.Height;
			ptRight.X = ptOrig.X + sizeBord.Width;
			ptRight.Y = ptOrig.Y + sizeBord.Height;
			
			double f_rok = Math.Pow(10,Math.Floor( Math.Log10(Convert.ToDouble(RokMin))));
			string s_rok = f_rok.ToString();
			stringSize = g.MeasureString(Math.Ceiling(RokMax*10).ToString(), font); // Измерим строку
			ptLeft.X -= stringSize.Width + 2;		// Подправим положение
			ptLeft.Y -= stringSize.Height/2;		// Подправим положение

			for ( int i = 0 ; i <= RokDecads; i ++ )
			{
				g.DrawString(s_rok, font, brush, ptLeft);  // слева
				f_rok *= 10;
				s_rok = f_rok.ToString();
				ptLeft.Y -= module;
				ptRight.Y  -= module;
			}

			// Наименования Осей

			// Заголовок бланка
			Font  fontHdr = new Font("Microsoft Sans Serif",8);
			ptTop.X = marginHoriz + sizeBord.Width/2;
			ptTop.Y = 2;
			fmt.Alignment = StringAlignment.Center;
			string hdrStr = string.Format("Участок: {0}\nПрофиль: {1}\nКривая: {2}",
										  areaName, profName, curveName);
			g.DrawString(hdrStr, fontHdr, brush, ptTop, fmt);
			fontHdr.Dispose();
			
			// Описание осей
			Font  fontAxis = new Font("Microsoft Sans Serif",8);

			ptTop.X = 0;

			ptTop.Y = marginVert + sizeBord.Height/2;
			fmt.Alignment = StringAlignment.Center;
//			fmt.FormatFlags = StringFormatFlags.DirectionVertical;
			// Под углом 90 градусов
			g.TranslateTransform( ptTop.X,ptTop.Y );
			g.RotateTransform(-90.0F);
//			g.DrawString("Удельное эл. сопротивление, Омм", fontAxis, brush, ptTop, fmt);
			g.DrawString("Удельное эл. сопротивление, Омм", fontAxis, brush, 0, 0, fmt);
			g.ResetTransform();

			ptTop.X = marginHoriz + sizeBord.Width/2;
			ptTop.Y = marginVert + sizeBord.Height + fontAxis.GetHeight()*3;
			fmt.Dispose();
			fmt = new StringFormat();
			fmt.Alignment = StringAlignment.Center;
			g.DrawString("AB/2, метры", fontAxis, brush, ptTop, fmt);

			// Уберем лишнее
			penDot.Dispose();
			penSolid.Dispose();
			brush.Dispose();
			font.Dispose();
		}

		/// <summary>
		/// Рисует кривые на бланке
		/// </summary>
		private void drawVesCurve(Graphics g)
		{
			//Размеры рамки 
			SizeF  sizeBord = new SizeF(module*AB2Decads,module*RokDecads);
			// Левый нижний угол рамки
			PointF ptOrigLB = new PointF(marginHoriz, marginVert + sizeBord.Height );
			// Значения Rok и AB/2 в левом нижнем углу рамки
			float ab2_0 = Convert.ToSingle( Math.Pow(10,Math.Floor( Math.Log10(Convert.ToDouble(AB2Min)))) );
			float rok_0 = Convert.ToSingle( Math.Pow(10,Math.Floor( Math.Log10(Convert.ToDouble(RokMin)))) );
			
			// Полевая кривая
			Pen   pen = new Pen(Color.Blue, 3F); //  перо
			float _ab2 = Convert.ToSingle( Math.Log10((AB2[0]/ab2_0))*module );
			float _rok = Convert.ToSingle( Math.Log10((fRok[0]/rok_0))*module );
			PointF pt1 = new PointF(ptOrigLB.X + _ab2, ptOrigLB.Y - _rok);
			PointF pt2 = new PointF();
			for ( int i = 1; i < nSamples; i ++ )
			{
				_ab2 = Convert.ToSingle( Math.Log10((AB2[i]/ab2_0))*module );
				_rok = Convert.ToSingle( Math.Log10((fRok[i]/rok_0))*module );
				pt2.X = ptOrigLB.X + _ab2;
				pt2.Y = ptOrigLB.Y - _rok;
				g.DrawLine(pen,pt1,pt2);
				pt1.X = pt2.X;
				pt1.Y = pt2.Y;
			}
			pen.Dispose();

			if (model.nLayers <= 1) return;

			// Вычисленная кривая
			Pen   pen1 = new Pen(Color.Red, 3F); // перо
			pen1.DashStyle = DashStyle.Dot;
			_ab2 = Convert.ToSingle( Math.Log10((AB2[0]/ab2_0))*module );
			_rok = Convert.ToSingle( Math.Log10((tRok[0]/rok_0))*module );
			pt1.X = ptOrigLB.X + _ab2;
			pt1.Y = ptOrigLB.Y - _rok;
			for ( int i = 1; i < nSamples; i ++ )
			{
				_ab2 = Convert.ToSingle( Math.Log10((AB2[i]/ab2_0))*module );
				_rok = Convert.ToSingle( Math.Log10((tRok[i]/rok_0))*module );
				pt2.X = ptOrigLB.X + _ab2;
				pt2.Y = ptOrigLB.Y - _rok;
				g.DrawLine(pen1,pt1,pt2);
				pt1.X = pt2.X;
				pt1.Y = pt2.Y;
			}
			pen1.Dispose();
		}

		/// <summary>
		/// Экспорт кривой в выходной XML файл с помощью класса XmlWriter<br />
		/// Кривая уже должна быть загружена.<br /><br />
		/// <example>
		/// <code>
		///	XmlTextWriter xmlWriter = new XmlTextWriter(outputXmlFile, System.Text.Encoding.GetEncoding(1251));<br />
		/// xmlWriter.Formatting = Formatting.Indented;<br />
		/// xmlWriter.WriteStartDocument();<br />
		/// ...<br />
		/// ...<br />
		///	currCurve.loadFromFile(vesFile);<br />
		///	currCurve.ExportToXml(xmlWriter,"curve.gif");<br />
		/// </code>
		/// </example>
		/// </summary>
		/// <param name="xmlWriter">Экземпляр класса XmlWriter</param>
		/// <param name="gifName">Имя файла GIF с картинкой</param>
		public void ExportToXml(XmlWriter xmlWriter, string gifName)
		{
			CultureInfo en	= new CultureInfo("en-US"); // Весь вывод будет в американском формате

			xmlWriter.WriteStartElement("curve");
			xmlWriter.WriteAttributeString("name", curveName);
			xmlWriter.WriteAttributeString("date", "" );
			xmlWriter.WriteAttributeString("x", X.ToString(en) );
			xmlWriter.WriteAttributeString("y", Y.ToString(en) );
			xmlWriter.WriteAttributeString("z", Z.ToString(en) );
			xmlWriter.WriteAttributeString("rms", RMS.ToString(en) );
			xmlWriter.WriteAttributeString("layers", model.nLayers.ToString() );
				
				// samples
				xmlWriter.WriteStartElement("samples");
				for ( int i = 0; i < nSamples; i ++ )
				{
					xmlWriter.WriteStartElement("sample");
					xmlWriter.WriteAttributeString("ab2", AB2[i].ToString(en));
					xmlWriter.WriteAttributeString("ro", fRok[i].ToString(en));
					if (model.nLayers > 1)
						xmlWriter.WriteAttributeString("rt", tRok[i].ToString(en));
					xmlWriter.WriteEndElement(); // sample
				}
				xmlWriter.WriteEndElement(); // samples
				
				//layers
				xmlWriter.WriteStartElement("layers");
				for ( int i = 0; i < model.nLayers; i ++ )
				{
					xmlWriter.WriteStartElement("layer");
					xmlWriter.WriteAttributeString("id", i.ToString());

					if (i != (model.nLayers-1))
						xmlWriter.WriteAttributeString("h", model.H[i].ToString(en));
					else
						xmlWriter.WriteAttributeString("h", "INFINITY");

					xmlWriter.WriteAttributeString("r", model.Ro[i].ToString(en));
					xmlWriter.WriteEndElement(); // layer
				}
				xmlWriter.WriteEndElement(); // layers

			xmlWriter.WriteStartElement("image");
			xmlWriter.WriteString(gifName);
			xmlWriter.WriteEndElement();
			xmlWriter.WriteStartElement("curvedescr");
			xmlWriter.WriteEndElement();
			xmlWriter.WriteStartElement("operator");
			xmlWriter.WriteEndElement();
			xmlWriter.WriteStartElement("calculator");
			xmlWriter.WriteEndElement();
			xmlWriter.WriteStartElement("weather");
			xmlWriter.WriteEndElement();
			xmlWriter.WriteStartElement("device");
			xmlWriter.WriteString("АНЧ-3");
			xmlWriter.WriteEndElement();
			xmlWriter.WriteEndElement(); // curve
		}


		/// <summary>
		/// Загрузить кривую из потока.<br />
		/// Поток должен быть уже открыт и заголовок профиля уже должен
		/// быть считан из этого же потока методом <b>Load()</b> класса <b>VesFileHeaderClass:</b><br /><br />
		/// <example>
		/// <code>
		/// // Откроем поток<br />
		/// FileStream vesFile = new FileStream("file.ves", FileMode.Open, FileAccess.Read);<br />
		/// fileType = GetFileType(inputFile);		// Тип ВЭЗ-файла<br />
		/// <br />
		/// // Загрузить заголовок<br />
		/// hdrVES.Load(vesFile, fileType);<br />
		/// </code>
		/// </example>
		/// </summary>
		/// <param name="stream"></param>
		public void Load(FileStream stream)
		{
			loadFromBinFile(stream);
		}

		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="reader"></param>
		public void Load(StreamReader reader)
		{
			loadFromTextFile(reader);
		}

		
		/// <summary>
		/// Загрузить кривую из текстового ВЭЗ файла (формат VEZ)<br />
		/// Метод вызывается из метода <b>Load()</b>
		/// </summary>
		/// <param name="sr">Входной текстовый поток</param>
		private void loadFromTextFile(StreamReader sr)
		{
			CultureInfo	en = new CultureInfo("en-US");	// Для правильного преобразования string в float
														// У нас разделитель - точка, поэтому используем
														// культуру en-US
			
			// Ищем строку, содержащую начало кривой (#curve)
			while (sr.ReadLine() != "#curve");

			// Имя кривой
			curveName = TextVezFileParserClass.ParseParam(sr);
			// Координаты
			string scoords = TextVezFileParserClass.ParseParam(sr);
			scoords = scoords.Trim();
			string [] sa = new string [3];
			sa = scoords.Split(" ".ToCharArray(),3);
			X = Convert.ToSingle(sa[0], en);
			Y = Convert.ToSingle(sa[1], en);
			Z = Convert.ToSingle(sa[2], en);
			
			// Получим Отсчеты
			string	line;
			ushort	i = 0;
			AB2Min = 1000000;
			AB2Max = -1;
			RokMin = 1000000;
			RokMax = -1;
			while ((line=sr.ReadLine()) != "#endcurve")  
			{
				line = line.Trim();
				if (line == "") continue;
				sa = line.Split(" ".ToCharArray(),2);
				AB2[i]  = Convert.ToSingle(sa[0], en);
				fRok[i] = Convert.ToSingle(sa[1], en);
				if (AB2[i] > AB2Max) AB2Max = AB2[i];
				if (AB2[i] < AB2Min) AB2Min = AB2[i];
				if (fRok[i] > RokMax) RokMax = fRok[i];
				if (fRok[i] < RokMin) RokMin = fRok[i];
				++ i;
			}

			nSamples = i; // Кол-во отсчетов

			OrgAB2 = Convert.ToSingle(Math.Pow(10,Math.Floor( Math.Log10(Convert.ToDouble(AB2Min)))));
			OrgRok = Convert.ToSingle(Math.Pow(10,Math.Floor( Math.Log10(Convert.ToDouble(RokMin)))));
			RokDecads = Convert.ToUInt16(Math.Floor(Math.Log10(RokMax/OrgRok))) + 1;
			AB2Decads = Convert.ToUInt16(Math.Floor(Math.Log10(AB2Max/OrgAB2))) + 1;
		}

	}
}
