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
''  TextBox Class
''
''  https://msdn.microsoft.com/en-us/library/system.windows.forms.textbox(v=vs.110).aspx
''

#include once "wfxTextBox.bi"


constructor wfxTextBox( byref wszName as wstring = "" )
   this.CtrlType = ControlType.TextBox
   this.Name = wszName
   this.BackColor = Colors.SystemWindow
   this.ForeColor = Colors.SystemWindowText
   this.MaxLength = 32767
end constructor

Property wfxTextBox.TextAlign() As TextAlignment
   if this.hWindow then 
      Dim As Long wsStyle = AfxGetWindowStyle(this.hWindow)
      If (wsStyle And ES_LEFT) Then 
         _TextAlign = TextAlignment.Left
      ElseIf (wsStyle And ES_CENTER) Then 
         _TextAlign = TextAlignment.Center
      ElseIf (wsStyle And ES_RIGHT) Then 
         _TextAlign = TextAlignment.Right
      End If 
   End If
   Property = _TextAlign
end property

Property wfxTextBox.TextAlign( ByVal nValue As TextAlignment )
   if this.hWindow then 
      ' Remove the current alignment and set the new style
      AfxRemoveWindowStyle(this.hWindow, ES_LEFT)
      AfxRemoveWindowStyle(this.hWindow, ES_CENTER)
      AfxRemoveWindowStyle(this.hWindow, ES_RIGHT)
      Dim As Long wsStyle
      Select Case nValue 
         Case TextAlignment.Left:   wsStyle = ES_LEFT
         Case TextAlignment.Center: wsStyle = ES_CENTER
         Case TextAlignment.Right:  wsStyle = ES_RIGHT
      End Select
      AfxAddWindowStyle(this.hWindow, wsStyle)
      this.Refresh
   end if
   _TextAlign = nValue
end property

Property wfxTextBox.BorderStyle( ByVal nValue As ControlBorderStyle )
   If this.hWindow Then 
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

Property wfxTextBox.CharacterCasing() As CharacterCase
   If this.hWindow Then 
      Dim As Long wsStyle = AfxGetWindowStyle(this.hWindow)
      If (wsStyle And ES_LOWERCASE) Then
         _CharacterCasing = CharacterCase.Lower
      ElseIf (wsStyle And ES_UPPERCASE) Then
         _CharacterCasing = CharacterCase.Upper
      Else
         _CharacterCasing = CharacterCase.Normal
      End If   
   End If
   Property = _CharacterCasing
End Property

Property wfxTextBox.CharacterCasing( ByVal nValue As CharacterCase )
   If this.hWindow Then 
      AfxRemoveWindowStyle(this.hWindow, ES_LOWERCASE)
      AfxRemoveWindowStyle(this.hWindow, ES_UPPERCASE)
      Select Case nValue
         Case CharacterCase.Normal
         Case CharacterCase.Upper 
            AfxAddWindowStyle(this.hWindow, ES_UPPERCASE)
         Case CharacterCase.Lower
            AfxAddWindowStyle(this.hWindow, ES_LOWERCASE)
      End Select
   End If
   _CharacterCasing = nValue
End Property

Property wfxTextBox.Multiline() As boolean
   if this.hWindow then 
      _Multiline = Iif( (AfxGetWindowStyle(this.hWindow) And ES_MULTILINE), True, False)
   end if
   property = _Multiline
end property

property wfxTextBox.Multiline( byval nValue as boolean )
   if this.hWindow then 
      AfxAddWindowStyle(this.hWindow, ES_MULTILINE)
      If nValue Then AfxRemoveWindowStyle(this.hWindow, ES_MULTILINE)
      ' TODO: Recreate textbox if multiline style changed?
      this.Refresh  
   end if
   _Multiline = nValue
end property

Property wfxTextBox.ReadOnly() As boolean
   If this.hWindow Then 
      _ReadOnly = Iif( (AfxGetWindowStyle(this.hWindow) And ES_READONLY), True, False)
   End If
   Property = _ReadOnly
End Property

Property wfxTextBox.ReadOnly( ByVal nValue As boolean )
   If this.hWindow Then 
      SendMessage( this.hWindow, EM_SETREADONLY, nValue, 0 )
   End If
   _ReadOnly = nValue
End Property

Property wfxTextBox.MaxLength() As long
   If this.hWindow Then 
      _MaxLength = SendMessage( this.hWindow, EM_GETLIMITTEXT, 0, 0 )
   End If
   Property = _MaxLength
End Property

Property wfxTextBox.MaxLength( ByVal nValue As long )
   If this.hWindow Then 
      SendMessage( this.hWindow, EM_SETLIMITTEXT, nValue, 0 )
   End If
   _MaxLength = nValue
End Property

