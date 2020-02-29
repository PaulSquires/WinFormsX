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

#include once "wfxTreeView.bi"


constructor wfxTreeView( byref wszName as wstring = "" )
   this.CtrlType  = ControlType.TreeView
   this.Name      = wszName
   this.BackColor = Colors.SystemWindow
   this.ForeColor = Colors.SystemWindowText
end constructor

destructor wfxTreeView
   this.Nodes.Clear
end destructor


Function wfxTreeView.Node( ByVal nIndex As Long ) ByRef As wfxTreeViewNode
   return this.Nodes.ByIndex(nIndex)
END function

function wfxTreeView.Nodes byref As wfxTreeViewNodesCollection
   return this._NodesCollection
END function

Property wfxTreeView.BorderStyle() As ControlBorderStyle
   If this.hWindow Then 
      If (AfxGetWindowExStyle(this.hWindow) And WS_EX_CLIENTEDGE) Then
         _BorderStyle = ControlBorderStyle.Fixed3D
      ElseIf (AfxGetWindowStyle(this.hWindow) And WS_BORDER) Then
         _BorderStyle = ControlBorderStyle.FixedSingle
      Else
         _BorderStyle = ControlBorderStyle.None
      End If   
   End If
   Property = _BorderStyle
End Property

Property wfxTreeView.BorderStyle( ByVal nValue As ControlBorderStyle )
   If this.hWindow Then 
      Dim As Long wsStyle
      Select Case nValue
         Case ControlBorderStyle.None
            AfxRemoveWindowStyle(this.hWindow, WS_BORDER)
            AfxRemoveWindowExStyle(this.hWindow, WS_EX_CLIENTEDGE)
         Case ControlBorderStyle.Fixed3D
            AfxRemoveWindowStyle(this.hWindow, WS_BORDER)
            AfxAddWindowExStyle(this.hWindow, WS_EX_CLIENTEDGE)
         Case ControlBorderStyle.FixedSingle
            AfxAddWindowStyle(this.hWindow, WS_BORDER)
            AfxRemoveWindowExStyle(this.hWindow, WS_EX_CLIENTEDGE)
      End Select
      AfxRedrawNonClientArea( this.hWindow )
   End If
   _BorderStyle = nValue
End Property


Property wfxTreeView.CheckBoxes() As boolean
   Property = _CheckBoxes
End Property

property wfxTreeView.CheckBoxes( byval nValue as boolean )
   _CheckBoxes = nValue
end property

Property wfxTreeView.FullRowSelect() As boolean
   Property = _FullRowSelect
End Property

property wfxTreeView.FullRowSelect( byval nValue as boolean )
   ' FullRowSelect only works if Lines between nodes styles are inactive 
   _FullRowSelect = nValue
end property

Property wfxTreeView.HideSelection() As boolean
   Property = _HideSelection
End Property

property wfxTreeView.HideSelection( byval nValue as boolean )
   _HideSelection = nValue
end property

property wfxTreeView.SelectedNode() byref as wfxTreeViewNode
   property = _SelectedNode
end property

property wfxTreeView.SelectedNode( byref tvItem as wfxTreeViewNode )
   _SelectedNode = tvItem
end property

property wfxTreeView.TreeNode() byref as wfxTreeViewNode
   property = _TreeNode
end property

property wfxTreeView.TreeNode( byref tvItem as wfxTreeViewNode )
   _TreeNode = tvItem
end property

Property wfxTreeView.Sorting() As SortOrder
   property = _Sorting
end property

property wfxTreeView.Sorting( byval nValue as SortOrder )
   _Sorting = nValue
end property

Property wfxTreeView.Scrollable() As boolean
   Property = _Scrollable
End Property

property wfxTreeView.Scrollable( byval nValue as boolean )
   _Scrollable = nValue
end property

Property wfxTreeView.BackColor() As COLORREF
   if this.hWindow then
      _BackColor = TreeView_GetBkColor( this.hWindow )
   end if   
   property = _BackColor
