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

destructor wfxMainMenu()
end destructor

Function wfxMainMenu.MenuItem( ByVal nIndex As Long ) ByRef As wfxMenuItem
   return this.MenuItems.ByIndex(nIndex)
END function

function wfxMainMenu.MenuItems byref As wfxMenuItemsCollection
   return this._ItemsCollection
END function

property wfxMainMenu.Handle() as HMENU
   property = _Handle
END PROPERTY

property wfxMainMenu.Handle( ByVal nValue As HMENU) 
   _Handle = nValue
END PROPERTY

Property wfxMainMenu.IsLoading() As boolean
   property = _IsLoading
END PROPERTY

property wfxMainMenu.IsLoading( ByVal nValue As boolean) 
   _IsLoading = nValue
END PROPERTY


function wfxMainMenu.GetByPopupMenuHandle_Internal( byval hPopupMenu as HMENU, _
                                                    byval pMenuItem as _wfxMenuItem ptr _
                                                    ) as _wfxMenuItem ptr
   dim pSubMenuItem as wfxMenuItem ptr
   dim pFoundMenuItem as wfxMenuItem ptr
   For i As Long = 0 To pMenuItem->MenuItems.Count - 1
      pSubMenuItem = @pMenuItem->MenuItem(i)
      if pSubMenuItem->PopupMenuHandle = hPopupMenu then return pSubMenuItem
      if pSubMenuItem->IsParent then
         pFoundMenuItem = this.GetByPopupMenuHandle_Internal( hPopupMenu, pSubMenuItem )
         if pFoundMenuItem then return pFoundMenuItem
      end if   
   Next
   function = 0
end function

Function wfxMainMenu.ByPopupMenuHandle( ByVal hPopupMenu As HMENU ) ByRef As wfxMenuItem
   dim pMenuItem as wfxMenuItem ptr
   dim pFoundMenuItem as wfxMenuItem ptr
   For i As Long = 0 To this.MenuItems.Count - 1
      pMenuItem = @this.MenuItem(i)
      if pMenuItem->PopupMenuHandle = hPopupMenu then 
         pFoundMenuItem = pMenuItem: exit for
      end if
      pFoundMenuItem = this.GetByPopupMenuHandle_Internal( hPopupMenu, pMenuItem) 
      if pFoundMenuItem then exit for
   Next
   if pFoundMenuItem then return *(pFoundMenuItem)
END function

function wfxMainMenu.GetByMenuID_Internal( byval nMenuID as long, _
                                           byval pMenuItem as _wfxMenuItem ptr _
                                           ) as _wfxMenuItem ptr
   dim pSubMenuItem as wfxMenuItem ptr
   dim pFoundMenuItem as wfxMenuItem ptr
   For i As Long = 0 To pMenuItem->MenuItems.Count - 1
      pSubMenuItem = @pMenuItem->MenuItem(i)
      if pSubMenuItem->MenuID = nMenuID then return pSubMenuItem
      if pSubMenuItem->IsParent then
         pFoundMenuItem = this.GetByMenuID_Internal( nMenuID, pSubMenuItem )
         if pFoundMenuItem then return pFoundMenuItem
      end if   
   Next
   function = 0
end function

Function wfxMainMenu.ByMenuID( ByVal nMenuID As Long ) ByRef As wfxMenuItem
   dim pMenuItem as wfxMenuItem ptr
   dim pFoundMenuItem as wfxMenuItem ptr
   For i As Long = 0 To this.MenuItems.Count - 1
      pMenuItem = @this.MenuItem(i)
      if pMenuItem->MenuID = nMenuID then 
         pFoundMenuItem = pMenuItem: exit for
      end if
      pFoundMenuItem = this.GetByMenuID_Internal( nMenuID, pMenuItem) 
      if pFoundMenuItem then exit for
   Next
   if pFoundMenuItem then return *(pFoundMenuItem)
END function

