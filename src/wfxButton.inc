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
''  Button Class
''

#include once "wfxButton.bi"

constructor wfxButton( byref wszName as wstring = "" )
   this.CtrlType = ControlType.Button
   this.Name = wszName
   this.BackColor = Colors.SystemControl
End Constructor

Destructor wfxButton()
   if _XpButtonPtr then Delete _XpButtonPtr
   _XpButtonPtr = 0
End Destructor

Property wfxButton.AllowFocusRect() As boolean 
   If _XpButtonPtr Then 
      _AllowFocusRect = _XpButtonPtr->GetAllowFocusRect
   End If
   Property = _AllowFocusRect
End Property

Property wfxButton.AllowFocusRect( ByVal nValue As boolean )
   If _XpButtonPtr Then 
      _XpButtonPtr->SetAllowFocusRect(nValue)
   End If
   _AllowFocusRect = nValue
End Property

Property wfxButton.MultiLine() As boolean 
   Property = _MultiLine
End Property

Property wfxButton.MultiLine( ByVal nValue As boolean )
   _MultiLine = nValue
   If _XpButtonPtr Then 
      ' Force the button to redraw with new multiline or singleline setting
      this.TextAlign = this.TextAlign
   end if
End Property

Property wfxButton.ToggleMode() As boolean 
   If _XpButtonPtr Then 
      _ToggleMode = cbool(_XpButtonPtr->GetToggle)
   End If
   Property = _ToggleMode   
End Property

Property wfxButton.ToggleMode( ByVal nValue As boolean )
   If _XpButtonPtr Then 
      _XpButtonPtr->SetToggle(nValue)
   End If
   _ToggleMode = nValue
End Property

Property wfxButton.ToggleState() As boolean 
   If _XpButtonPtr Then 
      _ToggleState = cbool(_XpButtonPtr->GetToggleState)
   End If
   Property = _ToggleState
End Property

Property wfxButton.ToggleState( ByVal nValue As boolean )
   If _XpButtonPtr Then 
      _XpButtonPtr->SetToggleState(nValue, True)
   End If
   _ToggleState = nValue
End Property

Property wfxButton.ThemeSupport() As boolean 
   If _XpButtonPtr Then 
      _ThemeSupport = _XpButtonPtr->IsThemed
   End If
   Property = _ThemeSupport   
End Property

Property wfxButton.ThemeSupport( ByVal nValue As boolean )
   If _XpButtonPtr Then 
      If nValue Then 
         _XpButtonPtr->EnableTheming
      Else
         _XpButtonPtr->DisableTheming
      End If
   End If
   _ThemeSupport = nValue
End Property

Property wfxButton.TextForeColor( ByVal nValue As COLORREF )
   If _XpButtonPtr Then 
      _XpButtonPtr->SetTextForeColor(nValue, True)
   End If
   _TextForeColor = nValue
End Property

Property wfxButton.TextForeColor() As COLORREF
   If _XpButtonPtr Then 
      _TextForeColor = _XpButtonPtr->GetTextForeColor
   End If
   Property = _TextForeColor 
End Property

Property wfxButton.TextForeColorHot( ByVal nValue As COLORREF )
   If _XpButtonPtr Then 
      _XpButtonPtr->SetTextForeColorHot(nValue, True)
   End If
   _TextForeColorHot = nValue
End Property

Property wfxButton.TextForeColorHot() As COLORREF
   If _XpButtonPtr Then 
      _TextForeColorHot = _XpButtonPtr->GetTextForeColorHot
   End If
   Property = _TextForeColorHot 
End Property

Property wfxButton.TextForeColorDown( ByVal nValue As COLORREF )
   If _XpButtonPtr Then 
      _XpButtonPtr->SetTextForeColorDown(nValue, True)
   End If
   _TextForeColorDown = nValue
End Property

Property wfxButton.TextForeColorDown() As COLORREF
   If _XpButtonPtr Then 
      _TextForeColorDown = _XpButtonPtr->GetTextForeColorDown
   End If
   Property = _TextForeColorDown 
End Property

Property wfxButton.TextBackColor( ByVal nValue As COLORREF )
   If _XpButtonPtr Then 
      _XpButtonPtr->SetTextBkColor(nValue, True)
   End If
   _TextBackColor = nValue
End Property

