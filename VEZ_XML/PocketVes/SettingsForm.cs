using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;

namespace PocketVes
{
	/// <summary>
	/// Summary description for SettingsForm.
	/// </summary>
	public class SettingsForm : System.Windows.Forms.Form
	{
		#region Controls
		private System.Windows.Forms.TabControl tabControl1;
		private System.Windows.Forms.TabPage tabPageNames;
		private System.Windows.Forms.TabPage tabPageVES;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.TextBox txtDeviceName;
		private System.Windows.Forms.TextBox txtCalcName;
		private System.Windows.Forms.TextBox txtOperName;
		private System.Windows.Forms.TextBox txtCurveName;
		private System.Windows.Forms.TextBox txtProfilName;
		private System.Windows.Forms.TextBox txtAreaName;
		private System.Windows.Forms.DataGrid dgAB2;
		private System.Windows.Forms.TextBox txtI;
		private System.Windows.Forms.ToolBar tbSettings;
		private System.Windows.Forms.Label label10;
		private System.Windows.Forms.TextBox txtAB2;
		private System.Windows.Forms.Label label11;
		private System.Windows.Forms.TextBox txtMN2;
		private System.Windows.Forms.Button btnDelete;
		private System.Windows.Forms.Button btnCnanhge;
		private System.Windows.Forms.Button btnAdd;
		private System.Windows.Forms.Label label9;
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
			this.tabControl1 = new System.Windows.Forms.TabControl();
			this.tabPageNames = new System.Windows.Forms.TabPage();
			this.label7 = new System.Windows.Forms.Label();
			this.txtDeviceName = new System.Windows.Forms.TextBox();
			this.label6 = new System.Windows.Forms.Label();
			this.txtCalcName = new System.Windows.Forms.TextBox();
			this.label5 = new System.Windows.Forms.Label();
			this.txtOperName = new System.Windows.Forms.TextBox();
			this.label4 = new System.Windows.Forms.Label();
			this.txtCurveName = new System.Windows.Forms.TextBox();
			this.label3 = new System.Windows.Forms.Label();
			this.txtProfilName = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.txtAreaName = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.tabPageVES = new System.Windows.Forms.TabPage();
			this.btnAdd = new System.Windows.Forms.Button();
			this.btnDelete = new System.Windows.Forms.Button();
			this.btnCnanhge = new System.Windows.Forms.Button();
			this.label11 = new System.Windows.Forms.Label();
			this.txtMN2 = new System.Windows.Forms.TextBox();
			this.label10 = new System.Windows.Forms.Label();
			this.txtAB2 = new System.Windows.Forms.TextBox();
			this.dgAB2 = new System.Windows.Forms.DataGrid();
			this.label9 = new System.Windows.Forms.Label();
			this.label8 = new System.Windows.Forms.Label();
			this.txtI = new System.Windows.Forms.TextBox();
			this.tbSettings = new System.Windows.Forms.ToolBar();
			// 
			// tabControl1
			// 
			this.tabControl1.Controls.Add(this.tabPageNames);
			this.tabControl1.Controls.Add(this.tabPageVES);
			this.tabControl1.SelectedIndex = 0;
			this.tabControl1.Size = new System.Drawing.Size(240, 272);
			// 
			// tabPageNames
			// 
			this.tabPageNames.Controls.Add(this.label7);
			this.tabPageNames.Controls.Add(this.txtDeviceName);
			this.tabPageNames.Controls.Add(this.label6);
			this.tabPageNames.Controls.Add(this.txtCalcName);
			this.tabPageNames.Controls.Add(this.label5);
			this.tabPageNames.Controls.Add(this.txtOperName);
			this.tabPageNames.Controls.Add(this.label4);
			this.tabPageNames.Controls.Add(this.txtCurveName);
			this.tabPageNames.Controls.Add(this.label3);
			this.tabPageNames.Controls.Add(this.txtProfilName);
			this.tabPageNames.Controls.Add(this.label2);
			this.tabPageNames.Controls.Add(this.txtAreaName);
			this.tabPageNames.Controls.Add(this.label1);
			this.tabPageNames.Location = new System.Drawing.Point(4, 4);
			this.tabPageNames.Size = new System.Drawing.Size(232, 246);
			this.tabPageNames.Text = "Наименования";
			// 
			// label7
			// 
			this.label7.Location = new System.Drawing.Point(112, 155);
			this.label7.Size = new System.Drawing.Size(100, 16);
			this.label7.Text = "Аппаратура";
			// 
			// txtDeviceName
			// 
			this.txtDeviceName.Location = new System.Drawing.Point(8, 152);
			this.txtDeviceName.Text = "";
			// 
			// label6
			// 
			this.label6.Location = new System.Drawing.Point(112, 130);
			this.label6.Size = new System.Drawing.Size(100, 16);
			this.label6.Text = "Вычислитель";
			// 
			// txtCalcName
			// 
			this.txtCalcName.Location = new System.Drawing.Point(8, 128);
			this.txtCalcName.Text = "";
			// 
			// label5
			// 
			this.label5.Location = new System.Drawing.Point(112, 106);
			this.label5.Size = new System.Drawing.Size(100, 16);
			this.label5.Text = "Оператор";
			// 
			// txtOperName
			// 
			this.txtOperName.Location = new System.Drawing.Point(8, 104);
			this.txtOperName.Text = "";
			// 
			// label4
			// 
			this.label4.Location = new System.Drawing.Point(112, 82);
			this.label4.Size = new System.Drawing.Size(100, 16);
			this.label4.Text = "Имя кривой";
			// 
			// txtCurveName
			// 
			this.txtCurveName.Location = new System.Drawing.Point(8, 80);
			this.txtCurveName.Text = "";
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(112, 58);
			this.label3.Size = new System.Drawing.Size(100, 16);
			this.label3.Text = "Профиль";
			// 
			// txtProfilName
			// 
			this.txtProfilName.Location = new System.Drawing.Point(8, 56);
			this.txtProfilName.Text = "";
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(112, 34);
			this.label2.Size = new System.Drawing.Size(100, 16);
			this.label2.Text = "Участок";
			// 
			// txtAreaName
			// 
			this.txtAreaName.Location = new System.Drawing.Point(8, 32);
			this.txtAreaName.Text = "";
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(8, 8);
			this.label1.Size = new System.Drawing.Size(184, 16);
			this.label1.Text = "Значения по умолчанию";
			// 
			// tabPageVES
			// 
			this.tabPageVES.Controls.Add(this.btnAdd);
			this.tabPageVES.Controls.Add(this.btnDelete);
			this.tabPageVES.Controls.Add(this.btnCnanhge);
			this.tabPageVES.Controls.Add(this.label11);
			this.tabPageVES.Controls.Add(this.txtMN2);
			this.tabPageVES.Controls.Add(this.label10);
			this.tabPageVES.Controls.Add(this.txtAB2);
			this.tabPageVES.Controls.Add(this.dgAB2);
			this.tabPageVES.Controls.Add(this.label9);
			this.tabPageVES.Controls.Add(this.label8);
			this.tabPageVES.Controls.Add(this.txtI);
			this.tabPageVES.Location = new System.Drawing.Point(4, 4);
			this.tabPageVES.Size = new System.Drawing.Size(232, 246);
			this.tabPageVES.Text = "Установка ВЭЗ";
			// 
			// btnAdd
			// 
			this.btnAdd.Location = new System.Drawing.Point(156, 163);
			this.btnAdd.Text = "Добавить";
			this.btnAdd.Click += new System.EventHandler(this.btnAdd_Click);
			// 
			// btnDelete
			// 
			this.btnDelete.Location = new System.Drawing.Point(156, 208);
			this.btnDelete.Text = "Удалить";
			this.btnDelete.Click += new System.EventHandler(this.btnDelete_Click);
			// 
			// btnCnanhge
			// 
			this.btnCnanhge.Location = new System.Drawing.Point(156, 139);
			this.btnCnanhge.Text = "Изменить";
			this.btnCnanhge.Click += new System.EventHandler(this.btnCnanhge_Click);
			// 
			// label11
			// 
			this.label11.Location = new System.Drawing.Point(157, 96);
			this.label11.Size = new System.Drawing.Size(32, 14);
			this.label11.Text = "MN/2";
			// 
			// txtMN2
			// 
			this.txtMN2.Location = new System.Drawing.Point(156, 112);
			this.txtMN2.Size = new System.Drawing.Size(72, 20);
			this.txtMN2.Text = "";
			// 
			// label10
			// 
			this.label10.Location = new System.Drawing.Point(156, 56);
			this.label10.Size = new System.Drawing.Size(29, 16);
			this.label10.Text = "AB/2";
			// 
			// txtAB2
			// 
			this.txtAB2.Location = new System.Drawing.Point(156, 72);
			this.txtAB2.Size = new System.Drawing.Size(72, 20);
			this.txtAB2.Text = "";
			// 
			// dgAB2
			// 
			this.dgAB2.Location = new System.Drawing.Point(8, 24);
			this.dgAB2.Size = new System.Drawing.Size(136, 216);
			this.dgAB2.Text = "Параметры установки";
			this.dgAB2.Click += new System.EventHandler(this.dgAB2_Click);
			// 
			// label9
			// 
			this.label9.Location = new System.Drawing.Point(8, 8);
			this.label9.Size = new System.Drawing.Size(128, 16);
			this.label9.Text = "Параметры установки";
			// 
			// label8
			// 
			this.label8.Location = new System.Drawing.Point(156, 8);
			this.label8.Size = new System.Drawing.Size(43, 16);
			this.label8.Text = "Ток mA";
			// 
			// txtI
			// 
			this.txtI.Location = new System.Drawing.Point(156, 24);
			this.txtI.Size = new System.Drawing.Size(72, 20);
			this.txtI.Text = "";
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			// 
			// SettingsForm
			// 
			this.Controls.Add(this.tabControl1);
			this.Controls.Add(this.tbSettings);
			this.Text = "Настройки";

		}
		#endregion

