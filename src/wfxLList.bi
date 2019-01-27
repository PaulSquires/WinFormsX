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

type wfxLListNode
   pNodePrev as wfxLListNode ptr
   pNodeNext as wfxLListNode ptr
   CtrlType  as long      ' identifies the type of data pointed to in pData
   hWindow   as HWND      ' hwnd of form/control. Allows fast search/retrieval of data
   pData     as any ptr
end type   

type wfxLList
   private:
      nodeCount   as Long
      pNodeFirst  as wfxLListNode ptr    ' anchor to first node in list
      pNodeLast   as wfxLListNode ptr    ' anchor to last node in list
      
   public:
      declare constructor
      declare destructor
      declare function size() as Long
      declare function add( byval CtrlType as long, byval pData as any ptr) as wfxLListNode ptr
      declare function remove( byval pNodeDelete as wfxLListNode ptr ) as wfxLListNode ptr
      declare function get_first() as wfxLListNode ptr
      declare function get_next( byval pNode as wfxLListNode ptr ) as wfxLListNode ptr
      declare function search_data( byval pData as any ptr ) as wfxLListNode ptr
      declare function search_handle( byval hWindow as hwnd) as wfxLListNode ptr
      declare function search_controltype( byval nCtrlType as ControlType) as wfxLListNode ptr
      declare function search_controlID( byval nCtrlID as long ) as wfxLListNode ptr
      declare function remove_bydata( byval pData as any ptr ) as wfxLListNode ptr
END TYPE


