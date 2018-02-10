# WinFormsX - EventArgs

The *EventArgs* structure is common to every Event Handler. It contains various information related to the message being handled. 

````Function Form1_Button1_Click( byref sender as wfxButton, byref e as EventArgs ) ````

````
Type EventArgs as wfxEventArgs   
Type wfxEventArgs Extends Object
   private:
   public:
      Message         As UINT        ' Windows value of message being sent (WM_COMMAND, WM_NOTIFY, etc)
      wParam          as WPARAM      ' the wParam of the raw message
      lParam          as LPARAM      ' the lParam of the raw message
      Handled         as Boolean     ' indicates whether the event is handled by the user
      Cancel          as boolean     ' set to True to cancel closing of Form
      Ctrl            as Boolean     ' the CTRL key is pressed
      Alt             as Boolean     ' the Alt key is pressed
      Shift           as Boolean     ' the SHIFT key is pressed
      KeyChar         as long        ' stores the character of the key pressed (WM_CHAR)
      KeyCode         as long        ' stores the keyboard code for the event (WM_KEYDOWN, WM_KEYUP)
      LButton         as boolean     ' the left mouse button pressed
      MButton         as boolean     ' the middle mouse button pressed
      RButton         as boolean     ' the right mouse button pressed
      x               as long        ' the x-coordinate of the mouse click
      y               as long        ' the y-coordinate of the mouse click
      PanelClickIndex as long        ' the zero-based index of clicked statusbar panel 
end type 
````
