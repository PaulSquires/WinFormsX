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
   this.MSG_WINFORMS_FORMREADY = RegisterWindowMessage( wstr("MSG_WINFORMS_FORMREADY") )
   this.MSG_WINFORMS_AFTERCHECK = RegisterWindowMessage( wstr("MSG_WINFORMS_AFTERCHECK") )
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
''
''   M A C R O S
''
#Macro WINFORMSX_DIM_POINTERS    
   Dim pNode        As wfxLListNode Ptr
   Dim e            As wfxEventArgs
   Dim pCtrl        As wfxControl Ptr
   Dim pForm        As wfxForm Ptr
#ifdef CODEGEN_LABEL
   Dim pLabel       As wfxLabel Ptr
#endif
#ifdef CODEGEN_FRAME
   Dim pFrame       As wfxFrame Ptr
#endif
#ifdef CODEGEN_PICTUREBOX
   Dim pPictureBox  As wfxPictureBox Ptr
#endif
#ifdef CODEGEN_BUTTON
   Dim pButton      As wfxButton Ptr
#endif
#ifdef CODEGEN_TEXTBOX
   Dim pTextBox     As wfxTextBox Ptr
#endif
#ifdef CODEGEN_RICHEDIT
   Dim pRichEdit    As wfxRichEdit Ptr
#endif
#ifdef CODEGEN_MASKEDEDIT
   Dim pMaskedEdit  As wfxMaskedEdit Ptr
#endif
#ifdef CODEGEN_CHECKBOX
   Dim pCheckBox    As wfxCheckBox Ptr
#endif
#ifdef CODEGEN_OPTIONBUTTON
   Dim pOption      As wfxOptionButton Ptr
#endif
#ifdef CODEGEN_LISTBOX
   Dim pListBox     As wfxListBox Ptr
#endif
#ifdef CODEGEN_COMBOBOX
   dim pComboBox    as wfxComboBox ptr
#endif
#ifdef CODEGEN_STATUSBAR
   Dim pStatusBar   As wfxStatusBar Ptr
#endif   
#ifdef CODEGEN_MAINMENU
   Dim pMainMenu    As wfxMainMenu Ptr
#endif
#ifdef CODEGEN_TOOLBAR
   Dim pToolBar     As wfxToolBar Ptr
#endif   
#ifdef CODEGEN_PROGRESSBAR
   Dim pProgressBar As wfxProgressBar Ptr
#endif
#ifdef CODEGEN_LISTVIEW
   Dim pListView    As wfxListView Ptr
#endif
#ifdef CODEGEN_MONTHCALENDAR
   Dim pMonthCal    As wfxMonthCalendar Ptr
#endif
#ifdef CODEGEN_DATETIMEPICKER
   Dim pDateTimePicker As wfxDateTimePicker Ptr
#endif
#ifdef CODEGEN_TABCONTROL
   Dim pTabControl As wfxTabControl Ptr
#endif
#ifdef CODEGEN_UPDOWN
   Dim pUpDown As wfxUpDown Ptr
#endif
#ifdef CODEGEN_TREEVIEW
   Dim pTreeView As wfxTreeView Ptr
#endif

   pNode = Application.GetControlByHandle(hWin)
   If pNode Then 
      pCtrl = Cast(wfxControl Ptr, pNode->pData)
      Select Case pNode->CtrlType 
         Case ControlType.Form:         pForm        = Cast(wfxForm Ptr, pNode->pData)
#ifdef CODEGEN_LABEL
         Case ControlType.Label:        pLabel       = Cast(wfxLabel Ptr, pNode->pData)
#endif
#ifdef CODEGEN_FRAME
         Case ControlType.Frame:        pFrame       = Cast(wfxFrame Ptr, pNode->pData)
#endif
#ifdef CODEGEN_PICTUREBOX
         Case ControlType.PictureBox:   pPictureBox  = Cast(wfxPictureBox Ptr, pNode->pData)
#endif
#ifdef CODEGEN_BUTTON
         Case ControlType.Button:       pButton      = Cast(wfxButton Ptr, pNode->pData)
#endif
#ifdef CODEGEN_TEXTBOX
         Case ControlType.TextBox:      pTextBox     = Cast(wfxTextBox Ptr, pNode->pData)
#endif
#ifdef CODEGEN_RICHEDIT
         Case ControlType.RichEdit:     pRichEdit    = Cast(wfxRichEdit Ptr, pNode->pData)
#endif
#ifdef CODEGEN_MASKEDEDIT
         Case ControlType.MaskedEdit:   pMaskedEdit  = Cast(wfxMaskedEdit Ptr, pNode->pData)
#endif
#ifdef CODEGEN_CHECKBOX
         Case ControlType.CheckBox:     pCheckBox    = Cast(wfxCheckBox Ptr, pNode->pData)
#endif
#ifdef CODEGEN_OPTIONBUTTON
         Case ControlType.OptionButton: pOption      = Cast(wfxOptionButton Ptr, pNode->pData)
#endif
#ifdef CODEGEN_LISTBOX
         Case ControlType.ListBox:      pListBox     = Cast(wfxListBox Ptr, pNode->pData)
#endif
#ifdef CODEGEN_COMBOBOX
         Case ControlType.ComboBox:     pComboBox    = Cast(wfxComboBox Ptr, pNode->pData)
#endif
#ifdef CODEGEN_STATUSBAR
         Case ControlType.StatusBar:    pStatusBar   = Cast(wfxStatusBar Ptr, pNode->pData)
#endif            
#ifdef CODEGEN_MAINMENU
         Case ControlType.MainMenu:     pMainMenu    = Cast(wfxMainMenu Ptr, pNode->pData)
#endif
#ifdef CODEGEN_TOOLBAR
         Case ControlType.ToolBar:      pToolBar     = Cast(wfxToolBar Ptr, pNode->pData)
#endif
#ifdef CODEGEN_PROGRESSBAR
         Case ControlType.ProgressBar:  pProgressBar = Cast(wfxProgressBar Ptr, pNode->pData)
#endif
#ifdef CODEGEN_LISTVIEW
         Case ControlType.ListView:     pListView    = Cast(wfxListView Ptr, pNode->pData)
#endif
#ifdef CODEGEN_MONTHCALENDAR
         Case ControlType.MonthCalendar: pMonthCal   = Cast(wfxMonthCalendar Ptr, pNode->pData)
#endif
#ifdef CODEGEN_DATETIMEPICKER
         Case ControlType.DateTimePicker: pDateTimePicker = Cast(wfxDateTimePicker Ptr, pNode->pData)
#endif
#ifdef CODEGEN_TABCONTROL
         Case ControlType.TabControl: pTabControl = Cast(wfxTabControl Ptr, pNode->pData)
#endif
#ifdef CODEGEN_UPDOWN
         Case ControlType.UpDown: pUpDown = Cast(wfxUpDown Ptr, pNode->pData)
#endif
#ifdef CODEGEN_TREEVIEW
         Case ControlType.TreeView: pTreeView = Cast(wfxTreeView Ptr, pNode->pData)
#endif
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
#ifdef CODEGEN_LABEL
         If pLabel AndAlso pLabel->##msg Then pLabel->##msg(*pLabel, e)
#endif
      #EndIf
#ifdef CODEGEN_STATUSBAR
      If pStatusBar AndAlso pStatusBar->##msg Then pStatusBar->##msg(*pStatusBar, e)
#endif
#ifdef CODEGEN_PICTUREBOX
      If pPictureBox AndAlso pPictureBox->##msg Then pPictureBox->##msg(*pPictureBox, e)
#endif
#ifdef CODEGEN_FRAME
      If pFrame AndAlso pFrame->##msg Then pFrame->##msg(*pFrame, e)
#endif
#ifdef CODEGEN_PROGRESSBAR
      If pProgressBar AndAlso pProgressBar->##msg Then pProgressBar->##msg(*pProgressBar, e)
#endif
   #EndIf
   ' ListBox doubleclicks are handled through LBN_DBLCLK notifications
   ' ListBox Clicks are handled through LBN_SELCHANGE
   ' ComboBox Clicks are handled through CBN_SELCHANGE
   #If(#msg <> "OnMouseDoubleClick" AndAlso #msg <> "OnClick")  
#ifdef CODEGEN_LISTBOX
      If pListBox AndAlso pListBox->##msg Then pListBox->##msg(*pListBox, e)
#endif
#ifdef CODEGEN_COMBOBOX
      If pComboBox AndAlso pComboBox->##msg Then pComboBox->##msg(*pComboBox, e)
#endif
   #EndIf

#ifdef CODEGEN_BUTTON
   If pButton AndAlso pButton->##msg Then pButton->##msg(*pButton, e)
#endif
#ifdef CODEGEN_TEXTBOX 
   If pTextBox AndAlso pTextBox->##msg Then pTextBox->##msg(*pTextBox, e)
#endif
#ifdef CODEGEN_RICHEDIT
   If pRichEdit AndAlso pRichEdit->##msg Then pRichEdit->##msg(*pRichEdit, e)
#endif
#ifdef CODEGEN_MASKEDEDIT
   If pMaskedEdit AndAlso pMaskedEdit->##msg Then pMaskedEdit->##msg(*pMaskedEdit, e)
