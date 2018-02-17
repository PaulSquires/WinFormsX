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
   this.BackColor = Colors.SystemWindowFace
   this.ForeColor = Colors.SystemWindowText
end constructor

function wfxListBox.Item( ByVal nIndex As long ) byref As wfxListBoxItem
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

property wfxListBox.AllowSelection() as boolean
   property = _AllowSelection
end property

property wfxListBox.BorderStyle() as FormBorderStyle
   property = _BorderStyle
end property

property wfxListBox.BorderStyle( byval nValue as FormBorderStyle )
   if this.hWindow then 
      ' Remove the current alignment and set the new style
      AfxRemoveWindowStyle(this.hWindow, _BorderStyle)
      if nValue = false then AfxAddWindowStyle(this.hWindow, nValue)
      this.Refresh
   end if
   _BorderStyle = nValue
end property

property wfxListBox.ColumnWidth() as long
   property = _ColumnWidth
end property

property wfxListBox.ColumnWidth( byval nValue as long )
   if this.hWindow then 
      SendMessage( this.hWindow, LB_SETCOLUMNWIDTH, nValue, 0)
      this.Refresh
   end if
   _ColumnWidth = nValue
end property

property wfxListBox.IntegralHeight() as boolean
   property = _IntegralHeight
end property

property wfxListBox.IntegralHeight( byval nValue as boolean )
   _IntegralHeight = nValue
end property

property wfxListBox.MultiColumn() as boolean
   property = _MultiColumn
end property

property wfxListBox.MultiColumn( byval nValue as boolean )
   _MultiColumn = nValue
end property

property wfxListBox.SelectionMode() as ListBoxSelectionMode
   property = _SelectionMode
end property

property wfxListBox.SelectionMode( byval nValue as ListBoxSelectionMode )
   _SelectionMode = nValue
end property

property wfxListBox.ScrollAlwaysVisible() as boolean
   property = _ScrollAlwaysVisible
end property

property wfxListBox.ScrollAlwaysVisible( byval nValue as boolean )
   _ScrollAlwaysVisible = nValue
end property

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
   property = _Sorted
end property

property wfxListBox.Sorted( byval nValue as boolean )
   _Sorted = nValue
end property

property wfxListBox.TopIndex() as long
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
      
   dim as long dwExStyle = _BorderStyle
   dim as long dwStyle = WS_HSCROLL OR WS_VSCROLL or LBS_HASSTRINGS OR LBS_NOTIFY
  
   if _ScrollAlwaysVisible then dwStyle = dwStyle or LBS_DISABLENOSCROLL
   if _AllowSelection = false then dwStyle = dwStyle or LBS_NOSEL
   if _IntegralHeight = false then dwStyle = dwStyle or LBS_NOINTEGRALHEIGHT
   if _Sorted then dwStyle = dwStyle or LBS_SORT
   if _MultiColumn then dwStyle = dwStyle or LBS_MULTICOLUMN
   if _TabStop then dwStyle = dwStyle OR WS_TABSTOP 
   if _Visible THEN dwStyle = dwStyle OR WS_VISIBLE
   
   _AllowSelection = true
   select case _SelectionMode 
      CASE ListBoxSelectionMode.None
         dwStyle = dwStyle or LBS_NOSEL
         _AllowSelection = false
      CASE ListBoxSelectionMode.One
         ' This is the default for a listbox
      CASE ListBoxSelectionMode.MultiSimple
         dwStyle = dwStyle or LBS_MULTIPLESEL
      CASE ListBoxSelectionMode.MultiExtended
         dwStyle = dwStyle or LBS_EXTENDEDSEL
   END SELECT

   this.hWindow = this.Parent->pWindow->AddControl ( _
         "LISTBOX", _                      ' // Class name
         hWndParent, _                     ' // Parent window handle
         100, _                            ' // Control identifier (this gets modified when added to controls collection)
         this.Text, _                      ' // Control caption
         this.Left, _                      ' // Horizontal position
         this.Top, _                       ' // Vertical position
         this.Width, _                     ' // Control width
         this.Height, _                    ' // Control height
         dwStyle, _                        ' // Control style
         dwExStyle, _                      ' // Extended style
         0, _                              ' // Pointer to custom data
         Cast(WNDPROC, @wfxApplication.SubclassProc), _   ' // Address of the window callback procedure
         100, _                            ' // The subclass ID
         Cast(DWORD_PTR, 0) _              ' // Pointer to reference data
         )


   ' Do not set the focus/selected here because doing so will also Activate the form and
   ' cause an Activated message to be fired. We want the Form's Load event to
   ' complete before any Activate message.
   ' Refer to wfxForm.CreateFormInternal for the setting of the focus/selected
   ' control once events have fired correctly.
      
   ' Store the hWindow in the linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   dim pNode as wfxLListNode ptr = this.Parent->Controls.search_data(@this)
   if pNode then pNode->hWindow = this.hWindow
      
   this.Enabled = _Enabled
   if _MultiColumn then this.ColumnWidth = _ColumnWidth 
   
   ' Set the text for the Items.
   for i as long = 0 to this.Items.Count - 1
      ' Get the Item text prior to assigning the ListBox handle otherwise the
      ' library will try to retrieve the text from the actual window control and
      ' that text hasn't even been assigned yet.
      dim as CWSTR wszItemText = this.Item(i).Text
      dim as long nData32 = this.Item(i).data32
      this.Item(i).hWindow = this.hWindow
      dim as long idx = SendMessage( this.hWindow, LB_ADDSTRING, 0, cast(LPARAM, wszItemText.vptr) )
      SendMessage( this.hWindow, LB_SETITEMDATA, idx, CAST(LPARAM, nData32) )
   next
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
END PROPERTY

