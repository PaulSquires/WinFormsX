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

#include once "wfxForm.bi"

''
''  Form Class
''
''  https://msdn.microsoft.com/en-us/library/system.windows.forms.form(v=vs.110).aspx
''

constructor wfxForm( byref wszName as wstring = "" )
   ' Create new CWindow class for this Form
   this.pWindow = New CWindow()
   this.CtrlType = ControlType.Form
   this.Width    = CW_USEDEFAULT
   this.Height   = CW_USEDEFAULT
   this.Name     = wszName
End Constructor

destructor wfxForm
   If this.pWindow Then Delete this.pWindow
End Destructor 
         
property wfxForm.WindowState() as FormWindowState
   if this.pWindow andalso this.pWindow->hWindow THEN
      if IsIconic(this.pWindow->hWindow) THEN
         property = FormWindowState.Minimized
      elseif IsZoomed(this.pWindow->hWindow) THEN  
         property = FormWindowState.Maximized
      else      
         property = FormWindowState.Normal
      END IF
   else   
      property = _WindowState
   END IF
end property

property wfxForm.WindowState( byval nValue as FormWindowState )
   if this.pWindow andalso this.pWindow->hWindow THEN
      dim nState as long 
      select case nValue 
         case FormWindowState.Minimized: nState = SW_SHOWMINIMIZED
         case FormWindowState.Maximized: nState = SW_SHOWMAXIMIZED
         case FormWindowState.Normal:    nState = SW_SHOWNORMAL
      end select      
      ShowWindow(this.pWindow->hWindow, nValue)
   else
      _WindowState = nValue
   end if   
end property

Property wfxForm.BorderStyle() As FormBorderStyle
   Dim As Long wsStyle, wsExStyle
   If this.hWindow Then 
      wsStyle = AfxGetWindowStyle(this.hWindow)
      wsExStyle = AfxGetWindowExStyle(this.hWindow)
      If (wsStyle And (Not WS_BORDER)) Then
         _BorderStyle = FormBorderStyle.None
      ElseIf (wsStyle And (WS_BORDER Or WS_THICKFRAME)) AndAlso (wsExStyle And WS_EX_TOOLWINDOW) Then
         _BorderStyle = FormBorderStyle.SizableToolWindow
      ElseIf (wsStyle And (WS_BORDER Or WS_DLGFRAME)) AndAlso (wsExStyle And WS_EX_TOOLWINDOW) Then
         _BorderStyle = FormBorderStyle.FixedToolWindow
      ElseIf (wsStyle And (WS_BORDER Or WS_THICKFRAME Or WS_DLGFRAME)) AndAlso (wsExStyle And WS_EX_WINDOWEDGE) Then
         _BorderStyle = FormBorderStyle.FixedToolWindow
      ElseIf (wsStyle And (WS_BORDER Or WS_DLGFRAME)) AndAlso (wsExStyle And (WS_EX_WINDOWEDGE Or WS_EX_CLIENTEDGE)) Then
         _BorderStyle = FormBorderStyle.Fixed3D
      ElseIf (wsStyle And (WS_BORDER Or WS_DLGFRAME)) AndAlso (wsExStyle And WS_EX_WINDOWEDGE) Then
         _BorderStyle = FormBorderStyle.FixedSingle
      ElseIf (wsStyle And (WS_BORDER Or WS_DLGFRAME)) AndAlso (wsExStyle And WS_EX_DLGMODALFRAME) Then
         _BorderStyle = FormBorderStyle.FixedDialog
      End If   
   End If
   Property = _BorderStyle
End Property

