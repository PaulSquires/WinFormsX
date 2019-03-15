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
   Dim pFrame      As wfxFrame Ptr
   Dim pPictureBox As wfxPictureBox Ptr
   Dim pButton     As wfxButton Ptr
   Dim pTextBox    As wfxTextBox Ptr
   Dim pMaskedEdit As wfxMaskedEdit Ptr
   Dim pCheckBox   As wfxCheckBox Ptr
   Dim pOption     As wfxOptionButton Ptr
   Dim pListBox    As wfxListBox Ptr
   dim pComboBox   as wfxComboBox ptr
   Dim pStatusBar  As wfxStatusBar Ptr
   Dim pMainMenu   As wfxMainMenu Ptr

   pNode = Application.GetControlByHandle(hWin)
   If pNode Then 
      pCtrl = Cast(wfxControl Ptr, pNode->pData)
      Select Case pNode->CtrlType 
         Case ControlType.Form:         pForm       = Cast(wfxForm Ptr, pNode->pData)
         Case ControlType.Label:        pLabel      = Cast(wfxLabel Ptr, pNode->pData)
         Case ControlType.Frame:        pFrame      = Cast(wfxFrame Ptr, pNode->pData)
         Case ControlType.PictureBox:   pPictureBox = Cast(wfxPictureBox Ptr, pNode->pData)
         Case ControlType.Button:       pButton     = Cast(wfxButton Ptr, pNode->pData)
         Case ControlType.TextBox:      pTextBox    = Cast(wfxTextBox Ptr, pNode->pData)
         Case ControlType.MaskedEdit:   pMaskedEdit = Cast(wfxMaskedEdit Ptr, pNode->pData)
         Case ControlType.CheckBox:     pCheckBox   = Cast(wfxCheckBox Ptr, pNode->pData)
         Case ControlType.OptionButton: pOption     = Cast(wfxOptionButton Ptr, pNode->pData)
         Case ControlType.ListBox:      pListBox    = Cast(wfxListBox Ptr, pNode->pData)
         Case ControlType.ComboBox:     pComboBox   = Cast(wfxComboBox Ptr, pNode->pData)
         Case ControlType.StatusBar:    pStatusBar  = Cast(wfxStatusBar Ptr, pNode->pData)
         Case ControlType.MainMenu:     pMainMenu   = Cast(wfxMainMenu Ptr, pNode->pData)
      End Select
   End If   
#EndMacro

