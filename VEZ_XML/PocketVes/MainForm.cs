using System;
using System.Drawing;
using System.Collections;
using System.Windows.Forms;
using System.Data;
using System.Xml;
using System.IO;

namespace PocketVes
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class MainForm : System.Windows.Forms.Form
	{
		#region Controls
		private System.Windows.Forms.MainMenu mainMenu;
		private System.Windows.Forms.MenuItem menuItem4;
		private System.Windows.Forms.TabPage tabPage1;
		private System.Windows.Forms.TabPage tabPage2;
		private System.Windows.Forms.TabPage tabPage3;
		private System.Windows.Forms.TreeView treeView;
		private System.Windows.Forms.DataGrid dgLayers;
		private System.Windows.Forms.DataGrid dgSamples;
		private System.Windows.Forms.MenuItem menuFile;
		private System.Windows.Forms.MenuItem menuFileOpen;
		private System.Windows.Forms.MenuItem menuFileSave;
		private System.Windows.Forms.MenuItem menuFileExit;
		private System.Windows.Forms.MenuItem menuFileNew;
		private System.Windows.Forms.MenuItem menuService;
		private System.Windows.Forms.MenuItem menuServiceSettings;
		private System.Windows.Forms.MenuItem menuGraph;
		private System.Windows.Forms.TabControl tabControlMain;
		private System.Windows.Forms.SaveFileDialog saveFileDialog;
		private System.Windows.Forms.Label lblFileName;
		private System.Windows.Forms.TextBox txtAB2;
		private System.Windows.Forms.TextBox txtRok;
		private System.Windows.Forms.Button btnSave;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.OpenFileDialog openFileDialog;
		#endregion

		#region Constructor/Dispose
		public MainForm()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			base.Dispose( disposing );
		}
		#endregion

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.mainMenu = new System.Windows.Forms.MainMenu();
			this.menuFile = new System.Windows.Forms.MenuItem();
			this.menuFileNew = new System.Windows.Forms.MenuItem();
			this.menuFileOpen = new System.Windows.Forms.MenuItem();
			this.menuFileSave = new System.Windows.Forms.MenuItem();
			this.menuItem4 = new System.Windows.Forms.MenuItem();
			this.menuFileExit = new System.Windows.Forms.MenuItem();
			this.menuService = new System.Windows.Forms.MenuItem();
			this.menuServiceSettings = new System.Windows.Forms.MenuItem();
			this.menuGraph = new System.Windows.Forms.MenuItem();
			this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
			this.tabControlMain = new System.Windows.Forms.TabControl();
			this.tabPage1 = new System.Windows.Forms.TabPage();
			this.lblFileName = new System.Windows.Forms.Label();
			this.treeView = new System.Windows.Forms.TreeView();
			this.tabPage2 = new System.Windows.Forms.TabPage();
			this.label2 = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.btnSave = new System.Windows.Forms.Button();
			this.txtRok = new System.Windows.Forms.TextBox();
			this.txtAB2 = new System.Windows.Forms.TextBox();
			this.dgSamples = new System.Windows.Forms.DataGrid();
			this.tabPage3 = new System.Windows.Forms.TabPage();
			this.dgLayers = new System.Windows.Forms.DataGrid();
			this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
			// 
			// mainMenu
			// 
			this.mainMenu.MenuItems.Add(this.menuFile);
			this.mainMenu.MenuItems.Add(this.menuService);
			this.mainMenu.MenuItems.Add(this.menuGraph);
			// 
			// menuFile
			// 
			this.menuFile.MenuItems.Add(this.menuFileNew);
			this.menuFile.MenuItems.Add(this.menuFileOpen);
			this.menuFile.MenuItems.Add(this.menuFileSave);
			this.menuFile.MenuItems.Add(this.menuItem4);
			this.menuFile.MenuItems.Add(this.menuFileExit);
			this.menuFile.Text = "Файл";
			// 
			// menuFileNew
			// 
			this.menuFileNew.Text = "Создать...";
			this.menuFileNew.Click += new System.EventHandler(this.menuFileNew_Click);
			// 
			// menuFileOpen
			// 
			this.menuFileOpen.Text = "Открыть...";
			this.menuFileOpen.Click += new System.EventHandler(this.menuFileOpen_Click);
			// 
			// menuFileSave
			// 
			this.menuFileSave.Text = "Сохранить...";
			this.menuFileSave.Click += new System.EventHandler(this.menuFileSave_Click);
			// 
			// menuItem4
			// 
			this.menuItem4.Text = "-";
			// 
			// menuFileExit
			// 
			this.menuFileExit.Text = "Выход";
			this.menuFileExit.Click += new System.EventHandler(this.menuFileExit_Click);
			// 
			// menuService
			// 
			this.menuService.MenuItems.Add(this.menuServiceSettings);
			this.menuService.Text = "Сервис";
			// 
			// menuServiceSettings
			// 
			this.menuServiceSettings.Text = "Параметры...";
			this.menuServiceSettings.Click += new System.EventHandler(this.menuServiceSettings_Click);
			// 
			// menuGraph
			// 
			this.menuGraph.Text = "График";
			this.menuGraph.Click += new System.EventHandler(this.menuGraph_Click);
			// 
			// openFileDialog
			// 
			this.openFileDialog.Filter = "(*.xml)|*.xml|(*.*)|*.*";
			this.openFileDialog.InitialDirectory = "Program Files";
			// 
			// tabControlMain
			// 
			this.tabControlMain.Controls.Add(this.tabPage1);
			this.tabControlMain.Controls.Add(this.tabPage2);
			this.tabControlMain.Controls.Add(this.tabPage3);
			this.tabControlMain.SelectedIndex = 0;
			this.tabControlMain.Size = new System.Drawing.Size(240, 272);
			// 
			// tabPage1
			// 
			this.tabPage1.Controls.Add(this.lblFileName);
			this.tabPage1.Controls.Add(this.treeView);
			this.tabPage1.Location = new System.Drawing.Point(4, 4);
			this.tabPage1.Size = new System.Drawing.Size(232, 246);
			this.tabPage1.Text = "Выбор";
			// 
			// lblFileName
			// 
			this.lblFileName.Location = new System.Drawing.Point(8, 8);
			this.lblFileName.Size = new System.Drawing.Size(216, 20);
			this.lblFileName.Text = "Файл не загружен";
			// 
			// treeView
			// 
			this.treeView.ImageIndex = -1;
			this.treeView.Location = new System.Drawing.Point(8, 32);
			this.treeView.SelectedImageIndex = -1;
			this.treeView.Size = new System.Drawing.Size(216, 200);
			this.treeView.GotFocus += new System.EventHandler(this.treeView_GotFocus);
			this.treeView.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeView_AfterSelect);
			this.treeView.LostFocus += new System.EventHandler(this.treeView_LostFocus);
			// 
			// tabPage2
			// 
			this.tabPage2.Controls.Add(this.label2);
			this.tabPage2.Controls.Add(this.label1);
			this.tabPage2.Controls.Add(this.btnSave);
			this.tabPage2.Controls.Add(this.txtRok);
			this.tabPage2.Controls.Add(this.txtAB2);
			this.tabPage2.Controls.Add(this.dgSamples);
			this.tabPage2.Location = new System.Drawing.Point(4, 4);
			this.tabPage2.Size = new System.Drawing.Size(232, 246);
			this.tabPage2.Text = "Отсчеты";
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(76, 2);
			this.label2.Size = new System.Drawing.Size(48, 16);
			this.label2.Text = "Rok";
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(11, 2);
			this.label1.Size = new System.Drawing.Size(48, 16);
			this.label1.Text = "AB/2";
			// 
			// btnSave
			// 
			this.btnSave.Location = new System.Drawing.Point(145, 20);
			this.btnSave.Size = new System.Drawing.Size(79, 20);
			this.btnSave.Text = "Записать";
			this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
			// 
			// txtRok
			// 
			this.txtRok.Location = new System.Drawing.Point(76, 20);
			this.txtRok.Size = new System.Drawing.Size(65, 20);
			this.txtRok.Text = "";
			// 
			// txtAB2
			// 
			this.txtAB2.Location = new System.Drawing.Point(8, 20);
			this.txtAB2.Size = new System.Drawing.Size(65, 20);
			this.txtAB2.Text = "";
			// 
			// dgSamples
			// 
			this.dgSamples.Location = new System.Drawing.Point(8, 45);
			this.dgSamples.Size = new System.Drawing.Size(216, 195);
			this.dgSamples.Text = "dgSamples";
			this.dgSamples.Click += new System.EventHandler(this.dgSamples_Click);
			// 
			// tabPage3
			// 
			this.tabPage3.Controls.Add(this.dgLayers);
			this.tabPage3.Location = new System.Drawing.Point(4, 4);
			this.tabPage3.Size = new System.Drawing.Size(232, 246);
			this.tabPage3.Text = "Слои";
			// 
			// dgLayers
			// 
			this.dgLayers.Location = new System.Drawing.Point(8, 8);
			this.dgLayers.Size = new System.Drawing.Size(216, 232);
			this.dgLayers.Text = "dataGrid2";
			// 
			// saveFileDialog
			// 
			this.saveFileDialog.FileName = "doc1";
			this.saveFileDialog.Filter = "(*.xml)|*.xml";
			// 
			// MainForm
			// 
			this.Controls.Add(this.tabControlMain);
			this.Menu = this.mainMenu;
			this.Text = "PocketVES";

		}
		#endregion

		#region Methods

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		static void Main() 
		{
			Application.Run(new MainForm());
		}

		/// <summary>
		/// Создать новый файл данных
		/// </summary>
		private void cmdFileNew()
		{
			// Создадим экземпляр  класса значений по умолчанию
			Settings settings = new Settings();
			// Создать форму
			NewFileForm frm = new NewFileForm();
			// Привязать элементы формы к свойствам класса значений по умолчанию
			frm.Bindings(settings);

			if ( frm.ShowDialog() == DialogResult.OK)
			{
				// Сначала освободим ресурсы
				this.closeFile();
				
				VesXml vesXml = new VesXml(settings);
				_currentXmlDoc = vesXml.XmlDoc;
				_currentVesXml = vesXml;
				this.fillTreeView(treeView, _currentXmlDoc);
				lblFileName.Text = "Новый файл";
			}
			
			treeView.Focus();
		}

		/// <summary>
		/// Открыть файл данных
		/// </summary>
		private void cmdFileOpen()
		{
			if ( openFileDialog.ShowDialog() == DialogResult.OK )
			{
				// Освободим ресурсы
				this.closeFile();

				lblFileName.Text = String.Format("Файл: {0}",Path.GetFileName(openFileDialog.FileName));

				string fileName = openFileDialog.FileName;
				
				VesXml vesXml = new VesXml(fileName);
				_currentVesXml = vesXml;
				_currentXmlDoc = vesXml.XmlDoc;

				this.fillTreeView(treeView, _currentXmlDoc );
				treeView.SelectedNode = treeView.Nodes[0];
			}
		}

		/// <summary>
		/// Сохранить файл данных
		/// </summary>
		private void cmdFileSave()
		{
			if (_currentXmlDoc != null)
			{
				saveFileDialog.InitialDirectory = "\\My Documents\\Personal";
				if ( saveFileDialog.ShowDialog() == DialogResult.OK)
				{
					_currentXmlDoc.Save(saveFileDialog.FileName);
					lblFileName.Text = "Файл: " + Path.GetFileName(saveFileDialog.FileName);
				}
			}
		}

		/// <summary>
		/// Освободить ресурсы
		/// </summary>
		private void closeFile()
		{
			// Очистим treeView и прочие контролы
			treeView.Nodes.Clear();
			dgSamples.DataSource = null;
			dgLayers.DataSource = null;

			// Сбросим текущую кривую
			if (_currentCurve != null)
				_currentCurve = null;
			// Сбросим текущий XML документ
			if (_currentXmlDoc != null) 
			{
				_currentXmlDoc.RemoveAll();
				_currentXmlDoc = null;
			}
		}

		/// <summary>
		/// Загрузить XML документ в TreeView
		/// </summary>
		/// <param name="treeView">Целевой TreeView</param>
		/// <param name="xmlDoc">Загружаемый Xml документ</param>
		private void fillTreeView(TreeView treeView, XmlDocument xmlDoc)
		{
			treeView.Nodes.Clear();		// Очистим treeView
			treeView.BeginUpdate();		// Чтоб не мерцало

			string areaName;
			string areaDescr;
			
			XmlNode	areaNode;
			//			areaNode = xmlDoc.SelectSingleNode("/area");
			areaNode = xmlDoc.GetElementsByTagName("area")[0];

			areaName = areaNode.Attributes.GetNamedItem("name").Value;
			TreeNode areaTreeNode = treeView.Nodes.Add(areaName);
			areaTreeNode.Tag = areaNode;		// Прицепим к узлу объект
			areaTreeNode.ImageIndex = 0;
			areaTreeNode.SelectedImageIndex = 0;

			//			areaNode = xmlDoc.SelectSingleNode("/area/areadescr");
			areaNode = xmlDoc.GetElementsByTagName("areadescr")[0];
			areaDescr = areaNode.InnerText;
			
			// Загрузим профили
			_fillProfilesNodes(xmlDoc, treeView, areaTreeNode);

			treeView.EndUpdate();
		}

		/// <summary>
		/// Вспомогательная функция, вызывается из fillTreeView()
		/// Загружает узлы профилей в TreeView из XML документа
		/// </summary>
		/// <param name="xmlDoc">Исходный XML документ</param>
		/// <param name="treeView">Целевой TreeView</param>
		/// <param name="areaTreeNode">Корневой узел в TreeView, к которому добавляются узлы профилей</param>
		private void _fillProfilesNodes(XmlDocument xmlDoc, System.Windows.Forms.TreeView treeView, System.Windows.Forms.TreeNode areaTreeNode )
		{
			// Цикл по профилям
			string profName;
//			string profDescr;
//			XmlNode currNode;
			XmlNodeList profNodeList;

			//			profNodeList = xmlDoc.SelectNodes("/area/profil");
			profNodeList = xmlDoc.GetElementsByTagName("profil");

			foreach (XmlNode profNode in profNodeList)
			{
				string	profType;		// Тип профиля
				profName = profNode.Attributes.GetNamedItem("name").Value;
				profType = profNode.Attributes.GetNamedItem("type").Value;
				if (profType != "profil")
					profName = "Отдельные кривые " + profName;
				TreeNode profTreeNode = areaTreeNode.Nodes.Add(profName);
				profTreeNode.Tag = profNode;

				if (profType == "profil")	
				{
					profTreeNode.ImageIndex = 1;
					profTreeNode.SelectedImageIndex = 1;
				}
				else
				{
					profTreeNode.ImageIndex = 2;
					profTreeNode.SelectedImageIndex = 2;
				}

				//				currNode  = profNode.SelectSingleNode("profildescr");
				//				if (currNode != null)
				//					profDescr = currNode.InnerText;
				//				else
				//					profDescr = "*";

//				loadCurves(profNode, treeView, profTreeNode);
				_fillCurvesNodes(profNode, treeView, profTreeNode );

			} // По профилям
		}

		/// <summary>
		/// Вспомогательная функция, вызывается из _fillProfilesNodes
		/// Загружает узлы кривых ВЭЗ в TreeView из XML документа
		/// </summary>
		/// <param name="profNode">Родительский узел Xml</param>
		/// <param name="treeView">Целевой TreeView</param>
		/// <param name="profTreeNode">Родительский узел в TreeView</param>
		private void _fillCurvesNodes(XmlNode profNode, System.Windows.Forms.TreeView treeView, System.Windows.Forms.TreeNode profTreeNode)
		{
			// По кривым
//			XmlNodeList curveNodeList;
			XmlNodeList cNodeList;

			//			curveNodeList = profNode.SelectNodes("curves/curve");
			cNodeList = profNode.ChildNodes;

			foreach (XmlNode cNode in cNodeList)
			{
				if (cNode.LocalName == "curves")
				{
					foreach (XmlNode curveNode in cNode.ChildNodes)
					{
						if (curveNode.LocalName == "curve")
						{
							string curveName = curveNode.Attributes.GetNamedItem("name").Value;
							TreeNode curveTreeNode = profTreeNode.Nodes.Add(curveName);
							curveTreeNode.Tag = curveNode;
							curveTreeNode.ImageIndex = 3;
							curveTreeNode.SelectedImageIndex = 3;

							int nlayers = 0;
							if (curveNode.Attributes.GetNamedItem("layers") != null)
								nlayers = Convert.ToInt16(curveNode.Attributes.GetNamedItem("layers").Value);
				
							if (nlayers <= 1)
							{
								curveTreeNode.ImageIndex = 4;
								curveTreeNode.SelectedImageIndex = 4;
							}
						}
					}
				}
			} // По кривым
		}

		/// <summary>
		/// Сделать узел в TreeView, соответствующий заданному узлу XML, текущим
		/// </summary>
		/// <param name="profNode">Узел Xml</param>
		/// <param name="treeView">Целевой TreeView</param>
		/// <param name="profTreeNode">Соотв. узел в TreeView</param>
		private void selectTreeNode(XmlNode xmlNode, System.Windows.Forms.TreeView treeView)
		{
			if (xmlNode == null) 
			{ 
				treeView.SelectedNode = treeView.Nodes[0];
				return;
			}

			treeView.ExpandAll();

			TreeNode currTreeNode = treeView.Nodes[0];
			while (currTreeNode != null)
			{
				if ((XmlNode) currTreeNode.Tag == xmlNode)
				{
					treeView.SelectedNode = currTreeNode;
					break;
				}
				//				currTreeNode = currTreeNode.NextVisibleNode;
				//				currTreeNode = currTreeNode;
			}
		}


		#endregion

		#region Fields
		
		/// <summary>
		/// Текущая кривая ВЭЗ
		/// </summary>
		private VesCurve		_currentCurve;
		/// <summary>
		/// Текущий документ Xml
		/// </summary>
		private	XmlDocument		_currentXmlDoc;
		/// <summary>
		/// 
		/// </summary>
		private VesXml			_currentVesXml;
		private static string	_appName = "PocketVes";
		private static string	_appVersion = "1.0.0.1";
		private TreeNode		_currTreeNode;			// Текущий выделенный узел в treeView

		#endregion

		#region Properties

		public static string AppName
		{
			get
			{
				return _appName;
			}
			set
			{
				_appName = value;
			}
		}
		public static string Version
		{
			get
			{
				return _appVersion;
			}
			set
			{
				_appVersion = value;
			}
		}


		#endregion

		#region Event Handlers

		private void menuFileOpen_Click(object sender, System.EventArgs e)
		{
			this.cmdFileOpen();
		}

		private void treeView_AfterSelect(object sender, System.Windows.Forms.TreeViewEventArgs e)
		{
			XmlNode node = (XmlNode) e.Node.Tag;

			switch (node.LocalName)
			{
				case "curve":
					VesCurve vesCurve = new VesCurve( node, _currentXmlDoc);
					_currentCurve   = vesCurve;

					dgSamples.DataSource = vesCurve.Samples;
					dgLayers.DataSource = vesCurve.Layers;

					break;
				case "area":
					//					VesArea vesArea = new VesArea(node);
					//					propertyGrid1.SelectedObject = vesArea;
					break;
				case "profil":
					//					VesProfil vesProfil = new VesProfil(node);
					//					propertyGrid1.SelectedObject = vesProfil;
					break;
			}

			//			tabPage4.Invalidate();					// Перерисуем
		}

		private void menuGraph_Click(object sender, System.EventArgs e)
		{
			GraphForm frm = new GraphForm(_currentCurve);
			frm.ShowDialog();
			treeView.Focus();
		}

		private void menuServiceSettings_Click(object sender, System.EventArgs e)
		{
			Settings settings = new Settings();
			SettingsForm frm = new SettingsForm();
			frm.Bindings(settings);

			if ( frm.ShowDialog() == DialogResult.OK)
				settings.Save();

			treeView.Focus();
		}
		private void menuFileExit_Click(object sender, System.EventArgs e)
		{
			Application.Exit();
		}

		private void menuFileNew_Click(object sender, System.EventArgs e)
		{
			this.cmdFileNew();
		}

		private void menuFileSave_Click(object sender, System.EventArgs e)
		{
			this.cmdFileSave();
		}

		private void treeView_LostFocus(object sender, System.EventArgs e)
		{
			// Запомним выделенный узел
			_currTreeNode = treeView.SelectedNode;
		}

		private void treeView_GotFocus(object sender, System.EventArgs e)
		{
			// Восстановим выделенный узел
			if (_currTreeNode != null)
			{
				treeView.SelectedNode = _currTreeNode;
			}
		
		}

		private void dgSamples_Click(object sender, System.EventArgs e)
		{
			DataTable dt = (DataTable) dgSamples.DataSource;
			if (dt != null)
			{
				int i = dgSamples.CurrentCell.RowNumber;
				txtAB2.Text = dt.Rows[i]["AB2"].ToString();
				txtRok.Text = dt.Rows[i]["ROK"].ToString();
			}
		}

		private void btnSave_Click(object sender, System.EventArgs e)
		{
			DataTable dt = (DataTable) dgSamples.DataSource;
			if ( (dt != null) && (txtAB2.Text) != "" )
			{
				int i = dgSamples.CurrentCell.RowNumber;
				float rok = Convert.ToSingle(txtRok.Text);
				dt.Rows[i]["ROK"] = rok;
			}
		}


		#endregion

	}
}
