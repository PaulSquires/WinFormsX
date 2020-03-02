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
''  Size Class
''
''  https://msdn.microsoft.com/en-us/library/system.drawing.size(v=vs.110).aspx
''

#include once "wfxSize.bi"

constructor wfxSize( byval nWidth as long = 0, byval nHeight as long = 0)
   _Width = nWidth
   _Height = nHeight
end constructor

constructor wfxSize( byval hWin as HWND )
   this.Convert(hWin)
end constructor

function wfxSize.Convert( byval hWin as HWND ) as Long
   if IsWindow(hWin) then
      _hWindow = hWin
      _Width = AfxGetWindowWidth(hWin)
      _Height = AfxGetWindowHeight(hWin)
   end if
   function = 0
end function

Property wfxSize.hWindow() As HWND
   property = _hWindow
end property

Property wfxSize.hWindow( ByVal nValue As HWND )
   this.Convert(nValue)
end property

property wfxSize.Width() as LONG
   property = _Width
end property

property wfxSize.Width( byval nValue as long )
   _Width = nValue
end property

property wfxSize.Height() as LONG
   property = _Height
end property

property wfxSize.Height( byval nValue as long )
   _Height = nValue
end property

function wfxSize.IsEmpty() as Boolean
   function = iif(_Width = 0 andalso _Height = 0, true, false)
END FUNCTION
