
declare function frmMain_Load( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function frmMain_FormClosing( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function frmMain_FormClosed( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function frmMain_Resize( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function frmMain_StatusBar_Click( byref sender as wfxStatusBar, byref e as EventArgs ) as LRESULT

''          
''  Define the form
''
type TFORMMAIN extends wfxForm
   private:
   
   public:
      ' Controls
      StatusBar as wfxStatusBar
      
      declare constructor   
END TYPE

''
''  Use the Constructor to define the properties and assign methods
''  to the form and child controls.
''
constructor TFORMMAIN
   
   ' Set the properties of the form 
   with this
      .Size          = 600, 400
      .StartPosition = FormStartPosition.CenterScreen
      .Text          = "CryptoX Password Manager"
      .Name          = "frmMain"
      .OnLoad        = @frmMain_Load
      .OnFormClosing = @frmMain_FormClosing
      .OnFormClosed  = @frmMain_FormClosed
      .OnResize      = @frmMain_Resize
   end with
   ' Add the form to the global application collection
   Application.Forms.Add(ControlType.Form, @this)

   with this.StatusBar
      .Parent = @this
      .SizingGrip = false
      ' Add 3 statusbar panels
      for i as long = 0 to 2
         .Panels.Add
      NEXT
      .Panel(0).Text = "Panel1"
      .Panel(0).Width = 120
      .Panel(1).Text = "Panel2"
      .Panel(1).Width = 200
      .Panel(2).Text = "Panel3"
      .Panel(2).AutoSize = StatusBarPanelAutoSize.Spring
      .OnClick = @frmMain_StatusBar_Click
   END WITH    
   this.Controls.add(controltype.StatusBar, @this.StatusBar)
END CONSTRUCTOR

''  Define a global variable that will allow access to the form and controls
dim shared frmMain as TFORMMAIN

