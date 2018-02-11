# WinFormsX - TextBox

### Properties

| Name       | Description |
| ---------- | ----------- |
| Background | Gets or sets the background color of the control.|
| BorderStyle | Gets or sets the border type of the text box control. Refer to the TextBoxBorderStyle enum. |
| CtrlType      | Gets or sets the control type value. Always ControlType.TextBox and used when adding control to its form's controls collection. |
| Enabled       | Gets or sets a value (true/false) indicating whether the control can respond to user interaction. |
| Focused | Gets a value (true/false) indicating whether the control has input focus.|
| Foreground | Gets or sets the foreground color of the control.|
| Height        | Gets or sets the height of the control. |
| hWindow       | Gets the Windows handle (hwnd) of the control. |
| Left          | Gets or sets the distance, in pixels, between the left edge of the control and the left edge of its container's client area (normally the form). |
| Multiline | Gets or sets a value (true/false) indicating whether this is a multiline TextBox control|
| Name          | Gets or sets the name of the control. |
| Parent        | Gets or sets the parent container of the control. |
| Position      | Gets or sets the top and left position of the control relative to the form.<br />Get: returns wfxPoint object <br />Set: (left, top) |
| Size          | Gets or sets the size of the control.<br />Get: returns wfxSize object.<br />Set: (width, height) |
| TabStop | Gets or sets a value (true/false) indicating whether the user can give the focus to this control using the TAB key|
| Text          | Gets or sets the text (caption) associated with this control. |
| TextAlign | Gets or sets a value indicating the alignment of the text on a control. Refer to TextBoxAlignment enum. |
| Top           | Gets or sets the distance, in pixels, between the top edge of the control and the top edge of its container's client area (normally the form). |
| Visible       | Gets or sets a value (true/false) indicating whether the control is displayed. |
| Width         | Gets or sets the width of the control. |
| WordWrap | Indicates (true/false) whether a multiline text box control automatically wraps words to the beginning of the next line when necessary.|

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

### TextBox Alignment Enum
````
enum TextBoxAlignment
   Left   = ES_LEFT 
   Right  = ES_RIGHT
   Center = ES_CENTER
end enum
````
### TextBoxBorderStyle Enum
````
enum TextBoxBorderStyle
   None	= 0
   Fixed3D = WS_EX_CLIENTEDGE	
   FixedSingle	= WS_EX_WINDOWEDGE	
   FixedDialog	= WS_EX_DLGMODALFRAME
end enum
````