#endif
#ifdef CODEGEN_CHECKBOX
   If pCheckBox AndAlso pCheckBox->##msg Then pCheckBox->##msg(*pCheckBox, e)
#endif
#ifdef CODEGEN_OPTIONBUTTON
   If pOption AndAlso pOption->##msg Then pOption->##msg(*pOption, e)
#endif
#ifdef CODEGEN_LISTVIEW
   If pListView AndAlso pListView->##msg Then pListView->##msg(*pListView, e)
#endif
#ifdef CODEGEN_MONTHCALENDAR
   If pMonthCal AndAlso pMonthCal->##msg Then pMonthCal->##msg(*pMonthCal, e)
#endif
#ifdef CODEGEN_DATETIMEPICKER
   If pDateTimePicker AndAlso pDateTimePicker->##msg Then pDateTimePicker->##msg(*pDateTimePicker, e)
#endif
#ifdef CODEGEN_TABCONTROL
   If pTabControl AndAlso pTabControl->##msg Then pTabControl->##msg(*pTabControl, e)
#endif
#ifdef CODEGEN_UPDOWN
   If pUpDown AndAlso pUpDown->##msg Then pUpDown->##msg(*pUpDown, e)
#endif
#ifdef CODEGEN_TREEVIEW
   If pTreeView AndAlso pTreeView->##msg Then pTreeView->##msg(*pTreeView, e)
#endif
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
   e.Ctrl    = iif( GetKeyState(VK_CONTROL) < 0, true, false )
   e.Shift   = iif( GetKeyState(VK_SHIFT) < 0, true, false )
   e.ALT     = iif( GetKeyState(VK_MENU) < 0, true, false )

   dim as POINT pt
   GetCursorPos( @pt )
   e.pt = pt
   e.x = e.pt.x
   e.y = e.pt.y
   
   Select Case uMsg
      Case WM_MOUSEMOVE
         e.LButton = (wParam And MK_LBUTTON)
         e.MButton = (wParam And MK_MBUTTON)
         e.RButton = (wParam And MK_RBUTTON)

      case WM_LBUTTONDOWN, WM_LBUTTONUP, WM_LBUTTONDBLCLK
         e.LButton = true

      case WM_MBUTTONDOWN, WM_MBUTTONUP, WM_MBUTTONDBLCLK
         e.MButton = true
         
      case WM_RBUTTONDOWN, WM_RBUTTONUP, WM_RBUTTONDBLCLK
         e.RButton = true

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
''  Generic function to retrieve form object based on form name.
''  Used by the Tab Control to retrieve child Tab Page window handles.
''
function wfxApplication.GetpFormObjectByName( byref wszFormName as wstring ) as wfxForm ptr
   dim pNode as wfxLListNode ptr
   dim pForm as wfxForm ptr
   dim idx as long = 0
   
   dim as CWSTR wszFormNameUCASE = ucase(wszFormName)
   
   pNode = this.Forms.get_first
   do until pNode = 0
      If pNode->CtrlType = ControlType.Form Then
         pForm = Cast(wfxForm Ptr, pNode->pData)
         if pForm then
            if ucase(pForm->Name) = wszFormNameUCASE then
               return pForm
            end if   
         end if
      End If
      ' Get the next form in the application 
      idx = idx + 1  
      pNode = this.Forms.get_next(idx)
   loop
   function = 0
end function


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
#ifdef CODEGEN_BUTTON
   If pMsg->message = WM_KEYDOWN Then
      If pMsg->wParam = VK_RETURN Then
         pActiveForm = Application.GetpFormObject(hWndForm)
         If pActiveForm andalso pActiveForm->AcceptButton then
            if pActiveForm->AcceptButton Then
               ' Simulates the user clicking a button. This message causes the button to receive the
               ' WM_LBUTTONDOWN and WM_LBUTTONUP messages, and the button's parent window to receive a
               ' BN_CLICKED notification code.
               SendMessage(pActiveForm->AcceptButton->hWindow, BM_CLICK, 0, 0)
               Return True
            end if
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
#endif
            
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
         If e.Handled Then Return True
      Case WM_KEYUP
         WINFORMSX_HANDLE_MESSAGE(OnKeyUp)
         If e.Handled Then Return True
      Case WM_CHAR
         WINFORMSX_HANDLE_MESSAGE(OnKeyPress)
         If e.Handled Then Return True
   End Select
   
   ' If this is a multiline textbox then test to see if a TAB key should be
   ' allowed as a valid character (the default action) or if the TAB should
   ' move control focus.
#ifdef CODEGEN_TEXTBOX
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
#endif

   Return False
End Function



''
''  Begins running a standard wfxApplication message loop and 
''  makes the specified form visible.
''
Function wfxApplication.Run( Byref pForm As wfxForm ) As LRESULT

   ' Ensure the window is placed on screen should the user had changed 
   ' the logical ordering of a multiple display setup.
   AfxForceVisibleDisplay( pForm.pWindow->hWindow )
   
   ' Show the window and update its client area (this will also create any child controls)
   pForm.IsMainForm = true
   Function = pForm.ShowDialog()
     
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
''  Generic function to retrieve control object via Windows handle
''
function wfxApplication.GetControlByHandle( byval hWindow as hwnd ) as wfxLListNode ptr
   dim pNodeCtrl as wfxLListNode ptr
   dim pNode as wfxLListNode ptr
   dim pForm as wfxForm ptr
   dim idx as long = 0
   
   ' Search all Forms and each control in each Form.
   pNode = this.Forms.get_first
   do until pNode = 0
      ' Does the hWindow match the form itself
      if pNode->hWindow = hWindow then return pNode
      ' Search all the controls on the form for a match
      pForm = cast(wfxForm ptr, pNode->pData)
      pNodeCtrl = pForm->Controls.search_handle(hWindow)
      if pNodeCtrl then return pNodeCtrl
      ' Get the next form in the application 
      idx = idx + 1  
      pNode = this.Forms.get_next(idx)
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
         ' If this is a Label/ListBox/StatusBar then redraw so hot colors will be used
#ifdef CODEGEN_LABEL
         if pLabel then pLabel->Refresh
#endif
#ifdef CODEGEN_LISTBOX
         if pListBox then pListBox->Refresh
#endif         
#ifdef CODEGEN_STATUSBAR
         if pStatusBar then 
            ' Determine which Panel the mouse is over and set it to Hot
            dim as Boolean bHit = false
            dim as RECT rcPanel
            dim as POINT pt
            GetCursorPos( @pt )
            MapWindowPoints( 0, hWin, cast( POINT ptr, @pt ), 1 )
            for i as long = 0 to pStatusBar->Panels.Count - 1
               StatusBar_GetRect( hWin, i, @rcPanel )
               pStatusBar->Panel(i).IsHot = PtInRect(@rcPanel, pt) 
               ' Set a Tooltip for the panel
               if pStatusBar->Panel(i).IsHot then
                  bHit = true
                  pStatusBar->ToolTip = pStatusBar->Panel(i).ToolTip
               end if   
            next   
            ' If the mouse has left a Panel but is still over a portion
            ' of the uncovered statusbar control then clear the tooltip.
            if bHit = false then pStatusBar->ToolTip = ""
         end if
#endif
         ' There is no such thing as a WM_MOUSEENTER message so we need to simulate it
         ' here by using a tracking variable and TRACKMOUSEEVENT.
         dim as DWORD dwFlags = TME_HOVER Or TME_LEAVE
#ifdef CODEGEN_LISTVIEW
         ' Do not allow HOVER on a ListView as it somehow invokes hot tracking an
         ' automatic row selection when the mouse hovers over it. Not desirable.
         if pListView then dwFlags = TME_LEAVE
#endif         
         If pCtrl Then
            If pCtrl->IsTracking = False Then
               pCtrl->IsTracking = True
               Dim tme As TrackMouseEvent
               tme.cbSize = Sizeof(TrackMouseEvent)
               tme.dwFlags = dwFlags
               tme.hwndTrack = hWin
               TrackMouseEvent(@tme) 
               WINFORMSX_HANDLE_MESSAGE(OnMouseEnter)
            End If
         End If
           
       
      Case WM_MOUSELEAVE
         If pCtrl Then pCtrl->IsTracking = False 
         WINFORMSX_HANDLE_MESSAGE(OnMouseLeave)
         ' If this is a Label/ListBox/StatusBar then redraw so normal colors will be used
#ifdef CODEGEN_LABEL
         if pLabel then pLabel->Refresh
#endif
#ifdef CODEGEN_LISTBOX
         if pListBox then pListBox->Refresh
#endif         
#ifdef CODEGEN_STATUSBAR
         if pStatusBar then 
            ' Mouse has left the control so set all Panels to not Hot.
            for i as long = 0 to pStatusBar->Panels.Count - 1
               pStatusBar->Panel(i).IsHot = false
               pStatusBar->ToolTip = ""
            next
         end if
#endif
       
       
      Case WM_MOUSEHOVER
#ifdef CODEGEN_LISTVIEW
         ' Don't allow MouseHover for a ListView control
#else
         WINFORMSX_HANDLE_MESSAGE(OnMouseHover)
