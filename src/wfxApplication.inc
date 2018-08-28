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
   'print "app destructor"
End Destructor


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
''
''   M A C R O S
''
#Macro WINFORMSX_DIM_POINTERS    
   Dim pNode       As wfxLListNode Ptr
   Dim e           As wfxEventArgs
   Dim pCtrl       As wfxControl Ptr
   Dim pForm       As wfxForm Ptr
   Dim pLabel      As wfxLabel Ptr
   Dim pButton     As wfxButton Ptr
   Dim pTextBox    As wfxTextBox Ptr
   Dim pCheckBox   As wfxCheckBox Ptr
   Dim pOption     As wfxOptionButton Ptr
   Dim pListBox    As wfxListBox Ptr
   Dim pStatusBar  As wfxStatusBar Ptr

   pNode = Application.GetControlByHandle(hWin)
   If pNode Then 
      pCtrl = Cast(wfxControl Ptr, pNode->pData)
      Select Case pNode->CtrlType 
         Case ControlType.Form:         pForm      = Cast(wfxForm Ptr, pNode->pData)
         Case ControlType.Label:        pLabel     = Cast(wfxLabel Ptr, pNode->pData)
         Case ControlType.Button:       pButton    = Cast(wfxButton Ptr, pNode->pData)
         Case ControlType.TextBox:      pTextBox   = Cast(wfxTextBox Ptr, pNode->pData)
         Case ControlType.CheckBox:     pCheckBox  = Cast(wfxCheckBox Ptr, pNode->pData)
         Case ControlType.OptionButton: pOption    = Cast(wfxOptionButton Ptr, pNode->pData)
         Case ControlType.ListBox:      pListBox   = Cast(wfxListBox Ptr, pNode->pData)
         Case ControlType.StatusBar:    pStatusBar = Cast(wfxStatusBar Ptr, pNode->pData)
      End Select
   End If   
#EndMacro

#Macro WINFORMSX_HANDLE_MESSAGE(msg)    
   ' Bypass controls that do not handle focus or keyboard input
   #If( #msg <> "OnGotFocus" AndAlso #msg <> "OnLostFocus" AndAlso #msg <> "OnKeyDown" AndAlso #msg <> "OnKeyUp" AndAlso #msg <> "OnKeyPress" )  
      #If(#msg <> "OnDestroy")  ' OnDestroy is FormClosed for forms.
         If pForm AndAlso pForm->##msg Then pForm->##msg(*pForm, e)
      #EndIf
      #If(#msg <> "OnMouseDoubleClick")  ' Handled through STN_DBLCLK notification
         If pLabel AndAlso pLabel->##msg Then pLabel->##msg(*pLabel, e)
      #EndIf
      If pStatusBar AndAlso pStatusBar->##msg Then pStatusBar->##msg(*pStatusBar, e)
   #EndIf
   ' Mouse doubleclicks are handled through LBN_DBLCLK notifications
   ' ListBox Clicks are handled through LBN_SELCHANGE
   #If(#msg <> "OnMouseDoubleClick" AndAlso #msg <> "OnClick")  
      If pListBox AndAlso pListBox->##msg Then pListBox->##msg(*pListBox, e)
   #EndIf
   If pButton AndAlso pButton->##msg Then pButton->##msg(*pButton, e)
   If pTextBox AndAlso pTextBox->##msg Then pTextBox->##msg(*pTextBox, e)
   If pCheckBox AndAlso pCheckBox->##msg Then pCheckBox->##msg(*pCheckBox, e)
   If pOption AndAlso pOption->##msg Then pOption->##msg(*pOption, e)
#EndMacro
''
''
''

