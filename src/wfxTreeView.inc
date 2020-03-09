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

'property wfxTreeView.SelectedNode() byref as wfxTreeNode
'   dim pTreeViewNode as wfxTreeNode ptr
'   dim as HTREEITEM hItem
'   if this.hWindow then
'      hItem = TreeView_GetSelection( this.hWindow )
'      if hItem then
'         pTreeViewNode = cast(wfxTreeNode ptr, TreeView_GetlParam( this.hWindow, hItem))
'         if pTreeViewNode then 
'            _SelectedNode = *pTreeViewNode
'            this.pSelectedNode = pTreeViewNode
'         end if   
'      end if
'   end if
'   if (hItem = 0) or (pTreeViewNode = 0) then
'      ' Need to return a reference otherwise crash if trying to access the return reference.
'      static tvNode as wfxTreeNode
'      _SelectedNode = tvNode
'   end if
'   _SelectedNode.pTreeView = @this
'   property = _SelectedNode
'end property

'property wfxTreeView.SelectedNode( byval hItem as HTREEITEM )
'   if this.hWindow then
'      TreeView_SelectItem( this.hWindow, hItem )
'      dim pTreeViewNode as wfxTreeNode ptr = cast(wfxTreeNode ptr, TreeView_GetlParam( this.hWindow, hItem))
'      if pTreeViewNode then _SelectedNode = *pTreeViewNode 
'   end if
'end property

'property wfxTreeView.SelectedNode( byref tvNode as wfxTreeNode )
'   if this.hWindow then
'      TreeView_SelectItem( this.hWindow, tvNode.hNode )
'   end if
'   _SelectedNode = tvNode
'end property

function wfxTreeView.GetSelectedNode() byref as wfxTreeNode
   dim pTreeViewNode as wfxTreeNode ptr
   dim as HTREEITEM hItem
   if this.hWindow then
      hItem = TreeView_GetSelection( this.hWindow )
      if hItem then
         pTreeViewNode = cast(wfxTreeNode ptr, TreeView_GetlParam( this.hWindow, hItem))
         if pTreeViewNode then 
            _SelectedNode = *pTreeViewNode
            this.pSelectedNode = pTreeViewNode
         end if   
      end if
   end if
   if (hItem = 0) or (pTreeViewNode = 0) then
      ' Need to return a reference otherwise crash if trying to access the return reference.
      static tvNode as wfxTreeNode
      _SelectedNode = tvNode
      ' Do not set the pTreeView for the Nodes collection because we test for
      ' an empty pointer in Add/Insert to differentiate that this is a fake node.
   end if
   _SelectedNode.pTreeView = @this
   function = _SelectedNode
end function

function wfxTreeView.SetSelectedNode( byval hItem as HTREEITEM ) as Long
   if this.hWindow then
      TreeView_SelectItem( this.hWindow, hItem )
      dim pTreeViewNode as wfxTreeNode ptr = cast(wfxTreeNode ptr, TreeView_GetlParam( this.hWindow, hItem))
      if pTreeViewNode then _SelectedNode = *pTreeViewNode 
   end if
   function = 0
end function

function wfxTreeView.SetSelectedNode( byref tvNode as wfxTreeNode ) as Long
   if this.hWindow then
      TreeView_SelectItem( this.hWindow, tvNode.hNode )
   end if
   _SelectedNode = tvNode
   function = 0
end function

Property wfxTreeView.pSelectedNode(byval nValue as wfxTreeNode ptr) 
   _pSelectedNode = nValue  
end property

Property wfxTreeView.pSelectedNode() as wfxTreeNode ptr
   property = _pSelectedNode
end property

' TreeNode is used to hold a reference to the node that is currently
' being acted on for messages like OnBeforeCollapse, OnAfterCollapse, etc.
property wfxTreeView.TreeNode() byref as wfxTreeNode
   property = _TreeNode
end property

property wfxTreeView.TreeNode( byref tvItem as wfxTreeNode )
   _TreeNode = tvItem
end property

Property wfxTreeView.Sorted() As boolean
   property = _Sorted
end property