Property wfxForm.BorderStyle( ByVal nValue As FormBorderStyle )
   If this.hWindow Then 
      AfxRemoveWindowExStyle(this.hWindow, WS_EX_CLIENTEDGE)
      AfxRemoveWindowExStyle(this.hWindow, WS_EX_WINDOWEDGE)
      AfxRemoveWindowExStyle(this.hWindow, WS_EX_DLGMODALFRAME)
      AfxRemoveWindowExStyle(this.hWindow, WS_EX_TOOLWINDOW)
      AfxRemoveWindowStyle(this.hWindow, WS_BORDER)
      AfxRemoveWindowStyle(this.hWindow, WS_THICKFRAME)
      AfxRemoveWindowStyle(this.hWindow, WS_DLGFRAME)
      Dim As Long wsStyle = AfxGetWindowStyle(this.hWindow)
      Dim As Long wsExStyle = AfxGetWindowExStyle(this.hWindow)
      Select Case nValue
         Case FormBorderStyle.None
            wsStyle   = wsStyle And (Not WS_BORDER)
         Case FormBorderStyle.SizableToolWindow
            wsExStyle = wsExStyle Or WS_EX_TOOLWINDOW
            wsStyle   = wsStyle Or WS_BORDER Or WS_THICKFRAME
         Case FormBorderStyle.FixedToolWindow
            wsStyle   = wsStyle Or WS_BORDER Or WS_DLGFRAME
            wsExStyle = wsExStyle Or WS_EX_TOOLWINDOW
         Case FormBorderStyle.Sizable
            wsStyle   = wsStyle Or WS_THICKFRAME Or WS_DLGFRAME Or WS_BORDER	
            wsExStyle = wsExStyle Or WS_EX_WINDOWEDGE
         Case FormBorderStyle.Fixed3D
            wsStyle   = wsStyle Or WS_BORDER Or WS_DLGFRAME
            wsExStyle = wsExStyle Or WS_EX_WINDOWEDGE Or WS_EX_CLIENTEDGE
         Case FormBorderStyle.FixedSingle
            wsStyle   = wsStyle Or WS_BORDER Or WS_DLGFRAME
            wsExStyle = wsExStyle Or WS_EX_WINDOWEDGE
         Case FormBorderStyle.FixedDialog
            wsStyle   = wsStyle Or WS_BORDER Or WS_DLGFRAME
            wsExStyle = wsExStyle Or WS_EX_DLGMODALFRAME
      End Select     
      AfxAddWindowStyle(this.hWindow, wsStyle)
      AfxAddWindowExStyle(this.hWindow, wsExStyle)
      AfxRedrawNonClientArea(this.hWindow)
   End If
   _BorderStyle = nValue
End Property

property wfxForm.StartPosition() as FormStartPosition
   property = _StartPosition
end property

property wfxForm.StartPosition( byval nValue as FormStartPosition )
   _StartPosition = nValue
end property

property wfxForm.MinimizeBox() as boolean
   if this.pWindow andalso this.pWindow->hWindow THEN
      _MinimizeBox = (AfxGetWindowStyle(this.pWindow->hWindow) and WS_MINIMIZEBOX)
   end if
   property = _MinimizeBox
end property

property wfxForm.MinimizeBox( byval nValue as boolean )
   if this.pWindow andalso this.pWindow->hWindow THEN
      If nValue Then
         AfxAddWindowStyle(this.hWindow, WS_MINIMIZEBOX)
      Else
         AfxRemoveWindowStyle(this.hWindow, WS_MINIMIZEBOX)
      End If   
   End If
   _MinimizeBox = nValue
end property

property wfxForm.MaximizeBox() as boolean
   if this.pWindow andalso this.pWindow->hWindow THEN
      _MaximizeBox = (AfxGetWindowStyle(this.pWindow->hWindow) and WS_MAXIMIZEBOX)
   end if   
   property = _MaximizeBox
end property

property wfxForm.MaximizeBox( byval nValue as boolean )
   if this.pWindow andalso this.pWindow->hWindow THEN
      If nValue Then
         AfxAddWindowStyle(this.hWindow, WS_MAXIMIZEBOX)
      Else
         AfxRemoveWindowStyle(this.hWindow, WS_MAXIMIZEBOX)
      End If   
   End If
   _MaximizeBox = nValue
end property

property wfxForm.ControlBox() as boolean
   if this.pWindow andalso this.pWindow->hWindow THEN
      _ControlBox = (AfxGetWindowStyle(this.pWindow->hWindow) and WS_SYSMENU)
   end if   
   property = _ControlBox
end property

property wfxForm.ControlBox( byval nValue as boolean )
   if this.pWindow andalso this.pWindow->hWindow THEN
      If nValue Then
         AfxAddWindowStyle(this.hWindow, WS_SYSMENU)
      Else
         AfxRemoveWindowStyle(this.hWindow, WS_SYSMENU)
      End If   
   End If
   _ControlBox = nValue
end property

property wfxForm.IsMainForm() as boolean
   property = _IsMainForm
end property

property wfxForm.IsMainForm( byval nValue as boolean )
   _IsMainForm = nValue
end property

property wfxForm.IsModal() as boolean
   property = _IsModal
end property

property wfxForm.IsModal( byval nValue as boolean )
   _IsModal = nValue
