using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace VesExplore
{
	/// <summary>
	/// Summary description for AboutForm.
	/// </summary>
	public class AboutForm : System.Windows.Forms.Form
	{
		#region Controls
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.Label labelApp;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label labelOS;
		private System.Windows.Forms.Label labelSP;
		private System.Windows.Forms.PictureBox pictureBox1;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;
		#endregion

		#region Constructor /Dispose
		public AboutForm()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//

//			System.Diagnostics.Process proc = System.Diagnostics.Process.GetCurrentProcess();
//			string appname = proc.MainModule.FileName.ToString();
//			appname = Path.GetFileName(appname);
//			string version = System.Reflection.AssemblyName.GetAssemblyName(appname).Version.ToString();

			labelApp.Text = String.Format("{0} v{1}","VesExplore", MainForm.Version );
//			OperatingSystem os = Environment.OSVersion;
//			Version ver = os.Version;
			OSInfoClass osInfo = new OSInfoClass();
			labelOS.Text = osInfo.OS;
			labelSP.Text = osInfo.ServicePack;
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
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(AboutForm));
			this.button1 = new System.Windows.Forms.Button();
			this.labelApp = new System.Windows.Forms.Label();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.label1 = new System.Windows.Forms.Label();
			this.labelOS = new System.Windows.Forms.Label();
			this.labelSP = new System.Windows.Forms.Label();
			this.pictureBox1 = new System.Windows.Forms.PictureBox();
			this.SuspendLayout();
			// 
			// button1
			// 
			this.button1.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.button1.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.button1.Location = new System.Drawing.Point(115, 200);
			this.button1.Name = "button1";
			this.button1.TabIndex = 0;
			this.button1.Text = "Ok";
			// 
			// labelApp
			// 
			this.labelApp.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(204)));
			this.labelApp.Location = new System.Drawing.Point(120, 16);
			this.labelApp.Name = "labelApp";
			this.labelApp.Size = new System.Drawing.Size(176, 23);
			this.labelApp.TabIndex = 1;
			// 
			// groupBox1
			// 
			this.groupBox1.Location = new System.Drawing.Point(8, 88);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(287, 8);
			this.groupBox1.TabIndex = 2;
			this.groupBox1.TabStop = false;
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(120, 48);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(176, 23);
			this.label1.TabIndex = 3;
			this.label1.Text = "Vladimir A.Korotkov 2002";
			// 
			// labelOS
			// 
			this.labelOS.Location = new System.Drawing.Point(8, 112);
			this.labelOS.Name = "labelOS";
			this.labelOS.Size = new System.Drawing.Size(288, 23);
			this.labelOS.TabIndex = 4;
			this.labelOS.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// labelSP
			// 
			this.labelSP.Location = new System.Drawing.Point(8, 152);
			this.labelSP.Name = "labelSP";
			this.labelSP.Size = new System.Drawing.Size(288, 23);
			this.labelSP.TabIndex = 5;
			// 
			// pictureBox1
			// 
			this.pictureBox1.Image = ((System.Drawing.Bitmap)(resources.GetObject("pictureBox1.Image")));
			this.pictureBox1.Location = new System.Drawing.Point(32, 24);
			this.pictureBox1.Name = "pictureBox1";
			this.pictureBox1.Size = new System.Drawing.Size(40, 40);
			this.pictureBox1.TabIndex = 6;
			this.pictureBox1.TabStop = false;
			// 
			// AboutForm
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(304, 232);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.pictureBox1,
																		  this.labelSP,
																		  this.labelOS,
																		  this.label1,
																		  this.groupBox1,
																		  this.labelApp,
																		  this.button1});
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Name = "AboutForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "About";
			this.ResumeLayout(false);

		}
		#endregion

	}
}