property wfxTreeView.Sorted( byval nValue as boolean )
   ' If the TreeView is switched from Non-Sorted to Sorted then
   ' do a resorting of all of the nodes in the control.
   if (_Sorted = false) and (nValue = true) then
      ' Sort the root nodes and then all of the child nodes off of the root
      TreeView_SortChildren( this.hWindow, 0, false )
      for i as long = 0 to this.Nodes.Count - 1
         TreeView_SortChildren( this.hWindow, this.Node(i).hNode, true )
      next
   end if
   _Sorted = nValue
end property

function wfxTreeView.Sort() as Long
   ' Re-sort the treeview by simply simply turning sort off and on again.
   this.Sorted = false
   this.Sorted = true
   function = 0
end function


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
      ParentNode.Nodes.pTreeView = ParentNode.pTreeView
      ParentNode.Node(i).pTreeView = ParentNode.pTreeView
      ParentNode.Node(i).hNode = _
         TreeView_AppendItem( this.hWindow, ParentNode.hNode, _
                              LPSTR_TEXTCALLBACK, ParentNode.Node(i).Data32 )
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
         tvNode.pTreeView = @this   
         ' Do not set the pTreeView for the Nodes collection because we test for
         ' an empty pointer in Add/Insert to differentiate that this is a fake node.
         return tvNode
      end if
   end if
end function

function wfxTreeView.GetNodeAt( byval pt as POINT ) byref as wfxTreeNode
   return this.GetNodeAt( pt.x, pt.y )
end function

function wfxTreeView.GetNodeAt( byval wpt as wfxPoint ) byref as wfxTreeNode
   return this.GetNodeAt( wpt.pt.x, wpt.pt.y )
end function


function wfxTreeView.RecurseTreeNodeSearch( byref ParentNode as wfxTreeNode, _ 
                                            byval pTreeNode as wfxTreeNode ptr _
                                            ) as boolean
   for i as long = 0 to ParentNode.Nodes.count - 1
      if @ParentNode.Node(i) = pTreeNode then
         ParentNode.Nodes.Remove(i)
         return true
      end if   
      if this.RecurseTreeNodeSearch( ParentNode.Node(i), pTreeNode ) = true then return true
   next      
   function = false
end function

function wfxTreeView.Remove( byval pTreeNode as wfxTreeNode ptr ) as boolean
   if pTreeNode = 0 then return false
   for i as long = 0 to this.Nodes.count - 1
      if @this.Node(i) = pTreeNode then
         this.Nodes.Remove(i)
         return true
      end if
      if this.RecurseTreeNodeSearch( this.Node(i), pTreeNode ) then return true
   next
   function = false
END function

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
   dim as long dwStyle = WS_CLIPCHILDREN or TVS_INFOTIP or TVS_DISABLEDRAGDROP 
   ' TreeView will eat the WM_LBUTTONUP message if TVS_DISABLEDRAGDROP is not specified
   
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
   
   ' No need to apply the Sorted property because it is applied every time a new node is inserted.
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
      
   ' Pass the Treeview pointer down to the subnode collection
   this.Nodes.pTreeView = @this
   
   ' Recursively load all of the nodes...
   this.BeginUpdate
   for i as long = 0 to this.Nodes.count - 1
      this.Node(i).pTreeView = @this
      this.Node(i).hNode = _
         TreeView_AddRootItem( this.hWindow, LPSTR_TEXTCALLBACK, this.Node(i).Data32 )
      this.PopulateTree( this.Node(i) )
   next
   this.EndUpdate      

   function = 0
END FUNCTION



'' TreeView Node

destructor wfxTreeNode
   '
end destructor

property wfxTreeNode.hNode() as HTREEITEM
   property = _hNode
end property

property wfxTreeNode.hNode( byVal nValue as HTREEITEM)
   _hNode = nValue
end property

Property wfxTreeNode.pTreeView() as wfxTreeView ptr
   property = _pTreeView 
end property

Property wfxTreeNode.pTreeView( ByVal ptv as wfxTreeView ptr)
   _pTreeView = ptv
end property