function wfxMainMenu.GetByMenuName_Internal( byref wszMenuName_ucase as WString, _
                                             byval pMenuItem as _wfxMenuItem ptr _
                                             ) as _wfxMenuItem ptr
   dim pSubMenuItem as wfxMenuItem ptr
   dim pFoundMenuItem as wfxMenuItem ptr
   For i As Long = 0 To pMenuItem->MenuItems.Count - 1
      pSubMenuItem = @pMenuItem->MenuItem(i)
      if ucase(pSubMenuItem->Name) = wszMenuName_ucase then return pSubMenuItem
      if pSubMenuItem->IsParent then
         pFoundMenuItem = this.GetByMenuName_Internal( wszMenuName_ucase, pSubMenuItem )
         if pFoundMenuItem then return pFoundMenuItem
      end if   
   Next
   function = 0
end function

Function wfxMainMenu.ByMenuName( byref wszMenuName as WString ) ByRef As wfxMenuItem
   dim pMenuItem as wfxMenuItem ptr
   dim pFoundMenuItem as wfxMenuItem ptr
   dim wszMenuName_ucase as CWSTR = ucase(wszMenuName)
   For i As Long = 0 To this.MenuItems.Count - 1
      pMenuItem = @this.MenuItem(i)
      if ucase(pMenuItem->Name) = wszMenuName_ucase then 
         pFoundMenuItem = pMenuItem: exit for
      end if
      pFoundMenuItem = this.GetByMenuName_Internal( wszMenuName_ucase, pMenuItem) 
      if pFoundMenuItem then exit for
   Next
   if pFoundMenuItem then return *(pFoundMenuItem)
END function


function wfxMainMenu.CreateMenuStructure_Internal( byval hSubMenu as HMENU, _
                                                   byref tMenuItem as _wfxMenuItem _
                                                   ) as long
   ' Internal function that recursive creates all of the menu items. It takes into
   ' account that submenus can exist for each MenuItem.
   dim as long NumItems = tMenuItem.MenuItems.Count 
   dim as long fState
   dim wszText as wstring * MAX_PATH

   tMenuItem.MenuParent = @this
   tMenuItem.MenuID = this.Parent->GetNextCtrlID

   wszText = tMenuItem.Text 
   if len(tMenuItem.Shortcut) then wszText = wszText & wchr(9) & tMenuItem.Shortcut

   fState = fState or iif(tMenuItem.Checked, MFS_CHECKED, MFS_UNCHECKED)
   fState = fState or iif(tMenuItem.Grayed, MFS_GRAYED, MFS_ENABLED)
   
   dim as MENUITEMINFO itemInfo
   with itemInfo
      .cbSize     = sizeof(MENUITEMINFO)
      .fMask      = MIIM_ID or MIIM_FTYPE or MIIM_STATE or MIIM_STRING or MIIM_SUBMENU
      .fType      = iif(wszText = "-", MFT_SEPARATOR, MFT_STRING)
      .fState     = fState
      .wID        = tMenuItem.MenuID
      .dwTypeData = @wszText
      .hSubMenu   = iif( NumItems > 0, CreatePopupMenu, null)
   end with

   if len(tMenuItem.Shortcut) then 
      dim pWindow as CWindow ptr = AfxCWindowPtr(this.hWindow) 
      if pWindow then
         ' Parse the shortcut string into format suitable for accelerator
         dim as CWSTR wszShortcut = tMenuItem.Shortcut
         dim as CWSTR wszKey, wszSt
         dim as long nShiftState = FVIRTKEY
         dim as long nKey, NumParses
         
         If Right(wszShortcut,2) = "++" Then wszShortcut = AfxStrReplace(wszShortcut, "++", "+PLUS")
         If Right(wszShortcut,2) = "+-" Then wszShortcut = AfxStrReplace(wszShortcut, "+-", "+MINUS")

         ' Determine how many Parses (could have a Shortcut like Ctrl+Shift+B etc..)
         NumParses = AfxStrParseCount( wszShortcut, "+" )
         If NumParses = 0 Then
            ' No '+' key was found, therefore must be a regular function key. e.g. F1, F2, F3 etc..   
            wszKey = Trim(wszShortcut)  
         Else
            For i as long = 1 To NumParses 
               wszSt = Trim(AfxStrParse(wszShortcut, i, "+"))  ' e.g.  CTRL
               select case UCase(wszSt)
                  case "CTRL":   nShiftState = nShiftState Or FCONTROL
                  case "SHIFT":  nShiftState = nShiftState Or FSHIFT
                  case "ALT":    nShiftState = nShiftState Or FALT
                  CASE ELSE
                     wszKey = wszSt
               end select
            Next                                           
         End If
         Select Case ucase(wszKey)
            Case "ENTER": nKey = VK_RETURN
            Case "PLUS":  nKey = VK_OEM_PLUS
            Case "MINUS": nKey = VK_OEM_MINUS
            case "INS":   nKey = VK_INSERT
            case "DEL":   nKey = VK_DELETE
            case "TAB":   nKey = VK_TAB
            case "LEFT":  nKey = VK_LEFT
            case "RIGHT": nKey = VK_RIGHT
            case "UP":    nKey = VK_UP
            case "DOWN":  nKey = VK_DOWN
            case "HOME":  nKey = VK_HOME
            case "END":   nKey = VK_END
            case "PGUP":  nKey = VK_PRIOR
            case "PGDN":  nKey = VK_NEXT
            case "SPACE": nKey = VK_SPACE
            Case "F1":    nKey = VK_F1
            Case "F2":    nKey = VK_F2
            Case "F3":    nKey = VK_F3
            Case "F4":    nKey = VK_F4
            Case "F5":    nKey = VK_F5
            Case "F6":    nKey = VK_F6
            Case "F7":    nKey = VK_F7
            Case "F8":    nKey = VK_F8
            Case "F9":    nKey = VK_F9
            Case "F10":   nKey = VK_F10
            Case "F11":   nKey = VK_F11
            Case "F12":   nKey = VK_F12
         End Select      
         if nKey then
            pWindow->AddAccelerator(nShiftState, nKey, tMenuItem.MenuID)
         else   
            pWindow->AddAccelerator(nShiftState, wszKey, tMenuItem.MenuID)
         end if
      end if
   end if

   if itemInfo.hSubMenu then 
      tMenuItem.IsParent = true
      tMenuItem.PopupMenuHandle = itemInfo.hSubMenu
   end if

   InsertMenuItem(hSubMenu, tMenuItem.MenuID, false, @itemInfo)

   For i As Long = 0 To NumItems - 1
      ' Make sure that the main menu handle propagates down through all of the MenuItems
      this.CreateMenuStructure_Internal(itemInfo.hSubMenu, tMenuItem.MenuItem(i))
   Next
   
   function = 0
