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
''  TextBox Class
''
''  https://msdn.microsoft.com/en-us/library/system.windows.forms.textbox(v=vs.110).aspx
''

#include once "wfxTextBox.bi"


constructor wfxTextBox( byref wszName as wstring = "" )
   this.CtrlType = ControlType.TextBox
   this.Name = wszName
   this.BackColor = Colors.SystemWindowFace
   this.ForeColor = Colors.SystemWindowText
end constructor

property wfxTextBox.TextAlign() as TextBoxAlignment
   property = _TextAlign
end property

property wfxTextBox.TextAlign( byval nValue as TextBoxAlignment )
   if this.hWindow then 
      ' Remove the current alignment and set the new style
      AfxRemoveWindowStyle(this.hWindow, _TextAlign)
      AfxAddWindowStyle(this.hWindow, nValue)
      this.Refresh
   end if
   _TextAlign = nValue
end property

property wfxTextBox.BorderStyle() as TextBoxBorderStyle
   property = _BorderStyle
end property

property wfxTextBox.BorderStyle( byval nValue as TextBoxBorderStyle )
   _BorderStyle = nValue
end property

property wfxTextBox.Multiline() as boolean
   if this.hWindow then 
      _Multiline = iIF( (AfxGetWindowStyle(this.hWindow) AND ES_MULTILINE) = ES_MULTILINE, true, false)
   end if
   property = _Multiline
end property

property wfxTextBox.Multiline( byval nValue as boolean )
   if this.hWindow then 
      ' Test if the style has changed
      if nValue <> _Multiline THEN
         AfxRemoveWindowStyle(this.hWindow, ES_MULTILINE)
         if nValue then AfxAddWindowStyle(this.hWindow, ES_MULTILINE)
      END IF
      ' TODO: Recreate textbox if multiline style changed?
      this.Refresh  
   end if
   _Multiline = nValue
end property

property wfxTextBox.WordWrap() as boolean
   if this.hWindow then 
      _WordWrap = iIF( (AfxGetWindowStyle(this.hWindow) AND ES_AUTOHSCROLL) = ES_AUTOHSCROLL, false, true)
   end if
   property = _WordWrap
end property

property wfxTextBox.WordWrap( byval nValue as boolean )
   if this.hWindow then 
      ' Test if the style has changed
      if nValue <> _WordWrap THEN
         AfxRemoveWindowStyle(this.hWindow, ES_MULTILINE)
         if nValue then AfxAddWindowStyle(this.hWindow, ES_MULTILINE)
      END IF
      ' TODO: Recreate textbox if wordwrap style changed?
      this.Refresh  
   end if
   _Multiline = nValue
end property

function wfxTextBox.Show(byval hWndParent as hwnd = 0) as long

   dim wszClassName as wstring * MAX_PATH
   
   ' If the control is created but simply hidden, then show it.
   if this.hWindow THEN
      ShowWindow(this.hWindow, SW_SHOW)
      exit function
   END IF

   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function
      
   dim as long dwExStyle = _BorderStyle
   dim as long dwStyle = _TextAlign
   
   if _Multiline then
      dwStyle = dwStyle or WS_VSCROLL OR ES_MULTILINE OR ES_NOHIDESEL OR ES_WANTRETURN
      if _WordWrap = false then dwStyle = dwStyle OR ES_AUTOHSCROLL
      wszClassName = "MULTILINETEXTBOX"
   else   
      dwStyle = dwStyle or ES_AUTOHSCROLL 
      wszClassName = "TEXTBOX"
   end if   

   if _TabStop then dwStyle = dwStyle OR WS_TABSTOP 
   if _Visible THEN dwStyle = dwStyle OR WS_VISIBLE
   
   this.hWindow = this.Parent->pWindow->AddControl ( _
         wszClassName, _                   ' // Class name
         hWndParent, _                     ' // Parent window handle
         100, _                            ' // Control identifier (this gets modified when added to controls collection)
         this.Text, _                      ' // Control caption
         this.Left, _                      ' // Horizontal position
         this.Top, _                       ' // Vertical position
         this.Width, _                     ' // Control width
         this.Height, _                    ' // Control height
         dwStyle, _                        ' // Control style
         dwExStyle, _                      ' // Extended style
         0, _                              ' // Pointer to custom data
         Cast(WNDPROC, @wfxApplication.SubclassProc), _   ' // Address of the window callback procedure
         100, _                            ' // The subclass ID
         Cast(DWORD_PTR, 0) _              ' // Pointer to reference data
         )

   ' Do not set the focus/selected here because doing so will also Activate the form and
   ' cause an Activated message to be fired. We want the Form's Load event to
   ' complete before any Activate message.
   ' Refer to wfxForm.CreateFormInternal for the setting of the focus/selected
   ' control once events have fired correctly.
      
   ' Store the hWindow in the linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   dim pNode as wfxLListNode ptr = this.Parent->Controls.search_data(@this)
   if pNode then pNode->hWindow = this.hWindow
      
   this.Enabled = _Enabled

   function = 0
END FUNCTION




