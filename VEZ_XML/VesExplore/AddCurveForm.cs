using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace VesExplore
{
	/// <summary>
	/// Summary description for AddCurveForm.
	/// </summary>
	public class AddCurveForm : System.Windows.Forms.Form
	{
		#region Controls
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.Label label10;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.TextBox txtCalculatorName;
		private System.Windows.Forms.TextBox txtOperatorName;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.TextBox txtDeviceName;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.TextBox txtCurveName;
		private System.Windows.Forms.DateTimePicker dtPicker;
		private System.Windows.Forms.TextBox txtDescr;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.Button btnOk;
		private System.Windows.Forms.DataGrid dgSamples;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.TextBox txtX;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.TextBox txtY;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.TextBox txtZ;
		private System.Windows.Forms.Label label9;
		private System.Windows.Forms.ComboBox cbWeater;
		private System.Windows.Forms.DataGridTableStyle dataGridTableStyle;
		private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumn1;
		private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumn2;
		private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumn3;
		private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumn4;
		private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumn5;
		private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumn6;
		private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumn7;
		private System.Windows.Forms.DataGridTextBoxColumn dataGridTextBoxColumn8;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;
		#endregion

		#region Constructors/Disposing
		public AddCurveForm()
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
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(AddCurveForm));
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.cbWeater = new System.Windows.Forms.ComboBox();
			this.label9 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.txtDescr = new System.Windows.Forms.TextBox();
			this.dtPicker = new System.Windows.Forms.DateTimePicker();
			this.label10 = new System.Windows.Forms.Label();
			this.label8 = new System.Windows.Forms.Label();
			this.txtCalculatorName = new System.Windows.Forms.TextBox();
			this.txtOperatorName = new System.Windows.Forms.TextBox();
			this.label7 = new System.Windows.Forms.Label();
			this.txtDeviceName = new System.Windows.Forms.TextBox();
			this.label6 = new System.Windows.Forms.Label();
			this.txtCurveName = new System.Windows.Forms.TextBox();
			this.dgSamples = new System.Windows.Forms.DataGrid();
			this.dataGridTableStyle = new System.Windows.Forms.DataGridTableStyle();
			this.dataGridTextBoxColumn1 = new System.Windows.Forms.DataGridTextBoxColumn();
			this.dataGridTextBoxColumn2 = new System.Windows.Forms.DataGridTextBoxColumn();
			this.dataGridTextBoxColumn3 = new System.Windows.Forms.DataGridTextBoxColumn();
			this.dataGridTextBoxColumn4 = new System.Windows.Forms.DataGridTextBoxColumn();
			this.dataGridTextBoxColumn5 = new System.Windows.Forms.DataGridTextBoxColumn();
			this.dataGridTextBoxColumn6 = new System.Windows.Forms.DataGridTextBoxColumn();
			this.dataGridTextBoxColumn7 = new System.Windows.Forms.DataGridTextBoxColumn();
			this.dataGridTextBoxColumn8 = new System.Windows.Forms.DataGridTextBoxColumn();
			this.btnCancel = new System.Windows.Forms.Button();
			this.btnOk = new System.Windows.Forms.Button();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.label5 = new System.Windows.Forms.Label();
			this.txtZ = new System.Windows.Forms.TextBox();
			this.label4 = new System.Windows.Forms.Label();
			this.txtY = new System.Windows.Forms.TextBox();
			this.label3 = new System.Windows.Forms.Label();
			this.txtX = new System.Windows.Forms.TextBox();
			this.groupBox2.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.dgSamples)).BeginInit();
			this.groupBox1.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.AddRange(new System.Windows.Forms.Control[] {
																					this.cbWeater,
																					this.label9,
																					this.label2,
																					this.label1,
																					this.txtDescr,
																					this.dtPicker,
																					this.label10,
																					this.label8,
																					this.txtCalculatorName,
																					this.txtOperatorName,
																					this.label7,
																					this.txtDeviceName,
																					this.label6,
																					this.txtCurveName});
			this.groupBox2.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.groupBox2.Location = new System.Drawing.Point(8, 11);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(224, 277);
			this.groupBox2.TabIndex = 0;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "Заголовок";
			// 
			// cbWeater
			// 
			this.cbWeater.Items.AddRange(new object[] {
														  "Ясно",
														  "Пасмурно",
														  "Сыро",
														  "Дождь",
														  "Снег",
														  "Гололед"});
			this.cbWeater.Location = new System.Drawing.Point(8, 196);
			this.cbWeater.Name = "cbWeater";
			this.cbWeater.Size = new System.Drawing.Size(130, 21);
			this.cbWeater.TabIndex = 14;
			// 
			// label9
			// 
			this.label9.Location = new System.Drawing.Point(142, 243);
			this.label9.Name = "label9";
			this.label9.Size = new System.Drawing.Size(55, 16);
			this.label9.TabIndex = 13;
			this.label9.Text = "Дата";
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(141, 200);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(80, 12);
			this.label2.TabIndex = 11;
			this.label2.Text = "Погода";
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(8, 44);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(100, 12);
			this.label1.TabIndex = 2;
			this.label1.Text = "Описание";
			// 
			// txtDescr
			// 
			this.txtDescr.Location = new System.Drawing.Point(8, 61);
			this.txtDescr.Multiline = true;
			this.txtDescr.Name = "txtDescr";
			this.txtDescr.Size = new System.Drawing.Size(208, 56);
			this.txtDescr.TabIndex = 3;
			this.txtDescr.Text = "";
			// 
			// dtPicker
			// 
			this.dtPicker.Location = new System.Drawing.Point(8, 240);
			this.dtPicker.Name = "dtPicker";
			this.dtPicker.Size = new System.Drawing.Size(128, 20);
			this.dtPicker.TabIndex = 12;
			// 
			// label10
			// 
			this.label10.Location = new System.Drawing.Point(141, 176);
			this.label10.Name = "label10";
			this.label10.Size = new System.Drawing.Size(80, 12);
			this.label10.TabIndex = 9;
			this.label10.Text = "Вычислитель";
			// 
			// label8
			// 
			this.label8.Location = new System.Drawing.Point(141, 150);
			this.label8.Name = "label8";
			this.label8.Size = new System.Drawing.Size(80, 16);
			this.label8.TabIndex = 7;
			this.label8.Text = "Оператор";
			// 
			// txtCalculatorName
			// 
			this.txtCalculatorName.Location = new System.Drawing.Point(8, 172);
			this.txtCalculatorName.Name = "txtCalculatorName";
			this.txtCalculatorName.Size = new System.Drawing.Size(128, 20);
			this.txtCalculatorName.TabIndex = 8;
			this.txtCalculatorName.Text = "";
			// 
			// txtOperatorName
			// 
			this.txtOperatorName.Location = new System.Drawing.Point(8, 148);
			this.txtOperatorName.Name = "txtOperatorName";
			this.txtOperatorName.Size = new System.Drawing.Size(128, 20);
			this.txtOperatorName.TabIndex = 6;
			this.txtOperatorName.Text = "";
			// 
			// label7
			// 
			this.label7.Location = new System.Drawing.Point(141, 126);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(80, 16);
			this.label7.TabIndex = 5;
			this.label7.Text = "Аппаратура";
			// 
			// txtDeviceName
			// 
			this.txtDeviceName.Location = new System.Drawing.Point(8, 124);
			this.txtDeviceName.Name = "txtDeviceName";
			this.txtDeviceName.ReadOnly = true;
			this.txtDeviceName.Size = new System.Drawing.Size(128, 20);
			this.txtDeviceName.TabIndex = 4;
			this.txtDeviceName.Text = "";
			// 
			// label6
			// 
			this.label6.Location = new System.Drawing.Point(141, 23);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(68, 13);
			this.label6.TabIndex = 1;
			this.label6.Text = "Имя кривой";
			// 
			// txtCurveName
			// 
			this.txtCurveName.Location = new System.Drawing.Point(8, 19);
			this.txtCurveName.Name = "txtCurveName";
			this.txtCurveName.Size = new System.Drawing.Size(128, 20);
			this.txtCurveName.TabIndex = 0;
			this.txtCurveName.Text = "";
			// 
			// dgSamples
			// 
			this.dgSamples.AllowSorting = false;
			this.dgSamples.CaptionText = "Отсчеты";
			this.dgSamples.DataMember = "";
			this.dgSamples.FlatMode = true;
			this.dgSamples.HeaderForeColor = System.Drawing.SystemColors.ControlText;
			this.dgSamples.Location = new System.Drawing.Point(240, 16);
			this.dgSamples.Name = "dgSamples";
			this.dgSamples.PreferredColumnWidth = 45;
			this.dgSamples.Size = new System.Drawing.Size(384, 304);
			this.dgSamples.TabIndex = 2;
			this.dgSamples.TableStyles.AddRange(new System.Windows.Forms.DataGridTableStyle[] {
																								  this.dataGridTableStyle});
			// 
			// dataGridTableStyle
			// 
			this.dataGridTableStyle.DataGrid = this.dgSamples;
			this.dataGridTableStyle.GridColumnStyles.AddRange(new System.Windows.Forms.DataGridColumnStyle[] {
																												 this.dataGridTextBoxColumn1,
																												 this.dataGridTextBoxColumn2,
																												 this.dataGridTextBoxColumn3,
																												 this.dataGridTextBoxColumn4,
																												 this.dataGridTextBoxColumn5,
																												 this.dataGridTextBoxColumn6,
																												 this.dataGridTextBoxColumn7,
																												 this.dataGridTextBoxColumn8});
			this.dataGridTableStyle.HeaderForeColor = System.Drawing.SystemColors.ControlText;
			this.dataGridTableStyle.MappingName = "";
			// 
			// dataGridTextBoxColumn1
			// 
			this.dataGridTextBoxColumn1.Format = "";
			this.dataGridTextBoxColumn1.FormatInfo = null;
			this.dataGridTextBoxColumn1.HeaderText = "AB/2";
			this.dataGridTextBoxColumn1.MappingName = "AB2";
			this.dataGridTextBoxColumn1.Width = 45;
			// 
			// dataGridTextBoxColumn2
			// 
			this.dataGridTextBoxColumn2.Format = "";
			this.dataGridTextBoxColumn2.FormatInfo = null;
			this.dataGridTextBoxColumn2.HeaderText = "MN/2";
			this.dataGridTextBoxColumn2.MappingName = "MN2";
			this.dataGridTextBoxColumn2.Width = 45;
			// 
			// dataGridTextBoxColumn3
			// 
			this.dataGridTextBoxColumn3.Format = "";
			this.dataGridTextBoxColumn3.FormatInfo = null;
			this.dataGridTextBoxColumn3.HeaderText = "K";
			this.dataGridTextBoxColumn3.MappingName = "K";
			this.dataGridTextBoxColumn3.Width = 0;
			// 
			// dataGridTextBoxColumn4
			// 
			this.dataGridTextBoxColumn4.Format = "";
			this.dataGridTextBoxColumn4.FormatInfo = null;
			this.dataGridTextBoxColumn4.HeaderText = "Отсч";
			this.dataGridTextBoxColumn4.MappingName = "U";
			this.dataGridTextBoxColumn4.Width = 45;
			// 
			// dataGridTextBoxColumn5
			// 
			this.dataGridTextBoxColumn5.Format = "";
			this.dataGridTextBoxColumn5.FormatInfo = null;
			this.dataGridTextBoxColumn5.HeaderText = "Диап";
			this.dataGridTextBoxColumn5.MappingName = "Diap";
			this.dataGridTextBoxColumn5.Width = 45;
			// 
			// dataGridTextBoxColumn6
			// 
			this.dataGridTextBoxColumn6.Format = "";
			this.dataGridTextBoxColumn6.FormatInfo = null;
			this.dataGridTextBoxColumn6.HeaderText = "I, mA";
			this.dataGridTextBoxColumn6.MappingName = "I";
			this.dataGridTextBoxColumn6.Width = 45;
			// 
			// dataGridTextBoxColumn7
			// 
			this.dataGridTextBoxColumn7.Format = "";
			this.dataGridTextBoxColumn7.FormatInfo = null;
			this.dataGridTextBoxColumn7.HeaderText = "Уд сопр Омм";
			this.dataGridTextBoxColumn7.MappingName = "ROK";
			this.dataGridTextBoxColumn7.Width = 45;
			// 
			// dataGridTextBoxColumn8
			// 
			this.dataGridTextBoxColumn8.Format = "";
			this.dataGridTextBoxColumn8.FormatInfo = null;
			this.dataGridTextBoxColumn8.HeaderText = "Примеч.";
			this.dataGridTextBoxColumn8.MappingName = "Note";
			this.dataGridTextBoxColumn8.Width = 60;
			// 
			// btnCancel
			// 
			this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.btnCancel.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.btnCancel.Location = new System.Drawing.Point(552, 328);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(71, 23);
			this.btnCancel.TabIndex = 4;
			this.btnCancel.Text = "Cancel";
			// 
			// btnOk
			// 
			this.btnOk.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.btnOk.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.btnOk.Location = new System.Drawing.Point(480, 328);
			this.btnOk.Name = "btnOk";
			this.btnOk.Size = new System.Drawing.Size(71, 23);
			this.btnOk.TabIndex = 3;
			this.btnOk.Text = "OK";
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.AddRange(new System.Windows.Forms.Control[] {
																					this.label5,
																					this.txtZ,
																					this.label4,
																					this.txtY,
																					this.label3,
																					this.txtX});
			this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.groupBox1.Location = new System.Drawing.Point(8, 291);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(224, 64);
			this.groupBox1.TabIndex = 1;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Координаты";
			// 
			// label5
			// 
			this.label5.Location = new System.Drawing.Point(181, 14);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(11, 12);
			this.label5.TabIndex = 4;
			this.label5.Text = "Z";
			// 
			// txtZ
			// 
			this.txtZ.Location = new System.Drawing.Point(167, 32);
			this.txtZ.Name = "txtZ";
			this.txtZ.Size = new System.Drawing.Size(39, 20);
			this.txtZ.TabIndex = 5;
			this.txtZ.Text = "";
			// 
			// label4
			// 
			this.label4.Location = new System.Drawing.Point(100, 16);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(16, 12);
			this.label4.TabIndex = 2;
			this.label4.Text = "Y";
			// 
			// txtY
			// 
			this.txtY.Location = new System.Drawing.Point(88, 32);
			this.txtY.Name = "txtY";
			this.txtY.Size = new System.Drawing.Size(41, 20);
			this.txtY.TabIndex = 3;
			this.txtY.Text = "";
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(21, 17);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(16, 12);
			this.label3.TabIndex = 0;
			this.label3.Text = "X";
			// 
			// txtX
			// 
			this.txtX.Location = new System.Drawing.Point(9, 32);
			this.txtX.Name = "txtX";
			this.txtX.Size = new System.Drawing.Size(41, 20);
			this.txtX.TabIndex = 1;
			this.txtX.Text = "";
			// 
			// AddCurveForm
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(634, 360);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.groupBox1,
																		  this.btnCancel,
																		  this.btnOk,
																		  this.dgSamples,
																		  this.groupBox2});
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Name = "AddCurveForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Добавить кривую ВЭЗ";
			this.groupBox2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.dgSamples)).EndInit();
			this.groupBox1.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// Метод производит привязку элементов управления формы
		/// к полям класса AddCurveSettings
		/// Метод необходимо вызывать после создания экземпляра формы
		/// перед показом формы
		/// </summary>
		public void Bindings(AddCurveSettings settings)
		{
			dgSamples.DataSource = settings.SamplesTable;

			txtCurveName.DataBindings.Add("Text", settings, "CurveName");
			txtDescr.DataBindings.Add("Text", settings, "CurveDescr");
			txtDeviceName.DataBindings.Add("Text", settings, "Device");
			txtCalculatorName.DataBindings.Add("Text", settings, "CalculatorName");
			txtOperatorName.DataBindings.Add("Text", settings, "OperatorName");
			cbWeater.DataBindings.Add("Text", settings, "Weather");
			txtX.DataBindings.Add("Text", settings, "X");
			txtY.DataBindings.Add("Text", settings, "Y");
			txtZ.DataBindings.Add("Text", settings, "Z");
			dtPicker.DataBindings.Add("Value", settings, "Date");

		}
	}
}
