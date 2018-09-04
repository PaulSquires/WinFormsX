'    WinFormsX - Windows GUI Framework for the FreeBASIC Compiler
'    Copyright (C) 2018 Paul Squires, PlanetSquires Software
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

' ListBox Class
' https://msdn.microsoft.com/en-us/library/system.windows.forms.listbox(v=vs.110).aspx

#include once "wfxListBox.bi"

constructor wfxListBox( byref wszName as wstring = "" )
   this.CtrlType = ControlType.ListBox
   this.Name = wszName
   this.BackColor = Colors.SystemWindow
   this.ForeColor = Colors.SystemWindowText
end constructor


Function wfxListBox.Item( ByVal nIndex As Long ) ByRef As wfxListBoxItem
   if _IsLoading then
      return this.Items.ByIndex(nIndex)
   else
      this._TempItem.hWindow = this.hWindow
      this._TempItem.Index = nIndex
      return this._TempItem
   end if
   return this.Items.ByIndex(nIndex)
END function

function wfxListBox.Items byref As wfxListBoxItemsCollection
   return this._ItemsCollection
END function

Property wfxListBox.BorderStyle() As ControlBorderStyle
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

Property wfxListBox.BorderStyle( ByVal nValue As ControlBorderStyle )
   If this.hWindow Then 
      AfxRemoveWindowExStyle(this.hWindow, WS_EX_CLIENTEDGE)
      AfxRemoveWindowStyle(this.hWindow, WS_BORDER)
      Dim As Long wsStyle
      Select Case nValue
         Case ControlBorderStyle.None
         Case ControlBorderStyle.Fixed3D
            AfxAddWindowExStyle(this.hWindow, WS_EX_CLIENTEDGE)
         Case ControlBorderStyle.FixedSingle
            AfxAddWindowStyle(this.hWindow, WS_BORDER)
      End Select
      SetWindowPos( this.hWindow, 0, 0, 0, 0, 0, SWP_NOZORDER Or SWP_NOMOVE Or SWP_NOSIZE Or SWP_DRAWFRAME)
   End If
   _BorderStyle = nValue
End Property

property wfxListBox.ColumnWidth() as long
   ' There is no such existing message as LB_GETCOLUMNWIDTH unfortunately.
   Property = _ColumnWidth
end property

property wfxListBox.ColumnWidth( byval nValue as long )
   if this.hWindow then 
      ' if column width is zero it will cause a gpf
      If nValue > 0 Then SendMessage( this.hWindow, LB_SETCOLUMNWIDTH, nValue, 0)
      this.Refresh
   end if
   _ColumnWidth = nValue
end property

property wfxListBox.IntegralHeight() as boolean
   If this.hWindow Then 
      _IntegralHeight = Iif( (AfxGetWindowStyle(this.hWindow) And LBS_NOINTEGRALHEIGHT), False, True)
   End If
   Property = _IntegralHeight
end property

property wfxListBox.IntegralHeight( byval nValue as boolean )
   If this.hWindow Then 
      AfxRemoveWindowStyle(this.hWindow, LBS_NOINTEGRALHEIGHT)
      If nValue = False Then AfxAddWindowStyle(this.hWindow, LBS_NOINTEGRALHEIGHT)
      this.Refresh
   End If   
   _IntegralHeight = nValue
end property

property wfxListBox.MultiColumn() as boolean
   If this.hWindow Then 
      _MultiColumn = Iif( (AfxGetWindowStyle(this.hWindow)And LBS_MULTICOLUMN), True, False)
   End If
   Property = _MultiColumn
end property

property wfxListBox.MultiColumn( byval nValue as boolean )
   If this.hWindow Then 
      AfxRemoveWindowStyle(this.hWindow, LBS_MULTICOLUMN)
      If nValue Then AfxAddWindowStyle(this.hWindow, LBS_MULTICOLUMN)
      this.Refresh
   End If   
   _MultiColumn = nValue
end property

Property wfxListBox.AllowSelection() As boolean
   ' This is a Get only property. Set via SelectionMode.
   If this.hWindow Then 
      _AllowSelection = True
      If (AfxGetWindowStyle(this.hWindow)And LBS_NOSEL) Then _AllowSelection = False
   End If
   Property = _AllowSelection
End Property

