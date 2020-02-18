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


#include once "wfxToolBar.bi"

''
''  wfxToolBar Class
''

''  TOOLBAR

constructor wfxToolBar
   this.CtrlType = ControlType.ToolBar
   this.Name = "ToolBar"
end constructor

destructor wfxToolBar
   '
END DESTRUCTOR

function wfxToolBar.Button( ByVal nIndex As long ) byref As wfxToolBarButton
   return this.Buttons.ByIndex(nIndex)
END function

function wfxToolBar.Buttons byref As wfxToolBarButtonsCollection
   return this._ButtonsCollection
END function

property wfxToolBar.hWindow() as hwnd
   property = _hWindow
end property

property wfxToolBar.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

property wfxToolBar.hRebar() as hwnd
   property = _hRebar
end property

property wfxToolBar.hRebar( byVal nValue as hwnd)
   _hRebar = nValue
end property

property wfxToolBar.ButtonSize() as long
   property = _ButtonSize
end property

property wfxToolBar.ButtonSize( byVal nValue as long)
   _ButtonSize = nValue
end property

property wfxToolBar.ClickIndex() as long
   property = _ClickIndex
end property

property wfxToolBar.ClickIndex( byVal nValue as long)
   _ClickIndex = nValue
end property

property wfxToolBar.ClickDropDownIndex() as long
   property = _ClickDropDownIndex
end property

property wfxToolBar.ClickDropDownIndex( byVal nValue as long)
   _ClickDropDownIndex = nValue
end property

