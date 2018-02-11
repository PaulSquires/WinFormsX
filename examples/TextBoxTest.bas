''
''  TEXTBOXTEST
''  Button test application. 
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

declare function Form1_Text1_AllEvents( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text1_Destroy( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text1_MouseMove( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text1_MouseDown( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text1_MouseUp( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text1_MouseDoubleClick( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text1_MouseEnter( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text1_MouseHover( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text1_MouseLeave( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text1_KeyPress( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text1_GotFocus( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text1_LostFocus( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text2_Destroy( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text2_MouseEnter( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text2_MouseHover( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text2_MouseLeave( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text2_KeyPress( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text2_GotFocus( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text2_LostFocus( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text3_Destroy( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text3_MouseEnter( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text3_MouseHover( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text3_MouseLeave( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text3_KeyPress( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text3_GotFocus( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
declare function Form1_Text3_LostFocus( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT

''          
''  Define the form and the child button controls
''
type TFORMMAIN extends wfxForm
   private:
   
   public:
      ' Controls
      Text1 as wfxTextBox
      Text2 as wfxTextBox
      Text3 as wfxTextBox
      
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
      .Text          = "Form1"
      .Name          = "Form1"
   end with
   ' Add the form to the global application collection
   Application.Forms.Add(ControlType.Form, @this)
   
   with this.Text1
      .Parent = @this
      .Name = "Text1"
      .Text = "Text1"
      .SetBounds(10, 25, 120, 24)
      .Focused       = true   ' set initial focus to this control
      .TextAlign     = TextBoxAlignment.Left
      .OnAllEvents   = @Form1_Text1_AllEvents
      .OnDestroy     = @Form1_Text1_Destroy
      .OnMouseMove   = @Form1_Text1_MouseMove
      .OnMouseDown   = @Form1_Text1_MouseDown
      .OnMouseUp     = @Form1_Text1_MouseUp
      .OnMouseDoubleClick = @Form1_Text1_MouseDoubleClick
      .OnMouseEnter  = @Form1_Text1_MouseEnter
      .OnMouseHover  = @Form1_Text1_MouseHover
      .OnMouseLeave  = @Form1_Text1_MouseLeave
      .OnKeyPress    = @Form1_Text1_KeyPress
      .OnGotFocus    = @Form1_Text1_GotFocus
      .OnLostFocus   = @Form1_Text1_LostFocus
   end with
   this.Controls.add(controltype.TextBox, @this.Text1)
   
   with this.Text2
      .Parent = @this
      .Name = "Text2"
      .Text = "Text2"
      .TextAlign = TextBoxAlignment.Center
      .SetBounds(145, 25, 120, 24)
      .OnDestroy    = @Form1_Text2_Destroy
      .OnMouseEnter = @Form1_Text2_MouseEnter
      .OnMouseHover = @Form1_Text2_MouseHover
      .OnMouseLeave = @Form1_Text2_MouseLeave
      .OnKeyPress   = @Form1_Text2_KeyPress
      .OnGotFocus   = @Form1_Text2_GotFocus
      .OnLostFocus  = @Form1_Text2_LostFocus
   end with
   this.Controls.add(controltype.TextBox, @this.Text2)

   with this.Text3
      .Parent = @this
      .Name = "Text3"
      .Text = "Text3"
      .TextAlign = TextBoxAlignment.Right
      .Background = Colors.Yellow
      .Foreground = Colors.Red
      .SetBounds(270, 25, 120, 24)
      .OnDestroy    = @Form1_Text3_Destroy
      .OnMouseEnter = @Form1_Text3_MouseEnter
      .OnMouseHover = @Form1_Text3_MouseHover
      .OnMouseLeave = @Form1_Text3_MouseLeave
      .OnKeyPress   = @Form1_Text3_KeyPress
      .OnGotFocus   = @Form1_Text3_GotFocus
      .OnLostFocus  = @Form1_Text3_LostFocus
   end with
   this.Controls.add(controltype.TextBox, @this.Text3)

END CONSTRUCTOR

''  Define a global variable that will allow access to the form and controls
dim shared Form1 as TFORMMAIN


''
''  Define the various methods that the application will respond to.
''  User code will go into these methods in order to make the application work.
''
function Form1_Text1_AllEvents( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   ' All events flow through here so basically you can capture and respond to
   ' any Windows message through this handler. If you handle the message here then
   ' you simply set e.Handled = True before returning.
   function = 0
end function

function Form1_Text1_Destroy( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   ? "Text1 Destroy"
   function = 0
end function

function Form1_Text1_MouseMove( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Text1 MouseMove (x,y) = (" & e.x & "," & e.y & ")"
   function = 0
end function

function Form1_Text1_MouseDown( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Text1 MouseDown (x,y) = (" & e.x & "," & e.y & ")"
   function = 0
end function

function Form1_Text1_MouseUp( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Text1 MouseUp (x,y) = (" & e.x & "," & e.y & ")"
   function = 0
end function

function Form1_Text1_MouseDoubleClick( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Text1 MouseDoubleClick (x,y) = (" & e.x & "," & e.y & ")"
   function = 0
end function

function Form1_Text1_MouseEnter( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Text1 MouseEnter"
   function = 0
end function

function Form1_Text1_MouseHover( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Text1 MouseHover"
   function = 0
end function

function Form1_Text1_MouseLeave( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Text1 MouseLeave"
   function = 0
end function

function Form1_Text1_GotFocus( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   ? "Text1 GotFocus"
   function = 0
end function

function Form1_Text1_LostFocus( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   ? "Text1 LostFocus"
   function = 0
end function

function Form1_Text1_KeyPress( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   ? "Text1 KeyPress: "; chr(e.KeyChar)
   function = 0
end function

function Form1_Text2_Destroy( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   ? "Text2 Destroy"
   function = 0
end function

function Form1_Text2_MouseEnter( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Text2 MouseEnter"
   function = 0
end function

function Form1_Text2_MouseHover( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Text2 MouseHover"
   function = 0
end function

function Form1_Text2_MouseLeave( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Text2 MouseLeave"
   function = 0
end function

function Form1_Text2_GotFocus( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   ? "Text2 GotFocus"
   function = 0
end function

function Form1_Text2_KeyPress( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   ? "Text2 KeyPress: "; chr(e.KeyChar)
   function = 0
end function

function Form1_Text2_LostFocus( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   ? "Text2 LostFocus"
   function = 0
end function

function Form1_Text3_Destroy( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   ? "Text3 Destroy"
   function = 0
end function

function Form1_Text3_MouseEnter( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Text3 MouseEnter"
   function = 0
end function

function Form1_Text3_MouseHover( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Text3 MouseHover"
   function = 0
end function

function Form1_Text3_MouseLeave( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Text3 MouseLeave"
   function = 0
end function

function Form1_Text3_GotFocus( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   ? "Text3 GotFocus"
   function = 0
end function

function Form1_Text3_KeyPress( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   ? "Text3 KeyPress: "; chr(e.KeyChar)
   function = 0
end function

function Form1_Text3_LostFocus( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
   ? "Text3 LostFocus"
   function = 0
end function



''
''  Main code for the application. 
''
Application.Run(Form1)

' Pause at the end so we can see the last messages in the console window
sleep

