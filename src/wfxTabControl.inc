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

' TabControl Class

#include once "wfxTabControl.bi"

constructor wfxTabControl( byref wszName as wstring = "" )
   this.CtrlType = ControlType.TabControl
   this.Name     = wszName
end constructor

destructor wfxTabControl
   if this.TabPages.hImageList then ImageList_Destroy(this.TabPages.hImageList)
end destructor


property wfxTabControl.TabHeight( byval nValue as long )
   _TabHeight = nValue
end property

property wfxTabControl.TabHeight() as Long
   property = _TabHeight 
end property

property wfxTabControl.TabWidth( byval nValue as long )
   _TabWidth = nValue
end property

property wfxTabControl.TabWidth() as Long
   property = _TabWidth 
end property

property wfxTabControl.TabTopPadding( byval nValue as long )
   _TabTopPadding = nValue
end property

property wfxTabControl.TabTopPadding() as Long
   property = _TabTopPadding 
end property

property wfxTabControl.TabSidePadding( byval nValue as long )
   _TabSidePadding = nValue
end property

property wfxTabControl.TabSidePadding() as Long
   property = _TabSidePadding 
end property

property wfxTabControl.SelectedIndex( byval nValue as long )
   if this.hWindow then
      this.HideTabPage( this.TabPages.SelectedIndex )
      TabCtrl_SetCurSel( this.hWindow, nValue )
      TabCtrl_SetCurFocus( this.hWindow, nValue )
      this.ShowTabPage( nValue )
   end if      
   this.TabPages.SelectedIndex = nValue
end property

property wfxTabControl.SelectedIndex() as Long
   property = this.TabPages.SelectedIndex 
end property

property wfxTabControl.TabImageSize( byval nValue as ControlImageSize )
   _TabImageSize = nValue
end property

property wfxTabControl.TabImageSize() as ControlImageSize
   property = _TabImageSize
end property

Function wfxTabControl.TabPage( ByVal nIndex As Long ) ByRef As wfxTabPage
   return this.TabPages.ByIndex(nIndex)
END function

function wfxTabControl.TabPages byref As wfxTabPageCollection
   return this._TabPageCollection
END function

Property wfxTabControl.BorderStyle() As ControlBorderStyle
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

Property wfxTabControl.BorderStyle( ByVal nValue As ControlBorderStyle )
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

Property wfxTabControl.ResizeTabPages() As boolean
   property = _ResizeTabPages
end property

Property wfxTabControl.ResizeTabPages( ByVal nValue As boolean)
   _ResizeTabPages = nValue
end property

Property wfxTabControl.FixedWidthTabs() As boolean
   property = _FixedWidthTabs
end property

Property wfxTabControl.FixedWidthTabs( ByVal nValue As boolean)
   _FixedWidthTabs = nValue
end property

Property wfxTabControl.ButtonStyle() As boolean
   property = _ButtonStyle
end property

Property wfxTabControl.ButtonStyle( ByVal nValue As boolean)
   _ButtonStyle = nValue
end property

Property wfxTabControl.ForceImageLeft() As boolean
   property = _ForceImageLeft
end property

Property wfxTabControl.ForceImageLeft( ByVal nValue As boolean)
   _ForceImageLeft = nValue
end property

Property wfxTabControl.ForceLabelLeft() As boolean
   property = _ForceLabelLeft
end property

Property wfxTabControl.ForceLabelLeft( ByVal nValue As boolean)
   _ForceLabelLeft = nValue
end property

Property wfxTabControl.AllowFocus() As boolean
   property = _AllowFocus
end property

Property wfxTabControl.AllowFocus( ByVal nValue As boolean)
   _AllowFocus = nValue
end property

Property wfxTabControl.HotTracking() As boolean
   property = _HotTracking
end property

Property wfxTabControl.HotTracking( ByVal nValue As boolean)
   _HotTracking = nValue
end property

Property wfxTabControl.hImageList() As HANDLE
   property = this.TabPages.hImageList
end property

Property wfxTabControl.hImageList( ByVal nValue As HANDLE)
   this.TabPages.hImageList = nValue
end property



function wfxTabControl.ShowTabPage( byval nIndex as long ) as long
   ' Show the current TabPage
   if (nIndex >= 0) and (nIndex <= this.TabPages.Count - 1) then
      ShowWindow( this.TabPage(nIndex).hWindowChildForm, SW_SHOW )
      this.TabPages.SelectedIndex = nIndex
   end if   
   function = 0
end function

