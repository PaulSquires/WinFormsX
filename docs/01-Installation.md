# WinFormsX

## Windows Form library for FreeBASIC



#### Introduction

WinFormsX is a forms building library for the FreeBASIC programming language. It is designed specifically for the Windows operating system. The goal of WinFormsX is to hide the complexity of the Win32 API that powers Windows application development. This is done through easy to use classes and syntax that is similar in nature to that of higher level programming languages like vb.net and C#.

#### Installation

Before you can use WinFormsX, there are a few tools and libraries that you should have installed on your system. 

- FreeBASIC Compiler. Version 1.05 is the latest version (as of February 2018) and can be found at [https://sourceforge.net/projects/fbc/files/](https://sourceforge.net/projects/fbc/files/). It is recommended to download and install both the 32-bit and 64-bit versions of the compiler. If you wish, you can also install the very latest builds for the yet unreleased version 1.06 from this link [http://users.freebasic-portal.de/stw/builds/](http://users.freebasic-portal.de/stw/builds/) .

- WinFBE Editor. Full featured, open source, Windows based, code editor. This editor integrates perfectly with the FreeBASIC compiler that you would have installed in the previous step. Download from [https://github.com/PaulSquires/WinFBE/releases](https://github.com/PaulSquires/WinFBE/releases). There is no formal installation program required. Simply unzip the downloaded file to any folder on your computer and then run either the WinFBE32.exe or WinFBE64.exe program depending on your version of Windows.

- WinFBX Library created by José Roca. Every FreeBASIC programmer should have this library. It is a comprehensive library containing hundreds of functions and classes that make programming so much easier. WinFormsX relies on this library and will not work without it. Download the library [https://github.com/JoseRoca/WinFBX](https://github.com/JoseRoca/WinFBX). Unzip the downloaded file to your computer and then copy the *Afx* folder to your *\inc* folder for your FreeBASIC installation.
  For example, if you installed the FreeBASIC compiler to a folder called *C:\FB\FreeBASIC-1.05.0-win32* then you should copy the *Afx* folder to this location: *C:\FB\FreeBASIC-1.05.0-win32\inc.* Do the same for the location where you installed the 64 bit version of the compiler (eg. *X:\FB\FreeBASIC-1.05.0-win64\inc*).



- The WinFormsX Library itself needs to be copied to the *WinFormsX* folder in your *\inc* folder for your FreeBASIC installation.
  For example, if you installed the FreeBASIC compiler to a folder called *C:\FB\FreeBASIC-1.05.0-win32* then you should create a folder called *C:\FB\FreeBASIC-1.05.0-win32\inc\WinFormsX* and copy the contents of the *\src* folder to this location:  Do the same for the location where you installed the 64 bit version of the compiler (eg. *C:\FB\FreeBASIC-1.05.0-win64\inc*).

  ​

#### Using WinFormsX

Once you have setup and installed the necessary supporting tools, the next step is to run a simple test source code file to ensure that everything works correctly. In the *examples* folder, open the file named *FormTest.bas* into your source code editor (eg. in the WinFBE Editor). Compile and execute that program and if there are no errors then you should see a simple form display on the screen. This will indicate that your system is setup and configured correctly.

Looking at the code you will see the following line:

```
#include once "WinFormsX\WinFormsX.bi"
```

That is the only reference to the WinFormsX library that you need. That include file is located in the *\inc* folder that you specified in the previous section when you installed the library (eg. C:\FB\FreeBASIC-1.05.0-win32\inc\WinFormsX). If you open that file you will see that there are many other #include files listed. Each of those other include files represent the core of the WinFormsX library and are required in order to make the library work correctly. Do not edit or remove anything from that file. The *WinFormsX.bi* file is simply a wrapper file that makes including all of the additional WinFormsX files easier (you only need to include the *WinFormsX.bi* in your programs).

> If you encountered errors when compiling and executing the *FormTest.bas* file then you have not correctly configured your system. Ensure that all steps in the *Installation* section have been completed correctly and that your code editor has been setup to point to the FreeBASIC compiler that you have installed. 





