
enum ControlType
   Form = 1
   Button
   CheckBox
   RadioButton
   DateTimePicker
   GroupBox
   Label
   ListBox
   Listview
   MonthCalendar
   PictureBox
   ProgressBar
   ScrollBar
   StatusBar
   StatusBarPanel
   TabControl
   TextBox
   ToolBar
   TrackBar
   Treeview
end enum

enum FormWindowState
   Maximized = 1
   Minimized
   Normal
end enum

enum FormStartPosition
   CenterParent = 1
   CenterScreen
   Manual
   WindowsDefaultLocation
end enum

enum FormBorderStyle
   None	= 0
   Sizable = WS_THICKFRAME	
   Fixed3D = WS_EX_CLIENTEDGE	
   FixedSingle	= WS_EX_WINDOWEDGE	
   FixedDialog	= WS_EX_DLGMODALFRAME
   FixedToolWindow = 1
   SizableToolWindow = 2
end enum

enum ButtonAlignment
   BottomCenter = BS_CENTER OR BS_BOTTOM
   BottomLeft   = BS_LEFT   or BS_BOTTOM
   BottomRight  = BS_RIGHT  or BS_BOTTOM
   MiddleCenter = BS_CENTER OR BS_VCENTER
   MiddleLeft   = BS_LEFT   or BS_VCENTER
   MiddleRight  = BS_RIGHT  or BS_VCENTER
   TopCenter    = BS_CENTER or BS_TOP
   TopLeft      = BS_LEFT   or BS_TOP
   TopRight     = BS_RIGHT  or BS_TOP     
end enum

enum LabelAlignment
   MiddleCenter = SS_CENTER OR SS_CENTERIMAGE
   MiddleLeft   = SS_LEFT   or SS_CENTERIMAGE
   MiddleRight  = SS_RIGHT  or SS_CENTERIMAGE
   TopCenter    = SS_CENTER
   TopLeft      = SS_LEFT  
   TopRight     = SS_RIGHT 
end enum

enum TextBoxAlignment
   Left   = ES_LEFT 
   Right  = ES_RIGHT
   Center = ES_CENTER
end enum

enum TextBoxBorderStyle
   None	= 0
   Fixed3D = WS_EX_CLIENTEDGE	
   FixedSingle	= WS_EX_WINDOWEDGE	
   FixedDialog	= WS_EX_DLGMODALFRAME
end enum

type EventArgs as wfxEventArgs    ' forward reference
Type wfxEventArgs Extends Object
   private:
   public:
      Message         As UINT        ' Windows value of message being sent (WM_COMMAND, WM_NOTIFY, etc)
      wParam          as WPARAM      ' the wParam of the raw message
      lParam          as LPARAM      ' the lParam of the raw message
      Handled         as Boolean     ' indicates whether the event is handled by the user
      Cancel          as boolean     ' set to True to cancel closing of Form
      Ctrl            as Boolean     ' the CTRL key is pressed
      Alt             as Boolean     ' the Alt key is pressed
      Shift           as Boolean     ' the SHIFT key is pressed
      KeyChar         as long        ' stores the character corresponding to the key pressed
      KeyCode         as long        ' stores the keyboard code for the event
      LButton         as boolean     ' the left mouse button pressed
      MButton         as boolean     ' the middle mouse button pressed
      RButton         as boolean     ' the right mouse button pressed
      x               as long        ' the x-coordinate of the mouse click
      y               as long        ' the y-coordinate of the mouse click
      PanelClickIndex as long        ' the zero-based index of clicked statusbar panel 
end type


'Type wfxCheckBox Extends wfxControl
'      _TextAlign as ButtonAlignment = ButtonAlignment.MiddleLeft
'      _Checked   as Boolean
          
'   Public:
'      Declare Property TextAlign() As ButtonAlignment
'      Declare Property TextAlign( ByVal nValue As ButtonAlignment )
'      declare property Checked() as boolean
'      declare property Checked( byval nValue as boolean )
'      Declare Constructor( byref wszName as wstring = "" )
'      declare function Show(byval hWndParent as hwnd = 0) as long override
'End Type

'Type wfxRadioButton Extends wfxControl
'      _TextAlign  as ButtonAlignment = ButtonAlignment.MiddleLeft
'      _Checked    as Boolean
'      _StartGroup as Boolean
       
'   Public:
'      Declare Property TextAlign() As ButtonAlignment
'      Declare Property TextAlign( ByVal nValue As ButtonAlignment )
'      declare property Checked() as boolean
'      declare property Checked( byval nValue as boolean )
'      declare property StartGroup() as boolean
'      declare property StartGroup( byval nValue as boolean )
'      Declare Constructor( byref wszName as wstring = "" )
'      declare function Show(byval hWndParent as hwnd = 0) as long override
'End Type




