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
type _wfxTreeNodeCollection as wfxTreeNodeCollection
type _wfxTreeNode as wfxTreeNode
type _wfxTreeView as wfxTreeView


type wfxTreeSubNodeCollection
   private:
      _pTreeView as _wfxTreeView ptr
      _hParentNode as HTREEITEM
      _Collection  As wfxLList
       
   public:
      declare property hParentNode() as HTREEITEM
      declare property hParentNode( byval nValue as HTREEITEM)
      Declare Property pTreeView() as _wfxTreeView ptr
      Declare Property pTreeView( ByVal ptv as _wfxTreeView ptr)
      Declare function Clear() as long 
      Declare function Count() as long 
      Declare Function Remove( ByVal nIndex As Long ) As Long 
      Declare Function Insert( ByVal nIndex As Long, ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
      Declare Function Add( ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
      declare function ByIndex( byval nIndex as long ) byref as _wfxTreeNode
      declare function DeallocateNodes( byref ParentNode as _wfxTreeNode ) as Long
      Declare Constructor
      declare destructor 
END TYPE

type wfxTreeNode
   private:
      _pTreeView as _wfxTreeView ptr
      _hNode           as HTREEITEM
      _Index           as Long
      _Checked         as boolean
      _Selected        as boolean
      _Text            as CWSTR
      _ToolTipText     as CWSTR
      _Data32          as long
      _NodesCollection as wfxTreeSubNodeCollection
       
   public:
      Declare Property pTreeView() as _wfxTreeView ptr
      Declare Property pTreeView( ByVal ptv as _wfxTreeView ptr)
      declare property hNode() as HTREEITEM
      declare property hNode( byval nValue as HTREEITEM)
      Declare Property Index() As long
      Declare Property Index( ByVal nValue As long)
      Declare Property Checked() As boolean
      Declare Property Checked( ByVal nValue As boolean)
      Declare Property Selected() As boolean
      Declare Property Selected( ByVal nValue As boolean)
      declare property Text() as CWSTR
      declare property Text( byref wszValue as wstring )
      declare property ToolTipText() as CWSTR
      declare property ToolTipText( byref wszValue as wstring )
      Declare Property Data32() As long
      Declare Property Data32( ByVal nValue As long)
      declare function Remove() as boolean
      declare function Expand() as long
      declare function ExpandAll() as long
      declare function Collapse() as long
      declare function EnsureVisible() as long
      declare function SortChildren() as long
      Declare Function Node( ByVal nIndex As Long) ByRef As _wfxTreeNode
      declare function Nodes byref As wfxTreeSubNodeCollection
      declare destructor 
END TYPE


type wfxTreeNodeCollection
   private:
      _Collection As wfxLList
      _pTreeView as _wfxTreeView ptr
       
   public:
      Declare Property pTreeView() as _wfxTreeView ptr
      Declare Property pTreeView( ByVal ptv as _wfxTreeView ptr)
      Declare function Clear() as long 
      Declare function Count() as long 
      Declare Function Remove( ByVal nIndex As Long ) As Long 
      Declare Function Insert( ByVal nIndex As Long, ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
      Declare Function Add( ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
      declare function ByIndex( byval nIndex as long ) byref as wfxTreeNode
      declare function DeallocateNodes( byref ParentNode as _wfxTreeNode ) as Long
      Declare Constructor
      declare destructor 
END TYPE


Type wfxTreeView Extends wfxControl
   private:
      _BorderStyle As ControlBorderStyle = ControlBorderStyle.Fixed3D
      _BackColor as COLORREF
      _ForeColor as COLORREF
      _FadeButtons as Boolean = false
      _CheckBoxes as Boolean = false
      _FullRowSelect as Boolean = false
      _Scrollable as Boolean = true
      _HideSelection as Boolean = false
      _ItemHeight as long = 20
      
      ' Per FreeBasic Help file:
      ' The arrays of references and the non-static reference fields for UDT are not supported yet.
      ' Therefore we have to return a copy to _SelectedNoderather than a reference. This is a 
      ' shame because now we have to do special additional checks when performing methods such
      ' as Remove.
      _SelectedNode as wfxTreeNode
      _pSelectedNode as wfxTreeNode ptr
      
      _TreeNode as wfxTreeNode
      _Sorted as boolean = false
      _ShowLines as Boolean = true
      _ShowRootLines as Boolean = true
      _ShowPlusMinus as Boolean = true
      _HotTracking as boolean = false
      _NodesCollection as wfxTreeNodeCollection
      
   Public:
      UpdateFlag as Boolean = false  ' BeginUpdate/EndUpdate
      Declare Function Node( ByVal nIndex As Long) ByRef As wfxTreeNode
      declare function Nodes byref As wfxTreeNodeCollection
      Declare Property BorderStyle() As ControlBorderStyle
      Declare Property BorderStyle( ByVal nValue As ControlBorderStyle )
      Declare Property FadeButtons() As boolean
      Declare Property FadeButtons( ByVal nValue As boolean)
      Declare Property CheckBoxes() As boolean
      Declare Property CheckBoxes( ByVal nValue As boolean)
      Declare Property FullRowSelect() As boolean
      Declare Property FullRowSelect( ByVal nValue As boolean)
      Declare Property Scrollable() As boolean
      Declare Property Scrollable( ByVal nValue As boolean)
      Declare Property HideSelection() As boolean
      Declare Property HideSelection( ByVal nValue As boolean)
      Declare Property ItemHeight() As long
      Declare Property ItemHeight( ByVal nValue As long)

'      declare property SelectedNode( byval hItem as HTREEITEM )
'      Declare Property SelectedNode( byref nValue as wfxTreeNode ) 
'      Declare Property SelectedNode() byref as wfxTreeNode
      Declare function GetSelectedNode() byref as wfxTreeNode
      declare function SetSelectedNode( byval hItem as HTREEITEM ) as Long
      Declare function SetSelectedNode( byref nValue as wfxTreeNode ) as Long
      
      Declare Property pSelectedNode(byval nValue as wfxTreeNode ptr) 
      Declare Property pSelectedNode() as wfxTreeNode ptr
      
      Declare Property TreeNode(byref as wfxTreeNode) 
      Declare Property TreeNode() byref as wfxTreeNode
      Declare Property Sorted() As boolean
      Declare Property Sorted( ByVal nValue As boolean)
      Declare Property BackColor() As COLORREF
      Declare Property BackColor( ByVal nValue As COLORREF )
      Declare Property ForeColor() As COLORREF
      Declare Property ForeColor( ByVal nValue As COLORREF )
      Declare Property ShowLines() As boolean
      Declare Property ShowLines( ByVal nValue As boolean)
      Declare Property ShowRootLines() As boolean
      Declare Property ShowRootLines( ByVal nValue As boolean)
      Declare Property ShowPlusMinus() As boolean
      Declare Property ShowPlusMinus( ByVal nValue As boolean)
      Declare Property HotTracking() As boolean
      Declare Property HotTracking( ByVal nValue As boolean)
      
      Declare Constructor( byref wszName as wstring = "" )
      declare destructor
      declare function Show(byval hWndParent as hwnd = 0) as long override
      declare function PopulateTree( byref ParentNode as wfxTreeNode ) as Long
      declare function BeginUpdate() as Long
      declare function EndUpdate() as Long
      declare function ExpandAll() as Long
      declare function CollapseAll() as Long
      declare function GetNodeAt( byval x as long, byval y as Long ) byref as wfxTreeNode
      declare function GetNodeAt( byval pt as POINT ) byref as wfxTreeNode
      declare function GetNodeAt( byval pt as wfxPoint ) byref as wfxTreeNode
      declare function RecurseTreeNodeSearch( byref ParentNode as wfxTreeNode, _
                                              byval pTreeNode as wfxTreeNode ptr ) as boolean
      declare function Remove( byval pTreeNode as wfxTreeNode ptr ) as boolean  ' called from the TreeNode class
      declare function Sort() as Long

      OnAllEvents        as function( byref sender as wfxTreeView, byref e as EventArgs ) as LRESULT
      OnBeforeSelect     As Function( ByRef sender As wfxTreeView, ByRef e As EventArgs ) As LRESULT
      OnAfterSelect      As Function( ByRef sender As wfxTreeView, ByRef e As EventArgs ) As LRESULT
      OnBeforeCollapse   As Function( ByRef sender As wfxTreeView, ByRef e As EventArgs ) As LRESULT
      OnAfterCollapse    As Function( ByRef sender As wfxTreeView, ByRef e As EventArgs ) As LRESULT
      OnBeforeExpand     As Function( ByRef sender As wfxTreeView, ByRef e As EventArgs ) As LRESULT
      OnAfterExpand      As Function( ByRef sender As wfxTreeView, ByRef e As EventArgs ) As LRESULT
      OnBeforeCheck      As Function( ByRef sender As wfxTreeView, ByRef e As EventArgs ) As LRESULT
      OnAfterCheck       As Function( ByRef sender As wfxTreeView, ByRef e As EventArgs ) As LRESULT
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
      OnDropFiles        As Function( ByRef sender As wfxTreeView, ByRef e As EventArgs ) As LRESULT
      OnKeyDown          as function( byref sender as wfxTreeView, byref e as EventArgs ) as LRESULT
      OnKeyUp            as function( byref sender as wfxTreeView, byref e as EventArgs ) as LRESULT
      OnKeyPress         as function( byref sender as wfxTreeView, byref e as EventArgs ) as LRESULT
End Type