Property wfxButton.TextBackColor() As COLORREF
   If _XpButtonPtr Then 
      _TextBackColor = _XpButtonPtr->GetTextBkColor
   End If
   Property = _TextBackColor 
End Property

Property wfxButton.TextBackColorDown( ByVal nValue As COLORREF )
   If _XpButtonPtr Then 
      _XpButtonPtr->SetTextBkColorDown(nValue, True)
   End If
   _TextBackColorDown = nValue
End Property

Property wfxButton.TextBackColorDown() As COLORREF
   If _XpButtonPtr Then 
      _TextBackColorDown = _XpButtonPtr->GetTextBkColorDown
   End If
   Property = _TextBackColorDown 
End Property

Property wfxButton.BackColor( ByVal nValue As COLORREF )
   If _XpButtonPtr Then 
      _XpButtonPtr->SetButtonBkColor(nValue, True)
   End If
   _BackColor = nValue
End Property

Property wfxButton.BackColor() As COLORREF 
   If _XpButtonPtr Then 
      _BackColor = _XpButtonPtr->GetButtonBkColor
   End If
   Property = _BackColor 
End Property

Property wfxButton.BackColorDown( ByVal nValue As COLORREF )
   If _XpButtonPtr Then 
      _XpButtonPtr->SetButtonBkColorDown(nValue, True)
   End If
   _BackColorDown = nValue
End Property

Property wfxButton.BackColorDown() As COLORREF 
   If _XpButtonPtr Then 
      _BackColorDown = _XpButtonPtr->GetButtonBkColorDown
   End If
   Property = _BackColorDown 
End Property

Property wfxButton.BackColorHot( ByVal nValue As COLORREF )
   If _XpButtonPtr Then 
      _XpButtonPtr->SetButtonBkColorHot(nValue, True)
   End If
   _BackColorHot = nValue
End Property

Property wfxButton.BackColorHot() As COLORREF 
   If _XpButtonPtr Then 
      _BackColorHot = _XpButtonPtr->GetButtonBkColorHot
   End If
   Property = _BackColorHot
End Property

Property wfxButton.TextAlign( ByVal nValue As ButtonAlignment )
   If _XpButtonPtr Then 
      Dim As Long wsStyle
      Select case nValue
         case ButtonAlignment.BottomCenter: wsStyle = DT_CENTER Or DT_BOTTOM
         case ButtonAlignment.BottomLeft:   wsStyle = DT_LEFT   Or DT_BOTTOM
         case ButtonAlignment.BottomRight:  wsStyle = DT_RIGHT  Or DT_BOTTOM
         case ButtonAlignment.MiddleCenter: wsStyle = DT_CENTER Or DT_VCENTER
         case ButtonAlignment.MiddleLeft:   wsStyle = DT_LEFT   Or DT_VCENTER
         case ButtonAlignment.MiddleRight:  wsStyle = DT_RIGHT  Or DT_VCENTER
         case ButtonAlignment.TopCenter:    wsStyle = DT_CENTER Or DT_TOP
         case ButtonAlignment.TopLeft:      wsStyle = DT_LEFT   Or DT_TOP
         case ButtonAlignment.TopRight:     wsStyle = DT_RIGHT  Or DT_TOP
      End Select

      if _MultiLine then
         _XpButtonPtr->SetTextFormat(wsStyle Or DT_WORDBREAK, True)
         ' Convert any embedded {br} identifiers to chr(10) LF.
         dim as CWSTR wszText = this.Text
         this.Text = AfxStrReplace( wszText, "{br}", chr(10) )
      else
         _XpButtonPtr->SetTextFormat(wsStyle Or DT_SINGLELINE, True)
      end if   
   End If
   _TextAlign = nValue
end property

