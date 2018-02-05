''
''  Control Class
''
''  https://msdn.microsoft.com/en-us/library/system.windows.forms.control(v=vs.110).aspx
''

constructor wfxControl()
end constructor

destructor wfxControl()
   ' Destroy the background brush
   DeleteObject(_hBackBrush)
end destructor

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

property wfxControl.hBackBrush() as HBRUSH
   property = _hBackBrush
end property

property wfxControl.Background() as COLORREF
   property = _Background
end property

property wfxControl.Background( byval nValue as COLORREF )
   ' Create new back brush of the color has changed
   if nValue <> _Background THEN
      DeleteObject(_hBackBrush)
      _hBackBrush = CreateSolidBrush(nValue)
   END IF
   _Background = nValue
   if this.hWindow THEN AfxRedrawWindow(this.hWindow)
end property

property wfxControl.Foreground() as COLORREF
   property = _Foreground
end property

property wfxControl.Foreground( byval nValue as COLORREF )
   _Foreground = nValue
   if this.hWindow THEN AfxRedrawWindow(this.hWindow)
   ' You can not change the Foreground color of the following controls:
   ' - Button
   ' - CheckBox
   ' - RadioButton
end property

property wfxControl.Selected() as Boolean
   if this.hWindow then 
      _Selected = iif( GetFocus() = this.hWindow, true, false)
   end if
   property = _Selected 
end property

property wfxControl.Selected( byval nValue as Boolean )
   if this.hWindow then 
      if nValue then SetFocus(this.hWindow)
   end if
   _Selected = nValue
end property

property wfxControl.IsTracking() as Boolean
   property = _bIsTracking
end property

property wfxControl.IsTracking( byval nValue as Boolean )
   _bIsTracking = nValue
end property

property wfxControl.Enabled() as Boolean
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
      _Enabled = IsWindowVisible(this.hWindow)
   end if
   property = _Enabled 
end property

property wfxControl.Visible( byval nValue as Boolean )
   if this.hWindow then 
      ShowWindow(this.hWindow, IIF(nValue, SW_SHOW, SW_HIDE))
   end if
   _Enabled = nValue
end property

property wfxControl.Left() as LONG
   if this.hWindow then 
      dim as long nLeft, nTop
      AfxGetWindowLocation(this.hWindow, @nLeft, @nTop)
      _Position.x = nLeft
   end if
   property = _Position.x
end property

property wfxControl.Left( byval nValue as long )
   if this.hWindow then 
      SetWindowPos(this.hWindow, 0, nValue, this.Top, 0, 0, SWP_NOZORDER or SWP_NOSIZE)
   end if
   _Position.x = nValue
end property

property wfxControl.Top() as LONG
   if this.hWindow then 
      dim as long nLeft, nTop
      AfxGetWindowLocation(this.hWindow, @nLeft, @nTop)
      _Position.y = nTop
   end if
   property = _Position.y
end property

property wfxControl.Top( byval nValue as long )
   if this.hWindow then 
      SetWindowPos(this.hWindow, 0, this.Left, nValue, 0, 0, SWP_NOZORDER or SWP_NOSIZE)
   end if
   _Position.y = nValue
end property

property wfxControl.Width() as LONG
   if this.hWindow then 
      _Size.Width = AfxGetWindowWidth(this.hWindow)
   end if
   property = _Size.Width
end property

property wfxControl.Width( byval nValue as long )
   if this.hWindow then 
      SetWindowPos(this.hWindow, 0, 0, 0, nValue, this.Height, SWP_NOZORDER or SWP_NOMOVE)
   end if
   _Size.Width = nValue
end property

property wfxControl.Height() as LONG
   if this.hWindow then 
      _Size.Height = AfxGetWindowHeight(this.hWindow)
   end if
   property = _Size.Height
end property

property wfxControl.Height( byval nValue as long )
   if this.hWindow then 
      SetWindowPos(this.hWindow, 0, 0, 0, this.Width, nValue, SWP_NOZORDER or SWP_NOMOVE)
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
      SetWindowPos(this.hWindow, 0, 0, 0, nWidth, nHeight, SWP_NOZORDER or SWP_NOMOVE)
   end if
   _Size.Width = nWidth
   _Size.Height = nHeight
end property

property wfxControl.Position() as wfxPoint
   if this.hWindow then 
      _Position.x = this.Left
      _Position.y = this.Top
   end if
   property = _Position
end property

property wfxControl.Position( byval xPos as long, byval yPos as long ) 
   if this.hWindow then 
      SetWindowPos(this.hWindow, 0, xPos, yPos, 0, 0, SWP_NOZORDER or SWP_NOSIZE)
   end if
   _Position.x = xPos
   _Position.y = yPos
end property

function wfxControl.SetBounds( byval xPos as long, byval yPos as long, byval nWidth as long, byval nHeight as long ) as long
   if this.hWindow then 
      SetWindowPos(this.hWindow, 0, xPos, yPos, nWidth, nHeight, SWP_NOZORDER)
   end if
   _Position.x  = xPos
   _Position.y  = yPos
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
   end if   
   _Text = nValue
end property

property wfxControl.Parent() as wfxForm ptr
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

function wfxControl.Refresh() as Long
   AfxRedrawWindow(this.hWindow)
   function = 0
END FUNCTION

function wfxControl.Hide() as Long
   ShowWindow(this.hWindow, SW_HIDE)
   function = 0
END FUNCTION