Property wfxTextBox.AcceptsReturn() As boolean
   If this.hWindow Then 
      _AcceptsReturn = Iif( (AfxGetWindowStyle(this.hWindow) And ES_WANTRETURN), True, False)
   End If
   Property = _AcceptsReturn
End Property

Property wfxTextBox.AcceptsReturn( ByVal nValue As boolean )
   If this.hWindow Then 
      AfxRemoveWindowStyle(this.hWindow, ES_WANTRETURN)
      If nValue Then AfxAddWindowStyle(this.hWindow, ES_WANTRETURN)
   End If
   _AcceptsReturn = nValue
End Property

Property wfxTextBox.AcceptsTab() As boolean
   Property = _AcceptsTab
End Property

Property wfxTextBox.AcceptsTab( ByVal nValue As boolean )
   _AcceptsTab = nValue
End Property

Property wfxTextBox.HideSelection() As boolean
   if this.hWindow then 
      _HideSelection = Iif( (AfxGetWindowStyle(this.hWindow) And ES_NOHIDESEL) = ES_NOHIDESEL, False, True)
   End If
   Property = _HideSelection
End Property

Property wfxTextBox.HideSelection( ByVal nValue As boolean )
   If this.hWindow Then 
      AfxRemoveWindowStyle(this.hWindow, ES_NOHIDESEL)
      If nValue = False Then AfxAddWindowStyle(this.hWindow, ES_NOHIDESEL)
   End If
   _HideSelection = nValue
End Property

Property wfxTextBox.WordWrap() As boolean
   if this.hWindow then 
      _WordWrap = iIF( (AfxGetWindowStyle(this.hWindow) AND ES_AUTOHSCROLL) = ES_AUTOHSCROLL, false, true)
   end if
   property = _WordWrap
end property

property wfxTextBox.WordWrap( byval nValue as boolean )
   ' Recreate textbox if wordwrap style changed
   If nValue <> _WordWrap Then 
      _WordWrap = nValue
      if this.hWindow then 
         dim as HWND hParent = GetParent(this.hWindow)
         DestroyWindow( this.hWindow )
         this.Show( hParent )
      End If
   end if
end property

Property wfxTextBox.CueBannerText() As CWSTR
   Property = _CueBannerText
End Property

Property wfxTextBox.CueBannerText( ByRef nValue As WString )
   If this.hWindow Then 
      SendMessage(this.hWindow, EM_SETCUEBANNER, 1, CAST(LPARAM, @nValue))
   End If
   _CueBannerText = nValue      
End Property

Property wfxTextBox.PasswordChar() As CWSTR
   Dim As Long iChr = 0
   If this.hWindow Then 
      iChr = SendMessage(this.hWindow, EM_GETPASSWORDCHAR, 0, 0)
   End If
   _PasswordChar = WChr(iChr)      
   Property = _PasswordChar
End Property

Property wfxTextBox.PasswordChar( ByRef nValue As WString )
   Dim As Long iChr = 0
   If Len(nValue) Then iChr = nValue[0]
   If this.hWindow Then 
      SendMessage(this.hWindow, EM_SETPASSWORDCHAR, iChr, 0)
   End If
   _PasswordChar = WChr(iChr)      
End Property

Property wfxTextBox.TextScrollBars() As ScrollBars
   If this.hWindow Then 
      Dim As Long wsStyle = AfxGetWindowStyle(this.hWindow)
      If (wsStyle And (WS_HSCROLL Or WS_VSCROLL) ) Then 
         _TextScrollBars = ScrollBars.Both
      ElseIf (wsStyle And WS_VSCROLL) Then 
         _TextScrollBars = ScrollBars.Vertical
      ElseIf (wsStyle And WS_HSCROLL) Then 
         _TextScrollBars = ScrollBars.Horizontal
      Else
         _TextScrollBars = ScrollBars.None
      End If 
   End If
   Property = _TextScrollBars
End Property

Property wfxTextBox.TextScrollBars( ByVal nValue As ScrollBars )
   If this.hWindow Then 
      AfxRemoveWindowStyle(this.hWindow, WS_HSCROLL)
      AfxRemoveWindowStyle(this.hWindow, WS_VSCROLL)
      Dim As Long wsStyle
      Select Case nValue 
         Case ScrollBars.None
         Case ScrollBars.Both:       wsStyle = (WS_HSCROLL Or WS_VSCROLL)
         Case ScrollBars.Horizontal: wsStyle = WS_HSCROLL
         Case ScrollBars.Vertical:   wsStyle = WS_VSCROLL
      End Select
      AfxAddWindowStyle(this.hWindow, wsStyle)
      this.Refresh
   End If
   _TextScrollBars = nValue
End Property