end property

Property wfxTreeView.BackColor( ByVal nValue As COLORREF )
   if this.hWindow then
      TreeView_SetBkColor( this.hWindow, nValue )
   end if
   _BackColor = nValue
end property

Property wfxTreeView.ForeColor() As COLORREF
   if this.hWindow then
      _ForeColor = TreeView_GetTextColor( this.hWindow )
   end if   
   property = _ForeColor
end property

Property wfxTreeView.ForeColor( ByVal nValue As COLORREF )
   if this.hWindow then
      TreeView_SetTextColor( this.hWindow, nValue )
   end if
   _ForeColor = nValue
end property

Property wfxTreeView.ItemHeight() As long
   if this.hWindow then
      _ItemHeight = TreeView_GetItemHeight( this.hWindow )
   end if   
   property = _ItemHeight
end property

Property wfxTreeView.ItemHeight( ByVal nValue As long)
   if this.hWindow then
      TreeView_SetItemHeight( this.hWindow, AfxScaleY(nValue) )
   end if   
   _ItemHeight = nValue
end property

Property wfxTreeView.ShowLines() As boolean
   property = _ShowLines
end property

Property wfxTreeView.ShowLines( ByVal nValue As boolean)
   _ShowLines = nValue
end property
   
Property wfxTreeView.ShowRootLines() As boolean
   property = _ShowRootLines
end property

Property wfxTreeView.ShowRootLines( ByVal nValue As boolean)
   _ShowRootLines = nValue
end property

Property wfxTreeView.ShowPlusMinus() As boolean
   property = _ShowPlusMinus
end property

Property wfxTreeView.ShowPlusMinus( ByVal nValue As boolean)
   _ShowPlusMinus = nValue
end property

Property wfxTreeView.HotTracking() As boolean
   property = _HotTracking
end property

Property wfxTreeView.HotTracking( ByVal nValue As boolean)
   _HotTracking = nValue
end property

Property wfxTreeView.FadeButtons() As boolean
   property = _FadeButtons
end property

Property wfxTreeView.FadeButtons( ByVal nValue As boolean)
   _FadeButtons = nValue
end property

function wfxTreeView.PopulateTree( byref ParentNode as wfxTreeViewNode ) as Long
   for i as long = 0 to ParentNode.Nodes.count - 1
      ParentNode.Nodes.hWindow = ParentNode.hWindow
      ParentNode.Node(i).hWindow = ParentNode.hWindow
      ParentNode.Node(i).hNode = _
         TreeView_AppendItem( this.hWindow, ParentNode.hNode, _
                              ParentNode.Node(i).Text, ParentNode.Node(i).Data32 )
      this.PopulateTree( ParentNode.Node(i) )
   next      
   function = 0
end function


