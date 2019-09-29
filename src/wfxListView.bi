'    WinFormsX - Windows GUI Framework for the FreeBASIC Compiler
'    Copyright (C) 2018-2019 Paul Squires, PlanetSquires Software
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

' ListView Class


'type wfxListBoxItem
'   private:
'      _hWindow     as hwnd
'      _Index       as Long
'      _Text        as CWSTR
'      _Data32      as Long 
'      _Selected    as boolean
      
'   public:
'      Declare Property hWindow() As hwnd
'      Declare Property hWindow( ByVal nValue As hwnd)
'      Declare Property Index() As long
'      Declare Property Index( ByVal nValue As long)
'      Declare Property Selected() As boolean
'      Declare Property Selected( ByVal nValue As boolean)
'      declare property Text() as CWSTR
'      declare property Text( byref wszValue as wstring )
'      Declare Property Data32() As long
'      Declare Property Data32( ByVal nValue As long)
'END TYPE

'type wfxListBoxItemsCollection
'   private:
'      _hWindow     as hwnd
'      _Collection As wfxLList
       
'   public:
'      Declare Property hWindow() As hwnd
'      Declare Property hWindow( ByVal nValue As hwnd)
'      Declare function Clear() as long 
'      Declare function Count() as long 
'      Declare Function SelectedCount() As Long
'      Declare Function Remove( ByVal nIndex As Long ) As Long 
'      Declare Function Add( ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
'      declare function ByIndex( byval nIndex as long ) byref as wfxListBoxItem
'      Declare Constructor
'      declare destructor 
'END TYPE

Type wfxListView Extends wfxControl
   private:
'      _TempItem As wfxListBoxItem
      _AllowColumnReorder As boolean = false 
      _BorderStyle As ControlBorderStyle = ControlBorderStyle.Fixed3D
      _CheckBoxes as Boolean = false
      _FullRowSelect as Boolean = true
      _GridLines as Boolean = false
      _HideSelection as Boolean = false
      _HeaderStyle as ColumnHeaderStyle = ColumnHeaderStyle.Clickable
      _LabelEdit As boolean = false
      _MultiSelect As boolean = false
'      _SelectedItem as wfxListBoxItem
'      _SelectedIndex as Long = -1
      _Sorting as SortOrder = SortOrder.None
'      _ItemsCollection as wfxListBoxItemsCollection
      _IsLoading as Boolean = true   ' internal
      
   Public:
'      Declare Function Item( ByVal nIndex As Long) ByRef As wfxListBoxItem
'      declare function Items byref As wfxListBoxItemsCollection
      Declare Property AllowColumnReorder() As boolean
      Declare Property AllowColumnReorder( ByVal nValue As boolean)
      Declare Property BorderStyle() As ControlBorderStyle
      Declare Property BorderStyle( ByVal nValue As ControlBorderStyle )
      Declare Property CheckBoxes() As boolean
      Declare Property CheckBoxes( ByVal nValue As boolean)
      Declare Property FullRowSelect() As boolean
      Declare Property FullRowSelect( ByVal nValue As boolean)
      Declare Property GridLines() As boolean
      Declare Property GridLines( ByVal nValue As boolean)
      Declare Property HideSelection() As boolean
      Declare Property HideSelection( ByVal nValue As boolean)
      Declare Property HeaderStyle() As ColumnHeaderStyle
      Declare Property HeaderStyle( ByVal nValue As ColumnHeaderStyle )
      Declare Property LabelEdit() As boolean
      Declare Property LabelEdit( ByVal nValue As boolean)
      Declare Property MultiSelect() As boolean
      Declare Property MultiSelect( ByVal nValue As boolean)
'      Declare Property SelectedItem(byref as wfxListBoxItem) 
'      Declare Property SelectedItem() byref as wfxListBoxItem
'      Declare Property SelectedIndex() As long
'      Declare Property SelectedIndex( ByVal nValue As long)
      Declare Property Sorting() As SortOrder
      Declare Property Sorting( ByVal nValue As SortOrder)
      
      Declare Constructor( byref wszName as wstring = "" )
      declare destructor
      declare function Show(byval hWndParent as hwnd = 0) as long override

      OnAllEvents        as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnDestroy          as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnMouseMove        as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnMouseDown        as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnMouseUp          as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnMouseDoubleClick as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnMouseEnter       as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnMouseHover       as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnMouseLeave       as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnGotFocus         as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnLostFocus        as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnKeyDown          as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnKeyUp            as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnKeyPress         as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnDropFiles        As Function( ByRef sender As wfxListView, ByRef e As EventArgs ) As LRESULT
End Type