#Macro WINFORMSX_HANDLE_MESSAGE(msg)    
   ' Bypass controls that do not handle focus or keyboard input
   #If( #msg <> "OnGotFocus" AndAlso #msg <> "OnLostFocus" AndAlso _
        #msg <> "OnKeyDown" AndAlso #msg <> "OnKeyUp" AndAlso #msg <> "OnKeyPress" )  
      #If(#msg <> "OnDestroy")  ' OnDestroy is FormClosed for forms.
         If pForm AndAlso pForm->##msg Then pForm->##msg(*pForm, e)
      #EndIf
      #If(#msg <> "OnMouseDoubleClick")  ' Handled through STN_DBLCLK notification
         If pLabel AndAlso pLabel->##msg Then pLabel->##msg(*pLabel, e)
      #EndIf
      If pStatusBar AndAlso pStatusBar->##msg Then pStatusBar->##msg(*pStatusBar, e)
      If pPictureBox AndAlso pPictureBox->##msg Then pPictureBox->##msg(*pPictureBox, e)
      If pFrame AndAlso pFrame->##msg Then pFrame->##msg(*pFrame, e)
   #EndIf
   ' ListBox doubleclicks are handled through LBN_DBLCLK notifications
   ' ListBox Clicks are handled through LBN_SELCHANGE
   ' ComboBox Clicks are handled through CBN_SELCHANGE
   #If(#msg <> "OnMouseDoubleClick" AndAlso #msg <> "OnClick")  
      If pListBox AndAlso pListBox->##msg Then pListBox->##msg(*pListBox, e)
      If pComboBox AndAlso pComboBox->##msg Then pComboBox->##msg(*pComboBox, e)
   #EndIf
   If pButton AndAlso pButton->##msg Then pButton->##msg(*pButton, e)
   If pTextBox AndAlso pTextBox->##msg Then pTextBox->##msg(*pTextBox, e)
   If pMaskedEdit AndAlso pMaskedEdit->##msg Then pMaskedEdit->##msg(*pMaskedEdit, e)
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
         ' If this is a Label/ListBox then redraw so hot colors will be used
         if pLabel then pLabel->Refresh
         if pListBox then pListBox->Refresh
         
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
         ' If this is a Label/ListBox then redraw so normal colors will be used
         if pLabel then pLabel->Refresh
         if pListBox then pListBox->Refresh
      
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
      
  
      CASE WM_INITMENUPOPUP
         ' wParam: A handle to the drop-down menu or submenu.
         ' lParam: The low-order word specifies the zero-based relative position of 
         '         the menu item that opens the drop-down menu or submenu.
         '         The high-order word indicates whether the drop-down menu is the 
         '         window menu. If the menu is the window menu, this parameter 
         '         is TRUE; otherwise, it is FALSE.
         if hiword( lParam ) = false then
            pForm = Application.GetpFormObject(hWin)
            if pForm then pNode = pForm->Controls.search_controltype(ControlType.MainMenu)
            if pNode then pMainMenu = cast(wfxMainMenu ptr, pNode->pData)
            if pMainMenu andalso pMainMenu->OnPopup then 
               dim byref iMenuItem as wfxMenuItem = pMainMenu->ByPopupMenuHandle(cast(HMENU, wParam))
               pMainMenu->OnPopup(iMenuItem, e)
            end if
         end if
         
      
      case WM_COMMAND
         ' wParam: LOWORD contains the button's control identifier. 
         '         HIWORD specifies the notification code.
         ' lParam: Handle to the button.
         ' Determine the pointer based on the Window handle generating the notification.

         '
         ' Message 
         ' Source        wParam (high word)   wParam (low word)      lParam
         ' ------------------------------------------------------------------------
         ' Menu          0                    Menu identifier        0
         '                                    (IDM_*) 
         ' Accelerator   1                    Accelerator 
         '                                    identifier (IDM_*)     0
         ' Control       Control-defined      Control identifier     Handle to the  
         '               notification code                           control window
         '

         Dim As Long lNotification = Hiword(wParam)
         pForm = Application.GetpFormObject(hWin)

         ' Handle the different types of notifications
         if (lNotification = 0 or lNotification = 1) andalso (lParam = 0) then
            ' Menu notification or accelerator key
            if pForm then pNode = pForm->Controls.search_controltype(ControlType.MainMenu)
            if pNode then pMainMenu = cast(wfxMainMenu ptr, pNode->pData)
            if pMainMenu andalso pMainMenu->OnClick then 
               ' Get the MenuItem that is being opened based on MenuID
               ' Need to search all menus and submenus until we find a match.
               dim byref iMenuItem as wfxMenuItem = pMainMenu->ByMenuID(loword(wParam))
               pMainMenu->OnClick(iMenuItem, e)
            end if
         else
            ' Control 
            pNode = Application.GetControlByHandle( Cast(HWnd, lParam) )
         end if
         
         
         If pNode Then
            Select Case pNode->CtrlType 
               Case ControlType.Label
                  pLabel = Cast(wfxLabel Ptr, pNode->pData)
                  If pLabel AndAlso lNotification = STN_CLICKED AndAlso pLabel->OnClick Then pLabel->OnClick(*pLabel, e)
                  If pLabel AndAlso lNotification = STN_DBLCLK AndAlso pLabel->OnMouseDoubleClick Then pLabel->OnMouseDoubleClick(*pLabel, e)
                  if pLabel then pLabel->Refresh
               Case ControlType.Button
                  pButton = Cast(wfxButton Ptr, pNode->pData)
                  If pButton AndAlso lNotification = BN_CLICKED AndAlso pButton->OnClick Then pButton->OnClick(*pButton, e)
               Case ControlType.CheckBox
                  pCheckBox = Cast(wfxCheckBox Ptr, pNode->pData)
                  If pCheckBox AndAlso lNotification = BN_CLICKED AndAlso pCheckBox->OnClick Then pCheckBox->OnClick(*pCheckBox, e)
               Case ControlType.OptionButton
                  pOption = Cast(wfxOptionButton Ptr, pNode->pData)
                  If pOption AndAlso lNotification = BN_CLICKED AndAlso pOption->OnClick Then pOption->OnClick(*pOption, e)
               Case ControlType.TextBox
                  pTextBox = Cast(wfxTextBox Ptr, pNode->pData)
                  If pTextBox AndAlso lNotification = EN_CHANGE AndAlso pTextBox->OnTextChanged Then pTextBox->OnTextChanged(*pTextBox, e)
               Case ControlType.MaskedEdit
                  pMaskedEdit = Cast(wfxMaskedEdit Ptr, pNode->pData)
                  If pMaskedEdit AndAlso lNotification = EN_CHANGE AndAlso pMaskedEdit->OnTextChanged Then pMaskedEdit->OnTextChanged(*pMaskedEdit, e)
               Case ControlType.ListBox
                  pListBox = Cast(wfxListBox Ptr, pNode->pData)
                  If pListBox AndAlso lNotification = LBN_DBLCLK AndAlso pListBox->OnMouseDoubleClick Then pListBox->OnMouseDoubleClick(*pListBox, e)
                  If pListBox AndAlso lNotification = LBN_SELCHANGE AndAlso pListBox->OnClick Then pListBox->OnClick(*pListBox, e)
                  if pListBox then pListBox->Refresh
               Case ControlType.ComboBox
                  pComboBox = Cast(wfxComboBox Ptr, pNode->pData)
                  If pComboBox AndAlso lNotification = CBN_DBLCLK AndAlso pComboBox->OnMouseDoubleClick Then pComboBox->OnMouseDoubleClick(*pComboBox, e)
                  If pComboBox AndAlso lNotification = CBN_SELCHANGE AndAlso pComboBox->OnClick Then pComboBox->OnClick(*pComboBox, e)
                  If pComboBox AndAlso lNotification = CBN_DROPDOWN AndAlso pComboBox->OnDropDown Then pComboBox->OnDropDown(*pComboBox, e)
                  If pComboBox AndAlso lNotification = CBN_CLOSEUP AndAlso pComboBox->OnDropDownClosed Then pComboBox->OnDropDownClosed(*pComboBox, e)
                  If pComboBox AndAlso lNotification = CBN_EDITCHANGE AndAlso pComboBox->OnTextChanged Then pComboBox->OnTextChanged(*pComboBox, e)
            End Select
         End If
         
         
      case WM_NOTIFY
         Dim pNMHDR As NMHDR Ptr = Cast(NMHDR Ptr, lParam)
         if pNMHDR = 0 then exit function
         Dim As Long lNotification = pNMHDR->code
         
         pNode = Application.GetControlByHandle( pNMHDR->hwndFrom )
         
         If pNode Then

            Select Case pNode->CtrlType 
               Case ControlType.StatusBar
                  ' Process clicking on the panels in the statusbar
                  pStatusBar = cast(wfxStatusBar ptr, pNode->pData)
                  if pStatusBar then
                     Dim lpnm As NMMOUSE Ptr = Cast(NMMOUSE Ptr, pNMHDR)
                     e.PanelClickIndex = lpnm->dwItemSpec  
                     e.x = lpnm->pt.x: e.y = lpnm->pt.y
                     if pStatusBar andalso pStatusBar->OnClick then pStatusBar->OnClick(*pStatusBar, e)
                  end if
                  
               Case ControlType.PictureBox
                  pPictureBox = Cast(wfxPictureBox Ptr, pNode->pData)
                  If pPictureBox AndAlso lNotification = NM_CLICK AndAlso pPictureBox->OnClick Then pPictureBox->OnClick(*pPictureBox, e)
                  If pPictureBox AndAlso lNotification = NM_DBLCLK AndAlso pPictureBox->OnMouseDoubleClick Then pPictureBox->OnMouseDoubleClick(*pPictureBox, e)
                  
            end select
            
         end if
         
      
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
      
      
      Case WM_CTLCOLORSTATIC, WM_CTLCOLORLISTBOX 
         ' WinFormsX Label and ListBox controls handle color using OwnerDraw via WM_DRAWITEM
         
     
      case WM_CTLCOLOREDIT, WM_CTLCOLORBTN
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


      case WM_MEASUREITEM
         dim lpmis As MEASUREITEMSTRUCT Ptr = cast( MEASUREITEMSTRUCT Ptr, lParam )
         if lpmis = 0 then exit function
         if pForm = 0 then exit function
         ' WM_MEASUREITEM is sent prior to valid hWindow so we need to manually
         ' search all controls in the controls collection to get a matching CtrlID.
         pNode = pForm->Controls.get_first
         do until pNode = 0
            if pNode->CtrlType = ControlType.ListBox then
               ' Set the height of the List box items. 
               pListBox = cast( wfxListBox ptr, pNode->pData )
               if pListBox then
                  lpmis->itemHeight = pListBox->Parent->pWindow->ScaleY( pListBox->ItemHeight )
                  return true
               end if
            end if
            pNode = pForm->Controls.get_next( pNode )
         LOOP
         
         
      case WM_DRAWITEM
         Dim memDC as HDC      ' Double buffering
         Dim hbit As HBITMAP   ' Double buffering
         Dim As RECT rc
         Dim wszText As WString * MAX_PATH

         dim lpdis As DRAWITEMSTRUCT Ptr = cast( DRAWITEMSTRUCT Ptr, lParam )
         if lpdis = 0 then exit function
         
         pNode = Application.GetControlByHandle( lpdis->hwndItem )
         If pNode Then
            pCtrl = cast(wfxControl ptr, pNode->pData)
            SaveDC(lpdis->hDC)
            if pCtrl = 0 then exit function
             
            if ( lpdis->itemAction = ODA_DRAWENTIRE ) orelse _
               ( lpdis->itemAction = ODA_SELECT ) then

               Select Case pNode->CtrlType 
                  Case ControlType.Label   '' LABEL CONTROL
                     pLabel = cast(wfxLabel ptr, pNode->pData)
                     if pLabel = 0 then exit function
                     GetClientRect( lpdis->hwndItem, @rc )
                     
                     memDC = CreateCompatibleDC( lpdis->hDC )
                     hbit  = CreateCompatibleBitmap( lpdis->hDC, rc.right, rc.bottom )
                     If hbit Then hbit = SelectObject( memDC, hbit )

                     dim as HFONT _hFont = AfxGetWindowFont( lpdis->hwndItem )
                     SelectObject( memDC, _hFont )
                     
                     dim as POINT pt
                     GetCursorPos( @pt )
                     MapWindowPoints( 0, lpdis->hwndItem, cast( POINT ptr, @pt ), 1 )
                     dim as Boolean IsHot = PtInRect( @rc, pt )
                     
                     ' Paint the entire background
                     FillRect( memDC, @rc, iif( IsHot, pLabel->hBackBrushHot, pLabel->hBackBrush) )

                     ' Prepare and paint the text coloring
                     SetBkColor( memDC, iif( IsHot, pLabel->BackColorHot, pLabel->BackColor) )   
                     SetTextColor( memDC, iif( IsHot, pLabel->ForeColorHot, pLabel->ForeColor) )

                     dim as long lFormat = pLabel->GetTextAlignStyleValue( pLabel->TextAlign )
                     lFormat = lFormat or DT_SINGLELINE
                     if pLabel->UseMnemonic = false then lFormat = lFormat or DT_NOPREFIX
                     
                     ' pad the drawing rectangle to allow left and right margins
                     dim as RECT rcText = lpdis->rcItem
                     rcText.left = rcText.left + pLabel->Parent->ScaleX(4) 
                     rcText.right = rcText.right - pLabel->Parent->ScaleX(4) 
                     
                     wszText = AfxGetWindowText( lpdis->hwndItem )
                     DrawText( memDC, wszText, -1, Cast(lpRect, @rcText), lFormat )

                     BitBlt lpdis->hDC, 0, 0, rc.right, rc.bottom, memDC, 0, 0, SRCCOPY 

                     ' Cleanup
                     If hbit  Then DeleteObject SelectObject(memDC, hbit)
                     If memDC Then DeleteDC memDC


                  Case ControlType.ListBox   '' LISTBOX CONTROL
                     If lpdis->itemID = -1 Then Exit Function
                     pListBox = cast(wfxListBox ptr, pNode->pData)
                     if pListBox = 0 then exit function
                     
                     dim as COLORREF clrBack, clrFore
                     dim as HBRUSH hBrushBack
                     
                     rc = lpdis->rcItem
                     dim as long nWidth  = rc.right-rc.left
                     dim as long nHeight = rc.bottom-rc.top 

                     memDC = CreateCompatibleDC( lpdis->hDC )
                     hbit  = CreateCompatibleBitmap( lpdis->hDC, nWidth, nHeight )
                     If hbit Then hbit = SelectObject( memDC, hbit )

                     dim as HFONT _hFont = AfxGetWindowFont( lpdis->hwndItem )
                     SelectObject( memDC, _hFont )

                     ' CLEAR BACKGROUND
                     If (lpdis->itemState And ODS_SELECTED) Then     
                        clrBack = pListBox->BackColorSelected 
                        clrFore = pListBox->ForeColorSelected 
                        hBrushBack = pListBox->hBackBrushSelected
                     else
                        clrBack = pListBox->BackColor 
                        clrFore = pListBox->ForeColor 
                        hBrushBack = pListBox->hBackBrush

                        dim as POINT pt
                        GetCursorPos( @pt )
                        MapWindowPoints( 0, lpdis->hwndItem, cast( POINT ptr, @pt ), 1 )
                        if PtInRect( @rc, pt ) then
                           clrBack = pListBox->BackColorHot
                           clrFore = pListBox->ForeColorHot
                           hBrushBack = pListBox->hBackBrushHot
                        end if   
                     end if
                     
                     ' Paint the entire background
                     ' Create our rect that works with the entire line
                     SetRect(@rc, 0, 0, nWidth, nHeight)
                     FillRect( memDC, @rc, hBrushBack )

                     ' Prepare and paint the text coloring
                     SetBkColor( memDC, clrBack )   
                     SetTextColor( memDC, clrFore )

                     dim as long lFormat = pListBox->GetTextAlignStyleValue( pListBox->TextAlign )
                     lFormat = lFormat or DT_SINGLELINE or DT_NOPREFIX 

                     ' pad the drawing rectangle to allow left and right margins
                     dim as RECT rcText = rc
                     rcText.left = rcText.left + pListBox->Parent->ScaleX(4) 
                     rcText.right = rcText.right - pListBox->Parent->ScaleX(4) 

                     wszText = AfxGetListBoxText( lpdis->hwndItem, lpdis->itemID )
                     DrawText( memDC, wszText, -1, Cast(lpRect, @rcText), lFormat )

                     BitBlt lpdis->hDC, lpdis->rcItem.left, lpdis->rcItem.top, _
                            nWidth, nHeight, memDC, 0, 0, SRCCOPY 

                     ' Cleanup
                     If hbit  Then DeleteObject SelectObject(memDC, hbit)
                     If memDC Then DeleteDC memDC

               end select

            end if
            RestoreDC(lpdis->hDC, -1)
         end if
         
      
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
         
      case WM_ERASEBKGND   
         WINFORMSX_DIM_POINTERS
         ' Only erase the bottom portion of the listbox that extends from the last item
         ' to the bottom edge of the listbox. All other lines are already drawn. This helps
         ' reduce screen flicker.
         if pListBox then
            dim as RECT rc: GetClientRect( hWin, @rc )
            ' Caculate the top of the rectangle. This is basically 
            
            ' If the number of lines in the listbox is less than the number per page then 
            ' calculate from last item to bottom of listbox, otherwise calculate based on
            ' the mod of the lineheight to listbox height so we can color the partial line
            ' that won't be displayed at the bottom of the list.
            dim as long itemHeight = pListBox->Parent->pWindow->ScaleY(pListBox->ItemHeight)
            dim as long NumItems = pListBox->Items.Count
            dim as long ItemsPerPage = ( rc.bottom \ itemHeight )
            dim as long nTopIndex = SendMessage( hWin, LB_GETTOPINDEX, 0, 0 ) 
            dim as long visible_rows = 0

            if NumItems > 0 then
               ItemsPerPage = (rc.bottom - rc.top) / itemHeight
               dim as long bottom_index = (nTopIndex + ItemsPerPage) - 1
               if bottom_index >= NumItems then bottom_index = NumItems - 1
               visible_rows = (bottom_index - nTopIndex) + 1
            end if

            rc.top = visible_rows * itemHeight 
            if rc.top < rc.bottom then
               dim as HDC _hDC = cast(HDC, wParam)
               FillRect( _hDC, @rc, pListBox->hBackBrush  )
            end if

            return TRUE
         end if
         
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