#endif            
      
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
#ifdef CODEGEN_TEXTBOX
            If pTextBox AndAlso pTextBox->OnClick Then pTextBox->OnClick(*pTextBox, e)
#endif
#ifdef CODEGEN_RICHEDIT
            If pRichEdit AndAlso pRichEdit->OnClick Then pRichEdit->OnClick(*pRichEdit, e)
#endif
#ifdef CODEGEN_DATETIMEPICKER
            If pDateTimePicker AndAlso pDateTimePicker->OnClick Then pDateTimePicker->OnClick(*pDateTimePicker, e)
#endif
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
''  wfxApplication General Timer control handling procedure
''
static sub wfxApplication.TimerProc( byval hWin    as HWND, _
                                     byval uMsg    as UINT, _
                                     byval TimerID as UINT ptr, _
                                     byval dwTime  as DWORD _
                                     )
               
#ifdef CODEGEN_TIMER
   ' Fill the EventArgs variable with any info related to this message
   Dim e As wfxEventArgs
   Application.SetEventArgs(uMsg, 0, 0, e)

   ' Determine the Form that the incoming timer belongs to and then
   ' dispatch to any defined TimedEvent event.
   dim pTimer as wfxTimer ptr
   dim pNode as wfxLListNode ptr
   dim pForm as wfxForm ptr = Application.GetpFormObject(hWin)
   if pForm then
      for i as long = 0 to pForm->Controls.size - 1
         pNode = pForm->Controls.get_index(i)
         if pNode then
            pTimer = Cast(wfxTimer Ptr, pNode->pData)
            If pTimer AndAlso pTimer->TimerID = TimerID then
               if pTimer->OnElapsed Then pTimer->OnElapsed(*pTimer, e)
               if pTimer->AutoReset = false then pTimer->StopTimer
            end if
         end if
      next
   end if   
#endif
end sub


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

      case Application.MSG_WINFORMS_FORMREADY
         ' Handle any user defined FormReady event handler. This message is send via
         ' PostMessage from the Form's creation function.
         pForm = Application.GetpFormObject(hWin)
         If pForm Then 
            if pForm->OnFormReady THEN pForm->OnFormReady(*pForm, e)
         end if
         
         
      case Application.MSG_WINFORMS_AFTERCHECK
#ifdef CODEGEN_TREEVIEW
         ' Custom message fired via PostMessage to simulate AfterCheck when a user
         ' clicks on a TreeView checkbox.
         ' wParam = hTree item
         ' lParam = pTreeView pointer
         pTreeView = Cast(wfxTreeView Ptr, lParam)
         if pTreeView = 0 then exit function
         dim pTreeViewNode as wfxTreeNode ptr 
         pTreeViewNode = cast(wfxTreeNode ptr, TreeView_GetlParam( pTreeView->hWindow, cast(HTREEITEM, wParam)))
         if pTreeViewNode then pTreeView->TreeNode = *pTreeViewNode
         if pTreeView->OnAfterCheck Then pTreeView->OnAfterCheck(*pTreeView, e)
#endif         
          
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
            If pForm->IsModal Then 
               if pForm->hWindowParent then
                  EnableWindow( pForm->hWindowParent, True)
               end if
            end if      
         End If   
         DestroyWindow(hWin)
      
      
      case WM_NCDESTROY
         ' At this point all of the child controls and main form have been destroyed
         pForm = Application.GetpFormObject(hWin)
         If pForm Then 
            ' Remove any previously added controls from this form. We do it here because 
            ' each time the form is shown we need to re-initialize any of the default 
            ' control/form properties.
            pForm->Controls.clear

            ' Set any necessary Window handles to zero to ensure that they get re-created.
            pForm->hWindow = 0
            
#ifdef CODEGEN_MAINMENU
            pForm->MainMenu.Handle = 0
            pForm->MainMenu.MenuItems.Handle = 0
#endif
#ifdef CODEGEN_TOOLBAR
            pForm->ToolBar.hWindow = 0
            pForm->ToolBar.hRebar = 0
#endif
#ifdef CODEGEN_STATUSBAR
            pForm->StatusBar.hWindow = 0
            pForm->StatusBar.Panels.hWindow = 0
#endif      
            
            ' Re-Initialize the properties of the controls and the form itself so that the
            ' user can continue to interact with fresh copy of the form in case they want
            ' to show that form again.
            pForm->InitializeComponent( pForm )

         end if
         
         
      Case WM_DESTROY
         pForm = Application.GetpFormObject(hWin)
         If pForm Then 
            If pForm->OnFormClosed Then pForm->OnFormClosed(*pForm, e)
            ' Always let the WM_DESTROY complete
            e.Handled = False

#ifdef CODEGEN_TIMER
            ' Kill any Timers that may still be firing
            dim pTimer as wfxTimer ptr
            for i as long = 0 to pForm->Controls.size - 1
               pNode = pForm->Controls.get_index(i)
               if pNode then
                  pTimer = Cast(wfxTimer Ptr, pNode->pData)
                  If pTimer andalso pTimer->CtrlType = ControlType.Timer then
                     pTimer->StopTimer
                     If pTimer->OnDestroy Then pTimer->OnDestroy(*pTimer, e)
                  end if
               end if
            next
#endif

            ' Make sure to delete all controls so that their subclasses are reset
            dim pNode as wfxLListNode ptr 
            for i as long = 0 to pForm->Controls.size - 1
               pNode = pForm->Controls.get_index(i)
               if pNode then
                  if pNode->hWindow then 
                     DestroyWindow( pNode->hWindow )
                     pNode->hWindow = 0
                  end if
               end if
            next

            If pForm->pWindow Then 
               ' Delete the CWindow of the form.
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
#ifdef CODEGEN_MAINMENU
         if hiword( lParam ) = false then
            pForm = Application.GetpFormObject(hWin)
            if pForm then pNode = pForm->Controls.search_controltype(ControlType.MainMenu)
            if pNode then pMainMenu = cast(wfxMainMenu ptr, pNode->pData)
            if pMainMenu andalso pMainMenu->OnPopup then 
               dim byref iMenuItem as wfxMenuItem = pMainMenu->ByPopupMenuHandle(cast(HMENU, wParam))
               pMainMenu->OnPopup(iMenuItem, e)
            end if
         end if
#endif         
      
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
#ifdef CODEGEN_MAINMENU
            ' Menu notification or accelerator key
            if pForm then pNode = pForm->Controls.search_controltype(ControlType.MainMenu)
            if pNode then pMainMenu = cast(wfxMainMenu ptr, pNode->pData)
            if pMainMenu andalso pMainMenu->OnClick then 
               ' Get the MenuItem that is being opened based on MenuID
               ' Need to search all menus and submenus until we find a match.
               dim byref iMenuItem as wfxMenuItem = pMainMenu->ByMenuID(loword(wParam))
               pMainMenu->OnClick(iMenuItem, e)
            end if
#endif
         else
            ' Control
            pNode = Application.GetControlByHandle( Cast(HWnd, lParam) )
         end if
         
         
         If pNode Then
            Select Case pNode->CtrlType
#ifdef CODEGEN_TOOLBAR
               case ControlType.ToolBar
                  pToolBar = Cast(wfxToolBar Ptr, pNode->pData)
                  if pToolBar then
                     ' Convert the command id to button index
                     pToolBar->ClickIndex = Toolbar_CommandToIndex(pToolBar->hWindow, loword(wParam))
                     pToolBar->ClickDropDownIndex = -1
                     if pToolBar->OnClick Then pToolBar->OnClick(*pToolBar, e)
                  end if
#endif
#ifdef CODEGEN_LABEL
               Case ControlType.Label
                  pLabel = Cast(wfxLabel Ptr, pNode->pData)
                  If pLabel AndAlso lNotification = STN_CLICKED AndAlso pLabel->OnClick Then pLabel->OnClick(*pLabel, e)
                  If pLabel AndAlso lNotification = STN_DBLCLK AndAlso pLabel->OnMouseDoubleClick Then pLabel->OnMouseDoubleClick(*pLabel, e)
                  if pLabel then pLabel->Refresh
#endif
#ifdef CODEGEN_BUTTON
               Case ControlType.Button
                  pButton = Cast(wfxButton Ptr, pNode->pData)
                  If pButton AndAlso lNotification = BN_CLICKED AndAlso pButton->OnClick Then pButton->OnClick(*pButton, e)
#endif
#ifdef CODEGEN_CHECKBOX
               Case ControlType.CheckBox
                  pCheckBox = Cast(wfxCheckBox Ptr, pNode->pData)
                  If pCheckBox AndAlso lNotification = BN_CLICKED AndAlso pCheckBox->OnClick Then pCheckBox->OnClick(*pCheckBox, e)
#endif
#ifdef CODEGEN_OPTIONBUTTON
               Case ControlType.OptionButton
                  pOption = Cast(wfxOptionButton Ptr, pNode->pData)
                  If pOption AndAlso lNotification = BN_CLICKED AndAlso pOption->OnClick Then pOption->OnClick(*pOption, e)
#endif
#ifdef CODEGEN_TEXTBOX
               Case ControlType.TextBox
                  pTextBox = Cast(wfxTextBox Ptr, pNode->pData)
                  If pTextBox AndAlso lNotification = EN_CHANGE AndAlso pTextBox->OnTextChanged Then pTextBox->OnTextChanged(*pTextBox, e)
