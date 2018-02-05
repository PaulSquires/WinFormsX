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
