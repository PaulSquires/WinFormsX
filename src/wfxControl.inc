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

''
''  Control Class
''
''  https://msdn.microsoft.com/en-us/library/system.windows.forms.control(v=vs.110).aspx
''

#Include Once "wfxControl.bi"

Constructor wfxControl()
end constructor

destructor wfxControl()
   ' Destroy the background brush
   DeleteObject(_hBackBrush)
   If _wfxFontPtr Then Delete _wfxFontPtr
   if IsWindow(_hWndToolTip) then DestroyWindow(_hWndToolTip)
End Destructor

property wfxControl.CtrlType() as LONG
   property = _CtrlType
end property

property wfxControl.CtrlType( byval nValue as long )
   _CtrlType = nValue
end property

property wfxControl.Name() as CWSTR
   property = _CtrlName
end property

property wfxControl.Name( byref cwzValue as wstring )
   _CtrlName = cwzValue
end property

property wfxControl.Tag() as CWSTR
   property = _Tag
end property

property wfxControl.Tag( byref cwzValue as wstring )
   _Tag = cwzValue
end property

property wfxControl.Anchor() as CWSTR
   property = _Anchor
end property

property wfxControl.Anchor( byref cwzValue as wstring )
   _Anchor = cwzValue
end property

property wfxControl.hWindowToolTip() as hwnd
   property = _hWndToolTip
end property

property wfxControl.ToolTip() as CWSTR
   property = _ToolTip
end property

property wfxControl.ToolTip( byref cwzValue as wstring )
   if this.hWindow then
      if IsWindow(_hWndToolTip) = 0 then
         _hWndToolTip = AfxAddTooltip( this.hWindow, _ToolTip, _ToolTipBalloon, false )
      else
         AfxSetTooltipText(_hWndToolTip, this.hWindow, cwzValue)
      end if
   end if
   _ToolTip = cwzValue
end property

Property wfxControl.ToolTipBalloon() As boolean
   Property = _ToolTipBalloon
End Property

Property wfxControl.ToolTipBalloon( ByVal nValue As boolean )
   ' If the ToolTip changes to a different type from/to balloon style
   ' then we will destroy the original tooltip and create a new one.
   _ToolTipBalloon = nValue
   if IsWindow(_hWndToolTip) then
      DestroyWindow(_hWndToolTip)
      _hWndToolTip = 0
      this.ToolTip = _ToolTip
   end if
End Property

property wfxControl.CtrlID() as LONG
   if this.hWindow then 
      _CtrlID = GetDlgCtrlID(this.hWindow)
   end if   
   property = _CtrlID
end property

property wfxControl.CtrlID( byval nValue as long )
   if this.hWindow then 
      SetWindowLongPtr(this.hWindow, GWLP_ID, nValue)
   end if
   _CtrlID = nValue
end property

Property wfxControl.AllowDrop() As boolean
   Property = _AllowDrop
End Property

Property wfxControl.AllowDrop( ByVal nValue As boolean )
   _AllowDrop = nValue
End Property

Property wfxControl.hBackBrush() As HBRUSH
   property = _hBackBrush
end property

property wfxControl.BackColor() as COLORREF
   property = _BackColor
end property

property wfxControl.BackColor( byval nValue as COLORREF )
   ' Create new back brush of the color has changed
   if nValue <> _BackColor THEN
      DeleteObject(_hBackBrush)
      _hBackBrush = CreateSolidBrush(nValue)
   END IF
   _BackColor = nValue
   if this.hWindow THEN AfxRedrawWindow(this.hWindow)
end property

Property wfxControl.Locked() As boolean
   Property = _Locked
End Property

Property wfxControl.Locked( ByVal nValue As boolean )
   _Locked = nValue
End Property

Property wfxControl.ForeColor() As COLORREF
   property = _ForeColor
end property

property wfxControl.ForeColor( byval nValue as COLORREF )
   _ForeColor = nValue
   if this.hWindow THEN AfxRedrawWindow(this.hWindow)
   ' You can not change the Foreground color of the following controls:
   ' (unless Windows Themes are disabled and we don't want to do that)
   ' - CheckBox
   ' - RadioButton
   ' - Frame (GroupBoxes)
end property