#endif
#ifdef CODEGEN_RICHEDIT
               Case ControlType.RichEdit
                  pRichEdit = Cast(wfxRichEdit Ptr, pNode->pData)
                  If pRichEdit AndAlso lNotification = EN_CHANGE AndAlso pRichEdit->OnTextChanged Then pRichEdit->OnTextChanged(*pRichEdit, e)
#endif
#ifdef CODEGEN_MASKEDEDIT
               Case ControlType.MaskedEdit
                  pMaskedEdit = Cast(wfxMaskedEdit Ptr, pNode->pData)
                  If pMaskedEdit AndAlso lNotification = EN_CHANGE AndAlso pMaskedEdit->OnTextChanged Then pMaskedEdit->OnTextChanged(*pMaskedEdit, e)
#endif
#ifdef CODEGEN_LISTBOX
               Case ControlType.ListBox
                  pListBox = Cast(wfxListBox Ptr, pNode->pData)
                  If pListBox AndAlso lNotification = LBN_DBLCLK AndAlso pListBox->OnMouseDoubleClick Then pListBox->OnMouseDoubleClick(*pListBox, e)
                  If pListBox AndAlso lNotification = LBN_SELCHANGE AndAlso pListBox->OnClick Then pListBox->OnClick(*pListBox, e)
                  if pListBox then pListBox->Refresh
#endif
#ifdef CODEGEN_COMBOBOX
               Case ControlType.ComboBox
                  pComboBox = Cast(wfxComboBox Ptr, pNode->pData)
                  If pComboBox AndAlso lNotification = CBN_DBLCLK AndAlso pComboBox->OnMouseDoubleClick Then pComboBox->OnMouseDoubleClick(*pComboBox, e)
                  If pComboBox AndAlso lNotification = CBN_SELCHANGE AndAlso pComboBox->OnClick Then pComboBox->OnClick(*pComboBox, e)
                  If pComboBox AndAlso lNotification = CBN_DROPDOWN AndAlso pComboBox->OnDropDown Then pComboBox->OnDropDown(*pComboBox, e)
                  If pComboBox AndAlso lNotification = CBN_CLOSEUP AndAlso pComboBox->OnDropDownClosed Then pComboBox->OnDropDownClosed(*pComboBox, e)
                  If pComboBox AndAlso lNotification = CBN_EDITCHANGE AndAlso pComboBox->OnTextChanged Then pComboBox->OnTextChanged(*pComboBox, e)
#endif
               Case Else
                  ' To prevent an empty case structure
            End Select
         End If
         
         
      case WM_NOTIFY
         Dim pNMHDR As NMHDR Ptr = Cast(NMHDR Ptr, lParam)
         if pNMHDR = 0 then exit function
         Dim As UINT lNotification = pNMHDR->code
         
#ifdef CODEGEN_TOOLBAR
         if lNotification = TTN_GETDISPINFO then
            dim lpttt as TOOLTIPTEXT ptr = cast(TOOLTIPTEXT ptr, pNMHDR)
            dim tbb as wfxToolBarButton
            pForm = Application.GetpFormObject(hWin)
            if pForm then 
               dim as long nIndex = Toolbar_CommandToIndex( pForm->ToolBar.hWindow, lpttt->hdr.idFrom )
               tbb = pForm->ToolBar.Buttons.ByIndex(nIndex)
               lpttt->lpszText = tbb.ToolTip
               return CTRUE
            end if   
         end if
#endif

#ifdef CODEGEN_MONTHCALENDAR
         ' Need to handle the MCN_GETDAYSTATE notification here prior to the pNode lookup because
         ' the calendar handle is not added to that list until after this notifcation had already
         ' been sent.
         ' Correct value for MCN_GETDAYSTATE (pre-Vista value is defined in FB's commctrl.bi file)
         if lNotification = (MCN_FIRST - 1) then   
            ' We set all of the displayed days to normal (rather than bold) and then allow the
            ' user to change the values via their WM_NOTIFY. A more elegant solution would be
            ' to call an WinFBE event that captures the user's intentions.
            if AfxGetWindowClassName(pNMHDR->hwndFrom) = "SysMonthCal32" then
               ' We set all of the displayed days to normal (rather than bold) and then allow the
               ' user to change the values via their WM_NOTIFY. A more elegant solution would be
               ' to call an WinFBE event that captures the user's intentions.
               dim as NMDAYSTATE ptr pNMDayState = cast(NMDAYSTATE ptr, pNMHDR)
               dim as MONTHDAYSTATE rgMonths(12)
               pNMDayState->prgDayState = @rgMonths(0)
            end if
         end if
#endif


         pNode = Application.GetControlByHandle( pNMHDR->hwndFrom )

         If pNode Then

            Select Case pNode->CtrlType 

#ifdef CODEGEN_RICHEDIT
               case ControlType.RichEdit
                  if lNotification = EN_SELCHANGE then
                     pRichEdit = Cast(wfxRichEdit Ptr, pNode->pData)
                     if pRichEdit then
                        if pRichEdit->OnSelectionChanged Then pRichEdit->OnSelectionChanged(*pRichEdit, e)
                     end if
                  end if

                  if lNotification = EN_CHANGE then
                     pRichEdit = Cast(wfxRichEdit Ptr, pNode->pData)
                     if pRichEdit then
                        if pRichEdit->OnTextChanged Then pRichEdit->OnTextChanged(*pRichEdit, e)
                     end if
                  end if

#endif

#ifdef CODEGEN_UPDOWN
               case ControlType.UpDown
                  pUpDown = Cast(wfxUpDown Ptr, pNode->pData)

                  if lNotification = UDN_DELTAPOS then
                     dim lpnmud as NMUPDOWN ptr = cast(NMUPDOWN ptr, pNMHDR)
                     ' The Win32 api documentation appears to be incorrect for
                     ' value of the iDelta field:
                     ' From the docs: The iDelta member of the structure is a 
                     ' signed integer that contains the proposed change in position. 
                     ' If the user has clicked the up button, this is a positive value. 
                     ' If the user has clicked the down button, this is a negative value.
                     ' It appears to be the opposite in practice so I will invert the
                     ' value before assigning it to the UpDown control's Delta property.
                     pUpDown->Delta = (lpnmud->iDelta * -1)
                     if pUpDown->OnClick Then pUpDown->OnClick(*pUpDown, e)
                     if e.Cancel then return true
                  end if
#endif


#ifdef CODEGEN_TABCONTROL
               case ControlType.TabControl
                  pTabControl = Cast(wfxTabControl Ptr, pNode->pData)

                  dim as long nTabIndex = TabCtrl_GetCurSel(pNMHDR->hwndFrom)
                  
                  if lNotification = NM_CLICK then
                     if pTabControl->OnClick Then pTabControl->OnClick(*pTabControl, e)
                  end if
                  
                  if lNotification = TCN_SELCHANGING then
                     if pTabControl->OnSelecting Then 
                        if pTabControl->OnSelecting(*pTabControl, e) = true then return true
                     end if
                     if e.Cancel then return true
                     pTabControl->HideTabPage( nTabIndex )
                  end if

                  if lNotification = TCN_SELCHANGE then
                     if pTabControl->OnSelected Then pTabControl->OnSelected(*pTabControl, e)
                     ' Show the current TabPage
                     pTabControl->ShowTabPage( nTabIndex )
                  end if   
#endif

#ifdef CODEGEN_MONTHCALENDAR
               case ControlType.MonthCalendar
                  pMonthCal = Cast(wfxMonthCalendar Ptr, pNode->pData)

                  if lNotification = MCN_SELECT then
                     if pMonthCal->OnClick Then pMonthCal->OnClick(*pMonthCal, e)
                  end if

                  if lNotification = MCN_SELCHANGE then
                     if pMonthCal->OnSelectionChanged Then pMonthCal->OnSelectionChanged(*pMonthCal, e)
                  end if
#endif

#ifdef CODEGEN_DATETIMEPICKER
               case ControlType.DateTimePicker
                  pDateTimePicker = Cast(wfxDateTimePicker Ptr, pNode->pData)
                  if lNotification = DTN_DATETIMECHANGE then
                     if pDateTimePicker->OnDateTimeChanged Then pDateTimePicker->OnDateTimeChanged(*pDateTimePicker, e)
                  end if
#endif

