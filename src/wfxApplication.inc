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


#include once "wfxApplication.bi"

''
''  wfxApplication Class
''

''  Main class for the entire wfxApplication. Everything starts and ends
''  through this class. 
''
''  https://msdn.microsoft.com/en-us/library/system.windows.forms.clsApplication(v=vs.110).aspx
''

Constructor wfxApplication()
   'print "app constructor"
end constructor

Destructor wfxApplication()
   ' Loop through the form collection and deallocate each form
'   dim pForm as wfxControl ptr
'   for i as long = 0 to this.Forms.Count - 1
'      pForm = this.Forms.ItemAt(i)
'      this.Forms.Remove(pForm)
'   NEXT
end destructor

''
''  Company name as stored in the program's resource file
''
Property wfxApplication.CompanyName() As CWSTR
   'TODO: CompanyName
   dim wszText as CWSTR = "PlanetSquires"
   return wszText
END Property

''
''  Product name as stored in the program's resource file
''
Property wfxApplication.ProductName() As CWSTR
   'TODO: ProductName
   dim wszText as CWSTR = "My App"
   return wszText
END Property

''
''  Product version as stored in the program's resource file
''
Property wfxApplication.ProductVersion() As CWSTR
   'TODO: ProductVersion
   dim wszText as CWSTR = "1.0.0"
   return wszText
END Property

''
''  Gets the path for the wfxApplication data that is shared amongst all users
''  (no trailing backspace)
''
Property wfxApplication.CommonAppDataPath() As CWSTR
   dim wszText as CWSTR = AfxGetSpecialFolderLocation(CSIDL_APPDATA)
   return wszText
END Property

''
''  Path for the wfxApplication data of the user (ie. AppData\Local)
''  (no trailing backspace)
''
Property wfxApplication.UserAppDataPath() As CWSTR
   dim wszText as CWSTR = AfxGetSpecialFolderLocation(CSIDL_LOCAL_APPDATA)
   return wszText
END Property

''
''  Full path and exe name for this running wfxApplication
''
Property wfxApplication.ExecutablePath() As CWSTR
   dim wszText as CWSTR = AfxGetExeFullPath()
   return wszText
END Property

''
''  Gets the path for the executable file that started the wfxApplication, 
''  not including the executable name. (no trailing backspace)
''
Property wfxApplication.StartupPath() As CWSTR
   dim wszText as CWSTR = rtrim(AfxGetExePathName, any "\/")
   return wszText
END Property

''
''  Processes all Windows messages currently in the message queue.
''
Function wfxApplication.DoEvents() As LRESULT
   AfxDoEvents()
   return 0
end function

''
''  Begins running a standard wfxApplication message loop without a form.
''
Function wfxApplication.Run() As LRESULT
' TODO: wfxApplication Run
   sleep
   return 0
end function

''
''  Begins running a standard wfxApplication message loop and 
''  makes the specified form visible.
''
Function wfxApplication.Run( Byref pForm As wfxForm ) As LRESULT

   Dim as MSG uMsg 

   ' Show the window and update its client area (this will also create any child controls)
   pForm.IsMainForm = true
   pForm.Show()
     
   ' Ensure the window is placed on screen should the user had changed 
   ' the logical ordering of a multiple display setup.
   AfxForceVisibleDisplay(pForm.pWindow->hWindow)
   
   ' Message loop
   Do While GetMessage(@uMsg, Null, 0, 0)
      ' Processes accelerator keys for menu commands
      If (pForm.pWindow->AccelHandle = 0) Or _
         (TranslateAccelerator(pForm.pWindow->hWindow, pForm.pWindow->AccelHandle, @uMsg)) = 0 Then
         If IsDialogMessage(pForm.pWindow->hWindow, @uMsg) = 0 Then
            TranslateMessage @uMsg    ' Translates virtual-key messages into character messages.
            DispatchMessage  @uMsg    ' Dispatches a message to a window procedure.
         End If
      End If
   Loop
   Function = uMsg.wParam

print "Message loop exited. Program ending."

end function


''    
''  Generic function to retrieve control object via Windows handle
''
function wfxApplication.GetControlByHandle( byval hWindow as hwnd ) as wfxLListNode ptr
   dim pNodeCtrl as wfxLListNode ptr
   dim pNode as wfxLListNode ptr
   dim pForm as wfxForm ptr
   
   ' Search all Forms and each control in each Form.
   pNode = this.Forms.get_first
   do until pNode = 0
      ' Does the hWindow match the form itself
      if pNode->hWindow = hWindow then return pNode
      ' Search all the controls on the form for a match
      pForm = cast(wfxForm ptr, pNode->pData)
      pNodeCtrl = pForm->Controls.search_handle(hWindow)
      if pNodeCtrl then return pNodeCtrl
      ' Get the form in the application   
      pNode = this.Forms.get_next(pNode)
   LOOP
   function = 0