function wfxTreeView.Show(byval hWndParent as hwnd = 0) as long

   dim wszClassName as wstring * MAX_PATH
   
   ' If the control is created but simply hidden, then show it.
   if this.hWindow THEN
      ShowWindow(this.hWindow, SW_SHOW)
      exit function
   END IF

   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function
      
   Dim As Long dwExStyle = 0
   dim as long dwStyle = WS_CLIPCHILDREN or TVS_INFOTIP 

   if _TabStop       then dwStyle = dwStyle OR WS_TABSTOP 
   if _Visible       THEN dwStyle = dwStyle OR WS_VISIBLE
   if _CheckBoxes    then dwStyle = dwStyle OR TVS_CHECKBOXES
   if _FullRowSelect then dwStyle = dwStyle OR TVS_FULLROWSELECT
   if _ShowLInes     then dwStyle = dwStyle OR TVS_HASLINES
   if _ShowRootLines then dwStyle = dwStyle OR TVS_LINESATROOT
   if _ShowPlusMinus then dwStyle = dwStyle OR TVS_HASBUTTONS
   if _HotTracking   then dwStyle = dwStyle OR TVS_TRACKSELECT
   
   if _HideSelection = false then dwStyle = dwStyle OR TVS_SHOWSELALWAYS
   if _Scrollable    = false then dwStyle = dwStyle OR TVS_NOSCROLL

   _CtrlID = this.Parent->GetNextCtrlID()

   this.hWindow = this.Parent->pWindow->AddControl ( _
         "SysTreeView32", _                ' // Class name
         hWndParent, _                     ' // Parent window handle
         _CtrlID, _                        ' // Control identifier 
         this.Text, _                      ' // Control caption
         this.Left, _                      ' // Horizontal position
         this.Top, _                       ' // Vertical position
         this.Width, _                     ' // Control width
         this.Height, _                    ' // Control height
         dwStyle, _                        ' // Control style
         dwExStyle, _                      ' // Extended style
         0, _                              ' // Pointer to custom data
         Cast(SUBCLASSPROC, @wfxApplication.SubclassProc), _   ' // Address of the window callback procedure
         _CtrlID, _                        ' // The subclass ID
         Cast(DWORD_PTR, 0) _              ' // Pointer to reference data
         )

   ' Use the new style Explorer Treeview (triangles instead of boxes).
   ' Set an undocumented extended style that enables the treeview glyphs to resize
   ' according to the high dpi setting.
   ' https://stackoverflow.com/questions/38772670/ctreectrl-with-explorer-theme-not-dpi-aware
   TreeView_SetExtendedStyle( this.hWindow, &H1000, &H1000 )
   SetWindowTheme(this.hWindow, @wstr("EXPLORER"), 0)
   TreeView_SetExtendedStyle( this.hWindow, TVS_EX_DOUBLEBUFFER, TVS_EX_DOUBLEBUFFER )
   TreeView_SetExtendedStyle( this.hWindow, TVS_EX_AUTOHSCROLL, TVS_EX_AUTOHSCROLL )

   ' Should we enable drag and drop files
   If this.AllowDrop Then DragAcceptFiles(this.hWindow, CTRUE)

   ' Apply properties that require a valid window handle
   if _FadeButtons then TreeView_SetExtendedStyle( this.hWindow, TVS_EX_FADEINOUTEXPANDOS, TVS_EX_FADEINOUTEXPANDOS )
   
   this.Font        = _wfxFontPtr
   this.BackColor   = _BackColor
   this.ForeColor   = _ForeColor
   this.BorderStyle = _BorderStyle
   this.ItemHeight  = _ItemHeight
   this.Enabled     = _Enabled

   this.ToolTip     = _ToolTip

   ' Do not set the focus/selected here because doing so will also Activate the form and
   ' cause an Activated message to be fired. We want the Form's Load event to
   ' complete before any Activate message.
   ' Refer to wfxForm.CreateFormInternal for the setting of the focus/selected
   ' control once events have fired correctly.
      
   ' Store the hWindow in the linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   dim pNode as wfxLListNode ptr = this.Parent->Controls.search_data(@this)
   if pNode then pNode->hWindow = this.hWindow
      
   this.Nodes.hWindow = this.hWindow
   
   ' Recursively load all of the nodes...
   for i as long = 0 to this.Nodes.count - 1
      ' Set the hWindow for the collection
      this.Node(i).hWindow = this.hWindow
      this.Node(i).hNode = _
         TreeView_AddRootItem( this.hWindow, this.Node(i).Text, this.Node(i).Data32 )
      this.PopulateTree( this.Node(i) )
   next      

   _IsLoading = false

   function = 0
END FUNCTION



'' TreeView Node

destructor wfxTreeViewNode
   '
end destructor

property wfxTreeViewNode.hNode() as HTREEITEM
   property = _hNode
end property

property wfxTreeViewNode.hNode( byVal nValue as HTREEITEM)
   _hNode = nValue
end property

property wfxTreeViewNode.hWindow() as hwnd
   property = _hWindow
end property

property wfxTreeViewNode.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

