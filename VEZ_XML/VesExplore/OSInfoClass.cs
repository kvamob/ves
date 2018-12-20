using System;
using System.Diagnostics;

namespace VesExplore
{
	/// <summary>
	/// Enumeration defining different Operating Systems.
	/// </summary>
	public enum SystemOS 
	{
		WinErr = 0x0000000,		// Error
		Win95  = 0x0000001,		// Windows 95
		Win98  = 0x0000002,		// Windows 98
		WinME  = 0x0000003,		// Windows ME
		WinNT  = 0x0000004,		// Windows NT
		Win2K  = 0x0000005,		// Windows 2000
		WinXP  = 0x0000006,		// Windows XP (Whistler for now)
		Win32s = 0x0000007		// Windows 32s (yeah right :-))
	}

	/// <summary>
	///		This class can be used to extract information about Operating
	///		 System Environment installed on the machine.
	/// </summary>
	public class OSInfoClass
	{
		#region Constructor/Dispose
		public OSInfoClass()
		{
			InitInfo ();
		}

		#endregion

		#region Fields
		/// // Major Version Of Operating System
		protected int m_nMajorVer;
		/// Minor Version Of Operating System
		protected int m_nMinorVersion;
		/// Operating System Revision Number
		protected int m_nRevision;
		/// Operating System Build Number
		protected int m_nBuildNumber;
		/// Service Pack Installed For Operating System
		protected string m_strServicePack;
		/// String Representation For Operating System
		protected string m_strOS;
		/// Enum for Operating System type
		SystemOS m_osID;
		#endregion

		#region Properties
		/// Property gets the service pack currently installed in system.
		public string ServicePack
		{
			get
			{
				return this.m_strServicePack;
			}
		}

		/// Property tells if OS is Windows NT or not
		public bool IsWinNT
		{
			get
			{
				return m_osID == SystemOS.WinNT;
			}
		}

		/// Property indicates if OS is Windows 2000 family or not
		public bool IsWin2K
		{
			get
			{
				return m_osID == SystemOS.Win2K;
			}
		}

		/// Property indicates if OS is Win95 or not
		public bool IsWin95
		{
			get
			{
				return m_osID == SystemOS.Win95;
			}
		}

		/// Property indicates if OS is Win98 or not
		public bool IsWin98
		{
			get
			{
				return m_osID == SystemOS.Win98;
			}
		}

		/// Property indicates if OS is Windows Millenium or not
		public bool IsWinME
		{
			get
			{
				return m_osID == SystemOS.WinME;
			}
		}

		/// Property indicates if OS is Windows XP or not
		public bool IsWinXP
		{
			get
			{
				return m_osID == SystemOS.WinXP;
			}
		}

		/// Property returns string representation of operating system version

		public string OS
		{
			get
			{
				return this.m_strOS;
			}
		}

		
		#endregion

		#region Methods
		/// <summary>
		/// This method can be used to extract version information.
		/// </summary>
		/// <param name="nMajorVer"> Major Version Of Operating System</param>
		/// <param name="nMinorVer"> Minor Version Of Operating System</param>
		/// <param name="nRevision"> Revision Number Of Operating System</param>
		/// <param name="nBuildNumber"> Build Number Of Operating System</param>
		public bool GetVersionInfo (ref int nMajorVer, ref int nMinorVer, ref int nRevision, ref int nBuildNumber)
		{
			nMajorVer = this.m_nMajorVer;
			nMinorVer = this.m_nMinorVersion;
			nRevision = this.m_nRevision;
			nBuildNumber = this.m_nBuildNumber;

			return true;
		}

		/// <summary>
		/// This private method gets called by constructor. It extracts all the required
		/// information using Environment class and stuffs into class variables for
		/// later use.
		/// </summary>
		protected void InitInfo ()
		{
			try
			{
				m_osID = SystemOS.WinErr;

				// Get the Operating System From Environment Class.
				OperatingSystem os = Environment.OSVersion;

				// Get the version information.
				Version vs = os.Version;
				this.m_nMajorVer = vs.Major;
				this.m_nMinorVersion = vs.Minor;
				this.m_nRevision = vs.Revision;
				this.m_nBuildNumber = vs.Build;

				// Get the service pack information.
//				this.m_strServicePack = os.CSD;
				this.m_strServicePack = "";

				if (os.Platform == PlatformID.Win32NT && vs.Major == 5)
				{
					if (vs.Minor > 0)
					{
						this.m_osID = SystemOS.WinXP;
					}
					else
					{
						this.m_osID = SystemOS.Win2K;
					}
				}
				else if (os.Platform == PlatformID.Win32NT && vs.Major <= 4)
				{
					this.m_osID = SystemOS.WinNT;
				}
				else if (os.Platform == PlatformID.Win32Windows)
				{
					if (vs.Major >= 4 && vs.Minor > 0)
					{
						if (vs.Minor < 90)
						{
							this.m_osID = SystemOS.Win98;
						}
						else
						{
							this.m_osID = SystemOS.WinME;
						}
					}
					else
					{
						this.m_osID = SystemOS.Win95;
					}
				}
				else if (os.Platform == PlatformID.Win32S)
				{
					this.m_osID = SystemOS.Win32s;
				}

				// Depending on the Operating system type, set the string value.
				
				//
				// TODO: Use resource manager to use localized string.
				//
				switch (this.m_osID)
				{
					case SystemOS.Win2K:
						this.m_strOS = "Windows 2000";
						break;
					case SystemOS.Win95:
						this.m_strOS = "Windows 95";
						break;
					case SystemOS.Win98:
						this.m_strOS = "Windows 98";
						break;
					case SystemOS.WinME:
						this.m_strOS = "Windows ME";
						break;
					case SystemOS.WinNT:
						this.m_strOS = "Windows NT";
						break;
					case SystemOS.WinXP:
						this.m_strOS = "Windows XP";
						break;
					case SystemOS.Win32s:
						this.m_strOS = "Windows 32s";
						break;
					default:
						this.m_strOS = "Unknown";
						break;
				}
			}
			catch (Exception ex)
			{
				Trace.WriteLine (ex.Message);
			}
		}

		#endregion
	}
}
