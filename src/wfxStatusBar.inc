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

function wfxStatusBar.Panels overload (ByVal nIndex As long ) byref As wfxStatusBarPanel
   return this.Panels.ByIndex(nIndex)
END function

function wfxStatusBar.Panels overload(byval st as string = "") byref As wfxStatusBarPanelsCollection
   return this._PanelsCollection
END function

property wfxStatusBar.hWindow() as hwnd
   property = _hWindow
end property

property wfxStatusBar.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

property wfxStatusBar.SizingGrip() as boolean
   property = _SizingGrip
end property

property wfxStatusBar.SizingGrip( byval nValue as boolean )
   if this.hWindow then 
      ' Add and/or Remove the sizing grip
      AfxRemoveWindowStyle(this.hWindow, SBARS_SIZEGRIP)
      if nValue then AfxAddWindowStyle(this.hWindow, SBARS_SIZEGRIP)
      this.Refresh
   end if
   _SizingGrip = nValue
end property

function wfxStatusBar.Show(byval hWndParent as hwnd = 0) as long

   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function
      
   ' If the control is created but simply hidden, then show it.
   if this.hWindow THEN
      ShowWindow(this.hWindow, SW_SHOW)
      exit function
   END IF

   dim as long dwExStyle = 0
   dim as long dwStyle = WS_CLIPCHILDREN OR WS_CLIPSIBLINGS OR CCS_BOTTOM 

   if this.SizingGrip THEN dwStyle = dwStyle OR SBARS_SIZEGRIP
   if this.Visible THEN dwStyle = dwStyle OR WS_VISIBLE
   
   this.hWindow = _
         this.Parent->pWindow->AddControl ( _
         "STATUSBAR", _                    ' Class name
         hWndParent, _                     ' Parent window handle
         100, _                            ' Control identifier (this gets modified when added to controls collection)
         this.Text, _                      ' Control caption
         this.Left, _                      ' Horizontal position
         this.Top, _                       ' Vertical position
         this.Width, _                     ' Control width
         this.Height, _                    ' Control height
         dwStyle, _                        ' Control style
         dwExStyle, _                      ' Extended style
         0, _                              ' Pointer to custom data
         Cast(WNDPROC, @wfxApplication.SubclassProc), _   ' Address of the window callback procedure
         100, _                            ' The subclass ID
         Cast(DWORD_PTR, 0) _              ' Pointer to reference data
         )

   ' Update the hWindow in the form's linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   dim pNode as wfxLListNode ptr = this.Parent->Controls.search_data(@this)
   if pNode then pNode->hWindow = this.hWindow

   ' Make sure the Panels collection also knows the window handle of the parent statusbar
'   this.Panels.hWindow = this.hWindow

   dim as single cx = this.Parent->pWindow->rxRatio
   
   ' Calculate and set the widths of the panels.
   if this.Panels.Count then
      dim as long nWidths(0 to this.Panels.Count - 1)
      for i as long = 0 to this.Panels.Count - 1
'         dim byref Panel as wfxStatusBarPanel = this.Panels.ByIndex(i)
'         if Panel.AutoSize = StatusBarPanelAutoSize.Spring then  
'            nWidths(i) = -1
'         else   
'            nWidths(i) = iif(i, nWidths(i-1), 0) + (Panel.Width * cx)
'         end if
         if this.Panels(i).AutoSize = StatusBarPanelAutoSize.Spring then  
            nWidths(i) = -1
         else   
            nWidths(i) = iif(i, nWidths(i-1), 0) + (this.Panels(i).Width * cx)
         end if
      NEXT
      StatusBar_SetParts( this.hWindow, this.Panels.Count, @nWidths(0))
   end if

   ' Set the text for the panels. Need to do this after the widths are set.
   for i as long = 0 to this.Panels.Count - 1
      ' Get the panel text prior to assigning the statusbar handle otherwise the
      ' library will try to retrieve the text from the actual window control and
      ' that text hasn't even been assigned yet.
      'dim byref Panel as wfxStatusBarPanel = this.Panels.ByIndex(i)
      'dim as CWSTR wszPanelText = Panel.Text
      'Panel.hWindow = this.hWindow
      dim as CWSTR wszPanelText = this.Panels(i).Text
      this.Panels(i).hWindow = this.hWindow
      StatusBar_SetText(this.hWindow, i, wszPanelText, this.Panels(i).BorderStyle) 
   next
   
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

property wfxStatusBarPanel.BorderStyle() as StatusBarPanelBorderStyle
   property = _BorderStyle
end property

property wfxStatusBarPanel.BorderStyle( byval nValue as StatusBarPanelBorderStyle)
   _BorderStyle = nValue
end property

property wfxStatusBarPanel.Text() as CWSTR
   if this.hWindow then 
      StatusBar_GetText(this.hWindow, this.Index, _Text.vptr)
   end if   
   property = _Text
end property

property wfxStatusBarPanel.Text( byref wszValue as wstring )
   if this.hWindow then 
      StatusBar_SetText(this.hWindow, this.Index, @wszValue, this.BorderStyle) 
   end if   
   _Text = wszValue
end property

property wfxStatusBarPanel.Width() as long
   property = _Width
end property

property wfxStatusBarPanel.Width( byVal nValue as long)
   _Width = nValue
end property

'' STATUSBARCOLLECTION
property wfxStatusBarPanelsCollection.hWindow() as hwnd
   property = _hWindow
end property

property wfxStatusBarPanelsCollection.hWindow( byVal nValue as hwnd)
   _hWindow = nValue
end property

function wfxStatusBarPanelsCollection.Count() as Long
   function = _Collection.Size
end function

function wfxStatusBarPanelsCollection.Add() byref as wfxStatusBarPanel 
   dim pData as wfxStatusBarPanel ptr = new wfxStatusBarPanel
   pData->hWindow = this.hWindow
   pData->Index = (this.Count - 1) + 1
   _Collection.Add( ControlType.StatusBarPanel, pData ) 
   return *pData
end function

function wfxStatusBarPanelsCollection.ByIndex( byval nIndex as long ) byref as wfxStatusBarPanel 
   dim pPanel as wfxStatusBarPanel ptr
   dim pNode as wfxLListNode ptr
   pNode = _Collection.get_first
   do until pNode = 0
      pPanel = cast(wfxStatusBarPanel ptr, pNode->pData)
      if pPanel->Index = nIndex then
         exit do
      END IF
      pNode = _Collection.get_next(pNode)
   LOOP
   return *pPanel
end function





