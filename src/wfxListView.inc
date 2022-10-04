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

#include once "wfxListView.bi"


constructor wfxListView( byref wszName as wstring = "" )
   this.CtrlType    = ControlType.ListView
   this.Name        = wszName
   this.BackColor   = Colors.SystemWindow
   this.ForeColor   = Colors.SystemWindowText
   this.OddRowColor = this.BackColor
   this.HeaderForeColor = this.ForeColor
   this.HeaderBackColor = this.BackColor
end constructor

destructor wfxListView
   this.Columns.Clear
   this.Items.Clear
end destructor


Function wfxListView.Item( ByVal nIndex As Long ) ByRef As wfxListViewItem
   return this.Items.ByIndex(nIndex)
END function

function wfxListView.Items byref As wfxListViewItemsCollection
   return this._ItemsCollection
END function

Function wfxListView.Column( ByVal nIndex As Long ) ByRef As wfxListViewColumn
   return this.Columns.ByIndex(nIndex)
END function

function wfxListView.Columns byref As wfxListViewColumnsCollection
   return this._ColumnsCollection
END function

function wfxListView.BeginUpdate() As long
   SendMessage( this.hWindow, WM_SETREDRAW, false, 0 )
   this.Items.UpdateFlag = true
   for iRow as long = 0 to this.Items.Count - 1
      for iCol as long = 0 to this.Item(iRow).SubItems.Count - 1
         this.Item(iRow).SubItem(iCol).UpdateFlag = this.Items.UpdateFlag
      next 
   next
   function = 0
end function

function wfxListView.EndUpdate() as Long
   SendMessage( this.hWindow, WM_SETREDRAW, true, 0 )
   this.Items.UpdateFlag = false
   for iRow as long = 0 to this.Items.Count - 1
      for iCol as long = 0 to this.Item(iRow).SubItems.Count - 1
         this.Item(iRow).SubItem(iCol).UpdateFlag = this.Items.UpdateFlag
      next 
   next
   ListView_SetItemCountEx( this.hWindow, this.Items.Count, 0 )
   this.Refresh
   function = 0
end function

Property wfxListView.OddRowColorEnabled() As boolean
   Property = _OddRowColorEnabled
End Property

property wfxListView.OddRowColorEnabled( byval nValue as boolean )
   _OddRowColorEnabled = nValue
end property

property wfxListView.OddRowColor() as COLORREF
   property = _OddRowColor
end property

property wfxListView.OddRowColor( byval nValue as COLORREF )
   _OddRowColor = nValue
   if this.hWindow THEN AfxRedrawWindow(this.hWindow)
end property

property wfxListView.HeaderForeColor() as COLORREF
   property = _HeaderForeColor
end property

property wfxListView.HeaderForeColor( byval nValue as COLORREF )
   _HeaderForeColor = nValue
   if this.hWindow THEN AfxRedrawWindow(this.hWindow)
end property

property wfxListView.HeaderBackColor() as COLORREF
   property = _HeaderBackColor
end property

property wfxListView.HeaderBackColor( byval nValue as COLORREF )
   _HeaderBackColor = nValue
   if this.hWindow THEN AfxRedrawWindow(this.hWindow)
end property

property wfxListView.HeaderHeight() as long
   property = _HeaderHeight
end property

property wfxListView.HeaderHeight( byval nValue as long )
   _HeaderHeight = nValue
   if this.hWindow THEN AfxRedrawWindow(this.hWindow)
end property

Property wfxListView.BorderStyle() As ControlBorderStyle
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

Property wfxListView.BorderStyle( ByVal nValue As ControlBorderStyle )
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


property wfxListView.AllowColumnReorder() as boolean
   If this.hWindow Then 
      dim as DWORD dwExStyle = ListView_GetExtendedListViewStyle( this.hWindow )
      _AllowColumnReorder = iif( dwExStyle and LVS_EX_HEADERDRAGDROP, true, false )
   End If
   Property = _AllowColumnReorder
end property

property wfxListView.AllowColumnReorder( byval nValue as boolean )
   If this.hWindow Then 
      dim as DWORD dwExStyle = ListView_GetExtendedListViewStyle( this.hWindow )
      if nValue = false then
         ListView_SetExtendedListViewStyle( this.hWindow, dwExStyle and (not LVS_EX_HEADERDRAGDROP) )
      else   
         ListView_SetExtendedListViewStyle( this.hWindow, dwExStyle or LVS_EX_HEADERDRAGDROP )
      end if
      this.Refresh
   End If   
   _AllowColumnReorder = nValue
end property

Property wfxListView.CheckBoxes() As boolean
   If this.hWindow Then 
      dim as DWORD dwExStyle = ListView_GetExtendedListViewStyle( this.hWindow )
      _CheckBoxes = iif( dwExStyle and LVS_EX_CHECKBOXES, true, false )
   End If
   Property = _CheckBoxes
End Property

property wfxListView.CheckBoxes( byval nValue as boolean )
   If this.hWindow Then
      dim as DWORD dwExStyle = ListView_GetExtendedListViewStyle( this.hWindow )
      if nValue = false then
         ListView_SetExtendedListViewStyle( this.hWindow, dwExStyle and (not LVS_EX_CHECKBOXES) )
      else   
         ListView_SetExtendedListViewStyle( this.hWindow, dwExStyle or LVS_EX_CHECKBOXES )
      end if
      this.Refresh
   End If   
   _CheckBoxes = nValue
