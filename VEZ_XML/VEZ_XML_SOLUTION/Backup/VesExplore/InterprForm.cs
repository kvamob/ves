using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace VesExplore
{
	/// <summary>
	/// Summary description for InterprForm.
	/// </summary>
	public class InterprForm : System.Windows.Forms.Form
	{
		private System.Windows.Forms.NumericUpDown numericUpDown1;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.TextBox txtR1;
		private System.Windows.Forms.TextBox txtR2;
		private System.Windows.Forms.TextBox txtR3;
		private System.Windows.Forms.TextBox txtR4;
		private System.Windows.Forms.TextBox txtR5;
		private System.Windows.Forms.TextBox txtR6;
		private System.Windows.Forms.TextBox txtH1;
		private System.Windows.Forms.TextBox txtH2;
		private System.Windows.Forms.TextBox txtH3;
		private System.Windows.Forms.TextBox txtH4;
		private System.Windows.Forms.TextBox txtH5;

		private ArrayList arrR = new ArrayList();
		private ArrayList arrH = new ArrayList();
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public InterprForm()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			arrR.Add(txtR1);
			arrR.Add(txtR2);
			arrR.Add(txtR3);
			arrR.Add(txtR4);
			arrR.Add(txtR5);
			arrR.Add(txtR6);

			arrH.Add(txtH1);
			arrH.Add(txtH2);
			arrH.Add(txtH3);
			arrH.Add(txtH4);
			arrH.Add(txtH5);

			TextBox txtBox;
			for ( int i = 0; i < arrR.Count; i ++)
			{
				txtBox = (TextBox) arrR[i];
				if ( i > 2 )
					txtBox.Visible = false;
				else
					txtBox.Visible = true;

			}

			for ( int i = 0; i < arrH.Count; i ++)
			{
				txtBox = (TextBox) arrH[i];
				if ( i > 1 )
					txtBox.Visible = false;
				else
					txtBox.Visible = true;

			}

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

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.txtR1 = new System.Windows.Forms.TextBox();
			this.txtR2 = new System.Windows.Forms.TextBox();
			this.txtR3 = new System.Windows.Forms.TextBox();
			this.txtR4 = new System.Windows.Forms.TextBox();
			this.txtR5 = new System.Windows.Forms.TextBox();
			this.txtR6 = new System.Windows.Forms.TextBox();
			this.txtH1 = new System.Windows.Forms.TextBox();
			this.txtH2 = new System.Windows.Forms.TextBox();
			this.txtH3 = new System.Windows.Forms.TextBox();
			this.txtH4 = new System.Windows.Forms.TextBox();
			this.txtH5 = new System.Windows.Forms.TextBox();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
			this.groupBox1.SuspendLayout();
			this.SuspendLayout();
			// 
			// numericUpDown1
			// 
			this.numericUpDown1.Location = new System.Drawing.Point(8, 8);
			this.numericUpDown1.Maximum = new System.Decimal(new int[] {
																		   6,
																		   0,
																		   0,
																		   0});
			this.numericUpDown1.Minimum = new System.Decimal(new int[] {
																		   1,
																		   0,
																		   0,
																		   0});
			this.numericUpDown1.Name = "numericUpDown1";
			this.numericUpDown1.Size = new System.Drawing.Size(48, 20);
			this.numericUpDown1.TabIndex = 0;
			this.numericUpDown1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.numericUpDown1.Value = new System.Decimal(new int[] {
																		 1,
																		 0,
																		 0,
																		 0});
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.AddRange(new System.Windows.Forms.Control[] {
																					this.txtH5,
																					this.txtH4,
																					this.txtH3,
																					this.txtH2,
																					this.txtH1,
																					this.txtR6,
																					this.txtR5,
																					this.txtR4,
																					this.txtR3,
																					this.txtR2,
																					this.txtR1});
			this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.groupBox1.Location = new System.Drawing.Point(8, 40);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(224, 176);
			this.groupBox1.TabIndex = 2;
			this.groupBox1.TabStop = false;
			// 
			// txtR1
			// 
			this.txtR1.Location = new System.Drawing.Point(24, 24);
			this.txtR1.Name = "txtR1";
			this.txtR1.Size = new System.Drawing.Size(72, 20);
			this.txtR1.TabIndex = 2;
			this.txtR1.Text = "";
			// 
			// txtR2
			// 
			this.txtR2.Location = new System.Drawing.Point(24, 48);
			this.txtR2.Name = "txtR2";
			this.txtR2.Size = new System.Drawing.Size(72, 20);
			this.txtR2.TabIndex = 3;
			this.txtR2.Text = "";
			// 
			// txtR3
			// 
			this.txtR3.Location = new System.Drawing.Point(24, 72);
			this.txtR3.Name = "txtR3";
			this.txtR3.Size = new System.Drawing.Size(72, 20);
			this.txtR3.TabIndex = 4;
			this.txtR3.Text = "";
			// 
			// txtR4
			// 
			this.txtR4.Location = new System.Drawing.Point(24, 96);
			this.txtR4.Name = "txtR4";
			this.txtR4.Size = new System.Drawing.Size(72, 20);
			this.txtR4.TabIndex = 5;
			this.txtR4.Text = "";
			// 
			// txtR5
			// 
			this.txtR5.Location = new System.Drawing.Point(24, 120);
			this.txtR5.Name = "txtR5";
			this.txtR5.Size = new System.Drawing.Size(72, 20);
			this.txtR5.TabIndex = 6;
			this.txtR5.Text = "";
			// 
			// txtR6
			// 
			this.txtR6.Location = new System.Drawing.Point(24, 144);
			this.txtR6.Name = "txtR6";
			this.txtR6.Size = new System.Drawing.Size(72, 20);
			this.txtR6.TabIndex = 7;
			this.txtR6.Text = "";
			// 
			// txtH1
			// 
			this.txtH1.Location = new System.Drawing.Point(120, 24);
			this.txtH1.Name = "txtH1";
			this.txtH1.Size = new System.Drawing.Size(72, 20);
			this.txtH1.TabIndex = 8;
			this.txtH1.Text = "";
			// 
			// txtH2
			// 
			this.txtH2.Location = new System.Drawing.Point(120, 48);
			this.txtH2.Name = "txtH2";
			this.txtH2.Size = new System.Drawing.Size(72, 20);
			this.txtH2.TabIndex = 9;
			this.txtH2.Text = "";
			// 
			// txtH3
			// 
			this.txtH3.Location = new System.Drawing.Point(120, 72);
			this.txtH3.Name = "txtH3";
			this.txtH3.Size = new System.Drawing.Size(72, 20);
			this.txtH3.TabIndex = 10;
			this.txtH3.Text = "";
			// 
			// txtH4
			// 
			this.txtH4.Location = new System.Drawing.Point(120, 96);
			this.txtH4.Name = "txtH4";
			this.txtH4.Size = new System.Drawing.Size(72, 20);
			this.txtH4.TabIndex = 11;
			this.txtH4.Text = "";
			// 
			// txtH5
			// 
			this.txtH5.Location = new System.Drawing.Point(120, 120);
			this.txtH5.Name = "txtH5";
			this.txtH5.Size = new System.Drawing.Size(72, 20);
			this.txtH5.TabIndex = 12;
			this.txtH5.Text = "";
			// 
			// InterprForm
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(440, 310);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.groupBox1,
																		  this.numericUpDown1});
			this.Name = "InterprForm";
			this.Text = "InterprForm";
			((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
			this.groupBox1.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion
	}
}