Property wfxTreeNode.Selected() As boolean
   if this.pTreeview->hWindow then 
      dim as HTREEITEM hItem = TreeView_GetSelection( this.pTreeview->hWindow )
      _Selected = iif( hItem = this.hNode, true, false )
   end if
   property = _Selected
END PROPERTY

property wfxTreeNode.Selected( ByVal nValue As boolean) 
   if this.pTreeview->hWindow then 
      TreeView_SelectItem( this.pTreeview->hWindow, iif(nValue, this.hNode, 0) )
   end if
   _Selected = nValue
END PROPERTY

Property wfxTreeNode.Checked() As boolean
   if this.pTreeview->hWindow then 
      _Checked = TreeView_IsItemChecked( this.pTreeview->hWindow, this.hNode )
   end if
   property = _Checked
END PROPERTY

property wfxTreeNode.Checked( ByVal nValue As boolean) 
   if this.pTreeview->hWindow then 
      TreeView_SetCheckState( this.pTreeview->hWindow, this.hNode, nValue )
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
   property = _Text 
end property

property wfxTreeNode.Text( byref wszValue as wstring )
   _Text = wszValue
end property

property wfxTreeNode.ToolTipText() as CWSTR
   property = _ToolTipText 
end property

property wfxTreeNode.ToolTipText( byref wszValue as wstring )
   _ToolTipText = wszValue
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

function wfxTreeNode.Remove() as boolean
   ' Per FreeBasic Help file:
   ' The arrays of references and the non-static reference fields for UDT are not supported yet.
   ' Therefore we have to return a copy to _SelectedNode rather than a reference. This is a 
   ' shame because now we have to do special additional checks when performing methods such
   ' as Remove.
   if this.Selected then
      return this.pTreeView->Remove( this.pTreeView->pSelectedNode ) 
   else   
      return this.pTreeView->Remove( @this ) 
   end if
END function

function wfxTreeNode.Expand() as long
   if this.pTreeView then
      TreeView_Expand( this.pTreeView->hWindow, this.hNode, TVE_EXPAND)
   end if
   function = 0
end function

function wfxTreeNode.ExpandAll() as long
   if this.pTreeView then
      this.pTreeView->BeginUpdate
      TreeView_ExpandAllChildItems( this.pTreeView->hWindow, this.hNode )
      this.pTreeView->EndUpdate
   end if
   function = 0
end function

function wfxTreeNode.Collapse() as long
   if this.pTreeView then
      TreeView_Expand( this.pTreeView->hWindow, this.hNode, TVE_COLLAPSE)
   end if
   function = 0
end function

function wfxTreeNode.EnsureVisible() as long
   if this.pTreeView then
      TreeView_EnsureVisible( this.pTreeView->hWindow, this.hNode )
   end if
   function = 0
end function

function wfxTreeNode.SortChildren() as long
   if this.pTreeView then
      TreeView_SortChildren( this.pTreeView->hWindow, this.hNode, false )
   end if
   function = 0
end function



'' NODESCOLLECTION
constructor wfxTreeNodeCollection
   '
END CONSTRUCTOR

destructor wfxTreeNodeCollection
   '
end destructor

Property wfxTreeNodeCollection.pTreeView() as wfxTreeView ptr
   property = _pTreeView 
end property

Property wfxTreeNodeCollection.pTreeView( ByVal ptv as wfxTreeView ptr)
   _pTreeView = ptv
end property

function wfxTreeNodeCollection.Count() as Long
   function = _Collection.Size
end function

