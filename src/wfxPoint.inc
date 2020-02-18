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

constructor wfxPoint( byval xPos as long = 0, byval yPos as long = 0)
   this.x = xPos
   this.y = yPos
end constructor

property wfxPoint.x() as LONG
   property = _x
end property

property wfxPoint.x( byval nValue as long )
   _x = nValue
end property

property wfxPoint.y() as LONG
   property = _y
end property

property wfxPoint.y( byval nValue as long )
   _y = nValue
end property

function wfxPoint.IsEmpty() as Boolean
   function = iif(_x = 0 andalso _y = 0, true, false)
END FUNCTION
