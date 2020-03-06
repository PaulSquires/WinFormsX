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
''  Point Class
''
''  https://msdn.microsoft.com/en-us/library/system.drawing.point(v=vs.110).aspx
''

type wfxPoint
   private:
      _pt as POINT 

   public:
      Declare Property x() As Long
      Declare Property x( ByVal nValue As Long )
      Declare Property y() As Long
      Declare Property y( ByVal nValue As Long )
      Declare Property pt() As POINT
      Declare Property pt( ByVal nValue As POINT )
      declare function IsEmpty() as Boolean
      declare function Convert( byval hWndFrom as HWND, byval hWndTo as HWND ) as Long
      declare function Convert( byval hWndTo as HWND ) as Long
      declare OPERATOR @() AS POINT ptr
      DECLARE OPERATOR LET (BYval nValue AS POINT)
      declare constructor ( byval xPos as long = 0, byval yPos as long = 0)
      declare constructor ( byval nValue as POINT )
      declare constructor 
END TYPE

