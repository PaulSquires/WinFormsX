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
''  MonthCalendar Class
''

#include once "wfxMonthCalendar.bi"


constructor wfxMonthCalendar( byref wszName as wstring = "" )
   this.CtrlType = ControlType.MonthCalendar
   this.Name = wszName
   this.BackColor = Colors.SystemControl
end constructor

Property wfxMonthCalendar.SelectedDate() As CWSTR
   if this.hWindow then 
      Dim As SYSTEMTIME pst
      MonthCal_GetCurSel( this.hWindow, @pst )
      ' make sure that the string being returned is 8 length
      _SelectedDate = _
         AfxStrRSet( wstr(pst.wYear),  4, "0" )  & _
         AfxStrRSet( wstr(pst.wMonth), 2, "0" ) & _
         AfxStrRSet( wstr(pst.wDay),   2, "0" )
   End If
   Property = _SelectedDate
end property

Property wfxMonthCalendar.SelectedDate( Byref wszValue As wstring )
   if this.hWindow then 
      ' The incoming date string should be in the format YYYYMMDD
      Dim As SYSTEMTIME pst
      pst.wYear  = val(mid(wszValue, 1, 4))
      pst.wMonth = val(mid(wszValue, 5, 2))
      pst.wDay   = val(right(wszValue, 2))
      MonthCal_SetCurSel( this.hWindow, @pst )
   end if
   _SelectedDate = wszValue
end property


Property wfxMonthCalendar.WeekNumbers() As boolean
   if this.hWindow then 
      _WeekNumbers = Iif( (AfxGetWindowStyle(this.hWindow) And MCS_WEEKNUMBERS), True, False)
   end if
   property = _WeekNumbers
end property

property wfxMonthCalendar.WeekNumbers( byval nValue as boolean )
   if this.hWindow then 
      If nValue Then 
         AfxAddWindowStyle(this.hWindow, MCS_WEEKNUMBERS)
      else
         AfxRemoveWindowStyle(this.hWindow, MCS_WEEKNUMBERS)
      end if   
      this.Refresh  
   end if
   _WeekNumbers = nValue
end property

Property wfxMonthCalendar.TodayCircle() As boolean
   if this.hWindow then 
      _TodayCircle = Iif( (AfxGetWindowStyle(this.hWindow) And MCS_NOTODAYCIRCLE), False, true)
   end if
   property = _TodayCircle
end property

property wfxMonthCalendar.TodayCircle( byval nValue as boolean )
   if this.hWindow then 
      If nValue Then 
         AfxRemoveWindowStyle(this.hWindow, MCS_NOTODAYCIRCLE)
      else
         AfxAddWindowStyle(this.hWindow, MCS_NOTODAYCIRCLE)
      end if   
      this.Refresh  
   end if
   _TodayCircle = nValue
end property

Property wfxMonthCalendar.TodaySelector() As boolean
   if this.hWindow then 
      _TodaySelector = Iif( (AfxGetWindowStyle(this.hWindow) And MCS_NOTODAY), False, true)
   end if
   property = _TodaySelector
end property

property wfxMonthCalendar.TodaySelector( byval nValue as boolean )
   if this.hWindow then 
      If nValue Then 
         AfxRemoveWindowStyle(this.hWindow, MCS_NOTODAY)
      else
         AfxAddWindowStyle(this.hWindow, MCS_NOTODAY)
      end if   
      this.Refresh  
   end if
   _TodaySelector = nValue
end property

Property wfxMonthCalendar.TrailingDates() As boolean
   if this.hWindow then 
      _TrailingDates = Iif( (AfxGetWindowStyle(this.hWindow) And MCS_NOTRAILINGDATES), False, true)
   end if
   property = _TrailingDates
end property

property wfxMonthCalendar.TrailingDates( byval nValue as boolean )
   if this.hWindow then 
      If nValue Then 
         AfxRemoveWindowStyle(this.hWindow, MCS_NOTRAILINGDATES)
      else
         AfxAddWindowStyle(this.hWindow, MCS_NOTRAILINGDATES)
      end if   
      this.Refresh  
   end if
   _TrailingDates = nValue
end property

Property wfxMonthCalendar.ShortDayNames() As boolean
   if this.hWindow then 
      _ShortDayNames = Iif( (AfxGetWindowStyle(this.hWindow) And MCS_SHORTDAYSOFWEEK), true, false)
   end if
   property = _ShortDayNames
end property

property wfxMonthCalendar.ShortDayNames( byval nValue as boolean )
   if this.hWindow then 
      If nValue Then 
         AfxAddWindowStyle(this.hWindow, MCS_SHORTDAYSOFWEEK)
      else
         AfxRemoveWindowStyle(this.hWindow, MCS_SHORTDAYSOFWEEK)
      end if   
      this.Refresh  
   end if
   _ShortDayNames = nValue
end property

Property wfxMonthCalendar.BackColor() As COLORREF
   if this.hWindow then 
      _BackColor = MonthCal_GetColor( this.hWindow, MCSC_BACKGROUND )
   end if
   property = _BackColor
end property

property wfxMonthCalendar.BackColor( byval nValue as COLORREF )
   if this.hWindow then 
      MonthCal_SetColor( this.hWindow, MCSC_BACKGROUND, nValue )
   end if
   _BackColor = nValue
end property



Function wfxMonthCalendar.Show(ByVal hWndParent As HWnd = 0) As Long

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
   
   dwStyle = dwStyle or MCS_DAYSTATE    ' always allow the MCN_GETDAYSTATE notification to fire
   
   If _WeekNumbers   Then dwStyle = dwStyle Or MCS_WEEKNUMBERS
   If _ShortDayNames Then dwStyle = dwStyle Or MCS_SHORTDAYSOFWEEK
   If _TodayCircle   = false Then dwStyle = dwStyle Or MCS_NOTODAYCIRCLE
   If _TodaySelector = false Then dwStyle = dwStyle Or MCS_NOTODAY
   If _TrailingDates = false Then dwStyle = dwStyle Or MCS_NOTRAILINGDATES

   _CtrlID = this.Parent->GetNextCtrlID()

   this.hWindow = this.Parent->pWindow->AddControl ( _
         "SYSMONTHCAL32", _                ' // Class name
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
   this.Font      = _wfxFontPtr
   this.BackColor = _BackColor
   this.SelectedDate = _SelectedDate 
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




