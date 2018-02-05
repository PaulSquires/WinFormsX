'    WinFormsX - Windows GUI Framework for the FreeBASIC Compiler
'    Copyright (C) 2018 Paul Squires, PlanetSquires Software
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


Type wfxForm Extends wfxControl
   protected:
      _WindowState     as FormWindowState = FormWindowState.Normal
      _StartPosition   as FormStartPosition = FormStartPosition.Manual
      _BorderStyle     as FormBorderStyle = FormBorderStyle.Sizable
      _MinimizeBox     as boolean = true
      _MaximizeBox     as boolean = true
      _ControlBox      as boolean = true
      _ClientSize      as wfxSize 
      _NextCtrlID      as long    = 100
      _IsMainForm      as boolean = false 
      _IsModal         as Boolean = false
      
   Public:           
      Controls         As wfxLList
      
      pWindow As CWindow Ptr
      Declare Property WindowState() As FormWindowState
      Declare Property WindowState( ByVal nValue As FormWindowState )
      Declare Property StartPosition() As FormStartPosition
      Declare Property StartPosition( ByVal nValue As FormStartPosition )
      Declare Property BorderStyle() As FormBorderStyle
      Declare Property BorderStyle( ByVal nValue As FormBorderStyle )
      Declare Property MinimizeBox() As boolean
      Declare Property MinimizeBox( ByVal nValue As boolean )
      Declare Property MaximizeBox() As boolean
      Declare Property MaximizeBox( ByVal nValue As boolean )
      Declare Property ControlBox() As boolean
      Declare Property ControlBox( ByVal nValue As boolean )
      Declare Property ClientSize() As wfxSize
      declare property ClientSize( byval nWidth as long, byval nHeight as long )
      Declare Property IsMainForm() As boolean
      Declare Property IsMainForm( ByVal nValue As boolean )
      Declare Property IsModal() As boolean
      Declare Property IsModal( ByVal nValue As boolean )

      declare function GetNextCtrlID() as Long     
      declare function Close() as Long
      declare function Show(byval hWndParent as hwnd = 0) as Long override
      declare function Show(byref frmParent as wfxForm) as Long 
      declare function Show(byval frmParent as wfxForm ptr) as Long
      declare function ShowDialog(byval hWndParent as hwnd = 0) as Long 
      declare function ShowDialog(byref frmParent as wfxForm) as Long
      declare function ShowDialog(byval frmParent as wfxForm ptr) as Long
      declare function CreateFormInternal( byval hWndParent as hwnd, byval IsModal as boolean ) as long   
      declare function GetControlByName( ByRef cwzName As wstring) as wfxControl ptr
      
      OnAllEvents        as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnLoad             as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnActivated        as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnDeactivate       as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnShown            as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnFormClosing      as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnFormClosed       as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnMove             as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnResize           as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnMouseMove        as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnMouseDown        as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnMouseUp          as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnMouseDoubleClick as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnKeyDown          as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnKeyPress         as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnKeyUp            as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnGotFocus         as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnLostFocus        as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT

      Declare Constructor( byref wszName as wstring = "" )
      Declare Destructor
      
End Type