end function


''
''  Internal function to set the elements of the various EventArg types.
''
Function wfxApplication.SetEventArgs( byval uMsg   as UINT, _
                                      ByVal wParam As WPARAM, _
                                      ByVal lParam As LPARAM, _
                                      byref e      as wfxEventArgs _ 
                                      ) as Long
   e.Message = uMsg
   e.Handled = false
   e.Cancel  = false    ' cancel a form close
   e.Ctrl    = (GetKeyState(VK_CONTROL) and &H8000)
   e.Shift   = (GetKeyState(VK_SHIFT) and &H8000)
   e.Alt     = (GetKeyState(VK_MENU) and &H8000)

   select case uMsg
      case WM_MOUSEMOVE, _
           WM_LBUTTONDOWN, WM_MBUTTONDOWN, WM_RBUTTONDOWN, _
           WM_LBUTTONUP, WM_MBUTTONUP, WM_RBUTTONUP, _
           WM_LBUTTONDBLCLK, WM_MBUTTONDBLCLK, WM_RBUTTONDBLCLK
         e.x = GET_X_LPARAM(lParam)
         e.y = GET_Y_LPARAM(lParam)
         e.LButton = (wParam and MK_LBUTTON)
         e.MButton = (wParam and MK_MBUTTON)
         e.RButton = (wParam and MK_RBUTTON)

      case WM_KEYDOWN, WM_KEYUP, WM_CHAR
         e.KeyChar = wParam
   END SELECT
         
   function = 0
END FUNCTION
 
