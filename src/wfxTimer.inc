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
''  Timer Class
''
''

#include once "wfxTimer.bi"

constructor wfxTimer( byref wszName as wstring = "" )
   this.CtrlType = ControlType.Timer
   this.Name = wszName
end constructor

property wfxTimer.TimerID() as Long
   property = _TimerID
end property

property wfxTimer.TimerID( byval nValue as long ) 
   _TimerID = nValue
end property

property wfxTimer.Interval() as Long
   property = _Interval
end property

property wfxTimer.Interval( byval nValue as long ) 
   ' If a running timer already exists and the interval is changed, then
   ' kill the existing timer and start running the new timer.
   if nValue <> _Interval then
      this.StopTimer
      _Interval = nValue
      this.StartTimer
   end if   
   _Interval = nValue
end property

Property wfxTimer.AutoReset() As Boolean
   property = _AutoReset
end property

property wfxTimer.AutoReset( byval nValue as Boolean )
   _AutoReset = nValue
end property

Property wfxTimer.Enabled() As Boolean
   property = _Enabled 
end property

property wfxTimer.Enabled( byval nValue as Boolean )
   _Enabled = nValue
   if _Enabled then 
      this.StartTimer
   else
      this.StopTimer
   end if
end property

function wfxTimer.StartTimer() as Long
   ' Create a timer that fires every Interval period.
   SetTimer( this.Parent->hWindow, _         ' window handle to form
             this.TimerID, _                 ' timer identifier 
             this.Interval, _                ' millisecond interval 
             cast(TIMERPROC, @wfxApplication.TimerProc) )  ' timer callback   
   function = 0
end function

function wfxTimer.StopTimer() as Long
   ' Kill the timer that was previously created.
   KillTimer( this.Parent->hWindow, this.TimerID )
   function = 0
end function


Function wfxTimer.Show(ByVal hWndParent As HWnd = 0) As Long

   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function
      
   _TimerID = this.Parent->GetNextCtrlID()
   this.Enabled = _Enabled

   ' Timers do not have hWindow but are stored in the form's linked list 
   ' in order to allow for traversing all "controls" related to the form.
   ' No need to update the linked list with a zero window handle.
      
   function = 0
END FUNCTION



