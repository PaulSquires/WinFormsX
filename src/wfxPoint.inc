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

#include once "wfxPoint.bi"

constructor wfxPoint
end constructor

constructor wfxPoint( byval nValue as POINT )
   _pt = nValue
end constructor

constructor wfxPoint( byval xPos as long = 0, byval yPos as long = 0)
   _pt.x = xPos
   _pt.y = yPos
end constructor

OPERATOR wfxPoint.@ () AS POINT ptr
   OPERATOR = cast(POINT ptr, @_pt)
END OPERATOR

OPERATOR wfxPoint.Let (BYval nValue AS POINT)
   _pt = nValue
END OPERATOR

property wfxPoint.pt() as POINT
   property = _pt
end property

property wfxPoint.pt( byval nValue as POINT )
   _pt = nValue
end property

property wfxPoint.x() as LONG
   property = _pt.x
end property

property wfxPoint.x( byval nValue as long )
   _pt.x = nValue
end property

property wfxPoint.y() as LONG
   property = _pt.y
end property

property wfxPoint.y( byval nValue as long )
   _pt.y = nValue
end property

function wfxPoint.IsEmpty() as Boolean
   function = iif(_pt.x = 0 andalso _pt.y = 0, true, false)
END FUNCTION

function wfxPoint.Convert( byval hWndFrom as HWND, byval hWndTo as HWND ) as Long
   MapWindowPoints( hWndFrom, hWndTo, cast(point ptr, @_pt), 1)
   function = 0
end function

function wfxPoint.Convert( byval hWndTo as HWND ) as Long
   this.Convert( HWND_DESKTOP, hWndTo )
   function = 0
end function


