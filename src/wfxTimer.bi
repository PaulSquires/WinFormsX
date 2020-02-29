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


Type wfxTimer Extends wfxControl
   private:
      _TimerID   as Long
      _Interval  as Long = 1000
      _Enabled   as Boolean = false
      _AutoReset as Boolean = true
      
   Public:
      Declare Constructor( ByRef wszName As WString = "" )
      Declare Property TimerID() As Long
      Declare Property TimerID( ByVal nValue As Long )
      declare property Interval() as Long    
      declare property Interval( byval nValue as long )  ' milliseconds
      Declare Property Enabled() As boolean
      Declare Property Enabled( ByVal nValue As Boolean)
      Declare Property AutoReset() As boolean
      Declare Property AutoReset( ByVal nValue As Boolean)
      
      declare function StartTimer() as Long
      declare function StopTimer() as Long
      declare function Show(byval hWndParent as hwnd = 0) as long override
        
      OnAllEvents        as function( byref sender as wfxTimer, byref e as EventArgs ) as LRESULT
      OnDestroy          as function( byref sender as wfxTimer, byref e as EventArgs ) as LRESULT
      OnElapsed          as function( byref sender as wfxTimer, byref e as EventArgs ) as LRESULT
End Type

