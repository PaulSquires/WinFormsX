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

' ListView Class


type wfxListViewColumn
   private:
      _hWindow     as hwnd
      _Index       as Long
      _Text        as CWSTR
      _Width       as long
      _TextAlign   as TextAlignment
      
   public:
      Declare Property hWindow() As hwnd
      Declare Property hWindow( ByVal nValue As hwnd)
      Declare Property Index() As long
      Declare Property Index( ByVal nValue As long)
      declare property Text() as CWSTR
      declare property Text( byref wszValue as wstring )
      Declare Property Width() As long
      Declare Property Width( ByVal nValue As long)
      Declare Property TextAlign() As TextAlignment
      Declare Property TextAlign( ByVal nValue As TextAlignment )

end type

type wfxListViewColumnsCollection
   private:
      _hWindow    as hwnd
      _Collection As wfxLList
       
   public:
      declare function SetupColumns_Internal() as Long   ' internal
      Declare Property hWindow() As hwnd
      Declare Property hWindow( ByVal nValue As hwnd)
      Declare function Clear() as long 
      Declare function Count() as long 
      Declare Function Remove( ByVal nIndex As Long ) As Long 
      declare Function Add( ByRef wszValue As WString = "", ByVal nWidth As Long = 100, byval nTextAlign as TextAlignment = TextAlignment.Left ) as Long
      declare function ByIndex( byval nIndex as long ) byref as wfxListViewColumn
      Declare Constructor
      declare destructor 
END TYPE

type wfxListViewSubItem
   private:
      _hWindow     as hwnd
      _ItemIndex   as Long   ' index within the items collection
      _Index       as Long   ' index within the subitems collection
      _Text        as CWSTR
      _BackColor   As COLORREF = Colors.SystemWindow
      _ForeColor   As COLORREF = Colors.SystemWindowText
      
   public:
      UpdateFlag as Boolean = false
      Declare Property hWindow() As hwnd
      Declare Property hWindow( ByVal nValue As hwnd)
      Declare Property ItemIndex() As long
      Declare Property ItemIndex( ByVal nValue As long)
      Declare Property Index() As long
      Declare Property Index( ByVal nValue As long)
      declare property Text() as CWSTR
      declare property Text( byref wszValue as wstring )
      Declare Property BackColor() As COLORREF
      Declare Property BackColor( ByVal nValue As COLORREF )
      Declare Property ForeColor() As COLORREF
      Declare Property ForeColor( ByVal nValue As COLORREF )
      declare destructor 

end type

type wfxListViewSubItemsCollection
   private:
      _hWindow    as hwnd
      _Collection As wfxLList
      _ItemIndex  as Long   ' index within the items collection
       
   public:
      UpdateFlag as Boolean = false
      Declare Property ItemIndex() As long
      Declare Property ItemIndex( ByVal nValue As long)
      Declare Property hWindow() As hwnd
      Declare Property hWindow( ByVal nValue As hwnd)
      Declare function Clear() as long 
      Declare function Count() as long 
      Declare Function Remove( ByVal nIndex As Long ) As Long 
      Declare Function Add( ByRef wszValue As WString = "") As Long
      declare function ByIndex( byval nIndex as long ) byref as wfxListViewSubItem
      Declare Constructor
      declare destructor 
END TYPE


type wfxListViewItem 
   private:
      _hWindow            as HWND
      _Index              as Long
      _IsLoading          as Boolean = true   ' internal
      _Checked            as boolean
      _Selected           as boolean
      _Data32             as long
      _SubItemsCollection as wfxListViewSubItemsCollection
   
   public:
      
      Declare Property hWindow() As hwnd
      Declare Property hWindow( ByVal nValue As hwnd)
      Declare Property Index() As long
      Declare Property Index( ByVal nValue As long)
      Declare Property Checked() As boolean
      Declare Property Checked( ByVal nValue As boolean)
      Declare Property Selected() As boolean
      Declare Property Selected( ByVal nValue As boolean)
      declare property Text() as CWSTR
      declare property Text( byref wszValue as wstring )
      Declare Property Data32() As long
      Declare Property Data32( ByVal nValue As long)
      Declare Property BackColor() As COLORREF
      Declare Property BackColor( ByVal nValue As COLORREF )
      Declare Property ForeColor() As COLORREF
      Declare Property ForeColor( ByVal nValue As COLORREF )
      Declare Function SubItem( ByVal nIndex As Long) ByRef As wfxListViewSubItem
      declare function SubItems byref As wfxListViewSubItemsCollection
      declare destructor 
END TYPE


