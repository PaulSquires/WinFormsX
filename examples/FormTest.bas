''
''  FORMTEST
''  Form test application. 
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

declare function Form1_AllEvents( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function Form1_MouseMove( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function Form1_MouseDown( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function Form1_MouseUp( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function Form1_MouseDoubleClick( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function Form1_Click( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function Form1_Load( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function Form1_Activated( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function Form1_Deactivate( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function Form1_Shown( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function Form1_FormClosing( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function Form1_FormClosed( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function Form1_Move( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function Form1_Resize( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function Form1_KeyDown( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function Form1_KeyPress( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function Form1_KeyUp( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
    
''          
''  Define the form (no child controls for this test)
''
type TFORMMAIN extends wfxForm
   private:
   
   public:
      ' Controls
      ' Normally we would define our child controls. 
      ' For example:
      '
      ' Label1 as wfxLabel
      ' StatusBar as wfxStatusBar
      
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
      .BackColor     = Colors.SystemButtonFace
      .OnAllEvents   = @Form1_AllEvents
      .OnClick       = @Form1_Click
      .OnResize      = @Form1_Resize
      .OnMouseMove   = @Form1_MouseMove
      .OnMouseDown   = @Form1_MouseDown
      .OnMouseUp     = @Form1_MouseUp
      .OnMouseDoubleClick = @Form1_MouseDoubleClick
      .OnLoad        = @Form1_Load
      .OnActivated   = @Form1_Activated
      .OnDeactivate  = @Form1_Deactivate
      .OnShown       = @Form1_Shown
      .OnFormClosing = @Form1_FormClosing
      .OnFormClosed  = @Form1_FormClosed
      .OnMove        = @Form1_Move
      .OnKeyDown     = @Form1_KeyDown
      .OnKeyUp       = @Form1_KeyUp
      .OnKeyPress    = @Form1_KeyPress
   end with
END CONSTRUCTOR

''  Define a global variable that will allow access to the form and controls
dim shared Form1 as TFORMMAIN


''
''  Define the various methods that the application will respond to.
''  User code will go into these methods in order to make the application work.
''
function Form1_AllEvents( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   ' All events flow through here so basically you can capture and respond to
   ' any Windows message through this handler. If you handle the message here then
   ' you simply set e.Handled = True before returning.
   function = 0
end function

function Form1_Load( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   ? "Form Load"
   function = 0
end function

function Form1_Activated( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   ? "Form Activated"
   function = 0
end function

function Form1_Deactivate( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   ? "Form Deactivate"
   function = 0
end function

function Form1_Shown( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   ? "Form Shown"
   function = 0
end function

function Form1_FormClosing( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   ? "Form FormClosing"
   function = 0
end function

function Form1_FormClosed( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   ? "Form FormClosed"
   function = 0
end function

function Form1_Move( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   dim pt as wfxPoint = sender.Location
   ? "Form Move (x,y) = (" & pt.x & ", " & pt.y & ")"
   function = 0
end function

function Form1_MouseMove( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   sender.Text = "Form MouseMove (x,y) = (" & e.x & "," & e.y & ")"
   function = 0
end function

function Form1_MouseDown( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   sender.Text = "Form MouseDown (x,y) = (" & e.x & "," & e.y & ")"
   ? "MouseDown"
   ? "Ctrl: "; e.Ctrl
   ? "Shift: "; e.Shift
   ? "Alt: "; e.Alt
   ? "LButton: "; e.LButton
   ? "MButton: "; e.MButton
   ? "RButton: "; e.RButton
   ?
   function = 0
end function

function Form1_MouseUp( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   sender.Text = "Form MouseUp (x,y) = (" & e.x & "," & e.y & ")"
   ? "MouseUp"
   ? "Ctrl: "; e.Ctrl
   ? "Shift: "; e.Shift
   ? "Alt: "; e.Alt
   ? "LButton: "; e.LButton
   ? "MButton: "; e.MButton
   ? "RButton: "; e.RButton
   ?
   function = 0
end function

function Form1_MouseDoubleClick( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   sender.Text = "Form MouseDoubleClick (x,y) = (" & e.x & "," & e.y & ")"
   ? "MouseDoubleClick"
   ? "Ctrl: "; e.Ctrl
   ? "Shift: "; e.Shift
   ? "Alt: "; e.Alt
   ? "LButton: "; e.LButton
   ? "MButton: "; e.MButton
   ? "RButton: "; e.RButton
   ?
   function = 0
end function

function Form1_Resize( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   dim size as wfxSize = sender.Size
   sender.Text = "Form Resize (x,y) = (" & size.Width & " x " & size.Height & ")"
   function = 0
end function

function Form1_KeyDown( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   sender.Text = "Form KeyDown " & e.KeyChar
   function = 0
end function

function Form1_KeyUp( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   sender.Text = "Form KeyUp " & e.KeyChar
   function = 0
end function

function Form1_KeyPress( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   sender.Text = "Form KeyPress " & e.KeyChar
   function = 0
end function

function Form1_Click( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   ' Print the properties of the form to the console window
   ' In addition to using the "sender" object we could also have referred to the 
   ' form properties through use of the global shared Form1 variable.
   dim pt as wfxPoint = sender.Location
   dim size as wfxSize = sender.Size
   dim clientsize as wfxSize = sender.ClientSize
   
   ? "Name: "; sender.Name
   ? "Text: "; sender.Text
   ? "Parent: "; sender.Parent
   ? "BackColor: "; sender.BackColor
   ? "Enabled: "; sender.Enabled
   ? "Visible: "; sender.Visible
   ? "Left: "; sender.Left
   ? "Top: "; sender.Top
   ? "Width: "; sender.Width
   ? "Height: "; sender.Height
   ? "Size: "; size.Width; " x "; size.Height
   ? "ClientSize: "; clientsize.Width; " x "; clientsize.Height
   ? "Location: "; pt.x; ", "; pt.y
   ? "WindowState: "; sender.WindowState
   ? "StartPosition: "; sender.StartPosition
   ? "BorderStyle: "; sender.BorderStyle
   ? "MinimizeBox: "; sender.MinimizeBox
   ? "MaximizeBox: "; sender.MaximizeBox
   ? "ControlBox: "; sender.ControlBox
   ? "IsMainForm: "; sender.IsMainForm
   ? "IsModal: "; sender.IsModal
   ?
   function = 0
end function



''
''  Main code for the application. 
''
Application.Run(Form1)

' Pause at the end so we can see the last messages in the console window
sleep