end property

Property wfxForm.KeyPreview() As boolean
   Property = _KeyPreview
End Property

Property wfxForm.KeyPreview( ByVal nValue As boolean )
   _KeyPreview = nValue
End Property

'property wfxForm.ShowInTaskBar() as boolean
'   if this.pWindow->hWindow THEN
'      _ShowInTaskBar = (AfxGetWindowExStyle(this.pWindow->hWindow) And WS_EX_APPWINDOW)
'   End If
'   Property = _ShowInTaskBar
'end property
'
'property wfxForm.ShowInTaskBar( byval nValue as boolean )
'   if this.pWindow->hWindow THEN
'      If nValue Then
'         AfxRemoveWindowExStyle(this.hWindow, WS_EX_TOOLWINDOW)
'         AfxAddWindowExStyle(this.hWindow, WS_EX_APPWINDOW)
'      Else
'         AfxRemoveWindowExStyle(this.hWindow, WS_EX_APPWINDOW)
'         AfxAddWindowExStyle(this.hWindow, WS_EX_TOOLWINDOW)
'      End If   
'   End If
'   _ShowInTaskBar = nValue
'end property

property wfxForm.MaximumHeight() as long
   property = _MaximumHeight
end property

property wfxForm.MaximumHeight( byval nValue as long )
   _MaximumHeight = nValue
end property

property wfxForm.MaximumWidth() as long
   property = _MaximumWidth
end property

property wfxForm.MaximumWidth( byval nValue as long )
   _MaximumWidth = nValue
end property

property wfxForm.MinimumHeight() as long
   property = _MinimumHeight
end property

property wfxForm.MinimumHeight( byval nValue as long )
   _MinimumHeight = nValue
end property

property wfxForm.MinimumWidth() as long
   property = _MinimumWidth
end property

property wfxForm.MinimumWidth( byval nValue as long )
   _MinimumWidth = nValue
end property

Property wfxForm.AcceptButton() As wfxButton ptr
   property = _AcceptButton
END PROPERTY

Property wfxForm.AcceptButton( byval nValue as wfxButton ptr )
   _AcceptButton = nValue
END PROPERTY

Property wfxForm.CancelButton() As wfxButton ptr
   property = _CancelButton
END PROPERTY

Property wfxForm.CancelButton( byval nValue as wfxButton ptr )
   _CancelButton = nValue
END PROPERTY

'Property wfxForm.MainMenu() As wfxMainMenu 
'   if _wfxMainMenuPtr = 0 then exit property
'   property = *(_wfxMainMenuPtr)
'END PROPERTY

'Property wfxForm.MainMenu( byval nValue as wfxMainMenu ptr )
'   _wfxMainMenuPtr = nValue
'END PROPERTY

property wfxForm.Icon() as CWSTR
   property = _Icon
end property

property wfxForm.Icon( byref cwzValue as wstring )
   if this.pWindow andalso this.pWindow->hWindow THEN
      If len(cwzValue) Then
         dim as HANDLE hIcon
         dim as LRESULT ret
         ' Attempt to use an Icon resource first and if that fails then attempt
         ' to load an RCDATA resource.
         hIcon = LoadImage( this.pWindow->InstanceHandle, cwzValue, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE ) 
         if hIcon = 0 then
            hIcon = AfxGdipIconFromRes( this.pWindow->InstanceHandle, cwzValue )
         end if
         ' Ensure that we destroy the old icon before setting the new icon. The WM_SETICON message
         ' returns the handle to the previously set icon.
         ret = SendMessage( this.hWindow, WM_SETICON, CAST(WPARAM, ICON_BIG), CAST(LPARAM, hIcon)) 
         DestroyIcon( cast(HANDLE, ret) )
         ret = SendMessage( this.hWindow, WM_SETICON, CAST(WPARAM, ICON_SMALL), CAST(LPARAM, hIcon))
         DestroyIcon( cast(HANDLE, ret) )
      End If   
   End If
   AfxRedrawNonClientArea(this.hWindow)
   _Icon = cwzValue
end property


property wfxForm.ClientSize() as wfxSize
   if this.pWindow andalso this.pWindow->hWindow THEN
      _ClientSize.Width = this.pWindow->ClientWidth
      _ClientSize.Height = this.pWindow->ClientHeight
   End If   
   property = _ClientSize
end property