function wfxToolBar.Show(byval hWndParent as hwnd = 0) as long

   ' If the control is created but simply hidden, then show it.
   if this.hRebar THEN
      ShowWindow(this.hRebar, SW_SHOW)
      ShowWindow(this.hWindow, SW_SHOW)
      exit function
   END IF

   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function
      
   dim as long dwExStyle = 0
   dim as long dwStyle = WS_CHILD Or WS_VISIBLE Or TBSTYLE_TOOLTIPS Or TBSTYLE_FLAT Or CCS_NODIVIDER Or CCS_NOPARENTALIGN

   if this.Visible THEN dwStyle = dwStyle OR WS_VISIBLE
   
   _CtrlID = this.Parent->GetNextCtrlID()

   ' Create the Rebar and ToolBar
   this.hRebar = _
         this.Parent->pWindow->AddControl("Rebar", hWndParent, 100)
         
   this.hWindow = _
         this.Parent->pWindow->AddControl ( _
         "TOOLBAR", _
         hWndParent, _
         101, _                            ' Control identifier (this gets modified when added to controls collection)
         "", _
         this.Left, _                      ' Horizontal position
         this.Top, _                       ' Vertical position
         this.Width, _                     ' Control width
         this.Height, _                    ' Control height
         dwStyle, _                        ' Control style
         dwExStyle, _                      ' Extended style
         0, _                              ' Pointer to custom data
         Cast(SUBCLASSPROC, @wfxApplication.SubclassProc), _   ' Address of the window callback procedure
         _CtrlID, _                        ' The subclass ID
         Cast(DWORD_PTR, 0) _              ' Pointer to reference data
         )

   ' Set the button size
   DIM AS LONG nButtonWidth, nButtonHeight
   nButtonWidth = this.ButtonSize * this.Parent->pWindow->rxRatio
   nButtonHeight = this.ButtonSize * this.Parent->pWindow->ryRatio
   SendMessage( this.hWindow, TB_SETBUTTONSIZE, 0, MAKELONG(nButtonWidth, nButtonHeight) )
   ' Send this message for backward compatibility
   SendMessage( this.hWindow, TB_BUTTONSTRUCTSIZE, SIZEOF(TBBUTTON), 0 )

   ' Allow drop down arrows
   SendMessage( this.hWindow, TB_SETEXTENDEDSTYLE, 0, TBSTYLE_EX_DRAWDDARROWS )

   Dim As HIMAGELIST hImageListNormal, hImageListHot, hImageListDisabled
   hImageListNormal   = ImageList_Create( nButtonWidth, nButtonHeight, ILC_COLOR32 Or ILC_MASK, 20, 1)
   hImageListHot      = ImageList_Create( nButtonWidth, nButtonHeight, ILC_COLOR32 Or ILC_MASK, 20, 1)
   hImageListDisabled = ImageList_Create( nButtonWidth, nButtonHeight, ILC_COLOR32 Or ILC_MASK, 20, 1)

   ' Update the hWindow in the form's linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   dim pNode as wfxLListNode ptr = this.Parent->Controls.search_data(@this)
   if pNode then pNode->hWindow = this.hWindow

   ' Make sure the Buttons collection also knows the window handle of the parent toolbar
   this.Buttons.hWindow = this.hWindow

   ' Add buttons to the toolbar
   Dim As Long i, ii
   
   for i as long = 0 to this.Buttons.Count - 1

      this.Button(i).hWindow = this.hWindow
      
      ii = -1
      if this.Button(i).ButtonType = ToolBarButton.Separator then
         Toolbar_AddSeparator this.hWindow
      else
         if len( this.Button(i).NormalImage ) then
            ii = AfxGdipAddIconFromRes( hImageListNormal, this.Parent->pWindow->InstanceHandle, this.Button(i).NormalImage )
         end if
         if len( this.Button(i).HotImage ) then
            ii = AfxGdipAddIconFromRes( hImageListHot, this.Parent->pWindow->InstanceHandle, this.Button(i).HotImage )
         end if
         if len( this.Button(i).DisabledImage ) then
            ii = AfxGdipAddIconFromRes( hImageListDisabled, this.Parent->pWindow->InstanceHandle, this.Button(i).DisabledImage )
         end if

         select case this.Button(i).ButtonType
            case ToolBarButton.Button:        dwStyle = 0
            case ToolBarButton.DropDown:      dwStyle = TBSTYLE_DROPDOWN
            case ToolBarButton.WholeDropDown: dwStyle = BTNS_WHOLEDROPDOWN
         end select      
         Toolbar_AddButton this.hWindow, ii, 1000 + i, 0, dwStyle
      end if

   next

   ' Attach the ImageLists to the toolbar
   SendMessage this.hWindow, TB_SETIMAGELIST, 0, Cast(LPARAM, hImageListNormal)
   SendMessage this.hWindow, TB_SETHOTIMAGELIST, 0, Cast(LPARAM, hImageListHot)
   SendMessage this.hWindow, TB_SETDISABLEDIMAGELIST, 0, Cast(LPARAM, hImageListDisabled)

   ' Size the toolbar
   SendMessage this.hWindow, TB_AUTOSIZE, 0, 0

   ' Add the band containing the toolbar control to the rebar
   ' The size of the REBARBANDINFOW is different in Vista/Windows 7
   Dim rbbi As REBARBANDINFOW
   If (AfxWindowsVersion >= 600) AndAlso (AfxComCtlVersion >= 600) Then
      rbbi.cbSize  = REBARBANDINFO_V6_SIZE
   Else
      rbbi.cbSize  = REBARBANDINFO_V3_SIZE
   End If

   ' Insert the toolbar in the rebar control
   rbbi.fMask      = RBBIM_STYLE Or RBBIM_CHILD Or RBBIM_CHILDSIZE Or _
                     RBBIM_SIZE Or RBBIM_ID Or RBBIM_IDEALSIZE Or RBBIM_COLORS
   rbbi.fStyle     = RBBS_CHILDEDGE Or RBBS_GRIPPERALWAYS
   rbbi.hwndChild  = this.hWindow
   rbbi.cxMinChild = 270 * this.Parent->pWindow->rxRatio
   rbbi.cyMinChild = Hiword(SendMessage(this.hWindow, TB_GETBUTTONSIZE, 0, 0))
   rbbi.cx         = 270 * this.Parent->pWindow->rxRatio
   rbbi.cxIdeal    = 270 * this.Parent->pWindow->rxRatio
   rbbi.clrFore    = GetSysColor(COLOR_BTNTEXT)
   rbbi.clrBack    = GetSysColor(COLOR_BTNFACE)

   ' Insert band into rebar
   SendMessage this.hRebar, RB_INSERTBANDW, -1, Cast(LPARAM, @rbbi)

   function = 0
