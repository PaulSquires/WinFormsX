''
''  LISTBOXTEST
''  ListBox test application. 
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

declare function Form1_List1_AllEvents( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
declare function Form1_List1_Destroy( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
declare function Form1_List1_Click( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
declare function Form1_List1_MouseMove( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
declare function Form1_List1_MouseDown( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
declare function Form1_List1_MouseUp( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
declare function Form1_List1_MouseDoubleClick( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
declare function Form1_List1_MouseEnter( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
declare function Form1_List1_MouseHover( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
declare function Form1_List1_MouseLeave( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
declare function Form1_cmdAdd_Click( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
declare function Form1_cmdDelete_Click( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
declare function Form1_cmdClear_Click( byref sender as wfxButton, byref e as EventArgs ) as LRESULT

''          
''  Define the form (no child controls for this test)
''
type TFORMMAIN extends wfxForm
   private:
   
   public:
      ' Controls
      List1     as wfxListBox
      cmdAdd    as wfxButton
      cmdDelete as wfxButton
      cmdClear  as wfxButton
      
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
   
   with this.List1
      .Parent = @this
      .Name = "List"
      .SetBounds(10, 25, 200, 300)
      .SelectionMode = ListSelectionMode.MultiExtended
      .BackColorHot  = colors.AliceBlue
      .ForeColorHot  = colors.Ivory
      .OnAllEvents   = @Form1_List1_AllEvents
      .OnDestroy     = @Form1_List1_Destroy
      .OnClick       = @Form1_List1_Click
      .OnMouseMove   = @Form1_List1_MouseMove
      .OnMouseDown   = @Form1_List1_MouseDown
      .OnMouseUp     = @Form1_List1_MouseUp
      .OnMouseDoubleClick = @Form1_List1_MouseDoubleClick
      .OnMouseEnter  = @Form1_List1_MouseEnter
      .OnMouseHover  = @Form1_List1_MouseHover
      .OnMouseLeave  = @Form1_List1_MouseLeave
   end with
   this.Controls.add(controltype.ListBox, @this.List1)
   
   ' Load 10 items into the ListBox
   dim as Long idx
   for i as long = 1 to 10
     idx = this.List1.Items.Add
     this.List1.Item(idx).Text = "Listbox line:" & i
     this.List1.Item(idx).data32 = i
   next
   this.List1.SelectedIndex = 0
   
   with this.cmdAdd
      .Parent = @this
      .Name = "cmdAdd"
      .Text = "Add"
      .SetBounds(220, 25, 70, 30)
      .Focused = true   ' set initial focus to this control
      .OnClick = @Form1_cmdAdd_Click
   end with
   this.Controls.add(controltype.Button, @this.cmdAdd)
   
   with this.cmdDelete
      .Parent = @this
      .Name = "cmdDelete"
      .Text = "Delete"
      .SetBounds(300, 25, 70, 30)
      .OnClick = @Form1_cmdDelete_Click
   end with
   this.Controls.add(controltype.Button, @this.cmdDelete)

   with this.cmdClear
      .Parent = @this
      .Name = "cmdClear"
      .Text = "Clear"
      .SetBounds(380, 25, 70, 30)
      .OnClick = @Form1_cmdClear_Click
   end with

   this.Controls.add(controltype.Button, @this.cmdClear)

END CONSTRUCTOR

''  Define a global variable that will allow access to the form and controls
dim shared Form1 as TFORMMAIN


''
''  Define the various methods that the application will respond to.
''  User code will go into these methods in order to make the application work.
''

function Form1_List1_AllEvents( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
   ' All events flow through here so basically you can capture and respond to
   ' any Windows message through this handler. If you handle the message here then
   ' you simply set e.Handled = True before returning.
   function = 0
end function

function Form1_List1_Destroy( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
   ? "List1 Destroy"
   function = 0
end function

function Form1_List1_MouseMove( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "List1 MouseMove (x,y) = (" & e.x & "," & e.y & ")"
   function = 0
end function

function Form1_List1_MouseDown( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "List1 MouseDown (x,y) = (" & e.x & "," & e.y & ")"
'   ? "MouseDown"
'   ? "Ctrl: "; e.Ctrl
'   ? "Shift: "; e.Shift
'   ? "Alt: "; e.Alt
'   ? "LButton: "; e.LButton
'   ? "MButton: "; e.MButton
'   ? "RButton: "; e.RButton
'   ?
   function = 0
end function

function Form1_List1_MouseUp( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "List1 MouseUp (x,y) = (" & e.x & "," & e.y & ")"
'   ? "MouseUp"
'   ? "Ctrl: "; e.Ctrl
'   ? "Shift: "; e.Shift
'   ? "Alt: "; e.Alt
'   ? "LButton: "; e.LButton
'   ? "MButton: "; e.MButton
'   ? "RButton: "; e.RButton
'   ?
   function = 0
end function

function Form1_List1_MouseDoubleClick( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
   Form1.Text = "List1 MouseDoubleClick (x,y) = (" & e.x & "," & e.y & ")"
'   ? "MouseDoubleClick"
'   ? "Ctrl: "; e.Ctrl
'   ? "Shift: "; e.Shift
'   ? "Alt: "; e.Alt
'   ? "LButton: "; e.LButton
'   ? "MButton: "; e.MButton
'   ? "RButton: "; e.RButton
'   ?
   function = 0
end function

function Form1_List1_MouseEnter( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
   '? "List1 MouseEnter"
   function = 0
end function

function Form1_List1_MouseHover( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
   '? "List1 MouseHover"
   function = 0
end function

function Form1_List1_MouseLeave( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
   '? "List1 MouseLeave"
   function = 0
end function

function Form1_List1_Click( byref sender as wfxListBox, byref e as EventArgs ) as LRESULT
   ' Print the properties of the label to the console window
   ' In addition to using the "sender" object we could also have referred to the 
   ' label properties through use of the global shared Form1 variable (Form1.Label1).
   ? "List1 Click"
   
   if Form1.List1.SelectionMode = ListSelectionMode.One then
      dim byref ListItem as wfxListBoxItem = Form1.List1.SelectedItem
      ? ListItem.Text, ListItem.Data32
   else
      ' If this ListBox allows multiple items to be selected then loop through and display.
      for i as long = 0 to Form1.List1.Items.Count - 1
         if Form1.List1.Item(i).Selected then
            ? "ListBox Item index: "; i; " is selected."
         end if
      NEXT
   end if
   
   function = 0
end function

function Form1_cmdAdd_Click( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
   ? "Button Click: "; sender.Name
   ? "Add 10 lines to the Listbox"
   dim as Long idx
   for i as long = 1 to 10
     idx = Form1.List1.Items.Add
     Form1.List1.Item(idx).Text = "Add Listbox line:" & idx
     Form1.List1.Item(idx).Data32 = idx
   next
   ? "List1 count: "; Form1.List1.Items.Count
   function = 0
end function

function Form1_cmdDelete_Click( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
   ? "Button Click: "; sender.Name
   ? "Delete index: "; Form1.List1.SelectedIndex
   Form1.List1.Items.Remove(Form1.List1.SelectedIndex)
   function = 0
end function

function Form1_cmdClear_Click( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
   ? "Button Click: "; sender.Name
   ? "Clear List1"
   Form1.List1.Items.Clear
   ? "List1 count: "; Form1.List1.Items.Count
   function = 0
end function


''
''  Main code for the application. 
''
Application.Run(Form1)

' Pause at the end so we can see the last messages in the console window
sleep

