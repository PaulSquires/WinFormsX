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
   return this.Nodes
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
'   If this.hWindow Then 
'      dim as DWORD dwExStyle = ListView_GetExtendedListViewStyle( this.hWindow )
'      _CheckBoxes = iif( dwExStyle and LVS_EX_CHECKBOXES, true, false )
'   End If
   Property = _CheckBoxes
End Property

property wfxTreeView.CheckBoxes( byval nValue as boolean )
'   If this.hWindow Then
'      dim as DWORD dwExStyle = ListView_GetExtendedListViewStyle( this.hWindow )
'      if nValue = false then
'         ListView_SetExtendedListViewStyle( this.hWindow, dwExStyle and (not LVS_EX_CHECKBOXES) )
'      else   
'         ListView_SetExtendedListViewStyle( this.hWindow, dwExStyle or LVS_EX_CHECKBOXES )
'      end if
'      this.Refresh
'   End If   
   _CheckBoxes = nValue
end property

Property wfxTreeView.FullRowSelect() As boolean
'   If this.hWindow Then 
'      dim as DWORD dwExStyle = ListView_GetExtendedListViewStyle( this.hWindow )
'      _FullRowSelect = iif( dwExStyle and LVS_EX_FULLROWSELECT, true, false )
'   End If
   Property = _FullRowSelect
End Property

property wfxTreeView.FullRowSelect( byval nValue as boolean )
'   If this.hWindow Then
'      dim as DWORD dwExStyle = ListView_GetExtendedListViewStyle( this.hWindow )
'      if nValue = false then
'         ListView_SetExtendedListViewStyle( this.hWindow, dwExStyle and (not LVS_EX_FULLROWSELECT) )
'      else   
'         ListView_SetExtendedListViewStyle( this.hWindow, dwExStyle or LVS_EX_FULLROWSELECT )
'      end if
'      this.Refresh
'   End If   
   _FullRowSelect = nValue
end property

Property wfxTreeView.HideSelection() As boolean
'   If this.hWindow Then 
'      _HideSelection = Iif( (AfxGetWindowStyle(this.hWindow) And LVS_SHOWSELALWAYS), false, true)
'   End If
   Property = _HideSelection
End Property

property wfxTreeView.HideSelection( byval nValue as boolean )
'   If this.hWindow Then 
'      AfxRemoveWindowStyle(this.hWindow, LVS_SHOWSELALWAYS)
'      If nValue = false Then AfxAddWindowStyle(this.hWindow, LVS_SHOWSELALWAYS)
'      this.Refresh
'   End If   
   _HideSelection = nValue
end property

property wfxTreeView.SelectedNode() byref as wfxTreeViewNode
'   if this.hWindow then 
'      _SelectedNode = this.Node(this.SelectedIndex)
'   end if
   property = _SelectedNode
end property

property wfxTreeView.SelectedNode( byref lbItem as wfxTreeViewNode )
'   if this.hWindow then 
'      ListView_SelectItem( this.hWindow, lbItem.Index )
'   end if
   _SelectedNode = lbItem
end property

Property wfxTreeView.Sorting() As SortOrder
'   if this.hWindow then 
'      if (AfxGetWindowStyle(this.hWindow) And LVS_SORTASCENDING) then
'         _Sorting = SortOrder.Ascending
'      elseif (AfxGetWindowStyle(this.hWindow) And LVS_SORTDESCENDING) then
'         _Sorting = SortOrder.Descending
'      else
'         _Sorting = SortOrder.None   
'      end if
'   end if
   property = _Sorting
end property

property wfxTreeView.Sorting( byval nValue as SortOrder )
'   if this.hWindow then 
'      AfxRemoveWindowStyle(this.hWindow, LVS_SORTASCENDING)
'      AfxRemoveWindowStyle(this.hWindow, LVS_SORTDESCENDING)
'      select case nValue 
'         case SortOrder.Ascending:  AfxAddWindowStyle(this.hWindow, LVS_SORTASCENDING)
'         case SortOrder.Descending: AfxAddWindowStyle(this.hWindow, LVS_SORTDESCENDING)
'      end select
'      this.Refresh
'   end if
   _Sorting = nValue