property wfxForm.ClientSize( byval nWidth as long, byval nHeight as long ) 
   if this.pWindow andalso this.pWindow->hWindow THEN
      this.pWindow->SetClientSize( nWidth, nHeight )
   else
      _ClientSize.Width = nWidth
      _ClientSize.Height = nHeight
   end if   
end property


function wfxForm.ScaleX( byval nValue as long ) as Long
   if this.pWindow THEN
      nValue = this.pWindow->ScaleX(nValue)
   end if
   return nValue
end function       

function wfxForm.ScaleY( byval nValue as long ) as Long
   if this.pWindow THEN
      nValue = this.pWindow->ScaleY(nValue)
   end if
   return nValue
end function       

function wfxForm.UnScaleX( byval nValue as long ) as Long
   if this.pWindow THEN
      nValue = this.pWindow->UnScaleX(nValue)
   end if
   return nValue
end function       

function wfxForm.UnScaleY( byval nValue as long ) as Long
   if this.pWindow THEN
      nValue = this.pWindow->UnScaleY(nValue)
   end if
   return nValue
end function       


function wfxForm.GetNextCtrlID() as Long     
   ' This function is internal to the class.
   ' Return the next available control id. Used when creating controls.
   _NextCtrlID = _NextCtrlID + 1
   function = _NextCtrlID 
End Function

function wfxForm.Close() as Long
   ' Call WM_CLOSE for the form. This allows the user to respond to
   ' OnFormClosing and re-enable parent form in IsModal situations.
   SendMessage(this.hWindow, WM_CLOSE, 0, 0)
   function = 0
end function

''
''
function wfxForm.CalculateStartPosition( BYVAL rc as RECT, BYVAL hwndParent AS HWND = NULL ) as POINT

   ' Incoming rc AS RECT        ' Form coordinates
   DIM rcParent      AS RECT    ' Parent window coordinates
   DIM rcWorkArea    AS RECT    ' Work area coordinates
   DIM pt            AS POINT   ' x and y coordinates of centered window

   ' Calculate the width and height of the Form (need to scale these coordinates)
   DIM nWidth AS LONG = this.ScaleX( rc.Right - rc.Left )
   DIM nHeight AS LONG = this.ScaleY( rc.Bottom - rc.Top )

   ' Get the coordinates of the work area
   IF SystemParametersInfoW(SPI_GETWORKAREA, SIZEOF(rcWorkArea), @rcWorkArea, 0) = 0 THEN
      rcWorkArea.Right  = GetSystemMetrics(SM_CXSCREEN)
      rcWorkArea.Bottom = GetSystemMetrics(SM_CYSCREEN)
   END IF
   
   ' Get the coordinates of the parent window
   IF hwndParent THEN
      GetWindowRect( hwndParent, @rcParent )
   ELSE
      rcParent.Left   = rcWorkArea.Left
      rcParent.Top    = rcWorkArea.Top
      rcParent.Right  = rcWorkArea.Right
      rcParent.Bottom = rcWorkArea.Bottom
   END IF
   
   ' Calculate the width and height of the parent window
   DIM nParentWidth AS LONG = rcParent.Right - rcParent.Left
   DIM nParentHeight AS LONG = rcParent.Bottom - rcParent.Top
   
   ' Calculate the new x coordinate and adjust for work area
   pt.x = rcParent.Left + ((nParentWidth - nWidth) \ 2)
   IF (pt.x < rcWorkArea.Left) THEN
      pt.x = rcWorkArea.Left
   ELSEIF ((pt.x + nWidth) > rcWorkArea.Right) THEN
      pt.x = rcWorkArea.Right - nWidth
   END IF
   
   ' Calculate the new y coordinate and adjust for work area
   pt.y = rcParent.Top  + ((nParentHeight - nHeight) \ 2)
   IF (pt.y < rcWorkArea.Top) THEN
      pt.y = rcWorkArea.Top
   ELSEIF ((pt.y + nHeight) > rcWorkArea.Bottom) THEN
      pt.y = rcWorkArea.Bottom - nHeight
   END IF
   
   ' Need to unscale the result position point because pWindow->Create will scale it.
   pt.x = this.UnScaleX( pt.x )
   pt.y = this.UnScaleY( pt.y )
   
   function = pt
END function