''    
''  wfxApplication General Window procedure
''
static Function wfxApplication.WndProc( ByVal hWin   As HWnd, _
                                        ByVal uMsg   As UINT, _
                                        ByVal wParam As WPARAM, _
                                        ByVal lParam As LPARAM _
                                        ) As LRESULT


   dim pNode as wfxLListNode ptr
   dim e     as wfxEventArgs 
   
   dim pCtrl  as wfxControl ptr
   dim pForm  as wfxForm ptr
   dim pLabel as wfxLabel ptr
   
   pNode = Application.GetControlByHandle(hWin)
   if pNode then 
      pCtrl = cast(wfxControl ptr, pNode->pData)
      select case pNode->CtrlType 
         CASE ControlType.Form:   pForm  = cast(wfxForm ptr, pNode->pData)
         CASE ControlType.Label:  pLabel = cast(wfxLabel ptr, pNode->pData)
      END SELECT
   end if   

   Application.SetEventArgs(uMsg, wParam, lParam, e)
    
   ' Send to AllEvents handler should it be active
   if pForm andalso pForm->OnAllEvents then pForm->OnAllEvents(*pForm, e)

   ' If the event was handled in the OnAllEvents then return true
   if e.Handled THEN return true


   ' Attempt to process the message using any defined functions
   Select Case uMsg
      case WM_ACTIVATE
         if pForm then 
            ' Get the activation state
            if LoWord(wParam) = WA_INACTIVE THEN  ' Deactivated
               if pForm->OnDeactivate THEN pForm->OnDeactivate(*pForm, e)
            else ' Activated   
               if pForm->OnActivated THEN pForm->OnActivated(*pForm, e)
            END IF
         END IF

      case WM_CLOSE
         if pForm then 
            if pForm->OnFormClosing then 
               pForm->OnFormClosing(*pForm, e)
               if e.Cancel THEN return true
            end if   
            if pForm->IsModal then 
               ' Enables parent window keeping parent's zorder
               EnableWindow( GetParent(hWin), true)
               DestroyWindow(hWin)
            end if    
         end if   
          
      Case WM_DESTROY
         if pForm andalso pForm->OnFormClosed then pForm->OnFormClosed(*pForm, e)
         if pLabel andalso pLabel->OnDestroy then pLabel->OnDestroy(*pLabel, e)
         ' If this is the main form then post a quit message
         if pForm then 
            if pForm->IsMainForm THEN 
               PostQuitMessage(0)
               ? "postquitmessage"
            end if   
         END IF
  
      case WM_COMMAND
         select CASE hiword(wParam)
            case BN_CLICKED
               ' wParam: LOWORD contains the button's control identifier. 
               '         HIWORD specifies the notification code.
               ' lParam: Handle to the button.
               ' Determine the pointer based on the Window handle generating the notification.
               pNode = Application.GetControlByHandle( cast(hwnd, lParam) )
               if pNode then 
                  pCtrl = cast(wfxControl ptr, pNode->pData)
                  select case pNode->CtrlType 
                     CASE ControlType.Label
                        pLabel = cast(wfxLabel ptr, pNode->pData)
                        if pLabel andalso pLabel->OnClick then pLabel->OnClick(*pLabel, e)
                  END SELECT
               end if   
         END SELECT
 
      case WM_CTLCOLORSTATIC, WM_CTLCOLOREDIT 
         if pCtrl THEN 
            SetTextColor(cast(HDC, wParam), pCtrl->Foreground)
            SetBkColor(cast(HDC, wParam), pCtrl->Background)
            Return Cast(LRESULT, pCtrl->hBackBrush)
         end if   

      case WM_ERASEBKGND
         if pForm then 
            dim as Rect rc
            GetClientRect(hWin, @rc)
            FillRect(Cast(HDC, wParam), @rc, pForm->hBackBrush)
            return true
         end if   
          
      case WM_LBUTTONDBLCLK, WM_MBUTTONDBLCLK, WM_RBUTTONDBLCLK
         if pForm andalso pForm->OnMouseDoubleClick then pForm->OnMouseDoubleClick(*pForm, e)

      case WM_LBUTTONDOWN, WM_MBUTTONDOWN, WM_RBUTTONDOWN
         if pForm andalso pForm->OnMouseDown then pForm->OnMouseDown(*pForm, e)

      case WM_LBUTTONUP, WM_MBUTTONUP, WM_RBUTTONUP
         if pForm andalso pForm->OnMouseUp then pForm->OnMouseUp(*pForm, e)
         ' Forms convert LBUTTONUP to simulate OnClick()
         if uMsg = WM_LBUTTONUP then
            if pForm andalso pForm->OnClick then pForm->OnClick(*pForm, e)
         end if
         
      case WM_SETFOCUS
         if pForm andalso pForm->OnGotFocus then pForm->OnGotFocus(*pForm, e)

      case WM_KILLFOCUS
         if pForm andalso pForm->OnLostFocus then pForm->OnLostFocus(*pForm, e)

      case WM_KEYDOWN
         if pForm andalso pForm->OnKeyDown then pForm->OnKeyDown(*pForm, e)

      case WM_KEYUP
         if pForm andalso pForm->OnKeyUp then pForm->OnKeyUp(*pForm, e)

      case WM_CHAR
         if pForm andalso pForm->OnKeyPress then pForm->OnKeyPress(*pForm, e)
         
      case WM_MOUSEMOVE
         if pForm andalso pForm->OnMouseMove then pForm->OnMouseMove(*pForm, e)
         if pLabel andalso pLabel->OnMouseMove then pLabel->OnMouseMove(*pLabel, e)
          
      Case WM_MOVE
         if pForm andalso pForm->OnMove then pForm->OnMove(*pForm, e)

      Case WM_SIZE
         if pForm then 
            if pForm->OnResize then pForm->OnResize(*pForm, e)
            
            ' If a StatusBar exists on this form then resize it.
            pCtrl = pForm->GetControlByName("StatusBar")
            if pCtrl then
               dim pStatusBar as wfxStatusBar ptr = cast(wfxStatusBar ptr, pCtrl)
               SendMessage(pStatusBar->hWindow, uMsg, wParam, lParam)
            END IF
         
         END IF

   End Select
   
   ' For messages that we don't deal with make sure that Windows handles them.
   Function = DefWindowProc(hWin, uMsg, wParam, lParam)

End Function

'
'    
'  wfxApplication General Subclass Window procedure
'
static Function wfxApplication.SubclassProc ( _
                  ByVal hWin   As HWnd, _                 ' // Control window handle
                  ByVal uMsg   As UINT, _                 ' // Type of message
                  ByVal wParam As WPARAM, _               ' // First message parameter
                  ByVal lParam As LPARAM, _               ' // Second message parameter
                  ByVal uIdSubclass As UINT_PTR, _        ' // The subclass ID
                  ByVal dwRefData As DWORD_PTR _          ' // Pointer to reference data
                  ) As LRESULT

   Select Case uMsg
      Case WM_GETDLGCODE
         ' All keyboard input
         Function = DLGC_WANTALLKEYS

      Case WM_DESTROY
         ' REQUIRED: Remove control subclassing
         RemoveWindowSubclass( hWin, @wfxApplication.SubclassProc, uIdSubclass )

      case else
         wfxApplication.WndProc( hWin, uMsg, wParam, lParam )
         return true

   End Select
    
   ' For messages that we don't deal with
   Function = DefSubclassProc(hWin, uMsg, wParam, lParam)

End Function