end property


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
   dim as long dwStyle = WS_CLIPCHILDREN 

   if _TabStop then dwStyle = dwStyle OR WS_TABSTOP 
   if _Visible THEN dwStyle = dwStyle OR WS_VISIBLE
   if _HideSelection = false then dwStyle = dwStyle OR TVS_SHOWSELALWAYS

 '        TVS_HASBUTTONS OR TVS_HASLINES OR TVS_LINESATROOT 

   
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

   ' Should we enable drag and drop files
   If this.AllowDrop Then DragAcceptFiles(this.hWindow, CTRUE)

   ' Apply properties that require a valid window handle
   this.Font        = _wfxFontPtr
   this.BorderStyle = _BorderStyle
   this.Enabled     = _Enabled

   this.BorderStyle        = _BorderStyle
   this.CheckBoxes         = _CheckBoxes
   this.FullRowSelect      = _FullRowSelect
   this.Sorting            = _Sorting

   if len(_ToolTip) then
      _hWndToolTip = AfxAddTooltip( this.hWindow, _ToolTip, _ToolTipBalloon, false )
   end if

   ' Do not set the focus/selected here because doing so will also Activate the form and
   ' cause an Activated message to be fired. We want the Form's Load event to
   ' complete before any Activate message.
   ' Refer to wfxForm.CreateFormInternal for the setting of the focus/selected
   ' control once events have fired correctly.
      
   ' Store the hWindow in the linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   dim pNode as wfxLListNode ptr = this.Parent->Controls.search_data(@this)
   if pNode then pNode->hWindow = this.hWindow
      
  
'   ' Set the text for the Items.
'   ListView_SetItemCount( this.hWindow, this.Nodes.Count )
    
'   For i As Long = 0 To this.Nodes.Count - 1
'      this.Node(i).hWindow = this.hWindow
'   Next
'   ListView_SelectItem( this.hWindow, _SelectedIndex )

'   ' Set the hWindow for the collection
'   this.Nodes.hWindow = this.hWindow
   _IsLoading = false

   function = 0
END FUNCTION



'' TreeView ITEM

destructor wfxTreeViewNode
   '
end destructor

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
   property = _Data32
end property

property wfxTreeViewNode.Data32( byval nValue as long )
   _Data32 = nValue
end property

Function wfxTreeViewNode.Node( ByVal nIndex As Long ) ByRef As _wfxTreeViewNode
   return this.Nodes.ByIndex(nIndex)
END function

function wfxTreeViewNode.Nodes byref As _wfxTreeViewNodesCollection
   return this.Nodes
END function




'' ITEMSCOLLECTION
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
   pData->Index = (this.Count - 1) + 1
   pData->Data32 = nValue
   pData->Nodes.Add( wszValue )
   _Collection.Add( ControlType.TreeView, pData ) 
'   If this.hWindow Then ListView_SetItemCount( this.hWindow, this.Count )
   function = pData->Index
end function

Function wfxTreeViewNodesCollection.Insert( ByVal nIndex As Long, ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
   Dim pData As wfxTreeViewNode Ptr = New wfxTreeViewNode
   pData->hWindow = this.hWindow
   pData->Index = nIndex
   pData->Data32 = nValue
   pData->Nodes.Add( wszValue )
   _Collection.Insert( nIndex, ControlType.TreeView, pData ) 
'   If this.hWindow Then ListView_SetItemCount( this.hWindow, this.Count )
   function = pData->Index
end function

function wfxTreeViewNodesCollection.Remove( byval nIndex as long ) as long
   dim pNode as wfxLListNode ptr = _Collection.get_index(nIndex)
   if pNode then
      ' Delete ListViewItem fires destructor that deletes any subitems
      Delete cast(wfxTreeViewNode ptr, pNode->pData)
      _Collection.Remove(pNode)
'      If this.hWindow Then ListView_SetItemCount( this.hWindow, this.Count )
   end if   
   function = _Collection.Size
end function

function wfxTreeViewNodesCollection.ByIndex( byval nIndex as long ) byref as wfxTreeViewNode 
   dim pItem as wfxTreeViewNode ptr
   dim pNode as wfxLListNode ptr
   pNode = _Collection.get_index(nIndex)
   if pNode then
      pItem = cast(wfxTreeViewNode ptr, pNode->pData)
      return *pItem
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