''    
''  ToolBar resize procedure
''
Function wfxForm.SizeToolBar() As Long

   Dim pNode    As wfxLListNode Ptr
   dim pToolBar as wfxToolBar ptr
            
   ' If a ToolBar exists on this form then resize it.
   pNode = this.Controls.search_controltype(ControlType.ToolBar)
   if pNode = 0 then exit function
   
   pToolBar = cast(wfxToolBar ptr, pNode->pData)
   if pToolBar = 0 then exit function
   
   if this.pWindow = 0 then exit function
   
   if pToolBar->hRebar then
      dim rc as RECT 
      GetClientRect( this.hWindow, @rc )
      dim as long cx, cy
      cx = rc.left - rc.right
      cy = AfxGetWindowHeight( pToolBar->hRebar )
      SendMessage pToolBar->hRebar, WM_SIZE, cx, cy
   end if
   
   function = 0   
end function


''    
''  StatusBar resize procedure
''
Function wfxForm.SizeStatusBar() As Long

   Dim pNode      As wfxLListNode Ptr
   dim pStatusBar as wfxStatusBar ptr
            
   ' If a StatusBar exists on this form then resize it.
   pNode = this.Controls.search_controltype(ControlType.StatusBar)
   if pNode = 0 then exit function
   
   pStatusBar = cast(wfxStatusBar ptr, pNode->pData)
   if pStatusBar = 0 then exit function
   
   if this.pWindow = 0 then exit function
   
   dim rc as RECT 
   GetClientRect( this.hWindow, @rc )
   
   dim as long nHeight = AfxGetWindowHeight( pStatusBar->hWindow )
   SetWindowPos( pStatusBar->hWindow, 0, _
                  0, rc.bottom - nHeight, rc.right, nHeight, _
                  SWP_NOZORDER )

   dim as single cx = this.pWindow->rxRatio
   
   ' Calculate and set the widths of the panels.
   if pStatusBar->Panels.Count then
      dim as long nWidths( 0 to pStatusBar->Panels.Count - 1 )
      for i as long = 0 to pStatusBar->Panels.Count - 1
         dim as long nPanelWidth    = pStatusBar->Panel(i).Width * cx
         dim as long nPanelMinWidth = pStatusBar->Panel(i).MinWidth * cx
         
         if pStatusBar->Panel(i).AutoSize = StatusBarPanelAutoSize.Spring then  
            nPanelWidth = iif(i, rc.right - nWidths(i-1), rc.right)
         elseif pStatusBar->Panel(i).AutoSize = StatusBarPanelAutoSize.Contents then  
            dim as HDC _hdc = GetDC(pStatusBar->hWindow)
            dim as SIZE _size 
            dim as HFONT oldfont = SelectObject( _hdc, this.pWindow->Font )
            dim as WString * MAX_PATH wszBuffer = " " & pStatusBar->Panel(i).Text & " "
            GetTextExtentPoint32( _hdc, wszBuffer, len(wszBuffer), @_size)
            SelectObject( _hdc, oldfont )
            ReleaseDC( pStatusBar->hWindow, _hdc )
            nPanelWidth = _size.cx
            if nPanelWidth < nPanelMinWidth then nPanelWidth = nPanelMinWidth
         elseif pStatusBar->Panel(i).AutoSize = StatusBarPanelAutoSize.None then  
            if nPanelWidth < nPanelMinWidth then nPanelWidth = nPanelMinWidth
         end if
         nWidths(i) = iif(i, nWidths(i-1), 0) + nPanelWidth
    NEXT
      StatusBar_SetParts( pStatusBar->hWindow, pStatusBar->Panels.Count, @nWidths(0))
   end if

   ' Set the text/icons for the panels. Need to do this after the widths are set.
   for i as long = 0 to pStatusBar->Panels.Count - 1
      dim as CWSTR wszPanelText = pStatusBar->Panel(i).Text
      select case pStatusBar->Panel(i).Alignment
         case StatusBarPanelAlignment.Left:   ' do nothing
         case StatusBarPanelAlignment.Center: wszPanelText = chr(9) & wszPanelText
         case StatusBarPanelAlignment.Right:  wszPanelText = chr(9,9) & wszPanelText
      end select
      pStatusBar->Panel(i).hWindow = pStatusBar->hWindow
      StatusBar_SetText( pStatusBar->hWindow, i, wszPanelText, pStatusBar->Panel(i).BorderStyle ) 

      dim as CWSTR wszToolTip = pStatusBar->Panel(i).ToolTip
      if len( wszToolTip ) then
         StatusBar_SetTipText( pStatusBar->hWindow, i, wszToolTip )
      end if
   
      dim wszImageName as wstring * MAX_PATH
      wszImageName = pStatusBar->Panel(i).Icon
   
      if len(wszImageName) then
         dim as HANDLE hIcon
         ' Attempt to use an Icon resource first and if that fails then attempt
         ' to load an RCDATA resource.
         hIcon = LoadImage( this.pWindow->InstanceHandle, wszImageName, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE ) 
         if hIcon = 0 then
            hIcon = AfxGdipIconFromRes( this.pWindow->InstanceHandle, wszImageName)
         end if
         ' If no hIcon defined then any previous icon will be removed
         DestroyIcon( StatusBar_GetIcon( pStatusBar->hWindow, i ) )
         StatusBar_SetIcon( pStatusBar->hWindow, i, hIcon ) 
      End If   
   next

   function = 0 
