// VesExplore
// Приложение для просмотра, редактирования, интерпретации данных полевых наблюдений 
// методом ВЭЗ
// Коротков В.А. 2002-2003 гг.
//
using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Xml;
using System.IO;
using System.Configuration;

using CommandManagement;


namespace VesExplore
{
	/// <summary>
	/// Главная форма приложения <b>VesExplore</b>
	/// </summary>
	public class MainForm : System.Windows.Forms.Form
	{
		#region Controls

		private System.Windows.Forms.MainMenu mainMenu1;
        private System.Windows.Forms.MenuItem menuItem5;
		private System.Windows.Forms.TreeView treeView;
		private System.Windows.Forms.Splitter splitter1;
		private System.Windows.Forms.OpenFileDialog openFileDialog;
		private System.Windows.Forms.TabControl tabControl1;
		private System.Windows.Forms.TabPage tabPage1;
		private System.Windows.Forms.TabPage tabPage2;
		private System.Windows.Forms.ToolBarButton tbbOpen;
		private System.Windows.Forms.ToolBarButton tbbAbout;
		private System.Windows.Forms.ImageList imageList1;
		private System.Windows.Forms.ToolBarButton tbbNew;
		private System.Windows.Forms.ToolBarButton tbbSave;
		private System.Windows.Forms.ToolBarButton tbbDelete;
		private System.Windows.Forms.PropertyGrid propertyGrid1;
		private System.ComponentModel.IContainer components;
		private System.Windows.Forms.MenuItem menuFileNew;
		private System.Windows.Forms.MenuItem menuNewProfil;
		private System.Windows.Forms.MenuItem menuNewCurve;
		private System.Windows.Forms.MenuItem menuNewArea;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.SaveFileDialog saveFileDialog1;
		private System.Windows.Forms.MenuItem menuFileOpen;
		private System.Windows.Forms.MenuItem menuFileSave;
		private System.Windows.Forms.MenuItem menuFileSaveAs;
		private System.Windows.Forms.MenuItem menuFileExit;
		private System.Windows.Forms.MenuItem menuFileClose;
		private System.Windows.Forms.ImageList imageList2;
		private System.Windows.Forms.ToolBarButton tbbPrint;
		private System.Windows.Forms.MenuItem menuFilePrint;
		private System.Windows.Forms.MenuItem menuItem2;
		private System.Windows.Forms.DataGrid dgSamples;
		private System.Windows.Forms.DataGrid dgLayers;
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
		/// <summary>
		/// Менеджер команд
		/// </summary>
		private CommandManagement.CommandManager cmdMgr;

		private static string _appName = "VesExplore";
		private System.Windows.Forms.MenuItem menuFile;
		private System.Windows.Forms.MenuItem menuHelp;
		private System.Windows.Forms.MenuItem menuService;
		private System.Windows.Forms.MenuItem menuHelpAbout;
		private System.Windows.Forms.ToolBarButton tbbSettings;
		private System.Windows.Forms.ToolBarButton tbbAddProf;
		private System.Windows.Forms.ToolBarButton tbbSep1;
		private System.Windows.Forms.ToolBarButton tbbSep2;
		private System.Windows.Forms.ToolBarButton tbbSep3;
		private System.Windows.Forms.ToolBarButton tbbAddCurve;
		private System.Windows.Forms.ToolBarButton tbbRefresh;
		private System.Drawing.Printing.PrintDocument printDoc;
		private System.Windows.Forms.PrintPreviewDialog printPreviewDialog;
		private System.Windows.Forms.ToolBar tlbMain;
		private System.Windows.Forms.MenuItem menuServiceSettings;
        private System.Windows.Forms.Button button3;
        private StatusBar statusBar;
		private static string _versionName = "1.0";

		#endregion

		#region Properties
		/// <summary>
		/// Имя приложения
		/// </summary>
		public static string AppName
		{
			get
			{
				return _appName;
			}
		}


		/// <summary>
		/// Версия приложения
		/// </summary>
		public static string Version
		{
			get
			{
				return _versionName;
			}
		}


		#endregion

		#region Constructor/Dispose
		public MainForm()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();
			InitializeCommands();

			// 
			// Определим имя приложения и версию
			System.Diagnostics.Process proc = System.Diagnostics.Process.GetCurrentProcess();
			_appName = proc.MainModule.FileName.ToString();
			_appName = Path.GetFileName(_appName);
			_versionName = System.Reflection.AssemblyName.GetAssemblyName(_appName).Version.ToString();

			//			string tst = ConfigurationSettings.AppSettings["Test2"];
			//			ConfigurationSettings.AppSettings.Set("Test1", "Changed!");

