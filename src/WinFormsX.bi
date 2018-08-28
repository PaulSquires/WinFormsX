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
#Include Once "Afx\CXpButton.inc"

using Afx

namespace WinFormsX

#Include Once "wfxColors.bi"
#Include Once "wfxDeclares.bi"
#Include Once "wfxFont.bi"
#Include Once "wfxSize.bi"
#Include Once "wfxPoint.bi"
#Include once "wfxLList.bi"
#include once "wfxControl.bi"
#include once "wfxButton.bi"
#include once "wfxForm.bi"
#include once "wfxLabel.bi"
#Include Once "wfxFrame.bi"
#Include Once "wfxTextBox.bi"
#include once "wfxCheckBox.bi"
#include once "wfxOptionButton.bi"
#Include Once "wfxListbox.bi"
#include once "wfxStatusBar.bi"
#Include Once "wfxApplication.bi"

#Include Once "wfxSize.inc"
#Include Once "wfxPoint.inc"
#include once "wfxLList.inc"
#Include Once "wfxApplication.inc"
#Include Once "wfxControl.inc"
#include once "wfxButton.inc"
#include once "wfxListbox.inc"
#include once "wfxCheckBox.inc"
#Include Once "wfxOptionButton.inc"
#include once "wfxTextBox.inc"
#include once "wfxLabel.inc"
#include once "wfxFrame.inc"
#Include Once "wfxStatusBar.inc"
#include once "wfxForm.inc"


end namespace

Using Afx, WinFormsX  



