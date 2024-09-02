# Microsoft Developer Studio Project File - Name="demotractor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=demotractor - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "demotractor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "demotractor.mak" CFG="demotractor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "demotractor - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "demotractor - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "demotractor - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DEMOTRACTOR_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DEMOTRACTOR_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40b /d "NDEBUG"
# ADD RSC /l 0x40b /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib winmm.lib /nologo /dll /machine:I386 /nodefaultlib:"LIBC" /out:"../Release/demotractor.dll"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "demotractor - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DEMOTRACTOR_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DEMOTRACTOR_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40b /d "_DEBUG"
# ADD RSC /l 0x40b /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib winmm.lib /nologo /dll /debug /machine:I386 /nodefaultlib:"LIBC" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "demotractor - Win32 Release"
# Name "demotractor - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\base.cpp
# End Source File
# Begin Source File

SOURCE=.\beziercurve.cpp
# End Source File
# Begin Source File

SOURCE=.\face.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\font.hpp
# End Source File
# Begin Source File

SOURCE=.\globals.cpp
# End Source File
# Begin Source File

SOURCE=.\hermitecurve.cpp
# End Source File
# Begin Source File

SOURCE=.\image.cpp
# End Source File
# Begin Source File

SOURCE=.\log.cpp
# End Source File
# Begin Source File

SOURCE=.\matrix.cpp
# End Source File
# Begin Source File

SOURCE=.\matrix4.cpp
# End Source File
# Begin Source File

SOURCE=.\mmgr.cpp
# End Source File
# Begin Source File

SOURCE=.\object.cpp
# End Source File
# Begin Source File

SOURCE=.\opengl.cpp
# End Source File
# Begin Source File

SOURCE=.\PAKfile.cpp
# End Source File
# Begin Source File

SOURCE=.\parser.cpp
# End Source File
# Begin Source File

SOURCE=.\spline.cpp
# End Source File
# Begin Source File

SOURCE=.\t3d.cpp
# End Source File
# Begin Source File

SOURCE=.\texture.cpp
# End Source File
# Begin Source File

SOURCE=.\timer.cpp
# End Source File
# Begin Source File

SOURCE=.\vector.cpp
# End Source File
# Begin Source File

SOURCE=.\vertex.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\base.hpp
# End Source File
# Begin Source File

SOURCE=.\beziercurve.hpp
# End Source File
# Begin Source File

SOURCE=.\enums.hpp
# End Source File
# Begin Source File

SOURCE=.\face.hpp
# End Source File
# Begin Source File

SOURCE=.\Glext.h
# End Source File
# Begin Source File

SOURCE=.\globals.hpp
# End Source File
# Begin Source File

SOURCE=.\hermitecurve.hpp
# End Source File
# Begin Source File

SOURCE=.\image.hpp
# End Source File
# Begin Source File

SOURCE=.\log.hpp
# End Source File
# Begin Source File

SOURCE=.\matrix.hpp
# End Source File
# Begin Source File

SOURCE=.\matrix4.hpp
# End Source File
# Begin Source File

SOURCE=.\mmgr.h
# End Source File
# Begin Source File

SOURCE=.\nommgr.h
# End Source File
# Begin Source File

SOURCE=.\object.hpp
# End Source File
# Begin Source File

SOURCE=.\opengl.hpp
# End Source File
# Begin Source File

SOURCE=.\PAKfile.hpp
# End Source File
# Begin Source File

SOURCE=.\parser.hpp
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\spline.hpp
# End Source File
# Begin Source File

SOURCE=.\t3d.hpp
# End Source File
# Begin Source File

SOURCE=.\texture.hpp
# End Source File
# Begin Source File

SOURCE=.\timer.hpp
# End Source File
# Begin Source File

SOURCE=.\vector.hpp
# End Source File
# Begin Source File

SOURCE=.\vertex.hpp
# End Source File
# Begin Source File

SOURCE=.\wglext.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\resource.rc
# End Source File
# End Group
# Begin Group "Logs"

# PROP Default_Filter "log;txt;"
# Begin Source File

SOURCE=.\Manual.txt
# End Source File
# Begin Source File

SOURCE=.\worklog.txt
# End Source File
# End Group
# Begin Group "Engine sources"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\effectmanager.cpp
# End Source File
# Begin Source File

SOURCE=.\fontmanager.cpp
# End Source File
# Begin Source File

SOURCE=.\objectmanager.cpp
# End Source File
# Begin Source File

SOURCE=.\sound.cpp
# End Source File
# Begin Source File

SOURCE=.\texturemanager.cpp
# End Source File
# End Group
# Begin Group "Engine headers"

# PROP Default_Filter "hpp"
# Begin Source File

SOURCE=.\effectmanager.hpp
# End Source File
# Begin Source File

SOURCE=.\fontmanager.hpp
# End Source File
# Begin Source File

SOURCE=.\objectmanager.hpp
# End Source File
# Begin Source File

SOURCE=.\sound.hpp
# End Source File
# Begin Source File

SOURCE=.\texturemanager.hpp
# End Source File
# End Group
# Begin Group "Library files"

# PROP Default_Filter "lib"
# Begin Source File

SOURCE=.\OPENGL32.LIB
# End Source File
# Begin Source File

SOURCE=.\GLU32.LIB
# End Source File
# Begin Source File

SOURCE=.\ILUT.lib
# End Source File
# Begin Source File

SOURCE=.\DevIL.lib
# End Source File
# Begin Source File

SOURCE=.\ILU.lib
# End Source File
# Begin Source File

SOURCE=.\fmodex_vc.lib
# End Source File
# Begin Source File

SOURCE=.\ds.lib
# End Source File
# End Group
# End Target
# End Project