			//			AppSettingsReader asr = new AppSettingsReader();
			//			string test = (string) asr.GetValue("Test1", System.Type.GetType("String") );

		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.tlbMain = new System.Windows.Forms.ToolBar();
            this.tbbNew = new System.Windows.Forms.ToolBarButton();
            this.tbbOpen = new System.Windows.Forms.ToolBarButton();
            this.tbbSave = new System.Windows.Forms.ToolBarButton();
            this.tbbPrint = new System.Windows.Forms.ToolBarButton();
            this.tbbSep1 = new System.Windows.Forms.ToolBarButton();
            this.tbbAddProf = new System.Windows.Forms.ToolBarButton();
            this.tbbAddCurve = new System.Windows.Forms.ToolBarButton();
            this.tbbDelete = new System.Windows.Forms.ToolBarButton();
            this.tbbRefresh = new System.Windows.Forms.ToolBarButton();
            this.tbbSep2 = new System.Windows.Forms.ToolBarButton();
            this.tbbSettings = new System.Windows.Forms.ToolBarButton();
            this.tbbSep3 = new System.Windows.Forms.ToolBarButton();
            this.tbbAbout = new System.Windows.Forms.ToolBarButton();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.mainMenu1 = new System.Windows.Forms.MainMenu(this.components);
            this.menuFile = new System.Windows.Forms.MenuItem();
            this.menuFileNew = new System.Windows.Forms.MenuItem();
            this.menuNewArea = new System.Windows.Forms.MenuItem();
            this.menuNewProfil = new System.Windows.Forms.MenuItem();
            this.menuNewCurve = new System.Windows.Forms.MenuItem();
            this.menuFileOpen = new System.Windows.Forms.MenuItem();
            this.menuFileSave = new System.Windows.Forms.MenuItem();
            this.menuFileSaveAs = new System.Windows.Forms.MenuItem();
            this.menuFileClose = new System.Windows.Forms.MenuItem();
            this.menuItem5 = new System.Windows.Forms.MenuItem();
            this.menuFilePrint = new System.Windows.Forms.MenuItem();
            this.menuItem2 = new System.Windows.Forms.MenuItem();
            this.menuFileExit = new System.Windows.Forms.MenuItem();
            this.menuService = new System.Windows.Forms.MenuItem();
            this.menuServiceSettings = new System.Windows.Forms.MenuItem();
            this.menuHelp = new System.Windows.Forms.MenuItem();
            this.menuHelpAbout = new System.Windows.Forms.MenuItem();
            this.treeView = new System.Windows.Forms.TreeView();
            this.imageList2 = new System.Windows.Forms.ImageList(this.components);
            this.splitter1 = new System.Windows.Forms.Splitter();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.button3 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.dgSamples = new System.Windows.Forms.DataGrid();
            this.button1 = new System.Windows.Forms.Button();
            this.dgLayers = new System.Windows.Forms.DataGrid();
            this.propertyGrid1 = new System.Windows.Forms.PropertyGrid();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.printDoc = new System.Drawing.Printing.PrintDocument();
            this.printPreviewDialog = new System.Windows.Forms.PrintPreviewDialog();
            this.statusBar = new System.Windows.Forms.StatusBar();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgSamples)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgLayers)).BeginInit();
            this.SuspendLayout();
            // 
            // tlbMain
            // 
            this.tlbMain.Buttons.AddRange(new System.Windows.Forms.ToolBarButton[] {
            this.tbbNew,
            this.tbbOpen,
            this.tbbSave,
            this.tbbPrint,
            this.tbbSep1,
            this.tbbAddProf,
            this.tbbAddCurve,
            this.tbbDelete,
            this.tbbRefresh,
            this.tbbSep2,
            this.tbbSettings,
            this.tbbSep3,
            this.tbbAbout});
            this.tlbMain.Divider = false;
            this.tlbMain.DropDownArrows = true;
            this.tlbMain.ImageList = this.imageList1;
            this.tlbMain.Location = new System.Drawing.Point(0, 0);
            this.tlbMain.Name = "tlbMain";
            this.tlbMain.ShowToolTips = true;
            this.tlbMain.Size = new System.Drawing.Size(750, 26);
            this.tlbMain.TabIndex = 0;
            // 
            // tbbNew
            // 
            this.tbbNew.ImageIndex = 0;
            this.tbbNew.Name = "tbbNew";
            this.tbbNew.ToolTipText = "Новый файл";
            // 
            // tbbOpen
            // 
            this.tbbOpen.ImageIndex = 1;
            this.tbbOpen.Name = "tbbOpen";
            this.tbbOpen.ToolTipText = "Открыть файл";
            // 
            // tbbSave
            // 
            this.tbbSave.ImageIndex = 5;
            this.tbbSave.Name = "tbbSave";
            this.tbbSave.ToolTipText = "Сохранить файл";
            // 
            // tbbPrint
            // 
            this.tbbPrint.ImageIndex = 6;
            this.tbbPrint.Name = "tbbPrint";
            this.tbbPrint.ToolTipText = "Печать";
            // 
            // tbbSep1
            // 
            this.tbbSep1.Name = "tbbSep1";
            this.tbbSep1.Style = System.Windows.Forms.ToolBarButtonStyle.Separator;
            // 
            // tbbAddProf
            // 
            this.tbbAddProf.ImageIndex = 11;
            this.tbbAddProf.Name = "tbbAddProf";
            this.tbbAddProf.ToolTipText = "Добавить профиль";
            // 
            // tbbAddCurve
            // 
            this.tbbAddCurve.ImageIndex = 13;
            this.tbbAddCurve.Name = "tbbAddCurve";
            this.tbbAddCurve.ToolTipText = "Добавить кривую ВЭЗ";
            // 
            // tbbDelete
            // 
            this.tbbDelete.ImageIndex = 3;
            this.tbbDelete.Name = "tbbDelete";
            this.tbbDelete.ToolTipText = "Удалить";
            // 
            // tbbRefresh
            // 
            this.tbbRefresh.ImageIndex = 10;
            this.tbbRefresh.Name = "tbbRefresh";
            this.tbbRefresh.ToolTipText = "Обновить";
            // 
            // tbbSep2
            // 
            this.tbbSep2.Name = "tbbSep2";
            this.tbbSep2.Style = System.Windows.Forms.ToolBarButtonStyle.Separator;
            // 
            // tbbSettings
            // 
            this.tbbSettings.ImageIndex = 7;
            this.tbbSettings.Name = "tbbSettings";
            this.tbbSettings.ToolTipText = "Настройки";
            // 
            // tbbSep3
            // 
            this.tbbSep3.Name = "tbbSep3";
            this.tbbSep3.Style = System.Windows.Forms.ToolBarButtonStyle.Separator;
            // 
            // tbbAbout
            // 
            this.tbbAbout.ImageIndex = 4;
            this.tbbAbout.Name = "tbbAbout";
            this.tbbAbout.ToolTipText = "О программе";
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "");
            this.imageList1.Images.SetKeyName(1, "");
            this.imageList1.Images.SetKeyName(2, "");
            this.imageList1.Images.SetKeyName(3, "");
            this.imageList1.Images.SetKeyName(4, "");
            this.imageList1.Images.SetKeyName(5, "");
            this.imageList1.Images.SetKeyName(6, "");
            this.imageList1.Images.SetKeyName(7, "");
            this.imageList1.Images.SetKeyName(8, "");
            this.imageList1.Images.SetKeyName(9, "");
            this.imageList1.Images.SetKeyName(10, "");
            this.imageList1.Images.SetKeyName(11, "");
            this.imageList1.Images.SetKeyName(12, "");
            this.imageList1.Images.SetKeyName(13, "");
            // 
            // mainMenu1
            // 
            this.mainMenu1.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.menuFile,
            this.menuService,
            this.menuHelp});
            // 
            // menuFile
            // 
            this.menuFile.Index = 0;
            this.menuFile.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.menuFileNew,
            this.menuFileOpen,
            this.menuFileSave,
            this.menuFileSaveAs,
            this.menuFileClose,
            this.menuItem5,
            this.menuFilePrint,
            this.menuItem2,
            this.menuFileExit});
            this.menuFile.Text = "Файл";
            // 
            // menuFileNew
            // 
            this.menuFileNew.Index = 0;
            this.menuFileNew.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.menuNewArea,
            this.menuNewProfil,
            this.menuNewCurve});
            this.menuFileNew.Text = "Создать";
            // 
            // menuNewArea
            // 
            this.menuNewArea.Index = 0;
            this.menuNewArea.Text = "Area...";
            // 
            // menuNewProfil
            // 
            this.menuNewProfil.Index = 1;
            this.menuNewProfil.Text = "Profil...";
            // 
            // menuNewCurve
            // 
            this.menuNewCurve.Index = 2;
            this.menuNewCurve.Text = "Curve...";
            // 
            // menuFileOpen
            // 
            this.menuFileOpen.Index = 1;
            this.menuFileOpen.Text = "Открыть...";
            // 
            // menuFileSave
            // 
            this.menuFileSave.Index = 2;
            this.menuFileSave.Text = "Сохранить...";
            // 
            // menuFileSaveAs
            // 
            this.menuFileSaveAs.Index = 3;
            this.menuFileSaveAs.Text = "Сохранить как...";
            // 
            // menuFileClose
            // 
            this.menuFileClose.Index = 4;
            this.menuFileClose.Text = "Закрыть...";
            // 
            // menuItem5
            // 
            this.menuItem5.Index = 5;
            this.menuItem5.Text = "-";
            // 
            // menuFilePrint
            // 
            this.menuFilePrint.Index = 6;
            this.menuFilePrint.Text = "Печать...";
            // 
            // menuItem2
            // 
            this.menuItem2.Index = 7;
            this.menuItem2.Text = "-";
            // 
            // menuFileExit
            // 
            this.menuFileExit.Index = 8;
            this.menuFileExit.Text = "Выход";
            // 
            // menuService
            // 
            this.menuService.Index = 1;
            this.menuService.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.menuServiceSettings});
            this.menuService.Text = "Сервис";
            // 
            // menuServiceSettings
            // 
            this.menuServiceSettings.Index = 0;
            this.menuServiceSettings.Text = "Параметры...";
            // 
            // menuHelp
            // 
            this.menuHelp.Index = 2;
            this.menuHelp.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.menuHelpAbout});
            this.menuHelp.Text = "Помощь";
            // 
            // menuHelpAbout
            // 
            this.menuHelpAbout.Index = 0;
            this.menuHelpAbout.Text = "О программе...";
            // 
            // treeView
            // 
            this.treeView.Dock = System.Windows.Forms.DockStyle.Left;
            this.treeView.HideSelection = false;
            this.treeView.ImageIndex = 1;
            this.treeView.ImageList = this.imageList2;
            this.treeView.Location = new System.Drawing.Point(0, 26);
            this.treeView.Name = "treeView";
            this.treeView.SelectedImageIndex = 0;
            this.treeView.Size = new System.Drawing.Size(176, 447);
            this.treeView.TabIndex = 1;
            this.treeView.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeView_AfterSelect);
            // 
            // imageList2
            // 
            this.imageList2.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList2.ImageStream")));
            this.imageList2.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList2.Images.SetKeyName(0, "");
            this.imageList2.Images.SetKeyName(1, "");
            this.imageList2.Images.SetKeyName(2, "");
            this.imageList2.Images.SetKeyName(3, "");
            this.imageList2.Images.SetKeyName(4, "");
            this.imageList2.Images.SetKeyName(5, "");
            this.imageList2.Images.SetKeyName(6, "");
            this.imageList2.Images.SetKeyName(7, "");
            this.imageList2.Images.SetKeyName(8, "");
            this.imageList2.Images.SetKeyName(9, "");
            this.imageList2.Images.SetKeyName(10, "");
            this.imageList2.Images.SetKeyName(11, "");
            this.imageList2.Images.SetKeyName(12, "");
            this.imageList2.Images.SetKeyName(13, "");
            this.imageList2.Images.SetKeyName(14, "");
            this.imageList2.Images.SetKeyName(15, "");
            // 
            // splitter1
            // 
            this.splitter1.Location = new System.Drawing.Point(176, 26);
            this.splitter1.Name = "splitter1";
            this.splitter1.Size = new System.Drawing.Size(3, 447);
            this.splitter1.TabIndex = 3;
            this.splitter1.TabStop = false;
            // 
            // openFileDialog
            // 
            this.openFileDialog.DefaultExt = "xml";
            this.openFileDialog.Filter = "XML files (*.xml)|*.xml|All files (*.*)|*.*";
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(179, 26);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(571, 447);
            this.tabControl1.TabIndex = 2;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.button3);
            this.tabPage1.Controls.Add(this.button2);
            this.tabPage1.Controls.Add(this.dgSamples);
            this.tabPage1.Controls.Add(this.button1);
            this.tabPage1.Controls.Add(this.dgLayers);
            this.tabPage1.Controls.Add(this.propertyGrid1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Size = new System.Drawing.Size(563, 421);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Data";
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(24, 392);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 5;
            this.button3.Text = "InterpForm";
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(392, 392);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(136, 23);
            this.button2.TabIndex = 4;
            this.button2.Text = "UpdateLayersXml";
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // dgSamples
            // 
            this.dgSamples.CaptionText = "Отсчеты";
            this.dgSamples.DataMember = "";
            this.dgSamples.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dgSamples.Location = new System.Drawing.Point(304, 8);
            this.dgSamples.Name = "dgSamples";
            this.dgSamples.Size = new System.Drawing.Size(248, 232);
            this.dgSamples.TabIndex = 1;
            // 
            // button1
            // 
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.button1.Location = new System.Drawing.Point(304, 392);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 3;
            this.button1.Text = "AutoInterpr";
            // 
            // dgLayers
            // 
            this.dgLayers.CaptionText = "Параметры разреза";
            this.dgLayers.DataMember = "";
            this.dgLayers.FlatMode = true;
            this.dgLayers.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dgLayers.Location = new System.Drawing.Point(304, 248);
            this.dgLayers.Name = "dgLayers";
            this.dgLayers.Size = new System.Drawing.Size(248, 136);
            this.dgLayers.TabIndex = 2;
            // 
            // propertyGrid1
            // 
            this.propertyGrid1.LineColor = System.Drawing.SystemColors.ScrollBar;
            this.propertyGrid1.Location = new System.Drawing.Point(8, 8);
            this.propertyGrid1.Name = "propertyGrid1";
            this.propertyGrid1.Size = new System.Drawing.Size(288, 375);
            this.propertyGrid1.TabIndex = 0;
            this.propertyGrid1.ToolbarVisible = false;
            // 
            // tabPage2
            // 
            this.tabPage2.Cursor = System.Windows.Forms.Cursors.Cross;
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Size = new System.Drawing.Size(563, 421);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Graph";
            this.tabPage2.Paint += new System.Windows.Forms.PaintEventHandler(this.tabPage2_Paint);
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.DefaultExt = "xml";
            this.saveFileDialog1.FileName = "doc1";
            this.saveFileDialog1.Filter = "XML files (*.xml)|*.xml";
            // 
            // printDoc
            // 
            this.printDoc.PrintPage += new System.Drawing.Printing.PrintPageEventHandler(this.printDoc_PrintPage);
            // 
            // printPreviewDialog
            // 
            this.printPreviewDialog.AutoScrollMargin = new System.Drawing.Size(0, 0);
            this.printPreviewDialog.AutoScrollMinSize = new System.Drawing.Size(0, 0);
            this.printPreviewDialog.ClientSize = new System.Drawing.Size(400, 300);
            this.printPreviewDialog.Document = this.printDoc;
            this.printPreviewDialog.Enabled = true;
            this.printPreviewDialog.Icon = ((System.Drawing.Icon)(resources.GetObject("printPreviewDialog.Icon")));
            this.printPreviewDialog.Name = "printPreviewDialog";
            this.printPreviewDialog.Visible = false;
            // 
            // statusBar
            // 
            this.statusBar.Location = new System.Drawing.Point(0, 473);
            this.statusBar.Name = "statusBar";
            this.statusBar.Size = new System.Drawing.Size(750, 22);
            this.statusBar.TabIndex = 1;
            this.statusBar.Text = "Файл не загружен";
            // 
            // MainForm
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(750, 495);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.splitter1);
            this.Controls.Add(this.treeView);
            this.Controls.Add(this.statusBar);
            this.Controls.Add(this.tlbMain);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Menu = this.mainMenu1;
            this.Name = "MainForm";
            this.Text = "VesExplore";
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dgSamples)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgLayers)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

		}
		#endregion

		#region Methods
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new MainForm());
		}

		private void InitializeCommands()
		{
			// Инициализация менеджера команд (использует классы CommandManager, см.
			// MSDN Magazine Russian октябрь 2002 стр 52)
			// Создать Command Manager
			cmdMgr = new CommandManager();

			//
			// Добавим объекты-команды
			//
			cmdMgr.Commands.Add( new Command("FileNew", 
								 new Command.ExecuteHandler(onFileNew), null));

			cmdMgr.Commands.Add( new Command("FileOpen", 
								 new Command.ExecuteHandler(onFileOpen), null));

			cmdMgr.Commands.Add( new Command("FileSave", 
								 new Command.ExecuteHandler(onFileSave), null));

			cmdMgr.Commands.Add( new Command("FileSaveAs", 
								 new Command.ExecuteHandler(onFileSave), null));

			cmdMgr.Commands.Add( new Command("FileClose", 
				 				 new Command.ExecuteHandler(onFileClose), null));

			cmdMgr.Commands.Add( new Command("FileExit", 
							     new Command.ExecuteHandler(onFileExit), null));

			cmdMgr.Commands.Add( new Command("FilePrint", 
								 new Command.ExecuteHandler(onFilePrint), 
								 new Command.UpdateHandler(updateFilePrintCommand)));

			cmdMgr.Commands.Add( new Command("AddProfil", 
								 new Command.ExecuteHandler(onAddProfil), 
								 new Command.UpdateHandler(updateAddProfilCommand)));

			cmdMgr.Commands.Add( new Command("AddCurve", 
								 new Command.ExecuteHandler(onAddCurve), 
				                 new Command.UpdateHandler(updateAddCurveCommand)));

			cmdMgr.Commands.Add( new Command("Delete", 
								 new Command.ExecuteHandler(onDelete), null));

			cmdMgr.Commands.Add( new Command("Refresh", 
								 new Command.ExecuteHandler(onRefresh), null));

			cmdMgr.Commands.Add( new Command("ServiceSettings", 
								 new Command.ExecuteHandler(onServiceSettings), null));

			cmdMgr.Commands.Add( new Command("About", 
								 new Command.ExecuteHandler(onAbout), null));

			//
			// Ассоциируем UI контролы с командами
			//
			cmdMgr.Commands["FileNew"].CommandInstances.Add(
				new Object[]{menuNewArea, tlbMain.Buttons[0]});

			cmdMgr.Commands["FileOpen"].CommandInstances.Add(
				new Object[]{menuFileOpen, tlbMain.Buttons[1]});

			cmdMgr.Commands["FileSave"].CommandInstances.Add(
				new Object[]{menuFileSave, tlbMain.Buttons[2]});

			cmdMgr.Commands["FileSaveAs"].CommandInstances.Add(
				new Object[]{menuFileSaveAs});

			cmdMgr.Commands["FileClose"].CommandInstances.Add(
				new Object[]{menuFileClose});

			cmdMgr.Commands["FileExit"].CommandInstances.Add(
				new Object[]{menuFileExit});

			cmdMgr.Commands["FilePrint"].CommandInstances.Add(
				new Object[]{menuFilePrint, tlbMain.Buttons[3]});

			cmdMgr.Commands["AddProfil"].CommandInstances.Add(
				new Object[]{menuNewProfil, tlbMain.Buttons[5]});

			cmdMgr.Commands["AddCurve"].CommandInstances.Add(
				new Object[]{menuNewCurve, tlbMain.Buttons[6]});

			cmdMgr.Commands["Delete"].CommandInstances.Add(
				new Object[]{tlbMain.Buttons[7]});

			cmdMgr.Commands["Refresh"].CommandInstances.Add(
				new Object[]{tlbMain.Buttons[8]});

			cmdMgr.Commands["ServiceSettings"].CommandInstances.Add(
				new Object[]{menuServiceSettings, tlbMain.Buttons[10]});

			cmdMgr.Commands["About"].CommandInstances.Add(
				new Object[]{menuHelpAbout, tlbMain.Buttons[12]});

			//
			// Начальные установки команд
			//
			cmdMgr.Commands["FileSave"].Enabled = false;
			cmdMgr.Commands["FileSaveAs"].Enabled = false;
			cmdMgr.Commands["FileClose"].Enabled = false;
			cmdMgr.Commands["AddProfil"].Enabled = false;
			cmdMgr.Commands["AddCurve"].Enabled = false;
			cmdMgr.Commands["FilePrint"].Enabled = false;
			cmdMgr.Commands["Delete"].Enabled = false;
			cmdMgr.Commands["Refresh"].Enabled = false;
		}

		/// <summary>
		/// Обработчик команды FileNew
		/// </summary>
		/// <param name="cmd">Команда</param>
		private void onFileNew(Command cmd)
		{
			// Сначала освободим ресурсы
			closeFile();
			
			// Создадим экземпляр вспомогательного класса значений по умолчанию
			NewFileSettings settings = new NewFileSettings();
			// Создать форму
			NewFileForm newFileForm = new NewFileForm();
			// Привязать элементы формы к свойствам класса значений по умолчанию
			newFileForm.Bindings(settings);

			// Показать диалог
			if ( newFileForm.ShowDialog() == DialogResult.Cancel) return;


			VesXml vesXml = new VesXml(settings);
			_currentXmlDoc = vesXml.XmlDoc;
			_currentVesXml = vesXml;
			//			vesXml.LoadTree(treeView);
			this.fillTreeView(treeView, _currentXmlDoc);

			statusBar.Text = "Новый файл";
			cmdMgr.Commands["FileSave"].Enabled = true;
			cmdMgr.Commands["FileSaveAs"].Enabled = true;
			cmdMgr.Commands["Delete"].Enabled = true;
			cmdMgr.Commands["Refresh"].Enabled = true;
			cmdMgr.Commands["FileClose"].Enabled = true;
		}

		/// <summary>
		/// Обработчик команды FileOpen
		/// </summary>
		/// <param name="cmd">Команда</param>
		private void onFileOpen(Command cmd)
		{
			// Вызвать диалог
			if ( openFileDialog.ShowDialog() != DialogResult.OK) return;

			// Сначала освободим ресурсы
			closeFile();

			string fileName = openFileDialog.FileName;
			VesXml vesXml = new VesXml(fileName);
			_currentVesXml = vesXml;
			_currentXmlDoc = vesXml.XmlDoc;

			this.fillTreeView(treeView, _currentXmlDoc );
			treeView.SelectedNode = treeView.Nodes[0];
			
			statusBar.Text = fileName;
			cmdMgr.Commands["FileSave"].Enabled = true;
			cmdMgr.Commands["FileSaveAs"].Enabled = true;
			cmdMgr.Commands["Delete"].Enabled = true;
			cmdMgr.Commands["Refresh"].Enabled = true;
			cmdMgr.Commands["FileClose"].Enabled = true;
		}

		/// <summary>
		/// Обработчик команды FileClose
		/// </summary>
		/// <param name="cmd">Команда</param>
		private void onFileClose(Command cmd)
		{
			this.closeFile();
			cmdMgr.Commands["FileSave"].Enabled = false;
			cmdMgr.Commands["FileSaveAs"].Enabled = false;
			cmdMgr.Commands["FileClose"].Enabled = false;
			cmdMgr.Commands["AddProfil"].Enabled = false;
			cmdMgr.Commands["AddCurve"].Enabled = false;
			cmdMgr.Commands["FilePrint"].Enabled = false;
			cmdMgr.Commands["Delete"].Enabled = false;
			cmdMgr.Commands["Refresh"].Enabled = false;

		}
		
		/// <summary>
		/// Обработчик команды FileExit
		/// </summary>
		/// <param name="cmd">Команда</param>
		private void onFileExit(Command cmd)
		{
			Application.Exit();
		}

		/// <summary>
		/// Обработчик команды FileSave
		/// </summary>
		/// <param name="cmd">Команда</param>
		private void onFileSave(Command cmd)
		{
			if (saveFileDialog1.ShowDialog() == DialogResult.OK)
			{
				_currentXmlDoc.Save(saveFileDialog1.FileName);
				statusBar.Text = saveFileDialog1.FileName;
			}

		}
		
		/// <summary>
		/// Обработчик команды FilePrint
		/// </summary>
		/// <param name="cmd">Команда</param>
		private void onFilePrint(Command cmd)
		{
			if (_currentCurve != null)
			{
				printPreviewDialog.ShowDialog();
			}
		}

		/// <summary>
		/// Обработчик события Update в период простоя приложения для
		/// команды FilePrint
		/// </summary>
		/// <param name="cmd">Команда</param>
		private void updateFilePrintCommand(Command cmd)
		{
			if (treeView.SelectedNode != null)
			{
				XmlNode node = (XmlNode) treeView.SelectedNode.Tag;
				cmd.Enabled = (node.LocalName == "curve");
			}
			else
				cmd.Enabled = false;
		}

		/// <summary>
		/// Обработчик команды AddProfil
		/// </summary>
		/// <param name="cmd">Команда</param>
		private void onAddProfil(Command cmd)
		{
			// Создадим экземпляр вспомогательного класса значений по умолчанию
			AddProfilSettings settings = new AddProfilSettings();
			// Создать форму
			AddProfilForm apForm = new AddProfilForm();

			// Привязать элементы формы к свойствам класса значений по умолчанию
			apForm.Bindings(settings);

			// Показать диалог
			if ( apForm.ShowDialog() == DialogResult.Cancel) return;
			
			// Добавить профиль
			XmlNode addedXmlNode = _currentVesXml.AddProfil(settings);

			// Заполним TreeView
			this.fillTreeView(treeView, _currentXmlDoc);
			// Выделим добавленное
			this.selectTreeNode(addedXmlNode, treeView);

		}
		/// <summary>
		/// Обработчик события Update в период простоя приложения для
		/// команды AddProfil
		/// </summary>
		/// <param name="cmd">Команда</param>
		private void updateAddProfilCommand(Command cmd)
		{
			if (treeView.SelectedNode != null)
			{
				cmd.Enabled = true;
			}
			else
				cmd.Enabled = false;

		}

		/// <summary>
		/// Обработчик команды AddCurve
		/// </summary>
		/// <param name="cmd">Команда</param>
		private void onAddCurve(Command cmd)
		{
			XmlNode selXmlNode = (XmlNode) treeView.SelectedNode.Tag;
			
			if (selXmlNode.LocalName == "area")  return;

			// Создадим экземпляр вспомогательного класса значений по умолчанию
			AddCurveSettings settings = new AddCurveSettings();
			// Создать форму
			AddCurveForm acForm = new AddCurveForm();

			// Привязать элементы формы к свойствам класса значений по умолчанию
			acForm.Bindings(settings);

			// Показать диалог
			if ( acForm.ShowDialog() == DialogResult.Cancel) return;
			
			// Добавить кривую
			XmlNode addedXmlNode = _currentVesXml.AddCurve(settings, selXmlNode);

			// Обновить дерево
			fillTreeView(treeView, _currentXmlDoc);
			// Выделим добавленный элемент
			selectTreeNode(addedXmlNode, treeView);

		}

		/// <summary>
		/// Обработчик события Update в период простоя приложения для
		/// команды AddCurve
		/// </summary>
		/// <param name="cmd">Команда</param>
		private void updateAddCurveCommand(Command cmd)
		{
			if (treeView.SelectedNode != null)
			{
				XmlNode node = (XmlNode) treeView.SelectedNode.Tag;
				cmd.Enabled = ( node.LocalName == "profil" || node.LocalName == "curve");
			}
			else
				cmd.Enabled = false;

		}

		/// <summary>
		/// Обработчик команды ServiceSettings
		/// </summary>
		/// <param name="cmd">Команда</param>
		private void onServiceSettings(Command cmd)
		{
			Settings settings = new Settings();

			SettingsForm sf = new SettingsForm();
			sf.Bindings(settings);
			
			if ( sf.ShowDialog() == DialogResult.OK)
			{
				settings.Save();
			}
		}

		/// <summary>
		/// Обработчик команды Delete
		/// </summary>
		/// <param name="cmd">Команда</param>
		private void onDelete(Command cmd)
		{
			XmlNode xmlNode = (XmlNode) treeView.SelectedNode.Tag;
			string msg = String.Format("Вы хотите удалить {0} ?", treeView.SelectedNode.Text );
			if (	MessageBox.Show(msg, "Удаление", MessageBoxButtons.OKCancel , 
				MessageBoxIcon.Question) == DialogResult.Cancel ) return;

			XmlNode prev = _currentVesXml.DeleteNode(xmlNode);
			
			// Обновим дерево
			fillTreeView(treeView, _currentXmlDoc);
			this.selectTreeNode(prev, treeView);

		}

		/// <summary>
		/// Обработчик команды Refresh
		/// </summary>
		/// <param name="cmd">Команда</param>
		private void onRefresh(Command cmd)
		{
			if (_currentXmlDoc == null) return;

			if ( treeView.SelectedNode != null )
			{
				XmlNode xmlNode = (XmlNode) treeView.SelectedNode.Tag;

				// Обновим дерево
				fillTreeView(treeView, _currentXmlDoc);
				this.selectTreeNode(xmlNode, treeView);
			}

		}

		/// <summary>
		/// Обработчик команды About
		/// </summary>
		/// <param name="cmd">Команда</param>
		private void onAbout(Command cmd)
		{
			AboutForm  aboutForm = new AboutForm();
			aboutForm.ShowDialog();
		}

		/// <summary>
		/// Закрыть текущий файл и освободить ресурсы
		/// </summary>
		private void closeFile()
		{
			// Очистим treeView и прочие контролы
			treeView.Nodes.Clear();
			propertyGrid1.SelectedObject = null;
			dgSamples.DataSource = null;
			dgSamples.DataSource = null;
			statusBar.Text = "Файл не загружен";

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

			string areaName;
			string areaDescr;
			
			XmlNode	areaNode;
			areaNode = xmlDoc.SelectSingleNode("/area");
			areaName = areaNode.Attributes.GetNamedItem("name").Value;
			TreeNode areaTreeNode = treeView.Nodes.Add(areaName);
			areaTreeNode.Tag = areaNode;		// Прицепим к узлу объект
			areaTreeNode.ImageIndex = 0;
			areaTreeNode.SelectedImageIndex = 0;

			areaNode = xmlDoc.SelectSingleNode("/area/areadescr");
			areaDescr = areaNode.InnerText;
			
			// Загрузим профили
			_fillProfilesNodes(xmlDoc, treeView, areaTreeNode);

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
			string profDescr;
			XmlNode currNode;
			XmlNodeList profNodeList;

			profNodeList = xmlDoc.SelectNodes("/area/profil");

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

				currNode  = profNode.SelectSingleNode("profildescr");
				if (currNode != null)
					profDescr = currNode.InnerText;
				else
					profDescr = "*";

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
			XmlNodeList curveNodeList;

			curveNodeList = profNode.SelectNodes("curves/curve");
			foreach (XmlNode curveNode in curveNodeList)
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
				currTreeNode = currTreeNode.NextVisibleNode;
			}
		}


		#endregion

		#region Event Handlers

		/// <summary>
		/// Обработчик события AfterSelect treeView
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void treeView_AfterSelect(object sender, System.Windows.Forms.TreeViewEventArgs e)
		{
			XmlNode node = (XmlNode) e.Node.Tag;

			switch (node.LocalName)
			{
				case "curve":
					VesCurve vesCurve = new VesCurve(node,_currentXmlDoc);
					_currentCurve   = vesCurve;

					dgSamples.DataSource = vesCurve.Samples;
					dgLayers.DataSource = vesCurve.Layers;
					propertyGrid1.SelectedObject = _currentCurve;
					propertyGrid1.Visible = true;
					//					tabPage2.Invalidate();					// Перерисуем
					break;
				case "area":
					VesArea vesArea = new VesArea(node);
					propertyGrid1.SelectedObject = vesArea;
					break;
				case "profil":
					VesProfil vesProfil = new VesProfil(node);
					propertyGrid1.SelectedObject = vesProfil;
					break;
			}
			tabPage2.Invalidate();					// Перерисуем

		}


		private void button1_Click(object sender, System.EventArgs e)
		{
			if (_currentCurve != null) 
			{
				_currentCurve.NLayers = _currentCurve.Layers.Rows.Count;
				_currentCurve.AutoInterp(0.01F,50);
			}
		}

		private void tabPage2_Paint(object sender, System.Windows.Forms.PaintEventArgs e)
		{
			if (_currentCurve != null)
			{
				// Создадим контекст устройства
				Graphics  clientDC = e.Graphics;
				_currentCurve.Draw(clientDC, tabPage2.Width, tabPage2.Height);
			}
		}

		private void button2_Click(object sender, System.EventArgs e)
		{
			if (_currentCurve != null)
			{
				_currentCurve.UpdateLayersXml();
				_currentCurve.UpdateSamplesXml();
			}
		}


		private void printDoc_PrintPage(object sender, System.Drawing.Printing.PrintPageEventArgs e)
		{
			Graphics g = e.Graphics;

			if (_currentCurve != null)
			{
				PrintingSettings ps = new PrintingSettings();
				_currentCurve.Print(g, ps);
			}
		}

			
		#endregion

		private void button3_Click(object sender, System.EventArgs e)
		{
			InterprForm frm = new InterprForm();
			frm.ShowDialog();
		}

		
	}
}
