''
''  CHECKBOXTEST
''  CheckBox test application. 
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

declare function Form1_Check1_AllEvents( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check1_Click( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check1_Destroy( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check1_MouseMove( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check1_MouseDown( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check1_MouseUp( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check1_MouseDoubleClick( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check1_MouseEnter( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check1_MouseHover( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check1_MouseLeave( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check1_KeyPress( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check1_GotFocus( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check1_LostFocus( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check2_Click( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check2_Destroy( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check2_MouseEnter( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check2_MouseHover( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check2_MouseLeave( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check2_KeyPress( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check2_GotFocus( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check2_LostFocus( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check3_Click( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check3_Destroy( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check3_MouseEnter( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check3_MouseHover( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check3_MouseLeave( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check3_KeyPress( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check3_GotFocus( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
declare function Form1_Check3_LostFocus( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT

''          
''  Define the form and the child button controls
''
type TFORMMAIN extends wfxForm
   private:
   
   public:
      ' Controls
      Check1 as wfxCheckBox
      Check2 as wfxCheckBox
      Check3 as wfxCheckBox
      
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
   
   with this.Check1
      .Parent = @this
      .Name = "Check1"
      .Text = "Check1"
      .SetBounds(20, 25, 80, 24)
      .Focused       = true   ' set initial focus to this control
      .Checked       = true   ' checkmark
      .BackColor     = Colors.Azure
      .OnAllEvents   = @Form1_Check1_AllEvents
      .OnClick       = @Form1_Check1_Click
      .OnDestroy     = @Form1_Check1_Destroy
      .OnMouseMove   = @Form1_Check1_MouseMove
      .OnMouseDown   = @Form1_Check1_MouseDown
      .OnMouseUp     = @Form1_Check1_MouseUp
      .OnMouseDoubleClick = @Form1_Check1_MouseDoubleClick
      .OnMouseEnter  = @Form1_Check1_MouseEnter
      .OnMouseHover  = @Form1_Check1_MouseHover
      .OnMouseLeave  = @Form1_Check1_MouseLeave
      .OnKeyPress    = @Form1_Check1_KeyPress
      .OnGotFocus    = @Form1_Check1_GotFocus
      .OnLostFocus   = @Form1_Check1_LostFocus
   end with
   this.Controls.add(controltype.CheckBox, @this.Check1)
   
   with this.Check2
      .Parent = @this
      .Name = "Check2"
      .Text = "Check2"
      .BackColor = Colors.HotPink
      .SetBounds(20, 54, 80, 24)
      .OnClick      = @Form1_Check2_Click
      .OnDestroy    = @Form1_Check2_Destroy
      .OnMouseEnter = @Form1_Check2_MouseEnter
      .OnMouseHover = @Form1_Check2_MouseHover
      .OnMouseLeave = @Form1_Check2_MouseLeave
      .OnKeyPress   = @Form1_Check2_KeyPress
      .OnGotFocus   = @Form1_Check2_GotFocus
      .OnLostFocus  = @Form1_Check2_LostFocus
   end with
   this.Controls.add(controltype.CheckBox, @this.Check2)

   with this.Check3
      .Parent = @this
      .Name = "Check3"
      .Text = "Check3"
      .BackColor = Colors.Yellow
      .SetBounds(20, 83, 80, 24)
      .OnClick      = @Form1_Check3_Click
      .OnDestroy    = @Form1_Check3_Destroy
      .OnMouseEnter = @Form1_Check3_MouseEnter
      .OnMouseHover = @Form1_Check3_MouseHover
      .OnMouseLeave = @Form1_Check3_MouseLeave
      .OnKeyPress   = @Form1_Check3_KeyPress
      .OnGotFocus   = @Form1_Check3_GotFocus
      .OnLostFocus  = @Form1_Check3_LostFocus
   end with
   this.Controls.add(controltype.CheckBox, @this.Check3)

END CONSTRUCTOR

''  Define a global variable that will allow access to the form and controls
dim shared Form1 as TFORMMAIN


''
''  Define the various methods that the application will respond to.
''  User code will go into these methods in order to make the application work.
''
function Form1_Check1_AllEvents( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   ' All events flow through here so basically you can capture and respond to
   ' any Windows message through this handler. If you handle the message here then
   ' you simply set e.Handled = True before returning.
   function = 0
end function

function Form1_Check1_Click( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   ? "Check1 Click"
   function = 0
end function

function Form1_Check1_Destroy( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   ? "Check1 Destroy"
   function = 0
end function

function Form1_Check1_MouseMove( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Check1 MouseMove (x,y) = (" & e.x & "," & e.y & ")"
   function = 0
end function

function Form1_Check1_MouseDown( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Check1 MouseDown (x,y) = (" & e.x & "," & e.y & ")"
   function = 0
end function

function Form1_Check1_MouseUp( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Check1 MouseUp (x,y) = (" & e.x & "," & e.y & ")"
   function = 0
end function

function Form1_Check1_MouseDoubleClick( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Check1 MouseDoubleClick (x,y) = (" & e.x & "," & e.y & ")"
   function = 0
end function

function Form1_Check1_MouseEnter( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Check1 MouseEnter"
   function = 0
end function

function Form1_Check1_MouseHover( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Check1 MouseHover"
   function = 0
end function

function Form1_Check1_MouseLeave( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Check1 MouseLeave"
   function = 0
end function

function Form1_Check1_GotFocus( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   ? "Check1 GotFocus"
   function = 0
end function

function Form1_Check1_LostFocus( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   ? "Check1 LostFocus"
   function = 0
end function

function Form1_Check1_KeyPress( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   ? "Check1 KeyPress: "; chr(e.KeyChar)
   function = 0
end function

function Form1_Check2_Click( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   ? "Check2 Click"
   function = 0
end function

function Form1_Check2_Destroy( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   ? "Check2 Destroy"
   function = 0
end function

function Form1_Check2_MouseEnter( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Check2 MouseEnter"
   function = 0
end function

function Form1_Check2_MouseHover( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Check2 MouseHover"
   function = 0
end function

function Form1_Check2_MouseLeave( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Check2 MouseLeave"
   function = 0
end function

function Form1_Check2_GotFocus( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   ? "Check2 GotFocus"
   function = 0
end function

function Form1_Check2_KeyPress( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   ? "Check2 KeyPress: "; chr(e.KeyChar)
   function = 0
end function

function Form1_Check2_LostFocus( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   ? "Check2 LostFocus"
   function = 0
end function

function Form1_Check3_Click( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   ? "Check3 Click"
   function = 0
end function

function Form1_Check3_Destroy( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   ? "Check3 Destroy"
   function = 0
end function

function Form1_Check3_MouseEnter( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Check3 MouseEnter"
   function = 0
end function

function Form1_Check3_MouseHover( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Check3 MouseHover"
   function = 0
end function

function Form1_Check3_MouseLeave( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "Check3 MouseLeave"
   function = 0
end function

function Form1_Check3_GotFocus( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   ? "Check3 GotFocus"
   function = 0
end function

function Form1_Check3_KeyPress( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   ? "Check3 KeyPress: "; chr(e.KeyChar)
   function = 0
end function

function Form1_Check3_LostFocus( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
   ? "Check3 LostFocus"
   function = 0
end function



''
''  Main code for the application. 
''
Application.Run(Form1)

' Pause at the end so we can see the last messages in the console window
sleep


