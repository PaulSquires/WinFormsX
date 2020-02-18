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

' TabControl Class


type wfxTabPage
   private:
      _hWindow          as hwnd   ' hwnd of TabControl itself
      _Index            as Long
      _Text             as CWSTR
      _ChildFormName    as CWSTR
      _ChildForm        as wfxForm
      _hWindowChildForm as HWND
      _Image            as CWSTR
      _Data32           as Long 
      _Selected         as boolean
     
   public:
      Declare Property hWindow() As hwnd
      Declare Property hWindow( ByVal nValue As hwnd)
      Declare Property Index() As long
      Declare Property Index( ByVal nValue As long)
      Declare Property Selected() As boolean
      Declare Property Selected( ByVal nValue As boolean)
      declare property Text() as CWSTR
      declare property Text( byref wszValue as wstring )
      declare property ChildFormName() as CWSTR
      declare property ChildFormName( byref wszValue as wstring )
      Declare Property hWindowChildForm() As hwnd
      Declare Property hWindowChildForm( ByVal nValue As hwnd)
      declare property Image() as CWSTR
      declare property Image( byref wszValue as wstring )
      Declare Property Data32() As long
      Declare Property Data32( ByVal nValue As long)
END TYPE

type wfxTabPageCollection
   private:
      _hWindow     as hwnd
      _Collection As wfxLList
      
   public:
      SelectedIndex as Long
      hImageList as HANDLE
      Declare Property hWindow() As hwnd
      Declare Property hWindow( ByVal nValue As hwnd)
      Declare function Clear() as long 
      Declare function Count() as long 
      Declare Function Remove( ByVal nIndex As Long ) As Long 
      Declare Function Add( ByRef wszText As WString = "", _
                            ByRef wszTabPage As WString = "", _
                            ByRef wszImage As WString = "", _
                            ByVal nValue As Long = 0) As Long
      Declare Function Insert( byval nIndex as long, _
                            ByRef wszText As WString = "", _
                            ByRef wszTabPage As WString = "", _
                            ByRef wszImage As WString = "", _
                            ByVal nValue As Long = 0) As Long
      declare function ByIndex( byval nIndex as long ) byref as wfxTabPage
      declare function CreateTabPageInternal( byval i as long ) as Long
      Declare Constructor
      declare destructor 
END TYPE

Type wfxTabControl Extends wfxControl
   private:
      _TabPageCollection as wfxTabPageCollection
      _AllowFocus as Boolean = true
      _TabHeight as long = 24
      _TabWidth as long = 100
      _BorderStyle As ControlBorderStyle = ControlBorderStyle.None
      _IsLoading as Boolean = true   ' internal
      _ResizeTabPages as Boolean = true   
      _TabImageSize as ControlImageSize = ControlImageSize.Size16
      _ForceImageLeft as Boolean = false
      _ForceLabelLeft as Boolean = false
      _TabTopPadding as long = 4
      _TabSidePadding as long = 4
      _ButtonStyle as Boolean = false
      _FixedWidthTabs as Boolean = false
      _HotTracking as Boolean = true
      _MultiLine as Boolean = false
      
   Public:
      Declare Property AllowFocus() As boolean
      Declare Property AllowFocus( ByVal nValue As boolean)
      Declare Property hImageList() As HANDLE
      Declare Property hImageList( ByVal nValue As HANDLE)
      Declare Property MultiLine() As boolean
      Declare Property MultiLine( ByVal nValue As boolean)
      Declare Property HotTracking() As boolean
      Declare Property HotTracking( ByVal nValue As boolean)
      Declare Property FixedWidthTabs() As boolean
      Declare Property FixedWidthTabs( ByVal nValue As boolean)
      Declare Property ButtonStyle() As boolean
      Declare Property ButtonStyle( ByVal nValue As boolean)
      Declare Property ForceImageLeft() As boolean
      Declare Property ForceImageLeft( ByVal nValue As boolean)
      Declare Property ForceLabelLeft() As boolean
      Declare Property ForceLabelLeft( ByVal nValue As boolean)
      Declare Property ResizeTabPages() As boolean
      Declare Property ResizeTabPages( ByVal nValue As boolean)
      Declare Property SelectedIndex() As long
      Declare Property SelectedIndex( ByVal nValue As long)
      Declare Property TabTopPadding() As long
      Declare Property TabTopPadding( ByVal nValue As long)
      Declare Property TabSidePadding() As long
      Declare Property TabSidePadding( ByVal nValue As long)
      Declare Property TabImageSize() As ControlImageSize
      Declare Property TabImageSize( ByVal nValue As ControlImageSize)
      Declare Property TabHeight() As long
      Declare Property TabHeight( ByVal nValue As long)
      Declare Property TabWidth() As long
      Declare Property TabWidth( ByVal nValue As long)
      Declare Function TabPage( ByVal nIndex As Long) ByRef As wfxTabPage
      declare function TabPages byref As wfxTabPageCollection
      Declare Property BorderStyle() As ControlBorderStyle
      Declare Property BorderStyle( ByVal nValue As ControlBorderStyle )
      
      Declare Constructor( byref wszName as wstring = "" )
      declare destructor
      declare function Show(byval hWndParent as hwnd = 0) as long override
      declare function ShowTabPage( byval nIndex as long ) as long
      declare function HideTabPage( byval nIndex as long ) as long
      declare function AutoResizeTabPages() as long
      
      OnAllEvents        as function( byref sender as wfxTabControl, byref e as EventArgs ) as LRESULT
      OnDestroy          as function( byref sender as wfxTabControl, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxTabControl, byref e as EventArgs ) as LRESULT
      OnMouseMove        as function( byref sender as wfxTabControl, byref e as EventArgs ) as LRESULT
      OnMouseDown        as function( byref sender as wfxTabControl, byref e as EventArgs ) as LRESULT
      OnMouseUp          as function( byref sender as wfxTabControl, byref e as EventArgs ) as LRESULT
      OnMouseDoubleClick as function( byref sender as wfxTabControl, byref e as EventArgs ) as LRESULT
      OnMouseEnter       as function( byref sender as wfxTabControl, byref e as EventArgs ) as LRESULT
      OnMouseHover       as function( byref sender as wfxTabControl, byref e as EventArgs ) as LRESULT
      OnMouseLeave       as function( byref sender as wfxTabControl, byref e as EventArgs ) as LRESULT
      OnGotFocus         as function( byref sender as wfxTabControl, byref e as EventArgs ) as LRESULT
      OnLostFocus        as function( byref sender as wfxTabControl, byref e as EventArgs ) as LRESULT
      OnKeyDown          as function( byref sender as wfxTabControl, byref e as EventArgs ) as LRESULT
      OnKeyUp            as function( byref sender as wfxTabControl, byref e as EventArgs ) as LRESULT
      OnKeyPress         as function( byref sender as wfxTabControl, byref e as EventArgs ) as LRESULT
      OnSelecting        as function( byref sender as wfxTabControl, byref e as EventArgs ) as LRESULT
      OnSelected         as function( byref sender as wfxTabControl, byref e as EventArgs ) as LRESULT
      OnDropFiles        As Function( ByRef sender As wfxTabControl, ByRef e As EventArgs ) As LRESULT
End Type