#ifdef CODEGEN_LISTVIEW
               case ControlType.ListView
                  pListView = Cast(wfxListView Ptr, pNode->pData)

                  if lNotification = LVN_KEYDOWN then
                     dim plvkd as NMLVKEYDOWN ptr = cast(NMLVKEYDOWN ptr, pNMHDR)
                     ' user pressed space, toggle flag on selected item
                     if plvkd->wVKey = VK_SPACE then
                        ' Toggle if some item is selected
                        if pListView->SelectedIndex <> -1 then
                           pListView->Item(pListView->SelectedIndex).Checked = _
                              not pListView->Item(pListView->SelectedIndex).Checked
                           pListView->Refresh   
                        end if
                     end if
                     return false
                  end if
                  
                  
                  if lNotification = LVN_ITEMCHANGED then
                     dim lpStateChange as NMLISTVIEW ptr = cast(NMLISTVIEW ptr, pNMHDR)
                     IF (lpStateChange->uChanged AND LVIF_STATE) = LVIF_STATE THEN  
                        if (lpStateChange->uNewState AND LVIS_SELECTED) = LVIS_SELECTED then 
                          e.ListViewRow = lpStateChange->iItem
                          e.ListViewColumn = -1
                          if pListView->OnItemSelectionChanged Then pListView->OnItemSelectionChanged(*pListView, e)
                        end if          
                     end if
                  end if   
                  
                  
                  select case lNotification 
                     case NM_CLICK
                        if pListView then 
                           ' Test to see if the checkbox was clicked.
                           dim hitinfo as LVHITTESTINFO
                           dim as POINT pt
                           
                           GetCursorPos( @pt )
                           ScreenToClient( pNMHDR->hwndFrom, @pt )
                           hitinfo.pt = pt
                           e.ListViewColumn = -1
                           e.ListViewRow = SendMessage( pNMHDR->hwndFrom, LVM_SUBITEMHITTEST, 0, cast(ULONG_PTR, @hitinfo) ) 
                           if e.ListViewRow <> -1 then e.ListViewColumn = hitinfo.iSubItem

                           ' Toggle if some item is selected
                           if e.ListViewRow <> -1 then
                              if (hitinfo.flags and LVHT_ONITEMSTATEICON) = LVHT_ONITEMSTATEICON then
                                 pListView->Item(e.ListViewRow).Checked = _
                                    not pListView->Item(e.ListViewRow).Checked
                                 pListView->Refresh  
                              end if 
                           end if
                           
                           ' Invoke the Click event
                           if pListView->OnClick Then pListView->OnClick(*pListView, e)
                        end if
                     
                     case NM_RETURN
                        ' Invoke the Click event
                        e.ListViewRow = -1
                        e.ListViewColumn = -1
                        e.KeyChar = 13
                        e.KeyCode = VK_RETURN
                        if pListView then e.ListViewRow = pListView->SelectedIndex
                        if pListView->OnClick Then pListView->OnClick(*pListView, e)
                     case NM_RCLICK   
                        ' Invoke the RightClick event
                        if pListView then pListView->HitTest( e.ListViewRow, e.ListViewColumn )
                        if pListView->OnRightClick Then pListView->OnRightClick(*pListView, e)
                     case NM_DBLCLK   
                        ' Invoke the DoubleClick event
                        if pListView then pListView->HitTest( e.ListViewRow, e.ListViewColumn )
                        if pListView->OnDoubleClick Then pListView->OnDoubleClick(*pListView, e)
                     case LVN_COLUMNCLICK 
                        dim lpnm as NMLISTVIEW ptr = cast(NMLISTVIEW ptr, pNMHDR)
                        e.ListViewRow = -1
                        e.ListViewColumn = lpnm->iSubItem
                        if pListView->OnColumnClick Then pListView->OnColumnClick(*pListView, e)
                  end select
                  
                     
                  if lNotification = LVN_GETDISPINFO then
                     dim plvdi as NMLVDISPINFO ptr = cast(NMLVDISPINFO ptr, pNMHDR)
                     
                     dim as long nItem = plvdi->item.iItem
                     dim as long nSubItem = plvdi->item.iSubItem

                     if (plvdi->item.mask and LVIF_TEXT) then
                        ' Do an array bounds check because it is possible that the user
                        ' has not defined all subitems to match the number of columns.
                        if (nItem >= 0) and (nSubItem <= pListView->Item(nItem).SubItems.Count - 1) then
                           plvdi->item.pszText = pListView->Item(nItem).SubItem(nSubItem).Text.sptr
                           plvdi->item.cchTextMax = len(pListView->Item(nItem).SubItem(nSubItem).Text)
                        end if
                     end if
                        
                     if (plvdi->item.mask and LVIF_IMAGE) then  
                       
                        ' Show check box?
                        if pListView->CheckBoxes then
                       
                           ' To enable check box, we have to enable state mask.
                           plvdi->item.mask = (plvdi->item.mask or LVIF_STATE)
                           plvdi->item.stateMask = LVIS_STATEIMAGEMASK

                           if pListView->Item(nItem).Checked then
                               ' Turn check box on
                               plvdi->item.state = INDEXTOSTATEIMAGEMASK(2)
                           else
                               ' Turn check box off
                               plvdi->item.state = INDEXTOSTATEIMAGEMASK(1)
                           end if
                        end if
                     end if
    
                     return CTRUE
                  end if
                  

                  if lNotification = NM_CUSTOMDRAW then
                     
                     dim plvcd as NMLVCUSTOMDRAW ptr = cast(NMLVCUSTOMDRAW ptr, pNMHDR)
                     Select Case plvcd->nmcd.dwDrawStage
                     
                        case CDDS_PREPAINT
                           return CDRF_NOTIFYITEMDRAW 
                            
                        case CDDS_ITEMPREPAINT
                           return CDRF_NOTIFYSUBITEMDRAW or CDRF_NOTIFYPOSTPAINT
                              
                        case (CDDS_ITEMPREPAINT or CDDS_SUBITEM)
                           ' to retrieve the line and column number of the cell
                           dim as long nItem = plvcd->nmcd.dwItemSpec 
                           dim as long nSubItem = plvcd->iSubItem     
                          
                           ' Do an array bounds check because it is possible that the user
                           ' has not defined all subitems to match the number of columns.
                           if nSubItem <= pListView->Item(nItem).SubItems.Count - 1 then
                              plvcd->clrText   = pListView->Item(nItem).SubItem(nSubItem).ForeColor
                              plvcd->clrTextBk = pListView->Item(nItem).SubItem(nSubItem).BackColor
                           end if
                              
                           if pListView->OddRowColorEnabled then
                              if pListView->OddRowColor <> plvcd->clrTextBk then
                                 if (nItem mod 2) = 0 then
                                    plvcd->clrTextBk = pListView->OddRowColor
                                 end if   
                              end if
                           end if
                              
                           return CDRF_DODEFAULT

                     End Select
                  End if
#endif
                  

