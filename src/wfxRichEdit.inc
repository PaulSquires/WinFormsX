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
''  RichEdit Class
''
''

#include once "wfxRichEdit.bi"


constructor wfxRichEdit( byref wszName as wstring = "" )
   this.CtrlType       = ControlType.RichEdit
   this.Name           = wszName
   this.BackColor      = Colors.SystemWindow
   this.ForeColor      = Colors.SystemWindowText
   this.Multiline      = true
   this.WordWrap       = true
   this.AcceptsReturn  = true
   this.MaxLength      = 64000
end constructor




