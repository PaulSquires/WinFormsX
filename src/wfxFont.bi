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

Type wfxFont
   Private:
      _hFont       As HFONT
      _wszFontName As CWSTR
      _PointSize   As Single
      _FontStyles  As Long
      _CharSet     As Byte
      
   Public:
      Declare Constructor()
      Declare Constructor( ByRef wszFontName As WString, _
                           ByVal nPointSize As Single, _
                           ByVal nFontStyles As Long = FontStyles.Normal, _
                           ByVal nCharSet As FontCharset = FontCharset.Default )
      Declare Destructor
      Declare Function FontHandle() As HFONT
      Declare Function FontName() As CWSTR
      Declare Function PointSize() As Single
      Declare Function FontStyle() As Long
      Declare Function IsBold() As boolean
      Declare Function IsItalic() As boolean
      Declare Function IsUnderline() As boolean
      Declare Function IsStrikeout() As boolean
      Declare Function CharSet() As FontCharset
End Type

Constructor wfxFont()
End Constructor

Constructor wfxFont( ByRef wszFontName As WString, _
                     ByVal nPointSize  As Single, _
                     ByVal nFontStyles As Long = FontStyles.Normal, _
                     ByVal nCharSet    As FontCharset = FontCharset.Default )

   _wszFontName = wszFontName
   _PointSize   = nPointSize
   _FontStyles  = nFontStyles
   _CharSet     = nCharSet

   ' Create a font for the class and store it in _hFont
   Dim tlfw As LOGFONT
   Dim hDC As HDC = GetDC(HWND_DESKTOP)

   tlfw.lfHeight         = -MulDiv(nPointSize, GetDeviceCaps(hDC, LOGPIXELSY), 72)  ' logical font height
   tlfw.lfWidth          =  0                                                        ' average character width
   tlfw.lfEscapement     =  0                                                        ' escapement
   tlfw.lfOrientation    =  0                                                        ' orientation angles
   tlfw.lfWeight         =  Iif(this.IsBold, 700, 400)                               ' font weight
   tlfw.lfItalic         =  this.IsItalic                                            ' italic(CTRUE/FALSE)
   tlfw.lfUnderline      =  this.IsUnderline                                         ' underline(CTRUE/FALSE)
   tlfw.lfStrikeOut      =  this.IsStrikeOut                                         ' strikeout(CTRUE/FALSE)
   tlfw.lfCharSet        =  _CharSet                                                 ' character set
   tlfw.lfOutPrecision   =  OUT_TT_PRECIS                                            ' output precision
   tlfw.lfClipPrecision  =  CLIP_DEFAULT_PRECIS                                      ' clipping precision
   tlfw.lfQuality        =  DEFAULT_QUALITY                                          ' output quality
   tlfw.lfPitchAndFamily =  FF_DONTCARE                                              ' pitch and family
   tlfw.lfFaceName       =  _wszFontName                                             ' typeface name
   ReleaseDC HWND_DESKTOP, hDC

   _hFont = CreateFontIndirect(@tlfw)
End Constructor

Destructor wfxFont()
   If _hFont Then DeleteObject(_hFont)
End Destructor

Function wfxFont.FontHandle() As HFONT
   Function = _hFont
End Function                     

Function wfxFont.FontName() As CWSTR
   Function = _wszFontName
End Function

Function wfxFont.PointSize() As Single
   Function = _PointSize
End Function

Function wfxFont.FontStyle() As Long
   Function = _FontStyles
End Function

Function wfxFont.IsBold() As boolean
   Function = (_FontStyles And FontStyles.Bold)
End Function

Function wfxFont.IsItalic() As boolean
   Function = (_FontStyles And FontStyles.Italic)
End Function

Function wfxFont.IsUnderline() As boolean
   Function = (_FontStyles And FontStyles.Underline)
End Function

Function wfxFont.IsStrikeout() As boolean
   Function = (_FontStyles And FontStyles.Strikeout)
End Function

Function wfxFont.CharSet() As FontCharset
   Function = _CharSet
End Function

