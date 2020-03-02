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


Function wfxTreeView.Node( ByVal nIndex As Long ) ByRef As wfxTreeNode
   return this.Nodes.ByIndex(nIndex)
END function

function wfxTreeView.Nodes byref As wfxTreeNodeCollection
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

property wfxTreeView.SelectedNode() byref as wfxTreeNode
   if this.hWindow then
      dim as HTREEITEM hItem = TreeView_GetSelection( this.hWindow )
      if hItem then
         dim pTreeViewNode as wfxTreeNode ptr
         pTreeViewNode = cast(wfxTreeNode ptr, TreeView_GetlParam( this.hWindow, hItem))
         if pTreeViewNode then 
            _SelectedNode = *pTreeViewNode
         else
            ' Need to return a reference otherwise crash if trying to access the return reference.
            static tvNode as wfxTreeNode   
            _SelectedNode = tvNode
         end if   
      end if
   end if
   property = _SelectedNode
end property

property wfxTreeView.SelectedNode( byval hItem as HTREEITEM )
   if this.hWindow then
      TreeView_SelectItem( this.hWindow, hItem )
      dim pTreeViewNode as wfxTreeNode ptr = cast(wfxTreeNode ptr, TreeView_GetlParam( this.hWindow, hItem))
      if pTreeViewNode then _SelectedNode = *pTreeViewNode 
   end if
end property

property wfxTreeView.SelectedNode( byref tvNode as wfxTreeNode )
   if this.hWindow then
      TreeView_SelectItem( this.hWindow, tvNode.hNode )
   end if
   _SelectedNode = tvNode
end property

' TreeNode is used to hold a reference to the node that is currently
' being acted on for messages like OnBeforeCollapse, OnAfterCollapse, etc.
property wfxTreeView.TreeNode() byref as wfxTreeNode
   property = _TreeNode
end property

property wfxTreeView.TreeNode( byref tvItem as wfxTreeNode )
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

function wfxTreeView.PopulateTree( byref ParentNode as wfxTreeNode ) as Long
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

function wfxTreeView.BeginUpdate() as Long
   if this.UpdateFlag then exit function
   SendMessage( this.hWindow, WM_SETREDRAW, false, 0 )
   this.UpdateFlag = true
   function = 0
end function

function wfxTreeView.EndUpdate() as Long
   if this.UpdateFlag then 
      this.UpdateFlag = false
      SendMessage( this.hWindow, WM_SETREDRAW, true, 0 )
      this.Refresh
   end if   
   function = 0
end function

function wfxTreeView.ExpandAll() as Long
   ' Per Jose's comment in Afx code, the expanding can take a long time and 
   ' redraw many times causing slowness on large treeviews.
   this.BeginUpdate
   TreeView_ExpandAllItems( this.hWindow ) 
   this.EndUpdate
   function = 0
end function

function wfxTreeView.CollapseAll() as Long
   this.BeginUpdate
   TreeView_CollapseAllItems( this.hWindow ) 
   this.EndUpdate
   function = 0
end function
   

function wfxTreeView.GetNodeAt( byval x as long, byval y as Long ) byref as wfxTreeNode
   if this.hWindow then
      ' Test to see if the checkbox was clicked.
      dim hitinfo as TVHITTESTINFO
      hitinfo.pt.x = x
      hitinfo.pt.y = y
      SendMessage( this.hWindow, TVM_HITTEST, 0, cast(ULONG_PTR, @hitinfo) ) 

      ' Allow a hit if FullRowSelect is active and the hittest returns
      ' the area to the right of the label, or if clicked on the label itself.
      dim as Boolean bHit = false
      if this.FullRowSelect then
         if (hitinfo.flags and TVHT_ONITEMRIGHT) = TVHT_ONITEMRIGHT then bHit = true
      end if
      if (hitinfo.flags and TVHT_ONITEMLABEL) = TVHT_ONITEMLABEL then bHit = true                        

      if bHit then
         dim pTreeViewNode as wfxTreeNode ptr
         pTreeViewNode = cast(wfxTreeNode ptr, TreeView_GetlParam( this.hWindow, hitinfo.hItem))
         if pTreeViewNode then 
            return *pTreeViewNode
         else
            bHit = false
         end if      
      end if
      
      if bHit = false then
         ' Need to return a reference otherwise crash if trying to access the return reference.
         static tvNode as wfxTreeNode   
         return tvNode
      end if
   end if