function wfxTabControl.HideTabPage( byval nIndex as long ) as long
   ' Hide the current TabPage
   if (nIndex >= 0) and (nIndex <= this.TabPages.Count - 1) then
      ShowWindow( this.TabPage(nIndex).hWindowChildForm, SW_HIDE )
   end if   
   function = 0
end function
   

function wfxTabControl.AutoResizeTabPages() as long

   if this.hWindow = 0 then exit function
   
   ' Retrieve the size of the tab control window
   DIM rcParent AS RECT
   GetWindowRect( this.hWindow, @rcParent )

   ' Calculate the tab control display area given its window rectangle
   SendMessage( this.hWindow, TCM_ADJUSTRECT, FALSE, CAST(LPARAM, @rcParent) )
   MapWindowPoints( NULL, this.hWindow, CAST(LPPOINT, @rcParent), 2 )
   
   ' Move the tab pages
   for i as long = 0 to this.TabPages.Count - 1
      if this.ResizeTabPages then
         SetWindowPos( this.TabPage(i).hWindowChildForm, 0, _
                       rcParent.Left, rcParent.Top, _ 
                       rcParent.Right - rcParent.Left, _
                       rcParent.Bottom - rcParent.Top, _
                       SWP_NOZORDER )
      else   
         SetWindowPos( this.TabPage(i).hWindowChildForm, 0, _
                       rcParent.Left, rcParent.Top, 0, 0, SWP_NOSIZE or SWP_NOZORDER )
      end if
   next

   function = 0
end function



