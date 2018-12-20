using System;
using System.Drawing;
using System.Collections;
using System.Windows.Forms;
using System.Data;

namespace test
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.DataGrid dataGrid1;
	
		public Form1()
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
		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.button1 = new System.Windows.Forms.Button();
			this.dataGrid1 = new System.Windows.Forms.DataGrid();
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(536, 8);
			this.button1.Text = "button1";
			// 
			// dataGrid1
			// 
			this.dataGrid1.Location = new System.Drawing.Point(16, 16);
			this.dataGrid1.Size = new System.Drawing.Size(456, 248);
			this.dataGrid1.Text = "dataGrid1";
			// 
			// Form1
			// 
			this.Controls.Add(this.dataGrid1);
			this.Controls.Add(this.button1);
			this.Text = "Form1";

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>

		static void Main() 
		{
			Application.Run(new Form1());
		}
	}
}