property wfxListBoxItem.Index( ByVal nValue As long) 
   _Index = nValue
END PROPERTY

property wfxListBoxItem.Selected() as boolean
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

function wfxListBoxItemsCollection.Add() as long
   if this.hWindow then
      function = SendMessage( this.hWindow, LB_ADDSTRING, 0, cast(LPARAM, @"") )
   else
      dim pData as wfxListBoxItem ptr = new wfxListBoxItem
      pData->hWindow = this.hWindow
      pData->Index = (this.Count - 1) + 1
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

'function wfxListBox.ClearItems() as long
'   SendMessage( this.hWindow, LB_RESETCONTENT, 0, 0)
'   function = 0
'END FUNCTION

'function wfxListBox.Count() as Long
'   function = SendMessage( this.hWindow, LB_GETCOUNT, 0, 0)
'END FUNCTION

'function wfxListBox.SelectedCount() as Long
'   function = SendMessage( this.hWindow, LB_GETSELCOUNT, 0, 0)
'END FUNCTION

'function wfxListBox.AddItem( byref wszName as wstring, byval nValue32 as long = 0 ) as Long
'   dim as long nIndex
'   nIndex = SendMessage( this.hWindow, LB_ADDSTRING, 0, CAST(LPARAM, @wszName))   
'   SendMessage( this.hWindow, LB_SETITEMDATA, nIndex, CAST(LPARAM, nValue32))
'   function = nIndex
'END FUNCTION

'function wfxListBox.DeleteItem( byval nIndex as long ) as Long
'   function = SendMessage( this.hWindow, LB_DELETESTRING, nIndex, 0)
'END FUNCTION

'function wfxListBox.GetItemText( byval nIndex as long ) as CWSTR
'   DIM cbLen AS LONG = SendMessage(this.hWindow, LB_GETTEXTLEN, nIndex, 0)
'   IF cbLen THEN 
'      dim wszText as CWSTR = space(cbLen * 2)
'      SendMessage( this.hWindow, LB_GETTEXT, nIndex, CAST(LPARAM, wszText.vptr))
'      return wszText
'   end if   
'END FUNCTION

'function wfxListBox.GetItemData( byval nIndex as long ) as long
'   function = SendMessage( this.hWindow, LB_GETITEMDATA, nIndex, 0)
'end function


