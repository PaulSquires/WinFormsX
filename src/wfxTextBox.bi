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


Type wfxTextBox Extends wfxControl
      _TextAlign   as TextBoxAlignment = TextBoxAlignment.Left
      _BorderStyle as FormBorderStyle = FormBorderStyle.Fixed3D
      _Multiline   as Boolean = false
      _WordWrap    as Boolean = false
       
   Public:
      Declare Property TextAlign() As TextBoxAlignment
      Declare Property TextAlign( ByVal nValue As TextBoxAlignment)
      Declare Property BorderStyle() As TextBoxBorderStyle
      Declare Property BorderStyle( ByVal nValue As TextBoxBorderStyle )
      declare property Multiline() as boolean
      declare property Multiline( byval nValue as boolean )
      declare property WordWrap() as boolean
      declare property WordWrap( byval nValue as boolean )
      declare function Show(byval hWndParent as hwnd = 0) as long override
      Declare Constructor( byref wszName as wstring = "" )

      OnAllEvents        as function( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
      OnDestroy          as function( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
      OnGotFocus         as function( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
      OnLostFocus        as function( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
      OnMouseMove        as function( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
      OnMouseDown        as function( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
      OnMouseUp          as function( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
      OnMouseDoubleClick as function( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
      OnMouseEnter       as function( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
      OnMouseHover       as function( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
      OnMouseLeave       as function( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
      OnKeyDown          as function( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
      OnKeyPress         as function( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
      OnKeyUp            as function( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
End Type