End Function
                  

''
''
function wfxForm.CreateFormInternal( byval hWndParent as hwnd, byval IsFormModal as boolean ) as long   
   ' Internal function. Do not call from code.
   ' Get Window creation values before the hWindow actually exists

   ' If the form is created but simply hidden, then show it.
   If this.hWindow Then
      ShowWindow(this.hWindow, SW_SHOW)
      exit function
   END IF

   dim e as wfxEventArgs 

   ' If this form is being shown modal then save the current control focus 
   ' so that it can be restored when the modal form closes.
   Dim As HWnd hWndParentFocus 
   If IsFormModal Then hWndParentFocus = GetFocus()

   this.hWindowParent = hWndParent
   If this.pWindow = 0 Then this.pWindow = New CWindow()
   
   ' Allow the user to set/initialize properties of the form and controls prior
   ' to it be created. This essentially builds on the Form's constructor code generation.
   If this.OnInitialize Then 
      this.OnInitialize(this, *(@e))
      if e.Cancel = true then
         this.Close: exit function
      end if
   end if

   Dim pCtrl As wfxControl Ptr
   dim pCtrlFocus as wfxControl ptr
   
   dim as long nLeft   = this.Left
   dim as long nTop    = this.Top
   dim as long nWidth  = this.Width
   dim as long nHeight = this.Height
   
   dim as RECT rc: SetRect( @rc, nLeft, nTop, nLeft + nWidth, nTop + nHeight)
   dim as POINT pt = (nLeft, nTop)
   
   Dim As Long dwStyle = WS_CLIPCHILDREN Or WS_CLIPSIBLINGS 
   dim as long dwExStyle = WS_EX_CONTROLPARENT
   
   if this.IsMainForm THEN dwStyle = dwStyle or WS_POPUP 
   If IsFormModal Then dwStyle = dwStyle Or WS_POPUP
   this.IsModal = IsFormModal
      
   if this.StartPosition = FormStartPosition.WindowsDefaultLocation then
      nLeft = CW_USEDEFAULT: nTop = CW_USEDEFAULT
   end if

   select case this.WindowState
      case FormWindowState.Maximized: dwStyle = dwStyle or WS_MAXIMIZE
      case FormWindowState.Minimized: dwStyle = dwStyle or WS_MINIMIZE
      case FormWindowState.Normal     ' no style needed
   end select  
    
   if this.MinimizeBox then dwStyle = dwStyle or WS_MINIMIZEBOX or WS_CAPTION 
   if this.MaximizeBox then dwStyle = dwStyle or WS_MAXIMIZEBOX or WS_CAPTION
   if this.ControlBox  THEN dwStyle = dwStyle or WS_SYSMENU or WS_CAPTION
       
   select case this.BorderStyle 
      case FormBorderStyle.None
         dwStyle   = dwStyle and (not WS_BORDER)
      case FormBorderStyle.SizableToolWindow
         dwExStyle = dwExStyle or WS_EX_TOOLWINDOW
         dwStyle   = dwStyle or WS_BORDER or WS_THICKFRAME
      case FormBorderStyle.FixedToolWindow
         dwStyle   = dwStyle or WS_BORDER or WS_DLGFRAME
         dwExStyle = dwExStyle or WS_EX_TOOLWINDOW
      case FormBorderStyle.Sizable
         dwStyle   = dwStyle or WS_THICKFRAME or WS_DLGFRAME or WS_BORDER	
         dwExStyle = dwExStyle or WS_EX_WINDOWEDGE
      case FormBorderStyle.Fixed3D
         dwStyle   = dwStyle or WS_BORDER or WS_DLGFRAME
         dwExStyle = dwExStyle or WS_EX_WINDOWEDGE or WS_EX_CLIENTEDGE
      case FormBorderStyle.FixedSingle
         dwStyle   = dwStyle or WS_BORDER or WS_DLGFRAME
         dwExStyle = dwExStyle or WS_EX_WINDOWEDGE
      Case FormBorderStyle.FixedDialog
         dwStyle   = dwStyle or WS_BORDER or WS_DLGFRAME
         dwExStyle = dwExStyle or WS_EX_DLGMODALFRAME
   end select     

