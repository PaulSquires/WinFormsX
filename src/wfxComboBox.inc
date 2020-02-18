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

' ComboBox Class
' https://docs.microsoft.com/en-ca/dotnet/api/system.windows.forms.combobox

#Include Once "wfxComboBox.bi"

constructor wfxComboBox( byref wszName as wstring = "" )
   this.CtrlType = ControlType.ComboBox
   this.Name = wszName
   this.BackColor = Colors.SystemWindow
   this.ForeColor = Colors.SystemWindowText
end constructor


Function wfxComboBox.Item( ByVal nIndex As Long ) ByRef As wfxComboBoxItem
   if _IsLoading then
      return this.Items.ByIndex(nIndex)
   else
      this._TempItem.hWindow = this.hWindow
      this._TempItem.Index = nIndex
      return this._TempItem
   end if
   return this.Items.ByIndex(nIndex)
END function

function wfxComboBox.Items byref As wfxComboBoxItemsCollection
   return this._ItemsCollection
END function

property wfxComboBox.IntegralHeight() as boolean
   If this.hWindow Then 
      _IntegralHeight = Iif( (AfxGetWindowStyle(this.hWindow) And CBS_NOINTEGRALHEIGHT), False, True)
   End If
   Property = _IntegralHeight
end property

property wfxComboBox.IntegralHeight( byval nValue as boolean )
   If this.hWindow Then 
      AfxRemoveWindowStyle(this.hWindow, CBS_NOINTEGRALHEIGHT)
      If nValue = False Then AfxAddWindowStyle(this.hWindow, CBS_NOINTEGRALHEIGHT)
      this.Refresh
   End If   
   _IntegralHeight = nValue
end property

property wfxComboBox.SelectedItem() byref as wfxComboBoxItem
   if this.hWindow then 
      _SelectedItem = this.Item(this.SelectedIndex)
   end if
   property = _SelectedItem
end property

property wfxComboBox.SelectedItem( byref lbItem as wfxComboBoxItem )
   if this.hWindow then 
      SendMessage( this.hWindow, CB_SETCURSEL, lbItem.Index, 0)
   end if
   _SelectedItem = lbItem
end property

property wfxComboBox.SelectedIndex() as long
   if this.hWindow then 
      _SelectedIndex = SendMessage( this.hWindow, CB_GETCURSEL, 0, 0)
   end if
   property = _SelectedIndex
end property

property wfxComboBox.SelectedIndex( byval nValue as long )
   if this.hWindow then 
      SendMessage( this.hWindow, CB_SETCURSEL, nValue, 0)
   end if
   _SelectedIndex = nValue
end property

property wfxComboBox.Sorted() as boolean
   if this.hWindow then 
      _Sorted = Iif( (AfxGetWindowStyle(this.hWindow) And CBS_SORT), True, False)
   End If   
   Property = _Sorted
end property

property wfxComboBox.Sorted( byval nValue as boolean )
   if this.hWindow then 
      AfxRemoveWindowStyle(this.hWindow, CBS_SORT)
      If nValue Then AfxAddWindowStyle(this.hWindow, CBS_SORT)
      this.Refresh
   End If   
   _Sorted = nValue
end property

Property wfxComboBox.BorderStyle() As ControlBorderStyle
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

Property wfxComboBox.BorderStyle( ByVal nValue As ControlBorderStyle )
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

Property wfxComboBox.DropDownStyle() As ComboBoxStyle
   If this.hWindow Then 
      If (AfxGetWindowStyle(this.hWindow) And CBS_DROPDOWN ) Then
         _DropDownStyle = ComboBoxStyle.DropDown
      ElseIf (AfxGetWindowStyle(this.hWindow) And CBS_DROPDOWNLIST ) Then
         _DropDownStyle = ComboBoxStyle.DropDownList
      ElseIf (AfxGetWindowStyle(this.hWindow) And CBS_SIMPLE ) Then
         _DropDownStyle = ComboBoxStyle.Simple
      End If   
   End If
   Property = _DropDownStyle
End Property