end function


function wfxMainMenu.Show(byval hWndParent as hwnd = 0) as long

   
   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function

   this.hWindow = hWndParent    ' Form handle of window owning this mainmenu
   this.Handle = CreateMenu()
   this.IsLoading = true

   ' Set the text for the MainMenu items that display across the top of the form
   For i As Long = 0 To this.MenuItems.Count - 1
      this.CreateMenuStructure_Internal(this.Handle, this.MenuItem(i))
   Next
   
   ' Create the keyboard accelerator table. The table will only successfully
   ' create if one or more accelerator keys had alreayd been added to the pWindow.
   dim pWindow as CWindow ptr = AfxCWindowPtr(this.hWindow) '(hWndParent)
   if pWindow then pWindow->CreateAcceleratorTable

   SetMenu(hWndParent, this.Handle)
   DrawMenuBar(hWndParent)

   ' Store the hWindow in the form's linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   dim pNode as wfxLListNode ptr = this.Parent->Controls.search_data(@this)
   if pNode then pNode->hWindow = cast(hwnd, this.Handle)

   this.IsLoading = false

   function = 0
END FUNCTION


'' MENUITEM
constructor wfxMenuItem( ByRef wszText     As WString = "", _
                         ByRef wszName     As WString = "", _ 
                         Byref wszShortcut As WString = "", _
                         ByVal bChecked    As boolean = false, _
                         ByVal bGrayed     As boolean = false _
                         )
   _Text     = wszText
   _Name     = wszName
   _Shortcut = wszShortcut
   _Checked  = bChecked
   _Grayed   = bGrayed
   _Enabled  = not bGrayed
end constructor

destructor wfxMenuItem
   
end destructor

Function wfxMenuItem.MenuItem( ByVal nIndex As Long ) ByRef As wfxMenuItem
   return this.MenuItems.ByIndex(nIndex)