Property wfxTextBox.SelectionStart() As Long
   Property = Edit_GetSelStart(this.hWindow)
End Property

Property wfxTextBox.SelectionStart( ByVal nValue As Long )
   SendMessage( this.hWindow, EM_SETSEL, nValue, Edit_GetSelEnd(this.hWindow))
End Property

Property wfxTextBox.SelectionLength() As Long
   Property = Edit_GetSelEnd(this.hWindow) - Edit_GetSelStart(this.hWindow)
End Property

Property wfxTextBox.SelectionLength( ByVal nValue As Long )
   SendMessage( this.hWindow, EM_SETSEL, this.SelectionStart, this.SelectionStart + nValue)
End Property

Property wfxTextBox.LinePosition() As Long
   if this.hWindow then
      ' Find out what line we are on, based on the current selection's end
      dim as long nEnd   = Edit_GetSelEnd(this.hWindow) 
      _LinePosition = SendMessage( this.hWindow, EM_EXLINEFROMCHAR, 0, cast(LPARAM, nEnd) )
   end if
   Property = _LinePosition
End Property

Property wfxTextBox.LinePosition( ByVal nValue As Long )
   if this.hWindow then
      dim as long nLineStartPos = SendMessage( this.hWindow, EM_LINEINDEX, nValue, 0 )
      SendMessage( this.hWindow, EM_SETSEL, nLineStartPos, nLineStartPos )
   end if
   _LinePosition = nValue
End Property

Property wfxTextBox.ColumnPosition() As Long
   if this.hWindow then
      ' Find out what line we are on, based on the current selection's end
      dim as long nEnd   = Edit_GetSelEnd(this.hWindow) 
      ' Find the column, from the selection end, minus the char we are on  
      '_ColumnPosition = nEnd - SendMessage( this.hWindow, EM_LINEINDEX, -1, 0 )
      dim as long nLine = SendMessage( this.hWindow, EM_EXLINEFROMCHAR, 0, cast(LPARAM, nEnd) )
      _ColumnPosition = nEnd - SendMessage( this.hWindow, EM_LINEINDEX, nLine, 0 )
   end if
   Property = _ColumnPosition
End Property

Property wfxTextBox.ColumnPosition( ByVal nValue As Long )
   if this.hWindow then
      dim as long nLineStartPos = SendMessage( this.hWindow, EM_LINEINDEX, this.LinePosition, 0 )
      SendMessage( this.hWindow, EM_SETSEL, nLineStartPos + nValue, nLineStartPos + nValue)
   end if
   _ColumnPosition = nValue
End Property


Function wfxTextBox.Show(ByVal hWndParent As HWnd = 0) As Long

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
   
   If _Multiline Then 
      dwStyle = dwStyle Or ES_MULTILINE or ES_AUTOVSCROLL or WS_VSCROLL
      If _AcceptsReturn Then dwStyle = dwStyle Or ES_WANTRETURN 
      If _WordWrap = False Then dwStyle = dwStyle Or ES_AUTOHSCROLL or WS_HSCROLL
      wszClassName = "MULTILINETEXTBOX"
   else   
      dwStyle = dwStyle or ES_AUTOHSCROLL 
      wszClassName = "TEXTBOX"
   end if   
   
   if this.CtrlType = ControlType.RichEdit then
      wszClassName = "RICHEDIT"
   end if
   
   _CtrlID = this.Parent->GetNextCtrlID()

   this.hWindow = this.Parent->pWindow->AddControl ( _
         wszClassName, _                   ' // Class name
         hWndParent, _                     ' // Parent window handle
         _CtrlID, _                        ' // Control identifier (this gets modified when added to controls collection)
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
 
   if this.CtrlType = ControlType.RichEdit then
      SendMessage( this.hWindow, EM_SETEVENTMASK, 0, cast(LPARAM, ENM_SELCHANGE or ENM_CHANGE) )
      SendMessage( this.hWindow, EM_EXLIMITTEXT, 0, cast(LPARAM, 1024000) )  ' 1GB
   end if

   ' Should we enable drag and drop files
   If this.AllowDrop Then DragAcceptFiles(this.hWindow, CTRUE)

   ' Apply properties that require a valid window handle
   this.Font            = _wfxFontPtr
   this.CharacterCasing = _CharacterCasing
   this.ReadOnly        = _ReadOnly
   this.TextScrollBars  = _TextScrollBars
   this.TextAlign       = _TextAlign
   this.BorderStyle     = _BorderStyle
   this.PasswordChar    = _PasswordChar
   this.CueBannerText   = _CueBannerText
   this.ToolTip         = _ToolTip
   this.LinePosition    = _LinePosition
   this.ColumnPosition  = _ColumnPosition
   this.MaxLength       = _MaxLength
   
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