#ifdef CODEGEN_TREEVIEW
               case ControlType.TreeView

                  pTreeView = Cast(wfxTreeView Ptr, pNode->pData)
                  if pTreeView = 0 then exit function
                  Dim pnmtv As NMTREEVIEW Ptr = Cast(NMTREEVIEW Ptr, pNMHDR)
                  dim pTreeViewNode as wfxTreeNode ptr
                  
                  IF lNotification = TVN_GETDISPINFO then
                     dim as NMTVDISPINFO ptr lptvdi = cast(NMTVDISPINFO ptr, pNMHDR) 
                     if (lptvdi->item.mask and TVIF_TEXT) then
                        pTreeViewNode = cast(wfxTreeNode ptr, lptvdi->item.lParam)
                        if pTreeViewNode then 
                           lptvdi->item.pszText = pTreeViewNode->Text.sptr
                           lptvdi->item.cchTextMax = len(pTreeViewNode->Text)
                        end if
                     end if
                     exit function
                  end if

                  IF lNotification = TVN_GETINFOTIP then
                     dim as NMTVGETINFOTIP ptr lpGetInfoTip = cast(NMTVGETINFOTIP ptr, pNMHDR) 
                     pTreeViewNode = cast(wfxTreeNode ptr, lpGetInfoTip->lParam)
                     if pTreeViewNode then 
                        if len(pTreeViewNode->ToolTipText) then
                           lpGetInfoTip->pszText = pTreeViewNode->ToolTipText.sptr
                           lpGetInfoTip->cchTextMax = len(pTreeViewNode->ToolTipText)
                        end if   
                     end if
                     exit function
                  end if

                  select case lNotification 
                     case NM_RETURN
                        ' Invoke the Click event
                        e.KeyChar = 13
                        e.KeyCode = VK_RETURN
                        pTreeViewNode = cast(wfxTreeNode ptr, _
                                        TreeView_GetlParam( pNMHDR->hwndFrom, pTreeView->GetSelectedNode.hNode))
                        if pTreeViewNode then pTreeView->TreeNode = *pTreeViewNode
                        if pTreeView->OnClick Then pTreeView->OnClick(*pTreeView, e)
                        exit function
                        
                     case NM_CLICK, NM_RCLICK
                        ' Process these click notifications prior to the change/expand notifications
                        ' because we want the OnMouseUp message to fire before the Click.
                        ' Test to see if the checkbox was clicked.
                        dim hitinfo as TVHITTESTINFO
                        dim as POINT pt
                         
                        GetCursorPos( @pt )
                        ScreenToClient( pNMHDR->hwndFrom, @pt )
                        hitinfo.pt = pt
                        SendMessage( pNMHDR->hwndFrom, TVM_HITTEST, 0, cast(ULONG_PTR, @hitinfo) ) 
          
                        pTreeViewNode = cast(wfxTreeNode ptr, TreeView_GetlParam( pNMHDR->hwndFrom, hitinfo.hItem))
                        if pTreeViewNode then pTreeView->TreeNode = *pTreeViewNode

                        ' If the checkbox was clicked then attempt to call the user defined OnBeforeCheck
                        ' to see if the user wishes to cancel the action. If not cancelled, then post
                        ' a message to simulate a notification for OnAfterCheck.
                        if lNotification = NM_CLICK then 
                           if (hitinfo.flags and TVHT_ONITEMSTATEICON) = TVHT_ONITEMSTATEICON then
                              if pTreeView->OnBeforeCheck Then 
                                 if pTreeView->OnBeforeCheck(*pTreeView, e) then return true
                                 if e.Cancel then return true
                                 ' Post a message to handle the OnAfterCheck
                                 PostMessage(hWin, Application.MSG_WINFORMS_AFTERCHECK, _
                                                   cast(UINT_PTR, hitinfo.hItem), cast(LONG_PTR, pTreeView))
                              end if
                           end if
                        end if
                            
                        ' Allow a click event if FullRowSelect is active and the hittest returns
                        ' the area to the right of the label, or if clicked on the label itself.
                        dim as Boolean bHit = false
                        if pTreeView->FullRowSelect then
                           if (hitinfo.flags and TVHT_ONITEMRIGHT) = TVHT_ONITEMRIGHT then bHit = true
                        end if
                        if (hitinfo.flags and TVHT_ONITEMLABEL) = TVHT_ONITEMLABEL then bHit = true                        
                        if bHit then  ' Invoke the Click event
                           if lNotification = NM_RCLICK then 
                              ' Treeview dows not send WM_RBUTTONUP so send the event during NM_RCLICK
                              e.RButton = true
                              if pTreeView->OnMouseUp Then pTreeView->OnMouseUp(*pTreeView, e)
                           end if
                           if pTreeView->OnClick Then pTreeView->OnClick(*pTreeView, e)
                        end if   
                        exit function
                  end select

                  select case lNotification
                     case TVN_SELCHANGED, TVN_SELCHANGING, TVN_ITEMEXPANDED, TVN_ITEMEXPANDING
                        ' Get the TreeView class node related to the hItem handle. The pointer
                        ' to the TreeViewNode is stored in the lParam of the node.
                        pTreeViewNode = cast(wfxTreeNode ptr, TreeView_GetlParam( pNMHDR->hwndFrom, pnmtv->itemNew.hItem))
                        if pTreeViewNode then pTreeView->TreeNode = *pTreeViewNode
                  end select
                  
                  if lNotification = TVN_SELCHANGING then
                     if pTreeView->OnBeforeSelect Then 
                        if pTreeView->OnBeforeSelect(*pTreeView, e) then return true
                        if e.Cancel then return true
                     end if
                  end if
                  if lNotification = TVN_SELCHANGED then
                     if pTreeView->OnAfterSelect Then pTreeView->OnAfterSelect(*pTreeView, e)
                  end if

                  if lNotification = TVN_ITEMEXPANDING then
                     if pnmtv->action = TVE_EXPAND then
                        if pTreeView->OnBeforeExpand Then 
                           if pTreeView->OnBeforeExpand(*pTreeView, e) then return true
                        end if
                     end if
                     if pnmtv->action = TVE_COLLAPSE then
                        if pTreeView->OnBeforeCollapse Then 
                           if pTreeView->OnBeforeCollapse(*pTreeView, e) then return true
                        end if
                     end if
                     if e.Cancel then return true
                  end if
                  if lNotification = TVN_ITEMEXPANDED then
                     if pnmtv->action = TVE_EXPAND then
                        if pTreeView->OnAfterExpand Then pTreeView->OnAfterExpand(*pTreeView, e)
                     end if
                     if pnmtv->action = TVE_COLLAPSE then
                        if pTreeView->OnAfterCollapse Then pTreeView->OnAfterCollapse(*pTreeView, e)
                     end if
                  end if
                  exit function
#endif


#ifdef CODEGEN_TOOLBAR
               case ControlType.ToolBar
                  pToolBar = Cast(wfxToolBar Ptr, pNode->pData)
                  if pToolBar then
                     if lNotification = TBN_DROPDOWN then
                        Dim ptbn As NMTOOLBAR Ptr = Cast(NMTOOLBAR Ptr, pNMHDR)
                        ' Convert the command id to button index
                        pToolBar->ClickDropDownIndex = Toolbar_CommandToIndex(pToolBar->hWindow, ptbn->iItem)
                        pToolBar->ClickIndex = -1
                        if pToolBar->OnClick Then pToolBar->OnClick(*pToolBar, e)
                     end if
                  end if
#endif

#ifdef CODEGEN_STATUSBAR
               Case ControlType.StatusBar
                  ' Process clicking on the panels in the statusbar
                  pStatusBar = cast(wfxStatusBar ptr, pNode->pData)
                  if pStatusBar then
                     if lNotification = NM_CLICK then
                        Dim lpnm As NMMOUSE Ptr = Cast(NMMOUSE Ptr, pNMHDR)
                        e.x = lpnm->pt.x: e.y = lpnm->pt.y
                        if pStatusBar andalso pStatusBar->OnClick then 
                           pStatusBar->ClickIndex = lpnm->dwItemSpec  
                           pStatusBar->OnClick(*pStatusBar, e)
                        end if
                     end if
                  end if
#endif
                  
#ifdef CODEGEN_PICTUREBOX
               Case ControlType.PictureBox
                  pPictureBox = Cast(wfxPictureBox Ptr, pNode->pData)
                  If pPictureBox AndAlso lNotification = NM_CLICK AndAlso pPictureBox->OnClick Then pPictureBox->OnClick(*pPictureBox, e)
                  If pPictureBox AndAlso lNotification = NM_DBLCLK AndAlso pPictureBox->OnMouseDoubleClick Then pPictureBox->OnMouseDoubleClick(*pPictureBox, e)
#endif
                  
               Case Else
               
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
#ifdef CODEGEN_STATUSBAR
            ' If a StatusBar exists on this form then resize it.
            pForm->SizeStatusBar()
#endif

#ifdef CODEGEN_TOOLBAR
            ' If a ToolBar exists on this form then resize it.
            pForm->SizeToolBar()
#endif

            ' Size/move any controls that had their Anchor property set. We are using
            ' the WinFBX CLayout class to handle this.
            if pForm->pLayout then
               pForm->pLayout->AdjustControls
               ' Need to refresh the Form because any Frame controls will disappear during the movements
               pForm->Refresh      
            end if   
            
            ' Allow the user to respond to the size message
            If pForm->OnResize Then pForm->OnResize(*pForm, e)
         END IF
      
      
      case WM_CTLCOLOREDIT, WM_CTLCOLORBTN, WM_CTLCOLORLISTBOX, WM_CTLCOLORSTATIC
         ' wParam: HDC of the control. 
         ' lParam: Handle to the control.
         ' Need to determine the child control handle that is sending the request to be painted.
         pNode = Application.GetControlByHandle( Cast(HWnd, lParam) )
         if pNode then 
            pCtrl = cast(wfxControl ptr, pNode->pData)
            if pCtrl THEN 
               select case pCtrl->CtrlType
                  case ControlType.Label , ControlType.ListBox 
                     ' WinFormsX Label and ListBox controls handle color using OwnerDraw via WM_DRAWITEM
                  case else
                     SetTextColor(cast(HDC, wParam), pCtrl->ForeColor)
                     SetBkColor(cast(HDC, wParam), pCtrl->BackColor)
                     Return Cast(LRESULT, pCtrl->hBackBrush)
               end select
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
#ifdef CODEGEN_LISTBOX
         dim lpmis As MEASUREITEMSTRUCT Ptr = cast( MEASUREITEMSTRUCT Ptr, lParam )
         if lpmis = 0 then exit function
         if pForm = 0 then exit function
         dim idx as long = 0
         ' WM_MEASUREITEM is sent prior to valid hWindow so we need to manually
         ' search all controls in the controls collection to get a matching CtrlID.
         pNode = pForm->Controls.get_first
         do until pNode = 0
            if pNode->CtrlType = ControlType.ListBox then
               ' Set the height of the List box items. 
               pListBox = cast( wfxListBox ptr, pNode->pData )
               if pListBox then
                  if pListBox->CtrlID = wParam then
                     lpmis->itemHeight = pListBox->Parent->pWindow->ScaleY( pListBox->ItemHeight )
                     return true
                  end if   
               end if
            end if
            idx = idx + 1
            pNode = pForm->Controls.get_next( idx )
         LOOP
 #endif        
         
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
            if pCtrl = 0 then exit function
             
