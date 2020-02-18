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
''  MaskedEdit textBox Class
''

#Include Once "wfxMaskedEdit.bi"


Constructor wfxMaskedEdit( ByRef wszName As WString = "" )
   this.CtrlType = ControlType.MaskedEdit
   this.Name = wszName
   this.BackColor = Colors.SystemWindow
   this.ForeColor = Colors.SystemWindowText
end constructor

Destructor wfxMaskedEdit()
   if _MaskedEditPtr then Delete _MaskedEditPtr
   _MaskedEditPtr = 0
End Destructor

Property wfxMaskedEdit.BorderStyle() As ControlBorderStyle
   If _MaskedEditPtr Then 
      If (AfxGetWindowExStyle(_MaskedEditPtr->hWindow) And WS_EX_CLIENTEDGE) Then
         _BorderStyle = ControlBorderStyle.Fixed3D
      ElseIf (AfxGetWindowStyle(_MaskedEditPtr->hWindow) And WS_BORDER) Then
         _BorderStyle = ControlBorderStyle.FixedSingle
      Else
         _BorderStyle = ControlBorderStyle.None
      End If   
   End If
   Property = _BorderStyle
End Property

Property wfxMaskedEdit.BorderStyle( ByVal nValue As ControlBorderStyle )
   If _MaskedEditPtr Then 
      Dim As Long wsStyle
      Select Case nValue
         Case ControlBorderStyle.None
            AfxRemoveWindowStyle(_MaskedEditPtr->hWindow, WS_BORDER)
            AfxRemoveWindowExStyle(_MaskedEditPtr->hWindow, WS_EX_CLIENTEDGE)
         Case ControlBorderStyle.Fixed3D
            AfxRemoveWindowStyle(_MaskedEditPtr->hWindow, WS_BORDER)
            AfxAddWindowExStyle(_MaskedEditPtr->hWindow, WS_EX_CLIENTEDGE)
         Case ControlBorderStyle.FixedSingle
            AfxAddWindowStyle(_MaskedEditPtr->hWindow, WS_BORDER)
            AfxRemoveWindowExStyle(_MaskedEditPtr->hWindow, WS_EX_CLIENTEDGE)
      End Select
      AfxRedrawNonClientArea( _MaskedEditPtr->hWindow )
   End If
   _BorderStyle = nValue
End Property

Property wfxMaskedEdit.ReadOnly() As boolean
   If _MaskedEditPtr Then 
      _ReadOnly = Iif( (AfxGetWindowStyle(_MaskedEditPtr->hWindow) And ES_READONLY), True, False)
   End If
   Property = _ReadOnly
End Property

Property wfxMaskedEdit.ReadOnly( ByVal nValue As boolean )
   If _MaskedEditPtr Then 
      AfxRemoveWindowStyle(_MaskedEditPtr->hWindow, ES_READONLY)
      If nValue Then AfxAddWindowStyle(_MaskedEditPtr->hWindow, ES_READONLY)
   End If
   _ReadOnly = nValue
End Property

Property wfxMaskedEdit.HideSelection() As boolean
   If _MaskedEditPtr Then 
      _HideSelection = Iif( (AfxGetWindowStyle(_MaskedEditPtr->hWindow) And ES_NOHIDESEL) = ES_NOHIDESEL, False, True)
   End If
   Property = _HideSelection
End Property

Property wfxMaskedEdit.HideSelection( ByVal nValue As boolean )
   If _MaskedEditPtr Then 
      AfxRemoveWindowStyle(_MaskedEditPtr->hWindow, ES_NOHIDESEL)
      If nValue = False Then AfxAddWindowStyle(_MaskedEditPtr->hWindow, ES_NOHIDESEL)
   End If
   _HideSelection = nValue
End Property

Function wfxMaskedEdit.GetText( ByVal bGetMaskedCharsOnly As Boolean = False ) As CWSTR
   If _MaskedEditPtr Then 
      _Text = _MaskedEditPtr->GetText(bGetMaskedCharsOnly) 
   End If
   Function = _Text
End Function

Function wfxMaskedEdit.SetText( ByRef nValue As WString, ByVal bSetMaskedCharsOnly As Boolean = False ) As Long
   If _MaskedEditPtr Then 
      _MaskedEditPtr->SetText(nValue, bSetMaskedCharsOnly) 
   End If
   Function = 0
End Function

Function wfxMaskedEdit.GenerateMask() As Long
   If _MaskedEditPtr Then 
      _MaskedEditPtr->EnableMask(this.MaskString, this.InputString, this.DefaultCharacter, this.ValidCharacters) 
   End If
   Function = 0
End Function

Property wfxMaskedEdit.MaskString() As CWSTR
   Property = _MaskString
End Property

Property wfxMaskedEdit.MaskString( ByRef nValue As WString )
   _MaskString = nValue
   this.GenerateMask()
End Property

Property wfxMaskedEdit.InputString() As CWSTR
   Property = _InputString
End Property

Property wfxMaskedEdit.InputString( ByRef nValue As WString )
   _InputString = nValue
   this.GenerateMask()
End Property

Property wfxMaskedEdit.DefaultCharacter() As CWSTR
   Property = _DefaultCharacter
End Property

Property wfxMaskedEdit.DefaultCharacter( ByRef nValue As WString )
   _DefaultCharacter = nValue
   this.GenerateMask()
End Property

Property wfxMaskedEdit.ValidCharacters() As CWSTR
   Property = _ValidCharacters
End Property

Property wfxMaskedEdit.ValidCharacters( ByRef nValue As WString )
   _ValidCharacters = nValue
   this.GenerateMask()
End Property


Function wfxMaskedEdit.Show(ByVal hWndParent As HWnd = 0) As Long

   dim wszClassName as wstring * MAX_PATH
   
   ' If the control is created but simply hidden, then show it.
   if this.hWindow THEN
      ShowWindow(this.hWindow, SW_SHOW)
      exit function
   END IF

   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function
      
   Dim As dword dwStyle, dwExStyle
   
   If _HideSelection = False Then dwStyle = dwStyle Or ES_NOHIDESEL
   if _TabStop then dwStyle = dwStyle OR WS_TABSTOP 
   If _Visible Then dwStyle = dwStyle Or WS_VISIBLE
   
   Dim pWindow As CWindow Ptr = AfxCWindowPtr(hWndParent)

   ' Use the custom control CMaskedEdit
   _CtrlID = this.Parent->GetNextCtrlID()
   _MaskedEditPtr = New CMaskedEdit(pWindow, _CtrlID, this.Left, this.top, this.Width, this.height )
   this.hWindow = _MaskedEditPtr->hWindow
   SetWindowSubclass(this.hWindow, Cast(SUBCLASSPROC, @wfxApplication.SubclassProc), _CtrlID, Cast(DWORD_PTR, 0))
 
   ' Should we enable drag and drop files
   If this.AllowDrop Then DragAcceptFiles(this.hWindow, CTRUE)

   ' Apply properties that require a valid window handle
   this.Font             = _wfxFontPtr
   this.ReadOnly         = _ReadOnly
   this.BorderStyle      = _BorderStyle

   this.GenerateMask()
   this.SetText(_Text, False)   ' use _Text otherwise Text will use AfxGetWindowText and will return InputMask.
   
   this.ToolTip     = _ToolTip

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