END function

function wfxMenuItem.MenuItems byref As wfxMenuItemsCollection
   return this._ItemsCollection
END function

property wfxMenuItem.Handle() as HMENU
   if this.MenuParent then
      _Handle = this.MenuParent->Handle
   end if
   property = _Handle
END PROPERTY

property wfxMenuItem.Handle( ByVal nValue As HMENU) 
   _Handle = nValue
END PROPERTY

property wfxMenuItem.PopupMenuHandle() as HMENU
   property = _PopupMenuHandle
END PROPERTY

property wfxMenuItem.PopupMenuHandle( ByVal nValue As HMENU) 
   _PopupMenuHandle = nValue
END PROPERTY

Property wfxMenuItem.MenuParent() As wfxMainMenu ptr
   property = _MenuParent
end property

Property wfxMenuItem.MenuParent( Byval pValue As wfxMainMenu ptr)
   _MenuParent = pValue
end property

property wfxMenuItem.Index() as long
   property = _Index
End Property

property wfxMenuItem.Index( ByVal nValue As long) 
   _Index = nValue
END PROPERTY

property wfxMenuItem.MenuID() as long
   property = _MenuID
End Property

property wfxMenuItem.MenuID( ByVal nValue As long) 
   _MenuID = nValue
END PROPERTY

property wfxMenuItem.Shortcut() as CWSTR
   property = _Shortcut
End Property

property wfxMenuItem.Shortcut( Byref wszValue As WString ) 
   _Shortcut = wszValue
END PROPERTY

Property wfxMenuItem.IsParent() As boolean
   if this.Handle then 
      _IsParent = AfxIsMenuItemPopup(this.Handle, this.MenuID, false ) 
   end if
   property = _IsParent
END PROPERTY

property wfxMenuItem.IsParent( ByVal nValue As boolean) 
   _IsParent = nValue
END PROPERTY

Property wfxMenuItem.Selected() As boolean
   if this.Handle then 
   end if
   property = _Selected
END PROPERTY

property wfxMenuItem.Selected( ByVal nValue As boolean) 
   if this.Handle then 
   end if
   _Selected = nValue
END PROPERTY

Property wfxMenuItem.Checked() As boolean
   if this.Handle then
      if this.MenuParent->IsLoading = false then
         _Checked = AfxIsMenuItemChecked(this.Handle, this.MenuID, false)
      end if
   end if
   property = _Checked
END PROPERTY

property wfxMenuItem.Checked( ByVal nValue As boolean) 
   if this.Handle then
      if this.MenuParent->IsLoading = false then
         dim as long fState = iif(nValue, MFS_CHECKED, MFS_UNCHECKED)
         AfxSetMenuItemState(this.Handle, this.MenuID, fState, false)
         if AfxIsMenuItemPopup(this.Handle, this.MenuID, false ) then
            AfxRedrawWindow(this.MenuParent->hWindowParent)
         end if   
      end if
   end if
   _Checked = nValue
END PROPERTY

Property wfxMenuItem.Grayed() As boolean
   if this.Handle then
      if this.MenuParent->IsLoading = false then
         _Grayed = AfxIsMenuItemGrayed(this.Handle, this.MenuID, false)
      end if
   end if
   property = _Grayed
END PROPERTY

property wfxMenuItem.Grayed( ByVal nValue As boolean) 
   if this.Handle then
      if this.MenuParent->IsLoading = false then
         dim as long fState = iif(nValue, MFS_GRAYED, MFS_ENABLED)
         AfxSetMenuItemState(this.Handle, this.MenuID, fState, false)
         if AfxIsMenuItemPopup(this.Handle, this.MenuID, false ) then
            AfxRedrawWindow(this.MenuParent->hWindowParent)
         end if   
      end if
   end if
   _Grayed = nValue
END PROPERTY

Property wfxMenuItem.Enabled() As boolean
   if this.Handle then
      if this.MenuParent->IsLoading = false then
         _Enabled = not AfxIsMenuItemGrayed(this.Handle, this.MenuID, false)
      end if
   end if
   property = _Enabled
END PROPERTY

