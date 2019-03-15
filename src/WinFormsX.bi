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
#Include Once "Afx\CMaskedEdit.inc"
#Include Once "Afx\CImageCtx.inc"
#Include Once "Afx\AfxMenu.inc"

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
#Include Once "wfxMainMenu.bi"
#include once "wfxForm.bi"
#include once "wfxLabel.bi"
#Include Once "wfxFrame.bi"
#Include Once "wfxPictureBox.bi"
#Include Once "wfxTextBox.bi"
#Include Once "wfxRichEdit.bi"
#Include Once "wfxMaskedEdit.bi"
#Include Once "wfxCheckBox.bi"
#include once "wfxOptionButton.bi"
#Include Once "wfxListbox.bi"
#Include Once "wfxComboBox.bi"
#Include Once "wfxStatusBar.bi"
#Include Once "wfxApplication.bi"

#Include Once "wfxSize.inc"
#Include Once "wfxPoint.inc"
#include once "wfxLList.inc"
#Include Once "wfxApplication.inc"
#Include Once "wfxControl.inc"
#include once "wfxButton.inc"
#include once "wfxListbox.inc"
#Include Once "wfxComboBox.inc"
#Include Once "wfxCheckBox.inc"
#Include Once "wfxOptionButton.inc"
#include once "wfxTextBox.inc"
#include once "wfxRichEdit.inc"
#Include Once "wfxMaskedEdit.inc"
#Include Once "wfxLabel.inc"
#include once "wfxFrame.inc"
#include once "wfxPictureBox.inc"
#Include Once "wfxStatusBar.inc"
#Include Once "wfxMainMenu.inc"
#include once "wfxForm.inc"


end namespace

Using Afx, WinFormsX  