end function

function wfxTreeView.GetNodeAt( byval pt as POINT ) byref as wfxTreeNode
   return this.GetNodeAt( pt.x, pt.y )
end function

function wfxTreeView.GetNodeAt( byval pt as wfxPoint ) byref as wfxTreeNode
   return this.GetNodeAt( pt.pt.x, pt.pt.y )
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
   this.BeginUpdate
   for i as long = 0 to this.Nodes.count - 1
      ' Set the hWindow for the collection
      this.Node(i).hWindow = this.hWindow
      this.Node(i).hNode = _
         TreeView_AddRootItem( this.hWindow, this.Node(i).Text, this.Node(i).Data32 )
      this.PopulateTree( this.Node(i) )
   next
   this.EndUpdate      

   _IsLoading = false

   function = 0
END FUNCTION



'' TreeView Node

destructor wfxTreeNode
   ? "Destructor: "; this.text 
end destructor

property wfxTreeNode.hNode() as HTREEITEM
   property = _hNode
end property

property wfxTreeNode.hNode( byVal nValue as HTREEITEM)
   _hNode = nValue
end property

property wfxTreeNode.hWindow() as hwnd
   property = _hWindow
end property

property wfxTreeNode.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

Property wfxTreeNode.Selected() As boolean
   if this.hWindow then 
      dim as HTREEITEM hItem = TreeView_GetSelection( this.hWindow )
      _Selected = iif( hItem = this.hNode, true, false )
   end if
   property = _Selected
END PROPERTY

property wfxTreeNode.Selected( ByVal nValue As boolean) 
   if this.hWindow then 
      TreeView_SelectItem( this.hWindow, iif(nValue, this.hNode, 0) )
   end if
   _Selected = nValue
END PROPERTY

Property wfxTreeNode.Checked() As boolean
   if this.hWindow then 
      _Checked = TreeView_IsItemChecked( this.hWindow, this.hNode )
   end if
   property = _Checked
END PROPERTY

property wfxTreeNode.Checked( ByVal nValue As boolean) 
   if this.hWindow then 
      TreeView_SetCheckState( this.hWindow, this.hNode, nValue )
   end if
   _Checked = nValue
END PROPERTY

property wfxTreeNode.Index() as long
   property = _Index
End Property

property wfxTreeNode.Index( ByVal nValue As long) 
   _Index = nValue
END PROPERTY

property wfxTreeNode.Text() as CWSTR
   if this.hWindow then 
      DIM wszText AS WSTRING * 260
      TreeView_GetItemText( this.hWindow, this.hNode, @wszText, 260)
      _Text = wszText
   end if   
   property = _Text 
end property

property wfxTreeNode.Text( byref wszValue as wstring )
   if this.hWindow then 
      TreeView_SetItemText( this.hWindow, this.hNode, wszValue )
   end if
   _Text = wszValue
end property

property wfxTreeNode.Data32() as long
   ' The Data32 is only held in the classes, not the TreeView itself. The lParam
   ' of the Treeview node is actually a pointer to the TreeViewNode class for
   ' this node. That makes it fast to cross reference between the class and the node.
   property = _Data32
end property

property wfxTreeNode.Data32( byval nValue as long )
   _Data32 = nValue
end property

Function wfxTreeNode.Node( ByVal nIndex As Long ) ByRef As wfxTreeNode
   return this.Nodes.ByIndex(nIndex)
END function

function wfxTreeNode.Nodes byref As wfxTreeSubNodeCollection
   return this._NodesCollection 
END function



'' NODESCOLLECTION
constructor wfxTreeNodeCollection
   '
END CONSTRUCTOR