end property

Property wfxListView.FullRowSelect() As boolean
   If this.hWindow Then 
      dim as DWORD dwExStyle = ListView_GetExtendedListViewStyle( this.hWindow )
      _FullRowSelect = iif( dwExStyle and LVS_EX_FULLROWSELECT, true, false )
   End If
   Property = _FullRowSelect
End Property

property wfxListView.FullRowSelect( byval nValue as boolean )
   If this.hWindow Then
      dim as DWORD dwExStyle = ListView_GetExtendedListViewStyle( this.hWindow )
      if nValue = false then
         ListView_SetExtendedListViewStyle( this.hWindow, dwExStyle and (not LVS_EX_FULLROWSELECT) )
      else   
         ListView_SetExtendedListViewStyle( this.hWindow, dwExStyle or LVS_EX_FULLROWSELECT )
      end if
      this.Refresh
   End If   
   _FullRowSelect = nValue
end property

Property wfxListView.GridLines() As boolean
   If this.hWindow Then 
      dim as DWORD dwExStyle = ListView_GetExtendedListViewStyle( this.hWindow )
      _GridLines = iif( dwExStyle and LVS_EX_GRIDLINES, true, false )
   End If
   Property = _GridLines
End Property

property wfxListView.GridLines( byval nValue as boolean )
   If this.hWindow Then
      dim as DWORD dwExStyle = ListView_GetExtendedListViewStyle( this.hWindow )
      if nValue = false then
         ListView_SetExtendedListViewStyle( this.hWindow, dwExStyle and (not LVS_EX_GRIDLINES) )
      else   
         ListView_SetExtendedListViewStyle( this.hWindow, dwExStyle or LVS_EX_GRIDLINES )
      end if
      this.Refresh
   End If   
   _GridLines = nValue
end property

Property wfxListView.HideSelection() As boolean
   If this.hWindow Then 
      _HideSelection = Iif( (AfxGetWindowStyle(this.hWindow) And LVS_SHOWSELALWAYS), false, true)
   End If
   Property = _HideSelection
End Property

property wfxListView.HideSelection( byval nValue as boolean )
   If this.hWindow Then 
      AfxRemoveWindowStyle(this.hWindow, LVS_SHOWSELALWAYS)
      If nValue = false Then AfxAddWindowStyle(this.hWindow, LVS_SHOWSELALWAYS)
      this.Refresh
   End If   
   _HideSelection = nValue
end property

Property wfxListView.HeaderThemed() As boolean
   Property = _HeaderThemed
End Property

property wfxListView.HeaderThemed( byval nValue as boolean )
   _HeaderThemed = nValue
   If this.hWindow Then this.Refresh
end property

Property wfxListView.HeaderStyle() As ColumnHeaderStyle
   If this.hWindow Then 
      Dim As Long dwStyle = AfxGetWindowStyle(this.hWindow)
      If (dwStyle And LVS_NOCOLUMNHEADER) Then 
         _HeaderStyle  = ColumnHeaderStyle.None
      ElseIf (dwStyle And LVS_NOSORTHEADER) Then 
         _HeaderStyle  = ColumnHeaderStyle.NonClickable
      Else
         _HeaderStyle = ColumnHeaderStyle.Clickable   ' default
      End If
   End If
   Property = _HeaderStyle
End Property

Property wfxListView.HeaderStyle( ByVal nValue As ColumnHeaderStyle )
   if this.hWindow then 
      AfxRemoveWindowStyle(this.hWindow, LVS_NOSORTHEADER)
      AfxRemoveWindowStyle(this.hWindow, LVS_NOCOLUMNHEADER)
      Dim As Long dwStyle
      Select Case nValue
         Case ColumnHeaderStyle.NonClickable: dwStyle = LVS_NOSORTHEADER
         Case ColumnHeaderStyle.None: dwStyle = LVS_NOCOLUMNHEADER
         Case ColumnHeaderStyle.Clickable
      End Select
      AfxAddWindowStyle(this.hWindow, dwStyle)
   End If
   _HeaderStyle = nValue
end property

property wfxListView.LabelEdit() as boolean
   If this.hWindow Then 
      _LabelEdit = Iif( (AfxGetWindowStyle(this.hWindow) And LVS_EDITLABELS), True, False)
   End If   
   Property = _LabelEdit
end property

property wfxListView.LabelEdit( byval nValue as boolean )
   if this.hWindow then 
      AfxRemoveWindowStyle(this.hWindow, LVS_EDITLABELS)
      If nValue Then AfxAddWindowStyle(this.hWindow, LVS_EDITLABELS)
      this.Refresh
   End If   
   _LabelEdit = nValue
End Property

property wfxListView.SelectedItem() byref as wfxListViewItem
   if this.hWindow then 
      if this.SelectedIndex >= 0 then
         _SelectedItem = this.Item(this.SelectedIndex)
      end if   
   end if
   property = _SelectedItem
end property

property wfxListView.SelectedItem( byref lbItem as wfxListViewItem )
   if this.hWindow then 
      ListView_SelectItem( this.hWindow, lbItem.Index )
   end if
   _SelectedItem = lbItem
