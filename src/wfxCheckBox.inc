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
''  CheckBox Class
''
''  https://msdn.microsoft.com/en-us/library/system.windows.forms.checkbox(v=vs.110).aspx
''

#include once "wfxCheckBox.bi"

constructor wfxCheckBox( byref wszName as wstring = "" )
   this.CtrlType = ControlType.CheckBox
   this.Name = wszName
   this.BackColor = Colors.SystemControl
end constructor

Property wfxCheckBox.ThreeState() As boolean
   If this.hWindow Then 
      Dim As boolean bState = False
      Dim As Long wsStyle = AfxGetWindowStyle(this.hWindow)
      If (wsStyle And BS_3STATE) Then bState = True
      If (wsStyle And BS_AUTO3STATE) Then bState = True
      _ThreeState = bState
   End If
   Property = _ThreeState
End Property

Property wfxCheckBox.ThreeState( ByVal nValue As boolean )
   If this.hWindow Then 
      AfxRemoveWindowStyle(this.hWindow, BS_AUTOCHECKBOX)
      AfxAddWindowStyle(this.hWindow, BS_AUTO3STATE)
   End If
   _ThreeState = nValue
End Property

Property wfxCheckBox.CheckState() As CheckBoxState
   if this.hWindow then 
      Dim As Long wsState = SendMessage( this.hWindow, BM_GETCHECK, 0, 0)
      Select Case wsState
         Case BST_CHECKED: wsState = CheckBoxState.Checked
         Case BST_UNCHECKED: wsState = CheckBoxState.UnChecked
         Case BST_INDETERMINATE: wsState = CheckBoxState.Indeterminate
      End Select
      _CheckState = wsState
   End If
   Property = _CheckState
end property

Property wfxCheckBox.CheckState( ByVal nValue As CheckBoxState )
   if this.hWindow then 
      Dim As Long wsState
      Select Case nValue
         Case CheckBoxState.Checked: wsState = BST_CHECKED
         Case CheckBoxState.UnChecked: wsState = BST_UNCHECKED
         Case CheckBoxState.Indeterminate: wsState = BST_INDETERMINATE
      End Select   
      SendMessage( this.hWindow, BM_SETCHECK, wsState, 0)
   end if
   _CheckState = nValue
end property

Function wfxCheckBox.GetTextAlignStyleValue( ByVal nValue As ButtonAlignment ) As Long
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

Property wfxCheckBox.TextAlign() As ButtonAlignment 
   if this.hWindow then 
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

Property wfxCheckBox.TextAlign( ByVal nValue As ButtonAlignment )
   If this.hWindow Then 
      ' Remove the current alignment and set the new style
      AfxRemoveWindowStyle(this.hWindow, this.GetTextAlignStyleValue(_TextAlign))
      AfxAddWindowStyle(this.hWindow, this.GetTextAlignStyleValue(nValue))
      this.Refresh
   End If
   _TextAlign = nValue
End Property

Function wfxCheckBox.Show(ByVal hWndParent As HWnd = 0) As Long

   ' If the control is created but simply hidden, then show it.
   if this.hWindow THEN
      ShowWindow(this.hWindow, SW_SHOW)
      exit function
   END IF

   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function
      
   dim as long dwExStyle = 0
   Dim As Long dwStyle = BS_NOTIFY
   if _TabStop then dwStyle = dwStyle OR WS_TABSTOP 
   if _Visible THEN dwStyle = dwStyle OR WS_VISIBLE
   If _ThreeState Then 
      dwStyle = dwStyle Or BS_AUTO3STATE
   Else
      dwStyle = dwStyle Or BS_AUTOCHECKBOX
   End If   
   
   _CtrlID = this.Parent->GetNextCtrlID()

   this.hWindow = this.Parent->pWindow->AddControl ( _
         "CHECKBOX", _                     ' // Class name
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
   this.Font       = _wfxFontPtr
   this.TextAlign  = _TextAlign
   this.Enabled    = _Enabled
   this.CheckState = _CheckState
   this.ToolTip      = _ToolTip

   ' Do not set the focus/selected here because doing so will also Activate the form and
   ' cause an Activated message to be fired. We want the Form's Load event to
   ' complete before any Activate message.
   ' Refer to wfxForm.CreateFormInternal for the setting of the focus/selected
   ' control once events have fired correctly.
      
   ' Store the hWindow in the form's linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   dim pNode as wfxLListNode ptr = this.Parent->Controls.search_data(@this)
   if pNode then pNode->hWindow = this.hWindow
      
   function = 0
END FUNCTION