Property wfxComboBox.DropDownStyle( ByVal nValue As ComboBoxStyle )
   If this.hWindow Then 
      AfxRemoveWindowStyle(this.hWindow, CBS_DROPDOWN)
      AfxRemoveWindowStyle(this.hWindow, CBS_DROPDOWNLIST)
      AfxRemoveWindowStyle(this.hWindow, CBS_SIMPLE)
      Dim As Long wsStyle
      Select Case nValue
         Case ComboBoxStyle.Simple
            AfxAddWindowStyle(this.hWindow, CBS_SIMPLE)
         Case ComboBoxStyle.DropDown
            AfxAddWindowStyle(this.hWindow, CBS_DROPDOWN)
         Case ComboBoxStyle.DropDownList
            AfxAddWindowStyle(this.hWindow, CBS_DROPDOWNLIST)
      End Select
      SetWindowPos( this.hWindow, 0, 0, 0, 0, 0, SWP_NOZORDER Or SWP_NOMOVE Or SWP_NOSIZE Or SWP_DRAWFRAME)
   End If
   _DropDownStyle = nValue
End Property


function wfxComboBox.Show(byval hWndParent as hwnd = 0) as long

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
   Dim As Long dwStyle = WS_HSCROLL Or WS_VSCROLL
  
   If _IntegralHeight = False Then dwStyle = dwStyle Or CBS_NOINTEGRALHEIGHT
   If _Sorted Then dwStyle = dwStyle Or CBS_SORT
   if _TabStop then dwStyle = dwStyle OR WS_TABSTOP 
   if _Visible THEN dwStyle = dwStyle OR WS_VISIBLE
   
   Select Case _DropDownStyle
      Case ComboBoxStyle.Simple:       dwStyle = dwStyle OR CBS_SIMPLE 
      Case ComboBoxStyle.DropDown:     dwStyle = dwStyle OR CBS_DROPDOWN 
      Case ComboBoxStyle.DropDownList: dwStyle = dwStyle OR CBS_DROPDOWNLIST 
   End Select
   ' Need to give the combobox a height in order for dropdown lists to show.
   if _DropDownStyle <> ComboBoxStyle.Simple then
      this.Height = 200
   end if

   _CtrlID = this.Parent->GetNextCtrlID()

   this.hWindow = this.Parent->pWindow->AddControl ( _
         "COMBOBOX", _                     ' // Class name
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
   'this.BorderStyle = _BorderStyle
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
      
   ' Set the text for the Items.
   For i As Long = 0 To this.Items.Count - 1
      ' Get the Item text prior to assigning the ListBox handle otherwise the
      ' library will try to retrieve the text from the actual window control and
      ' that text hasn't even been assigned yet.
      Dim As CWSTR wszItemText = this.Item(i).Text
      Dim As Long nData32 = this.Item(i).data32
      this.Item(i).hWindow = this.hWindow
      Dim As Long idx = SendMessage( this.hWindow, CB_ADDSTRING, 0, Cast(LPARAM, wszItemText.vptr) )
      SendMessage( this.hWindow, CB_SETITEMDATA, idx, Cast(LPARAM, nData32) )
   Next
   SendMessage( this.hWindow, CB_SETCURSEL, _SelectedIndex, 0 )

   if this.SelectedIndex = -1 then this.Text = _Text

   ' Set the hWindow for the collection
   this.Items.hWindow = this.hWindow
   _IsLoading = false

   function = 0
END FUNCTION


'' COMBOBOX ITEM
property wfxComboBoxItem.hWindow() as hwnd
   property = _hWindow
END PROPERTY

property wfxComboBoxItem.hWindow( ByVal nValue As hwnd) 
   _hWindow = nValue
END PROPERTY

property wfxComboBoxItem.Index() as long
   property = _Index
End Property

property wfxComboBoxItem.Index( ByVal nValue As long) 
   _Index = nValue
END PROPERTY

Property wfxComboBoxItem.Selected() As boolean
   if this.hWindow then 
      _Selected = iif(_Index = SendMessage(this.hWindow, CB_GETCURSEL, 0, 0), true, false)
   end if
   property = _Selected
END PROPERTY

property wfxComboBoxItem.Selected( ByVal nValue As boolean) 
   if this.hWindow then 
      ' If False and already selected then unselected it
      if (nValue = false) andalso (this.Selected = true) then
         SendMessage(this.hWindow, CB_SETCURSEL, -1, 0)
      else
         SendMessage(this.hWindow, CB_SETCURSEL, _Index, 0)
      end if   
   end if
   _Selected = nValue
END PROPERTY

property wfxComboBoxItem.Text() as CWSTR
   if this.hWindow then 
      DIM cbLen AS LONG = SendMessage(this.hWindow, CB_GETLBTEXTLEN, _Index, 0)
      IF cbLen THEN 
         _Text = space(cbLen * 2)
         SendMessage( this.hWindow, CB_GETLBTEXT, _Index, CAST(LPARAM, _Text.vptr))
      end if   
   end if   
   property = _Text
end property

property wfxComboBoxItem.Text( byref wszValue as wstring )
   if this.hWindow then 
      dim as long nCurSel = SendMessage( this.hWindow, CB_GETCURSEL, 0, 0)
      SendMessage( this.hWindow, CB_DELETESTRING, _Index, 0)
      dim as long nCount = SendMessage( this.hWindow, CB_GETCOUNT, 0, 0)
      _Index = SendMessage( this.hWindow, CB_INSERTSTRING, iif(_Index > nCount - 1, -1, _Index), CAST(LPARAM, @wszValue))
      SendMessage( this.hWindow, CB_SETCURSEL, nCurSel, 0)
   end if   
   _Text = wszValue
end property

property wfxComboBoxItem.Data32() as long
   if this.hWindow then 
      _Data32 = SendMessage( this.hWindow, CB_GETITEMDATA, _Index, 0)
   end if
   property = _Data32
end property

property wfxComboBoxItem.Data32( byVal nValue as long)
   if this.hWindow then 
      SendMessage( this.hWindow, CB_SETITEMDATA, _Index, CAST(LPARAM, nValue))
   end if
   _Data32 = nValue
end property


'' ITEMSCOLLECTION
constructor wfxComboBoxItemsCollection
   '
END CONSTRUCTOR

destructor wfxComboBoxItemsCollection
   this.Clear
end destructor

property wfxComboBoxItemsCollection.hWindow() as hwnd
   property = _hWindow
end property

property wfxComboBoxItemsCollection.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

function wfxComboBoxItemsCollection.Count() as Long
   if this.hWindow then
      function = SendMessage( this.hWindow, CB_GETCOUNT, 0, 0 )
   else
      function = _Collection.Size
   end if
end function

Function wfxComboBoxItemsCollection.Add( ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
   If this.hWindow Then
      Dim As Long idx = SendMessage( this.hWindow, CB_ADDSTRING, 0, Cast(LPARAM, @wszValue) )
      SendMessage( this.hWindow, CB_SETITEMDATA, idx, CAST(LPARAM, nValue))
      Function = idx
   Else
      Dim pData As wfxComboBoxItem Ptr = New wfxComboBoxItem
      pData->hWindow = this.hWindow
      pData->Index = (this.Count - 1) + 1
      pData->Text = wszValue
      pData->Data32 = nValue
      _Collection.Add( ControlType.ListBox, pData ) 
      function = pData->Index
   END IF
end function

function wfxComboBoxItemsCollection.Remove( byval nIndex as long ) as long
   if this.hWindow then
      function = SendMessage( this.hWindow, CB_DELETESTRING, nIndex, 0)
   else
      dim pNode as wfxLListNode ptr = _Collection.get_index(nIndex)
      if pNode then
         Delete cast(wfxComboBoxItem ptr, pNode->pData)
         _Collection.Remove(pNode)
      end if   
   END IF
   ' Renumber the Index property for each item in the collection.
   dim pNode as wfxLListNode ptr 
   dim pComboBoxItem as wfxComboBoxItem ptr
   for i as long = 0 to _Collection.Size - 1
      pNode = _Collection.get_index(i)
      pComboBoxItem = cast(wfxComboBoxItem ptr, pNode->pData)
      if pComboBoxItem then pComboBoxItem->Index = i
   next
   function = _Collection.Size
end function

function wfxComboBoxItemsCollection.ByIndex( byval nIndex as long ) byref as wfxComboBoxItem 
   dim pItem as wfxComboBoxItem ptr
   dim pNode as wfxLListNode ptr
   pNode = _Collection.get_index(nIndex)
   if pNode then
      pItem = cast(wfxComboBoxItem ptr, pNode->pData)
      return *pItem
   end if   
end function

function wfxComboBoxItemsCollection.Clear() as long
   if this.hWindow then
      SendMessage( this.hWindow, CB_RESETCONTENT, 0, 0)
   else
      ' Deallocate elements in the Items collection.
      dim pNode as wfxLListNode ptr = _Collection.get_first
      do until pNode = 0
         Delete Cast(wfxComboBoxItem Ptr, pNode->pData)
         pNode = _Collection.remove(pNode)
      LOOP
   end if
   function = 0
END FUNCTION