end property

property wfxListView.SelectedIndex() as long
   if this.hWindow then 
      _SelectedIndex = ListView_GetSelection( this.hWindow )
   end if
   property = _SelectedIndex
end property

property wfxListView.SelectedIndex( byval nValue as long )
   if this.hWindow then 
      ' Deselect all items in a multiple select ListView if -1 is passed.
      if (nValue = -1) and (this.MultiSelect = true) then
         ListView_UnSelectAllItems( this.hWindow )
      end if
      ListView_SelectItem( this.hWindow, nValue)
   end if
   ' Set the Item's Selected property to true if it is in range.
   if (nValue > -1) and (nValue < this.Items.Count) then
      this.Item(nValue).Selected = true
   end if
   _SelectedIndex = nValue
end property

property wfxListView.MultiSelect() as boolean
   if this.hWindow then 
      _MultiSelect = Iif( (AfxGetWindowStyle(this.hWindow) And LVS_SINGLESEL), false, True )
   End If   
   Property = _MultiSelect
end property

property wfxListView.MultiSelect( byval nValue as boolean )
   if this.hWindow then 
      AfxRemoveWindowStyle(this.hWindow, LVS_SINGLESEL)
      If nValue = false Then AfxAddWindowStyle(this.hWindow, LVS_SINGLESEL)
      this.Refresh
   End If   
   _MultiSelect = nValue
end property

Property wfxListView.Sorting() As SortOrder
   if this.hWindow then 
      if (AfxGetWindowStyle(this.hWindow) And LVS_SORTASCENDING) then
         _Sorting = SortOrder.Ascending
      elseif (AfxGetWindowStyle(this.hWindow) And LVS_SORTDESCENDING) then
         _Sorting = SortOrder.Descending
      else
         _Sorting = SortOrder.None   
      end if
   end if
   property = _Sorting
end property

property wfxListView.Sorting( byval nValue as SortOrder )
   if this.hWindow then 
      AfxRemoveWindowStyle(this.hWindow, LVS_SORTASCENDING)
      AfxRemoveWindowStyle(this.hWindow, LVS_SORTDESCENDING)
      select case nValue 
         case SortOrder.Ascending:  AfxAddWindowStyle(this.hWindow, LVS_SORTASCENDING)
         case SortOrder.Descending: AfxAddWindowStyle(this.hWindow, LVS_SORTDESCENDING)
      end select
      this.Refresh
   end if
   _Sorting = nValue
end property

function wfxListView.HitTest( byref iItem as long, byref iSubItem as long ) as Long
   dim as POINT pt
   GetCursorPos( @pt )
   ScreenToClient( this.hWindow, @pt )
   
   dim hitinfo as LVHITTESTINFO
   hitinfo.pt = pt

   iSubItem = -1
   
   iItem = ListView_SubItemHitTest( this.hWindow, @hitinfo ) 
   if iItem <> -1 then iSubItem = hitinfo.iSubItem
   
   function = iItem
end function



static Function wfxListView.HeaderSubclassProc ( _
                  ByVal hWin   As HWnd, _                 ' // Control window handle
                  ByVal uMsg   As UINT, _                 ' // Type of message
                  ByVal _wParam As WPARAM, _               ' // First message parameter
                  ByVal _lParam As LPARAM, _               ' // Second message parameter
                  ByVal uIdSubclass As UINT_PTR, _        ' // The subclass ID
                  ByVal dwRefData As DWORD_PTR _          ' // Pointer to reference data
                  ) As LRESULT

   Select Case uMsg

      CASE HDM_LAYOUT
         ' Fill the WINDOWPOS structure with the appropriate size and position of the
         ' header control and change the top position of the rectangle that the header
         ' control will occupy.
         dim pListView as wfxListView ptr = cast( wfxListView ptr, dwRefData )
         if pListView then
            dim phdl AS HDLAYOUT PTR = cast(HDLAYOUT PTR, _lParam)
            phdl->pwpos->hwnd = hWin
            phdl->pwpos->flags = SWP_FRAMECHANGED
            phdl->pwpos->x = phdl->prc->Left
            phdl->pwpos->y = 0
            ' scale the size for high dpi
            phdl->pwpos->cx = pListView->Parent->ScaleX(phdl->prc->Right - phdl->prc->Left)
            phdl->pwpos->cy = pListView->Parent->ScaleY( pListView->HeaderHeight )
            phdl->prc->Top  = pListView->Parent->ScaleY( pListView->HeaderHeight )
            return true
         end if


      Case WM_DESTROY
         ' REQUIRED: Remove control subclassing
         RemoveWindowSubclass( hWin, @wfxListView.HeaderSubclassProc, uIdSubclass )
   End Select
    
   ' For messages that we don't deal with
   Function = DefSubclassProc(hWin, uMsg, _wParam, _lParam)

end function


