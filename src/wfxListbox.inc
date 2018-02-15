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

property wfxListBox.SelectedItem() as long
   if this.hWindow then 
      _SelectedItem = SendMessage( this.hWindow, LB_GETCURSEL, 0, 0)
   end if
   property = _SelectedItem
end property

property wfxListBox.SelectedItem( byval nValue as long )
   if this.hWindow then 
      SendMessage( this.hWindow, LB_SETCURSEL, nValue, 0)
   end if
   _SelectedItem = nValue
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

   function = 0
END FUNCTION


'' LISTBOX ITEM
property wfxListBoxItem.Text() as CWSTR
   if this.hWindow then 
      DIM cbLen AS LONG = SendMessage(this.hWindow, LB_GETTEXTLEN, nIndex, 0)
      IF cbLen THEN 
         _Text = space(cbLen * 2)
         SendMessage( this.hWindow, LB_GETTEXT, nIndex, CAST(LPARAM, wszText.vptr))
      end if   
   end if   
   property = _Text
end property

property wfxListBoxItem.Text( byref wszValue as wstring )
   if this.hWindow then 
      _Index = SendMessage( this.hWindow, LB_ADDSTRING, 0, CAST(LPARAM, @wszValue))   
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
   ' Deallocate elements in the Panels collection.
   dim pNode as wfxLListNode ptr = _Collection.get_first
   do until pNode = 0
'TODO: Delete wfxStatusBarPanelsCollection in destructor causes "destructor has no public access"
      'Delete cast(wfxControl ptr, pNode->pData)
      pNode = _Collection.remove(pNode)
   LOOP
end destructor

property wfxListBoxItemsCollection.hWindow() as hwnd
   property = _hWindow
end property

property wfxListBoxItemsCollection.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

function wfxListBoxItemsCollection.Count() as Long
   function = _Collection.Size
end function

function wfxListBoxItemsCollection.Add() byref as wfxListBoxItem
   dim pData as wfxListBoxItem ptr = new wfxListBoxItem
   pData->hWindow = this.hWindow
   pData->Index = (this.Count - 1) + 1
   _Collection.Add( ControlType.ListBox, pData ) 
   return *pData
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







