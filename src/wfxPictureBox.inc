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
''  PictureBox Class
''
''

#Include Once "wfxPictureBox.bi"

constructor wfxPictureBox( byref wszName as wstring = "" )
   this.CtrlType     = ControlType.PictureBox
   this.Name         = wszName
   this.BackColor    = Colors.SystemWindow
   this.BackColorHot = Colors.SystemWindow
End Constructor

property wfxPictureBox.Image() as CWSTR
   property = _Image
end property

Destructor wfxPictureBox()
   if _ImageCtxPtr then Delete _ImageCtxPtr
   _ImageCtxPtr = 0
End Destructor

property wfxPictureBox.Image( byref cwzValue as wstring )
   If _ImageCtxPtr Then 
      If len(cwzValue) Then
         if this.Parent->pWindow then
            ' Attempt to load the image directly from the resource file. If that
            ' fails then try to extract the image to a temporary disk file and
            ' load it from there.
            if _ImageCtxPtr->LoadImageFromResource( this.Parent->pWindow->InstanceHandle, cwzValue ) = 0 then
         
               dim wszTempPath as wstring * MAX_PATH
               GetTempPath( MAX_PATH, @wszTempPath )
               dim wszTempFilename as wstring * MAX_PATH
               GetTempFileName( @wszTempPath, "TMP", 0, @wszTempFilename )
               
               ' Attempt to extract the image resource. 
               ' Returns FALSE on failure
               if AfxExtractResourceToFile( this.Parent->pWindow->InstanceHandle, _
                                         cwzValue, wszTempFilename, RT_RCDATA ) = false then
               end if
               
               _ImageCtxPtr->LoadImageFromFile( wszTempFilename )
               AfxDeleteFile( wszTempFilename )
            end if
         end if
      else
         ' Clear any existing image
         _ImageCtxPtr->Clear      
         _Image = ""
      End If    
   End If
   _Image = cwzValue
end property

property wfxPictureBox.ImageFromFile( byref wszValue as wstring )
   If _ImageCtxPtr Then 
      If AfxFileExists(wszValue) Then
         if this.Parent->pWindow then
            _ImageCtxPtr->LoadImageFromFile( wszValue ) 
         end if
      else
         ' clear any existing image
         _ImageCtxPtr->Clear      
      end if
   end if      
   _Image = wszValue
end property

property wfxPictureBox.ImageWidth( byval nValue as Long )
   ' Only invoke size change if value is not zero
   if nValue = 0 then exit property
   If _ImageCtxPtr Then 
      _ImageCtxPtr->SetImageWidth( nValue )
   End If
   _ImageWidth = nValue
end property

property wfxPictureBox.ImageWidth() as Long
   If _ImageCtxPtr Then 
      _ImageWidth = _ImageCtxPtr->GetImageWidth()
   End If
   property = _ImageWidth
end property

property wfxPictureBox.ImageHeight( byval nValue as Long )
   ' Only invoke size change if value is not zero
   if nValue = 0 then exit property
   If _ImageCtxPtr Then 
      _ImageCtxPtr->SetImageHeight( nValue )
   End If
   _ImageHeight = nValue
end property

property wfxPictureBox.ImageHeight() as Long
   If _ImageCtxPtr Then 
      _ImageHeight = _ImageCtxPtr->GetImageHeight()
   End If
   property = _ImageHeight
end property

property wfxPictureBox.ImageScaling( byval nValue as ImageScale )
   If _ImageCtxPtr Then 
      select case nValue
         case ImageScale.None
            _ImageCtxPtr->SetImageAdjustment( GDIP_IMAGECTX_ACTUALSIZE )
         case ImageScale.AutoSize
            _ImageCtxPtr->SetImageAdjustment( GDIP_IMAGECTX_AUTOSIZE )
         case ImageScale.FitWidth   
            _ImageCtxPtr->SetImageAdjustment( GDIP_IMAGECTX_FITTOWIDTH )
         case ImageScale.FitHeight
            _ImageCtxPtr->SetImageAdjustment( GDIP_IMAGECTX_FITTOHEIGHT )
         case ImageScale.Stretch
            _ImageCtxPtr->SetImageAdjustment( GDIP_IMAGECTX_STRETCH )
      end select
   End If
   _ImageScaling = nValue