END FUNCTION


''  ToolBarButton
property wfxToolBarButton.hWindow() as hwnd
   property = _hWindow
end property

property wfxToolBarButton.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

property wfxToolBarButton.Index() as long
   property = _Index
end property

property wfxToolBarButton.Index( byVal nValue as long)
   _Index = nValue
end property

property wfxToolBarButton.ButtonType() as ToolBarButton
   property = _ButtonType
end property

property wfxToolBarButton.ButtonType( byval nValue as ToolBarButton )
   _ButtonType = nValue
end property

property wfxToolBarButton.ToolTip() as CWSTR
   property = _ToolTip
end property

property wfxToolBarButton.ToolTip( byref wszValue as wstring )
   _ToolTip = wszValue
end property

property wfxToolBarButton.NormalImage() as CWSTR
   property = _NormalImage
end property

property wfxToolBarButton.NormalImage( byref cwzValue as wstring )
   _NormalImage = cwzValue
end property

property wfxToolBarButton.HotImage() as CWSTR
   property = _HotImage
end property

property wfxToolBarButton.HotImage( byref cwzValue as wstring )
   _HotImage = cwzValue
end property

property wfxToolBarButton.DisabledImage() as CWSTR
   property = _DisabledImage
end property

property wfxToolBarButton.DisabledImage( byref cwzValue as wstring )
   _DisabledImage = cwzValue
end property

Property wfxToolBarButton.Enabled() As boolean
   if this.hWindow then
      dim as long idButton = 1000 + this.Index
      _Enabled = SendMessage(this.hWindow, TB_ISBUTTONENABLED, cast(WPARAM, idButton), 0)
   end if
   property = _Enabled
end property

Property wfxToolBarButton.Enabled( ByVal nValue As boolean)
   if this.hWindow then
      dim as long idButton = 1000 + this.Index
      SendMessage(this.hWindow, TB_ENABLEBUTTON, cast(WPARAM, idButton), cast(LPARAM, MAKELONG(nValue, 0)) )
   end if
   _Enabled = nValue
end property


'' TOOLBARBUTTONS COLLECTION
constructor wfxToolBarButtonsCollection
   '
END CONSTRUCTOR

destructor wfxToolBarButtonsCollection
   ' Deallocate elements in the Buttons collection. The pData element
   ' of the node has been NEW with a ToolBarButton.
   dim pNode as wfxLListNode ptr = _Collection.get_first
   do until pNode = 0
      Delete cast(wfxToolBarButton ptr, pNode->pData)
      pNode = _Collection.remove(pNode) 
   LOOP
end destructor

property wfxToolBarButtonsCollection.hWindow() as hwnd
   property = _hWindow
end property

property wfxToolBarButtonsCollection.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

function wfxToolBarButtonsCollection.Count() as Long
   function = _Collection.Size
end function

function wfxToolBarButtonsCollection.Add() as long
   dim pData as wfxToolBarButton ptr = new wfxToolBarButton
   pData->hWindow = this.hWindow
   pData->Index = (this.Count - 1) + 1
   _Collection.Add( ControlType.ToolBarButton, pData ) 
   return pData->Index
end function

function wfxToolBarButtonsCollection.ByIndex( byval nIndex as long ) byref as wfxToolBarButton 
   dim pButton as wfxToolBarButton ptr
   dim pNode as wfxLListNode ptr
   pNode = _Collection.get_index(nIndex)
   if pNode then 
      pButton = cast(wfxToolBarButton ptr, pNode->pData)
      return *pButton
   end if   
end function

function wfxToolBarButtonsCollection.Clear() as long
   _Collection.Clear
   function = 0
END FUNCTION




