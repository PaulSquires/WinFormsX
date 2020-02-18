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
''  wfxToolBar Class
''

enum ToolBarButton
   Button
   Separator
   DropDown
   WholeDropDown
end enum

type wfxToolBarButton
   private:
      _hWindow       as hwnd
      _Index         as Long
      _ButtonType    as ToolBarButton
      _ToolTip       as CWSTR
      _NormalImage   as wstring * MAX_PATH
      _HotImage      as wstring * MAX_PATH
      _DisabledImage as wstring * MAX_PATH
      _Enabled       as boolean
      _CtrlID        as long = 100
      
   public:
      Declare Property hWindow() As hwnd
      Declare Property hWindow( ByVal nValue As hwnd)
      Declare Property Index() As long
      Declare Property Index( ByVal nValue As long)
      declare property ButtonType() as ToolBarButton
      declare property ButtonType( byval nValue as ToolBarButton )
      declare property ToolTip() as CWSTR
      declare property ToolTip( byref wszValue as wstring )
      declare property NormalImage() as CWSTR
      declare property NormalImage( byref cwzValue as wstring )
      declare property HotImage() as CWSTR
      declare property HotImage( byref cwzValue as wstring )
      declare property DisabledImage() as CWSTR
      declare property DisabledImage( byref cwzValue as wstring )
      Declare Property Enabled() As boolean
      Declare Property Enabled( ByVal nValue As boolean)

END TYPE

type wfxToolBarButtonsCollection
   private:
      _hWindow     as hwnd
      _Collection As wfxLList
      
   public:
      Declare Property hWindow() As hwnd
      Declare Property hWindow( ByVal nValue As hwnd)
      declare function Clear() as Long
      Declare function Count() as long 
      declare function Add() as long 
      declare function ByIndex( byval nIndex as long ) byref as wfxToolBarButton
      Declare Constructor
      declare destructor 
END TYPE

type wfxToolBar extends wfxControl
   private:
      _hWindow    as hwnd
      _hRebar     as hwnd
      _ButtonSize as long = 24
      _ButtonsCollection as wfxToolBarButtonsCollection
      _ClickIndex as Long
      _ClickDropDownIndex as Long
         
   public:
      Declare function Button( byval nIndex as long) byref as wfxToolBarButton
      declare function Buttons byref As wfxToolBarButtonsCollection
      
      Declare Property hWindow() As hwnd
      Declare Property hWindow( ByVal nValue As hwnd)
      Declare Property hRebar() As hwnd
      Declare Property hRebar( ByVal nValue As hwnd)
      declare property ButtonSize() as Long
      Declare Property ButtonSize( ByVal nValue As long)
      Declare Property ClickIndex() As long
      Declare Property ClickIndex( ByVal nValue As long)
      Declare Property ClickDropDownIndex() As long
      Declare Property ClickDropDownIndex( ByVal nValue As long)
      
      declare function Show(byval hWndParent as hwnd = 0) as long override
      Declare Constructor
      declare destructor 

      OnAllEvents        as function( byref sender as wfxToolBar, byref e as EventArgs ) as LRESULT
      OnDestroy          as function( byref sender as wfxToolBar, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxToolBar, byref e as EventArgs ) as LRESULT
      OnMouseMove        as function( byref sender as wfxToolBar, byref e as EventArgs ) as LRESULT
      OnMouseDown        as function( byref sender as wfxToolBar, byref e as EventArgs ) as LRESULT
      OnMouseUp          as function( byref sender as wfxToolBar, byref e as EventArgs ) as LRESULT
      OnMouseDoubleClick as function( byref sender as wfxToolBar, byref e as EventArgs ) as LRESULT
      OnMouseEnter       as function( byref sender as wfxToolBar, byref e as EventArgs ) as LRESULT
      OnMouseHover       as function( byref sender as wfxToolBar, byref e as EventArgs ) as LRESULT
      OnMouseLeave       as function( byref sender as wfxToolBar, byref e as EventArgs ) as LRESULT
      OnDropFiles        As Function( ByRef sender As wfxToolBar, ByRef e As EventArgs ) As LRESULT
   
END TYPE



