''
''  Button Class
''

#include once "wfxButton.bi"

constructor wfxButton( byref wszName as wstring = "" )
   this.CtrlType = ControlType.Button
   this.Name = wszName
   this.BackColor = Colors.SystemButtonFace
   this.ForeColor = Colors.SystemButtonText
end constructor

property wfxButton.TextAlign() as ButtonAlignment
   property = _TextAlign
end property

property wfxButton.TextAlign( byval nValue as ButtonAlignment )
   if this.hWindow then 
      ' Remove the current alignment and set the new style
      AfxRemoveWindowStyle(this.hWindow, _TextAlign)
      AfxAddWindowStyle(this.hWindow, nValue)
      this.Refresh
   end if
   _TextAlign = nValue
end property

function wfxButton.Show(byval hWndParent as hwnd = 0) as long

   ' If the control is created but simply hidden, then show it.
   if this.hWindow THEN
      ShowWindow(this.hWindow, SW_SHOW)
      exit function
   END IF

   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function
      
   dim as long dwExStyle = 0
   dim as long dwStyle = BS_PUSHBUTTON or _TextAlign 
   if this.TabStop then dwStyle = dwStyle OR WS_TABSTOP 
   if this.Visible THEN dwStyle = dwStyle OR WS_VISIBLE
   
   this.hWindow = this.Parent->pWindow->AddControl ( _
         "BUTTON", _                       ' // Class name
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

   function = 0
END FUNCTION



