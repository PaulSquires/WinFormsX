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
''  DateTimePicker Class
''

#include once "wfxDateTimePicker.bi"


constructor wfxDateTimePicker( byref wszName as wstring = "" )
   this.CtrlType = ControlType.DateTimePicker
   this.Name = wszName
   this.BackColor = Colors.SystemWindow
end constructor

Property wfxDateTimePicker.FormatCustom() As CWSTR
   Property = _FormatCustom
end property

Property wfxDateTimePicker.FormatCustom( Byref wszValue As wstring )
   if this.hWindow then 
      if _DateFormat = DateTimePickerFormat.CustomFormat then
         dim wszCustomFormat as wstring * MAX_PATH = wszValue
         DateTime_SetFormat( this.hWindow, @wszCustomFormat )      
      end if
   end if
   _FormatCustom = wszValue
end property

Property wfxDateTimePicker.SelectedDate() As CWSTR
   if this.hWindow then 
      Dim As SYSTEMTIME st
      DateTime_GetSystemTime( this.hWindow, @st )
      ' make sure that the string being returned is 8 length
      _SelectedDate = _
         AfxStrRSet( wstr(st.wYear),  4, "0" ) & _
         AfxStrRSet( wstr(st.wMonth), 2, "0" ) & _
         AfxStrRSet( wstr(st.wDay),   2, "0" )
   End If
   Property = _SelectedDate
end property

Property wfxDateTimePicker.SelectedDate( Byref wszValue As wstring )
   if this.hWindow then 
      ' The incoming date string should be in the format YYYYMMDD
      Dim As SYSTEMTIME st
      st.wYear  = val(mid(wszValue, 1, 4))
      st.wMonth = val(mid(wszValue, 5, 2))
      st.wDay   = val(right(wszValue, 2))
      dim as CWSTR wszTime = this.SelectedTime
      st.wHour   = val(mid(wszTime, 1, 2))
      st.wSecond = val(mid(wszTime, 3, 2))
      st.wMinute = val(right(wszTime, 2))
      DateTime_SetSystemTime( this.hWindow, GDT_VALID, @st )
   end if
   _SelectedDate = wszValue
end property

Property wfxDateTimePicker.SelectedTime() As CWSTR
   if this.hWindow then 
      Dim As SYSTEMTIME st
      DateTime_GetSystemTime( this.hWindow, @st )
      ' make sure that the string being returned is 6 length
      _SelectedTime = _
         AfxStrRSet( wstr(st.wHour),   2, "0" ) & _
         AfxStrRSet( wstr(st.wMinute), 2, "0" ) & _
         AfxStrRSet( wstr(st.wSecond), 2, "0" )
   End If
   Property = _SelectedTime
end property

Property wfxDateTimePicker.SelectedTime( Byref wszValue As wstring )
   if this.hWindow then 
      Dim As SYSTEMTIME st
      dim as CWSTR wszDate = this.SelectedDate
      st.wYear  = val(mid(wszDate, 1, 4))
      st.wMonth = val(mid(wszDate, 5, 2))
      st.wDay   = val(right(wszDate, 2))
      ' The incoming date string should be in the format HHMMSS
      st.wHour   = val(mid(wszValue, 1, 2))
      st.wMinute = val(mid(wszValue, 3, 2))
      st.wSecond = val(right(wszValue, 2))
      DateTime_SetSystemTime( this.hWindow, GDT_VALID, @st )
   end if
   _SelectedTime = wszValue
end property


Property wfxDateTimePicker.CalendarRightAlign() As boolean
   if this.hWindow then 
      _RightAlign = Iif( (AfxGetWindowStyle(this.hWindow) And DTS_RIGHTALIGN), True, False)
   end if
   property = _RightAlign
end property

property wfxDateTimePicker.CalendarRightAlign( byval nValue as boolean )
   if this.hWindow then 
      If nValue Then 
         AfxAddWindowStyle(this.hWindow, DTS_RIGHTALIGN)
      else
         AfxRemoveWindowStyle(this.hWindow, DTS_RIGHTALIGN)
      end if   
      this.Refresh  
   end if
   _RightAlign = nValue