property wfxMenuItem.Enabled( ByVal nValue As boolean) 
   if this.Handle then
      if this.MenuParent->IsLoading = false then
         dim as long fState = iif(nValue, MFS_ENABLED, MFS_GRAYED)
         AfxSetMenuItemState(this.Handle, this.MenuID, fState, false)
         if AfxIsMenuItemPopup(this.Handle, this.MenuID, false ) then
            AfxRedrawWindow(this.MenuParent->hWindowParent)
         end if   
      end if
   end if
   _Enabled = nValue
END PROPERTY

property wfxMenuItem.Text() as CWSTR
   if this.Handle then
      if this.MenuParent->IsLoading = false then
         dim wszTemp as wstring * 260
         AfxGetMenuItemText( this.Handle, this.MenuID, false, @wszTemp, 260 )
         ' Filter out any keyboard accelerator
         _Text = AfxStrParse(wszTemp, 1, wchr(9))
      end if   
   end if
   property = _Text 
end property

property wfxMenuItem.Text( byref wszValue as wstring )
   if this.Handle then
      if this.MenuParent->IsLoading = false then
         AfxSetMenuItemText( this.Handle, this.MenuID, wszValue, false )
         if AfxIsMenuItemPopup(this.Handle, this.MenuID, false ) then
            AfxRedrawWindow(this.MenuParent->hWindowParent)
         end if   
      end if
   end if
   _Text = wszValue
end property

property wfxMenuItem.Name() as CWSTR
   property = _Name
end property

property wfxMenuItem.Name( byref wszValue as wstring )
   _Name = wszValue
end property


'' MENUITEMS COLLECTION
constructor wfxMenuItemsCollection
END CONSTRUCTOR

destructor wfxMenuItemsCollection
   this.Clear
end destructor

property wfxMenuItemsCollection.Handle() as HMENU
   property = _Handle
end property

property wfxMenuItemsCollection.Handle( byVal nValue as HMENU)
   _Handle = nValue
end property

function wfxMenuItemsCollection.Count() as Long
   function = _Collection.Size
end function

Function wfxMenuItemsCollection.Add( ByRef tMenuItem As _wfxMenuItem ) as long
   If this.Handle Then
      ' TODO: wfxMenuItemsCollection.Add
   Else
      Dim pData As wfxMenuItem Ptr = New wfxMenuItem
      ' Need to do a deep copy because the MenuItem structure contains the collection
      ' class that has manually allocated elements.
      pData->Handle   = this.Handle
      pData->Index    = (this.Count - 1) + 1
      pData->Selected = false
      pData->Text     = tMenuItem.Text
      pData->Name     = tMenuItem.Name
      pData->MenuID   = tMenuItem.MenuID
      pData->Shortcut = tMenuItem.Shortcut
      pData->Checked  = tMenuItem.Checked
      pData->Grayed   = tMenuItem.Grayed
      ' Copy the existing MenuItem collection to the newly created MenuItem
      for i as long = 0 to tMenuItem.MenuItems.Count - 1
         pData->MenuItems.Add(tMenuItem.MenuItem(i))
      next
      ' Add this new MenuItem to the collection
      _Collection.Add( ControlType.MainMenu, pData ) 
      function = pData->Index
   END IF
end function

function wfxMenuItemsCollection.Remove( byval nIndex as long ) as long
   if this.Handle then
      ' TODO: wfxMenuItemsCollection.Remove
   else
      dim pItem as wfxMenuItem ptr
      dim pNode as wfxLListNode ptr
      pNode = _Collection.get_index(nIndex)
      if pNode then
         Delete cast(wfxMenuItem ptr, pNode->pData)
         _Collection.Remove(pNode)
      end if
   END IF
   function = _Collection.Size
end function

function wfxMenuItemsCollection.ByIndex( byval nIndex as long ) byref as wfxMenuItem 
   dim pItem as wfxMenuItem ptr
   dim pNode as wfxLListNode ptr
   pNode = _Collection.get_index(nIndex)
   if pNode then
      pItem = cast(wfxMenuItem ptr, pNode->pData)
      return *pItem
   end if
end function

function wfxMenuItemsCollection.Clear() as long
   if this.Handle then
      DestroyMenu(this.Handle)
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