'   If this.ShowInTaskBar Then
'      dwExStyle = dwExStyle Or WS_EX_APPWINDOW
'   End If
   
   ' Calculate the correct size and position of the form that we are about
   ' to create. We do this because otherwise we would have to display the
   ' form and move it resulting in unsighlty visual movement to the user.
   select CASE this.StartPosition
      CASE FormStartPosition.CenterParent
         pt = this.CalculateStartPosition( rc, hWndParent )
      CASE FormStartPosition.CenterScreen
         pt = this.CalculateStartPosition( rc, 0 )
   END SELECT
   
   '  Create the main window based on properties set
   this.hWindow = this.pWindow->Create( hWndParent, _
                        this.Text, _
                        @wfxApplication.WndProc, _
                        pt.x, pt.y, nWidth, nHeight, _
                        dwStyle, dwExStyle ) 

   ' Set the Form icons. hWindow must be valid.
   this.Icon = _Icon
 
   ' Should we enable drag and drop files
   if this.AllowDrop then DragAcceptFiles(this.hWindow, CTRUE)

   ' Store the hWindow in the application linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   dim pNode as wfxLListNode ptr
   pNode = Application.Forms.search_data(@this)
   if pNode then pNode->hWindow = this.hWindow
   
   ' Create and show all of the child controls. Also track what control is being
   ' set as initially selected/focus
   pNode = this.Controls.get_first
   do until pNode = 0
      pCtrl = cast(wfxControl ptr, pNode->pData)
      If pCtrl Then
         pCtrl->Show(this.hWindow)
         If pCtrl->TabStop Then
            ' By default, set the first control to have keyboard focus. If a focus 
            ' is specifically set in a later control then the pCtrl->Focused property
            ' will catch that. Last control because controls created in reverse order.
            If pCtrlFocus = 0 Then pCtrlFocus = pCtrl
         End If
      End If
      pNode = this.Controls.get_next(pNode)
   LOOP

   ' Setting the ClientSize property will override the width/height of the form
   if this.ClientSize.IsEmpty = false THEN
      this.pWindow->SetClientSize( this.ClientSize.Width, this.ClientSize.Height )
   END IF


   ' Ensure that window gets correctly placed into the taskbar (if applicable) by
   ' calling ShowWindow with SW_SHOWDEFAULT initially specified.
   if this.IsMainForm then
      ShowWindow(this.hWindow, SW_SHOWDEFAULT)
   end if
    
   
   ' Form has been created but not yet shown. Fire the Load event now if 
   ' it has been defined. Need to do it here rather than in WM_CREATE because
   ' the Window handle is only assigned to the form object AFTER the WM_CREATE 
   ' finishes.
   If this.OnLoad Then 
      this.OnLoad(this, *(@e))
      if e.Cancel = true then
         this.Close: exit function
      end if
   end if
   If this.OnResize Then this.OnResize(this, *(@e))
   

   ShowWindow(this.hWindow, Iif(_Visible, SW_SHOW, SW_HIDE))
   AfxRedrawWindow(this.hWindow)
   
   ' The Shown event is only raised the first time a form is displayed; 
   ' subsequently minimizing, maximizing, restoring, hiding, showing, or 
   ' invalidating and repainting will not raise this event. 
   if IsWindowVisible(this.hWindow) THEN
      if this.OnShown then this.OnShown(this, *(@e))
   END IF

   
   ' Resize any defined StatusBar
   this.SizeStatusBar
   
   
   ' Check for new focus control in case it was set in the OnLoad/OnShown event.
   pNode = this.Controls.get_first
   do until pNode = 0
      pCtrl = cast(wfxControl ptr, pNode->pData)
      if pCtrl then
         If pCtrl->Focused Then pCtrlFocus = pCtrl
      End If
      pNode = this.Controls.get_next(pNode)
   LOOP

   ' Set the focus/selected control which will also cause the Activate 
   ' message for the Form to fire. 
   If pCtrlFocus Then 
      If pCtrlFocus->CtrlType = ControlType.TextBox Then
         Dim pTextBox As wfxTextBox Ptr = Cast(wfxTextBox Ptr, pCtrlFocus)
         If pTextBox->MultiLine = False Then
            pTextBox->SelectionStart = 0 
            pTextBox->SelectionLength = Len(pTextBox->Text)
         End If
      End If
      SetFocus(pCtrlFocus->hWindow)
   End If
   
   
   ' If this is a modal popup window so disable the parent window. The
   ' parent window will be re-enabled when this form is closed.
   If this.IsModal Then 
      if hWndParent then EnableWindow(hWndParent, False)

      ' Message loop
      Dim As MSG uMsg 
      Do While GetMessage(@uMsg, Null, 0, 0)
         ' Processes accelerator keys for menu commands
         If (this.pWindow->AccelHandle = 0) Or _
            (TranslateAccelerator(this.hWindow, this.pWindow->AccelHandle, @uMsg)) = 0 Then
   
            ' Preprocess the message to handle keyboard input and route it to the correct event
            ' handlers. If the message was not handled then continue to process the keystroke
            ' further via IsDialogMessage and TranslateMessage.
            If Application.PreprocessMessage(this.hWindow, uMsg.HWnd, @uMsg) = False Then 
               ' Use IsDialogMessage to handle all keyboard movement related keys for the dialog. This
               ' ensures that controls are TAB'd to correctly and that the focus rectangle also
               ' changes correctly. IsDialogMessage sends WM_GETDLGCODE messages to the control to
               ' determine if it should handle the message. At this point, we have handled all incoming
               ' keyboard messages through the PreprocessMessage function so we only want to send
               ' movement keys to the IsDialogMessage function. Doing this prevents unwanted beeps
               ' when illegal characters are entered for controls.
   
               ' Loop through the form collection and test each hWindow for IsDialogMessage
               Dim As boolean bIsDialogMessage = False
               Select Case uMsg.message
                  Case WM_KEYDOWN, WM_KEYUP, WM_CHAR
                     Select Case uMsg.wParam
                        Case VK_TAB, VK_LEFT, VK_UP, VK_DOWN, VK_RIGHT, VK_PRIOR, VK_NEXT 
                           Dim pNode As wfxLListNode Ptr = Application.Forms.get_first
                           Do Until pNode = 0
                              If IsDialogMessage(pNode->hWindow, @uMsg) Then
                                 bIsDialogMessage = True: Exit Do
                              end if
                              pNode = Application.Forms.get_next(pNode)
                           Loop
                      End Select
               End Select
                
               If bIsDialogMessage = False Then 
                  TranslateMessage @uMsg    ' Translates virtual-key messages into character messages.
                  DispatchMessage  @uMsg    ' Dispatches a message to a window procedure.
               End If
            End If
         End If
         If IsWindow(this.hWindow) = 0 Then Exit Do  ' popup modal window closed
      Loop

      ' Set the focus back to the control that had focus prior to the modal window being displayed.
      if hWndParentFocus then SetFocus( hWndParentFocus )
      
   End If
   
   Function = 0

