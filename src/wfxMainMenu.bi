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


type wfxMenuItem
   private:
      _hWindow     as hwnd
      _Index       as Long
      _Text        as CWSTR
      _Data32      as Long 
      _Selected    as boolean
     
   public:
      Declare Property hWindow() As hwnd
      Declare Property hWindow( ByVal nValue As hwnd)
      Declare Property Index() As long
      Declare Property Index( ByVal nValue As long)
      Declare Property Selected() As boolean
      Declare Property Selected( ByVal nValue As boolean)
      declare property Text() as CWSTR
      declare property Text( byref wszValue as wstring )
      Declare Property Data32() As long
      Declare Property Data32( ByVal nValue As long)
END TYPE

type wfxMenuItemsCollection
   private:
      _hWindow     as hwnd
      _Collection As wfxLList
      
   public:
      Declare Property hWindow() As hwnd
      Declare Property hWindow( ByVal nValue As hwnd)
      Declare function Clear() as long 
      Declare function Count() as long 
      Declare Function SelectedCount() As Long
      Declare Function Remove( ByVal nIndex As Long ) As Long 
      Declare Function Add( ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
      declare function ByIndex( byval nIndex as long ) byref as wfxMenuItem
      Declare Constructor
      declare destructor 
END TYPE

Type wfxMainMenu Extends wfxControl
   private:
      _TempItem As wfxMenuItem
      _SelectedItem as wfxMenuItem
      _SelectedIndex as Long = -1
      _ItemsCollection as wfxMenuItemsCollection
      _IsLoading as Boolean = true   ' internal
      
   Public:
      Declare Function Item( ByVal nIndex As Long) ByRef As wfxMenuItem
      declare function Items byref As wfxMenuItemsCollection
      Declare Property SelectedItem(byref as wfxMenuItem) 
      Declare Property SelectedItem() byref as wfxMenuItem
      Declare Property SelectedIndex() As long
      Declare Property SelectedIndex( ByVal nValue As long)
      
      Declare Constructor()
      declare function Show(byval hWndParent as hwnd = 0) as long override

      OnAllEvents        as function( byref sender as wfxMainMenu, byref e as EventArgs ) as LRESULT
      OnDestroy          as function( byref sender as wfxMainMenu, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxMainMenu, byref e as EventArgs ) as LRESULT
      OnMouseMove        as function( byref sender as wfxMainMenu, byref e as EventArgs ) as LRESULT
      OnMouseDown        as function( byref sender as wfxMainMenu, byref e as EventArgs ) as LRESULT
      OnMouseUp          as function( byref sender as wfxMainMenu, byref e as EventArgs ) as LRESULT
      OnMouseDoubleClick as function( byref sender as wfxMainMenu, byref e as EventArgs ) as LRESULT
      OnMouseEnter       as function( byref sender as wfxMainMenu, byref e as EventArgs ) as LRESULT
      OnMouseHover       as function( byref sender as wfxMainMenu, byref e as EventArgs ) as LRESULT
      OnMouseLeave       as function( byref sender as wfxMainMenu, byref e as EventArgs ) as LRESULT
      OnGotFocus         as function( byref sender as wfxMainMenu, byref e as EventArgs ) as LRESULT
      OnLostFocus        as function( byref sender as wfxMainMenu, byref e as EventArgs ) as LRESULT
      OnKeyDown          as function( byref sender as wfxMainMenu, byref e as EventArgs ) as LRESULT
      OnKeyUp            as function( byref sender as wfxMainMenu, byref e as EventArgs ) as LRESULT
      OnKeyPress         as function( byref sender as wfxMainMenu, byref e as EventArgs ) as LRESULT
      OnDropFiles        As Function( ByRef sender As wfxMainMenu, ByRef e As EventArgs ) As LRESULT
End Type

