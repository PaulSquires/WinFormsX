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

' ComboBox Class
' https://docs.microsoft.com/en-ca/dotnet/api/system.windows.forms.combobox


type wfxComboBoxItem
   private:
      _hWindow     as hwnd
      _Index       as Long
      _Text        as CWSTR
      _Data32      as Long 
      _Selected    as boolean
     
   public:
      Declare Property hWindow() As hwnd
      Declare Property hWindow( ByVal nValue As hwnd)
      Declare Property Index() As long
      Declare Property Index( ByVal nValue As long)
      Declare Property Selected() As boolean
      Declare Property Selected( ByVal nValue As boolean)
      declare property Text() as CWSTR
      declare property Text( byref wszValue as wstring )
      Declare Property Data32() As long
      Declare Property Data32( ByVal nValue As long)
END TYPE

type wfxComboBoxItemsCollection
   private:
      _hWindow     as hwnd
      _Collection As wfxLList
      
   public:
      Declare Property hWindow() As hwnd
      Declare Property hWindow( ByVal nValue As hwnd)
      Declare function Clear() as long 
      Declare function Count() as long 
      Declare Function Remove( ByVal nIndex As Long ) As Long 
      Declare Function Add( ByRef wszValue As WString = "", ByVal nValue As Long = 0) As Long
      declare function ByIndex( byval nIndex as long ) byref as wfxComboBoxItem
      Declare Constructor
      declare destructor 
END TYPE

Type wfxComboBox Extends wfxControl
   private:
      _TempItem As wfxComboBoxItem
      _DropDownStyle As ComboBoxStyle = ComboBoxStyle.DropDownList
      _BorderStyle As ControlBorderStyle = ControlBorderStyle.Fixed3D
      _IntegralHeight As boolean = False
      _SelectedItem as wfxComboBoxItem
      _SelectedIndex as Long = -1
      _Sorted As boolean = False
      _ItemsCollection as wfxComboBoxItemsCollection
      _IsLoading as Boolean = true   ' internal
      
   Public:
      Declare Function Item( ByVal nIndex As Long) ByRef As wfxComboBoxItem
      declare function Items byref As wfxComboBoxItemsCollection
      Declare Property BorderStyle() As ControlBorderStyle
      Declare Property BorderStyle( ByVal nValue As ControlBorderStyle )
      Declare Property DropDownStyle() As ComboBoxStyle
      Declare Property DropDownStyle( ByVal nValue As ComboBoxStyle )
      Declare Property IntegralHeight() As boolean
      Declare Property IntegralHeight( ByVal nValue As boolean)
      Declare Property SelectedItem(byref as wfxComboBoxItem) 
      Declare Property SelectedItem() byref as wfxComboBoxItem
      Declare Property SelectedIndex() As long
      Declare Property SelectedIndex( ByVal nValue As long)
      Declare Property Sorted() As boolean
      Declare Property Sorted( ByVal nValue As boolean)
      
      Declare Constructor( byref wszName as wstring = "" )
      declare function Show(byval hWndParent as hwnd = 0) as long override

      OnAllEvents        as function( byref sender as wfxComboBox, byref e as EventArgs ) as LRESULT
      OnDestroy          as function( byref sender as wfxComboBox, byref e as EventArgs ) as LRESULT
      OnClick            as function( byref sender as wfxComboBox, byref e as EventArgs ) as LRESULT
      OnMouseMove        as function( byref sender as wfxComboBox, byref e as EventArgs ) as LRESULT
      OnMouseDown        as function( byref sender as wfxComboBox, byref e as EventArgs ) as LRESULT
      OnMouseUp          as function( byref sender as wfxComboBox, byref e as EventArgs ) as LRESULT
      OnMouseDoubleClick as function( byref sender as wfxComboBox, byref e as EventArgs ) as LRESULT
      OnMouseEnter       as function( byref sender as wfxComboBox, byref e as EventArgs ) as LRESULT
      OnMouseHover       as function( byref sender as wfxComboBox, byref e as EventArgs ) as LRESULT
      OnMouseLeave       as function( byref sender as wfxComboBox, byref e as EventArgs ) as LRESULT
      OnGotFocus         as function( byref sender as wfxComboBox, byref e as EventArgs ) as LRESULT
      OnLostFocus        as function( byref sender as wfxComboBox, byref e as EventArgs ) as LRESULT
      OnKeyDown          as function( byref sender as wfxComboBox, byref e as EventArgs ) as LRESULT
      OnKeyUp            as function( byref sender as wfxComboBox, byref e as EventArgs ) as LRESULT
      OnKeyPress         as function( byref sender as wfxComboBox, byref e as EventArgs ) as LRESULT
      OnDropFiles        As Function( ByRef sender As wfxComboBox, ByRef e As EventArgs ) As LRESULT
      OnDropDown         As Function( ByRef sender As wfxComboBox, ByRef e As EventArgs ) As LRESULT
      OnDropDownClosed   As Function( ByRef sender As wfxComboBox, ByRef e As EventArgs ) As LRESULT
      OnTextChanged      As Function( ByRef sender As wfxComboBox, ByRef e As EventArgs ) As LRESULT
End Type

