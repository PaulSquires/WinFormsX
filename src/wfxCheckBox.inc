''
''  CheckBox Class
''
''  https://msdn.microsoft.com/en-us/library/system.windows.forms.checkbox(v=vs.110).aspx
''

constructor wfxCheckBox( byref wszName as wstring = "" )
   this.CtrlType = ControlType.CheckBox
   this.Name = wszName
end constructor

property wfxCheckBox.TextAlign() as ButtonAlignment
   property = _TextAlign
end property

property wfxCheckBox.TextAlign( byval nValue as ButtonAlignment )
   if this.hWindow then 
      ' Remove the current alignment and set the new style
      AfxRemoveWindowStyle(this.hWindow, _TextAlign)
      AfxAddWindowStyle(this.hWindow, nValue)
      this.Refresh
   end if
   _TextAlign = nValue
end property

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
   dim as long dwStyle = BS_AUTOCHECKBOX or _TextAlign
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

   this.Enabled = _Enabled
   this.Checked = _Checked
   ' Do not set the focus/selected here because doing so will also Activate the form and
   ' cause an Activated message to be fired. We want the Form's Load event to
   ' complete before any Activate message.
   ' Refer to wfxForm.CreateFormInternal for the setting of the focus/selected
   ' control once events have fired correctly.
      
   function = 0
END FUNCTION



