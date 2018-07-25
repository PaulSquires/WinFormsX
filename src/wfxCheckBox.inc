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

Property wfxCheckBox.TextAlign() As ButtonAlignment 
   Property = _TextAlign
End Property

Property wfxCheckBox.TextAlign( ByVal nValue As ButtonAlignment )
   If this.hWindow Then 
      AfxRemoveWindowStyle(this.hWindow, BS_LEFT)
      AfxRemoveWindowStyle(this.hWindow, BS_RIGHT)
      AfxRemoveWindowStyle(this.hWindow, BS_CENTER)
      AfxRemoveWindowStyle(this.hWindow, BS_TOP)
      AfxRemoveWindowStyle(this.hWindow, BS_BOTTOM)
      Dim As Long wsStyle
      Select Case nValue
         Case ButtonAlignment.BottomCenter: wsStyle = BS_CENTER Or BS_BOTTOM
         Case ButtonAlignment.BottomLeft:   wsStyle = BS_LEFT   Or BS_BOTTOM
         Case ButtonAlignment.BottomRight:  wsStyle = BS_RIGHT  Or BS_BOTTOM
         Case ButtonAlignment.MiddleCenter: wsStyle = BS_CENTER Or BS_VCENTER
         Case ButtonAlignment.MiddleLeft:   wsStyle = BS_LEFT   Or BS_VCENTER
         Case ButtonAlignment.MiddleRight:  wsStyle = BS_RIGHT  Or BS_VCENTER
         Case ButtonAlignment.TopCenter:    wsStyle = BS_CENTER Or BS_TOP
         Case ButtonAlignment.TopLeft:      wsStyle = BS_LEFT   Or BS_TOP
         Case ButtonAlignment.TopRight:     wsStyle = BS_RIGHT  Or BS_TOP
      End Select
      AfxAddWindowStyle(this.hWindow, wsStyle)
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
         Cast(WNDPROC, @wfxApplication.SubclassProc), _   ' // Address of the window callback procedure
         100, _                            ' // The subclass ID
         Cast(DWORD_PTR, 0) _              ' // Pointer to reference data
         )

   ' Should we enable drag and drop files
   If this.AllowDrop Then DragAcceptFiles(this.hWindow, CTRUE)

   ' Apply properties that require a valid window handle
   this.Font       = _wfxFontPtr
   this.TextAlign  = _TextAlign
   this.Enabled    = _Enabled
   this.CheckState = _CheckState

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