Property wfxListBox.SelectionMode() As ListSelectionMode
   If this.hWindow Then 
      Dim As Long dwStyle = AfxGetWindowStyle(this.hWindow)
      If (dwStyle And LBS_NOSEL) Then 
         _SelectionMode = ListSelectionMode.None
      ElseIf (dwStyle And LBS_MULTIPLESEL) Then 
         _SelectionMode = ListSelectionMode.MultiSimple
      ElseIf (dwStyle And LBS_EXTENDEDSEL) Then 
         _SelectionMode = ListSelectionMode.MultiExtended
      Else
         _SelectionMode = ListSelectionMode.One   ' default
      End If
   End If
   Property = _SelectionMode
End Property

Property wfxListBox.SelectionMode( ByVal nValue As ListSelectionMode )
   if this.hWindow then 
      AfxRemoveWindowStyle(this.hWindow, LBS_NOSEL)
      AfxRemoveWindowStyle(this.hWindow, LBS_MULTIPLESEL)
      AfxRemoveWindowStyle(this.hWindow, LBS_EXTENDEDSEL)
      Dim As Long dwStyle
      Select Case nValue
         Case ListSelectionMode.None
            dwStyle = LBS_NOSEL
            _AllowSelection = False
         Case ListSelectionMode.One
            ' This is the default for a listbox
         Case ListSelectionMode.MultiSimple
            dwStyle = LBS_MULTIPLESEL
         Case ListSelectionMode.MultiExtended
            dwStyle = LBS_EXTENDEDSEL
      End Select
      AfxAddWindowStyle(this.hWindow, dwStyle)
   End If
   _SelectionMode = nValue
end property

property wfxListBox.ScrollAlwaysVisible() as boolean
   If this.hWindow Then 
      _ScrollAlwaysVisible = Iif( (AfxGetWindowStyle(this.hWindow) And LBS_DISABLENOSCROLL), True, False)
   End If   
   Property = _ScrollAlwaysVisible
end property

property wfxListBox.ScrollAlwaysVisible( byval nValue as boolean )
   if this.hWindow then 
      AfxRemoveWindowStyle(this.hWindow, LBS_DISABLENOSCROLL)
      If nValue Then AfxAddWindowStyle(this.hWindow, LBS_DISABLENOSCROLL)
      this.Refresh
   End If   
   _ScrollAlwaysVisible = nValue
End Property

property wfxListBox.SelectedItem() byref as wfxListBoxItem
   if this.hWindow then 
      _SelectedItem = this.Item(this.SelectedIndex)
   end if
   property = _SelectedItem
end property

property wfxListBox.SelectedItem( byref lbItem as wfxListBoxItem )
   if this.hWindow then 
      SendMessage( this.hWindow, LB_SETCURSEL, lbItem.Index, 0)
   end if
   _SelectedItem = lbItem
end property

property wfxListBox.SelectedIndex() as long
   if this.hWindow then 
      _SelectedIndex = SendMessage( this.hWindow, LB_GETCURSEL, 0, 0)
   end if
   property = _SelectedIndex
end property

property wfxListBox.SelectedIndex( byval nValue as long )
   if this.hWindow then 
      SendMessage( this.hWindow, LB_SETCURSEL, nValue, 0)
   end if
   _SelectedIndex = nValue
end property

property wfxListBox.Sorted() as boolean
   if this.hWindow then 
      _Sorted = Iif( (AfxGetWindowStyle(this.hWindow) And LBS_SORT), True, False)
   End If   
   Property = _Sorted
end property

property wfxListBox.Sorted( byval nValue as boolean )
   if this.hWindow then 
      AfxRemoveWindowStyle(this.hWindow, LBS_SORT)
      If nValue Then AfxAddWindowStyle(this.hWindow, LBS_SORT)
      this.Refresh
   End If   
   _Sorted = nValue
end property

Property wfxListBox.UseTabStops() As boolean
   If this.hWindow Then 
      _UseTabStops = Iif( (AfxGetWindowStyle(this.hWindow) And LBS_USETABSTOPS), True, False)
   End If   
   Property = _UseTabStops
End Property

Property wfxListBox.UseTabStops( ByVal nValue As boolean )
   If this.hWindow Then 
      AfxRemoveWindowStyle(this.hWindow, LBS_USETABSTOPS)
      If nValue Then AfxAddWindowStyle(this.hWindow, LBS_USETABSTOPS)
      this.Refresh
   End If   
   _Sorted = nValue
End Property

Property wfxListBox.TopIndex() As Long
   if this.hWindow then 
      _TopIndex = SendMessage( this.hWindow, LB_GETTOPINDEX, 0, 0)
   end if
   property = _TopIndex
end property