Property wfxTreeViewNode.Selected() As boolean
   property = _Selected
END PROPERTY

property wfxTreeViewNode.Selected( ByVal nValue As boolean) 
'   if this.hWindow then 
'      SendMessage(this.hWindow, LB_SETSEL, nValue, cast(LPARAM, _Index) )
'   end if
   _Selected = nValue
END PROPERTY

Property wfxTreeViewNode.Checked() As boolean
   property = _Checked
END PROPERTY

property wfxTreeViewNode.Checked( ByVal nValue As boolean) 
   _Checked = nValue
END PROPERTY

property wfxTreeViewNode.Index() as long
   property = _Index
End Property

property wfxTreeViewNode.Index( ByVal nValue As long) 
   _Index = nValue
END PROPERTY

property wfxTreeViewNode.Text() as CWSTR
   property = _Text 
end property

property wfxTreeViewNode.Text( byref wszValue as wstring )
   _Text = wszValue
end property

property wfxTreeViewNode.Data32() as long
   ' The Data32 is only held in the classes, not the TreeView itself. The lParam
   ' of the Treeview node is actually a pointer to the TreeViewNode class for
   ' this node. That makes it fast to cross reference between the class and the node.
   property = _Data32
end property

property wfxTreeViewNode.Data32( byval nValue as long )
   _Data32 = nValue
end property

Function wfxTreeViewNode.Node( ByVal nIndex As Long ) ByRef As wfxTreeViewNode
   return this.Nodes.ByIndex(nIndex)
END function

function wfxTreeViewNode.Nodes byref As wfxTreeViewSubNodesCollection
   return this._NodesCollection 
END function



'' NODESCOLLECTION
constructor wfxTreeViewNodesCollection
   '
END CONSTRUCTOR

destructor wfxTreeViewNodesCollection
   '
end destructor

property wfxTreeViewNodesCollection.hWindow() as hwnd
   property = _hWindow
end property

property wfxTreeViewNodesCollection.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

function wfxTreeViewNodesCollection.Count() as Long
   function = _Collection.Size
end function

