'    WinFormsX - Windows GUI Framework for the FreeBASIC Compiler
'    Copyright (C) 2018-2020 Paul Squires, PlanetSquires Software
'
'    This program is free software: you can redistribute it and/or modify
'    it under the terms of the GNU General Public License as published by
'    the Free Software Foundation, either version 3 of the License, or
'    (at your option) any later version.
'
'    This program is distributed in the hope that it will be useful,
'    but WITHOUT any WARRANTY; without even the implied warranty of
'    MERCHANTABILITY or FITNESS for A PARTICULAR PURPOSE.  See the
'    GNU General Public License for more details.


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
   TrackBar
   Treeview
   Frame
   MaskedEdit
   ComboBox
   MainMenu
   RichEdit
   ToolBar
   ToolBarButton
   UpDown
   Timer
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

enum ImageAlignment
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
   Unchecked = 0   ' easier to do boolean ifchecked() type of tests
   Checked 
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

enum SortOrder
   None = 1
   Ascending
   Descending
end enum

enum ColumnHeaderStyle
   None = 1
   Clickable
   NonClickable
end enum

enum DateTimePickerFormat 
   LongDate = 1
   ShortDate
   ShortDateCentury
   TimeFormat
   CustomFormat
end enum

enum ControlImageSize
   Size16 = 16
   Size24 = 24
   Size32 = 32
   Size48 = 48
end enum   


type EventArgs as wfxEventArgs    ' forward reference
Type wfxEventArgs Extends Object
   private:
   public:
      Message           As UINT        ' Windows value of message being sent (WM_COMMAND, WM_NOTIFY, etc)
      wParam            as WPARAM      ' the wParam of the raw message
      lParam            as LPARAM      ' the lParam of the raw message
      Handled           as Boolean     ' indicates whether the event is handled by the user
      Cancel            as boolean     ' set to True to cancel closing of Form
      Ctrl              as Boolean     ' the CTRL key is pressed
      Alt               as Boolean     ' the Alt key is pressed
      Shift             as Boolean     ' the SHIFT key is pressed
      KeyChar           as long        ' stores the character corresponding to the key pressed
      KeyCode           as long        ' stores the keyboard code for the event
      LButton           as boolean     ' the left mouse button pressed
      MButton           as boolean     ' the middle mouse button pressed
      RButton           as boolean     ' the right mouse button pressed
      pt                as POINT       ' point structure window coordinates of mouse click
      x                 as long        ' the x-coordinate of the mouse click
      y                 as long        ' the y-coordinate of the mouse click
      hDrop             as HDROP       ' handle used for WM_DROPFILES message
      ListViewRow       as long        ' zero based value of current Listview row
      ListViewColumn    as long        ' zero based value of current Listview column
end type

function WinFBE_GetTextWidthPixels( byval hWin as HWND, byref wszText as WString ) as Long
   dim as HDC _hdc = GetDC(hWin)
   dim as SIZE _size 
   dim as HFONT oldfont = SelectObject( _hdc, AfxGetWindowFont(hWin) )
   GetTextExtentPoint32( _hdc, wszText, len(wszText), @_size)
   SelectObject( _hdc, oldfont )
   ReleaseDC( hWin, _hdc )
   function = _size.cx
end function
               






