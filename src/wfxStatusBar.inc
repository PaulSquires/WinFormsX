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


#include once "wfxStatusBar.bi"

''
''  wfxStatusBar Class
''
''  https://msdn.microsoft.com/en-us/library/system.windows.forms.statusbar(v=vs.110).aspx
''

''  STATUSBAR

constructor wfxStatusBar
   this.CtrlType = ControlType.StatusBar
   this.Name = "StatusBar"
end constructor

destructor wfxStatusBar
   '
END DESTRUCTOR

function wfxStatusBar.Panel( ByVal nIndex As long ) byref As wfxStatusBarPanel
   return this.Panels.ByIndex(nIndex)
END function

function wfxStatusBar.Panels byref As wfxStatusBarPanelsCollection
   return this._PanelsCollection
END function

property wfxStatusBar.SizingGrip() as boolean
   property = _SizingGrip
end property

property wfxStatusBar.SizingGrip( byval nValue as boolean )
   _SizingGrip = nValue
end property

property wfxStatusBar.ClickIndex() as long
   property = _ClickIndex
end property

property wfxStatusBar.ClickIndex( byVal nValue as long)
   _ClickIndex = nValue
end property

function wfxStatusBar.Show(byval hWndParent as hwnd = 0) as long

   ' If the control is created but simply hidden, then show it.
   if this.hWindow THEN
      ShowWindow(this.hWindow, SW_SHOW)
      exit function
   END IF

   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function
      
   dim as long dwExStyle = 0
   dim as long dwStyle = WS_CLIPCHILDREN OR WS_CLIPSIBLINGS OR CCS_BOTTOM 

   if this.SizingGrip THEN dwStyle = dwStyle OR SBARS_SIZEGRIP
   if this.Visible THEN dwStyle = dwStyle OR WS_VISIBLE
   
   _CtrlID = this.Parent->GetNextCtrlID()


   this.hWindow = _
         this.Parent->pWindow->AddControl ( _
         "STATUSBAR", _                    ' Class name
         hWndParent, _                     ' Parent window handle
         _CtrlID, _                        ' Control identifier 
         this.Text, _                      ' Control caption
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

   ' Apply properties that require a valid window handle
   this.Font = _wfxFontPtr
   
   ' Update the hWindow in the form's linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   dim pNode as wfxLListNode ptr = this.Parent->Controls.search_data(@this)
   if pNode then pNode->hWindow = this.hWindow

   ' Make sure the Panels collection also knows the window handle of the parent statusbar
   this.Panels.hWindow = this.hWindow

   function = 0
END FUNCTION


''  STATUSBARPANEL
property wfxStatusBarPanel.hWindow() as hwnd
   property = _hWindow
end property

property wfxStatusBarPanel.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

property wfxStatusBarPanel.Index() as long
   property = _Index
end property

property wfxStatusBarPanel.Index( byVal nValue as long)
   _Index = nValue
end property

property wfxStatusBarPanel.Alignment() as StatusBarPanelAlignment
   property = _Alignment
end property

property wfxStatusBarPanel.Alignment( byval nValue as StatusBarPanelAlignment)
   _Alignment = nValue
end property

property wfxStatusBarPanel.AutoSize() as StatusBarPanelAutoSize
   property = _AutoSize
end property

property wfxStatusBarPanel.AutoSize( byval nValue as StatusBarPanelAutoSize)
   _AutoSize = nValue
end property

' BorderStyle is deprecated as of v2.0.4 as it has no effect
' in WinFBE programs where Windows Themes are enabled.
'property wfxStatusBarPanel.BorderStyle() as StatusBarPanelBorderStyle
'   property = _BorderStyle
'end property
'
'property wfxStatusBarPanel.BorderStyle( byval nValue as StatusBarPanelBorderStyle)
'   _BorderStyle = nValue
'end property

property wfxStatusBarPanel.Text() as CWSTR
   if this.hWindow then
      ' StatusBar text is now ownerdraw so retrieve directly from Panel class.
   end if   
   property = _Text
end property

property wfxStatusBarPanel.Text( byref wszValue as wstring )
   _Text = wszValue
   if this.hWindow then this.Refresh
end property

property wfxStatusBarPanel.ToolTip() as CWSTR
   property = _ToolTip
end property

property wfxStatusBarPanel.ToolTip( byref wszValue as wstring )
   _ToolTip = wszValue
end property

property wfxStatusBarPanel.Width() as long
   property = _Width
end property

property wfxStatusBarPanel.Width( byVal nValue as long)
   _Width = nValue
end property

property wfxStatusBarPanel.MinWidth() as long
   property = _MinWidth
end property

property wfxStatusBarPanel.MinWidth( byVal nValue as long)
   _MinWidth = nValue
end property

property wfxStatusBarPanel.Icon() as CWSTR
   property = _Icon
end property

property wfxStatusBarPanel.Icon( byref cwzValue as wstring )
   _Icon = cwzValue
end property

property wfxStatusBarPanel.IsHot() as boolean
   property = _IsHot
end property

property wfxStatusBarPanel.IsHot( byval nValue as boolean )
   ' If the IsHot state has changed then refresh the control
   if nValue <> _IsHot then 
      _IsHot = nValue
      ' Only redraw if the back/fore colors differ between
      ' the two states in order to reduce flicker.
      if (_BackColor <> _BackColorHot) or _
         (_ForeColor <> _ForeColorHot) then
         ' Only redraw the Panel rather than the whole control
         ' in order to avoid flicker.
         this.Refresh
      end if
   end if
end property

function wfxStatusBarPanel.Refresh() as Long
   dim as RECT rcPanel
   StatusBar_GetRect( this.hWindow, this.Index, @rcPanel )
   InvalidateRect(this.hWindow, @rcPanel, CTRUE)
   UpdateWindow(this.hWindow)
   function = 0
end function

property wfxStatusBarPanel.BackColor() as COLORREF
   property = _BackColor
end property

property wfxStatusBarPanel.BackColor( byval nValue as COLORREF )
   if nValue <> _BackColor then
      _BackColor = nValue
      this.Refresh
   end if
end property

property wfxStatusBarPanel.BackColorHot() as COLORREF
   property = _BackColorHot
end property

property wfxStatusBarPanel.BackColorHot( byval nValue as COLORREF )
   if nValue <> _BackColorHot then
      _BackColorHot = nValue
      this.Refresh
   end if
end property

property wfxStatusBarPanel.ForeColor() as COLORREF
   property = _ForeColor
end property

property wfxStatusBarPanel.ForeColor( byval nValue as COLORREF )
   if nValue <> _ForeColor then
      _ForeColor = nValue
      this.Refresh
   end if
end property

property wfxStatusBarPanel.ForeColorHot() as COLORREF
   property = _ForeColorHot
end property

property wfxStatusBarPanel.ForeColorHot( byval nValue as COLORREF )
   if nValue <> _ForeColorHot then
      _ForeColorHot = nValue
      this.Refresh
   end if
end property


'' STATUSBARCOLLECTION
constructor wfxStatusBarPanelsCollection
   '
END CONSTRUCTOR

destructor wfxStatusBarPanelsCollection
   ' Deallocate elements in the Panels collection. The pData element
   ' of the node has been NEW with a StatusBarPanel.
   dim pNode as wfxLListNode ptr = _Collection.get_first
   do until pNode = 0
      ' Unallocate the StatusBarPanel
      Delete cast(wfxStatusBarPanel ptr, pNode->pData)
      pNode = _Collection.remove(pNode)
   LOOP
end destructor

property wfxStatusBarPanelsCollection.hWindow() as hwnd
   property = _hWindow
end property

property wfxStatusBarPanelsCollection.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

function wfxStatusBarPanelsCollection.Count() as Long
   function = _Collection.Size
end function

function wfxStatusBarPanelsCollection.Add() as long
   dim pData as wfxStatusBarPanel ptr = new wfxStatusBarPanel
   pData->hWindow = this.hWindow
   pData->Index = (this.Count - 1) + 1
   _Collection.Add( ControlType.StatusBarPanel, pData ) 
   return pData->Index
end function

function wfxStatusBarPanelsCollection.ByIndex( byval nIndex as long ) byref as wfxStatusBarPanel 
   dim pPanel as wfxStatusBarPanel ptr
   dim pNode as wfxLListNode ptr
   pNode = _Collection.get_index(nIndex)
   if pNode then
      pPanel = cast(wfxStatusBarPanel ptr, pNode->pData)
      return *pPanel
   end if   
end function

function wfxStatusBarPanelsCollection.Clear() as long
   _Collection.Clear
   function = 0
END FUNCTION






