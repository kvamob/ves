using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace VesExplore
{
	/// <summary>
	/// Форма, вызываемая при создании нового профиля ВЭЗ
	/// </summary>
	public class AddProfilForm : System.Windows.Forms.Form
	{
		#region Controls
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Button btnOK;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.TextBox txtProfDescr;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.ComboBox cbProfType;
		private System.Windows.Forms.TextBox txtProfName;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;
		#endregion

		#region Constructor/Dispose
		public AddProfilForm()
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
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(AddProfilForm));
			this.label1 = new System.Windows.Forms.Label();
			this.btnOK = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.txtProfName = new System.Windows.Forms.TextBox();
			this.txtProfDescr = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.cbProfType = new System.Windows.Forms.ComboBox();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(16, 6);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(192, 18);
			this.label1.TabIndex = 0;
			this.label1.Text = "Наименование профиля";
			// 
			// btnOK
			// 
			this.btnOK.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.btnOK.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.btnOK.Location = new System.Drawing.Point(48, 224);
			this.btnOK.Name = "btnOK";
			this.btnOK.TabIndex = 6;
			this.btnOK.Text = "OK";
			// 
			// btnCancel
			// 
			this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.btnCancel.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.btnCancel.Location = new System.Drawing.Point(128, 224);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.TabIndex = 7;
			this.btnCancel.Text = "Cancel";
			// 
			// txtProfName
			// 
			this.txtProfName.Location = new System.Drawing.Point(16, 24);
			this.txtProfName.Name = "txtProfName";
			this.txtProfName.Size = new System.Drawing.Size(192, 20);
			this.txtProfName.TabIndex = 1;
			this.txtProfName.Text = "";
			// 
			// txtProfDescr
			// 
			this.txtProfDescr.Location = new System.Drawing.Point(16, 110);
			this.txtProfDescr.Multiline = true;
			this.txtProfDescr.Name = "txtProfDescr";
			this.txtProfDescr.Size = new System.Drawing.Size(192, 104);
			this.txtProfDescr.TabIndex = 5;
			this.txtProfDescr.Text = "";
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(16, 92);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(192, 13);
			this.label2.TabIndex = 4;
			this.label2.Text = "Описание";
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(16, 48);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(143, 14);
			this.label3.TabIndex = 2;
			this.label3.Text = "Тип профиля";
			// 
			// cbProfType
			// 
			this.cbProfType.Location = new System.Drawing.Point(16, 64);
			this.cbProfType.Name = "cbProfType";
			this.cbProfType.Size = new System.Drawing.Size(192, 21);
			this.cbProfType.TabIndex = 3;
			// 
			// AddProfilForm
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(226, 256);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.cbProfType,
																		  this.label3,
																		  this.label2,
																		  this.txtProfDescr,
																		  this.txtProfName,
																		  this.btnCancel,
																		  this.btnOK,
																		  this.label1});
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Name = "AddProfilForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Добавить профиль";
			this.ResumeLayout(false);

		}
		#endregion

		#region Methods
		/// <summary>
		/// Метод производит привязку элементов управления формы
		/// к полям класса AddProfilSettings
		/// Метод необходимо вызывать после создания экземпляра формы
		/// перед показом формы
		/// </summary>
		/// <param name="defaults"></param>
		public void Bindings(AddProfilSettings settings)
		{
			// Типы профилей отобразим
			cbProfType.DataSource = settings.Types;
			cbProfType.DisplayMember = "Name";
			cbProfType.ValueMember = "Type";
		
			cbProfType.DataBindings.Add("SelectedValue", settings, "Type");
			txtProfDescr.DataBindings.Add("Text", settings, "Description");
			txtProfName.DataBindings.Add("Text", settings, "Name");
		}
		#endregion

	}
}
