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


Type wfxCheckBox Extends wfxControl
   private:
      _CheckState As CheckBoxState
      _ThreeState As boolean
      _TextAlign  As ButtonAlignment = ButtonAlignment.MiddleLeft
      
   Public:
      Declare Constructor( ByRef wszName As WString = "" )
      Declare Property CheckState() As CheckBoxState
      Declare Property CheckState( ByVal nValue As CheckBoxState )
      Declare Property ThreeState() As boolean
      Declare Property ThreeState( ByVal nValue As boolean )
      Declare Function GetTextAlignStyleValue( ByVal nValue As ButtonAlignment ) As Long
      Declare Property TextAlign() As ButtonAlignment
      Declare Property TextAlign( ByVal nValue As ButtonAlignment )
      declare function Show(byval hWndParent as hwnd = 0) as long override

      OnAllEvents        as function( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
      OnDestroy          as function( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
      OnGotFocus         as function( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
      OnLostFocus        as function( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
      OnMouseMove        as function( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
      OnMouseDown        as function( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
      OnMouseUp          as function( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
      OnMouseDoubleClick as function( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
      OnMouseEnter       as function( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
      OnMouseHover       as function( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
      OnMouseLeave       as function( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
      OnKeyDown          as function( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
      OnKeyPress         as function( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
      OnKeyUp            as function( byref sender as wfxCheckBox, byref e as EventArgs ) as LRESULT
      OnDropFiles        As Function( ByRef sender As wfxCheckBox, ByRef e As EventArgs ) As LRESULT
End Type