property wfxListBox.TopIndex( byval nValue as long )
   if this.hWindow then 
      SendMessage( this.hWindow, LB_SETTOPINDEX, nValue, 0)
   end if
   _TopIndex = nValue
end property



function wfxListBox.Show(byval hWndParent as hwnd = 0) as long

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
   dim as long dwStyle = WS_HSCROLL OR WS_VSCROLL or LBS_HASSTRINGS OR LBS_NOTIFY
  
   if _ScrollAlwaysVisible then dwStyle = dwStyle or LBS_DISABLENOSCROLL
   if _IntegralHeight = false then dwStyle = dwStyle or LBS_NOINTEGRALHEIGHT
   if _Sorted then dwStyle = dwStyle or LBS_SORT
   if _MultiColumn then dwStyle = dwStyle or LBS_MULTICOLUMN
   if _TabStop then dwStyle = dwStyle OR WS_TABSTOP 
   if _Visible THEN dwStyle = dwStyle OR WS_VISIBLE
   
   Select Case _SelectionMode
      Case ListSelectionMode.None:          dwStyle = dwStyle Or LBS_NOSEL
      Case ListSelectionMode.One            ' This is the default for a listbox
      Case ListSelectionMode.MultiSimple:   dwStyle = dwStyle Or LBS_MULTIPLESEL
      Case ListSelectionMode.MultiExtended: dwStyle = dwStyle Or LBS_EXTENDEDSEL
   End Select
   
   _CtrlID = this.Parent->GetNextCtrlID()

   this.hWindow = this.Parent->pWindow->AddControl ( _
         "LISTBOX", _                      ' // Class name
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

   If _MultiColumn Then this.ColumnWidth = _ColumnWidth 
   

   ' Do not set the focus/selected here because doing so will also Activate the form and
   ' cause an Activated message to be fired. We want the Form's Load event to
   ' complete before any Activate message.
   ' Refer to wfxForm.CreateFormInternal for the setting of the focus/selected
   ' control once events have fired correctly.
      
   ' Store the hWindow in the linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   dim pNode as wfxLListNode ptr = this.Parent->Controls.search_data(@this)
   if pNode then pNode->hWindow = this.hWindow
      
   ' Set the text for the Items.
   For i As Long = 0 To this.Items.Count - 1
      ' Get the Item text prior to assigning the ListBox handle otherwise the
      ' library will try to retrieve the text from the actual window control and
      ' that text hasn't even been assigned yet.
      Dim As CWSTR wszItemText = this.Item(i).Text
      Dim As Long nData32 = this.Item(i).data32
      this.Item(i).hWindow = this.hWindow
      Dim As Long idx = SendMessage( this.hWindow, LB_ADDSTRING, 0, Cast(LPARAM, wszItemText.vptr) )
      SendMessage( this.hWindow, LB_SETITEMDATA, idx, Cast(LPARAM, nData32) )
   Next
   SendMessage( this.hWindow, LB_SETCURSEL, _SelectedIndex, 0 )

   ' Set the hWindow for the collection
   this.Items.hWindow = this.hWindow
   _IsLoading = false

   function = 0
END FUNCTION


'' LISTBOX ITEM
property wfxListBoxItem.hWindow() as hwnd
   property = _hWindow
END PROPERTY

property wfxListBoxItem.hWindow( ByVal nValue As hwnd) 
   _hWindow = nValue
END PROPERTY

property wfxListBoxItem.Index() as long
   property = _Index
End Property

property wfxListBoxItem.Index( ByVal nValue As long) 
   _Index = nValue
END PROPERTY

Property wfxListBoxItem.Selected() As boolean
   if this.hWindow then 
      _Selected = false
      DIM nSelCount AS LONG = SendMessage(this.hWindow, LB_GETSELCOUNT, 0, 0)
      if nSelCount = 0 then return false
      dim iSel(nSelCount) as Long
      SendMessage(this.hWindow, LB_GETSELITEMS, nSelCount, cast(LPARAM, @iSel(0)) )
      for i as long = 0 to nSelCount - 1
         if iSel(i) = _Index then 
            _Selected = true: exit for
         end if   
      NEXT
   end if
   property = _Selected
END PROPERTY

property wfxListBoxItem.Selected( ByVal nValue As boolean) 
   if this.hWindow then 
      SendMessage(this.hWindow, LB_SETSEL, nValue, cast(LPARAM, _Index) )
   end if
   _Selected = nValue
END PROPERTY

property wfxListBoxItem.Text() as CWSTR
   if this.hWindow then 
      DIM cbLen AS LONG = SendMessage(this.hWindow, LB_GETTEXTLEN, _Index, 0)
      IF cbLen THEN 
         _Text = space(cbLen * 2)
         SendMessage( this.hWindow, LB_GETTEXT, _Index, CAST(LPARAM, _Text.vptr))
      end if   
   end if   
   property = _Text
end property

property wfxListBoxItem.Text( byref wszValue as wstring )
   if this.hWindow then 
      dim as long nCurSel = SendMessage( this.hWindow, LB_GETCURSEL, 0, 0)
      SendMessage( this.hWindow, LB_DELETESTRING, _Index, 0)
      dim as long nCount = SendMessage( this.hWindow, LB_GETCOUNT, 0, 0)
      _Index = SendMessage( this.hWindow, LB_INSERTSTRING, iif(_Index > nCount - 1, -1, _Index), CAST(LPARAM, @wszValue))
      SendMessage( this.hWindow, LB_SETCURSEL, nCurSel, 0)
   end if   
   _Text = wszValue
end property

property wfxListBoxItem.Data32() as long
   if this.hWindow then 
      _Data32 = SendMessage( this.hWindow, LB_GETITEMDATA, _Index, 0)
   end if
   property = _Data32
end property

property wfxListBoxItem.Data32( byVal nValue as long)
   if this.hWindow then 
      SendMessage( this.hWindow, LB_SETITEMDATA, _Index, CAST(LPARAM, nValue))
   end if
   _Data32 = nValue
end property


'' ITEMSCOLLECTION
constructor wfxListBoxItemsCollection
   '
END CONSTRUCTOR

destructor wfxListBoxItemsCollection
   this.Clear
end destructor

property wfxListBoxItemsCollection.hWindow() as hwnd
   property = _hWindow
end property

property wfxListBoxItemsCollection.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

function wfxListBoxItemsCollection.Count() as Long
   if this.hWindow then
      function = SendMessage( this.hWindow, LB_GETCOUNT, 0, 0 )
   else
      function = _Collection.Size
   end if
end function

Function wfxListBoxItemsCollection.SelectedCount() As Long
   If this.hWindow Then
      Function = SendMessage( this.hWindow, LB_GETSELCOUNT, 0, 0 )
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

Function wfxListBoxItemsCollection.Add( ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
   If this.hWindow Then
      Dim As Long idx = SendMessage( this.hWindow, LB_ADDSTRING, 0, Cast(LPARAM, @wszValue) )
      SendMessage( this.hWindow, LB_SETITEMDATA, idx, CAST(LPARAM, nValue))
      Function = idx
   Else
      Dim pData As wfxListBoxItem Ptr = New wfxListBoxItem
      pData->hWindow = this.hWindow
      pData->Index = (this.Count - 1) + 1
      pData->Text = wszValue
      pData->Data32 = nValue
      _Collection.Add( ControlType.ListBox, pData ) 
      function = pData->Index
   END IF
end function

function wfxListBoxItemsCollection.Remove( byval nIndex as long ) as long
   if this.hWindow then
      function = SendMessage( this.hWindow, LB_DELETESTRING, nIndex, 0)
   else
      dim pItem as wfxListBoxItem ptr
      dim pNode as wfxLListNode ptr
      pNode = _Collection.get_first
      do until pNode = 0
         pItem = cast(wfxListBoxItem ptr, pNode->pData)
         if pItem->Index = nIndex then
            _Collection.Remove(pNode)
            exit do
         END IF
         pNode = _Collection.get_next(pNode)
      LOOP
      function = 0
   END IF
   function = _Collection.Size
end function

function wfxListBoxItemsCollection.ByIndex( byval nIndex as long ) byref as wfxListBoxItem 
   dim pItem as wfxListBoxItem ptr
   dim pNode as wfxLListNode ptr
   pNode = _Collection.get_first
   do until pNode = 0
      pItem = cast(wfxListBoxItem ptr, pNode->pData)
      if pItem->Index = nIndex then
         exit do
      END IF
      pNode = _Collection.get_next(pNode)
   LOOP
   return *pItem
end function

function wfxListBoxItemsCollection.Clear() as long
   if this.hWindow then
      SendMessage( this.hWindow, LB_RESETCONTENT, 0, 0)
   else
      ' Deallocate elements in the Items collection.
      dim pNode as wfxLListNode ptr = _Collection.get_first
      do until pNode = 0
         Delete cast(wfxListBoxItem ptr, pNode->pData)
         pNode = _Collection.remove(pNode)
      LOOP
   end if
   function = 0
END FUNCTION



