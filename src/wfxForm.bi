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


Type wfxForm Extends wfxControl
   protected:
      _WindowState     as FormWindowState   = FormWindowState.Normal
      _StartPosition   as FormStartPosition = FormStartPosition.Manual
      _BorderStyle     as FormBorderStyle   = FormBorderStyle.Sizable
      _MinimizeBox     as boolean = true
      _MaximizeBox     as boolean = true
      _ControlBox      as boolean = true
      '_ShowInTaskBar   as Boolean = true
      _ClientSize      as wfxSize 
      _InitialCtrlID   as long
      _NextCtrlID      as long
      _ChildForm       as boolean = false 
      _ChildFormParent as CWSTR
      _IsMainForm      as boolean = false 
      _IsModal         as Boolean = false
      _KeyPreview      As Boolean = False
      _MinimumHeight   as Long = 0
      _MinimumWidth    as Long = 0
      _MaximumHeight   as Long = 0
      _MaximumWidth    as Long = 0
#ifdef CODEGEN_BUTTON
      _AcceptButton    as wfxButton ptr
      _CancelButton    as wfxButton ptr
#endif
#ifdef CODEGEN_MAINMENU
      _wfxMainMenuPtr  as wfxMainMenu ptr
#endif
      _Icon            as wstring * MAX_PATH
      _ReturnValue     as Long
      
   Public:           
      Controls         As wfxLList
#ifdef CODEGEN_MAINMENU
      MainMenu         as wfxMainMenu
#endif
#ifdef CODEGEN_TOOLBAR
      ToolBar          as wfxToolBar
#endif
#ifdef CODEGEN_STATUSBAR
      StatusBar        as wfxStatusBar
#endif      
      
      pWindow As CWindow Ptr
      pLayout AS CLayout Ptr
      
      declare function SetInitialCtrlID( byval nValue as long ) as Long     
      declare function CalculateStartPosition( BYVAL rc as RECT, BYVAL hwndParent AS HWND = NULL ) as POINT  'internal
      declare function GetAnchorEquateValue( byref wszValue as wstring ) as long
      declare function GetAnchorEquateByCtrl( byval pCtrl as wfxControl ptr ) as long
      declare function GetAnchorEquateByForm( byval pForm as wfxForm ptr ) as long
      declare property Text() as CWSTR
      declare property Text( byref nValue as wstring )
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
      Declare Property ChildForm() As boolean
      Declare Property ChildForm( ByVal nValue As boolean )
      declare property ChildFormParent() as CWSTR
      declare property ChildFormParent( byref nValue as wstring )
      Declare Property IsMainForm() As boolean
      Declare Property IsMainForm( ByVal nValue As boolean )
      Declare Property IsModal() As boolean
      Declare Property IsModal( ByVal nValue As boolean )
      Declare Property MinimumHeight( ByVal nValue As long )
      Declare Property MinimumHeight() As long
      Declare Property MinimumWidth( ByVal nValue As long )
      Declare Property MinimumWidth() As long
      Declare Property MaximumHeight( ByVal nValue As long )
      Declare Property MaximumHeight() as long
      Declare Property MaximumWidth( ByVal nValue As long )
      Declare Property MaximumWidth() as long
      Declare Property KeyPreview() As boolean
      Declare Property KeyPreview( ByVal nValue As boolean )
      'Declare Property ShowInTaskBar() As boolean
      'Declare Property ShowInTaskBar( ByVal nValue As boolean )
      declare function ScaleX( byval nValue as long ) as Long
      declare function ScaleY( byval nValue as long ) as Long
      declare function UnScaleX( byval nValue as long ) as Long
      declare function UnScaleY( byval nValue as long ) as Long
#ifdef CODEGEN_BUTTON
      Declare Property AcceptButton() As wfxButton ptr
      Declare Property AcceptButton( byval nValue as wfxButton ptr )
      Declare Property CancelButton() As wfxButton ptr
      Declare Property CancelButton( byval nValue as wfxButton ptr )
#endif
      'Declare Property MainMenu() As wfxMainMenu 
      'Declare Property MainMenu( byval nValue as wfxMainMenu ptr )
      declare property Icon() as CWSTR
      declare property Icon( byref cwzValue as wstring )

      declare function GetNextCtrlID() as Long     
      declare function Close( byval ReturnValue as long = 0 ) as Long
      declare function Show(byval hWndParent as hwnd = 0) as Long override
      declare function Show(byref frmParent as wfxForm) as Long 
      declare function Show(byval frmParent as wfxForm ptr) as Long
      declare function ShowDialog(byval hWndParent as hwnd = 0) as Long 
      declare function ShowDialog(byref frmParent as wfxForm) as Long
      declare function ShowDialog(byval frmParent as wfxForm ptr) as Long
      declare function ShowChild(byval hWndParent as hwnd = 0 ) as Long 
      declare function ShowChild(byref frmParent as wfxForm) as Long 
      declare function ShowChild(byval frmParent as wfxForm ptr) as Long
      declare function CreateFormInternal( byval hWndParent as hwnd, byval IsModal as boolean, byval IsChild as Boolean ) as long   
      declare Function SizeToolBar() As Long  ' internal function
      declare Function SizeStatusBar() As Long  ' internal function
      
      InitializeComponent as function( byval pForm as wfxForm ptr ) as LRESULT
      
      OnAllEvents        as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnLoad             as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnInitialize       As Function( ByRef sender As wfxForm, ByRef e As EventArgs ) As LRESULT
      OnActivated        As Function( ByRef sender As wfxForm, ByRef e As EventArgs ) As LRESULT
      OnDeactivate       as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnShown            as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnFormClosing      as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnFormClosed       as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnFormReady        as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnMove             as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnResize           as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnMouseMove        as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnMouseDown        as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnMouseUp          as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnMouseDoubleClick as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnMouseEnter       as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnMouseHover       as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnMouseLeave       as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnKeyDown          as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnKeyPress         as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnKeyUp            as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnDropFiles        as function( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
      OnMessagePumpHook  as function( byval lpMSG as MSG ptr ) as boolean
      
      Declare Constructor( byref wszName as wstring = "" )
      Declare Destructor
      
End Type

