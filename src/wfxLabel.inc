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
''  Label Class
''
''  https://msdn.microsoft.com/en-us/library/system.windows.forms.label(v=vs.110).aspx
''

#include once "wfxLabel.bi"

constructor wfxLabel( byref wszName as wstring = "" )
   this.CtrlType = ControlType.Label
   this.Name = wszName
   this.BackColor = Colors.SystemControl
   this.BackColorHot = Colors.SystemControl
   this.ForeColorHot = this.ForeColor
End Constructor

destructor wfxLabel()
   ' Destroy the backgroundhot brush
   DeleteObject(_hBackBrushHot)
End Destructor

Property wfxLabel.hBackBrushHot() As HBRUSH
   property = _hBackBrushHot
end property

property wfxLabel.BackColorHot() as COLORREF
   property = _BackColorHot
end property

property wfxLabel.BackColorHot( byval nValue as COLORREF )
   ' Create new back hot brush of the color has changed
   if nValue <> _BackColorHot THEN
      DeleteObject(_hBackBrushHot)
      _hBackBrushHot = CreateSolidBrush(nValue)
   END IF
   _BackColorHot = nValue
   if this.hWindow THEN AfxRedrawWindow(this.hWindow)
end property

property wfxLabel.ForeColorHot() as COLORREF
   property = _ForeColorHot
end property

property wfxLabel.ForeColorHot( byval nValue as COLORREF )
   _ForeColorHot = nValue
   if this.hWindow THEN AfxRedrawWindow(this.hWindow)
end property

Property wfxLabel.BorderStyle() As ControlBorderStyle
   if this.hWindow then 
      If (AfxGetWindowExStyle(this.hWindow) And WS_EX_CLIENTEDGE) Then
         _BorderStyle = ControlBorderStyle.Fixed3D
      ElseIf (AfxGetWindowStyle(this.hWindow) And WS_BORDER) Then
         _BorderStyle = ControlBorderStyle.FixedSingle
      Else
         _BorderStyle = ControlBorderStyle.None
      End If   
   End If
   Property = _BorderStyle
End Property

Property wfxLabel.BorderStyle( ByVal nValue As ControlBorderStyle )
   if this.hWindow then 
      Dim As Long wsStyle
      Select Case nValue
         Case ControlBorderStyle.None
            AfxRemoveWindowStyle(this.hWindow, WS_BORDER)
            AfxRemoveWindowExStyle(this.hWindow, WS_EX_CLIENTEDGE)
         Case ControlBorderStyle.Fixed3D
            AfxRemoveWindowStyle(this.hWindow, WS_BORDER)
            AfxAddWindowExStyle(this.hWindow, WS_EX_CLIENTEDGE)
         Case ControlBorderStyle.FixedSingle
            AfxAddWindowStyle(this.hWindow, WS_BORDER)
            AfxRemoveWindowExStyle(this.hWindow, WS_EX_CLIENTEDGE)
      End Select
      AfxRedrawNonClientArea( this.hWindow )
   End If
   _BorderStyle = nValue
End Property

Function wfxLabel.GetTextAlignStyleValue( ByVal nValue As LabelAlignment ) As Long
   dim as long wsStyle 
   Select Case nValue
      Case LabelAlignment.BottomCenter: wsStyle = DT_CENTER Or DT_BOTTOM  or DT_SINGLELINE
      Case LabelAlignment.BottomLeft:   wsStyle = DT_LEFT   Or DT_BOTTOM  or DT_SINGLELINE
      Case LabelAlignment.BottomRight:  wsStyle = DT_RIGHT  Or DT_BOTTOM  or DT_SINGLELINE
      Case LabelAlignment.MiddleCenter: wsStyle = DT_CENTER Or DT_VCENTER or DT_SINGLELINE
      Case LabelAlignment.MiddleLeft:   wsStyle = DT_LEFT   Or DT_VCENTER or DT_SINGLELINE
      Case LabelAlignment.MiddleRight:  wsStyle = DT_RIGHT  Or DT_VCENTER or DT_SINGLELINE
      Case LabelAlignment.TopCenter:    wsStyle = DT_CENTER Or DT_TOP     or DT_WORDBREAK 
      Case LabelAlignment.TopLeft:      wsStyle = DT_LEFT   Or DT_TOP     or DT_WORDBREAK 
      Case LabelAlignment.TopRight:     wsStyle = DT_RIGHT  Or DT_TOP     or DT_WORDBREAK 
   End Select
   wsStyle = wsStyle or DT_EXPANDTABS
   Return wsStyle 
End Function

Property wfxLabel.TextAlign( ByVal nValue As LabelAlignment )
   _TextAlign = nValue
   if this.hWindow then this.Refresh
end property

Property wfxLabel.TextAlign() As LabelAlignment 
   property = _TextAlign
End Property


Property wfxLabel.UseMnemonic() As boolean
   Property = _UseMnemonic
end property

Property wfxLabel.UseMnemonic( ByVal nValue As boolean )
   _UseMnemonic = nValue
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
   Dim As Long dwStyle = WS_GROUP Or SS_NOTIFY or SS_OWNERDRAW

   if this.Visible THEN dwStyle = dwStyle OR WS_VISIBLE 
   If this.UseMnemonic = False Then dwStyle = dwStyle Or SS_NOPREFIX 
   
   _CtrlID = this.Parent->GetNextCtrlID()

   this.hWindow = this.Parent->pWindow->AddControl ( _
         "LABEL", _                        ' // Class name
         hWndParent, _                     ' // Parent window handle
         _CtrlID, _                        ' // Control identifier 
         this.Text, _                      ' // Control caption
         this.Left, _                      ' // Horizontal position
         this.Top, _                       ' // Vertical position
         this.Width, _                     ' // Control width
         this.Height, _                    ' // Control height
         dwStyle, _                        ' // Control style
         dwExStyle, _                      ' // Extended style
         0, _                              ' // Pointer to custom data
         Cast(SUBCLASSPROC, @wfxApplication.SubclassProc), _   ' // Address of the window callback procedure
         _CtrlID, _                        ' // The subclass ID
         Cast(DWORD_PTR, 0) _              ' // Pointer to reference data
         )

   ' Should we enable drag and drop files
   If this.AllowDrop Then DragAcceptFiles(this.hWindow, CTRUE)

   ' Apply properties that require a valid window handle
   this.Font        = _wfxFontPtr
   this.TextAlign   = _TextAlign
   this.BorderStyle = _BorderStyle
   this.Enabled     = _Enabled
   this.ToolTip     = _ToolTip

   ' Store the hWindow in the form's linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   dim pNode as wfxLListNode ptr = this.Parent->Controls.search_data(@this)
   if pNode then pNode->hWindow = this.hWindow

   function = 0
END FUNCTION




