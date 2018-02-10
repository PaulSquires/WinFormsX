
#include once "frmMain.bi"


function frmMain_Load( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   function = 0
end function

function frmMain_FormClosing( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   function = 0
end function

function frmMain_FormClosed( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   function = 0
end function

function frmMain_Resize( byref sender as wfxForm, byref e as EventArgs ) as LRESULT
   function = 0
end function

function frmMain_StatusBar_Click( byref sender as wfxStatusBar, byref e as EventArgs ) as LRESULT
   '? "Statusbar Panel: " & e.PanelClickIndex & " Clicked"
   function = 0
end function


