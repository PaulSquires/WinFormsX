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
''  Label Class
''
''  https://msdn.microsoft.com/en-us/library/system.windows.forms.label(v=vs.110).aspx
''


Type wfxLabel Extends wfxControl
   private:
      _TextAlign     As LabelAlignment = LabelAlignment.TopLeft
      _UseMnemonic   As Boolean = True    
      _BorderStyle   As ControlBorderStyle = ControlBorderStyle.None
      _BackColorHot  As COLORREF 
      _ForeColorHot  As COLORREF 
      _hBackBrushHot As HBRUSH 
      
   Public:
      Declare Constructor( byref wszName as wstring = "" )
      Declare destructor
      Declare Function GetTextAlignStyleValue( ByVal nValue As LabelAlignment ) As Long
      Declare Property BorderStyle() As ControlBorderStyle
      Declare Property BorderStyle( ByVal nValue As ControlBorderStyle )
      Declare Property hBackBrushHot() As HBRUSH   ' internal get
      Declare Property BackColorHot() As COLORREF
      Declare Property BackColorHot( ByVal nValue As COLORREF )
      declare property ForeColorHot() as COLORREF
      Declare Property ForeColorHot( ByVal nValue As COLORREF )
      Declare Property TextAlign() As LabelAlignment
      declare property TextAlign( byval nValue as LabelAlignment )
      Declare Property UseMnemonic() As boolean
      Declare Property UseMnemonic( ByVal nValue As boolean )
      declare function Show(byval hWndParent as hwnd = 0) as long override

      OnAllEvents        as function( byref sender as wfxLabel, byref e as EventArgs ) as LRESULT
      OnDestroy          as function( byref sender as wfxLabel, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxLabel, byref e as EventArgs ) as LRESULT
      OnMouseMove        as function( byref sender as wfxLabel, byref e as EventArgs ) as LRESULT
      OnMouseDown        as function( byref sender as wfxLabel, byref e as EventArgs ) as LRESULT
      OnMouseUp          as function( byref sender as wfxLabel, byref e as EventArgs ) as LRESULT
      OnMouseDoubleClick as function( byref sender as wfxLabel, byref e as EventArgs ) as LRESULT
      OnMouseEnter       as function( byref sender as wfxLabel, byref e as EventArgs ) as LRESULT
      OnMouseHover       as function( byref sender as wfxLabel, byref e as EventArgs ) as LRESULT
      OnMouseLeave       as function( byref sender as wfxLabel, byref e as EventArgs ) as LRESULT
      OnDropFiles        As Function( ByRef sender As wfxLabel, ByRef e As EventArgs ) As LRESULT

End Type