destructor wfxTreeNodeCollection
   '
end destructor

property wfxTreeNodeCollection.hWindow() as hwnd
   property = _hWindow
end property

property wfxTreeNodeCollection.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

function wfxTreeNodeCollection.Count() as Long
   function = _Collection.Size
end function

Function wfxTreeNodeCollection.Add( ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
   Dim pData As wfxTreeNode Ptr = New wfxTreeNode
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
      ' Redraw to ensure that +/- shows
      AfxRedrawWindow( this.hWindow )
   end if      
   function = pData->Index
end function

Function wfxTreeNodeCollection.Insert( ByVal nIndex As Long, ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
   Dim pData As wfxTreeNode Ptr = New wfxTreeNode
   pData->hWindow = this.hWindow
   pData->Index = nIndex
   pData->Text = wszValue
   pData->Data32 = nValue
   _Collection.Insert( nIndex, ControlType.TreeView, pData ) 
   function = pData->Index
end function

function wfxTreeNodeCollection.DeallocateNodes( byref ParentNode as wfxTreeNode ) as Long
   for i as long = 0 to ParentNode.Nodes.count - 1
      this.DeallocateNodes( ParentNode.Node(i) )
   next      
   delete cast(wfxTreeNode ptr, @ParentNode)
   _Collection.Clear
   function = 0
end function

function wfxTreeNodeCollection.Remove( byval nIndex as long ) as long
   dim pNode as wfxLListNode ptr = _Collection.get_index(nIndex)
   if pNode then
      dim pTreeNode as wfxTreeNode ptr = cast(wfxTreeNode ptr, pNode->pData)
      if pTreeNode then
         ' Delete any subnodes in any TreeNode collection (use recursion)
         for i as long = 0 to pTreeNode->Nodes.Count - 1
            this.DeallocateNodes( pTreeNode->Node(i) )
         next
         if this.hWindow then TreeView_DeleteItem( this.hWindow, pTreeNode->hNode )
         Delete pTreeNode
         _Collection.Remove(pNode)
         ' Renumber the Index property for each node in the collection.
         for i as long = 0 to _Collection.Size - 1
            pNode = _Collection.get_index(i)
            pTreeNode = cast(wfxTreeNode ptr, pNode->pData)
            if pTreeNode then pTreeNode->Index = i
         next
      end if
   end if   
   function = _Collection.Size
end function

function wfxTreeNodeCollection.ByIndex( byval nIndex as long ) byref as wfxTreeNode 
   dim pItem as wfxTreeNode ptr
   dim pNode as wfxLListNode ptr
   if _Collection.Size then
      if (nIndex >= 0) and (nIndex <= _Collection.Size - 1) then
         pNode = _Collection.get_index(nIndex)
         if pNode then
            pItem = cast(wfxTreeNode ptr, pNode->pData)
            return *pItem
         end if
      end if      
   end if   
end function

function wfxTreeNodeCollection.Clear() as long
   ' Deallocate elements in the nodes collection.
   dim pTreeNode as wfxTreeNode ptr
   dim pNode as wfxLListNode ptr = _Collection.get_first
   for i as long = 0 to _Collection.Size - 1
      pNode = _Collection.get_index(i)
      pTreeNode = cast(wfxTreeNode ptr, pNode)
      if pTreeNode then
         pTreeNode->Selected = false 
         if this.hWindow then TreeView_DeleteItem( this.hWindow, pTreeNode->hNode )
         ' Delete TreeViewItem fires destructor that clears any subitems
         Delete pTreeNode
      end if
   next
   _Collection.Clear
   function = 0
END FUNCTION


'' SUBNODESCOLLECTION
constructor wfxTreeSubNodeCollection
   '
END CONSTRUCTOR

destructor wfxTreeSubNodeCollection
   '
end destructor

property wfxTreeSubNodeCollection.hParentNode() as HTREEITEM
   property = _hParentNode
end property

property wfxTreeSubNodeCollection.hParentNode( byVal nValue as HTREEITEM)
   _hParentNode = nValue
end property

property wfxTreeSubNodeCollection.hWindow() as hwnd
   property = _hWindow
end property

property wfxTreeSubNodeCollection.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

function wfxTreeSubNodeCollection.Count() as Long
   function = _Collection.Size
end function

Function wfxTreeSubNodeCollection.Add( ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
   function = this.Insert( -1, wszValue, nValue )
end function

Function wfxTreeSubNodeCollection.Insert( ByVal nIndex As Long, ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
   if (nIndex < 0) or (nIndex > this.Count - 1) then nIndex = (this.Count - 1) + 1
   
   Dim pData As wfxTreeNode Ptr = New wfxTreeNode
   pData->hWindow = this.hWindow
   pData->Text    = wszValue
   pData->Data32  = nValue
   pData->Index   = nIndex
   
   If this.hWindow Then 
      ' Get the HTREEITEM of the node immediately before the one to insert
      dim as HTREEITEM hInsertAfter = iif( this.Count, this.ByIndex(nIndex - 1).hNode, TVI_LAST) 
      pData->hNode = TreeView_AddItem( this.hWindow, this.hParentNode, hInsertAfter, wszValue, cast(LPARAM, pData) )
      pData->Nodes.hParentNode = pData->hNode    
      ' Redraw to ensure that +/- shows
      AfxRedrawWindow( this.hWindow )
   end if
   _Collection.Insert( nIndex, ControlType.TreeView, pData ) 
   
   function = pData->Index
end function

function wfxTreeSubNodeCollection.DeallocateNodes( byref ParentNode as wfxTreeNode ) as Long
   for i as long = 0 to ParentNode.Nodes.count - 1
      this.DeallocateNodes( ParentNode.Node(i) )
   next      
   delete cast(wfxTreeNode ptr, @ParentNode)
   _Collection.Clear
   function = 0
end function

function wfxTreeSubNodeCollection.Remove( byval nIndex as long ) as long
   dim pNode as wfxLListNode ptr = _Collection.get_index(nIndex)
   if pNode then
      dim pTreeNode as wfxTreeNode ptr = cast(wfxTreeNode ptr, pNode->pData)
      if pTreeNode then
         ' Delete any subnodes in any TreeNode collection (use recursion)
         for i as long = 0 to pTreeNode->Nodes.Count - 1
            this.DeallocateNodes( pTreeNode->Node(i) )
         next
         if this.hWindow then TreeView_DeleteItem( this.hWindow, pTreeNode->hNode )
         Delete pTreeNode
         _Collection.Remove(pNode)
         ' Renumber the Index property for each node in the collection.
         for i as long = 0 to _Collection.Size - 1
            pNode = _Collection.get_index(i)
            pTreeNode = cast(wfxTreeNode ptr, pNode->pData)
            if pTreeNode then pTreeNode->Index = i
         next
      end if
   end if   
   function = _Collection.Size
end function

function wfxTreeSubNodeCollection.ByIndex( byval nIndex as long ) byref as wfxTreeNode 
   dim pItem as wfxTreeNode ptr
   dim pNode as wfxLListNode ptr
   if _Collection.Size then
      if (nIndex >= 0) and (nIndex <= _Collection.Size - 1) then
         pNode = _Collection.get_index(nIndex)
         if pNode then
            pItem = cast(wfxTreeNode ptr, pNode->pData)
            return *pItem
         end if
      end if      
   end if   
end function

function wfxTreeSubNodeCollection.Clear() as long
   ' Deallocate elements in the nodes collection.
   dim pTreeNode as wfxTreeNode ptr
   dim pNode as wfxLListNode ptr = _Collection.get_first
   for i as long = 0 to _Collection.Size - 1
      pNode = _Collection.get_index(i)
      pTreeNode = cast(wfxTreeNode ptr, pNode)
      if pTreeNode then
         pTreeNode->Selected = false 
         if this.hWindow then TreeView_DeleteItem( this.hWindow, pTreeNode->hNode )
         Delete pTreeNode
      end if
   next
   _Collection.Clear
   function = 0
END FUNCTION


