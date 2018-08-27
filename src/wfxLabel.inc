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
   this.BackColor = Colors.SystemControl
End Constructor

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
      AfxRemoveWindowExStyle(this.hWindow, WS_EX_CLIENTEDGE)
      AfxRemoveWindowStyle(this.hWindow, WS_BORDER)
      Dim As Long wsStyle
      Select Case nValue
         Case ControlBorderStyle.None
         Case ControlBorderStyle.Fixed3D
            AfxAddWindowExStyle(this.hWindow, WS_EX_CLIENTEDGE)
         Case ControlBorderStyle.FixedSingle
            AfxAddWindowStyle(this.hWindow, WS_BORDER)
      End Select
      SetWindowPos( this.hWindow, 0, 0, 0, 0, 0, SWP_NOZORDER Or SWP_NOMOVE Or SWP_NOSIZE Or SWP_DRAWFRAME)
   End If
   _BorderStyle = nValue
End Property

Function wfxLabel.GetTextAlignStyleValue( ByVal nValue As LabelAlignment ) As Long
   Select Case nValue
      Case LabelAlignment.MiddleCenter: Return (SS_CENTER Or SS_CENTERIMAGE)
      Case LabelAlignment.MiddleLeft:   Return (SS_LEFT   Or SS_CENTERIMAGE)
      Case LabelAlignment.MiddleRight:  Return (SS_RIGHT  Or SS_CENTERIMAGE)
      Case LabelAlignment.TopCenter:    Return (SS_CENTER)
      Case LabelAlignment.TopLeft:      Return (SS_LEFT)
      Case LabelAlignment.TopRight:     Return (SS_RIGHT)
   End Select
   Return 0   
End Function

Property wfxLabel.TextAlign() As LabelAlignment
   if this.hWindow then 
      Dim As Long wsStyle = AfxGetWindowStyle(this.hWindow)
      If wsStyle And (SS_CENTER Or SS_CENTERIMAGE)  Then Return LabelAlignment.MiddleCenter
      If wsStyle And (SS_LEFT   Or SS_CENTERIMAGE)  Then Return LabelAlignment.MiddleLeft
      If wsStyle And (SS_RIGHT  Or SS_CENTERIMAGE)  Then Return LabelAlignment.MiddleRight
      If wsStyle And (SS_CENTER)                    Then Return LabelAlignment.TopCenter
      If wsStyle And (SS_LEFT)                      Then Return LabelAlignment.TopLeft
      If wsStyle And (SS_RIGHT)                     Then Return LabelAlignment.TopRight
   Else
      Return _TextAlign
   End If   
end property

property wfxLabel.TextAlign( byval nValue as LabelAlignment )
   if this.hWindow then 
      ' Remove the current alignment and set the new style
      AfxRemoveWindowStyle(this.hWindow, this.GetTextAlignStyleValue(_TextAlign))
      AfxAddWindowStyle(this.hWindow, this.GetTextAlignStyleValue(nValue))
      this.Refresh
   end if
   _TextAlign = nValue
end property

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
   Dim As Long dwStyle = WS_GROUP Or SS_NOTIFY 

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
         Cast(WNDPROC, @wfxApplication.SubclassProc), _   ' // Address of the window callback procedure
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

   ' Store the hWindow in the form's linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   dim pNode as wfxLListNode ptr = this.Parent->Controls.search_data(@this)
   if pNode then pNode->hWindow = this.hWindow

   function = 0
END FUNCTION




