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

type wfxSize
   private:
      _Width   as Long
      _Height  as long 
      _hWindow as HWND
      
   public:
      Declare Property Width() As Long
      Declare Property Width( ByVal nValue As Long )
      Declare Property Height() As Long
      Declare Property Height( ByVal nValue As Long )
      Declare Property hWindow() As HWND
      Declare Property hWindow( ByVal nValue As HWND )
      declare function IsEmpty() as Boolean
      declare function Convert( byval hWin as HWND ) as Long
      declare constructor ( byval nWidth as long = 0, byval nHeight as long = 0)
      declare constructor ( byval hWin as HWND )
END TYPE

