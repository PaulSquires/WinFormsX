# WinFormsX - Form

### Properties

| Name       | Description |
| ---------- | ----------- |
| Background    | Gets or sets the background color of the form. Refer to the Colors object. |
| BorderStyle   | Gets or sets the border style of the form. Refer to the FormBorderStyle enum. |
| CtrlType      | Gets or sets the control type value. Always ControlType.Form and used when adding form to the Application form collection. |
| ClientSize    | Gets or sets the client area of the form.  The client area of the form is the size of the form excluding the borders and the title bar.<br />Get: returns wfxSize object.<br />Set: (width, height) |
| ControlBox    | Gets or sets value (true/false) indicating whether a control box is displayed in the caption bar of the form. |
| Enabled       | Gets or sets a value (true/false) indicating whether the form can respond to user interaction. |
| Height        | Gets or sets the height of the form. |
| hWindow       | Gets the Windows handle (hwnd) of the form. |
| IsMainForm    | Gets or sets a value (true/false) indicating the form is main and will display when application starts. When the form is closed the application also ends. |
| IsModal       | Gets a value (true/false) indicating whether the form is displayed modally. |
| Left          | Gets or sets the distance, in pixels, between the left edge of the form and the left edge of its container's client area (normally the screen). |
| Location      | Gets or sets the top and left position of the form.<br />Get: returns wfxPoint object <br />Set: (left, top) |
| MaximizeBox   | Gets or sets a value (true/false) indicating whether the maximize button is displayed in the caption bar of the form. |
| MinimizeBox   | Gets or sets a value (true/false) indicating whether the minimize button is displayed in the caption bar of the form. |
| Name          | Gets or sets the name of the form. |
| Parent        | Gets or sets the parent container of the form. |
| Size          | Gets or sets the size of the form.<br />Get: returns wfxSize object.<br />Set: (width, height) |
| StartPosition | Gets or sets the starting position of the form at run time. Refer to FormStartPosition enum. |
| Text          | Gets or sets the text (caption) associated with this form. |
| Top           | Gets or sets the distance, in pixels, between the top edge of the form and the top edge of its container's client area (normally the screen). |
| Visible       | Gets or sets a value (true/false) indicating whether the form is displayed. |
| WindowState   | Gets or sets a value that indicates whether form is minimized, maximized, or normal. Refer to the FormWindowState enum. |
| Width         | Gets or sets the width of the form. |

### Methods

| Name       | Description                                                  |
| ---------- | ------------------------------------------------------------ |
| Close      | Closes the form.                                             |
| Hide       | Conceals the form from the user.                             |
| Refresh    | Forces the form to invalidate its client area and immediately redraw itself and any child controls |
| SetBounds  | Sets the bounds of the form to the specified location and size. (left, top, width, height) |
| Show       | Displays the form to the user.                               |
| ShowDialog | Shows the form as a modal dialog box.                        |

### Events

| Name | Description |
| ---- | ----------- |
| OnActivated     | Occurs when the form is activated in code or by the user. |
| OnAllEvents     | Special handler where **all** events are routed through. Use this handler if you prefer to use the Win32 api style messages and wParam and lParam parameters. Set the *Handled* element of *EventArgs* to **true** if you handle a message and do not want Windows to perform any further processing on the message. |
| OnClick     | Occurs when the client area of the form is clicked. |
| OnDeactivate     | Occurs when the form loses focus and is no longer the active form. |
| OnFormClosed     | Occurs after the form is closed. |
| OnFormClosing     | Occurs before the form is closed. |
| OnKeyDown | Occurs when a key is pressed while the form has focus. |
| OnKeyPress | Occurs when a character, space or backspace key is pressed while the form has focus. |
| OnKeyUp | Occurs when a key is released while the form has focus. |
| OnLoad     | Occurs before a form is displayed for the first time. |
| OnMouseDoubleClick     | Occurs when the form is double clicked by the mouse. |
| OnMouseDown     | Occurs when the mouse pointer is over the form and a mouse button is pressed. |
| OnMouseEnter   | Occurs when the mouse pointer enters the form. |
| OnMouseHover  | Occurs when the mouse pointer rests on the form. |
| OnMouseLeave  | Occurs when the mouse pointer leaves the form. |
| OnMouseMove     | Occurs when the mouse pointer is moved over the form. |
| OnMouseUp     | Occurs when the mouse pointer is over the form and a mouse button is released. |
| OnMove     | Occurs when the form is moved. |
| OnResize     | Occurs when the form is resized. |
| OnShown     | Occurs whenever the form is first displayed. |

### Form State and Style Enums
````
enum FormWindowState
   Maximized = 1
   Minimized
   Normal
end enum

enum FormStartPosition
   CenterParent = 1
   CenterScreen
   Manual
   WindowsDefaultLocation
end enum

enum FormBorderStyle
   None	= 0
   Sizable = WS_THICKFRAME	
   Fixed3D = WS_EX_CLIENTEDGE	
   FixedSingle	= WS_EX_WINDOWEDGE	
   FixedDialog	= WS_EX_DLGMODALFRAME
   FixedToolWindow = 1
   SizableToolWindow = 2
end enum


````
### Order of Events in Forms
WinFormsX fires form events in a specific order every time a form is created and shown. 

During form creation:
- OnFormLoad: The form handle and all child controls exist however the form and controls are not yet visible. Respond to this event to reposition controls or to add data to controls. For example, add rows to a Listbox or Combobox. 
- OnFormActivated: The form has gained input focus (similar to the OnGotFocus event of a control).
- OnShown: This event is only raised the first time a form is displayed; subsequently minimizing, maximizing, restoring, hiding, showing, or invalidating and repainting will not raise this event. 

During form destruction:
- OnFormClosing: Event occurs as the form is closing. If you cancel this event, then the form remains open. To cancel, simply set the *Cancel* element of the *EventArgs* structure to **True**.
- OnDeactivate: Occurs when the form loses focus and is no longer the active form (similar to the OnLostFocus event of a control).
- OnFormClosed: Occurs after the form has closed (similar to the OnDestroy event of a control).