Function wfxTreeNodeCollection.Add( ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
   function = this.Insert( -1, wszValue, nValue )
end function

Function wfxTreeNodeCollection.Insert( ByVal nIndex As Long, ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
   ' Test the pTreeView pointer. If it is Null then this action is
   ' originating from the fake SelectNode node.
   if this.pTreeview = 0 then exit function

   ' If the TreeView has the Sorted property set to True then we will always
   ' append the node and allow the control to do the sorting. The collection 
   ' is not maintained in sorted order. 
   if this.pTreeView->Sorted then nIndex = -1
   if (nIndex < 0) or (nIndex > this.Count - 1) then nIndex = (this.Count - 1) + 1
   
   Dim pData As wfxTreeNode Ptr = New wfxTreeNode
   pData->pTreeView = this.pTreeview
   pData->Text      = wszValue
   pData->Data32    = nValue
   pData->Index     = nIndex

   If this.pTreeview->hWindow Then 
      ' Get the HTREEITEM of the node immediately before the one to insert
      dim as HTREEITEM hInsertAfter = iif( this.Count, this.ByIndex(nIndex - 1).hNode, TVI_LAST) 
      if this.pTreeView->Sorted then hInsertAfter = TVI_SORT
      pData->hNode = TreeView_AddRootItem( this.pTreeview->hWindow, LPSTR_TEXTCALLBACK, cast(LPARAM, pData) )
      pData->Nodes.hParentNode = pData->hNode    
      pData->Nodes.pTreeView = this.pTreeview
      ' Redraw to ensure that +/- shows
      AfxRedrawWindow( this.pTreeview->hWindow )
   end if
   _Collection.Insert( nIndex, ControlType.TreeView, pData ) 
   
   function = pData->Index
end function

function wfxTreeNodeCollection.DeallocateNodes( byref ParentNode as wfxTreeNode ) as Long
   for i as long = 0 to ParentNode.Nodes.count - 1
      this.DeallocateNodes( ParentNode.Node(i) )
   next      
   dim pTreeNode as wfxTreeNode ptr = cast(wfxTreeNode ptr, @ParentNode)
   delete pTreeNode
   _Collection.remove_bydata(pTreeNode)
   function = 0
end function

function wfxTreeNodeCollection.Remove( byval nIndex as long ) as long
   dim pNode as wfxLListNode ptr = _Collection.get_index(nIndex)
   if pNode then
      dim pTreeNode as wfxTreeNode ptr = cast(wfxTreeNode ptr, pNode->pData)
      if pTreeNode then 
         ' Delete any subnodes in TreeNode collection (use recursion)
         for i as long = 0 to pTreeNode->Nodes.Count - 1
            this.DeallocateNodes( pTreeNode->Node(i) )
         next
         if this.pTreeview->hWindow then TreeView_DeleteItem( this.pTreeview->hWindow, pTreeNode->hNode )
         Delete pTreeNode
         _Collection.Remove(pNode)
      end if
      ' Renumber the Index property for each node in the collection.
      for i as long = 0 to _Collection.Size - 1
         pNode = _Collection.get_index(i)
         pTreeNode = cast(wfxTreeNode ptr, pNode->pData)
         if pTreeNode then pTreeNode->Index = i
      next
   end if   
   function = _Collection.Size
end function

function wfxTreeNodeCollection.Clear() as long
   ' Deallocate elements in the nodes and any sub-treenodes that have collections.
   dim pTreeNode as wfxTreeNode ptr
   dim pNode as wfxLListNode ptr
   do until _Collection.Size = 0
      pNode = _Collection.get_index(0)
      pTreeNode = cast(wfxTreeNode ptr, pNode)
      if pTreeNode then
         ' Calling Remove will recursively delete all subnodes and remove from the collection.
         this.Remove(0)
      end if
   loop
   _Collection.Clear
   function = 0
END FUNCTION

function wfxTreeNodeCollection.ByIndex( byval nIndex as long ) byref as wfxTreeNode 
   dim pItem as wfxTreeNode ptr
   dim pNode as wfxLListNode ptr
   if (nIndex >= 0) and (nIndex <= _Collection.Size - 1) and (_Collection.Size > 0) then
      pNode = _Collection.get_index(nIndex)
      if pNode then
         pItem = cast(wfxTreeNode ptr, pNode->pData)
         return *pItem
      end if
   else
      ' Need to return a reference otherwise crash if trying to access the return reference.
      static tvNode as wfxTreeNode
      tvNode.pTreeView = this.pTreeView
      pItem = @tvNode
      return *pItem
   end if      
end function



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

Property wfxTreeSubNodeCollection.pTreeView() as wfxTreeView ptr
   property = _pTreeView 
end property

Property wfxTreeSubNodeCollection.pTreeView( ByVal ptv as wfxTreeView ptr)
   _pTreeView = ptv
end property

function wfxTreeSubNodeCollection.Count() as Long
   function = _Collection.Size
end function

Function wfxTreeSubNodeCollection.Add( ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
   function = this.Insert( -1, wszValue, nValue )
end function

Function wfxTreeSubNodeCollection.Insert( ByVal nIndex As Long, ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
   ' Test the pTreeView pointer. If it is Null then this action is
   ' originating from the fake SelectNode node.
   if this.pTreeview = 0 then exit function
   
   ' If the TreeView has the Sorted property set to True then we will always
   ' append the node and allow the control to do the sorting. The collection 
   ' is not maintained in sorted order. 
   if this.pTreeView->Sorted then nIndex = -1
   if (nIndex < 0) or (nIndex > this.Count - 1) then nIndex = (this.Count - 1) + 1
   
   Dim pData As wfxTreeNode Ptr = New wfxTreeNode
   pData->pTreeView = this.pTreeview
   pData->Text      = wszValue
   pData->Data32    = nValue
   pData->Index     = nIndex

   If this.pTreeview->hWindow Then 
      ' Get the HTREEITEM of the node immediately before the one to insert
      dim as HTREEITEM hInsertAfter = iif( this.Count, this.ByIndex(nIndex - 1).hNode, TVI_LAST)
      if this.pTreeView->Sorted then hInsertAfter = TVI_SORT
      pData->hNode = TreeView_AddItem( this.pTreeview->hWindow, this.hParentNode, hInsertAfter, LPSTR_TEXTCALLBACK, cast(LPARAM, pData) )
      pData->Nodes.hParentNode = pData->hNode    
      pData->Nodes.pTreeView = this.pTreeview
      ' Redraw to ensure that +/- shows
      AfxRedrawWindow( this.pTreeview->hWindow )
   end if
   _Collection.Insert( nIndex, ControlType.TreeView, pData ) 
   
   function = pData->Index
end function

function wfxTreeSubNodeCollection.DeallocateNodes( byref ParentNode as wfxTreeNode ) as Long
   for i as long = 0 to ParentNode.Nodes.count - 1
      this.DeallocateNodes( ParentNode.Node(i) )
   next      
   dim pTreeNode as wfxTreeNode ptr = cast(wfxTreeNode ptr, @ParentNode)
   delete pTreeNode
   _Collection.remove_bydata(pTreeNode)
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
         if this.pTreeview->hWindow then TreeView_DeleteItem( this.pTreeview->hWindow, pTreeNode->hNode )
         Delete pTreeNode
         _Collection.Remove(pNode)
      end if
      ' Renumber the Index property for each node in the collection.
      for i as long = 0 to _Collection.Size - 1
         pNode = _Collection.get_index(i)
         pTreeNode = cast(wfxTreeNode ptr, pNode->pData)
         if pTreeNode then pTreeNode->Index = i
      next
   end if   
   function = _Collection.Size
end function

function wfxTreeSubNodeCollection.Clear() as long
   ' Deallocate elements in the nodes and any sub-treenodes that have collections.
   dim pTreeNode as wfxTreeNode ptr
   dim pNode as wfxLListNode ptr
   do until _Collection.Size = 0
      pNode = _Collection.get_index(0)
      pTreeNode = cast(wfxTreeNode ptr, pNode)
      if pTreeNode then
         ' Calling Remove will recursively delete all subnodes and remove from the collection.
         this.Remove(0)
      end if
   loop
   _Collection.Clear
   function = 0
END FUNCTION

function wfxTreeSubNodeCollection.ByIndex( byval nIndex as long ) byref as wfxTreeNode 
   dim pItem as wfxTreeNode ptr
   dim pNode as wfxLListNode ptr
   if (nIndex >= 0) and (nIndex <= _Collection.Size - 1) and (_Collection.Size > 0) then
      pNode = _Collection.get_index(nIndex)
      if pNode then
         pItem = cast(wfxTreeNode ptr, pNode->pData)
         return *pItem
      end if
   else
      ' Need to return a reference otherwise crash if trying to access the return reference.
      static tvNode as wfxTreeNode
      tvNode.pTreeView = this.pTreeView
      pItem = @tvNode
      return *pItem
   end if      
end function

