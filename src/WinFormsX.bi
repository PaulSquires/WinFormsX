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
''  WinFormsX.inc
''

#IfnDef UNICODE
   #Define UNICODE
#EndIf   
#IfnDef _WIN32_WINNT
   #Define _WIN32_WINNT &h0602  
#EndIf

#include once "windows.bi"
#include once "Afx\CWindow.inc"
#include once "Afx\AfxGdiPlus.inc"

#ifdef CODEGEN_BUTTON
#Include Once "Afx\CXpButton.inc"
#endif

#ifdef CODEGEN_MASKEDEDIT
#Include Once "Afx\CMaskedEdit.inc"
#endif

#ifdef CODEGEN_PICTUREBOX
#Include Once "Afx\CImageCtx.inc"
#endif

#ifdef CODEGEN_MAINMENU
#Include Once "Afx\AfxMenu.inc"
#endif

#ifdef CODEGEN_RICHEDIT
#Include Once "Afx\AfxRichEdit.inc"
#endif


using Afx

namespace WinFormsX

#Include Once "wfxColors.bi"
#Include Once "wfxDeclares.bi"
#Include Once "wfxFont.bi"
#Include Once "wfxSize.bi"
#Include Once "wfxPoint.bi"
#Include Once "wfxPopupMenu.bi"
#Include once "wfxLList.bi"
#include once "wfxControl.bi"


#ifdef CODEGEN_BUTTON
#include once "wfxButton.bi"
#endif

#ifdef CODEGEN_MAINMENU
#Include Once "wfxMainMenu.bi"
#endif

#ifdef CODEGEN_STATUSBAR
#Include Once "wfxStatusBar.bi"
#endif

#ifdef CODEGEN_TOOLBAR
#Include Once "wfxToolBar.bi"
#endif

#include once "wfxForm.bi"

#ifdef CODEGEN_LABEL
#include once "wfxLabel.bi"
#endif

#ifdef CODEGEN_FRAME
#Include Once "wfxFrame.bi"
#endif

#ifdef CODEGEN_PICTUREBOX
#Include Once "wfxPictureBox.bi"
#endif

#ifdef CODEGEN_TEXTBOX
#Include Once "wfxTextBox.bi"
#endif

#ifdef CODEGEN_RICHEDIT
#Include Once "wfxRichEdit.bi"
#endif

#ifdef CODEGEN_MASKEDEDIT
#Include Once "wfxMaskedEdit.bi"
#endif

#ifdef CODEGEN_CHECKBOX
#Include Once "wfxCheckBox.bi"
#endif

#ifdef CODEGEN_OPTIONBUTTON
#include once "wfxOptionButton.bi"
#endif

#ifdef CODEGEN_LISTBOX
#Include Once "wfxListbox.bi"
#endif

#ifdef CODEGEN_COMBOBOX
#Include Once "wfxComboBox.bi"
#endif

#ifdef CODEGEN_PROGRESSBAR
#Include Once "wfxProgressBar.bi"
#endif

#ifdef CODEGEN_LISTVIEW
#Include Once "wfxListView.bi"
#endif

#ifdef CODEGEN_MONTHCALENDAR
#Include Once "wfxMonthCalendar.bi"
#endif

#ifdef CODEGEN_DATETIMEPICKER
#Include Once "wfxDateTimePicker.bi"
#endif

#ifdef CODEGEN_TABCONTROL
#Include Once "wfxTabControl.bi"
#endif

#ifdef CODEGEN_UPDOWN
#Include Once "wfxUpDown.bi"
#endif

#ifdef CODEGEN_TIMER
#Include Once "wfxTimer.bi"
#endif

#ifdef CODEGEN_TREEVIEW
#Include Once "wfxTreeView.bi"
#endif

#Include Once "wfxApplication.bi"

#Include Once "wfxSize.inc"
#Include Once "wfxPoint.inc"
#Include Once "wfxPopupMenu.inc"
#include once "wfxLList.inc"
#Include Once "wfxApplication.inc"
#Include Once "wfxControl.inc"

#ifdef CODEGEN_BUTTON
#include once "wfxButton.inc"
#endif

#ifdef CODEGEN_LISTBOX
#include once "wfxListbox.inc"
#endif

#ifdef CODEGEN_COMBOBOX
#Include Once "wfxComboBox.inc"
#endif

#ifdef CODEGEN_CHECKBOX
#Include Once "wfxCheckBox.inc"
#endif

#ifdef CODEGEN_OPTIONBUTTON
#Include Once "wfxOptionButton.inc"
#endif

#ifdef CODEGEN_TEXTBOX
#include once "wfxTextBox.inc"
#endif

#ifdef CODEGEN_RICHEDIT
#include once "wfxRichEdit.inc"
#endif

#ifdef CODEGEN_MASKEDEDIT
#Include Once "wfxMaskedEdit.inc"
#endif

#ifdef CODEGEN_LABEL
#Include Once "wfxLabel.inc"
#endif

#ifdef CODEGEN_FRAME
#include once "wfxFrame.inc"
#endif

#ifdef CODEGEN_PICTUREBOX
#include once "wfxPictureBox.inc"
#endif

#ifdef CODEGEN_PROGRESSBAR
#Include Once "wfxProgressBar.inc"
#endif

#ifdef CODEGEN_LISTVIEW
#Include Once "wfxListView.inc"
#endif

#ifdef CODEGEN_TREEVIEW
#Include Once "wfxTreeView.inc"
#endif

#ifdef CODEGEN_MONTHCALENDAR
#Include Once "wfxMonthCalendar.inc"
#endif

#ifdef CODEGEN_DATETIMEPICKER
#Include Once "wfxDateTimePicker.inc"
#endif

#ifdef CODEGEN_TABCONTROL
#Include Once "wfxTabControl.inc"
#endif

#ifdef CODEGEN_UPDOWN
#Include Once "wfxUpDown.inc"
#endif

#ifdef CODEGEN_TIMER
#Include Once "wfxTimer.inc"
#endif

#ifdef CODEGEN_MAINMENU
#Include Once "wfxMainMenu.inc"
#endif

#ifdef CODEGEN_STATUSBAR
#Include Once "wfxStatusBar.inc"
#endif

#ifdef CODEGEN_TOOLBAR
#Include Once "wfxToolBar.inc"
#endif

#include once "wfxForm.inc"


end namespace

Using Afx, WinFormsX  