#ifdef CODEGEN_STATUSBAR
            if pNode->CtrlType = ControlType.StatusBar then
               pStatusBar = cast(wfxStatusBar ptr, pNode->pData)
               if pStatusBar = 0 then exit function
               rc = lpdis->rcItem
               
               dim as long nItem = lpdis->itemID
               If (nItem < 0) or (nItem > pStatusBar->Panels.Count-1) Then Exit Function

               dim as long nImageWidth 
               dim as long nImageHeight

               ' The image/text output rectangle is positioned within the main rc rectangle
               ' depending on the alignment.
               dim as RECT rc1 = rc
               
               dim wszImageName as wstring * MAX_PATH
               wszImageName = pStatusBar->Panel(nItem).Icon
            
               dim as HANDLE hIcon
               dim hImageListNormal As HIMAGELIST 
               if len(wszImageName) then
                  Dim cx As Long = AfxScaleX(16) 
                  hImageListNormal = ImageList_Create( cx, cx, ILC_COLOR32 Or ILC_MASK, 1, 1)
                  dim as long ii = AfxGdipAddIconFromRes( hImageListNormal, GetModuleHandle(null), wszImageName )
                  hIcon = ImageList_GetIcon( hImageListNormal, ii, ILD_NORMAL )
                  if hIcon then
                     nImageWidth = AfxScaleX(16)
                     nImageHeight = AfxScaleY(16)
                  end if   
               End If   
               
               wszText = " " & pStatusBar->Panel(nItem).Text & " "
               dim as long nTextWidth = WinFBE_GetTextWidthPixels( lpdis->hwndItem, wszText )  

               dim as long nTotalWidth 
               if nImageWidth then nTotalWidth = nImageWidth + AfxScaleX(4)
               if nTextWidth  then nTotalWidth = nTotalWidth + nTextWidth
               
               select case pStatusBar->Panel(nItem).Alignment
                  case StatusBarPanelAlignment.Left
                     ' No need to do anything because rc1 is already the full size of rc.
                  case StatusBarPanelAlignment.Center
                     dim as long nPad = MAX(0, (rc.right - rc.left - nTotalWidth) / 2)
                     rc1.left = rc1.left + nPad
                  case StatusBarPanelAlignment.Right
                     rc1.left  = rc1.right - nTotalWidth
               end select
               
               SaveDC(lpdis->hDC)
   
               memDC = CreateCompatibleDC( lpdis->hDC )
               hbit  = CreateCompatibleBitmap( lpdis->hDC, rc.right, rc.bottom )
               If hbit Then hbit = SelectObject( memDC, hbit )

               dim as HFONT _hFont = AfxGetWindowFont( lpdis->hwndItem )
               SelectObject( memDC, _hFont )

               ' Paint the entire background
               dim as HBRUSH hBackBrush
               if pStatusBar->Panel(nItem).IsHot then
                  SetBkColor( memDC, pStatusBar->Panel(nItem).BackColorHot )   
                  SetTextColor( memDC, pStatusBar->Panel(nItem).ForeColorHot )
                  hBackBrush = CreateSolidBrush(pStatusBar->Panel(nItem).BackColorHot)
               else
                  SetBkColor( memDC, pStatusBar->Panel(nItem).BackColor )   
                  SetTextColor( memDC, pStatusBar->Panel(nItem).ForeColor )
                  hBackBrush = CreateSolidBrush(pStatusBar->Panel(nItem).BackColor)
               end if
               FillRect( memDC, @rc, hBackBrush )
               DeleteObject(hBackBrush)

               ' Output any defined icon for the panel
               if hIcon then
                  ' Center the image vertically within rc1
                  dim as long nPad = (rc1.bottom - rc1.top - nImageHeight) / 2
                  DrawIconEx( memDC, rc1.left, rc1.top + nPad, _
                                     hIcon, _
                                     nImageWidth, nImageHeight, 0, null, DI_NORMAL ) 
                  DeleteObject( hIcon )
                  ImageList_Destroy( hImageListNormal )
                  rc1.left = rc1.left + nImageWidth + AfxScaleX(4)
               end if
               
               ' Output any panel text
               dim as long lFormat = DT_LEFT Or DT_VCENTER or DT_SINGLELINE
               wszText = pStatusBar->Panel(nItem).Text
               DrawText( memDC, wszText, -1, Cast(lpRect, @rc1), lFormat )

               BitBlt lpdis->hDC, 0, 0, rc.right, rc.bottom, memDC, 0, 0, SRCCOPY 

               ' Cleanup
               If hbit  Then DeleteObject SelectObject(memDC, hbit)
               If memDC Then DeleteDC memDC
               RestoreDC(lpdis->hDC, -1)
            end if
#endif

            select case pNode->CtrlType 
#ifdef CODEGEN_LABEL
               Case ControlType.Label   '' LABEL CONTROL
                  if ( lpdis->itemAction = ODA_DRAWENTIRE ) orelse _
                     ( lpdis->itemAction = ODA_SELECT ) orelse _
                     ( lpdis->itemAction = ODA_FOCUS ) then

                     pLabel = cast(wfxLabel ptr, pNode->pData)
                     if pLabel = 0 then exit function
                     if lpdis->itemAction = ODA_FOCUS then return true

                     GetClientRect( lpdis->hwndItem, @rc )
                     
                     SaveDC(lpdis->hDC)
      
                     memDC = CreateCompatibleDC( lpdis->hDC )
                     hbit  = CreateCompatibleBitmap( lpdis->hDC, rc.right, rc.bottom )
                     If hbit Then hbit = SelectObject( memDC, hbit )

                     dim as HFONT _hFont = AfxGetWindowFont( lpdis->hwndItem )
                     SelectObject( memDC, _hFont )
                     
                     dim as Boolean IsHot = pCtrl->IsTracking

                     ' Paint the entire background
                     FillRect( memDC, @rc, iif( IsHot, pLabel->hBackBrushHot, pLabel->hBackBrush) )

                     ' Prepare and paint the text coloring
                     SetBkColor( memDC, iif( IsHot, pLabel->BackColorHot, pLabel->BackColor) )   
                     SetTextColor( memDC, iif( IsHot, pLabel->ForeColorHot, pLabel->ForeColor) )

                     dim as long lFormat = pLabel->GetTextAlignStyleValue( pLabel->TextAlign )
                     if pLabel->UseMnemonic = false then lFormat = lFormat or DT_NOPREFIX 
                     
                     ' pad the drawing rectangle to allow left and right margins
                     dim as RECT rcText = lpdis->rcItem
                     'rcText.left = rcText.left + pLabel->Parent->ScaleX(4) 
                     'rcText.right = rcText.right - pLabel->Parent->ScaleX(4) 
                     
                     dim as CWSTR wszCaption = AfxGetWindowText( lpdis->hwndItem )
                     DrawText( memDC, wszCaption.sptr, -1, Cast(lpRect, @rcText), lFormat )

                     BitBlt lpdis->hDC, 0, 0, rc.right, rc.bottom, memDC, 0, 0, SRCCOPY 

                     ' Cleanup
                     If hbit  Then DeleteObject SelectObject(memDC, hbit)
                     If memDC Then DeleteDC memDC
                     RestoreDC(lpdis->hDC, -1)
                     return true
                  end if   
#endif

               Case ControlType.ListBox   '' LISTBOX CONTROL
#ifdef CODEGEN_LISTBOX
                  if ( lpdis->itemAction = ODA_DRAWENTIRE ) orelse _
                     ( lpdis->itemAction = ODA_SELECT ) orelse _
                     ( lpdis->itemAction = ODA_FOCUS ) then
                     
                     If lpdis->itemID = -1 Then return true

                     pListBox = cast(wfxListBox ptr, pNode->pData)
                     if pListBox = 0 then exit function
                     
                     if lpdis->itemAction = ODA_FOCUS then return true


                     dim as COLORREF clrBack, clrFore
                     dim as HBRUSH hBrushBack
                     
                     rc = lpdis->rcItem
                     dim as long nWidth  = rc.right-rc.left
                     dim as long nHeight = rc.bottom-rc.top 

                     SaveDC(lpdis->hDC)

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

                     ' Draw a focus rectangle around the item
                     if pListBox->SelectionMode <> ListSelectionMode.None then
                        If (lpdis->itemState And ODS_SELECTED) Then     
                           DrawFocusRect( lpdis->hDC, @lpdis->rcItem ) 
                        end if
                     end if   
                     
                     BitBlt lpdis->hDC, lpdis->rcItem.left, lpdis->rcItem.top, _
                            nWidth, nHeight, memDC, 0, 0, SRCCOPY 

                     ' Cleanup
                     If hbit  Then DeleteObject SelectObject(memDC, hbit)
                     If memDC Then DeleteDC memDC
                     RestoreDC(lpdis->hDC, -1)
                     return true
                  end if   
#endif

            end select

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
                  ByVal _wParam As WPARAM, _               ' // First message parameter
                  ByVal _lParam As LPARAM, _               ' // Second message parameter
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
           WM_MOUSELEAVE, WM_MOUSEHOVER, _
           WM_DROPFILES
         If Application.HandleCommonMessages(hWin, uMsg, _wParam, _lParam) Then Return 0

      
      case WM_SIZE
#ifdef CODEGEN_TABCONTROL
         dim pNode as wfxLListNode ptr = Application.GetControlByHandle( hWin )
         If pNode Then
            Select Case pNode->CtrlType 
               case ControlType.TabControl
                  dim pTabControl as wfxTabControl Ptr = Cast(wfxTabControl Ptr, pNode->pData)
                  if pTabControl then pTabControl->AutoResizeTabPages
            end select      
         end if
#endif         


case WM_PAINT
#ifdef CODEGEN_LISTBOX
   dim pNode as wfxLListNode ptr = Application.GetControlByHandle( hWin )
   If pNode Then
      if pNode->CtrlType = ControlType.ListBox then
         dim pListBox as wfxListBox Ptr = Cast(wfxListBox Ptr, pNode->pData)
         if pListBox then
            if pListBox->Items.Count = 0 then
               ' already painted so prevent flicker by not painting again
               return 0
            end if
         end if      
      end if
   end if
