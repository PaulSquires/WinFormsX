'    WinFormsX - Windows GUI Framework for the FreeBASIC Compiler
'    Copyright (C) 2018 Paul Squires, PlanetSquires Software
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


Type wfxButton Extends wfxControl
   private:
      _XpButtonPtr As CXpButton Ptr
      _TextAlign As ButtonAlignment = ButtonAlignment.MiddleCenter
      _ThemeSupport      As boolean = True
      _BackColorDown     As COLORREF = Colors.SystemControl
      _BackColorHot      As COLORREF = Colors.SystemControl
      _TextForeColor     As COLORREF = Colors.SystemControlText
      _TextForeColorDown As COLORREF = Colors.SystemControlText
      _TextBackColor     As COLORREF = Colors.SystemControl
      _TextBackColorDown As COLORREF = Colors.SystemControl
      _ToggleMode        As boolean = False
      _ToggleState       As boolean = False
      
   Public:
      declare Property BackColor( ByVal nValue As COLORREF )
      Declare Property BackColor() As COLORREF 
      Declare Property BackColorDown( ByVal nValue As COLORREF )
      Declare Property BackColorDown() As COLORREF 
      Declare Property BackColorHot( ByVal nValue As COLORREF )
      Declare Property BackColorHot() As COLORREF 
      Declare Property TextForeColor() As COLORREF
      Declare Property TextForeColor( ByVal nValue As COLORREF)
      Declare Property TextBackColor() As COLORREF
      Declare Property TextBackColor( ByVal nValue As COLORREF)
      Declare Property TextForeColorDown() As COLORREF
      Declare Property TextForeColorDown( ByVal nValue As COLORREF)
      Declare Property TextBackColorDown() As COLORREF
      Declare Property TextBackColorDown( ByVal nValue As COLORREF)
      Declare Property ToggleMode() As boolean
      Declare Property ToggleMode( ByVal nValue As boolean )
      Declare Property ToggleState() As boolean
      Declare Property ToggleState( ByVal nValue As boolean )
      Declare Property ThemeSupport() As boolean
      Declare Property ThemeSupport( ByVal nValue As boolean )
      Declare Property TextAlign() As ButtonAlignment
      Declare Property TextAlign( ByVal nValue As ButtonAlignment )
      declare function Show(byval hWndParent as hwnd = 0) as long override
      Declare Constructor( ByRef wszName As WString = "" )
      Declare Destructor()

      OnAllEvents        as function( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
      OnDestroy          as function( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
      OnGotFocus         as function( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
      OnLostFocus        as function( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
      OnMouseMove        as function( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
      OnMouseDown        as function( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
      OnMouseUp          as function( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
      OnMouseDoubleClick as function( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
      OnMouseEnter       as function( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
      OnMouseHover       as function( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
      OnMouseLeave       as function( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
      OnKeyDown          as function( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
      OnKeyPress         as function( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
      OnKeyUp            as function( byref sender as wfxButton, byref e as EventArgs ) as LRESULT
      OnDropFiles        as function( byref sender as wfxButton, byref e as EventArgs ) as LRESULT

End Type

