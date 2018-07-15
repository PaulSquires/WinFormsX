''
''  Control Collection
''

constructor wfxCollection
   '_arrControls
end constructor

destructor wfxCollection
   '_arrControls
end destructor

property wfxCollection.Count() as long
   return ubound(_arrControls) - lbound(_arrControls) + 1
end property

property wfxCollection.ItemFirst() as long
   return lbound(_arrControls)
end property

property wfxCollection.ItemLast() as long
   return Ubound(_arrControls)
end property

function wfxCollection.ItemAt( byval nIndex as long ) as wfxControl ptr
   return _arrControls(nIndex)
end function

function wfxCollection.ItemByName( byref wszName as wstring ) as wfxControl ptr
   for i as long = lbound(_arrControls) to ubound(_arrControls)
       if ucase(_arrControls(i)->Name) = ucase(wszName) THEN
         return _arrControls(i) 
       END IF
   next
   function = 0   ' null pointer not found
end function

function wfxCollection.Add( byval pCtrl as wfxControl ptr ) as long
   dim as long ub = ubound(_arrControls) + 1
   redim preserve _arrControls(ub) as wfxControl ptr
   _arrControls(ub) = pCtrl
   pCtrl->Parent = this.pFormParent
   ' If this is not a Form then render the control now. If the parent form
   ' has not yet been rendered then control creation will be delayed until
   ' the form gets created.
   If pCtrl->CtrlType <> ControlType.Form Then 
      If this.pFormParent->hWindow Then pCtrl->Show
   End If   
   function = ub
end function

function wfxCollection.Add( byref pCtrl as wfxControl ) as long
   function = this.Add(@pCtrl)
end function

function wfxCollection.Remove( byval pCtrl as wfxControl ptr ) as long
   dim as long idx = -1
   for i as long = lbound(_arrControls) to ubound(_arrControls)
      if _arrControls(i) = pCtrl THEN
         idx = i: exit for
      END IF
   NEXT
   if idx = -1 THEN exit function
      
   for i as long = idx to ubound(_arrControls) - 1
      _arrControls(i) = _arrControls(i+1)
   next
   
   if ubound(_arrControls)-1 THEN
      erase _arrControls
   else
      redim preserve _arrControls(ubound(_arrControls)-1) as wfxControl ptr
   END IF
   
   function = idx
end function


