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


#include once "wfxMainMenu.bi"

constructor wfxMainMenu()
   this.CtrlType = ControlType.MainMenu
end constructor


Function wfxMainMenu.Item( ByVal nIndex As Long ) ByRef As wfxMenuItem
   if _IsLoading then
      return this.Items.ByIndex(nIndex)
   else
      this._TempItem.hWindow = this.hWindow
      this._TempItem.Index = nIndex
      return this._TempItem
   end if
   return this.Items.ByIndex(nIndex)
END function

function wfxMainMenu.Items byref As wfxMenuItemsCollection
   return this._ItemsCollection
END function


function wfxMainMenu.Show(byval hWndParent as hwnd = 0) as long

   dim wszClassName as wstring * MAX_PATH
   
   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function

   dim as MENUITEMINFO itemInfo
   
   dim as HMENU hMenu = CreateMenu()
   
   with itemInfo
      .cbSize   = sizeof(MENUITEMINFO)
      .fMask    = MIIM_FTYPE or MIIM_STATE or MIIM_STRING
      .fType    = MFT_STRING
      .fState   = MFS_ENABLED
      .hSubMenu = null
   end with

   itemInfo.dwTypeData = @wstr("File")
   InsertMenuItem(hMenu, this.Parent->GetNextCtrlID, false, @itemInfo)
   
   itemInfo.dwTypeData = @wstr("Edit")
   InsertMenuItem(hMenu, this.Parent->GetNextCtrlID, false, @itemInfo)

   itemInfo.dwTypeData = @wstr("View")
   InsertMenuItem(hMenu, this.Parent->GetNextCtrlID, false, @itemInfo)

   itemInfo.dwTypeData = @wstr("Help")
   InsertMenuItem(hMenu, this.Parent->GetNextCtrlID, false, @itemInfo)
   
   SetMenu(hWndParent, hMenu)
   DrawMenuBar(hWndParent)
   
   
'   ' Set the hWindow for the collection
'   this.Items.hWindow = this.hWindow
   _IsLoading = false

   function = 0
END FUNCTION


'' MENUITEM
property wfxMenuItem.hWindow() as hwnd
   property = _hWindow
END PROPERTY

property wfxMenuItem.hWindow( ByVal nValue As hwnd) 
   _hWindow = nValue
END PROPERTY

property wfxMenuItem.Index() as long
   property = _Index
End Property

property wfxMenuItem.Index( ByVal nValue As long) 
   _Index = nValue
END PROPERTY

Property wfxMenuItem.Selected() As boolean
   if this.hWindow then 
   end if
   property = _Selected
END PROPERTY

property wfxMenuItem.Selected( ByVal nValue As boolean) 
   if this.hWindow then 
   end if
   _Selected = nValue
END PROPERTY

property wfxMenuItem.Text() as CWSTR
   if this.hWindow then 
      'DIM cbLen AS LONG = SendMessage(this.hWindow, LB_GETTEXTLEN, _Index, 0)
      'IF cbLen THEN 
      '   _Text = space(cbLen * 2)
      '   SendMessage( this.hWindow, LB_GETTEXT, _Index, CAST(LPARAM, _Text.vptr))
      'end if   
   end if   
   property = _Text
end property

property wfxMenuItem.Text( byref wszValue as wstring )
   if this.hWindow then 
'      dim as long nCurSel = SendMessage( this.hWindow, LB_GETCURSEL, 0, 0)
'      SendMessage( this.hWindow, LB_DELETESTRING, _Index, 0)
'      dim as long nCount = SendMessage( this.hWindow, LB_GETCOUNT, 0, 0)
'      _Index = SendMessage( this.hWindow, LB_INSERTSTRING, iif(_Index > nCount - 1, -1, _Index), CAST(LPARAM, @wszValue))
'      SendMessage( this.hWindow, LB_SETCURSEL, nCurSel, 0)
   end if   
   _Text = wszValue
end property

property wfxMenuItem.Data32() as long
   if this.hWindow then 
   '   _Data32 = SendMessage( this.hWindow, LB_GETITEMDATA, _Index, 0)
   end if
   property = _Data32
end property

property wfxMenuItem.Data32( byVal nValue as long)
   if this.hWindow then 
   '   SendMessage( this.hWindow, LB_SETITEMDATA, _Index, CAST(LPARAM, nValue))
   end if
   _Data32 = nValue
end property


'' MENUITEMS COLLECTION
constructor wfxMenuItemsCollection
   '
END CONSTRUCTOR

destructor wfxMenuItemsCollection
   this.Clear
end destructor

property wfxMenuItemsCollection.hWindow() as hwnd
   property = _hWindow
end property

property wfxMenuItemsCollection.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

function wfxMenuItemsCollection.Count() as Long
   if this.hWindow then
      function = SendMessage( this.hWindow, LB_GETCOUNT, 0, 0 )
   else
      function = _Collection.Size
   end if
end function

Function wfxMenuItemsCollection.SelectedCount() As Long
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

Function wfxMenuItemsCollection.Add( ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
   If this.hWindow Then
      Dim As Long idx = SendMessage( this.hWindow, LB_ADDSTRING, 0, Cast(LPARAM, @wszValue) )
      SendMessage( this.hWindow, LB_SETITEMDATA, idx, CAST(LPARAM, nValue))
      Function = idx
   Else
      Dim pData As wfxMenuItem Ptr = New wfxMenuItem
      pData->hWindow = this.hWindow
      pData->Index = (this.Count - 1) + 1
      pData->Text = wszValue
      pData->Data32 = nValue
      _Collection.Add( ControlType.ListBox, pData ) 
      function = pData->Index
   END IF
end function

function wfxMenuItemsCollection.Remove( byval nIndex as long ) as long
   if this.hWindow then
      function = SendMessage( this.hWindow, LB_DELETESTRING, nIndex, 0)
   else
      dim pItem as wfxMenuItem ptr
      dim pNode as wfxLListNode ptr
      pNode = _Collection.get_first
      do until pNode = 0
         pItem = cast(wfxMenuItem ptr, pNode->pData)
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

function wfxMenuItemsCollection.ByIndex( byval nIndex as long ) byref as wfxMenuItem 
   dim pItem as wfxMenuItem ptr
   dim pNode as wfxLListNode ptr
   pNode = _Collection.get_first
   do until pNode = 0
      pItem = cast(wfxMenuItem ptr, pNode->pData)
      if pItem->Index = nIndex then
         exit do
      END IF
      pNode = _Collection.get_next(pNode)
   LOOP
   return *pItem
end function

function wfxMenuItemsCollection.Clear() as long
   if this.hWindow then
      SendMessage( this.hWindow, LB_RESETCONTENT, 0, 0)
   else
      ' Deallocate elements in the Items collection.
      dim pNode as wfxLListNode ptr = _Collection.get_first
      do until pNode = 0
         Delete cast(wfxMenuItem ptr, pNode->pData)
         pNode = _Collection.remove(pNode)
      LOOP
   end if
   function = 0
END FUNCTION



