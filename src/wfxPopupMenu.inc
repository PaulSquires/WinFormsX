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

#include once "wfxPopupMenu.bi"

   
constructor wfxPopupMenu
   this.Create()
end constructor

destructor wfxPopupMenu
   ' Destroy the popup menu 
   this.Destroy()
end destructor

function wfxPopupMenu.AddItem( byref wszText as wstring, byval nResultCode as long ) as boolean
   return AppendMenu( _hPopUpMenu, MF_ENABLED or MF_STRING, nResultCode, wszText )
end function

function wfxPopupMenu.AddSeparator() as boolean
   return AppendMenu( _hPopUpMenu, MF_ENABLED or MF_SEPARATOR, 0, "" )
end function

function wfxPopupMenu.Show( byval hParentWindow as HWND, byval pt as POINT ) as Long
   ' Display the popup menu and receive the selected item. We use the TPM_RETURNCMD flag
   ' to retrieve the result here rather than have to get it from the parent Form handler.
   if _hPopUpMenu = 0 then return -1
   
   ' Per WinAPI docs:
   ' We specify TPM_NONOTIFY in the uFlags parameter, the function does not send messages 
   ' to the window identified by hWnd. However, you must still pass a window handle in hWnd. 
   ' It can be any window handle from your application.
   
   function = _
      TrackPopupMenu( _hPopUpMenu, TPM_RETURNCMD or TPM_NONOTIFY or TPM_NOANIMATION, _
                        pt.x, pt.y, 0, hParentWindow, ByVal Null )
end function

function wfxPopupMenu.Show( byval hParentWindow as HWND, byval wpt as wfxPoint) as Long
   return this.Show( hParentWindow, wpt.pt )
end function   

function wfxPopupMenu.Show( byval hParentWindow as HWND, byval xpos as long, byval ypos as long ) as Long
   dim pt as POINT
   pt.x = xpos: pt.y = ypos
   return this.Show( hParentWindow, pt )
end function   

function wfxPopupMenu.Handle() as HMENU
   return _hPopUpMenu 
end function

function wfxPopupMenu.Create() as boolean
   ' Create the menu if doesn't already exist
   if _hPopupMenu = 0 then _hPopUpMenu = CreatePopupMenu()
   if _hPopupMenu then return true
end function
   
function wfxPopupMenu.Destroy() as Long
  if _hPopUpMenu then DestroyMenu( _hPopUpMenu )
  _hPopUpMenu = 0
  function = 0 
end function

