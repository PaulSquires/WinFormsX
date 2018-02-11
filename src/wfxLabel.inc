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
''  Label Class
''
''  https://msdn.microsoft.com/en-us/library/system.windows.forms.label(v=vs.110).aspx
''

#include once "wfxLabel.bi"

constructor wfxLabel( byref wszName as wstring = "" )
   this.CtrlType = ControlType.Label
   this.Name = wszName
end constructor

property wfxLabel.TextAlign() as LabelAlignment
   property = _TextAlign
end property

property wfxLabel.TextAlign( byval nValue as LabelAlignment )
   if this.hWindow then 
      ' Remove the current alignment and set the new style
      AfxRemoveWindowStyle(this.hWindow, _TextAlign)
      AfxAddWindowStyle(this.hWindow, nValue)
      this.Refresh
   end if
   _TextAlign = nValue
end property

property wfxLabel.FlatStyle() as boolean
   property = _FlatStyle
end property

property wfxLabel.FlatStyle( byval nValue as boolean )
   _FlatStyle = nValue
end property

function wfxLabel.Show(byval hWndParent as hwnd = 0) as long

   ' If the control is created but simply hidden, then show it.
   if this.hWindow THEN
      ShowWindow(this.hWindow, SW_SHOW)
      exit function
   END IF

   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function
      
   dim as long dwExStyle = 0
   dim as long dwStyle = WS_GROUP OR SS_NOTIFY or _TextAlign

   if this.FlatStyle = false then dwStyle = dwStyle OR SS_SUNKEN
   if this.Visible THEN dwStyle = dwStyle OR WS_VISIBLE
   
   this.hWindow = this.Parent->pWindow->AddControl ( _
         "LABEL", _                        ' // Class name
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

   ' Store the hWindow in the form's linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   dim pNode as wfxLListNode ptr = this.Parent->Controls.search_data(@this)
   if pNode then pNode->hWindow = this.hWindow

   this.Enabled = _Enabled

   function = 0
END FUNCTION




