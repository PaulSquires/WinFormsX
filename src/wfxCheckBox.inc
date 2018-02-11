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
   this.BackColor = Colors.SystemButtonFace
end constructor

property wfxCheckBox.Checked() as boolean
   if this.hWindow then 
      _Checked = Iif( SendMessage( this.hWindow, BM_GETCHECK, 0, 0) = BST_CHECKED, true, false)
   end if
   property = _Checked
end property

property wfxCheckBox.Checked( byval nValue as boolean )
   if this.hWindow then 
      SendMessage( this.hWindow, BM_SETCHECK, iif(nValue, BST_CHECKED, BST_UNCHECKED), 0)
   end if
   _Checked = nValue
end property

function wfxCheckBox.Show(byval hWndParent as hwnd = 0) as long

   ' If the control is created but simply hidden, then show it.
   if this.hWindow THEN
      ShowWindow(this.hWindow, SW_SHOW)
      exit function
   END IF

   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function
      
   dim as long dwExStyle = 0
   dim as long dwStyle = BS_AUTOCHECKBOX 
   if _TabStop then dwStyle = dwStyle OR WS_TABSTOP 
   if _Visible THEN dwStyle = dwStyle OR WS_VISIBLE

   this.hWindow = this.Parent->pWindow->AddControl ( _
         "CHECKBOX", _                     ' // Class name
         hWndParent, _                     ' // Parent window handle
         100, _                            ' // Control identifier (this gets modified when added to controls collection)
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

   ' Do not set the focus/selected here because doing so will also Activate the form and
   ' cause an Activated message to be fired. We want the Form's Load event to
   ' complete before any Activate message.
   ' Refer to wfxForm.CreateFormInternal for the setting of the focus/selected
   ' control once events have fired correctly.
      
   ' Store the hWindow in the form's linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   dim pNode as wfxLListNode ptr = this.Parent->Controls.search_data(@this)
   if pNode then pNode->hWindow = this.hWindow
      
   this.Enabled = _Enabled
   this.Checked = _Checked

   function = 0
END FUNCTION