type wfxListViewItemsCollection
   private:
      _hWindow    as hwnd
      _Collection As wfxLList
       
   public:
      UpdateFlag as Boolean = false
      Declare Property hWindow() As hwnd
      Declare Property hWindow( ByVal nValue As hwnd)
      Declare function Clear() as long 
      Declare function Count() as long 
      declare function SortByColumn( ByVal nColNum As Long, byval nSortAscend as Boolean = true ) as long 
      Declare Function SelectedCount() As Long
      Declare Function Remove( ByVal nIndex As Long ) As Long 
      Declare Function Insert( ByVal nIndex As Long, ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
      Declare Function Add( ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
      declare function ByIndex( byval nIndex as long ) byref as wfxListViewItem
      Declare Constructor
      declare destructor 
END TYPE

Type wfxListView Extends wfxControl
   private:
      _AllowColumnReorder As boolean = false 
      _BorderStyle As ControlBorderStyle = ControlBorderStyle.Fixed3D
      _CheckBoxes as Boolean = false
      _FullRowSelect as Boolean = true
      _GridLines as Boolean = false
      _HideSelection as Boolean = false
      _HeaderStyle as ColumnHeaderStyle = ColumnHeaderStyle.Clickable
      _HeaderHeight as Long =  20
      _HeaderForeColor as COLORREF = Colors.SystemWindowText
      _HeaderBackColor as COLORREF = Colors.SystemWindow
      _HeaderThemed as boolean = false
      _LabelEdit As boolean = false
      _MultiSelect As boolean = false
      _SelectedItem as wfxListViewItem
      _SelectedIndex as Long = -1
      _Sorting as SortOrder = SortOrder.None
      _ItemsCollection as wfxListViewItemsCollection
      _ColumnsCollection as wfxListViewColumnsCollection
      _IsLoading as Boolean = true   ' internal
      _OddRowColor As COLORREF = Colors.SystemWindow
      _OddRowColorEnabled as boolean = False
      
   Public:
      Declare Function Item( ByVal nIndex As Long) ByRef As wfxListViewItem
      declare function Items byref As wfxListViewItemsCollection
      Declare Function Column( ByVal nIndex As Long) ByRef As wfxListViewColumn
      declare function Columns byref As wfxListViewColumnsCollection
      Declare function BeginUpdate() As long
      Declare function EndUpdate() as Long
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
      Declare Property SelectedItem(byref as wfxListViewItem) 
      Declare Property SelectedItem() byref as wfxListViewItem
      Declare Property SelectedIndex() As long
      Declare Property SelectedIndex( ByVal nValue As long)
      Declare Property Sorting() As SortOrder
      Declare Property Sorting( ByVal nValue As SortOrder)
      Declare Property OddRowColor() As COLORREF
      Declare Property OddRowColor( ByVal nValue As COLORREF )
      Declare Property OddRowColorEnabled() As boolean
      Declare Property OddRowColorEnabled( ByVal nValue As boolean)
      Declare Property HeaderThemed() As boolean
      Declare Property HeaderThemed( ByVal nValue As boolean)
      Declare Property HeaderForeColor() As COLORREF
      Declare Property HeaderForeColor( ByVal nValue As COLORREF )
      Declare Property HeaderBackColor() As COLORREF
      Declare Property HeaderBackColor( ByVal nValue As COLORREF )
      Declare Property HeaderHeight() As long
      Declare Property HeaderHeight( ByVal nValue As long)
      
      Declare Constructor( byref wszName as wstring = "" )
      declare destructor
      declare function Show(byval hWndParent as hwnd = 0) as long override
      declare function HitTest( byref iItem as long, byref iSubItem as long ) as Long
      declare static Function HeaderSubclassProc( ByVal HWnd As HWnd, ByVal uMsg As UINT, ByVal wParam As WPARAM, ByVal lParam As LPARAM, ByVal uIdSubclass As UINT_PTR, ByVal dwRefData As DWORD_PTR ) As LRESULT

      OnAllEvents        as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnDestroy          as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnRightClick       as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnDoubleClick      as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnColumnClick      as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnItemSelectionChanged as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnMouseMove        as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnMouseDown        as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnMouseUp          as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnMouseDoubleClick as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnMouseEnter       as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnMouseLeave       as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnGotFocus         as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnLostFocus        as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnKeyDown          as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnKeyUp            as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnKeyPress         as function( byref sender as wfxListView, byref e as EventArgs ) as LRESULT
      OnDropFiles        As Function( ByRef sender As wfxListView, ByRef e As EventArgs ) As LRESULT
End Type

