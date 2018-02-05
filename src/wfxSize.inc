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

''
''  Size Class
''
''  https://msdn.microsoft.com/en-us/library/system.drawing.size(v=vs.110).aspx
''

constructor wfxSize( byval nWidth as long = 0, byval nHeight as long = 0)
   this.Width = nWidth
   this.Height = nHeight
end constructor

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