Property wfxButton.TextAlign() As ButtonAlignment 
   If _XpButtonPtr Then 
      Dim As Long wsStyle
      wsStyle = _XpButtonPtr->GetTextFormat
      If wsStyle And (DT_CENTER Or DT_BOTTOM)  Then Return ButtonAlignment.BottomCenter
      If wsStyle And (DT_LEFT Or DT_BOTTOM)    Then Return ButtonAlignment.BottomLeft   
      If wsStyle And (DT_RIGHT Or DT_BOTTOM)   Then Return ButtonAlignment.BottomRight  
      If wsStyle And (DT_CENTER Or DT_VCENTER) Then Return ButtonAlignment.MiddleCenter 
      If wsStyle And (DT_LEFT Or DT_VCENTER)   Then Return ButtonAlignment.MiddleLeft   
      If wsStyle And (DT_RIGHT Or DT_VCENTER)  Then Return ButtonAlignment.MiddleRight  
      If wsStyle And (DT_CENTER Or DT_TOP)     Then Return ButtonAlignment.TopCenter    
      If wsStyle And (DT_LEFT Or DT_TOP)       Then Return ButtonAlignment.TopLeft      
      If wsStyle And (DT_RIGHT Or DT_TOP)      Then Return ButtonAlignment.TopRight     
   Else
      Return _TextAlign
   End If
End Property

property wfxButton.Image() as CWSTR
   property = _Image
end property

property wfxButton.Image( byref cwzValue as wstring )
   If _XpButtonPtr Then 
      If len(cwzValue) Then
         if this.Parent->pWindow then
            _XpButtonPtr->SetImageFromRes( this.Parent->pWindow->InstanceHandle, cwzValue )
            ' Ensure that the image honors the HighDPI setting for the button.
            this.ImageHighDPI = _ImageHighDPI
         end if   
      End If    
   End If
   _Image = cwzValue
end property

Property wfxButton.ImageAlign( ByVal nValue As ImageAlignment )
   If _XpButtonPtr Then 
      Dim As Long wsStyle
      Select Case nValue
         case ImageAlignment.BottomCenter: wsStyle = &H20 OR &H4
         case ImageAlignment.BottomLeft:   wsStyle = &H20 OR &H1
         case ImageAlignment.BottomRight:  wsStyle = &H20 OR &H2
         case ImageAlignment.MiddleCenter: wsStyle = &H8  OR &H4    ' no text 
         case ImageAlignment.MiddleLeft:   wsStyle = &H8  OR &H1
         case ImageAlignment.MiddleRight:  wsStyle = &H8  OR &H2
         case ImageAlignment.TopCenter:    wsStyle = &H10 OR &H4
         case ImageAlignment.TopLeft:      wsStyle = &H10 OR &H1
         case ImageAlignment.TopRight:     wsStyle = &H10 OR &H2
      End Select

      _XpButtonPtr->SetImagePos(wsStyle, True)
   End If
   _ImageAlign = nValue
end property

Property wfxButton.ImageAlign() As ImageAlignment 
   If _XpButtonPtr Then 
      Dim As Long wsStyle
      wsStyle = _XpButtonPtr->GetImagePos
      if wsStyle = &H20 OR &H4 then return ImageAlignment.BottomCenter
      if wsStyle = &H20 OR &H1 then return ImageAlignment.BottomLeft
      if wsStyle = &H20 OR &H2 then return ImageAlignment.BottomRight
      if wsStyle = &H8  OR &H4 then return ImageAlignment.MiddleCenter     ' no text 
      if wsStyle = &H8  OR &H1 then return ImageAlignment.MiddleLeft   
      if wsStyle = &H8  OR &H2 then return ImageAlignment.MiddleRight  
      if wsStyle = &H10 OR &H4 then return ImageAlignment.TopCenter    
      if wsStyle = &H10 OR &H1 then return ImageAlignment.TopLeft      
      if wsStyle = &H10 OR &H2 then return ImageAlignment.TopRight     
   Else
      Return _ImageAlign
   End If
End Property

property wfxButton.ImageHighDPI( byval nValue as boolean )
   If _XpButtonPtr Then 
      if nValue then 
         if this.Parent->pWindow then
            _XpButtonPtr->SetImageSize( this.Parent->pWindow->ScaleX(_ImageWidth), _
                                        this.Parent->pWindow->ScaleY(_ImageHeight), true )
         end if
      else
         _XpButtonPtr->SetImageSize( _ImageWidth, _ImageHeight, true )
      end if
   end if
   _ImageHighDPI = nValue
end property

property wfxButton.ImageHighDPI() as boolean
   property = _ImageHighDPI
end property

property wfxButton.ImageWidth( byval nValue as Long )
   If _XpButtonPtr Then 
      _XpButtonPtr->SetImageWidth( nValue )
   End If
   _ImageWidth = nValue
end property