end property

property wfxPictureBox.ImageScaling() as ImageScale
   If _ImageCtxPtr Then 
      dim nValue as long = _ImageCtxPtr->GetImageAdjustment()
      select case nValue
         case GDIP_IMAGECTX_ACTUALSIZE
            _ImageScaling = ImageScale.None
         case GDIP_IMAGECTX_AUTOSIZE
            _ImageScaling = ImageScale.AutoSize
         case GDIP_IMAGECTX_FITTOWIDTH
            _ImageScaling = ImageScale.FitWidth   
         case GDIP_IMAGECTX_FITTOHEIGHT
            _ImageScaling = ImageScale.FitHeight
         case GDIP_IMAGECTX_STRETCH
            _ImageScaling = ImageScale.Stretch
      end select
   End If
   property = _ImageScaling
end property

Property wfxPictureBox.BackColor( ByVal nValue As COLORREF )
   If _ImageCtxPtr Then 
      _ImageCtxPtr->SetBkColor(nValue, True)
   End If
   _BackColor = nValue
End Property

Property wfxPictureBox.BackColor() As COLORREF 
   If _ImageCtxPtr Then 
      _BackColor = _ImageCtxPtr->GetBkColor
   End If
   Property = _BackColor 
End Property

Property wfxPictureBox.BackColorHot( ByVal nValue As COLORREF )
   If _ImageCtxPtr Then 
      _ImageCtxPtr->SetBkColorHot(nValue, True)
   End If
   _BackColorHot = nValue
End Property

Property wfxPictureBox.BackColorHot() As COLORREF 
   If _ImageCtxPtr Then 
      _BackColorHot = _ImageCtxPtr->GetBkColorHot
   End If
   Property = _BackColorHot 
End Property


Function wfxPictureBox.Show(ByVal hWndParent As HWnd = 0) As Long

   ' If the control is created but simply hidden, then show it.
   if this.hWindow THEN
      ShowWindow(this.hWindow, SW_SHOW)
      exit function
   END IF

   ' If the parent form has not been created yet then simply exit. We will
   ' create this control when the form is created.
   if hWndParent = 0 THEN exit function
      
   Dim pWindow As CWindow Ptr = AfxCWindowPtr(hWndParent)

   ' Use the custom control CXpButton instead of the standard Windows button control.
   _CtrlID = this.Parent->GetNextCtrlID()
   _ImageCtxPtr = New CImageCtx(pWindow, _CtrlID, "", this.Left, this.top, this.Width, this.height )
   this.hWindow = _ImageCtxPtr->hWindow
   SetWindowSubclass(this.hWindow, Cast(SUBCLASSPROC, @wfxApplication.SubclassProc), _CtrlID, Cast(DWORD_PTR, 0))

   ' Should we enable drag and drop files
   If this.AllowDrop Then DragAcceptFiles(this.hWindow, CTRUE)

   ' Store the hWindow in the form's linked list in order to allow
   ' for fast lookups via GetControlByHandle.
   dim pNode as wfxLListNode ptr = this.Parent->Controls.search_data(@this)
   if pNode then pNode->hWindow = this.hWindow
      
   this.Image        = _Image
   this.ImageWidth   = _ImageWidth
   this.ImageHeight  = _ImageHeight
   this.ImageScaling = _ImageScaling
   this.BackColor    = _BackColor
   this.BackColorHot = _BackColorHot
   this.Enabled      = _Enabled
   this.ToolTip      = _ToolTip

   function = 0
END FUNCTION




