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


Type wfxMonthCalendar Extends wfxControl
      _SelectedDate    As CWSTR
      _WeekNumbers     As Boolean = False
      _TodayCircle     As Boolean = true
      _TodaySelector   As boolean = true
      _TrailingDates   As boolean = true
      _ShortDayNames   As boolean = false
      _BackColor       As COLORREF = Colors.SystemControl

   Public:
      declare Property BackColor() As COLORREF
      declare property BackColor( byval nValue as COLORREF )
      Declare Property SelectedDate() As CWSTR
      Declare Property SelectedDate( Byref wszValue As wstring )
      Declare Property WeekNumbers() As boolean
      Declare Property WeekNumbers( ByVal nValue As boolean )
      Declare Property TodayCircle() As boolean
      Declare Property TodayCircle( ByVal nValue As boolean )
      Declare Property TodaySelector() As boolean
      Declare Property TodaySelector( ByVal nValue As boolean )
      Declare Property TrailingDates() As boolean
      Declare Property TrailingDates( ByVal nValue As boolean )
      Declare Property ShortDayNames() As boolean
      Declare Property ShortDayNames( ByVal nValue As boolean )

      Declare Function Show(ByVal hWndParent As HWnd = 0) As Long Override
      Declare Constructor( byref wszName as wstring = "" )

      OnAllEvents        as function( byref sender as wfxMonthCalendar, byref e as EventArgs ) as LRESULT
      OnDestroy          as function( byref sender as wfxMonthCalendar, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxMonthCalendar, byref e as EventArgs ) as LRESULT
      OnGotFocus         as function( byref sender as wfxMonthCalendar, byref e as EventArgs ) as LRESULT
      OnLostFocus        as function( byref sender as wfxMonthCalendar, byref e as EventArgs ) as LRESULT
      OnMouseMove        as function( byref sender as wfxMonthCalendar, byref e as EventArgs ) as LRESULT
      OnMouseDown        as function( byref sender as wfxMonthCalendar, byref e as EventArgs ) as LRESULT
      OnMouseUp          as function( byref sender as wfxMonthCalendar, byref e as EventArgs ) as LRESULT
      OnMouseDoubleClick as function( byref sender as wfxMonthCalendar, byref e as EventArgs ) as LRESULT
      OnMouseEnter       as function( byref sender as wfxMonthCalendar, byref e as EventArgs ) as LRESULT
      OnMouseHover       as function( byref sender as wfxMonthCalendar, byref e as EventArgs ) as LRESULT
      OnMouseLeave       as function( byref sender as wfxMonthCalendar, byref e as EventArgs ) as LRESULT
      OnSelectionChanged As Function( ByRef sender As wfxMonthCalendar, ByRef e As EventArgs ) As LRESULT
      OnKeyDown          As Function( ByRef sender As wfxMonthCalendar, ByRef e As EventArgs ) As LRESULT
      OnKeyPress         as function( byref sender as wfxMonthCalendar, byref e as EventArgs ) as LRESULT
      OnKeyUp            as function( byref sender as wfxMonthCalendar, byref e as EventArgs ) as LRESULT
      OnDropFiles        As Function( ByRef sender As wfxMonthCalendar, ByRef e As EventArgs ) As LRESULT
End Type