property wfxButton.ImageWidth() as Long
   If _XpButtonPtr Then 
      _ImageWidth = _XpButtonPtr->GetImageWidth()
   End If
   property = _ImageWidth
end property

property wfxButton.ImageHeight( byval nValue as Long )
   If _XpButtonPtr Then 
      _XpButtonPtr->SetImageHeight( nValue )
   End If
   _ImageHeight = nValue
end property

property wfxButton.ImageHeight() as Long
   If _XpButtonPtr Then 
      _ImageHeight = _XpButtonPtr->GetImageHeight()
   End If
   property = _ImageHeight
end property

property wfxButton.ImageMargin( byval nValue as Long )
   If _XpButtonPtr Then 
      _XpButtonPtr->SetImageMargin( nValue )
   End If
   _ImageMargin = nValue
end property

property wfxButton.ImageMargin() as Long
   If _XpButtonPtr Then 
      _ImageMargin = _XpButtonPtr->GetImageMargin()
   End If
   property = _ImageMargin
end property

property wfxButton.TextMargin( byval nValue as Long )
   If _XpButtonPtr Then 
      _XpButtonPtr->SetTextMargin( nValue )
   End If
   _TextMargin = nValue
end property

property wfxButton.TextMargin() as Long
   If _XpButtonPtr Then 
      _TextMargin = _XpButtonPtr->GetTextMargin()
   End If
   property = _TextMargin
end property


Function wfxButton.Show(ByVal hWndParent As HWnd = 0) As Long

   ' If the control is created but simply hidden, then show it.
   if this.hWindow THEN
      ShowWindow(this.hWindow, SW_SHOW)
      exit function
   END IF

   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function
      
   dim as long dwExStyle = 0
   dim as long dwStyle = BS_PUSHBUTTON OR BS_CENTER OR BS_VCENTER
   if this.TabStop then dwStyle = dwStyle OR WS_TABSTOP 
   if this.Visible THEN dwStyle = dwStyle OR WS_VISIBLE
   
   Dim pWindow As CWindow Ptr = AfxCWindowPtr(hWndParent)

   ' Use the custom control CXpButton instead of the standard Windows button control.
   _CtrlID = this.Parent->GetNextCtrlID()
   _XpButtonPtr = New CXpButton(pWindow, _CtrlID, this.Text, this.Left, this.top, this.Width, this.height, dwStyle )
   this.hWindow = _XpButtonPtr->hWindow
   SetWindowSubclass(this.hWindow, Cast(SUBCLASSPROC, @wfxApplication.SubclassProc), _CtrlID, Cast(DWORD_PTR, 0))

   ' Should we enable drag and drop files
   If this.AllowDrop Then DragAcceptFiles(this.hWindow, CTRUE)

   ' Apply the properties
   this.ThemeSupport      = _ThemeSupport
   this.AllowFocusRect    = _AllowFocusRect
   this.ImageAlign         = _ImageAlign
   this.TextAlign         = _TextAlign
   this.BackColor         = _BackColor
   this.BackColorDown     = _BackColorDown
   this.BackColorHot      = _BackColorHot
   this.TextForeColor     = _TextForeColor
   this.TextForeColorHot  = _TextForeColorHot
   this.TextForeColorDown = _TextForeColorDown
   this.TextBackColor     = _TextBackColor
   this.TextBackColorDown = _TextBackColorDown
   this.ToggleMode        = _ToggleMode
   this.Font              = _wfxFontPtr
   
   ' Do not set the focus/selected here because doing so will also Activate the form and
   ' cause an Activated message to be fired. We want the Form's Load event to
   ' complete before any Activate message.
   ' Refer to wfxForm.CreateFormInternal for the setting of the focus/selected
   ' control once events have fired correctly.

   ' Store the hWindow in the form's linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   dim pNode as wfxLListNode ptr = this.Parent->Controls.search_data(@this)
   if pNode then pNode->hWindow = this.hWindow
      
   this.Image        = _Image
   this.ImageWidth   = _ImageWidth
   this.ImageHeight  = _ImageHeight
   this.ImageHighDPI = _ImageHighDPI
   this.ImageMargin  = _ImageMargin
   this.TextMargin   = _TextMargin
   this.Enabled      = _Enabled
   this.ToolTip      = _ToolTip
   
   function = 0
END FUNCTION