Function wfxTreeViewNodesCollection.Add( ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
   Dim pData As wfxTreeViewNode Ptr = New wfxTreeViewNode
   pData->hWindow = this.hWindow
   pData->Nodes.hWindow = this.hWindow
   pData->Index = (this.Count - 1) + 1
   pData->Text = wszValue
   pData->Data32 = nValue
   _Collection.Add( ControlType.TreeView, pData ) 
   If this.hWindow Then 
      ' Save the pointer to the TreeViewNode in the lParam of the node.
      pData->hNode = TreeView_AddRootItem( this.hWindow, wszValue, cast(LPARAM, pData) )
      pData->Nodes.hParentNode = pData->hNode
   end if      
   function = pData->Index
end function

Function wfxTreeViewNodesCollection.Insert( ByVal nIndex As Long, ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
   Dim pData As wfxTreeViewNode Ptr = New wfxTreeViewNode
   pData->hWindow = this.hWindow
   pData->Index = nIndex
   pData->Text = wszValue
   pData->Data32 = nValue
   _Collection.Insert( nIndex, ControlType.TreeView, pData ) 
   function = pData->Index
end function

function wfxTreeViewNodesCollection.Remove( byval nIndex as long ) as long
   dim pNode as wfxLListNode ptr = _Collection.get_index(nIndex)
   if pNode then
      ' Delete ListViewItem fires destructor that deletes any subitems
      Delete cast(wfxTreeViewNode ptr, pNode->pData)
      _Collection.Remove(pNode)
   end if   
   function = _Collection.Size
end function

function wfxTreeViewNodesCollection.ByIndex( byval nIndex as long ) byref as wfxTreeViewNode 
   dim pItem as wfxTreeViewNode ptr
   dim pNode as wfxLListNode ptr
   if _Collection.Size then
      if (nIndex >= 0) and (nIndex <= _Collection.Size - 1) then
         pNode = _Collection.get_index(nIndex)
         if pNode then
            pItem = cast(wfxTreeViewNode ptr, pNode->pData)
            return *pItem
         end if
      end if      
   end if   
end function

function wfxTreeViewNodesCollection.Clear() as long
   ' Deallocate elements in the Items collection.
   dim pNode as wfxLListNode ptr = _Collection.get_first
   do until pNode = 0
      ' Delete ListViewItem fires destructor that deletes any subitems
      Delete cast(wfxTreeViewNode ptr, pNode->pData)
      pNode = _Collection.remove(pNode)
   LOOP
'   If this.hWindow Then ListView_SetItemCount( this.hWindow, this.Count )
   function = 0
END FUNCTION


'' SUBNODESCOLLECTION
constructor wfxTreeViewSubNodesCollection
   '
END CONSTRUCTOR

destructor wfxTreeViewSubNodesCollection
   '
end destructor

property wfxTreeViewSubNodesCollection.hParentNode() as HTREEITEM
   property = _hParentNode
end property

property wfxTreeViewSubNodesCollection.hParentNode( byVal nValue as HTREEITEM)
   _hParentNode = nValue
end property

property wfxTreeViewSubNodesCollection.hWindow() as hwnd
   property = _hWindow
end property

property wfxTreeViewSubNodesCollection.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

function wfxTreeViewSubNodesCollection.Count() as Long
   function = _Collection.Size
end function

Function wfxTreeViewSubNodesCollection.Add( ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
   Dim pData As wfxTreeViewNode Ptr = New wfxTreeViewNode
   pData->hWindow = this.hWindow
   pData->Nodes.hWindow = this.hWindow
   pData->Index = (this.Count - 1) + 1
   pData->Text = wszValue
   pData->Data32 = nValue
   _Collection.Add( ControlType.TreeView, pData ) 
   If this.hWindow Then 
      ' Save the pointer to the TreeViewNode in the lParam of the node.
      pData->hNode = TreeView_AppendItem( this.hWindow, this.hParentNode, wszValue, cast(LPARAM, pData) )
      pData->Nodes.hParentNode = pData->hNode    
   end if
   function = pData->Index
end function

Function wfxTreeViewSubNodesCollection.Insert( ByVal nIndex As Long, ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
   Dim pData As wfxTreeViewNode Ptr = New wfxTreeViewNode
   pData->hWindow = this.hWindow
   pData->Index = nIndex
   pData->Text = wszValue
   pData->Data32 = nValue
   _Collection.Insert( nIndex, ControlType.TreeView, pData ) 
   function = pData->Index
end function

function wfxTreeViewSubNodesCollection.Remove( byval nIndex as long ) as long
   dim pNode as wfxLListNode ptr = _Collection.get_index(nIndex)
   if pNode then
      ' Delete ListViewItem fires destructor that deletes any subitems
      Delete cast(wfxTreeViewNode ptr, pNode->pData)
      _Collection.Remove(pNode)
   end if   
   function = _Collection.Size
end function

function wfxTreeViewSubNodesCollection.ByIndex( byval nIndex as long ) byref as wfxTreeViewNode 
   dim pItem as wfxTreeViewNode ptr
   dim pNode as wfxLListNode ptr
   if _Collection.Size then
      if (nIndex >= 0) and (nIndex <= _Collection.Size - 1) then
         pNode = _Collection.get_index(nIndex)
         if pNode then
            pItem = cast(wfxTreeViewNode ptr, pNode->pData)
            return *pItem
         end if
      end if      
   end if   
end function

function wfxTreeViewSubNodesCollection.Clear() as long
   ' Deallocate elements in the Items collection.
   dim pNode as wfxLListNode ptr = _Collection.get_first
   do until pNode = 0
      ' Delete ListViewItem fires destructor that deletes any subitems
      Delete cast(wfxTreeViewNode ptr, pNode->pData)
      pNode = _Collection.remove(pNode)
   LOOP
   function = 0
END FUNCTION


