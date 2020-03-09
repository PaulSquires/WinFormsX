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
''  Popup Menu Class
''

type wfxPopupMenu
   private:
      _hPopUpMenu As HMENU
      _hParentWindow as HWND 

   public:
      declare function AddItem( byref wszText as wstring, byval nResultCode as long ) as boolean
      declare function AddSeparator() as boolean
      declare function Handle () as HMENU
      declare function Create() as boolean
      declare function Destroy() as Long
      declare function Show( byval hParentWindow as HWND, byval xpos as long, byval ypos as long ) as Long
      declare function Show( byval hParentWindow as HWND, byval pt as POINT ) as Long
      declare function Show( byval hParentWindow as HWND, byval wpt as wfxPoint ) as Long
      declare constructor 
      declare destructor
END TYPE

