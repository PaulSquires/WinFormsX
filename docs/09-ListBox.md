# WinFormsX - ListBox

### Properties

| Name       | Description |
| ---------- | ----------- |
| AllowSelection | Gets a value (true/false) indicating whether the ListBox currently enables selection of list items. |
| BackColor | Gets or sets the background color of the control.|
| BorderStyle | Gets or sets the type of border that is drawn around the ListBox. Refer to FormBorderStyle enum.|
| ColumnWidth | Gets or sets the width of columns in a multicolumn ListBox.|
| CtrlType      | Gets or sets the control type value. Always ControlType.ListBox and used when adding control to its form's controls collection. |
| Enabled       | Gets or sets a value (true/false) indicating whether the control can respond to user interaction. |
| Focused | Gets a value (true/false) indicating whether the control has input focus.|
| ForeColor | Gets or sets the foreground color of the control.|
| Height        | Gets or sets the height of the control. |
| hWindow       | Gets the Windows handle (hwnd) of the control. |
| IntegralHeight | Gets or sets a value (true/false) indicating whether the control should resize to avoid showing partial items.|
| Item ()| Gets a ListBox item (wfxListBoxItem). |
| Items | Gets a reference to collection of ListBox items (wfxListBoxItemsCollection). |
| Left  | Gets or sets the distance, in pixels, between the left edge of the control and the left edge of its container's client area (normally the form). |
| Location | Gets or sets the top and left position of the control relative to the form.<br />Get: returns wfxPoint object <br />Set: (left, top) |
| MultiColumn | Gets or sets a value indicating whether the ListBox supports multiple columns.|
| Name | Gets or sets the name of the control. |
| Parent  | Gets or sets the parent container of the control. |
| ScrollAlwaysVisible | Gets or sets a value (true/false) indicating whether the vertical scroll bar is shown at all times.|
| SelectedIndex | Gets or sets the zero-based index of the currently selected item in a ListBox.|
| SelectedItem | Gets the ListBox Item (wfxListBoxItem) based on the currently selected item in a ListBox.|
| SelectionMode | Gets or sets the method in which items are selected in the ListBox. Refer to ListBoxSelectionMode enum.|
| Size | Gets or sets the size of the control.<br />Get: returns wfxSize object.<br />Set: (width, height) |
| Sorted | Gets or sets a value (true/false) indicating whether the items in the ListBox are sorted alphabetically.|
| TabStop | Gets or sets a value (true/false) indicating whether the user can give the focus to this control using the TAB key|
| Top | Gets or sets the distance, in pixels, between the top edge of the control and the top edge of its container's client area (normally the form). |
| TopIndex | Gets or sets the index of the first visible item in the ListBox.|
| Visible | Gets or sets a value (true/false) indicating whether the control is displayed. |
| Width | Gets or sets the width of the control. |

### Methods

| Name       | Description                                                  |
| ---------- | ------------------------------------------------------------ |
| Hide       | Conceals the control from the user. |
| Refresh    | Forces the control to invalidate its client area and immediately redraw itself |
| SetBounds  | Sets the bounds of the control to the specified location and size. (left, top, width, height) |
| Show | Makes the control visible to the user (and creates the control should it not already exist)|

### Events

| Name | Description |
| ---- | ----------- |
| OnAllEvents     | Special handler where **all** events are routed through. Use this handler if you prefer to use the Win32 api style messages and wParam and lParam parameters. Set the *Handled* element of *EventArgs* to **true** if you handle a message and do not want Windows to perform any further processing on the message. |
| OnClick     | Occurs when the client area of the control is clicked. |
| OnDestroy | Occurs immediately before the control is about to be destroyed and all resources associated with it released. |
| OnGotFocus     | Occurs when the control gains input focus. |
| OnLostFocus    | Occurs when the control loses input focus. |
| OnKeyDown | Occurs when a key is pressed while the control has focus. |
| OnKeyPress | Occurs when a character, space or backspace key is pressed while the control has focus. |
| OnKeyUp | Occurs when a key is released while the control has focus. |
| OnMouseDoubleClick     | Occurs when the control is double clicked by the mouse. |
| OnMouseDown     | Occurs when the mouse pointer is over the control and a mouse button is pressed. |
| OnMouseEnter   | Occurs when the mouse pointer enters the control. |
| OnMouseHover  | Occurs when the mouse pointer rests on the control. |
| OnMouseLeave  | Occurs when the mouse pointer leaves the control. |
| OnMouseMove     | Occurs when the mouse pointer is moved over the control. |
| OnMouseUp     | Occurs when the mouse pointer is over the control and a mouse button is released. |

<<<<<<< HEAD
### wfxListBoxItem

| Name       | Description |
| ---------- | ----------- |
| Text | Gets or sets the text associated with this ListBox item.|
| Data32 | Gets or sets a 32-bit user defined value for the ListBox item.|
| Selected | Gets or set a value (true/false) indicating whether the ListBox item is selected.|

### wfxListBoxItemsCollection

| Name       | Description |
| ---------- | ----------- |
| Add | Appends a new ListBox item to the ListBox. Returns index of new item. |
| ByIndex | Returns a wfxListBoxItem based on the specified row index. |
| Clear | Deletes all items in the ListBox.|
| Count | Gets the number of items in the ListBox.|
| Remove | Deletes the spcified ListboxItem index from the ListBox.|

### ListBoxSelectionMode

````
Enum ListBoxSelectionMode
=======
### ListBoxSelectionMode

​````Enum ListBoxSelectionMode
>>>>>>> 7bfa41f408ea3bbe9bd0815fd7c1e6137d3479c4
   None = 0
   One
   MultiSimple
   MultiExtended
End Enum
````
<<<<<<< HEAD

### Adding ListBox Items
````
   ' Add 10 lines to the Listbox
   Dim as Long idx
   for i as long = 0 to 9
     idx = Form1.List1.Items.Add
     Form1.List1.Item(idx).Text = "Add Listbox line:" & idx
     Form1.List1.Item(idx).Data32 = idx
   next
   ? "List1 count: "; Form1.List1.Items.Count
````

### Deleting ListBox Items
````
    ' Delete the currently selected item
    Form1.List1.Items.Remove( Form1.List1.SelectedIndex )
    ? "List1 count: "; Form1.List1.Items.Count
````

### Multiple Selection ListBoxes
Create ListBox using SelectionMode equal to either MultiSimple or MultiExtended.
````
   if Form1.List1.SelectionMode = ListBoxSelectionMode.One then
      dim byref ListItem as wfxListBoxItem = Form1.List1.SelectedItem
      ? ListItem.Text, ListItem.Data32
   else
      ' If this ListBox allows multiple items to be selected then loop through and display.
      for i as long = 0 to Form1.List1.Items.Count - 1
         if Form1.List1.Item(i).Selected then
            ? "ListBox Item index: "; i; " is selected."
         end if
      next
   end if
````

=======
### Multiple Selection ListBoxes
>>>>>>> 7bfa41f408ea3bbe9bd0815fd7c1e6137d3479c4