function wfxListView.Show(byval hWndParent as hwnd = 0) as long

   dim wszClassName as wstring * MAX_PATH
   
   ' If the control is created but simply hidden, then show it.
   if this.hWindow THEN
      ShowWindow(this.hWindow, SW_SHOW)
      exit function
   END IF

   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function
      
   this.Columns.Clear
   this.Items.Clear

   Dim As Long dwExStyle = 0
   dim as long dwStyle = WS_CLIPCHILDREN OR LVS_REPORT or LVS_OWNERDATA

   if _TabStop then dwStyle = dwStyle OR WS_TABSTOP 
   if _Visible THEN dwStyle = dwStyle OR WS_VISIBLE
   if _HideSelection = false then dwStyle = dwStyle OR LVS_SHOWSELALWAYS
   if _MultiSelect = false then dwStyle = dwStyle OR LVS_SINGLESEL
   
   select case _HeaderStyle
      case ColumnHeaderStyle.None
         dwStyle = dwStyle or LVS_NOCOLUMNHEADER
      case ColumnHeaderStyle.NonClickable
         dwStyle = dwStyle or LVS_NOSORTHEADER
      case ColumnHeaderStyle.Clickable   ' default
   end select

   _CtrlID = this.Parent->GetNextCtrlID()

   this.hWindow = this.Parent->pWindow->AddControl ( _
         "SysListView32", _                      ' // Class name
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

   ListView_SetExtendedListViewStyleEx( this.hWindow, LVS_EX_FLATSB, LVS_EX_FLATSB )
   ListView_SetExtendedListViewStyleEx( this.hWindow, LVS_EX_DOUBLEBUFFER, LVS_EX_DOUBLEBUFFER )
   
   ' Should we enable drag and drop files
   If this.AllowDrop Then DragAcceptFiles(this.hWindow, CTRUE)

   ' Apply properties that require a valid window handle
   this.Font        = _wfxFontPtr
   this.BorderStyle = _BorderStyle
   this.Enabled     = _Enabled

   this.AllowColumnReorder = _AllowColumnReorder
   this.BorderStyle        = _BorderStyle
   this.CheckBoxes         = _CheckBoxes
   this.FullRowSelect      = _FullRowSelect
   this.GridLines          = _GridLines
   this.Sorting            = _Sorting
   this.ToolTip            = _ToolTip

   ' Do not set the focus/selected here because doing so will also Activate the form and
   ' cause an Activated message to be fired. We want the Form's Load event to
   ' complete before any Activate message.
   ' Refer to wfxForm.CreateFormInternal for the setting of the focus/selected
   ' control once events have fired correctly.
      
   ' Store the hWindow in the linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   dim pNode as wfxLListNode ptr = this.Parent->Controls.search_data(@this)
   if pNode then 
      pNode->hWindow = this.hWindow
      
      ' The header subclassing must occur before the columns are added.
      ' Get the handle of the ListView header control and subclass it
      dim hLvHeader AS hwnd = ListView_GetHeader(this.hWindow)
      IF hLvHeader THEN 
         if this.HeaderThemed = false then
            SetWindowSubclass( hLvHeader, Cast(SUBCLASSPROC, @wfxListView.HeaderSubclassProc), _CtrlID, Cast(DWORD_PTR, @this) )
         end if   
      end if
   end if

   ' Call internal class function to setup the columns
   this.Columns.hWindow = this.hWindow
   For i As Long = 0 To this.Columns.Count - 1
      this.Column(i).hWindow = this.hWindow
   Next
   this.Columns.SetupColumns_Internal()
   
   ' Set the hWindow for the Items.
   For i As Long = 0 To this.Items.Count - 1
      this.Item(i).hWindow = this.hWindow
      this.Item(i).SubItems.hWindow = this.hWindow
   Next
   ListView_SetItemCountEx( this.hWindow, this.Items.Count, 0 )

   ListView_SelectItem( this.hWindow, _SelectedIndex )

   ' Set the hWindow for the collection
   this.Items.hWindow = this.hWindow
   _IsLoading = false

   function = 0
END FUNCTION



'' ListView COLUMN

property wfxListViewColumn.hWindow() as hwnd
   property = _hWindow
END PROPERTY

property wfxListViewColumn.hWindow( ByVal nValue As hwnd) 
   _hWindow = nValue
END PROPERTY

property wfxListViewColumn.Index() as long
   property = _Index
End Property

property wfxListViewColumn.Index( ByVal nValue As long) 
   _Index = nValue
END PROPERTY

property wfxListViewColumn.Text() as CWSTR
   dim wszText as wstring * MAX_PATH = _Text
   if this.hWindow then
      ListView_GetColumnText( this.hWindow, _Index, wszText, MAX_PATH )
   end if
   property = wszText
end property

property wfxListViewColumn.Text( byref wszValue as wstring )
   if this.hWindow then
      dim lvc as LVCOLUMN
      lvc.mask    = LVCF_TEXT
      lvc.pszText = @wszValue
      ListView_SetColumn( this.hWindow, _Index, @lvc )
   end if
   _Text = wszValue
end property

property wfxListViewColumn.Width() as long
   if this.hWindow then
      _Width = ListView_GetColumnWidth(this.hWindow, _Index) 
   end if
   property = _Width
end property

property wfxListViewColumn.Width( byval nValue as long )
   if this.hWindow then
      ListView_SetColumnWidth( this.hWindow, _Index, nValue )
   end if
   _Width = nValue
end property

property wfxListViewColumn.TextAlign() as TextAlignment
   if this.hWindow then
      dim lvc as LVCOLUMN
      lvc.mask = LVCF_FMT
      ListView_GetColumn( this.hWindow, _Index, @lvc )
      select case lvc.fmt
         case LVCFMT_LEFT:   _TextAlign = TextAlignment.Left
         case LVCFMT_RIGHT:  _TextAlign = TextAlignment.Right
         case LVCFMT_CENTER: _TextAlign = TextAlignment.Center
      end select
   end if
   property = _TextAlign
end property

property wfxListViewColumn.TextAlign( byval nValue as TextAlignment )
   if this.hWindow then
      dim lvc as LVCOLUMN
      lvc.mask = LVCF_FMT
      select case nValue
         case TextAlignment.Left:   lvc.fmt = LVCFMT_LEFT
         case TextAlignment.Right:  lvc.fmt = LVCFMT_RIGHT
         case TextAlignment.Center: lvc.fmt = LVCFMT_CENTER
      end select
      ListView_SetColumn( this.hWindow, _Index, @lvc )
   end if   
   _TextAlign = nValue
end property



'' ListView SUBITEM

destructor wfxListViewSubItem
   ' 
end destructor

property wfxListViewSubItem.hWindow() as hwnd
   property = _hWindow
END PROPERTY

property wfxListViewSubItem.hWindow( ByVal nValue As hwnd) 
   _hWindow = nValue
END PROPERTY

property wfxListViewSubItem.ItemIndex() as long
   property = _ItemIndex
end property

property wfxListViewSubItem.ItemIndex( byVal nValue as long)
   _ItemIndex = nValue
end property

property wfxListViewSubItem.Index() as long
   property = _Index
End Property

property wfxListViewSubItem.Index( ByVal nValue As long) 
   _Index = nValue
END PROPERTY

property wfxListViewSubItem.Text() as CWSTR
   property = _Text
end property

property wfxListViewSubItem.Text( byref wszValue as wstring )
   _Text = wszValue
   if this.hWindow THEN 
      if this.UpdateFlag = false then
         if ListView_IsItemVisible(this.hWindow, this.ItemIndex) then
            AfxRedrawWindow(this.hWindow)
         end if   
      end if
   end if
end property

property wfxListViewSubItem.BackColor() as COLORREF
   property = _BackColor
end property

property wfxListViewSubItem.BackColor( byval nValue as COLORREF )
   _BackColor = nValue
   if this.hWindow THEN 
      if this.UpdateFlag = false then
         if ListView_IsItemVisible(this.hWindow, this.ItemIndex) then
            AfxRedrawWindow(this.hWindow)
         end if   
      end if
   end if
end property

property wfxListViewSubItem.ForeColor() as COLORREF
   property = _ForeColor
end property

property wfxListViewSubItem.ForeColor( byval nValue as COLORREF )
   _ForeColor = nValue
   if this.hWindow THEN 
      if this.UpdateFlag = false then
         if ListView_IsItemVisible(this.hWindow, this.ItemIndex) then
            AfxRedrawWindow(this.hWindow)
         end if   
      end if
   end if
end property


'' SUBITEMSCOLLECTION
constructor wfxListViewSubItemsCollection
   '
END CONSTRUCTOR

destructor wfxListViewSubItemsCollection
   this.Clear
end destructor

property wfxListViewSubItemsCollection.ItemIndex() as long
   property = _ItemIndex
end property

property wfxListViewSubItemsCollection.ItemIndex( byVal nValue as long)
   _ItemIndex = nValue
end property

property wfxListViewSubItemsCollection.hWindow() as hwnd
   property = _hWindow
end property

property wfxListViewSubItemsCollection.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

function wfxListViewSubItemsCollection.Count() as Long
   function = _Collection.Size
end function

Function wfxListViewSubItemsCollection.Add( ByRef wszValue As WString = "" ) As Long
   Dim pData As wfxListViewSubItem Ptr = New wfxListViewSubItem
   if pData = 0 then exit function
   pData->UpdateFlag = this.UpdateFlag
   pData->hWindow = this.hWindow
   pData->ItemIndex = this.ItemIndex
   pData->Index = (this.Count - 1) + 1
   pData->Text = wszValue
   _Collection.Add( ControlType.ListView, pData ) 
   If this.hWindow Then 
      if this.UpdateFlag = false then
         if ListView_IsItemVisible(this.hWindow, pData->Index) then
            AfxRedrawWindow(this.hWindow)
         end if   
      end if
   end if
   function = pData->Index
end function

function wfxListViewSubItemsCollection.Remove( byval nIndex as long ) as long
   dim pNode as wfxLListNode ptr = _Collection.get_index(nIndex)
   if pNode then
       Delete cast(wfxListViewSubItem ptr, pNode->pData)
      _Collection.Remove(pNode)
   end if   
   If this.hWindow Then 
      if this.UpdateFlag = false then
         if ListView_IsItemVisible(this.hWindow, nIndex) then
            AfxRedrawWindow(this.hWindow)
         end if   
      end if
   end if
   function = _Collection.Size
end function

function wfxListViewSubItemsCollection.ByIndex( byval nIndex as long ) byref as wfxListViewSubItem 
   dim pItem as wfxListViewSubItem ptr
   dim pNode as wfxLListNode ptr
   ' Do array bounds check
   if _Collection.Size then
      if (nIndex >= 0) and (nIndex <= _Collection.Size - 1) then
         pNode = _Collection.get_index(nIndex)
         if pNode then
            pItem = cast(wfxListViewSubItem ptr, pNode->pData)
            return *pItem
         end if   
      end if
   end if
end function

function wfxListViewSubItemsCollection.Clear() as long
   ' Deallocate elements in the Items collection.
   dim pNode as wfxLListNode ptr 
   for i as long = 0 to _Collection.Size - 1
      pNode = _Collection.get_index(i)
      Delete cast(wfxListViewSubItem ptr, pNode->pData)
   next
   _Collection.Clear
   If this.hWindow Then 
      if this.UpdateFlag = false then
         AfxRedrawWindow(this.hWindow)
      end if
   end if
   function = 0
END FUNCTION


'' ListView ITEM

destructor wfxListViewItem
   ' Subitems Collection will automatically have its destructor
   ' called when the ListViewItem is destroyed.
end destructor

property wfxListViewItem.hWindow() as hwnd
   property = _hWindow
END PROPERTY

property wfxListViewItem.hWindow( ByVal nValue As hwnd) 
   _hWindow = nValue
END PROPERTY

Property wfxListViewItem.Selected() As boolean
   property = _Selected
END PROPERTY

property wfxListViewItem.Selected( ByVal nValue As boolean) 
   if this.hWindow then 
      SendMessage(this.hWindow, LB_SETSEL, nValue, cast(LPARAM, _Index) )
   end if
   _Selected = nValue
END PROPERTY

Property wfxListViewItem.Checked() As boolean
   property = _Checked
END PROPERTY

property wfxListViewItem.Checked( ByVal nValue As boolean) 
   _Checked = nValue
   if this.hWindow THEN 
      if ListView_IsItemVisible(this.hWindow, this.Index) then
         AfxRedrawWindow(this.hWindow)
      end if   
   end if
END PROPERTY

property wfxListViewItem.Index() as long
   property = _Index
End Property

property wfxListViewItem.Index( ByVal nValue As long) 
   _Index = nValue
END PROPERTY

property wfxListViewItem.Text() as CWSTR
   if this.SubItems.Count > 0 then
      property = this.SubItem(0).Text
   end if
end property

property wfxListViewItem.Text( byref wszValue as wstring )
   if this.SubItems.Count > 0 then
      this.SubItem(0).Text = wszValue
   end if   
end property

property wfxListViewItem.Data32() as long
   property = _Data32
end property

property wfxListViewItem.Data32( byval nValue as long )
   _Data32 = nValue
end property

property wfxListViewItem.BackColor() as COLORREF
   if this.SubItems.Count > 0 then
      property = this.SubItem(0).BackColor
   end if
end property

property wfxListViewItem.BackColor( byval nValue as COLORREF )
   if this.SubItems.Count > 0 then
      this.SubItem(0).BackColor = nValue
   end if
end property

property wfxListViewItem.ForeColor() as COLORREF
   if this.SubItems.Count > 0 then
      property = this.SubItem(0).ForeColor
   end if
end property

property wfxListViewItem.ForeColor( byval nValue as COLORREF )
   if this.SubItems.Count > 0 then
      this.SubItem(0).ForeColor = nValue
   end if   
end property

Function wfxListViewItem.SubItem( ByVal nIndex As Long ) ByRef As wfxListViewSubItem
   return this.SubItems.ByIndex(nIndex)
END function

function wfxListViewItem.SubItems byref As wfxListViewSubItemsCollection
   return this._SubItemsCollection
END function


'' COLUMNSCOLLECTION
constructor wfxListViewColumnsCollection
   '
END CONSTRUCTOR

destructor wfxListViewColumnsCollection
   this.Clear
end destructor

property wfxListViewColumnsCollection.hWindow() as hwnd
   property = _hWindow
end property

property wfxListViewColumnsCollection.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

function wfxListViewColumnsCollection.Count() as Long
   function = _Collection.Size
end function

' Internal function used to set up columns for the ListView
function wfxListViewColumnsCollection.SetupColumns_Internal() as Long   
   dim lvc as LVCOLUMN

   ' Delete all existing columns
   do until ListView_GetColumnCount( this.hWindow ) = 0
      ListView_DeleteColumn( this.hWindow, 0 )
   loop
   
   ' Add the columns for the ListView
   For i As Long = 0 To this.Count - 1
      ' Given the way the events are fired we want to get the raw text
      ' and width values from the class rather then the ones stored in
      ' the control itself, so hackthis by setting the hWindow to zero
      ' and then restoringit afterwards. 
      dim as hwnd hWin = this.hWindow
      this.ByIndex(i).hWindow = 0
      
      Dim As CWSTR wszText = this.ByIndex(i).Text
      dim as long nWidth = AfxScaleX( this.ByIndex(i).Width )

      lvc.mask  = LVCF_FMT
      select case this.ByIndex(i).TextAlign
         case TextAlignment.Left:   lvc.fmt = LVCFMT_LEFT
         case TextAlignment.Right:  lvc.fmt = LVCFMT_RIGHT
         case TextAlignment.Center: lvc.fmt = LVCFMT_CENTER
      end select
      this.ByIndex(i).hWindow = hWin
      
      dim as long idx = ListView_AddColumn( this.hWindow, i, wszText, nWidth )
      ListView_SetColumn( this.hWindow, idx, @lvc )
   next
   function = 0
end function

Function wfxListViewColumnsCollection.Add( ByRef wszValue As WString = "", _
                                           ByVal nWidth As Long = 100, _
                                           byval nTextAlign as TextAlignment = TextAlignment.Left _
                                           ) As Long
   Dim pData As wfxListViewColumn Ptr = New wfxListViewColumn
   pData->hWindow = this.hWindow
   pData->Index = (this.Count - 1) + 1
   pData->Text = wszValue
   pData->Width = nWidth
   pData->TextAlign = nTextAlign
   _Collection.Add( ControlType.ListView, pData ) 
   ' Call internal class function to setup the columns
   this.SetupColumns_Internal()
   function = pData->Index
end function

function wfxListViewColumnsCollection.Remove( byval nIndex as long ) as long
   dim pNode as wfxLListNode ptr = _Collection.get_index(nIndex)
   if pNode then
       Delete cast(wfxListViewColumn ptr, pNode->pData)
      _Collection.Remove(pNode)
   end if   

   ' Renumber the Index property for each item in the collectio.
   dim pListViewColumn as wfxListViewColumn ptr
   for i as long = 0 to _Collection.Size - 1
      pNode = _Collection.get_index(i)
      pListViewColumn = cast(wfxListViewColumn ptr, pNode->pData)
      if pListViewColumn then pListViewColumn->Index = i
   next

   ' Call internal class function to setup the columns
   this.SetupColumns_Internal()
   function = _Collection.Size
end function

function wfxListViewColumnsCollection.ByIndex( byval nIndex as long ) byref as wfxListViewColumn
   dim pItem as wfxListViewColumn ptr
   dim pNode as wfxLListNode ptr
   if _Collection.Size then
      if (nIndex >= 0) and (nIndex <= _Collection.Size - 1) then
         pNode = _Collection.get_index(nIndex)
         if pNode then
            pItem = cast(wfxListViewColumn ptr, pNode->pData)
            return *pItem
         end if   
      end if
   end if   
end function

function wfxListViewColumnsCollection.Clear() as long
   ' Deallocate elements in the Items collection.
   dim pNode as wfxLListNode ptr = _Collection.get_first
   do until pNode = 0
      Delete cast(wfxListViewColumn ptr, pNode->pData)
      pNode = _Collection.remove(pNode)
   LOOP
   ' Call internal class function to setup the columns
   this.SetupColumns_Internal()
   function = 0
END FUNCTION


'' ITEMSCOLLECTION
constructor wfxListViewItemsCollection
   '
END CONSTRUCTOR

destructor wfxListViewItemsCollection
   '
end destructor

property wfxListViewItemsCollection.hWindow() as hwnd
   property = _hWindow
end property

property wfxListViewItemsCollection.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

function wfxListViewItemsCollection.Count() as Long
   function = _Collection.Size
end function

Function wfxListViewItemsCollection.SelectedCount() As Long
   If this.hWindow Then
      Function = SendMessage( this.hWindow, LVM_GETSELECTEDCOUNT, 0, 0 )
   Else
      Dim As Long nSelCount = 0
      For i As Long = 0 To this.Count - 1
         If this.ByIndex(i).Selected Then
            nSelCount = nSelCount + 1
         End If
      Next    
      Function = nSelCount
   End If
End Function

Function wfxListViewItemsCollection.Add( ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
   Dim pData As wfxListViewItem Ptr = New wfxListViewItem
   if pData = 0 then exit function
   if this.hWindow then pData->hWindow = this.hWindow
   if this.hWindow then pData->SubItems.hWindow = this.hWindow
   pData->SubItems.UpdateFlag = pData->SubItems.UpdateFlag
   pData->Index = (this.Count - 1) + 1
   pData->Data32 = nValue
   pData->SubItems.ItemIndex = pData->Index
   pData->SubItems.Add( wszValue )
   _Collection.Add( ControlType.ListView, pData ) 
   If this.hWindow Then 
      if this.UpdateFlag = false then
         ListView_SetItemCountEx( this.hWindow, this.Count, 0 )
         if ListView_IsItemVisible(this.hWindow, pData->Index) then
            AfxRedrawWindow(this.hWindow)
         end if   
      end if
   end if
   function = pData->Index
end function

Function wfxListViewItemsCollection.Insert( ByVal nIndex As Long, ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
   Dim pData As wfxListViewItem Ptr = New wfxListViewItem
   if pData = 0 then exit function
   if this.hWindow then pData->hWindow = this.hWindow
   if this.hWindow then pData->SubItems.hWindow = this.hWindow
   pData->SubItems.UpdateFlag = pData->SubItems.UpdateFlag
   pData->Index = nIndex
   pData->Data32 = nValue
   pData->SubItems.Add( wszValue )
   _Collection.Insert( nIndex, ControlType.ListView, pData ) 

   ' Renumber the Index property for each item in the collection.
   dim pNode as wfxLListNode ptr 
   dim pListViewItem as wfxListViewItem ptr
   for i as long = 0 to _Collection.Size - 1
      pNode = _Collection.get_index(i)
      pListViewItem = cast(wfxListViewItem ptr, pNode->pData)
      if pListViewItem then 
         pListViewItem->Index = i
         pListViewItem->SubItems.ItemIndex = i
         for ii as long = 0 to pListViewItem->SubItems.Count - 1
            pListViewItem->SubItem(ii).ItemIndex = i
         next   
      end if
   next

   If this.hWindow Then 
      if this.UpdateFlag = false then
         ListView_SetItemCountEx( this.hWindow, this.Count, 0 )
         if ListView_IsItemVisible(this.hWindow, nIndex) then
            AfxRedrawWindow(this.hWindow)
         end if   
      end if   
   end if
   function = pData->Index
end function

function wfxListViewItemsCollection.Remove( byval nIndex as long ) as long
   dim pNode as wfxLListNode ptr = _Collection.get_index(nIndex)
   if pNode then
      ' Delete ListViewItem fires destructor that deletes any subitems
      Delete cast(wfxListViewItem ptr, pNode->pData)
      _Collection.Remove(pNode)

      ' Renumber the Index property for each item in the collection.
      dim pNode as wfxLListNode ptr 
      dim pListViewItem as wfxListViewItem ptr
      for i as long = 0 to _Collection.Size - 1
         pNode = _Collection.get_index(i)
         pListViewItem = cast(wfxListViewItem ptr, pNode->pData)
         if pListViewItem then 
            pListViewItem->Index = i
            pListViewItem->SubItems.ItemIndex = i
            for ii as long = 0 to pListViewItem->SubItems.Count - 1
               pListViewItem->SubItem(ii).ItemIndex = i
            next   
         end if
      next
      
      If this.hWindow Then 
         if this.UpdateFlag = false then
            ListView_SetItemCountEx( this.hWindow, this.Count, 0 )
            if ListView_IsItemVisible(this.hWindow, nIndex) then
               AfxRedrawWindow(this.hWindow)
            end if   
         end if   
      end if
   end if   
   function = _Collection.Size
end function

function wfxListViewItemsCollection.ByIndex( byval nIndex as long ) byref as wfxListViewItem 
   dim pItem as wfxListViewItem ptr
   dim pNode as wfxLListNode ptr
   if _Collection.Size then
      if (nIndex >= 0) and (nIndex <= _Collection.Size - 1) then
         pNode = _Collection.get_index(nIndex)
         if pNode then
            pItem = cast(wfxListViewItem ptr, pNode->pData)
            return *pItem
         end if   
      end if
   end if   
end function

function wfxListViewItemsCollection.Clear() as long
   ' Deallocate elements in the Items collection.
   ' In order to speed the deallocations, we first loop through
   ' the collection and deallocate the ListViewItems. We then call
   ' the LList's method Clear to quickly deallocate the list nodes
   ' and erase the list.
   ' Disabling drawing updates until all of the nodes are deleted, 
   ' otherwise we could get a GPF on a redraw while the node is being deleted.
   SendMessage( this.hWindow, WM_SETREDRAW, false, 0 )
   dim pNode as wfxLListNode ptr 
   for i as long = 0 to _Collection.Size - 1
      pNode = _Collection.get_index(i)
      ' Delete ListViewItem fires destructor that deletes any subitems
      Delete cast(wfxListViewItem ptr, pNode->pData)
   next
   _Collection.Clear

   If this.hWindow Then 
      ListView_SetItemCountEx( this.hWindow, this.Count, LVSICF_NOINVALIDATEALL or LVSICF_NOSCROLL)
      if this.UpdateFlag = false then AfxRedrawWindow(this.hWindow)
   end if
   SendMessage( this.hWindow, WM_SETREDRAW, true, 0 )
   function = 0
END FUNCTION


function wfxListViewItemsCollection.SortByColumn( ByVal nColNum As Long, byval nSortAscend as Boolean = true ) as long 
   ' Simple Bubblesort to sort the Items based on the specified column data
   dim as long numItems = _Collection.Size
   if numItems = 0 then exit function
   
   dim pNode1 as wfxLListNode ptr 
   dim pItem1 as wfxListViewItem ptr
   dim pNode2 as wfxLListNode ptr 
   dim pItem2 as wfxListViewItem ptr

   ' SHELL SORT 
   Dim As Long lb = 0
   Dim As Long ub = numItems - 1
   Dim As Long done, i, inc = ub - lb
 
    Do
        inc = Int(inc / 2.2)
        If inc < 1 Then inc = 1
 
        Do
            done = 0
            For i = lb To ub - inc
               pNode1 = _Collection.get_index(i)
               pItem1 = cast(wfxListViewItem ptr, pNode1->pData)
                  
               pNode2 = _Collection.get_index(i+inc)
               pItem2 = cast(wfxListViewItem ptr, pNode2->pData)

               if nSortAscend then
                  If ucase(pItem1->SubItem(nColNum).Text) > _
                     ucase(pItem2->SubItem(nColNum).Text) then
                     Swap pNode1->pData, pNode2->pData
                     done = 1
                  end if   
               else
                  If ucase(pItem1->SubItem(nColNum).Text) < _
                     ucase(pItem2->SubItem(nColNum).Text) then
                     Swap pNode1->pData, pNode2->pData
                     done = 1
                  end if   
               end if
            Next
        Loop Until done = 0
 
    Loop Until inc = 1
 

   If this.hWindow Then 
      if this.UpdateFlag = false then
         AfxRedrawWindow( this.hWindow )
      end if   
   end if
   
   function = 0
end function

