''
''  STATUSBARTEST
''  StatusBar test application. 
''

' Use the following Include line if the library has already been copied
' to the compiler's \inc folder.
'#include once "WinFormsX\WinFormsX.bi"

' Use the following include if we are simply testing code via the GitHub ownload.
#include once "..\src\WinFormsX.bi"

' When compiling, be sure to include the file "resource.rc". In WinFBE, this can be done
' via the Compiler Setup / Additional Compiler Settings, or using the #RESOURCE code
' directive as shown below.


'#CONSOLE ON
'#RESOURCE "resource.rc"

declare function Form1_Click( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function Form1_StatusBar_Click( byref sender as wfxStatusBar, byref e as EventArgs ) as LRESULT

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
      .OnClick       = @Form1_Click
   end with

   dim as long idx
   with this.StatusBar
      .Parent = @this
      .SizingGrip = false
      ' Add 3 statusbar panels
      idx = .Panels.Add   
      .Panel(idx).Text = "Panel1"
      .Panel(idx).Width = 120
      idx = .Panels.Add   
      .Panel(idx).Text = "Panel2"
      .Panel(idx).Width = 200
      idx = .Panels.Add   
      .Panel(idx).Text = "Panel3"
      .Panel(idx).AutoSize = StatusBarPanelAutoSize.Spring
      .OnClick = @Form1_StatusBar_Click
   END WITH    
   this.Controls.add(controltype.StatusBar, @this.StatusBar)

END CONSTRUCTOR

''  Define a global variable that will allow access to the form and controls
dim shared Form1 as TFORMMAIN


function Form1_Click( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   ' An area of the form was clicked on. Display the text of the existing panels.
   for i as long = 0 to Form1.StatusBar.Panels.Count - 1
      ? "Index:"; i, Form1.StatusBar.Panel(i).Text
   NEXT
   ?
   ' Change the text on Panel2 to a random number between 1 and 100.
   Form1.StatusBar.Panel(1).Text = "Text " & (Rnd * (100 - 1) + 1)
   
   function = 0
end function


function Form1_StatusBar_Click( byref sender as wfxStatusBar, byref e as EventArgs ) as LRESULT
   ' Display what statusbar panel was clicked.
   ? "Statusbar Panel: " & e.PanelClickIndex & " Clicked"
   function = 0
end function



''
''  Main code for the application. 
''
Application.Run(Form1)

' Pause at the end so we can see the last messages in the console window
sleep

