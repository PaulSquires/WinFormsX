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
''  CLASS LIST (ARRAY BASED)
''

#include once "wfxLList.bi"

''
''
constructor wfxLList
   '? "constructor"
end constructor

''
''
destructor wfxLList
   '? "destructor"
   ' It is the caller's responsibility to destroy the class. The class
   ' itself can not delete the allocated nodes because the pData member
   ' also needs to be deleted. However, pData is defined as ANY PTR and
   ' the delete command will fail as being an undefined action. The calling
   ' program must iterate the list, cast and delete the pData, and finally
   ' remove the node.
end destructor

''
''
function wfxLList.size() as Long
   function = ubound(this._ListArray) - lbound(this._ListArray) + 1
END function

''
''
function wfxLList.get_first() as wfxLListNode ptr
   ' Return pointer to the first node in the list
   if this.size <= 0 then return 0
   if lbound(this._ListArray) >= 0 then
      function = _ListArray(0)
   end if
end function

''
''
function wfxLList.get_next( byval idx as long ) as wfxLListNode ptr
   if this.size <= 0 then return 0
   ' Return pointer to the next node in the list
   if (idx < lbound(this._ListArray)) or (idx > ubound(this._ListArray)) then return 0
   function = this._ListArray(idx)
end function

''
''
function wfxLList.get_index( byval idx as long ) as wfxLListNode ptr
   if this.size <= 0 then return 0
   ' Return pointer to the specific node in the list
   if (idx < lbound(this._ListArray)) or (idx > ubound(this._ListArray)) then return 0
   function = this._ListArray(idx)
end function

''
''
function wfxLList.search_data( byval pData as any ptr ) as wfxLListNode ptr
   if this.size <= 0 then return 0
   ' Search the pData element for a match on incoming pData and return the node.
   for i as long = lbound(this._ListArray) to ubound(this._ListArray)
      if this._ListArray(i)->pData = pData then return this._ListArray(i)
   next
   function = 0
end function

''
''
function wfxLList.search_handle( byval hWindow as hwnd) as wfxLListNode ptr
   if this.size <= 0 then return 0
   ' Search the hWindow element for a match on incoming handle and return the node.
   for i as long = lbound(this._ListArray) to ubound(this._ListArray)
      if this._ListArray(i)->hWindow = hWindow then return this._ListArray(i)
   next
   function = 0
end function

''
''
function wfxLList.search_controlID( byval nCtrlID as long ) as wfxLListNode ptr
   if this.size <= 0 then return 0
   ' Search the hWindow element for a match on incoming ControlID and
   ' return the linked list list node.
   for i as long = lbound(this._ListArray) to ubound(this._ListArray)
      if GetDlgCtrlID(this._ListArray(i)->hWindow) = nCtrlID then return this._ListArray(i)
   next
   function = 0
end function

''
''
function wfxLList.search_controltype( byval nCtrlType as ControlType) as wfxLListNode ptr
   if this.size <= 0 then return 0
   ' Search the ControlType element for a match on incoming nCtrlType and return the node.
   for i as long = lbound(this._ListArray) to ubound(this._ListArray)
      if this._ListArray(i)->CtrlType = nCtrlType then return this._ListArray(i)
   next
   function = 0
end function

''
''
function wfxLList.remove( byval pNodeDelete as wfxLListNode ptr ) as wfxLListNode ptr
   if this.size <= 0 then return 0
   ' Remove the specified node and return the node that preceeds this node.
   if pNodeDelete = 0 then exit function
    
   ' Find the node position in the array.
   dim as long iPos = -1 
   for i as long = lbound(this._ListArray) to ubound(this._ListArray)
      if this._ListArray(i) = pNodeDelete then
         iPos = i: exit for
      end if
   next
   if iPos = -1 then return 0


   ' Remove the item from the list
   if this.size = 1 then
      erase this._ListArray
      function = 0
   else   

      for ii as long = iPos to ubound(this._ListArray) - 1 
         this._ListArray(ii) = this._ListArray(ii + 1) 
      next

      redim preserve this._ListArray(ubound(this._ListArray) - 1)
      
      function = iif( iPos <= ubound(this._ListArray), this._ListArray(iPos), 0 )

   end if

   ' Ensure that the list node memory is released
   delete pNodeDelete

end function

''
''
function wfxLList.remove_bydata( byval pData as any ptr ) as wfxLListNode ptr
   if this.size <= 0 then return 0
   ' Search the pData element for a match on incoming pData and
   ' then remove the node.
   dim pNode as wfxLListNode ptr = this.search_data(pData)
   return this.remove(pNode)
end function

''
''
function wfxLList.add( byval CtrlType as long, _
                       byval pData as any ptr _
                       ) as wfxLListNode ptr
   ' Create a new node and add it to the end of the list
   dim pNode as wfxLListNode ptr = new wfxLListNode
   ' Assign the node data
   pNode->CtrlType = CtrlType
   pNode->pData = pData

   dim as long ub = ubound(this._ListArray) + 1
   redim preserve this._ListArray(ub)
   this._ListArray(ub) = pNode
   
   function = pNode
end function

''
''
function wfxLList.insert( byval nIndex as long, _
                          byval CtrlType as long, _
                          byval pData as any ptr _
                          ) as wfxLListNode ptr
   ' Create a new node and insert it into the list
   dim pNode as wfxLListNode ptr = new wfxLListNode
   ' Assign the node data
   pNode->CtrlType = CtrlType
   pNode->pData = pData

   dim as long ub = ubound(this._ListArray) + 1
   redim preserve this._ListArray(ub)
   
   for i as long = ub to nIndex + 1 step -1
      this._ListArray(i) = this._ListArray(i-1)
   next
   this._ListArray(nIndex) = pNode
   
   function = pNode
end function


''
''
function wfxLList.clear() as long
   ' Deallocate all of the LListNodes and erase the array
   dim pNode as wfxLListNode ptr 
   for i as long = lbound(this._ListArray) to ubound(this._ListArray)
      pNode = cast( wfxLListNode ptr, this._ListArray(i) )
      delete pNode 
   next
   erase this._ListArray
   function = 0
end function
