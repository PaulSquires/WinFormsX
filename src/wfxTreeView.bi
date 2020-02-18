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

' TreeView Class

' Forward references
type _wfxTreeViewNodesCollection as wfxTreeViewNodesCollection
type _wfxTreeViewNode as wfxTreeViewNode

type wfxTreeViewNode
   private:
      _hWindow         as hwnd
      _Index           as Long
      _IsLoading       as Boolean = true   ' internal
      _Checked         as boolean
      _Selected        as boolean
      _Text            as CWSTR
      _Data32          as long
      
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
      Declare Function Node( ByVal nIndex As Long) ByRef As _wfxTreeViewNode
      declare function Nodes byref As _wfxTreeViewNodesCollection
      declare destructor 
END TYPE


type wfxTreeViewNodesCollection
   private:
      _hWindow    as hwnd
      _Collection As wfxLList
       
   public:
      Declare Property hWindow() As hwnd
      Declare Property hWindow( ByVal nValue As hwnd)
      Declare function Clear() as long 
      Declare function Count() as long 
      Declare Function Remove( ByVal nIndex As Long ) As Long 
      Declare Function Insert( ByVal nIndex As Long, ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
      Declare Function Add( ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
      declare function ByIndex( byval nIndex as long ) byref as wfxTreeViewNode
      Declare Constructor
      declare destructor 
END TYPE


Type wfxTreeView Extends wfxControl
   private:
      _BorderStyle As ControlBorderStyle = ControlBorderStyle.Fixed3D
      _CheckBoxes as Boolean = false
      _FullRowSelect as Boolean = true
      _HideSelection as Boolean = false
      _SelectedNode as wfxTreeViewNode
      _Sorting as SortOrder = SortOrder.None
      _IsLoading as Boolean = true   ' internal
      
   Public:
      Declare Function Node( ByVal nIndex As Long) ByRef As wfxTreeViewNode
      declare function Nodes byref As wfxTreeViewNodesCollection
      Declare Property BorderStyle() As ControlBorderStyle
      Declare Property BorderStyle( ByVal nValue As ControlBorderStyle )
      Declare Property CheckBoxes() As boolean
      Declare Property CheckBoxes( ByVal nValue As boolean)
      Declare Property FullRowSelect() As boolean
      Declare Property FullRowSelect( ByVal nValue As boolean)
      Declare Property HideSelection() As boolean
      Declare Property HideSelection( ByVal nValue As boolean)
      Declare Property SelectedNode(byref as wfxTreeViewNode) 
      Declare Property SelectedNode() byref as wfxTreeViewNode
      Declare Property Sorting() As SortOrder
      Declare Property Sorting( ByVal nValue As SortOrder)
      Declare Function Node( ByVal nIndex As Long) ByRef As _wfxTreeViewNode
      declare function Nodes byref As _wfxTreeViewNodesCollection
      
      Declare Constructor( byref wszName as wstring = "" )
      declare destructor
      declare function Show(byval hWndParent as hwnd = 0) as long override

      OnAllEvents        as function( byref sender as wfxTreeView, byref e as EventArgs ) as LRESULT
      OnDestroy          as function( byref sender as wfxTreeView, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxTreeView, byref e as EventArgs ) as LRESULT
      OnMouseMove        as function( byref sender as wfxTreeView, byref e as EventArgs ) as LRESULT
      OnMouseDown        as function( byref sender as wfxTreeView, byref e as EventArgs ) as LRESULT
      OnMouseUp          as function( byref sender as wfxTreeView, byref e as EventArgs ) as LRESULT
      OnMouseDoubleClick as function( byref sender as wfxTreeView, byref e as EventArgs ) as LRESULT
      OnMouseEnter       as function( byref sender as wfxTreeView, byref e as EventArgs ) as LRESULT
      OnMouseHover       as function( byref sender as wfxTreeView, byref e as EventArgs ) as LRESULT
      OnMouseLeave       as function( byref sender as wfxTreeView, byref e as EventArgs ) as LRESULT
      OnGotFocus         as function( byref sender as wfxTreeView, byref e as EventArgs ) as LRESULT
      OnLostFocus        as function( byref sender as wfxTreeView, byref e as EventArgs ) as LRESULT
      OnKeyDown          as function( byref sender as wfxTreeView, byref e as EventArgs ) as LRESULT
      OnKeyUp            as function( byref sender as wfxTreeView, byref e as EventArgs ) as LRESULT
      OnKeyPress         as function( byref sender as wfxTreeView, byref e as EventArgs ) as LRESULT
      OnDropFiles        As Function( ByRef sender As wfxTreeView, ByRef e As EventArgs ) As LRESULT
End Type

