using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace VesExplore
{
	/// <summary>
	/// Форма для редактирования настроек приложения
	/// </summary>
	public class SettingsForm : System.Windows.Forms.Form
	{
		#region Controls

		private System.Windows.Forms.Button btnOk;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.TabControl tcSettings;
		private System.Windows.Forms.TabPage tabPageNames;
		private System.Windows.Forms.TabPage tabPageVes;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.TextBox txtMN2;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.TextBox txtI;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TextBox txtCurveName;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox txtProfName;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox txtAreaName;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.TextBox txtOperName;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.TextBox txtCalcName;
		private System.Windows.Forms.DataGrid dgVes;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.TextBox txtDevice;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;
		#endregion

		#region Constructor/Dispose
		public SettingsForm()
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
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(SettingsForm));
			this.btnOk = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.tcSettings = new System.Windows.Forms.TabControl();
			this.tabPageNames = new System.Windows.Forms.TabPage();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.txtDevice = new System.Windows.Forms.TextBox();
			this.label8 = new System.Windows.Forms.Label();
			this.label7 = new System.Windows.Forms.Label();
			this.txtCalcName = new System.Windows.Forms.TextBox();
			this.label6 = new System.Windows.Forms.Label();
			this.txtOperName = new System.Windows.Forms.TextBox();
			this.label3 = new System.Windows.Forms.Label();
			this.txtCurveName = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.txtProfName = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.txtAreaName = new System.Windows.Forms.TextBox();
			this.tabPageVes = new System.Windows.Forms.TabPage();
			this.dgVes = new System.Windows.Forms.DataGrid();
			this.label5 = new System.Windows.Forms.Label();
			this.txtMN2 = new System.Windows.Forms.TextBox();
			this.label4 = new System.Windows.Forms.Label();
			this.txtI = new System.Windows.Forms.TextBox();
			this.tcSettings.SuspendLayout();
			this.tabPageNames.SuspendLayout();
			this.groupBox1.SuspendLayout();
			this.tabPageVes.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.dgVes)).BeginInit();
			this.SuspendLayout();
			// 
			// btnOk
			// 
			this.btnOk.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.btnOk.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.btnOk.Location = new System.Drawing.Point(248, 288);
			this.btnOk.Name = "btnOk";
			this.btnOk.TabIndex = 1;
			this.btnOk.Text = "Сохранить";
			// 
			// btnCancel
			// 
			this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.btnCancel.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.btnCancel.Location = new System.Drawing.Point(328, 288);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.TabIndex = 2;
			this.btnCancel.Text = "Выход";
			// 
			// tcSettings
			// 
			this.tcSettings.Controls.AddRange(new System.Windows.Forms.Control[] {
																					 this.tabPageNames,
																					 this.tabPageVes});
			this.tcSettings.Location = new System.Drawing.Point(8, 8);
			this.tcSettings.Name = "tcSettings";
			this.tcSettings.SelectedIndex = 0;
			this.tcSettings.Size = new System.Drawing.Size(400, 272);
			this.tcSettings.TabIndex = 3;
			// 
			// tabPageNames
			// 
			this.tabPageNames.Controls.AddRange(new System.Windows.Forms.Control[] {
																					   this.groupBox1});
			this.tabPageNames.Location = new System.Drawing.Point(4, 22);
			this.tabPageNames.Name = "tabPageNames";
			this.tabPageNames.Size = new System.Drawing.Size(392, 246);
			this.tabPageNames.TabIndex = 0;
			this.tabPageNames.Text = "Наименования";
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.AddRange(new System.Windows.Forms.Control[] {
																					this.txtDevice,
																					this.label8,
																					this.label7,
																					this.txtCalcName,
																					this.label6,
																					this.txtOperName,
																					this.label3,
																					this.txtCurveName,
																					this.label2,
																					this.txtProfName,
																					this.label1,
																					this.txtAreaName});
			this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.groupBox1.Location = new System.Drawing.Point(8, 16);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(376, 216);
			this.groupBox1.TabIndex = 12;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Значения по умолчанию";
			// 
			// txtDevice
			// 
			this.txtDevice.Location = new System.Drawing.Point(16, 184);
			this.txtDevice.Name = "txtDevice";
			this.txtDevice.Size = new System.Drawing.Size(152, 20);
			this.txtDevice.TabIndex = 24;
			this.txtDevice.Text = "";
			// 
			// label8
			// 
			this.label8.Location = new System.Drawing.Point(176, 187);
			this.label8.Name = "label8";
			this.label8.Size = new System.Drawing.Size(82, 16);
			this.label8.TabIndex = 23;
			this.label8.Text = "Аппаратура";
			// 
			// label7
			// 
			this.label7.Location = new System.Drawing.Point(176, 155);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(96, 16);
			this.label7.TabIndex = 21;
			this.label7.Text = "Вычислитель";
			// 
			// txtCalcName
			// 
			this.txtCalcName.Location = new System.Drawing.Point(16, 152);
			this.txtCalcName.Name = "txtCalcName";
			this.txtCalcName.Size = new System.Drawing.Size(152, 20);
			this.txtCalcName.TabIndex = 20;
			this.txtCalcName.Text = "";
			// 
			// label6
			// 
			this.label6.Location = new System.Drawing.Point(176, 123);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(72, 16);
			this.label6.TabIndex = 19;
			this.label6.Text = "Оператор";
			// 
			// txtOperName
			// 
			this.txtOperName.Location = new System.Drawing.Point(16, 120);
			this.txtOperName.Name = "txtOperName";
			this.txtOperName.Size = new System.Drawing.Size(152, 20);
			this.txtOperName.TabIndex = 18;
			this.txtOperName.Text = "";
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(176, 91);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(72, 16);
			this.label3.TabIndex = 17;
			this.label3.Text = "Имя кривой";
			// 
			// txtCurveName
			// 
			this.txtCurveName.Location = new System.Drawing.Point(16, 88);
			this.txtCurveName.Name = "txtCurveName";
			this.txtCurveName.Size = new System.Drawing.Size(152, 20);
			this.txtCurveName.TabIndex = 16;
			this.txtCurveName.Text = "";
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(176, 59);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(80, 16);
			this.label2.TabIndex = 15;
			this.label2.Text = "Имя профиля";
			// 
			// txtProfName
			// 
			this.txtProfName.Location = new System.Drawing.Point(16, 56);
			this.txtProfName.Name = "txtProfName";
			this.txtProfName.Size = new System.Drawing.Size(152, 20);
			this.txtProfName.TabIndex = 14;
			this.txtProfName.Text = "";
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(176, 27);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(72, 16);
			this.label1.TabIndex = 13;
			this.label1.Text = "Имя участка";
			// 
			// txtAreaName
			// 
			this.txtAreaName.Location = new System.Drawing.Point(16, 24);
			this.txtAreaName.Name = "txtAreaName";
			this.txtAreaName.Size = new System.Drawing.Size(152, 20);
			this.txtAreaName.TabIndex = 12;
			this.txtAreaName.Text = "";
			// 
			// tabPageVes
			// 
			this.tabPageVes.Controls.AddRange(new System.Windows.Forms.Control[] {
																					 this.dgVes,
																					 this.label5,
																					 this.txtMN2,
																					 this.label4,
																					 this.txtI});
			this.tabPageVes.Location = new System.Drawing.Point(4, 22);
			this.tabPageVes.Name = "tabPageVes";
			this.tabPageVes.Size = new System.Drawing.Size(392, 246);
			this.tabPageVes.TabIndex = 1;
			this.tabPageVes.Text = "Установка ВЭЗ";
			// 
			// dgVes
			// 
			this.dgVes.CaptionText = "Параметры установки";
			this.dgVes.DataMember = "";
			this.dgVes.HeaderForeColor = System.Drawing.SystemColors.ControlText;
			this.dgVes.Location = new System.Drawing.Point(120, 8);
			this.dgVes.Name = "dgVes";
			this.dgVes.Size = new System.Drawing.Size(264, 232);
			this.dgVes.TabIndex = 14;
			// 
			// label5
			// 
			this.label5.Location = new System.Drawing.Point(57, 37);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(48, 16);
			this.label5.TabIndex = 13;
			this.label5.Text = "MN/2 м";
			// 
			// txtMN2
			// 
			this.txtMN2.Location = new System.Drawing.Point(8, 34);
			this.txtMN2.Name = "txtMN2";
			this.txtMN2.Size = new System.Drawing.Size(48, 20);
			this.txtMN2.TabIndex = 12;
			this.txtMN2.Text = "";
			// 
			// label4
			// 
			this.label4.Location = new System.Drawing.Point(56, 11);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(48, 16);
			this.label4.TabIndex = 11;
			this.label4.Text = "Ток mA";
			// 
			// txtI
			// 
			this.txtI.Location = new System.Drawing.Point(8, 8);
			this.txtI.Name = "txtI";
			this.txtI.Size = new System.Drawing.Size(48, 20);
			this.txtI.TabIndex = 10;
			this.txtI.Text = "";
			// 
			// SettingsForm
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.CancelButton = this.btnCancel;
			this.ClientSize = new System.Drawing.Size(418, 320);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.tcSettings,
																		  this.btnCancel,
																		  this.btnOk});
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Name = "SettingsForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Настройки";
			this.tcSettings.ResumeLayout(false);
			this.tabPageNames.ResumeLayout(false);
			this.groupBox1.ResumeLayout(false);
			this.tabPageVes.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.dgVes)).EndInit();
			this.ResumeLayout(false);

		}
		#endregion

		#region Methods
		public void Bindings(Settings settings)
		{
			dgVes.DataSource = settings.TableAB2;

			txtAreaName.DataBindings.Add("Text", settings, "AreaName");
			txtProfName.DataBindings.Add("Text", settings, "ProfilName");
			txtCurveName.DataBindings.Add("Text", settings, "CurveName");
			txtOperName.DataBindings.Add("Text", settings, "OperatorName");
			txtCalcName.DataBindings.Add("Text", settings, "CalculatorName");
			txtDevice.DataBindings.Add("Text", settings, "DeviceName");
			txtI.DataBindings.Add("Text", settings, "I");
			txtMN2.DataBindings.Add("Text", settings, "MN2");

		}
		#endregion
	
	}
}
