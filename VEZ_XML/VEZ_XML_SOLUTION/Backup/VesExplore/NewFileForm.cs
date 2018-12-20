using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace VesExplore
{
	/// <summary>
	/// Summary description for NewFile.
	/// </summary>
	public class NewFileForm : System.Windows.Forms.Form
	{
		#region Controls

		private System.Windows.Forms.Button btnOk;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.TabControl tabControl1;
		private System.Windows.Forms.TabPage tabPageArea;
		private System.Windows.Forms.TabPage tabPageProf;
		private System.Windows.Forms.TabPage tabPageCurve;
		private System.Windows.Forms.TextBox txtNcurves;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.TextBox txtProfName;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox txtAreaDescr;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox txtAreaName;
		private System.Windows.Forms.CheckBox cbProfilType;
		private System.Windows.Forms.TextBox txtMN2;
		private System.Windows.Forms.TextBox txtAb2String;
		private System.Windows.Forms.Label label11;
		private System.Windows.Forms.TextBox txtDY;
		private System.Windows.Forms.Label label12;
		private System.Windows.Forms.TextBox txtDX;
		private System.Windows.Forms.DateTimePicker dateTimePicker;
		private System.Windows.Forms.Label label14;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.TextBox txtCalculatorName;
		private System.Windows.Forms.TextBox txtOperatorName;
		private System.Windows.Forms.TextBox txtDeviceName;
		private System.Windows.Forms.TextBox txtCurveName;
		private System.Windows.Forms.NumericUpDown nudNprof;
		private System.Windows.Forms.Label label13;
		private System.Windows.Forms.Label label9;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.Label label10;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Label label6;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;
		
		#endregion

		#region Constructor/Dispose

		public NewFileForm()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
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
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(NewFileForm));
			this.btnOk = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.tabControl1 = new System.Windows.Forms.TabControl();
			this.tabPageArea = new System.Windows.Forms.TabPage();
			this.label14 = new System.Windows.Forms.Label();
			this.dateTimePicker = new System.Windows.Forms.DateTimePicker();
			this.txtAreaDescr = new System.Windows.Forms.TextBox();
			this.label3 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.txtAreaName = new System.Windows.Forms.TextBox();
			this.tabPageProf = new System.Windows.Forms.TabPage();
			this.nudNprof = new System.Windows.Forms.NumericUpDown();
			this.label12 = new System.Windows.Forms.Label();
			this.txtDY = new System.Windows.Forms.TextBox();
			this.label4 = new System.Windows.Forms.Label();
			this.txtProfName = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.tabPageCurve = new System.Windows.Forms.TabPage();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.txtCalculatorName = new System.Windows.Forms.TextBox();
			this.txtOperatorName = new System.Windows.Forms.TextBox();
			this.txtDeviceName = new System.Windows.Forms.TextBox();
			this.txtCurveName = new System.Windows.Forms.TextBox();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.txtDX = new System.Windows.Forms.TextBox();
			this.label11 = new System.Windows.Forms.Label();
			this.txtAb2String = new System.Windows.Forms.TextBox();
			this.txtMN2 = new System.Windows.Forms.TextBox();
			this.cbProfilType = new System.Windows.Forms.CheckBox();
			this.txtNcurves = new System.Windows.Forms.TextBox();
			this.label13 = new System.Windows.Forms.Label();
			this.label9 = new System.Windows.Forms.Label();
			this.label5 = new System.Windows.Forms.Label();
			this.label10 = new System.Windows.Forms.Label();
			this.label8 = new System.Windows.Forms.Label();
			this.label7 = new System.Windows.Forms.Label();
			this.label6 = new System.Windows.Forms.Label();
			this.tabControl1.SuspendLayout();
			this.tabPageArea.SuspendLayout();
			this.tabPageProf.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.nudNprof)).BeginInit();
			this.tabPageCurve.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.SuspendLayout();
			// 
			// btnOk
			// 
			this.btnOk.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.btnOk.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.btnOk.Location = new System.Drawing.Point(144, 344);
			this.btnOk.Name = "btnOk";
			this.btnOk.Size = new System.Drawing.Size(71, 23);
			this.btnOk.TabIndex = 0;
			this.btnOk.Text = "OK";
			// 
			// btnCancel
			// 
			this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.btnCancel.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.btnCancel.Location = new System.Drawing.Point(224, 344);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(71, 23);
			this.btnCancel.TabIndex = 1;
			this.btnCancel.Text = "Cancel";
			// 
			// tabControl1
			// 
			this.tabControl1.Controls.AddRange(new System.Windows.Forms.Control[] {
																					  this.tabPageArea,
																					  this.tabPageProf,
																					  this.tabPageCurve});
			this.tabControl1.Location = new System.Drawing.Point(8, 8);
			this.tabControl1.Name = "tabControl1";
			this.tabControl1.SelectedIndex = 0;
			this.tabControl1.Size = new System.Drawing.Size(288, 328);
			this.tabControl1.TabIndex = 0;
			// 
			// tabPageArea
			// 
			this.tabPageArea.Controls.AddRange(new System.Windows.Forms.Control[] {
																					  this.label14,
																					  this.dateTimePicker,
																					  this.txtAreaDescr,
																					  this.label3,
																					  this.label2,
																					  this.txtAreaName});
			this.tabPageArea.Location = new System.Drawing.Point(4, 22);
			this.tabPageArea.Name = "tabPageArea";
			this.tabPageArea.Size = new System.Drawing.Size(280, 302);
			this.tabPageArea.TabIndex = 0;
			this.tabPageArea.Text = "Участок";
			// 
			// label14
			// 
			this.label14.Location = new System.Drawing.Point(16, 208);
			this.label14.Name = "label14";
			this.label14.Size = new System.Drawing.Size(100, 16);
			this.label14.TabIndex = 4;
			this.label14.Text = "Дата";
			// 
			// dateTimePicker
			// 
			this.dateTimePicker.Location = new System.Drawing.Point(17, 224);
			this.dateTimePicker.Name = "dateTimePicker";
			this.dateTimePicker.TabIndex = 5;
			// 
			// txtAreaDescr
			// 
			this.txtAreaDescr.Location = new System.Drawing.Point(16, 80);
			this.txtAreaDescr.Multiline = true;
			this.txtAreaDescr.Name = "txtAreaDescr";
			this.txtAreaDescr.Size = new System.Drawing.Size(248, 104);
			this.txtAreaDescr.TabIndex = 3;
			this.txtAreaDescr.Text = "";
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(16, 63);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(100, 12);
			this.label3.TabIndex = 2;
			this.label3.Text = "Описание";
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(16, 16);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(100, 16);
			this.label2.TabIndex = 0;
			this.label2.Text = "Наименование";
			// 
			// txtAreaName
			// 
			this.txtAreaName.Location = new System.Drawing.Point(16, 32);
			this.txtAreaName.Name = "txtAreaName";
			this.txtAreaName.Size = new System.Drawing.Size(248, 20);
			this.txtAreaName.TabIndex = 1;
			this.txtAreaName.Text = "";
			// 
			// tabPageProf
			// 
			this.tabPageProf.Controls.AddRange(new System.Windows.Forms.Control[] {
																					  this.nudNprof,
																					  this.label12,
																					  this.txtDY,
																					  this.label4,
																					  this.txtProfName,
																					  this.label1});
			this.tabPageProf.Location = new System.Drawing.Point(4, 22);
			this.tabPageProf.Name = "tabPageProf";
			this.tabPageProf.Size = new System.Drawing.Size(280, 302);
			this.tabPageProf.TabIndex = 1;
			this.tabPageProf.Text = "Профили";
			// 
			// nudNprof
			// 
			this.nudNprof.Location = new System.Drawing.Point(16, 64);
			this.nudNprof.Name = "nudNprof";
			this.nudNprof.Size = new System.Drawing.Size(56, 20);
			this.nudNprof.TabIndex = 0;
			this.nudNprof.Value = new System.Decimal(new int[] {
																   1,
																   0,
																   0,
																   0});
			// 
			// label12
			// 
			this.label12.Location = new System.Drawing.Point(74, 107);
			this.label12.Name = "label12";
			this.label12.Size = new System.Drawing.Size(178, 16);
			this.label12.TabIndex = 5;
			this.label12.Text = "Расстояние м-ду профилями, м ";
			// 
			// txtDY
			// 
			this.txtDY.Location = new System.Drawing.Point(16, 104);
			this.txtDY.Name = "txtDY";
			this.txtDY.Size = new System.Drawing.Size(56, 20);
			this.txtDY.TabIndex = 4;
			this.txtDY.Text = "";
			// 
			// label4
			// 
			this.label4.Location = new System.Drawing.Point(16, 8);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(81, 16);
			this.label4.TabIndex = 3;
			this.label4.Text = "Имя профиля:";
			// 
			// txtProfName
			// 
			this.txtProfName.Location = new System.Drawing.Point(16, 24);
			this.txtProfName.Name = "txtProfName";
			this.txtProfName.Size = new System.Drawing.Size(160, 20);
			this.txtProfName.TabIndex = 2;
			this.txtProfName.Text = "";
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(74, 66);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(101, 18);
			this.label1.TabIndex = 1;
			this.label1.Text = "Кол-во профилей";
			// 
			// tabPageCurve
			// 
			this.tabPageCurve.Controls.AddRange(new System.Windows.Forms.Control[] {
																					   this.label13,
																					   this.label9,
																					   this.label5,
																					   this.groupBox2,
																					   this.groupBox1,
																					   this.txtDX,
																					   this.label11,
																					   this.txtAb2String,
																					   this.txtMN2,
																					   this.cbProfilType,
																					   this.txtNcurves});
			this.tabPageCurve.Location = new System.Drawing.Point(4, 22);
			this.tabPageCurve.Name = "tabPageCurve";
			this.tabPageCurve.Size = new System.Drawing.Size(280, 302);
			this.tabPageCurve.TabIndex = 2;
			this.tabPageCurve.Text = "Кривые ВЭЗ";
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.AddRange(new System.Windows.Forms.Control[] {
																					this.label10,
																					this.label8,
																					this.label7,
																					this.label6,
																					this.txtCalculatorName,
																					this.txtOperatorName,
																					this.txtDeviceName,
																					this.txtCurveName});
			this.groupBox2.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.groupBox2.Location = new System.Drawing.Point(8, 126);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(264, 120);
			this.groupBox2.TabIndex = 8;
			this.groupBox2.TabStop = false;
			// 
			// txtCalculatorName
			// 
			this.txtCalculatorName.Location = new System.Drawing.Point(120, 92);
			this.txtCalculatorName.Name = "txtCalculatorName";
			this.txtCalculatorName.Size = new System.Drawing.Size(128, 20);
			this.txtCalculatorName.TabIndex = 6;
			this.txtCalculatorName.Text = "";
			// 
			// txtOperatorName
			// 
			this.txtOperatorName.Location = new System.Drawing.Point(120, 67);
			this.txtOperatorName.Name = "txtOperatorName";
			this.txtOperatorName.Size = new System.Drawing.Size(128, 20);
			this.txtOperatorName.TabIndex = 4;
			this.txtOperatorName.Text = "";
			// 
			// txtDeviceName
			// 
			this.txtDeviceName.Location = new System.Drawing.Point(120, 42);
			this.txtDeviceName.Name = "txtDeviceName";
			this.txtDeviceName.ReadOnly = true;
			this.txtDeviceName.Size = new System.Drawing.Size(128, 20);
			this.txtDeviceName.TabIndex = 2;
			this.txtDeviceName.Text = "";
			// 
			// txtCurveName
			// 
			this.txtCurveName.Location = new System.Drawing.Point(120, 17);
			this.txtCurveName.Name = "txtCurveName";
			this.txtCurveName.Size = new System.Drawing.Size(128, 20);
			this.txtCurveName.TabIndex = 0;
			this.txtCurveName.Text = "";
			// 
			// groupBox1
			// 
			this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.groupBox1.Location = new System.Drawing.Point(8, 30);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(264, 8);
			this.groupBox1.TabIndex = 1;
			this.groupBox1.TabStop = false;
			// 
			// txtDX
			// 
			this.txtDX.Location = new System.Drawing.Point(152, 96);
			this.txtDX.Name = "txtDX";
			this.txtDX.Size = new System.Drawing.Size(56, 20);
			this.txtDX.TabIndex = 6;
			this.txtDX.Text = "";
			// 
			// label11
			// 
			this.label11.Location = new System.Drawing.Point(6, 256);
			this.label11.Name = "label11";
			this.label11.Size = new System.Drawing.Size(258, 16);
			this.label11.TabIndex = 9;
			this.label11.Text = "Разносы AB/2, метры (через пробел)";
			// 
			// txtAb2String
			// 
			this.txtAb2String.Location = new System.Drawing.Point(8, 272);
			this.txtAb2String.Name = "txtAb2String";
			this.txtAb2String.Size = new System.Drawing.Size(264, 20);
			this.txtAb2String.TabIndex = 10;
			this.txtAb2String.Text = "";
			// 
			// txtMN2
			// 
			this.txtMN2.Location = new System.Drawing.Point(152, 70);
			this.txtMN2.Name = "txtMN2";
			this.txtMN2.Size = new System.Drawing.Size(56, 20);
			this.txtMN2.TabIndex = 4;
			this.txtMN2.Text = "";
			// 
			// cbProfilType
			// 
			this.cbProfilType.Location = new System.Drawing.Point(18, 8);
			this.cbProfilType.Name = "cbProfilType";
			this.cbProfilType.Size = new System.Drawing.Size(214, 24);
			this.cbProfilType.TabIndex = 0;
			this.cbProfilType.Text = "Кривые расположены на профиле";
			// 
			// txtNcurves
			// 
			this.txtNcurves.Location = new System.Drawing.Point(152, 44);
			this.txtNcurves.Name = "txtNcurves";
			this.txtNcurves.Size = new System.Drawing.Size(56, 20);
			this.txtNcurves.TabIndex = 2;
			this.txtNcurves.Text = "";
			// 
			// label13
			// 
			this.label13.Location = new System.Drawing.Point(8, 99);
			this.label13.Name = "label13";
			this.label13.Size = new System.Drawing.Size(142, 16);
			this.label13.TabIndex = 13;
			this.label13.Text = "Шаг по профилю, м:";
			// 
			// label9
			// 
			this.label9.Location = new System.Drawing.Point(8, 73);
			this.label9.Name = "label9";
			this.label9.Size = new System.Drawing.Size(142, 12);
			this.label9.TabIndex = 12;
			this.label9.Text = "MN/2, метры:";
			// 
			// label5
			// 
			this.label5.Location = new System.Drawing.Point(8, 45);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(142, 16);
			this.label5.TabIndex = 11;
			this.label5.Text = "Кол-во точек на профиле:";
			// 
			// label10
			// 
			this.label10.Location = new System.Drawing.Point(7, 94);
			this.label10.Name = "label10";
			this.label10.Size = new System.Drawing.Size(83, 16);
			this.label10.TabIndex = 11;
			this.label10.Text = "Вычислитель:";
			// 
			// label8
			// 
			this.label8.Location = new System.Drawing.Point(7, 70);
			this.label8.Name = "label8";
			this.label8.Size = new System.Drawing.Size(83, 16);
			this.label8.TabIndex = 10;
			this.label8.Text = "Оператор:";
			// 
			// label7
			// 
			this.label7.Location = new System.Drawing.Point(7, 44);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(83, 16);
			this.label7.TabIndex = 9;
			this.label7.Text = "Аппаратура:";
			// 
			// label6
			// 
			this.label6.Location = new System.Drawing.Point(7, 21);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(83, 13);
			this.label6.TabIndex = 8;
			this.label6.Text = "Имя кривой:";
			// 
			// NewFileForm
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(306, 376);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.tabControl1,
																		  this.btnCancel,
																		  this.btnOk});
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Name = "NewFileForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Создание нового файла";
			this.Load += new System.EventHandler(this.NewFileForm_Load);
			this.tabControl1.ResumeLayout(false);
			this.tabPageArea.ResumeLayout(false);
			this.tabPageProf.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.nudNprof)).EndInit();
			this.tabPageCurve.ResumeLayout(false);
			this.groupBox2.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		#region Methods
		/// <summary>
		/// Метод производит привязку элементов управления формы
		/// к полям класса NewFileSettings
		/// Метод необходимо вызывать после создания экземпляра формы
		/// перед показом формы
		/// </summary>
		/// <param name="defaults">Экземпляр класса, к свойствам которого привязываются элементы формы</param>
		public void Bindings(NewFileSettings settings)
		{
			txtAreaName.DataBindings.Add("Text",settings,"AreaName");
			txtAreaDescr.DataBindings.Add("Text",settings,"AreaDescr");
			dateTimePicker.DataBindings.Add("Value",settings,"Date");

			txtProfName.DataBindings.Add("Text",settings,"ProfName");
			nudNprof.DataBindings.Add("Value",settings,"NProfiles");
			txtDY.DataBindings.Add("Text",settings,"DY");
			cbProfilType.DataBindings.Add("Checked",settings,"TypeProf");

			txtCurveName.DataBindings.Add("Text",settings,"CurveName");
			txtNcurves.DataBindings.Add("Text",settings,"NCurves");
			txtDeviceName.DataBindings.Add("Text",settings,"DeviceName");
			txtOperatorName.DataBindings.Add("Text",settings,"OperatorName");
			txtCalculatorName.DataBindings.Add("Text",settings,"CalculatorName");
			txtMN2.DataBindings.Add("Text",settings,"MN2");
			txtAb2String.DataBindings.Add("Text",settings,"AB2String");
			txtDX.DataBindings.Add("Text",settings,"DX");

		}

		#endregion

		#region Event Handlers
		private void NewFileForm_Load(object sender, System.EventArgs e)
		{
		
		}

		#endregion

	}
}
