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


Type wfxTextBox Extends wfxControl
      _TextAlign       As TextAlignment = TextAlignment.Left
      _BorderStyle     As ControlBorderStyle = ControlBorderStyle.Fixed3D
      _CharacterCasing As CharacterCase = CharacterCase.Normal
      _TextScrollBars  As ScrollBars = ScrollBars.None
      _HideSelection   As boolean = True
      _Multiline       As Boolean = False
      _WordWrap        As Boolean = False
      _AcceptsReturn   As boolean = False
      _AcceptsTab      As boolean = False
      _ReadOnly        As boolean = False
      _PasswordChar    As wstring * 10
      _CueBannerText   As wstring * MAX_PATH
      _LinePosition    as long = 0
      _ColumnPosition  as long = 0
      _MaxLength       as long = 32767
       
   Public:
      Declare Property MaxLength() As long
      Declare Property MaxLength( ByVal nValue As long )
      Declare Property TextAlign() As TextAlignment
      Declare Property TextAlign( ByVal nValue As TextAlignment)
      Declare Property BorderStyle() As ControlBorderStyle
      Declare Property BorderStyle( ByVal nValue As ControlBorderStyle )
      Declare Property TextScrollBars() As ScrollBars
      Declare Property TextScrollBars( ByVal nValue As ScrollBars )
      Declare Property CueBannerText() As CWSTR
      Declare Property CueBannerText( ByRef nValue As WString )
      Declare Property PasswordChar() As CWSTR
      Declare Property PasswordChar( ByRef nValue As WString )
      Declare Property Multiline() As boolean
      Declare Property Multiline( ByVal nValue As boolean )
      Declare Property CharacterCasing() As CharacterCase
      Declare Property CharacterCasing( ByVal nValue As CharacterCase )
      Declare Property ReadOnly() As boolean
      Declare Property ReadOnly( ByVal nValue As boolean )
      Declare Property AcceptsReturn() As boolean
      Declare Property AcceptsReturn( ByVal nValue As boolean )
      Declare Property AcceptsTab() As boolean
      Declare Property AcceptsTab( ByVal nValue As boolean )
      Declare Property HideSelection() As boolean
      Declare Property HideSelection( ByVal nValue As boolean )
      Declare Property WordWrap() As boolean
      declare property WordWrap( byval nValue as boolean )
      Declare Property SelectionStart() As Long
      Declare Property SelectionStart( ByVal nValue As Long )
      Declare Property SelectionLength() As Long
      Declare Property SelectionLength( ByVal nValue As Long )
      Declare Property LinePosition() As Long
      Declare Property LinePosition( ByVal nValue As Long )
      Declare Property ColumnPosition() As Long
      Declare Property ColumnPosition( ByVal nValue As Long )

      Declare Function Show(ByVal hWndParent As HWnd = 0) As Long Override
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
      OnTextChanged      As Function( ByRef sender As wfxTextBox, ByRef e As EventArgs ) As LRESULT
      OnKeyDown          As Function( ByRef sender As wfxTextBox, ByRef e As EventArgs ) As LRESULT
      OnKeyPress         as function( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
      OnKeyUp            as function( byref sender as wfxTextBox, byref e as EventArgs ) as LRESULT
      OnDropFiles        As Function( ByRef sender As wfxTextBox, ByRef e As EventArgs ) As LRESULT
End Type