#endif
                  

      case WM_ERASEBKGND
#ifdef CODEGEN_LISTBOX
         dim pNode as wfxLListNode ptr = Application.GetControlByHandle( hWin )
         
         If pNode Then
            Select Case pNode->CtrlType 
               case ControlType.ListBox

                  dim pListBox as wfxListBox Ptr = Cast(wfxListBox Ptr, pNode->pData)

                  ' Only erase the bottom portion of the listbox that extends from the last item
                  ' to the bottom edge of the listbox. All other lines are already drawn. This helps
                  ' reduce screen flicker.
                  if pListBox then
                     dim as RECT rc: GetClientRect( hWin, @rc )

                     ' If the number of lines in the listbox is less than the number per page then 
                     ' calculate from last item to bottom of listbox, otherwise calculate based on
                     ' the mod of the lineheight to listbox height so we can color the partial line
                     ' that won't be displayed at the bottom of the list.
                     dim as RECT rcItem
                     SendMessage( hWin, LB_GETITEMRECT, 0, cast(LPARAM, @rcItem) )
                     dim as long itemHeight = rcItem.bottom - rcItem.top
                     dim as long NumItems = pListBox->Items.Count
                     dim as long nTopIndex = SendMessage( hWin, LB_GETTOPINDEX, 0, 0 ) 
                     dim as long visible_rows = 0
                     dim as long ItemsPerPage = 0
                     dim as long bottom_index = 0
                     
                     if pListBox->MultiColumn = false then
                        if NumItems > 0 then
                           ItemsPerPage = (rc.bottom - rc.top) / itemHeight
                           bottom_index = (nTopIndex + ItemsPerPage) 
                           if bottom_index >= NumItems then bottom_index = NumItems - 1
                           visible_rows = (bottom_index - nTopIndex) + 1
                           rc.top = visible_rows * itemHeight 
                        end if

                        if rc.top < rc.bottom then
                           dim as HDC _hDC = cast(HDC, _wParam)
                           FillRect( _hDC, @rc, pListBox->hBackBrush  )
                        end if

                     else
                        ' Painting for multicolumn listbox.
                        ' Check if the last item in the listbox is visible within the listbox
                        ' client area. We now need to clear the space to the right of the column
                        ' that this item is appearing. If the last item is not visible, then that
                        ' means that the whole client area of thelistbox must already be covered
                        ' with listbox items and therefore no blank spaces need to be manually
                        ' painted.
                        dim as HDC _hDC = cast(HDC, _wParam)
                        dim as RECT rcIntersect
                        GetWindowRect( hWin, @rc )
                        SendMessage( hWin, LB_GETITEMRECT, NumItems - 1, cast(LPARAM, @rcItem) )
                        MapWindowPoints( hWin, null, cast( POINT ptr, @rcItem), 2 )
                        if IntersectRect( @rcIntersect, @rcItem, @rc ) then
                           ' Get the client coordinates again...
                           SendMessage( hWin, LB_GETITEMRECT, NumItems - 1, cast(LPARAM, @rcItem) )
                           
                           ' Paint the items in the column under the last item
                           GetClientRect( hWin, @rc )
                           rc.top = rcItem.bottom
                           rc.left = rcItem.left
                           FillRect( _hDC, @rc, pListBox->hBackBrush  )
                           
                           ' Paint everything to the right
                           GetClientRect( hWin, @rc )
                           rc.left = rcItem.right
                           FillRect( _hDC, @rc, pListBox->hBackBrush  )
                        end if   
                        ' Always do the bottom gap painting
                        ' Paint the gap area between the bottom of the column lists and the
                        ' listbox bottom itself. Get the rect of the last item in the first column.
                        dim as long NumColItems = SendMessage( hWin, LB_GETLISTBOXINFO, 0, 0 )
                        SendMessage( hWin, LB_GETITEMRECT, nTopIndex + NumColItems - 1, cast(LPARAM, @rcItem) )
                        GetClientRect( hWin, @rc )
                        rc.top = rcItem.bottom
                        FillRect( _hDC, @rc, pListBox->hBackBrush  )
                     end if
                     
                     ValidateRect( hWin, @rc )
                     return true
                  end if
            end select
         end if   
#endif


      case WM_NOTIFY
#ifdef CODEGEN_LISTVIEW
 
         Dim pNMHDR As NMHDR Ptr = Cast(NMHDR Ptr, _lParam)
         if pNMHDR = 0 then exit function
         Dim As UINT lNotification = pNMHDR->code
         
         dim pNode as wfxLListNode ptr = Application.GetControlByHandle( GetParent(pNMHDR->hwndFrom) )
         
         If pNode Then

            ' The ListView Header messages are sent to its parent (the ListView itself)
            ' so we handle CustomDraw in the ListView subclass.
            
            Select Case pNode->CtrlType 

               case ControlType.ListView
                  dim pListView as wfxListView Ptr = Cast(wfxListView Ptr, pNode->pData)
                  if (lNotification = NM_CUSTOMDRAW) andalso (pListView <> 0) then
                     
                     if pListView->HeaderThemed = false then
                        dim plvcd as NMLVCUSTOMDRAW ptr = cast(NMLVCUSTOMDRAW ptr, pNMHDR)
                        Select Case plvcd->nmcd.dwDrawStage
                        
                           Case CDDS_PREPAINT
                              return CDRF_NOTIFYITEMDRAW
                                 
                           Case CDDS_ITEMPREPAINT 
                              dim hLvHeader AS hwnd
                              dim nIndex AS long
                              dim nState AS long
                              dim wszText as WString * MAX_PATH
                              
                              nIndex = plvcd->nmcd.dwItemSpec
                              nState = plvcd->nmcd.uItemState

                              ' Get the header item text...
                              dim hdi AS HDITEM
                              hdi.mask = HDI_TEXT
                              hdi.pszText = @wszText
                              hdi.cchtextmax = SIZEOF(wszText)
                              hLvHeader = ListView_GetHeader(hWin)
                              Header_GetItem(hLvHeader, nIndex, @hdi)
      
                              ' Draw the button state...
                              IF (nState AND CDIS_SELECTED) THEN
                                 DrawFrameControl plvcd->nmcd.hdc, @plvcd->nmcd.rc, DFC_BUTTON, DFCS_BUTTONPUSH OR DFCS_PUSHED
                              ELSE
                                 DrawFrameControl plvcd->nmcd.hdc, @plvcd->nmcd.rc, DFC_BUTTON, DFCS_BUTTONPUSH
                              END IF

                              ' Paint the background
                              dim hBrush AS HBRUSH
                              InflateRect @plvcd->nmcd.rc, -2, -2
                              
                              if pListView then
                                 hBrush = CreateSolidBrush(pListView->HeaderBackColor)
                                 FillRect plvcd->nmcd.hdc, @plvcd->nmcd.rc, hBrush
                              end if
                              
                              SetBkMode plvcd->nmcd.hdc, TRANSPARENT
                              ' Change your text color here...
                              SetTextColor plvcd->nmcd.hdc, pListView->HeaderForeColor

                              ' Get the text alignment
                              dim as long nAlign 
                              if pListView then
                                 ' Do array bounds check in case columns are deleted and
                                 ' this drawing routine attempts to access column due to
                                 ' horizontal scrollbar being moved too far right.
                                 if nIndex <= pListView->Columns.Count - 1 then
                                    select case pListView->Column(nIndex).TextAlign
                                       case TextAlignment.Left:   nAlign = DT_LEFT
                                       case TextAlignment.Right:  nAlign = DT_RIGHT
                                       case TextAlignment.Center: nAlign = DT_CENTER
                                    end select
                                 end if
                              end if
                              if instr(wszText, chr(13)) then
                                 nAlign = nAlign OR DT_WORDBREAK
                              else
                                 nAlign = nAlign OR DT_VCENTER or DT_SINGLELINE
                              end if
                              
                              ' Offset the text slightly if depressed...
                              IF (nState AND CDIS_SELECTED) THEN InflateRect @plvcd->nmcd.rc, -2, -2
                              
                              ' Draw multiline, using CRLF (i.e. wszText = "Customer" & $CRLF & "number")
                              DrawText plvcd->nmcd.hdc, wszText, LEN(wszText), @plvcd->nmcd.rc, nAlign

                              ' Cleanup
                              IF hBrush THEN DeleteObject hBrush

                              ' Tell Windows the item has already been drawn
                              FUNCTION = CDRF_SKIPDEFAULT
                              exit function
                                                           
                        End Select
                     end if
                  End if
            
            end select
         end if
#endif         
         
      
      Case WM_DESTROY
         ' Handle any final Destroy messages for the control and then return
         ' here to remove the subclassing.
         Application.HandleCommonMessages(hWin, uMsg, _wParam, _lParam) 
         ' REQUIRED: Remove control subclassing
         RemoveWindowSubclass( hWin, @wfxApplication.SubclassProc, uIdSubclass )
   End Select
    
   ' For messages that we don't deal with
   Function = DefSubclassProc(hWin, uMsg, _wParam, _lParam)

End Function

