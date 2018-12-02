''
''  MAINMENU TEST
''  MainMenu test application. 
''

#include once "..\src\WinFormsX.bi"

' When compiling, be sure to include the file "resource.rc". In WinFBE, this can be done
' via the Compiler Setup / Additional Compiler Settings, or using the #RESOURCE code
' directive as shown below.


'#CONSOLE ON
'#RESOURCE "resource.rc"

declare function Form1_Button1_Click( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
declare function Form1_MainMenu_Popup( byref sender as wfxMenuItem, byref e as EventArgs ) as LRESULT
declare function Form1_MainMenu_Click( byref sender as wfxMenuItem, byref e as EventArgs ) as LRESULT

type Form1Type extends wfxForm
   private:
      temp as byte
   public:
      declare constructor
      ' Controls
      MainMenu As wfxMainMenu
      Button1 as wfxButton
end type

constructor Form1Type
   dim as long idx
   this.Text = "Form1"
   this.SetBounds(10,10,500,300)
   
   this.MainMenu.Parent = @this

   dim mnuFile   as wfxMenuItem = wfxMenuItem("File", "mnuFile")
   dim mnuNew    as wfxMenuItem = wfxMenuItem("New",  "mnuNew", "Ctrl+DEL")
   DIM mnuOpen   as wfxMenuItem = wfxMenuItem("Open", "mnuOpen")
   DIM mnuSave   as wfxMenuItem = wfxMenuItem("Save", "mnuSave", "Ctrl+S")
   DIM mnuSaveAs as wfxMenuItem = wfxMenuItem("Save As", "mnuSaveAs", "F12")
   DIM mnuSep1   as wfxMenuItem = wfxMenuItem("-",    "mnuSep1")
   DIM mnuExit   as wfxMenuItem = wfxMenuItem("Exit", "mnuExit")
   mnuFile.MenuItems.Add(mnuNew)
   mnuFile.MenuItems.Add(mnuOpen)
   mnuFile.MenuItems.Add(mnuSave)
   mnuFile.MenuItems.Add(mnuSaveAs)
   mnuFile.MenuItems.Add(mnuSep1)
   mnuFile.MenuItems.Add(mnuExit)
   this.MainMenu.MenuItems.Add(mnuFile)
   
   DIM mnuEdit  as wfxMenuItem = wfxMenuItem("Edit", "mnuEdit")
   DIM mnuCut   as wfxMenuItem = wfxMenuItem("Cut",  "mnuCut")
   DIM mnuCopy  as wfxMenuItem = wfxMenuItem("Copy", "mnuCopy")
   DIM mnuPaste as wfxMenuItem = wfxMenuItem("Paste", "mnuPaste")
   mnuEdit.MenuItems.Add(mnuCut)
   mnuEdit.MenuItems.Add(mnuCopy)
   mnuEdit.MenuItems.Add(mnuPaste)
   this.MainMenu.MenuItems.Add(mnuEdit)
   
   this.MainMenu.OnPopup = @Form1_MainMenu_Popup
   this.MainMenu.OnClick = @Form1_MainMenu_Click

   this.Controls.Add(ControlType.MainMenu, @this.MainMenu)


   with this.Button1
      .Parent = @this
      .Name = "Button1"
      .Text = "Button1"
      .SetBounds(100, 100, 70, 30)
      .Focused = true   ' set initial focus to this control
      .OnClick = @Form1_Button1_Click
   end with
   this.Controls.add(controltype.Button, @this.Button1)


   Application.Forms.Add(ControlType.Form, @this)
end constructor

dim shared Form1 as Form1Type 



function IterateMenuItems( byref tMenuItem as wfxMenuItem ) as long
   
   ' Internal function that recursive processes all of the menu items. 
   ' It takes into account that submenus can exist for each MenuItem.

   select case ucase(tMenuItem.Name)
      CASE "MNUFILE", "MNUEDIT", "MNUVIEW", "MNUHELP"
         ' Do not modify these. These are on the MainMenu menu bar.
      CASE ELSE
         tMenuItem.Grayed = True
   end select

   ' Process any children MenuItems recursively
   For i As Long = 0 To tMenuItem.MenuItems.Count - 1
      if tMenuItem.MenuItem(i).IsParent then
         IterateMenuItems( tMenuItem.MenuItem(i) )
      end if   
   Next
   
   function = 0
end function


function Form1_Button1_Click( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
   ' Iterate all MenuItems in the MainMenu and set each one to Grayed.
   ' We start at the root MenuItem that is dsplayed on the MainMenu's menu bar
   ' (eg. File, Edit, View, Help) and use recursion to visit every sub-MenuItem. 
   For i As Long = 0 To Form1.MainMenu.MenuItems.Count - 1
      IterateMenuItems( Form1.MainMenu.MenuItem(i) )
   Next

   function = 0
end function




function Form1_MainMenu_Popup( byref sender as wfxMenuItem, byref e as EventArgs ) as LRESULT
   ? "menu popup: "; sender.Text
   function = 0
end function


function Form1_MainMenu_Click( byref sender as wfxMenuItem, byref e as EventArgs ) as LRESULT

   select case ucase(sender.Name)
      CASE "MNUFILE"
      CASE "MNUEDIT"
      CASE "MNUVIEW"
      CASE "MNUHELP"
   end select
   
   function = 0
end function

''
''  Main code for the application. 
''
Application.Run(Form1)