		#region Fields
		#endregion

		#region Methods
		/// <summary>
		/// Метод производит привязку элементов управления формы
		/// к полям класса Settings
		/// Метод необходимо вызывать после создания экземпляра формы
		/// перед показом формы
		/// </summary>
		/// <param name="settings">Экземпляр класса, к свойствам которого привязываются элементы формы</param>
		public void Bindings(Settings settings)
		{
			dgAB2.DataSource = settings.TableAB2;

			txtAreaName.DataBindings.Add("Text", settings, "AreaName");
			txtProfilName.DataBindings.Add("Text", settings, "ProfilName");
			txtCurveName.DataBindings.Add("Text", settings, "CurveName");
			txtOperName.DataBindings.Add("Text", settings, "OperatorName");
			txtCalcName.DataBindings.Add("Text", settings, "CalculatorName");
			txtDeviceName.DataBindings.Add("Text", settings, "DeviceName");
			txtI.DataBindings.Add("Text", settings, "I");
		}
		#endregion

		#region EventHandlers

		private void dgAB2_Click(object sender, System.EventArgs e)
		{
			DataTable dt = (DataTable) dgAB2.DataSource;
			if (dt != null)
			{
				int i = dgAB2.CurrentCell.RowNumber;
				txtAB2.Text = dt.Rows[i]["AB2"].ToString();
				txtMN2.Text = dt.Rows[i]["MN2"].ToString();
			}

		}