END FUNCTION

''
''  Show the Form as modeless using parent form window handle
''
function wfxForm.Show( byval hWndParent as hwnd = 0 ) as Long
   function = this.CreateFormInternal( hWndParent, false)
END FUNCTION

''
''  Show the Form as modeless using parent form object (BYREF)
''
function wfxForm.Show(byref frmParent as wfxForm) as Long
   function = this.CreateFormInternal( frmParent.hWindow, false)
end function

''
''  Show the Form as modeless using parent form object (POINTER)
''
function wfxForm.Show(byval frmParent as wfxForm ptr) as Long
   function = this.CreateFormInternal( frmParent->hWindow, false)
end function

''
''  Show the Form as modal using parent form window handle
''
function wfxForm.ShowDialog(byval hWndParent as hwnd = 0) as Long
   function = this.CreateFormInternal( hWndParent, true)
end function

''
''  Show the Form as modal using parent form object (BYREF)
''
function wfxForm.ShowDialog(byref frmParent as wfxForm) as Long
   function = this.CreateFormInternal( frmParent.hWindow, true)
end function

''
''  Show the Form as modal using parent form object (POINTER)
''
function wfxForm.ShowDialog(byval frmParent as wfxForm ptr) as Long
   function = this.CreateFormInternal( frmParent->hWindow, true)
end function

