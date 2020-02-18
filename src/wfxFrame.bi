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
''  Frame Class
''
''


Type wfxFrame Extends wfxControl
   private:
      _UseMnemonic As Boolean = True    
      
   Public:
      Declare Constructor( byref wszName as wstring = "" )
      Declare Property UseMnemonic() As boolean
      Declare Property UseMnemonic( ByVal nValue As boolean )
      declare function Show(byval hWndParent as hwnd = 0) as long override

      OnAllEvents        as function( byref sender as wfxFrame, byref e as EventArgs ) as LRESULT
      OnDestroy          as function( byref sender as wfxFrame, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxFrame, byref e as EventArgs ) as LRESULT
      OnMouseMove        as function( byref sender as wfxFrame, byref e as EventArgs ) as LRESULT
      OnMouseDown        as function( byref sender as wfxFrame, byref e as EventArgs ) as LRESULT
      OnMouseUp          as function( byref sender as wfxFrame, byref e as EventArgs ) as LRESULT
      OnMouseDoubleClick as function( byref sender as wfxFrame, byref e as EventArgs ) as LRESULT
      OnMouseEnter       as function( byref sender as wfxFrame, byref e as EventArgs ) as LRESULT
      OnMouseHover       as function( byref sender as wfxFrame, byref e as EventArgs ) as LRESULT
      OnMouseLeave       as function( byref sender as wfxFrame, byref e as EventArgs ) as LRESULT
      OnDropFiles        As Function( ByRef sender As wfxFrame, ByRef e As EventArgs ) As LRESULT

End Type

