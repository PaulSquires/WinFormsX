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


Type wfxApplication
   Private:
      _dummy As Long
      
   Public:
      Declare Constructor
      Declare Destructor
      
      Declare Property CompanyName() As CWSTR
      Declare Property ProductName() As CWSTR
      Declare Property ProductVersion() As CWSTR
      Declare Property CommonAppDataPath() As CWSTR
      Declare Property UserAppDataPath() As CWSTR
      Declare Property ExecutablePath() As CWSTR
      Declare Property StartupPath() As CWSTR
      
      Declare Function GetpFormObject( ByVal hWin As HWnd ) As wfxForm Ptr
      declare function GetpFormObjectByName( byref wszFormName as wstring ) as wfxForm ptr
      Declare Function TranslateFormWindowState( ByVal nValue As FormWindowState ) As Long
      Declare Function DoEvents() As LRESULT
      Declare Function Run() As LRESULT
      declare Function Run( Byref pForm As wfxForm ) As LRESULT
      declare function GetControlByHandle( byval hWindow as hwnd ) as wfxLListNode ptr
      declare Function SetEventArgs( byval uMsg as UINT, ByVal wParam As WPARAM, ByVal lParam As LPARAM, byref e as wfxEventArgs) as Long
      declare static Function WndProc( ByVal HWnd As HWnd, ByVal uMsg As UINT, ByVal wParam As WPARAM, ByVal lParam As LPARAM) As LRESULT
      declare static Function SubclassProc( ByVal HWnd As HWnd, ByVal uMsg As UINT, ByVal wParam As WPARAM, ByVal lParam As LPARAM, ByVal uIdSubclass As UINT_PTR, ByVal dwRefData As DWORD_PTR ) As LRESULT
      declare static sub TimerProc( byval hwnd as HWND, byval uMsg as UINT, byval TimerID as UINT ptr, byval dwTime as DWORD )
      Declare Function HandleCommonMessages( ByVal HWnd As HWnd, ByVal uMsg As UINT, ByVal wParam As WPARAM, ByVal lParam As LPARAM) As LRESULT
      Declare Function PreprocessMessage( ByVal hWndForm As HWnd, ByVal hwndControl As HWnd, ByVal pMsg As MSG Ptr) As Boolean
      
      ' Gets a collection of open forms owned by the wfxApplication
      Forms As wfxLList
      
      ' User defined message that is fired via PostMessage in order to
      ' simulate the DoAfterCheck notification for when a user clciks
      ' on a TreeView checkbox. RegisterMessage.
      MSG_WINFORMS_AFTERCHECK as UInteger

      ' User defined message that is fired via PostMessage in order to
      ' simulate the FormReady event handler. RegisterMessage.
      MSG_WINFORMS_FORMREADY as UInteger
      
End Type

''
''  Create a static instance of the wfxApplication class that will be
''  used for the entire life of the application.
Dim Shared Application As wfxApplication