Property wfxControl.Font( ByVal wfxFontPtr As wfxFont Ptr )
   If (_wfxFontPtr <> 0) AndAlso (_wfxFontPtr <> wfxFontPtr) Then Delete(_wfxFontPtr)
   _wfxFontPtr = wfxFontPtr
   If this.hWindow Then 
      If _wfxFontPtr Then
         if this.CtrlType = ControlType.DateTimePicker then
            SendMessage( this.hWindow, DTM_SETMCFONT, CAST(WPARAM, _wfxFontPtr->FontHandle), CTRUE )
            AfxSetWindowFont( this.hWindow, _wfxFontPtr->FontHandle, CTRUE )
         else   
            AfxSetWindowFont( this.hWindow, _wfxFontPtr->FontHandle, CTRUE )
         end if   
      End If
   End If
End Property
    
Property wfxControl.Font() As wfxFont 
   Property = *(_wfxFontPtr)
End Property

Property wfxControl.Focused() As Boolean
   if this.hWindow then 
      _Focused = iif( GetFocus() = this.hWindow, true, false)
   end if
   property = _Focused 
end property

property wfxControl.Focused( byval nValue as Boolean )
   if this.hWindow then 
      if nValue then SetFocus(this.hWindow)
   end if
   _Focused = nValue
end property

property wfxControl.IsTracking() as Boolean
   property = _bIsTracking
end property

property wfxControl.IsTracking( byval nValue as Boolean )
   _bIsTracking = nValue
end property

property wfxControl.TabStop() as Boolean
   property = _TabStop
end property

property wfxControl.TabStop( byval nValue as Boolean )
   _TabStop = nValue
end property

Property wfxControl.Enabled() As Boolean
   if this.hWindow then 
      _Enabled = IsWindowEnabled(this.hWindow)
   end if
   property = _Enabled 
end property

property wfxControl.Enabled( byval nValue as Boolean )
   if this.hWindow then 
      EnableWindow(this.hWindow, nValue)
   end if
   _Enabled = nValue
end property

property wfxControl.Visible() as Boolean
   if this.hWindow then 
      _Visible = IsWindowVisible(this.hWindow)
   end if
   property = _Visible 
end property

property wfxControl.Visible( byval nValue as Boolean )
   if this.hWindow then 
      ShowWindow(this.hWindow, IIF(nValue, SW_SHOW, SW_HIDE))
   end if
   _Visible = nValue
end property

property wfxControl.Left() as LONG
   if this.hWindow then 
      dim as long nLeft, nTop
      AfxGetWindowLocation(this.hWindow, nLeft, nTop)
      _Location.x = this.Parent->UnScaleX(nLeft)
   end if
   property = _Location.x
end property

property wfxControl.Left( byval nValue as long )
   if this.hWindow then 
      if this.Parent->pWindow then
         this.Parent->pWindow->SetWindowPos(this.hWindow, 0, nValue, this.Top, 0, 0, SWP_NOZORDER or SWP_NOSIZE)
      end if
   end if
   _Location.x = nValue
end property

property wfxControl.Top() as LONG
   if this.hWindow then 
      dim as long nLeft, nTop
      AfxGetWindowLocation(this.hWindow, nLeft, nTop)
      _Location.y = this.Parent->UnScaleY(nTop)
   end if
   property = _Location.y
end property

property wfxControl.Top( byval nValue as long )
   if this.hWindow then 
      if this.Parent->pWindow then
         this.Parent->pWindow->SetWindowPos(this.hWindow, 0, this.Left, nValue, 0, 0, SWP_NOZORDER or SWP_NOSIZE)
      end if
   end if
   _Location.y = nValue
end property

property wfxControl.Width() as LONG
   if this.hWindow then 
      if this.Parent->pWindow then
         _Size.Width = this.Parent->pWindow->ControlWidth(this.hWindow)
      end if
   end if
   property = _Size.Width
end property

property wfxControl.Width( byval nValue as long )
   if this.hWindow then 
      if this.Parent->pWindow then
         this.Parent->pWindow->SetWindowPos(this.hWindow, 0, 0, 0, nValue, this.Height, SWP_NOZORDER or SWP_NOMOVE)
      end if
   end if
   _Size.Width = nValue
end property

property wfxControl.Height() as LONG
   if this.hWindow then 
      if this.Parent->pWindow then
         _Size.Height = this.Parent->pWindow->ControlHeight(this.hWindow)
      end if
   end if
   property = _Size.Height
end property

property wfxControl.Height( byval nValue as long )
   if this.hWindow then 
      if this.Parent->pWindow then
         this.Parent->pWindow->SetWindowPos(this.hWindow, 0, 0, 0, this.Width, nValue, SWP_NOZORDER or SWP_NOMOVE)
      end if
   end if
   _Size.Height = nValue
end property

