
enum ControlType
   Form = 1
   Button
   CheckBox
   OptionButton
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
   Frame
   MaskedEdit
   ComboBox
   MainMenu
   RichEdit
End Enum

Enum FontStyles
   Normal    = 0
   Bold      = 1
   Italic    = 2
   Strikeout = 4
   Underline = 8
End Enum

Enum FontCharset
   Default     = DEFAULT_CHARSET
   Ansi        = ANSI_CHARSET
   Arabic      = ARABIC_CHARSET
   Baltic      = BALTIC_CHARSET
   ChineseBig5 = CHINESEBIG5_CHARSET
   EastEurope  = EASTEUROPE_CHARSET
   GB2312      = GB2312_CHARSET
   Greek       = GREEK_CHARSET
   Hangul      = HANGUL_CHARSET
   Hebrew      = HEBREW_CHARSET
   Johab       = JOHAB_CHARSET
   Mac         = MAC_CHARSET
   OEM         = OEM_CHARSET
   Russian     = RUSSIAN_CHARSET
   Shiftjis    = SHIFTJIS_CHARSET
   Symbol      = SYMBOL_CHARSET
   Thai        = THAI_CHARSET
   Turkish     = TURKISH_CHARSET
   Vietnamese  = VIETNAMESE_CHARSET
End Enum

Enum FormWindowState
   Maximized = 1
   Minimized
   Normal
End Enum

Enum FormStartPosition
   CenterParent = 1
   CenterScreen
   Manual
   WindowsDefaultLocation
end enum

enum FormBorderStyle
   None = 1
   Sizable 
   Fixed3D 
   FixedSingle	
   FixedDialog	
   FixedToolWindow 
   SizableToolWindow 
end enum

enum ControlBorderStyle
   None	= 1
   FixedSingle	
   Fixed3D 
End Enum

Enum ImageLayout
   None = 1
   Tile
   Center
   Stretch
   Zoom
END ENUM

enum ImageScale
   None = 1
   AutoSize
   FitWidth
   FitHeight   
   Stretch
end enum

enum ButtonAlignment
   BottomCenter = 1
   BottomLeft   
   BottomRight  
   MiddleCenter 
   MiddleLeft   
   MiddleRight  
   TopCenter    
   TopLeft      
   TopRight     
end enum

enum LabelAlignment
   MiddleCenter = 1
   MiddleLeft   
   MiddleRight  
   TopCenter    
   TopLeft      
   TopRight     
   BottomCenter 
   BottomLeft   
   BottomRight  
end enum

Enum CharacterCase
   Normal = 1
   Upper
   Lower
End Enum

Enum ScrollBars
   None = 1
   Horizontal
   Vertical
   Both
End Enum

Enum CheckBoxState      
   Checked = 1
   Unchecked
   Indeterminate
End Enum
   
Enum TextAlignment
   Left   = 1 
   Right  
   Center 
end enum

Enum ListSelectionMode
   None = 1
   One
   MultiSimple
   MultiExtended
END ENUM

enum ComboBoxStyle
   Simple = 1
   DropDown
   DropDownList
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
      hDrop           as HDROP       ' handle used for WM_DROPFILES message
end type






