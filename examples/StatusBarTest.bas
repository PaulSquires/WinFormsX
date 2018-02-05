''
''  STATUSBARTEST
''  StatusBar test application. 
''

' Use the following Include line if the library has already been copied
' to the compiler's \inc folder.
'#include once "WinFormsX\WinFormsX.bi"

' Use the following include if we are simply testing code via the GitHub ownload.
#include once "..\src\WinFormsX.bi"

' When compiling, be sure to incclude the file "resource.rc". In WinFBE, this can be done
' via the Compiler Setup / Additional Compiler Settings


'#CONSOLE ON

'declare function Form1_Click( byref sender as wfxForm, byref e as EventArgs ) as LRESULT

''          
''  Define the form and StatusBar
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
   ' Add the form to the global application collection
   Application.Forms.Add(ControlType.Form, @this)
   
   ' Set the properties of the form 
   with this
      .Size          = 600, 400
      .StartPosition = FormStartPosition.CenterScreen
      .Text          = "Form1"
      .Name          = "Form1"
   end with

   with this.StatusBar
      .Parent = @this
      .SizingGrip = false
      ' Add 3 statusbar panels
      for i as long = 0 to 2
         .Panels.Add
      NEXT
      .Panels(0).Text = "Panel1"
      .Panels(0).Width = 120
      .Panels(1).Text = "Panel2"
      .Panels(1).Width = 200
      .Panels(2).Text = "Panel3"
      .Panels(2).AutoSize = StatusBarPanelAutoSize.Spring
   END WITH
   
   this.Controls.add(controltype.StatusBar, @this.StatusBar)

END CONSTRUCTOR

''  Define a global variable that will allow access to the form and controls
dim shared Form1 as TFORMMAIN


'function StatusBar_Click( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
'   function = 0
'end function



''
''  Main code for the application. 
''
Application.Run(Form1)

' Pause at the end so we can see the last messages in the console window
sleep