''
''  Internal function to set the elements of the various EventArg types.
''
Function wfxApplication.SetEventArgs( ByVal uMsg   As UINT, _
                                      ByVal wParam As WPARAM, _
                                      ByVal lParam As LPARAM, _
                                      ByRef e      As wfxEventArgs _ 
                                      ) As Long
   e.Message = uMsg
   e.wParam  = wParam
   e.lParam  = lParam
   e.Handled = False
   e.Cancel  = False    ' cancel a form close
   e.Ctrl    = (GetKeyState(VK_CONTROL) And &H8000)
   e.Shift   = (GetKeyState(VK_SHIFT) And &H8000)
   e.ALT     = (GetKeyState(VK_MENU) And &H8000)

   Select Case uMsg
      Case WM_MOUSEMOVE, _
           WM_LBUTTONDOWN, WM_MBUTTONDOWN, WM_RBUTTONDOWN, _
           WM_LBUTTONUP, WM_MBUTTONUP, WM_RBUTTONUP, _
           WM_LBUTTONDBLCLK, WM_MBUTTONDBLCLK, WM_RBUTTONDBLCLK
         e.x = GET_X_LPARAM(lParam)
         e.y = GET_Y_LPARAM(lParam)
         e.LButton = (wParam And MK_LBUTTON)
         e.MButton = (wParam And MK_MBUTTON)
         e.RButton = (wParam And MK_RBUTTON)

      Case WM_KEYDOWN, WM_KEYUP
         e.KeyCode = wParam

      Case WM_CHAR   
         e.KeyChar = wParam
   
      Case WM_DROPFILES
         e.hDrop = Cast(HDROP, wParam)
   End Select
         
   Function = 0
End Function
 
''
''  wfxApplication get the pForm pointer object
''
Function wfxApplication.GetpFormObject( ByVal hWin As HWnd ) As wfxForm Ptr

   Dim pNode As wfxLListNode Ptr
   Dim pCtrl As wfxControl Ptr
   Dim pForm As wfxForm Ptr
   
   pNode = Application.GetControlByHandle(hWin)
   If pNode Then 
      pCtrl = Cast(wfxControl Ptr, pNode->pData)
      If pNode->CtrlType = ControlType.Form Then
         pForm  = Cast(wfxForm Ptr, pNode->pData)
      End If
   End If
   
   Return pForm
End Function      


''
''
''
Function wfxApplication.PreprocessMessage( ByVal hWndForm As HWnd, _
                                           ByVal hWin As HWnd, _
                                           ByVal pMsg As MSG Ptr _
                                           ) As Boolean

   Dim pActiveForm As wfxForm Ptr
   WINFORMSX_DIM_POINTERS    
   
   ' If a button has been set for ACCEPTBUTTON or CANCELBUTTON then send Click
   ' message to that button. We need to get the activewindow because this could
   ' a popup window.
   If pMsg->message = WM_KEYDOWN Then
      If pMsg->wParam = VK_RETURN Then
         pActiveForm = Application.GetpFormObject(hWndForm)
         If pActiveForm AndAlso pActiveForm->AcceptButton Then
            ' Simulates the user clicking a button. This message causes the button to receive the
            ' WM_LBUTTONDOWN and WM_LBUTTONUP messages, and the button's parent window to receive a
            ' BN_CLICKED notification code.
            SendMessage(pActiveForm->AcceptButton->hWindow, BM_CLICK, 0, 0)
            Return True
         End If   
      ElseIf pMsg->wParam = VK_ESCAPE Then
         pActiveForm = Application.GetpFormObject(hWndForm)
         If pActiveForm AndAlso pActiveForm->CancelButton Then
            ' Simulates the user clicking a button. This message causes the button to receive the
            ' WM_LBUTTONDOWN and WM_LBUTTONUP messages, and the button's parent window to receive a
            ' BN_CLICKED notification code.
            SendMessage(pActiveForm->CancelButton->hWindow, BM_CLICK, 0, 0)
            Return True
         End If   
      End If
   End If
            
   ' Handle any form level keypreview. All keys are previewed included the TAB
   ' key that would normally move focus input amongst controls.
   Select Case pMsg->message
      Case WM_KEYDOWN, WM_KEYUP, WM_CHAR
         pActiveForm = Application.GetpFormObject(hWndForm)
         Application.SetEventArgs(pMsg->message, pMsg->wParam, pMsg->lParam, e)
         If cbool(pActiveForm <> 0) AndAlso pActiveForm->KeyPreview Then
            If (pMsg->message = WM_KEYDOWN AndAlso pActiveForm->OnKeyDown) Then pActiveForm->OnKeyDown(*pActiveForm, e)
            If (pMsg->message = WM_KEYUP AndAlso pActiveForm->OnKeyUp) Then pActiveForm->OnKeyUp(*pActiveForm, e)
            If (pMsg->message = WM_CHAR AndAlso pActiveForm->OnKeyPress) Then pActiveForm->OnKeyPress(*pActiveForm, e)
            If e.Handled Then Return True  ' do not process any subsequent control handlers
         End If
   End Select   
   ' After form preview, pass the message to any defined control handler.
   Select Case pMsg->message
      Case WM_KEYDOWN
         WINFORMSX_HANDLE_MESSAGE(OnKeyDown)
      Case WM_KEYUP
         WINFORMSX_HANDLE_MESSAGE(OnKeyUp)
      Case WM_CHAR
         WINFORMSX_HANDLE_MESSAGE(OnKeyPress)
   End Select
   
   ' If this is a multiline textbox then test to see if a TAB key should be
   ' allowed as a valid character (the default action) or if the TAB should
   ' move control focus.
   If (pMsg->message = WM_KEYDOWN) AndAlso (pMsg->wParam = VK_TAB) Then
      Dim pNode As wfxLListNode Ptr
      Dim pCtrl As wfxControl Ptr
      Dim pTextBox As wfxTextBox Ptr
      pNode = Application.GetControlByHandle(pMsg->HWnd)
      If pNode Then 
         pCtrl = Cast(wfxControl Ptr, pNode->pData)
         If pNode->CtrlType = ControlType.TextBox Then
            pTextBox = Cast(wfxTextBox Ptr, pNode->pData)
            If cbool(pTextBox <> 0) AndAlso (pTextBox->MultiLine = True) Then
               If pTextBox->AcceptsTab = True Then
                  Edit_ReplaceSel(pMsg->HWnd, @WChr(9))
               ElseIf pTextBox->AcceptsTab = False Then
                  If (GetKeyState(VK_SHIFT) And &H8000) Then
                     SetFocus( GetNextDlgTabItem( hWndForm, pMsg->HWnd, True) )
                  Else
                     SetFocus( GetNextDlgTabItem( hWndForm, pMsg->HWnd, False) )
                  End If
               End If
               Return True   
            End If
         End If
      End If      
   End If
   
   Return False