function wfxTabControl.Show(byval hWndParent as hwnd = 0) as long

   ' If the control is created but simply hidden, then show it.
   if this.hWindow THEN
      ShowWindow(this.hWindow, SW_SHOW)
      exit function
   END IF

   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function
      
   Dim As Long dwExStyle = WS_EX_CONTROLPARENT
   dim as long dwStyle = WS_CLIPCHILDREN OR WS_CLIPSIBLINGS
  
   if _TabStop then dwStyle = dwStyle OR WS_TABSTOP 
   if _Visible THEN dwStyle = dwStyle OR WS_VISIBLE
   
   if _HotTracking THEN dwStyle = dwStyle OR TCS_HOTTRACK

   if _AllowFocus THEN 
      dwStyle = dwStyle OR TCS_FOCUSONBUTTONDOWN
   else   
      dwStyle = dwStyle OR TCS_FOCUSNEVER
   end if
   
   if _ButtonStyle then 
      dwStyle = dwStyle or TCS_BUTTONS or TCS_FLATBUTTONS
   else
      dwStyle = dwStyle or TCS_TABS
   end if

   if _FixedWidthTabs then
      dwStyle = dwStyle or TCS_FIXEDWIDTH
   else
      dwStyle = dwStyle or TCS_RAGGEDRIGHT
   end if

   if _MultiLine then 
      dwStyle = dwStyle or TCS_MULTILINE
   else   
      dwStyle = dwStyle or TCS_SINGLELINE
   end if
         
   if _ForceLabelLeft then
      ' This will force the label and icon left
      dwStyle = dwStyle or TCS_FORCELABELLEFT
   else
      if _ForceImageLeft then
         dwStyle = dwStyle or TCS_FORCEICONLEFT
      end if
   end if
            
   _CtrlID = this.Parent->GetNextCtrlID()

   this.hWindow = this.Parent->pWindow->AddControl ( _
         "SysTabControl32", _              ' // Class name
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

   ' Set the text for the tabs.
   dim as boolean bHasImages 
   For i As Long = 0 To this.TabPages.Count - 1
      if len(rtrim(TabPage(i).Image)) then 
         bHasImages = true: exit for
      end if
   next
   if bHasImages then
      dim as long cx = _TabImageSize * (this.Parent->pWindow->DPI \ 96)
      this.TabPages.hImageList = ImageList_Create(cx, cx, ILC_MASK Or ILC_COLOR32, 1, 0)
   end if

   if this.TabPages.hImageList then 
      SendMessage( this.hWindow, TCM_SETIMAGELIST, 0, cast(LPARAM, this.TabPages.hImageList) )
   end if
   
   ' Set the hWindow for the collection
   this.TabPages.hWindow = this.hWindow

   For i As Long = 0 To this.TabPages.Count - 1
      this.TabPages.CreateTabPageInternal(i)
   Next
   
   TabCtrl_SetCurSel( this.hWindow, this.TabPages.SelectedIndex )
   TabCtrl_SetCurFocus( this.hWindow, this.TabPages.SelectedIndex )
   this.AutoResizeTabPages
   this.ShowTabPage(this.TabPages.SelectedIndex)
   

   if _FixedWidthTabs then
      dim as long nWidth  = AfxScaleX(_TabWidth)
      dim as long nHeight = AfxScaleY(_TabHeight)
      if (nWidth * nHeight) <> 0 then  ' neither can be zero
         TabCtrl_SetItemSize( this.hWindow, nWidth, nHeight )
      end if   
   end if
         
   ' Set the horizontal and vertical padding
   dim as long nHorizPadding = AfxScaleX(_TabSidePadding)
   dim as long nVertPadding  = AfxScaleY(_TabTopPadding)
   TabCtrl_SetPadding( this.hWindow, nHorizPadding, nVertPadding )

   function = 0
END FUNCTION


'' TABPAGE ITEM
property wfxTabPage.hWindow() as hwnd
   property = _hWindow
END PROPERTY

property wfxTabPage.hWindow( ByVal nValue As hwnd) 
   _hWindow = nValue
END PROPERTY

property wfxTabPage.Index() as long
   property = _Index
End Property

property wfxTabPage.Index( ByVal nValue As long) 
   _Index = nValue
END PROPERTY

Property wfxTabPage.Selected() As boolean
   if this.hWindow then 
      _Selected = iif( TabCtrl_GetCurSel(this.hWindow) = this.Index, true, false )
   end if
   property = _Selected
END PROPERTY

property wfxTabPage.Selected( ByVal nValue As boolean) 
   if this.hWindow then 
      if nValue = true then
         TabCtrl_SetCurSel( this.hWindow, this.Index )
         TabCtrl_SetCurFocus( this.hWindow, this.Index )
      end if   
   end if
   _Selected = nValue
END PROPERTY

property wfxTabPage.Text() as CWSTR
   property = _Text
end property

property wfxTabPage.Text( byref wszValue as wstring )
   _Text = wszValue
end property

property wfxTabPage.ChildFormName() as CWSTR
   property = _ChildFormName
end property

property wfxTabPage.ChildFormName( byref wszValue as wstring )
   _ChildFormName = wszValue
end property

property wfxTabPage.hWindowChildForm() as hwnd
   property = _hWindowChildForm
END PROPERTY

property wfxTabPage.hWindowChildForm( ByVal nValue As hwnd) 
   _hWindowChildForm = nValue
END PROPERTY

property wfxTabPage.Image() as CWSTR
   property = _Image
end property

property wfxTabPage.Image( byref wszValue as wstring )
   _Image = wszValue
end property

property wfxTabPage.Data32() as long
   if this.hWindow then 
      DIM ttc_item AS TCITEM
      ttc_item.mask = TCIF_PARAM
      SendMessage( this.hWindow, TCM_GETITEM, cast(WPARAM, this.Index), cast(LPARAM, @ttc_item))
      _Data32 = ttc_item.lParam
   end if
   property = _Data32
end property

property wfxTabPage.Data32( byVal nValue as long)
   if this.hWindow then 
      DIM ttc_item AS TCITEM
      ttc_item.mask = TCIF_PARAM
      ttc_item.lParam = nValue
      SendMessage( this.hWindow, TCM_SETITEM, cast(WPARAM, this.Index), cast(LPARAM, @ttc_item))
   end if
   _Data32 = nValue
end property


'' TABPAGECOLLECTION
constructor wfxTabPageCollection
   '
END CONSTRUCTOR

destructor wfxTabPageCollection
   this.Clear
end destructor

property wfxTabPageCollection.hWindow() as hwnd
   property = _hWindow
end property

property wfxTabPageCollection.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

function wfxTabPageCollection.Count() as Long
   function = _Collection.Size
end function


function wfxTabPageCollection.CreateTabPageInternal( byval i as long ) as Long
   ' The incoming i variable is the index of the tabpage within the collection to create.
   dim pForm as wfxForm ptr
   Dim As CWSTR wszItemText = this.ByIndex(i).Text

   dim as long nImageIndex = -1
   if len(rtrim(this.ByIndex(i).Image)) then
      dim hInst AS HINSTANCE = GetModuleHandle(null)
      nImageIndex = AfxGdipAddIconFromRes( this.hImageList, hInst, this.ByIndex(i).Image )
   end if

   Dim As Long nData32 = this.ByIndex(i).data32

   TabCtrl_AddTab( this.hWindow, nImageIndex, wszItemText, nData32 )

   ' Create the child TabPage.
   pForm = Application.GetpFormObjectByName( this.ByIndex(i).ChildFormName )
   if pForm then
      pForm->ShowChild( this.hWindow )
      this.ByIndex(i).hWindowChildForm = pForm->hWindow
      ' ensure the child is not visible
      pForm->Visible = false
   end if
   
   function = 0
end function


''  ADD: Dynamically adding pages at run time not implemente dyet.
Function wfxTabPageCollection.Add( ByRef wszText As WString = "", _
                                   ByRef wszTabPage As WString = "", _
                                   ByRef wszImage As WString = "", _
                                   ByVal nValue As Long = 0) As Long
   Dim pData As wfxTabPage Ptr = New wfxTabPage
   pData->hWindow = this.hWindow
   pData->Index   = (this.Count - 1) + 1
   pData->Text    = wszText
   pData->ChildFormName = wszTabPage
   pData->Image   = wszImage
   pData->Data32  = nValue
   _Collection.Add( ControlType.TabControl, pData ) 
   function = pData->Index

   If this.hWindow Then
      this.CreateTabPageInternal(pData->Index)
   END IF
end function

''  INSERT: Dynamically inserting pages at run time not implemente dyet.
Function wfxTabPageCollection.Insert( byval nIndex as long, _
                                      ByRef wszText As WString = "", _
                                      ByRef wszTabPage As WString = "", _
                                      ByRef wszImage As WString = "", _
                                      ByVal nValue As Long = 0) As Long
   Dim pData As wfxTabPage Ptr = New wfxTabPage
   pData->hWindow = this.hWindow
   pData->Index   = nIndex
   pData->Text    = wszText
   pData->ChildFormName = wszTabPage
   pData->Image   = wszImage
   pData->Data32  = nValue
   _Collection.Insert( nIndex, ControlType.ListBox, pData ) 
   function = pData->Index
    
   ' Renumber the Index property for each item in the collection.
   dim pNode as wfxLListNode ptr 
   dim pTabPage as wfxTabPage ptr
   for i as long = 0 to _Collection.Size - 1
      pNode = _Collection.get_index(i)
      pTabPage = cast(wfxTabPage ptr, pNode->pData)
      if pTabPage then pTabPage->Index = i
   next

   If this.hWindow Then
      this.CreateTabPageInternal(pData->Index)
   END IF
end function

function wfxTabPageCollection.Remove( byval nIndex as long ) as long
   if nIndex < 0 then exit function
   if this.hWindow then
      ShowWindow( this.ByIndex(nIndex).hWindowChildForm, SW_HIDE )
      TabCtrl_DeleteItem( this.hWindow, nIndex )
   end if
   
   dim pNode as wfxLListNode ptr = _Collection.get_index(nIndex)
   if pNode then
      Delete cast(wfxTabPage ptr, pNode->pData)
      _Collection.Remove(pNode)
   end if   

   ' Renumber the Index property for each item in the collection.
   dim pTabPage as wfxTabPage ptr
   for i as long = 0 to _Collection.Size - 1
      pNode = _Collection.get_index(i)
      pTabPage = cast(wfxTabPage ptr, pNode->pData)
      if pTabPage then pTabPage->Index = i
   next
   this.SelectedIndex = Min( this.SelectedIndex, _Collection.Size - 1 )
   if this.SelectedIndex >= 0 then
      TabCtrl_SetCurSel( this.hWindow, this.SelectedIndex )
      TabCtrl_SetCurFocus( this.hWindow, this.SelectedIndex )
      ShowWindow( this.ByIndex(this.SelectedIndex).hWindowChildForm, SW_SHOW )
   end if
   
   function = _Collection.Size
end function

function wfxTabPageCollection.ByIndex( byval nIndex as long ) byref as wfxTabPage
   Dim pItem As wfxTabPage Ptr 
   dim pNode as wfxLListNode ptr
   pNode = _Collection.get_index(nIndex)
   if pNode then 
      pItem = cast(wfxTabPage Ptr , pNode->pData)
      return *pItem
   end if
end function

function wfxTabPageCollection.Clear() as long
   ' Deallocate elements in the Items collection.
   dim pNode as wfxLListNode ptr = _Collection.get_first
   do until pNode = 0
      Delete cast(wfxTabPage ptr, pNode->pData)
      pNode = _Collection.remove(pNode)
   LOOP
   function = 0
END FUNCTION



