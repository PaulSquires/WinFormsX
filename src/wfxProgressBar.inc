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

#include once "wfxProgressBar.bi"

constructor wfxProgressBar( byref wszName as wstring = "" )
   this.CtrlType = ControlType.ProgressBar
   this.Name = wszName
End Constructor

destructor wfxProgressBar()
   ''
End Destructor


property wfxProgressBar.Maximum() as long
   if this.hWindow then 
      _Maximum = ProgressBar_GetMaxRange( this.hWindow )
   end if
   property = _Maximum
end property

property wfxProgressBar.Maximum( byval nValue as long )
   _Maximum = nValue   
   if this.hWindow then 
      _Minimum = ProgressBar_GetMinRange( this.hWindow )
      ProgressBar_SetRange32( this.hWindow, _Minimum, _Maximum )
   end if
end property

property wfxProgressBar.Minimum() as long
   if this.hWindow then 
      _Minimum = ProgressBar_GetMinRange( this.hWindow )
   end if
   property = _Minimum
end property

property wfxProgressBar.Minimum( byval nValue as long )
   _Minimum = nValue   
   if this.hWindow then 
      _Maximum = ProgressBar_GetMaxRange( this.hWindow )
      ProgressBar_SetRange32( this.hWindow, _Minimum, _Maximum )
   end if
end property

property wfxProgressBar.Value() as long
   if this.hWindow then 
      _Value = ProgressBar_GetPos( this.hWindow )
   end if
   property = _Value
end property

property wfxProgressBar.Value( byval nValue as long )
   _Value = nValue   
   if this.hWindow then 
      ' // Note: When using the default green color and visual themes,
      ' // ProgressBar_StepIt only renders half of the progress bar.
      ' // Microsoft added fancy animations to the progress bar control in Vista.
      ' // To provide a smoother visual feedback drawing is delayed when moving forward.
      ' // By setting the position back to a smaller value, the ProgressBar drawing is
      ' // forced to jump back (no delay in getting to a position smaller than the current).
      ProgressBar_SetPos( this.hWindow, _Value + 1)
      ProgressBar_SetPos( this.hWindow, _Value )
   end if
end property

property wfxProgressBar.StepValue() as long
   if this.hWindow then 
      ' SetStep returns the previous step value assigned to the control
      _StepValue = ProgressBar_SetStep( this.hWindow, _StepValue )
   end if
   property = _StepValue
end property

property wfxProgressBar.StepValue( byval nValue as long )
   _StepValue = nValue   
   if this.hWindow then 
      ProgressBar_SetStep( this.hWindow, _StepValue )
   end if
end property

property wfxProgressBar.Vertical( byval nValue as boolean ) 
   _Vertical = nValue
end property 

property wfxProgressBar.Vertical() as boolean
   property = _Vertical
end property 

property wfxProgressBar.Marquee( byval nValue as boolean ) 
   _Marquee = nValue
end property 

property wfxProgressBar.Marquee() as boolean
   property = _Marquee
end property 

property wfxProgressBar.MarqueeAnimationSpeed() as long
   property = _MarqueeAnimationSpeed
end property

property wfxProgressBar.MarqueeAnimationSpeed( byval nValue as long )
   _MarqueeAnimationSpeed = nValue   
   if this.hWindow then 
      ProgressBar_SetMarquee( this.hWindow, false, _MarqueeAnimationSpeed )
   end if
end property

function wfxProgressBar.StartMarquee( byval nValue as Boolean) as Long
   if this.hWindow then 
      if nValue = true then
         ProgressBar_SetMarqueeOn( this.hWindow, _MarqueeAnimationSpeed )
      else   
         ProgressBar_SetMarqueeOff( this.hWindow )
      end if 
   end if
   function = 0
end function   

function wfxProgressBar.PerformStep() as Long
   if this.hWindow then 
      ' Call Value because we need to do the +1 hack in order to ensure
      ' that the bar draws correctly with Themes.
      this.Value = this.Value + this.StepValue
   end if
   function = 0
end function   



function wfxProgressBar.Show(byval hWndParent as hwnd = 0) as long

   ' If the control is created but simply hidden, then show it.
   if this.hWindow THEN
      ShowWindow(this.hWindow, SW_SHOW)
      exit function
   END IF

   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function
      
   dim as long dwExStyle = 0
   Dim As Long dwStyle = WS_CHILD

   if this.Visible  THEN dwStyle = dwStyle OR WS_VISIBLE 
   if this.Vertical THEN dwStyle = dwStyle OR PBS_VERTICAL
   if this.Marquee  then dwStyle = dwStyle OR PBS_MARQUEE
   
   _CtrlID = this.Parent->GetNextCtrlID()

   this.hWindow = this.Parent->pWindow->AddControl ( _
         "PROGRESSBAR", _                  ' // Class name
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
         Cast(SUBCLASSPROC, @wfxApplication.SubclassProc), _   ' // Address of the window callback procedure
         _CtrlID, _                        ' // The subclass ID
         Cast(DWORD_PTR, 0) _              ' // Pointer to reference data
         )

   ' Should we enable drag and drop files
   If this.AllowDrop Then DragAcceptFiles(this.hWindow, CTRUE)

   ' Apply properties that require a valid window handle
   this.Maximum   = _Maximum
   this.Minimum   = _Minimum
   this.Value     = _Value
   this.Enabled   = _Enabled
   this.ToolTip   = _ToolTip

   if this.Marquee then
      ProgressBar_SetMarquee( this.hWindow, false, _MarqueeAnimationSpeed )
   end if
   
   ' Store the hWindow in the form's linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   dim pNode as wfxLListNode ptr = this.Parent->Controls.search_data(@this)
   if pNode then pNode->hWindow = this.hWindow

   function = 0
END FUNCTION