End Function



''
''  Begins running a standard wfxApplication message loop and 
''  makes the specified form visible.
''
Function wfxApplication.Run( Byref pForm As wfxForm ) As LRESULT

   ' Ensure the window is placed on screen should the user had changed 
   ' the logical ordering of a multiple display setup.
   AfxForceVisibleDisplay(pForm.pWindow->hWindow)
   
   ' Show the window and update its client area (this will also create any child controls)
   pForm.IsMainForm = true
   Function = pForm.ShowDialog()
     
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
''  wfxApplication handle general common messages for form and controls
''
Function wfxApplication.HandleCommonMessages( ByVal hWin   As HWnd, _
                                              ByVal uMsg   As UINT, _
                                              ByVal wParam As WPARAM, _
                                              ByVal lParam As LPARAM _
                                              ) As LRESULT

   WINFORMSX_DIM_POINTERS

   ' Fill the EventArgs variable with any info related to this message
   Application.SetEventArgs(uMsg, wParam, lParam, e)

   ' Send to AllEvents handler should it be active
   WINFORMSX_HANDLE_MESSAGE(OnAllEvents)    
   If e.Handled Then Return True
   
   
   Select Case uMsg
   
      Case WM_DESTROY
         ' Only handle controls here. The form is handled in the main WndProc procedure.
         If pForm Then Return False
         WINFORMSX_HANDLE_MESSAGE(OnDestroy)
         ' Reset the window handles for the control and pNode so that future messages can no
         ' longer act on the control classes.
         If pCtrl Then
            pCtrl->hWindow = 0
            pNode->hWindow = 0
         End If
         ' You can not stop the destroy process so do not honor any e.Handled that may have been set.
         e.Handled = False
         
      Case WM_DROPFILES
         ' wParam: hDrop, a handle to an internal structure describing the dropped files. 
         '         Pass this handle DragFinish, DragQueryFile, or DragQueryPoint to retrieve 
         '         information about the dropped files.
         ' lParam: Must be zero.
         WINFORMSX_HANDLE_MESSAGE(OnDropFiles)

      Case WM_MOUSEMOVE
         WINFORMSX_HANDLE_MESSAGE(OnMouseMove)
         ' There is no such thing as a WM_MOUSEENTER message so we need to simulate it
         ' here by using a tracking variable and TRACKMOUSEEVENT.
         If pCtrl Then
            If pCtrl->IsTracking = False Then
               pCtrl->IsTracking = True
               Dim tme As TrackMouseEvent
               tme.cbSize = Sizeof(TrackMouseEvent)
               tme.dwFlags = TME_HOVER Or TME_LEAVE
               tme.hwndTrack = hWin
               TrackMouseEvent(@tme) 
               WINFORMSX_HANDLE_MESSAGE(OnMouseEnter)
            End If
         End If
          
      Case WM_MOUSELEAVE
         If pCtrl Then pCtrl->IsTracking = False 
         WINFORMSX_HANDLE_MESSAGE(OnMouseLeave)
      
      Case WM_MOUSEHOVER
         WINFORMSX_HANDLE_MESSAGE(OnMouseHover)
            
      Case WM_LBUTTONDBLCLK, WM_MBUTTONDBLCLK, WM_RBUTTONDBLCLK
         WINFORMSX_HANDLE_MESSAGE(OnMouseDoubleClick)
         ' For Listboxes, the doubleclick is handled through the LBN_DBLCLK notification.
         ' Labels handle doubleclick through STN_DBLCLK notification.
         
      Case WM_LBUTTONDOWN, WM_MBUTTONDOWN, WM_RBUTTONDOWN
         WINFORMSX_HANDLE_MESSAGE(OnMouseDown)

      Case WM_LBUTTONUP, WM_MBUTTONUP, WM_RBUTTONUP
         WINFORMSX_HANDLE_MESSAGE(OnMouseUp)
         ' Forms and TextBoxes convert LBUTTONUP to simulate OnClick()
         If uMsg = WM_LBUTTONUP Then
            If pForm AndAlso pForm->OnClick Then pForm->OnClick(*pForm, e)
            If pTextBox AndAlso pTextBox->OnClick Then pTextBox->OnClick(*pTextBox, e)
         End If
         
      Case WM_SETFOCUS
         WINFORMSX_HANDLE_MESSAGE(OnGotFocus)

      Case WM_KILLFOCUS
         WINFORMSX_HANDLE_MESSAGE(OnLostFocus)

   End Select
   
   ' If the event was handled then return true
   If e.Handled Then Return True
   Return False