		private void btnCnanhge_Click(object sender, System.EventArgs e)
		{
			DataTable dt = (DataTable) dgAB2.DataSource;
			if ( (dt != null) && (txtAB2.Text) != "" )
			{
				// Индекс выбранной строки
				int i = dgAB2.CurrentCell.RowNumber;
				// Изменим значение полей
				float val = Convert.ToSingle(txtAB2.Text);
				dt.Rows[i]["AB2"] = val;
				val = Convert.ToSingle(txtMN2.Text);
				dt.Rows[i]["MN2"] = val;
			}

		}

		private void btnDelete_Click(object sender, System.EventArgs e)
		{
			DataTable dt = (DataTable) dgAB2.DataSource;
			if ( dt != null )
			{
				if (MessageBox.Show("Удалить строку?","",MessageBoxButtons.YesNo,
					MessageBoxIcon.Question, 
					MessageBoxDefaultButton.Button1) == DialogResult.Yes)
				{
					// Индекс выбранной строки
					int i = dgAB2.CurrentCell.RowNumber;
					// Удалим строку
					dt.Rows[i].Delete();
				}
			}
		}

		private void btnAdd_Click(object sender, System.EventArgs e)
		{
			DataTable dt = (DataTable) dgAB2.DataSource;
			if ( dt != null )
			{
				// Индекс выбранной строки
				int i = dgAB2.CurrentCell.RowNumber;
				// Новая строка
				DataRow row = dt.NewRow();
				float val = Convert.ToSingle(txtAB2.Text);
				row["AB2"] = val;
				val = Convert.ToSingle(txtMN2.Text);
				row["MN2"] = val;
				// Вставим новую строку
				dt.Rows.InsertAt(row,i+1);
				dt.AcceptChanges();
			}
		}

		#endregion
	}
}
