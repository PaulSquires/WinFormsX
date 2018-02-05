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


type wfxForm_ as wfxForm    ' forward reference

Type wfxControl Extends Object
   private:
      _CtrlType   As Long
      _CtrlName   As CWSTR
      _CtrlID     As Long
      _Text       as CWSTR
      _Size       as wfxSize 
      _Position   as wfxPoint
      _Parent     as wfxForm_ ptr
      _hWindow    as hwnd
      _Selected   as Boolean = False
      _Enabled    as Boolean = True
      _Visible    as Boolean = True
      _TabStop    as boolean = true
      _Background as COLORREF = Colors.SystemButtonFace
      _hBackBrush as HBRUSH = CreateSolidBrush(Colors.SystemButtonFace)
      _Foreground as COLORREF = Colors.SystemWindowText
      
   Public:
      Declare Property hWindow() As hwnd
      Declare Property hWindow( ByVal nValue as hwnd )
      Declare Property CtrlType() As Long
      Declare Property CtrlType( ByVal nValue As Long )
      Declare Property Name() As CWSTR 
      Declare Property Name( ByRef cwzValue As wstring )
      Declare Property Selected() As boolean
      Declare Property Selected( ByVal nValue As Boolean)
      Declare Property CtrlID() As Long
      Declare Property CtrlID( ByVal nValue As Long )
      Declare Property hBackBrush() As HBRUSH   ' internal get
      Declare Property Background() As COLORREF
      Declare Property Background( ByVal nValue As COLORREF )
      Declare Property Foreground() As COLORREF
      Declare Property Foreground( ByVal nValue As COLORREF )
      Declare Property Enabled() As boolean
      Declare Property Enabled( ByVal nValue As Boolean)
      Declare Property Visible() As boolean
      Declare Property Visible( ByVal nValue As Boolean)
      Declare Property TabStop() As boolean
      Declare Property TabStop( ByVal nValue As Boolean)
      Declare Property Text() As CWSTR
      Declare Property Text( byref nValue as wstring )
      Declare Property Left() As Long
      Declare Property Left( ByVal nValue As Long )
      Declare Property Top() As Long
      Declare Property Top( ByVal nValue As Long )
      Declare Property Width() As Long
      Declare Property Width( ByVal nValue As Long )
      Declare Property Height() As Long
      Declare Property Height( ByVal nValue As Long )
      Declare Property Size() As wfxSize
      declare property Size( byval nWidth as long, byval nHeight as long )
      Declare Property Position() As wfxPoint
      declare property Position( byval xPos as long, byval yPos as long )
      Declare Property Parent() As wfxForm_ ptr
      Declare Property Parent( ByVal pForm as wfxForm_ ptr )
      declare function Refresh() as long
      declare function SetBounds( byval xPos as long, byval yPos as long, byval nWidth as long, byval nHeight as long ) as long
      declare function Hide() As long
      declare abstract function Show(byval hWndParent as hwnd = 0) as long

   Protected:
      declare constructor ()
      Declare Constructor ( ByRef rhs As wfxControl ) '' to avoid user copy-construction from root
      declare destructor ()
End Type