End Function


''    
''  wfxApplication General Window procedure
''
static Function wfxApplication.WndProc( ByVal hWin   As HWnd, _
                                        ByVal uMsg   As UINT, _
                                        ByVal wParam As WPARAM, _
                                        ByVal lParam As LPARAM _
                                        ) As LRESULT


   WINFORMSX_DIM_POINTERS
   
   ' Handle any common messages for the form or controls and
   ' return from WndProc if the message was handled.
   If Application.HandleCommonMessages(hWin, uMsg, wParam, lParam) Then Return 0

   ' Fill the EventArgs variable with any info related to this message
   Application.SetEventArgs(uMsg, wParam, lParam, e)

   ' Attempt to process the message using any defined functions
   Select Case uMsg

       Case WM_GETMINMAXINFO
         pForm = Application.GetpFormObject(hWin)
         If pForm Then 
             DefWindowProc(hWin, uMsg, wParam, lParam)
             Dim pMinMaxInfo As MINMAXINFO Ptr
             pMinMaxInfo = Cast(MINMAXINFO Ptr,lParam)
             pMinMaxInfo->ptMinTrackSize.x = Iif(pForm->MinimumWidth,  pForm->MinimumWidth,  pMinMaxInfo->ptMinTrackSize.x)
             pMinMaxInfo->ptMinTrackSize.y = iif(pForm->MinimumHeight, pForm->MinimumHeight, pMinMaxInfo->ptMinTrackSize.y)
             pMinMaxInfo->ptMaxTrackSize.x = Iif(pForm->MaximumWidth,  pForm->MaximumWidth,  pMinMaxInfo->ptMaxTrackSize.x)
             pMinMaxInfo->ptMaxTrackSize.y = iif(pForm->MaximumHeight, pForm->MaximumHeight, pMinMaxInfo->ptMaxTrackSize.y)
             return 0
          End If	 

      case WM_ACTIVATE
         pForm = Application.GetpFormObject(hWin)
         If pForm Then 
            ' Get the activation state
            if LoWord(wParam) = WA_INACTIVE THEN  ' Deactivated
               if pForm->OnDeactivate THEN pForm->OnDeactivate(*pForm, e)
            else ' Activated   
               if pForm->OnActivated THEN pForm->OnActivated(*pForm, e)
            END IF
         END IF

      Case WM_CLOSE
         pForm = Application.GetpFormObject(hWin)
         If pForm Then 
            if pForm->OnFormClosing then 
               pForm->OnFormClosing(*pForm, e)
               if e.Cancel THEN return true
            end if   
            ' Enables parent window keeping parent's zorder
            If pForm->IsModal Then EnableWindow( pForm->hWindowParent, True)
            DestroyWindow(hWin)
         End If   
          
      Case WM_DESTROY
         pForm = Application.GetpFormObject(hWin)
         If pForm Then 
            If pForm->OnFormClosed Then pForm->OnFormClosed(*pForm, e)
            ' Always let the WM_DESTROY complete
            e.Handled = False
            If pForm->pWindow Then 
               ' Remove the form to the Application Form collection
               Application.Forms.remove_bydata(pForm)
               Delete pForm->pWindow
               pForm->pWindow = 0
               pForm->hWindow = 0
            End If   
            If pForm->IsMainForm Then 
               ' If this is the main form then post a quit message
               PostQuitMessage(0)
            End If
         End If
      
  
      case WM_COMMAND
         ' wParam: LOWORD contains the button's control identifier. 
         '         HIWORD specifies the notification code.
         ' lParam: Handle to the button.
         ' Determine the pointer based on the Window handle generating the notification.
         Dim As Long lNotification = Hiword(wParam)
         pForm = Application.GetpFormObject(hWin)
         pNode = Application.GetControlByHandle( Cast(HWnd, lParam) )
         
         If pNode Then
            Select Case pNode->CtrlType 
               Case ControlType.Label
                  pLabel = Cast(wfxLabel Ptr, pNode->pData)
                  If pLabel AndAlso lNotification = STN_CLICKED AndAlso pLabel->OnClick Then pLabel->OnClick(*pLabel, e)
                  If pLabel AndAlso lNotification = STN_DBLCLK AndAlso pLabel->OnMouseDoubleClick Then pLabel->OnMouseDoubleClick(*pLabel, e)
               Case ControlType.Button
                  pButton = Cast(wfxButton Ptr, pNode->pData)
                  If pButton AndAlso lNotification = BN_CLICKED AndAlso pButton->OnClick Then pButton->OnClick(*pButton, e)
               Case ControlType.CheckBox
                  pCheckBox = Cast(wfxCheckBox Ptr, pNode->pData)
                  If pCheckBox AndAlso pCheckBox->OnClick Then pCheckBox->OnClick(*pCheckBox, e)
               Case ControlType.OptionButton
                  pOption = Cast(wfxOptionButton Ptr, pNode->pData)
                  If pOption AndAlso pOption->OnClick Then pOption->OnClick(*pOption, e)
               Case ControlType.TextBox
                  pTextBox = Cast(wfxTextBox Ptr, pNode->pData)
                  If pTextBox AndAlso lNotification = EN_CHANGE AndAlso pTextBox->OnTextChanged Then pTextBox->OnTextChanged(*pTextBox, e)
               Case ControlType.ListBox
                  pListBox = Cast(wfxListBox Ptr, pNode->pData)
                  If pListBox AndAlso lNotification = LBN_DBLCLK AndAlso pListBox->OnMouseDoubleClick Then pListBox->OnMouseDoubleClick(*pListBox, e)
                  If pListBox AndAlso lNotification = LBN_SELCHANGE AndAlso pListBox->OnClick Then pListBox->OnClick(*pListBox, e)
            End Select
         End If
         
         
      case WM_NOTIFY
         pForm = Application.GetpFormObject(hWin)
         Dim pNMHDR As NMHDR Ptr = Cast(NMHDR Ptr, lParam)
         Select Case pNMHDR->code 
            Case NM_CLICK
               ' Process clicking on the panels in the statusbar
               if pForm then
                  pNode = pForm->Controls.search_controltype(ControlType.StatusBar)
                  if pNode then 
                     pStatusBar = cast(wfxStatusBar ptr, pNode->pData)
                     if pStatusBar then
                        Dim lpnm As NMMOUSE Ptr = Cast(NMMOUSE Ptr, pNMHDR)
                        e.PanelClickIndex = lpnm->dwItemSpec  
                        e.x = lpnm->pt.x: e.y = lpnm->pt.y
                        if pStatusBar andalso pStatusBar->OnClick then pStatusBar->OnClick(*pStatusBar, e)
                     end if
                  end if
               end if
         end select
               
      Case WM_MOVING, WM_SIZING
         ' wParam: This parameter is not used.
         ' lParam: A pointer to a RECT structure with the current position of the window in screen coordinates. 
         '         To change the position of the drag rectangle, an application must change the members of this structure.
         pForm = Application.GetpFormObject(hWin)
         If pForm Then
            if pForm->Locked then 
               dim pRect as RECT ptr = cast(RECT ptr, lParam)
               dim rc as RECT = AfxGetWindowRect(hWin)
               *pRect = rc
               return true
            end if
         END IF

      Case WM_SIZE
         pForm = Application.GetpFormObject(hWin)
         If pForm Then 
            If pForm->OnResize Then pForm->OnResize(*pForm, e)
            ' If a StatusBar exists on this form then resize it.
            pNode = pForm->Controls.search_controltype(ControlType.StatusBar)
            if pNode then
               pStatusBar = cast(wfxStatusBar ptr, pNode->pData)
               SendMessage(pStatusBar->hWindow, uMsg, wParam, lParam)
            END IF
         END IF
      
      Case WM_CTLCOLORSTATIC, WM_CTLCOLOREDIT, WM_CTLCOLORBTN, WM_CTLCOLORLISTBOX 
         ' wParam: HDC of the control. 
         ' lParam: Handle to the control.
         ' Need to determine the child control handle that is sending the request to be painted.
         pNode = Application.GetControlByHandle( Cast(HWnd, lParam) )
         if pNode then 
            pCtrl = cast(wfxControl ptr, pNode->pData)
            if pCtrl THEN 
               SetTextColor(cast(HDC, wParam), pCtrl->ForeColor)
               SetBkColor(cast(HDC, wParam), pCtrl->BackColor)
               Return Cast(LRESULT, pCtrl->hBackBrush)
            end if   
         end if
         
      case WM_ERASEBKGND
         pForm = Application.GetpFormObject(hWin)
         If pForm Then 
            dim as Rect rc
            GetClientRect(hWin, @rc)
            FillRect(Cast(HDC, wParam), @rc, pForm->hBackBrush)
            return true
         end if   

      Case WM_MOVE
         pForm = Application.GetpFormObject(hWin)
         If pForm AndAlso pForm->OnMove Then pForm->OnMove(*pForm, e)

   End Select
   
   ' If the event was handled by the user then return true
   if e.Handled THEN return true

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
         ' Do not filter any types of messages. We want the dialog box manager to be
         ' able to correctly handle TAB, arrows, and focus rectangles, etc.
         
      Case WM_MOUSEMOVE, _
           WM_LBUTTONDBLCLK, WM_MBUTTONDBLCLK, WM_RBUTTONDBLCLK, _
           WM_LBUTTONDOWN, WM_MBUTTONDOWN, WM_RBUTTONDOWN, _
           WM_LBUTTONUP, WM_MBUTTONUP, WM_RBUTTONUP, _
           WM_SETFOCUS, WM_KILLFOCUS, _
           WM_MOUSELEAVE, WM_MOUSEHOVER
         If Application.HandleCommonMessages(hWin, uMsg, wParam, lParam) Then Return 0

      Case WM_KEYDOWN, WM_KEYUP, WM_CHAR
         ' If the key was handled then the WndProc will return True.
         ' Return 0 to prevent beep
         If Application.HandleCommonMessages(hWin, uMsg, wParam, lParam) Then Return 0
         
      Case WM_DESTROY
         ' Handle any final Destroy messages for the control and then return
         ' here to remove the subclassing.
         Application.HandleCommonMessages(hWin, uMsg, wParam, lParam) 
         ' REQUIRED: Remove control subclassing
         RemoveWindowSubclass( hWin, @wfxApplication.SubclassProc, uIdSubclass )
   End Select
    
   ' For messages that we don't deal with
   Function = DefSubclassProc(hWin, uMsg, wParam, lParam)

End Function

