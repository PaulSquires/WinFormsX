''
''  BUTTONTEST
''  Button test application. 
''

' Use the following Include line if the library has already been copied
' to the compiler's \inc folder.
'#include once "WinFormsX\WinFormsX.bi"

' Use the following include if we are simply testing code via the GitHub ownload.
#include once "..\src\WinFormsX.bi"

' When compiling, be sure to include the file "resource.rc". In WinFBE, this can be done
' via the Compiler Setup / Additional Compiler Settings


'#CONSOLE ON
'#RESOURCE "resource.rc"

declare function Form1_Click( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
declare function Form1_Button1_AllEvents( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
declare function Form1_Button1_Destroy( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
declare function Form1_Button1_Click( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
declare function Form1_Button1_MouseMove( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
declare function Form1_Button1_MouseDown( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
declare function Form1_Button1_MouseUp( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
declare function Form1_Button1_MouseDoubleClick( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
declare function Form1_Button1_MouseEnter( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
declare function Form1_Button1_MouseHover( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
declare function Form1_Button1_MouseLeave( byref sender as wfxButton, byref e as EventArgs ) as LRESULT

''          
''  Define the form (no child controls for this test)
''
type TFORMMAIN extends wfxForm
   private:
   
   public:
      ' Controls
      Button1 as wfxButton
      
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
      .Background    = Colors.SystemButtonFace
      .OnClick       = @Form1_Click
   end with
   with this.Button1
      .Parent = @this
      .Text = "This is a Button"
      .SetBounds(5, 5, 150, 30)
      .TextAlign     = ButtonAlignment.MiddleCenter
      .OnAllEvents   = @Form1_Button1_AllEvents
      .OnDestroy     = @Form1_Button1_Destroy
      .OnClick       = @Form1_Button1_Click
      .OnMouseMove   = @Form1_Button1_MouseMove
      .OnMouseDown   = @Form1_Button1_MouseDown
      .OnMouseUp     = @Form1_Button1_MouseUp
      .OnMouseDoubleClick = @Form1_Button1_MouseDoubleClick
      .OnMouseEnter  = @Form1_Button1_MouseEnter
      .OnMouseHover  = @Form1_Button1_MouseHover
      .OnMouseLeave  = @Form1_Button1_MouseLeave
   end with
   this.Controls.add(controltype.Button, @this.Button1)

END CONSTRUCTOR

''  Define a global variable that will allow access to the form and controls
dim shared Form1 as TFORMMAIN


''
''  Define the various methods that the application will respond to.
''  User code will go into these methods in order to make the application work.
''
function Form1_Click( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   ' Change the text for the label
   Form1.Button1.Text = "New Text"
   function = 0
end function

function Form1_Button1_AllEvents( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
   ' All events flow through here so basically you can capture and respond to
   ' any Windows message through this handler. If you handle the message here then
   ' you simply set e.Handled = True before returning.
   function = 0
end function

function Form1_Button1_Destroy( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
   ? "Button Destroy"
   function = 0
end function

function Form1_Button1_MouseMove( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
   Form1.Text = "Button MouseMove (x,y) = (" & e.x & "," & e.y & ")"
   function = 0
end function

function Form1_Button1_MouseDown( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
   Form1.Text = "Button MouseDown (x,y) = (" & e.x & "," & e.y & ")"
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

function Form1_Button1_MouseUp( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
   Form1.Text = "Button MouseUp (x,y) = (" & e.x & "," & e.y & ")"
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

function Form1_Button1_MouseDoubleClick( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
   sender.Text = "Button MouseDoubleClick (x,y) = (" & e.x & "," & e.y & ")"
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

function Form1_Button1_MouseEnter( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
   sender.Text = "Button MouseEnter"
   function = 0
end function

function Form1_Button1_MouseHover( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
   sender.Text = "Button MouseHover"
   function = 0
end function

function Form1_Button1_MouseLeave( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
   sender.Text = "Button MouseLeave"
   function = 0
end function

function Form1_Button1_Click( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
   ' Print the properties of the label to the console window
   ' In addition to using the "sender" object we could also have referred to the 
   ' label properties through use of the global shared Form1 variable (Form1.Label1).
   dim pt as wfxPoint = sender.Position
   dim size as wfxSize = sender.Size
   
   ? "Name: "; sender.Name
   ? "Text: "; sender.Text
   ? "Parent: "; sender.Parent
   ? "Background: "; sender.Background
   ? "Enabled: "; sender.Enabled
   ? "Visible: "; sender.Visible
   ? "Left: "; sender.Left
   ? "Top: "; sender.Top
   ? "Width: "; sender.Width
   ? "Height: "; sender.Height
   ? "Size: "; size.Width; " x "; size.Height
   ? "Position: "; pt.x; ", "; pt.y
   ?
   function = 0
end function



''
''  Main code for the application. 
''
Application.Run(Form1)

' Pause at the end so we can see the last messages in the console window
sleep

