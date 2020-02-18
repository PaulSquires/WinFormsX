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


Type wfxMaskedEdit Extends wfxControl
      _MaskedEditPtr    As CMaskedEdit Ptr
      _BorderStyle      As ControlBorderStyle = ControlBorderStyle.Fixed3D
      _HideSelection    As boolean = True
      _ReadOnly         As boolean = False
      _DefaultCharacter As CWSTR = "_"
      _ValidCharacters  As CWSTR
      _MaskString       As CWSTR
      _InputString      As CWSTR
       
   Public:
      Declare Property BorderStyle() As ControlBorderStyle
      Declare Property BorderStyle( ByVal nValue As ControlBorderStyle )
      Declare Property HideSelection() As boolean
      Declare Property HideSelection( ByVal nValue As boolean )
      Declare Property ReadOnly() As boolean
      Declare Property ReadOnly( ByVal nValue As boolean )
      Declare Property MaskString() As CWSTR
      Declare Property MaskString( ByRef nValue As WString )
      Declare Property InputString() As CWSTR
      Declare Property InputString( ByRef nValue As WString )
      Declare Property DefaultCharacter() As CWSTR
      Declare Property DefaultCharacter( ByRef nValue As WString )
      Declare Property ValidCharacters() As CWSTR
      Declare Property ValidCharacters( ByRef nValue As WString )

      Declare Function GenerateMask() As Long
      Declare Function GetText( ByVal bGetMaskedCharsOnly As Boolean = False ) As CWSTR
      Declare Function SetText( ByRef nValue As WString, ByVal bSetMaskedCharsOnly As Boolean = False ) As Long

      Declare Function Show(ByVal hWndParent As HWnd = 0) As Long Override
      Declare Constructor( byref wszName as wstring = "" )
      Declare destructor

      OnAllEvents        as function( byref sender as wfxMaskedEdit, byref e as EventArgs ) as LRESULT
      OnDestroy          as function( byref sender as wfxMaskedEdit, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxMaskedEdit, byref e as EventArgs ) as LRESULT
      OnGotFocus         as function( byref sender as wfxMaskedEdit, byref e as EventArgs ) as LRESULT
      OnLostFocus        as function( byref sender as wfxMaskedEdit, byref e as EventArgs ) as LRESULT
      OnMouseMove        as function( byref sender as wfxMaskedEdit, byref e as EventArgs ) as LRESULT
      OnMouseDown        as function( byref sender as wfxMaskedEdit, byref e as EventArgs ) as LRESULT
      OnMouseUp          as function( byref sender as wfxMaskedEdit, byref e as EventArgs ) as LRESULT
      OnMouseDoubleClick as function( byref sender as wfxMaskedEdit, byref e as EventArgs ) as LRESULT
      OnMouseEnter       as function( byref sender as wfxMaskedEdit, byref e as EventArgs ) as LRESULT
      OnMouseHover       as function( byref sender as wfxMaskedEdit, byref e as EventArgs ) as LRESULT
      OnMouseLeave       as function( byref sender as wfxMaskedEdit, byref e as EventArgs ) as LRESULT
      OnTextChanged      As Function( ByRef sender As wfxMaskedEdit, ByRef e As EventArgs ) As LRESULT
      OnKeyDown          As Function( ByRef sender As wfxMaskedEdit, ByRef e As EventArgs ) As LRESULT
      OnKeyPress         as function( byref sender as wfxMaskedEdit, byref e as EventArgs ) as LRESULT
      OnKeyUp            as function( byref sender as wfxMaskedEdit, byref e as EventArgs ) as LRESULT
      OnDropFiles        As Function( ByRef sender As wfxMaskedEdit, ByRef e As EventArgs ) As LRESULT
End Type

