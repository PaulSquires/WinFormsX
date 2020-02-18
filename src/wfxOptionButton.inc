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
''  RadioButton Class
''
''  https://msdn.microsoft.com/en-us/library/system.windows.forms.radiobutton(v=vs.110).aspx
''

#Include Once "wfxOptionButton.bi"

Constructor wfxOptionButton( ByRef wszName As WString = "" )
   this.CtrlType = ControlType.OptionButton
   this.Name = wszName
   this.BackColor = Colors.SystemControl
End Constructor

Function wfxOptionButton.GetTextAlignStyleValue( ByVal nValue As ButtonAlignment ) As Long
   Select Case nValue
      Case ButtonAlignment.BottomCenter: Return (BS_CENTER Or BS_BOTTOM)
      Case ButtonAlignment.BottomLeft:   Return (BS_LEFT   Or BS_BOTTOM)
      Case ButtonAlignment.BottomRight:  Return (BS_RIGHT  Or BS_BOTTOM)
      Case ButtonAlignment.MiddleCenter: Return (BS_CENTER Or BS_VCENTER)
      Case ButtonAlignment.MiddleLeft:   Return (BS_LEFT   Or BS_VCENTER)
      Case ButtonAlignment.MiddleRight:  Return (BS_RIGHT  Or BS_VCENTER)
      Case ButtonAlignment.TopCenter:    Return (BS_CENTER Or BS_TOP)
      Case ButtonAlignment.TopLeft:      Return (BS_LEFT   Or BS_TOP)
      Case ButtonAlignment.TopRight:     Return (BS_RIGHT  Or BS_TOP)
   End Select
   Return 0   
End Function

Property wfxOptionButton.TextAlign() As ButtonAlignment 
   If this.hWindow Then 
      Dim As Long wsStyle = AfxGetWindowStyle(this.hWindow)
      If wsStyle And (BS_CENTER Or BS_BOTTOM)  Then Return ButtonAlignment.BottomCenter
      If wsStyle And (BS_LEFT   Or BS_BOTTOM)  Then Return ButtonAlignment.BottomLeft
      If wsStyle And (BS_RIGHT  Or BS_BOTTOM)  Then Return ButtonAlignment.BottomRight
      If wsStyle And (BS_CENTER Or BS_VCENTER) Then Return ButtonAlignment.MiddleCenter
      If wsStyle And (BS_LEFT   Or BS_VCENTER) Then Return ButtonAlignment.MiddleLeft
      If wsStyle And (BS_RIGHT  Or BS_VCENTER) Then Return ButtonAlignment.MiddleRight
      If wsStyle And (BS_CENTER Or BS_TOP) Then Return ButtonAlignment.TopCenter
      If wsStyle And (BS_LEFT   Or BS_TOP) Then Return ButtonAlignment.TopLeft
      If wsStyle And (BS_RIGHT  Or BS_TOP) Then Return ButtonAlignment.TopRight
   Else
      Return _TextAlign
   End If   
End Property

Property wfxOptionButton.TextAlign( ByVal nValue As ButtonAlignment )
   If this.hWindow Then 
      ' Remove the current alignment and set the new style
      AfxRemoveWindowStyle(this.hWindow, this.GetTextAlignStyleValue(_TextAlign))
      AfxAddWindowStyle(this.hWindow, this.GetTextAlignStyleValue(nValue))
      this.Refresh
   End If
   _TextAlign = nValue
End Property

Property wfxOptionButton.Checked() As boolean
   if this.hWindow then 
      _Checked = Iif( SendMessage( this.hWindow, BM_GETCHECK, 0, 0) = BST_CHECKED, true, false)
   end if
   property = _Checked
end property

property wfxOptionButton.Checked( byval nValue as boolean )
   if this.hWindow then 
      SendMessage( this.hWindow, BM_SETCHECK, iif(nValue, BST_CHECKED, BST_UNCHECKED), 0)
   end if
   _Checked = nValue
end property

'Property wfxOptionButton.Index() As Long
'   Property = _Index
'End Property
'
'Property wfxOptionButton.Index( ByVal nValue As Long )
'   _Index = nValue
'End Property

Property wfxOptionButton.StartGroup() As boolean
   if this.hWindow then 
      _StartGroup = (AfxGetWindowStyle(this.hWindow) and WS_GROUP) = WS_GROUP
   end if
   property = _StartGroup
end property

property wfxOptionButton.StartGroup( byval nValue as boolean )
   if this.hWindow then 
      If nValue Then 
         AfxAddWindowStyle(this.hWindow, WS_GROUP)
      Else   
         AfxRemoveWindowStyle(this.hWindow, WS_GROUP)
      End If
   End If
   _StartGroup = nValue
end property

Property wfxOptionButton.GroupName() As CWSTR
   Property = _GroupName
End Property

Property wfxOptionButton.GroupName( ByRef nValue As WString )
   _GroupName = nValue
End Property

Function wfxOptionButton.Show(ByVal hWndParent As HWnd = 0) As Long

   ' If the control is created but simply hidden, then show it.
   if this.hWindow THEN
      ShowWindow(this.hWindow, SW_SHOW)
      exit function
   END IF

   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function
      
   dim as long dwExStyle = 0
   Dim As Long dwStyle = BS_AUTORADIOBUTTON 
   if _TabStop then dwStyle = dwStyle OR WS_TABSTOP 
   if _Visible THEN dwStyle = dwStyle OR WS_VISIBLE
   if _StartGroup THEN dwStyle = dwStyle or WS_GROUP

   _CtrlID = this.Parent->GetNextCtrlID()

   this.hWindow = this.Parent->pWindow->AddControl ( _
         "RADIOBUTTON", _                  ' // Class name
         hWndParent, _                     ' // Parent window handle
         _CtrlID, _                        ' // Control identifier 
         this.Text, _                      ' // Control caption
         this.Left, _                      ' // Horizontal position
         this.Top, _                       ' // Vertical position
         this.Width, _                     ' // Control width
         this.Height, _                    ' // Control height
         dwStyle, _                        ' // Control style
         dwExStyle, _                      ' // Extended style
          0, _                             ' // Pointer to custom data
         Cast(SUBCLASSPROC, @wfxApplication.SubclassProc), _   ' // Address of the window callback procedure
         _CtrlID, _                        ' // The subclass ID
         Cast(DWORD_PTR, 0) _              ' // Pointer to reference data
         )

   ' Should we enable drag and drop files
   If this.AllowDrop Then DragAcceptFiles(this.hWindow, CTRUE)

   ' Apply properties that require a valid window handle
   this.Font      = _wfxFontPtr
   this.TextAlign = _TextAlign
   this.Enabled   = _Enabled
   this.Checked   = _Checked
   this.ToolTip   = _ToolTip

   ' Do not set the focus/selected here because doing so will also Activate the form and
   ' cause an Activated message to be fired. We want the Form's Load event to
   ' complete before any Activate message.
   ' Refer to wfxForm.CreateFormInternal for the setting of the focus/selected
   ' control once events have fired correctly.

   ' Store the hWindow in the form's linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   Dim pNode As wfxLListNode Ptr = this.Parent->Controls.search_data(@this)
   If pNode Then pNode->hWindow = this.hWindow
      
      
   function = 0
END FUNCTION



