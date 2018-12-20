using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace PocketVes
{
	/// <summary>
	/// Summary description for GraphForm.
	/// </summary>
	public class GraphForm : System.Windows.Forms.Form
	{
		public GraphForm(VesCurve vesCurve)
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			_vesCurve = vesCurve;
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
			// 
			// GraphForm
			// 
			this.Text = "Graph";
			this.Paint += new System.Windows.Forms.PaintEventHandler(this.GraphForm_Paint);

		}
		#endregion

		private VesCurve _vesCurve;

		private void GraphForm_Paint(object sender, System.Windows.Forms.PaintEventArgs e)
		{
			if (_vesCurve != null)
			{
				// Создадим контекст устройства
				Graphics  clientDC = e.Graphics;
				_vesCurve.Draw(clientDC, this.Width, this.Height);
			}
		}

	}
}
