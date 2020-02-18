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

type _wfxMainMenu as wfxMainMenu
type _wfxMenuItem as wfxMenuItem


type wfxMenuItemsCollection
   private:
      _Handle     as HMENU
      _Collection As wfxLList
      
   public:
      Declare Property Handle() As HMENU
      Declare Property Handle( ByVal nValue As HMENU)
      Declare function Clear() as long 
      Declare function Count() as long 
      Declare Function Remove( ByVal nIndex As Long ) As Long 
      declare Function Add( ByRef tMenuItem As _wfxMenuItem ) As Long
      declare function ByIndex( byval nIndex as long ) byref as _wfxMenuItem
      Declare Constructor()
      declare destructor() 
END TYPE


type wfxMenuItem 
   private:
      _Handle          as HMENU
      _PopupMenuHandle as HMENU
      _MenuParent      as _wfxMainMenu ptr
      _Index           as Long
      _Selected        as boolean
      _Text            as CWSTR
      _Name            as CWSTR
      _MenuID          as Long
      _Shortcut        as CWSTR
      _Checked         as boolean
      _Grayed          as boolean
      _Enabled         as boolean
      _IsParent        as boolean
      _ItemsCollection as wfxMenuItemsCollection
     
   public:
      declare constructor( ByRef wszText     As WString = "", _
                           ByRef wszName     As WString = "", _ 
                           Byref wszShortcut As WString = "", _
                           ByVal bChecked    As boolean = false, _
                           ByVal bGrayed     As boolean = false )
      declare destructor()
      Declare Function MenuItem( ByVal nIndex As Long) ByRef As wfxMenuItem
      declare function MenuItems byref As wfxMenuItemsCollection
      Declare Property Handle() As HMENU   ' mainmenu handle
      Declare Property Handle( ByVal nValue As HMENU)
      Declare Property PopupMenuHandle() As HMENU   ' menuitem handle to child popup menu
      Declare Property PopupMenuHandle( ByVal nValue As HMENU)
      Declare Property MenuParent() As _wfxMainMenu ptr
      Declare Property MenuParent( Byval pValue As _wfxMainMenu ptr)
      Declare Property Index() As long
      Declare Property Index( ByVal nValue As long)
      Declare Property IsParent() As boolean
      Declare Property IsParent( byval nValue as boolean)
      Declare Property Selected() As boolean
      Declare Property Selected( ByVal nValue As boolean)
      
      declare property Text() as CWSTR
      declare property Text( byref wszValue as wstring )
      declare property Name() as CWSTR
      declare property Name( byref wszValue as wstring )
      Declare Property MenuID() As long
      Declare Property MenuID( ByVal nValue As long)
      Declare Property Checked() As boolean
      Declare Property Checked( ByVal nValue As boolean)
      Declare Property Grayed() As boolean
      Declare Property Grayed( ByVal nValue As boolean)
      Declare Property Enabled() As boolean
      Declare Property Enabled( ByVal nValue As boolean)
      Declare Property Shortcut() As CWSTR
      Declare Property Shortcut( byref wszValue as wstring)

END TYPE

Type wfxMainMenu Extends wfxControl
   private:
      _Handle as HMENU = 0
      _SelectedItem as wfxMenuItem
      _SelectedIndex as Long = -1
      _ItemsCollection as wfxMenuItemsCollection
      _IsLoading as Boolean   ' private
      
   Public:
      Declare Function MenuItem( ByVal nIndex As Long) ByRef As wfxMenuItem
      declare function MenuItems byref As wfxMenuItemsCollection
      Declare Property Handle() As HMENU
      Declare Property Handle( ByVal nValue As HMENU)
      Declare Property IsLoading() As boolean
      Declare Property IsLoading( ByVal nValue As boolean)
      Declare Property SelectedItem(byref as wfxMenuItem) 
      Declare Property SelectedItem() byref as wfxMenuItem
      Declare Property SelectedIndex() As long
      Declare Property SelectedIndex( ByVal nValue As long)
      declare function CreateMenuStructure_Internal(byval hSubMenu as HMENU, byref tMenuItem as _wfxMenuItem) as long
      declare function ByMenuID( byval nMenuID as long ) byref as _wfxMenuItem
      declare function GetByMenuID_Internal( byval nMenuID as long, byval pMenuItem as _wfxMenuItem ptr) as _wfxMenuItem ptr
      declare function ByMenuName( byref wszMenuName as wstring ) byref as _wfxMenuItem
      declare function GetByMenuName_Internal( byref wszMenuName as wstring, byval pMenuItem as _wfxMenuItem ptr) as _wfxMenuItem ptr
      declare function ByPopupMenuHandle( byval hPopupMenu as HMENU ) byref as _wfxMenuItem
      declare function GetByPopupMenuHandle_Internal( byval hPopupMenu as HMENU, byval pMenuItem as _wfxMenuItem ptr) as _wfxMenuItem ptr
      
      Declare Constructor()
      declare destructor()
      declare function Show(byval hWndParent as hwnd = 0) as long override

      ' Events are generated by WinFBE
      OnAllEvents        as function( byref sender as wfxMenuItem, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxMenuItem, byref e as EventArgs ) as LRESULT
      OnPopup            as function( byref sender as wfxMenuItem, byref e as EventArgs ) as LRESULT
End Type

