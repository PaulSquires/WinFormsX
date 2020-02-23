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


''
''  wfxStatusBar Class
''
''  https://msdn.microsoft.com/en-us/library/system.windows.forms.statusbar(v=vs.110).aspx
''

enum StatusBarPanelAutoSize
   None     = 0
   Contents = 1
   Spring   = 2
END ENUM

' BorderStyle is deprecated as of v2.0.4 as it has no effect
' in WinFBE programs where Windows Themes are enabled.
'enum StatusBarPanelBorderStyle
'   Sunken = 0
'   None   = SBT_NOBORDERS
'   Raised = SBT_POPOUT
'END ENUM

enum StatusBarPanelAlignment
   Left   = ES_LEFT 
   Right  = ES_RIGHT
   Center = ES_CENTER
end enum


type wfxStatusBarPanel
   private:
      _hWindow      as hwnd
      _Index        as Long
      _Alignment    as StatusBarPanelAlignment
      _AutoSize     as StatusBarPanelAutoSize
      ' BorderStyle is deprecated as of v2.0.4 as it has no effect
      ' in WinFBE programs where Windows Themes are enabled.
      '_BorderStyle as StatusBarPanelBorderStyle 
      _Icon         as wstring * MAX_PATH
      _Text         as CWSTR
      _ToolTip      as CWSTR
      _Width        as Long = 100
      _MinWidth     as Long = 0
      _CtrlID       as long = 100
      _IsHot        as boolean = false
      _BackColor    as COLORREF = GetSysColor(COLOR_3DFACE)
      _BackColorHot as COLORREF = GetSysColor(COLOR_3DFACE)
      _ForeColor    as COLORREF = GetSysColor(COLOR_BTNTEXT)
      _ForeColorHot as COLORREF = GetSysColor(COLOR_BTNTEXT)
     
   public:
      Declare Property hWindow() As hwnd
      Declare Property hWindow( ByVal nValue As hwnd)
      Declare Property Index() As long
      Declare Property Index( ByVal nValue As long)
      Declare Property Alignment() As StatusBarPanelAlignment
      Declare Property Alignment( ByVal nValue As StatusBarPanelAlignment)
      Declare Property AutoSize() As StatusBarPanelAutoSize
      Declare Property AutoSize( ByVal nValue As StatusBarPanelAutoSize)
      ' BorderStyle is deprecated as of v2.0.4 as it has no effect
      ' in WinFBE programs where Windows Themes are enabled.
      'Declare Property BorderStyle() As StatusBarPanelBorderStyle
      'Declare Property BorderStyle( ByVal nValue As StatusBarPanelBorderStyle)
      declare property Text() as CWSTR
      declare property Text( byref wszValue as wstring )
      declare property ToolTip() as CWSTR
      declare property ToolTip( byref wszValue as wstring )
      Declare Property Width() As long
      Declare Property Width( ByVal nValue As long)
      Declare Property MinWidth() As long
      Declare Property MinWidth( ByVal nValue As long)
      declare property Icon() as CWSTR
      declare property Icon( byref cwzValue as wstring )
      Declare Property IsHot() As boolean
      Declare Property IsHot( ByVal nValue As Boolean)
      declare property BackColor() as COLORREF
      declare property BackColor( byval nValue as COLORREF ) 
      declare property BackColorHot() as COLORREF
      declare property BackColorHot( byval nValue as COLORREF ) 
      declare property ForeColor() as COLORREF
      declare property ForeColor( byval nValue as COLORREF ) 
      declare property ForeColorHot() as COLORREF
      declare property ForeColorHot( byval nValue as COLORREF )
      declare function Refresh() as Long 
END TYPE

type wfxStatusBarPanelsCollection
   private:
      _hWindow     as hwnd
      _Collection As wfxLList
      
   public:
      Declare Property hWindow() As hwnd
      Declare Property hWindow( ByVal nValue As hwnd)
      Declare function Count() as long 
      declare function Clear() as Long
      declare function Add() as long 
      declare function ByIndex( byval nIndex as long ) byref as wfxStatusBarPanel
      Declare Constructor
      declare destructor 
END TYPE

type wfxStatusBar extends wfxControl
   private:
      _SizingGrip as boolean 
      _ClickIndex as long  
      _PanelsCollection as wfxStatusBarPanelsCollection
      
   public:
      Declare function Panel( byval nIndex as long) byref as wfxStatusBarPanel 
      declare function Panels byref As wfxStatusBarPanelsCollection
      
      Declare Property SizingGrip() As boolean
      Declare Property SizingGrip( ByVal nValue As Boolean)
      Declare Property ClickIndex() As long
      Declare Property ClickIndex( ByVal nValue As long)
      declare function Show(byval hWndParent as hwnd = 0) as long override
      Declare Constructor
      declare destructor 

      OnAllEvents        as function( byref sender as wfxStatusBar, byref e as EventArgs ) as LRESULT
      OnDestroy          as function( byref sender as wfxStatusBar, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxStatusBar, byref e as EventArgs ) as LRESULT
      OnMouseMove        as function( byref sender as wfxStatusBar, byref e as EventArgs ) as LRESULT
      OnMouseDown        as function( byref sender as wfxStatusBar, byref e as EventArgs ) as LRESULT
      OnMouseUp          as function( byref sender as wfxStatusBar, byref e as EventArgs ) as LRESULT
      OnMouseDoubleClick as function( byref sender as wfxStatusBar, byref e as EventArgs ) as LRESULT
      OnMouseEnter       as function( byref sender as wfxStatusBar, byref e as EventArgs ) as LRESULT
      OnMouseHover       as function( byref sender as wfxStatusBar, byref e as EventArgs ) as LRESULT
      OnMouseLeave       as function( byref sender as wfxStatusBar, byref e as EventArgs ) as LRESULT
      OnDropFiles        As Function( ByRef sender As wfxStatusBar, ByRef e As EventArgs ) As LRESULT
   
END TYPE



