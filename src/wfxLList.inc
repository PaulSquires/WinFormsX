'    WinFormsX - Windows GUI Framework for the FreeBASIC Compiler
'    Copyright (C) 2018 Paul Squires, PlanetSquires Software
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
''  CLASS LINKED LIST
''  This is a doubly linked list based loosely on the C++ STL Container List syntax
''

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
   function = this.nodeCount
END function

''
''
function wfxLList.get_first() as wfxLListNode ptr
   ' Return pointer to the first node in the list
   function = this.pNodeFirst
end function

''
''
function wfxLList.get_next( byval pNode as wfxLListNode ptr ) as wfxLListNode ptr
   ' Return pointer to the next node in the list
   if pNode = 0 then exit function
   function = pNode->pNodeNext
end function

''
''
function wfxLList.search_data( byval pData as any ptr ) as wfxLListNode ptr
   ' Search the pData element for a match on incoming pData and
   ' return the linked list list node.
   dim pNode as wfxLListNode ptr = this.pNodeFirst
   do until pNode = 0
      if pNode->pData = pData then return pNode
      pNode = pNode->pNodeNext
   LOOP
   function = 0
end function

''
''
function wfxLList.search_handle( byval hWindow as hwnd) as wfxLListNode ptr
   ' Search the hWindow element for a match on incoming handle and
   ' return the linked list list node.
   dim pNode as wfxLListNode ptr = this.pNodeFirst
   do until pNode = 0
      if pNode->hWindow = hWindow then return pNode
      pNode = pNode->pNodeNext
   LOOP
   function = 0
end function

''
''
function wfxLList.search_controlID( byval nCtrlID as long ) as wfxLListNode ptr
   ' Search the hWindow element for a match on incoming ControlID and
   ' return the linked list list node.
   dim pNode as wfxLListNode ptr = this.pNodeFirst
   do until pNode = 0
      if GetDlgCtrlID( pNode->hWindow ) = nCtrlID then return pNode
      pNode = pNode->pNodeNext
   LOOP
   function = 0
end function

''
''
function wfxLList.search_controltype( byval nCtrlType as ControlType) as wfxLListNode ptr
   ' Search the ControlType element for a match on incoming nCtrlType and
   ' return the linked list list node.
   dim pNode as wfxLListNode ptr = this.pNodeFirst
   do until pNode = 0
      if pNode->CtrlType = nCtrlType then return pNode
      pNode = pNode->pNodeNext
   LOOP
   function = 0
end function

''
''
function wfxLList.remove( byval pNodeDelete as wfxLListNode ptr ) as wfxLListNode ptr
   ' Remove the specified node and return the node that follows this node.
   if pNodeDelete = 0 then exit function
    
   ' If pNodeLast points to the node being deleted then
   ' we need to adjust it to point to the previous node.
   If this.pNodeLast = pNodeDelete Then
      this.pNodeLast = pNodeDelete->pNodePrev
   End If   

   function = pNodeDelete->pNodeNext

   ' Remove the item from the list
   If pNodeDelete->pNodePrev = 0 Then
      this.pNodeFirst = pNodeDelete->pNodeNext
      If pNodeDelete->pNodeNext Then
         pNodeDelete->pNodeNext->pNodePrev = 0
      End If   
   Else
      pNodeDelete->pNodePrev->pNodeNext = pNodeDelete->pNodeNext
      If pNodeDelete->pNodeNext Then
         If pNodeDelete->pNodeNext Then
            pNodeDelete->pNodeNext->pNodePrev = pNodeDelete->pNodePrev->pNodePrev
         End If   
      End If   
   End If
   ' Ensure that the previously NEW node is unallocated
   delete pNodeDelete
   this.nodeCount = this.nodeCount - 1
end function

''
''
function wfxLList.remove_bydata( byval pData as any ptr ) as wfxLListNode ptr
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
   ' Add the node to the list
   pNode->pNodeNext = 0
   ' Link the new node to the current last node
   pNode->pNodePrev = this.pNodeLast
   ' Link the current last node (if exists) to the newly created node
   if this.pNodeLast then this.pNodeLast->pNodeNext = pNode
   ' Save our reference as the new last node
   this.pNodeLast = pNode
   if this.pNodeFirst = 0 then this.pNodeFirst = pNode
   ' Update our node count 
   this.nodeCount = this.nodeCount + 1
   function = pNode
end function


