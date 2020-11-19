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
''  PictureBox Class
''
''


Type wfxPictureBox Extends wfxControl
   private:
      _ImageCtxPtr As CImageCtx Ptr
      _Image          as wstring * MAX_PATH
      _ImageWidth     as Long = 0
      _ImageHeight    as Long = 0
      _ImageScaling   as ImageScale = ImageScale.AutoSize
      _BackColor      as COLORREF = Colors.SystemWindow
      _BackColorHot   as COLORREF = Colors.SystemWindow
   
   Public:
      declare property Image() as CWSTR
      declare property Image( byref wszValue as wstring )
      declare property ImageWidth( byval nValue as Long )
      declare property ImageWidth() as Long
      declare property ImageHeight( byval nValue as Long )
      declare property ImageHeight() as Long
      declare property ImageScaling( byval nValue as ImageScale )
      declare property ImageScaling() as ImageScale
      declare Property BackColor( ByVal nValue As COLORREF )
      declare Property BackColor() as COLORREF
      declare Property BackColorHot( ByVal nValue As COLORREF )
      declare Property BackColorHot() as COLORREF

      declare property ImageFromFile( byref wszValue as wstring )
      
      declare function Show(byval hWndParent as hwnd = 0) as long override
      Declare Constructor( byref wszName as wstring = "" )
      Declare destructor

      OnAllEvents        as function( byref sender as wfxPictureBox, byref e as EventArgs ) as LRESULT
      OnDestroy          as function( byref sender as wfxPictureBox, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxPictureBox, byref e as EventArgs ) as LRESULT
      OnMouseMove        as function( byref sender as wfxPictureBox, byref e as EventArgs ) as LRESULT
      OnMouseDown        as function( byref sender as wfxPictureBox, byref e as EventArgs ) as LRESULT
      OnMouseUp          as function( byref sender as wfxPictureBox, byref e as EventArgs ) as LRESULT
      OnMouseDoubleClick as function( byref sender as wfxPictureBox, byref e as EventArgs ) as LRESULT
      OnMouseEnter       as function( byref sender as wfxPictureBox, byref e as EventArgs ) as LRESULT
      OnMouseHover       as function( byref sender as wfxPictureBox, byref e as EventArgs ) as LRESULT
      OnMouseLeave       as function( byref sender as wfxPictureBox, byref e as EventArgs ) as LRESULT
      OnDropFiles        As Function( ByRef sender As wfxPictureBox, ByRef e As EventArgs ) As LRESULT

End Type

