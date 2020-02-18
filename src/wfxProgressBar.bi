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
''  ProgressBar Class
''
''


Type wfxProgressBar Extends wfxControl
   private:
      _Maximum       As long = 100
      _Minimum       As long = 0
      _StepValue     As long = 1
      _Value         As long = 0
      _Vertical      as Boolean = false
      _Marquee       as Boolean = false
      _MarqueeAnimationSpeed as long = 30   ' update every milliseonds 
      
   Public:
      Declare Constructor( byref wszName as wstring = "" )
      Declare destructor
      Declare Property Maximum() As long
      Declare Property Maximum( ByVal nValue As long )
      Declare Property Minimum() As long
      Declare Property Minimum( ByVal nValue As long )
      Declare Property StepValue() As long
      Declare Property StepValue( ByVal nValue As long )
      Declare Property Value() As long
      Declare Property Value( ByVal nValue As long )
      Declare Property Vertical() As boolean
      Declare Property Vertical( ByVal nValue As boolean )
      Declare Property Marquee() As boolean
      Declare Property Marquee( ByVal nValue As boolean )
      Declare Property MarqueeAnimationSpeed() As long
      Declare Property MarqueeAnimationSpeed( ByVal nValue As long )
      declare function Increment( byval nValue as long ) as Long
      declare function PerformStep() as Long
      declare function StartMarquee( byval nValue as Boolean) as Long
      declare function Show(byval hWndParent as hwnd = 0) as long override

      OnAllEvents        as function( byref sender as wfxProgressBar, byref e as EventArgs ) as LRESULT
      OnDestroy          as function( byref sender as wfxProgressBar, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxProgressBar, byref e as EventArgs ) as LRESULT
      OnMouseMove        as function( byref sender as wfxProgressBar, byref e as EventArgs ) as LRESULT
      OnMouseDown        as function( byref sender as wfxProgressBar, byref e as EventArgs ) as LRESULT
      OnMouseUp          as function( byref sender as wfxProgressBar, byref e as EventArgs ) as LRESULT
      OnMouseDoubleClick as function( byref sender as wfxProgressBar, byref e as EventArgs ) as LRESULT
      OnMouseEnter       as function( byref sender as wfxProgressBar, byref e as EventArgs ) as LRESULT
      OnMouseHover       as function( byref sender as wfxProgressBar, byref e as EventArgs ) as LRESULT
      OnMouseLeave       as function( byref sender as wfxProgressBar, byref e as EventArgs ) as LRESULT
      OnDropFiles        As Function( ByRef sender As wfxProgressBar, ByRef e As EventArgs ) As LRESULT

End Type