property wfxControl.Size() as wfxSize
   if this.hWindow then 
      _Size.Width = this.Width
      _Size.Height = this.Height
   end if
   property = _Size
end property

property wfxControl.Size( byval nWidth as long, byval nHeight as long ) 
   if this.hWindow then 
      if this.Parent->pWindow then
         this.Parent->pWindow->SetWindowPos(this.hWindow, 0, 0, 0, nWidth, nHeight, SWP_NOZORDER or SWP_NOMOVE)
      end if
   end if
   _Size.Width = nWidth
   _Size.Height = nHeight
end property

property wfxControl.Location() as wfxPoint
   if this.hWindow then 
      _Location.x = this.Left
      _Location.y = this.Top
   end if
   property = _Location
end property

property wfxControl.Location( byval xPos as long, byval yPos as long ) 
   if this.hWindow then 
      if this.Parent->pWindow then
         this.Parent->pWindow->SetWindowPos(this.hWindow, 0, xPos, yPos, 0, 0, SWP_NOZORDER or SWP_NOSIZE)
      end if   
   end if
   _Location.x = xPos
   _Location.y = yPos
end property

function wfxControl.SetBounds( byval xPos as long, byval yPos as long, byval nWidth as long, byval nHeight as long ) as long
   if this.hWindow then 
      if this.Parent->pWindow then
         this.Parent->pWindow->SetWindowPos(this.hWindow, 0, xPos, yPos, nWidth, nHeight, SWP_NOZORDER)
      end if
   end if
   _Location.x  = xPos
   _Location.y  = yPos
   _Size.Width  = nWidth
   _Size.Height = nHeight
   function = 0
end function

property wfxControl.Text() as CWSTR
   if this.hWindow then 
      _Text = AfxGetWindowText(this.hWindow)
   end if   
   property = _Text
end property

property wfxControl.Text( byref nValue as wstring )
   if this.hWindow then 
      AfxSetWindowText(this.hWindow, nValue)
      AfxRedrawWindow(this.hWindow)
   End If   
   _Text = nValue
end property

property wfxControl.Parent() as wfxForm ptr
   if _Parent = 0 then _Parent = cast( wfxForm ptr, @this )
   property = _Parent
end property
 
property wfxControl.Parent( byval pForm as wfxForm ptr )
   _Parent = pForm
end property

property wfxControl.hWindow() as hwnd
   property = _hWindow
end property

property wfxControl.hWindow( byval nValue as hwnd )
   _hWindow = nValue
end property

Property wfxControl.hWindowParent() As HWnd
   if this.hWindow then 
      ' Only set if this is a child control
      If (AfxGetWindowStyle(this.hWindow) And WS_CHILD) Then
         _hWindowParent = GetParent(this.hWindow) 
      End If   
   End If
   Property = _hWindowParent
End Property

Property wfxControl.hWindowParent( ByVal nValue As HWnd )
   If this.hWindow Then 
      ' Only set if this is a child control
      If (AfxGetWindowStyle(this.hWindow) And WS_CHILD) Then
         SetParent(this.hWindow, nValue)
      End If   
   End If
   _hWindowParent = nValue
End Property

Function wfxControl.Refresh() As Long
   AfxRedrawWindow(this.hWindow)
   function = 0
END FUNCTION

function wfxControl.Hide() as Long
   ShowWindow(this.hWindow, SW_HIDE)
   function = 0
END FUNCTION

Function wfxControl.SelectNextControl( ByVal bForward As boolean ) As boolean
   ' move input fcous to the next/prev control in the tab order
   Dim As HWnd hCtrl = GetNextDlgTabItem( this.Parent->hWindow, this.hWindow, (Not bForward))

   ' If the control is a textbox then select all text to simulate a TAB press.
   dim pNode as wfxLListNode ptr
   pNode = Application.GetControlByHandle(hCtrl)
   If pNode Then 
      Dim pCtrl As wfxControl Ptr
      pCtrl = Cast(wfxControl Ptr, pNode->pData)
      If pNode->CtrlType = ControlType.TextBox Then
#ifdef CODEGEN_TEXTBOX
         Dim pTextBox As wfxTextBox Ptr
         pTextBox = Cast(wfxTextBox Ptr, pNode->pData)
         If pTextBox->MultiLine = False Then
            pTextBox->SelectionStart = 0 
            pTextBox->SelectionLength = Len(pTextBox->Text)
         End If
#endif
      End If
   End If      
   SetFocus(hCtrl)
   If hCtrl <> this.hWindow Then Return True
End Function




