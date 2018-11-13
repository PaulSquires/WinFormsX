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


type Form1Type extends wfxForm
   private:
      temp as byte
   public:
      declare constructor
      ' Controls
      MainMenu As wfxMainMenu
end type

constructor Form1Type
   this.Text = "Form1"
   this.SetBounds(10,10,500,300)
'   this.Button1.Parent = @this
'   this.Button1.Font = New wfxFont("Symbol",9,FontStyles.Normal,FontCharset.Symbol)
'   this.Button1.Text = "¯"
'   this.Button1.SetBounds(196,108,57,47)
   
   this.MainMenu.Parent = @this
   this.Controls.Add(ControlType.MainMenu, @this.MainMenu)
   Application.Forms.Add(ControlType.Form, @this)
end constructor

dim shared Form1 as Form1Type


''
''  Main code for the application. 
''
Application.Run(Form1)


