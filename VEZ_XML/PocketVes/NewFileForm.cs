using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace PocketVes
{
	/// <summary>
	/// Summary description for NewFileForm.
	/// </summary>
	public class NewFileForm : System.Windows.Forms.Form
	{

		#region Controls

		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.TextBox txtAreaName;
		private System.Windows.Forms.TextBox txtAreaDescr;
		private System.Windows.Forms.TextBox txtProfilName;
		private System.Windows.Forms.TextBox txtProfilDescr;
		private System.Windows.Forms.CheckBox cbProfilType;
		private System.Windows.Forms.ToolBar tbNewFile;
		private System.Windows.Forms.Button btnCancel;
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
			this.txtAreaName = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.txtAreaDescr = new System.Windows.Forms.TextBox();
			this.label3 = new System.Windows.Forms.Label();
			this.txtProfilName = new System.Windows.Forms.TextBox();
			this.label5 = new System.Windows.Forms.Label();
			this.txtProfilDescr = new System.Windows.Forms.TextBox();
			this.tbNewFile = new System.Windows.Forms.ToolBar();
			this.cbProfilType = new System.Windows.Forms.CheckBox();
			this.btnCancel = new System.Windows.Forms.Button();
			// 
			// txtAreaName
			// 
			this.txtAreaName.Location = new System.Drawing.Point(8, 8);
			this.txtAreaName.Text = "";
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(112, 10);
			this.label1.Size = new System.Drawing.Size(100, 16);
			this.label1.Text = "Участок";
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(8, 32);
			this.label2.Size = new System.Drawing.Size(224, 16);
			this.label2.Text = "Описание участка";
			// 
			// txtAreaDescr
			// 
			this.txtAreaDescr.Location = new System.Drawing.Point(8, 48);
			this.txtAreaDescr.Multiline = true;
			this.txtAreaDescr.Size = new System.Drawing.Size(224, 56);
			this.txtAreaDescr.Text = "";
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(112, 127);
			this.label3.Size = new System.Drawing.Size(100, 16);
			this.label3.Text = "Профиль";
			// 
			// txtProfilName
			// 
			this.txtProfilName.Location = new System.Drawing.Point(8, 125);
			this.txtProfilName.Text = "";
			// 
			// label5
			// 
			this.label5.Location = new System.Drawing.Point(8, 176);
			this.label5.Size = new System.Drawing.Size(224, 16);
			this.label5.Text = "Описание профиля";
			// 
			// txtProfilDescr
			// 
			this.txtProfilDescr.Location = new System.Drawing.Point(8, 192);
			this.txtProfilDescr.Multiline = true;
			this.txtProfilDescr.Size = new System.Drawing.Size(224, 40);
			this.txtProfilDescr.Text = "";
			// 
			// cbProfilType
			// 
			this.cbProfilType.Checked = true;
			this.cbProfilType.CheckState = System.Windows.Forms.CheckState.Checked;
			this.cbProfilType.Location = new System.Drawing.Point(8, 152);
			this.cbProfilType.Size = new System.Drawing.Size(224, 20);
			this.cbProfilType.Text = "Кривые расположены на профиле";
			// 
			// btnCancel
			// 
			this.btnCancel.Location = new System.Drawing.Point(160, 240);
			this.btnCancel.Text = "Отменить";
			this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
			// 
			// NewFileForm
			// 
			this.Controls.Add(this.btnCancel);
			this.Controls.Add(this.cbProfilType);
			this.Controls.Add(this.label5);
			this.Controls.Add(this.txtProfilDescr);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.txtProfilName);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.txtAreaDescr);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.txtAreaName);
			this.Controls.Add(this.tbNewFile);
			this.Text = "Новый файл";

		}
		#endregion

		#region Methods
		/// <summary>
		/// Метод производит привязку элементов управления формы
		/// к полям класса Settings
		/// Метод необходимо вызывать после создания экземпляра формы
		/// перед показом формы
		/// </summary>
		/// <param name="defaults">Экземпляр класса, к свойствам которого привязываются элементы формы</param>
		public void Bindings(Settings settings)
		{
			txtAreaName.DataBindings.Add("Text",settings,"AreaName");
			txtAreaDescr.DataBindings.Add("Text",settings,"AreaDescr");

			txtProfilName.DataBindings.Add("Text",settings,"ProfilName");
			txtProfilDescr.DataBindings.Add("Text",settings,"ProfilDescr");
			cbProfilType.DataBindings.Add("Checked",settings,"ProfilType");
		}

		#endregion

		#region Event Handlers
		private void btnCancel_Click(object sender, System.EventArgs e)
		{
			this.Close();
		}
		#endregion

	}
}