end property

Property wfxDateTimePicker.ShowUpDown() As boolean
   if this.hWindow then 
      _ShowUpDown = Iif( (AfxGetWindowStyle(this.hWindow) And DTS_UPDOWN), true, false)
   end if
   property = _ShowUpDown
end property

property wfxDateTimePicker.ShowUpDown( byval nValue as boolean )
   if this.hWindow then 
      ' Apparently this style can not be changed after control creation.      
      If nValue Then 
         AfxAddWindowStyle(this.hWindow, DTS_UPDOWN)
      else
         AfxRemoveWindowStyle(this.hWindow, DTS_UPDOWN)
      end if   
      this.Refresh  
   end if
   _ShowUpDown = nValue
end property


Property wfxDateTimePicker.DateFormat() As DateTimePickerFormat
   if this.hWindow then 
      dim as DWORD dwStyle = AfxGetWindowStyle(this.hWindow)
      if (dwStyle And DTS_LONGDATEFORMAT) then
         _DateFormat = DateTimePickerFormat.LongDate
      elseif (dwStyle And DTS_SHORTDATEFORMAT) then
         _DateFormat = DateTimePickerFormat.ShortDate
      elseif (dwStyle And DTS_SHORTDATECENTURYFORMAT) then
         _DateFormat = DateTimePickerFormat.ShortDateCentury
      elseif (dwStyle And DTS_TIMEFORMAT) then
         _DateFormat = DateTimePickerFormat.TimeFormat
      else
         _DateFormat = DateTimePickerFormat.CustomFormat
      end if
   end if
   property = _DateFormat
end property   

Property wfxDateTimePicker.DateFormat( ByVal nValue As DateTimePickerFormat )
   _DateFormat = nValue
   if this.hWindow then
      ' Need to rebuild the control
      dim as long nCtrlID = this.CtrlID
      dim as boolean bVisible = this.Visible
      dim as hwnd hParent = GetParent(this.hWindow)
      DestroyWindow( this.hWindow )
      this.Show(hParent)
      this.CtrlID = nCtrlID
      this.Visible = bVisible
   end if
end property


Function wfxDateTimePicker.Show(ByVal hWndParent As HWnd = 0) As Long

   ' If the control is created but simply hidden, then show it.
   if this.hWindow THEN
      ShowWindow(this.hWindow, SW_SHOW)
      exit function
   END IF

   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function
      
   Dim As DWORD dwStyle, dwExStyle
   
   if _TabStop then dwStyle = dwStyle OR WS_TABSTOP 
   If _Visible Then dwStyle = dwStyle Or WS_VISIBLE
   
   If _ShowUpDown Then dwStyle = dwStyle Or DTS_UPDOWN
   If _RightAlign Then dwStyle = dwStyle Or DTS_RIGHTALIGN
   
   select case _DateFormat
      case DateTimePickerFormat.LongDate
         dwStyle = dwStyle Or DTS_LONGDATEFORMAT
      case DateTimePickerFormat.ShortDate
         dwStyle = dwStyle Or DTS_SHORTDATEFORMAT
      case DateTimePickerFormat.ShortDateCentury
         dwStyle = dwStyle Or DTS_SHORTDATECENTURYFORMAT
      case DateTimePickerFormat.TimeFormat
         dwStyle = dwStyle Or DTS_TIMEFORMAT
      case DateTimePickerFormat.CustomFormat
         ' Set value after control is created
   end select

   _CtrlID = this.Parent->GetNextCtrlID()

   this.hWindow = this.Parent->pWindow->AddControl ( _
         "SysDateTimePick32", _            ' // Class name
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
 
   ' Should we enable drag and drop files
   If this.AllowDrop Then DragAcceptFiles(this.hWindow, CTRUE)

   ' Apply properties that require a valid window handle
   this.Font         = _wfxFontPtr
   this.FormatCustom = _FormatCustom
   ' Save _SelectedTime because this.SelectDate will reset it
   dim as CWSTR wszSave = _SelectedTime
   this.SelectedDate = _SelectedDate 
   _SelectedTime = wszSave
   this.SelectedTime = _SelectedTime

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




