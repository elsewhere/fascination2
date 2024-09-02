# Microsoft Developer Studio Project File - Name="efushow" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=efushow - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "efushow.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "efushow.mak" CFG="efushow - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "efushow - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "efushow - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "efushow - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "$(CG_INC_PATH)" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40b /d "NDEBUG"
# ADD RSC /l 0x40b /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 cg.lib cgGL.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /machine:I386 /libpath:"$(CG_LIB_PATH)"

!ELSEIF  "$(CFG)" == "efushow - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40b /d "_DEBUG"
# ADD RSC /l 0x40b /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "efushow - Win32 Release"
# Name "efushow - Win32 Debug"
# Begin Group "Effects"

# PROP Default_Filter "c;cpp;h;hpp"
# Begin Source File

SOURCE=.\effects\alku.cpp
# End Source File
# Begin Source File

SOURCE=.\effects\alku.hpp
# End Source File
# Begin Source File

SOURCE=.\effects\frustumtesti.cpp
# End Source File
# Begin Source File

SOURCE=.\effects\frustumtesti.hpp
# End Source File
# Begin Source File

SOURCE=.\effects\kareet.cpp
# End Source File
# Begin Source File

SOURCE=.\effects\kareet.hpp
# End Source File
# Begin Source File

SOURCE=.\effects\kierre.cpp
# End Source File
# Begin Source File

SOURCE=.\effects\kierre.hpp
# End Source File
# Begin Source File

SOURCE=.\effects\kuutio.cpp
# End Source File
# Begin Source File

SOURCE=.\effects\kuutio.hpp
# End Source File
# Begin Source File

SOURCE=.\effects\laser.cpp
# End Source File
# Begin Source File

SOURCE=.\effects\laser.hpp
# End Source File
# Begin Source File

SOURCE=.\effects\loppu.cpp
# End Source File
# Begin Source File

SOURCE=.\effects\loppu.hpp
# End Source File
# Begin Source File

SOURCE=.\effects\miami.cpp
# End Source File
# Begin Source File

SOURCE=.\effects\miami.hpp
# End Source File
# Begin Source File

SOURCE=.\effects\nauhat.cpp
# End Source File
# Begin Source File

SOURCE=.\effects\nauhat.hpp
# End Source File
# Begin Source File

SOURCE=.\effects\neonsade.cpp
# End Source File
# Begin Source File

SOURCE=.\effects\neonsade.hpp
# End Source File
# Begin Source File

SOURCE=.\effects\noise1.cpp
# End Source File
# Begin Source File

SOURCE=.\effects\noise1.hpp
# End Source File
# Begin Source File

SOURCE=.\effects\pikkuspiraalit.cpp
# End Source File
# Begin Source File

SOURCE=.\effects\pikkuspiraalit.hpp
# End Source File
# Begin Source File

SOURCE=.\effects\psyko.cpp
# End Source File
# Begin Source File

SOURCE=.\effects\psyko.hpp
# End Source File
# Begin Source File

SOURCE=.\effects\rekursio.cpp
# End Source File
# Begin Source File

SOURCE=.\effects\rekursio.hpp
# End Source File
# Begin Source File

SOURCE=.\effects\sade.cpp
# End Source File
# Begin Source File

SOURCE=.\effects\sade.hpp
# End Source File
# Begin Source File

SOURCE=.\effects\sauhu.cpp
# End Source File
# Begin Source File

SOURCE=.\effects\sauhu.hpp
# End Source File
# Begin Source File

SOURCE=.\effects\siluetti.cpp
# End Source File
# Begin Source File

SOURCE=.\effects\siluetti.hpp
# End Source File
# Begin Source File

SOURCE=.\effects\starfield.cpp
# End Source File
# Begin Source File

SOURCE=.\effects\starfield.hpp
# End Source File
# Begin Source File

SOURCE=.\effects\tanssilattia.cpp
# End Source File
# Begin Source File

SOURCE=.\effects\tanssilattia.hpp
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\analyzer.cpp
# End Source File
# Begin Source File

SOURCE=.\bezier.cpp
# End Source File
# Begin Source File

SOURCE=.\bpm.cpp
# End Source File
# Begin Source File

SOURCE=.\camera.cpp
# End Source File
# Begin Source File

SOURCE=.\catmullrom.cpp
# End Source File
# Begin Source File

SOURCE=.\config.cpp
# End Source File
# Begin Source File

SOURCE=.\cubemap.cpp
# End Source File
# Begin Source File

SOURCE=.\ext.cpp
# End Source File
# Begin Source File

SOURCE=.\frametimer.cpp
# End Source File
# Begin Source File

SOURCE=.\frustumculler.cpp
# End Source File
# Begin Source File

SOURCE=.\lista2.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\mathematics.cpp
# End Source File
# Begin Source File

SOURCE=.\matrix4.cpp
# End Source File
# Begin Source File

SOURCE=.\mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\meshfactory.cpp
# End Source File
# Begin Source File

SOURCE=.\mmgr.cpp
# End Source File
# Begin Source File

SOURCE=.\postproc.cpp
# End Source File
# Begin Source File

SOURCE=.\primitives.cpp
# End Source File
# Begin Source File

SOURCE=.\shader.cpp
# End Source File
# Begin Source File

SOURCE=.\trigger.cpp
# End Source File
# Begin Source File

SOURCE=.\writer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\analyzer.hpp
# End Source File
# Begin Source File

SOURCE=.\bezier.hpp
# End Source File
# Begin Source File

SOURCE=.\bpm.hpp
# End Source File
# Begin Source File

SOURCE=.\camera.hpp
# End Source File
# Begin Source File

SOURCE=.\catmullrom.hpp
# End Source File
# Begin Source File

SOURCE=.\config.hpp
# End Source File
# Begin Source File

SOURCE=.\cubemap.hpp
# End Source File
# Begin Source File

SOURCE=.\enums.hpp
# End Source File
# Begin Source File

SOURCE=.\ext.hpp
# End Source File
# Begin Source File

SOURCE=.\extension_functions.hpp
# End Source File
# Begin Source File

SOURCE=.\externs.hpp
# End Source File
# Begin Source File

SOURCE=.\frametimer.hpp
# End Source File
# Begin Source File

SOURCE=.\frustumculler.hpp
# End Source File
# Begin Source File

SOURCE=.\lista2.hpp
# End Source File
# Begin Source File

SOURCE=.\mathematics.hpp
# End Source File
# Begin Source File

SOURCE=.\matrix4.hpp
# End Source File
# Begin Source File

SOURCE=.\mesh.hpp
# End Source File
# Begin Source File

SOURCE=.\meshfactory.hpp
# End Source File
# Begin Source File

SOURCE=.\mmgr.h
# End Source File
# Begin Source File

SOURCE=.\nommgr.h
# End Source File
# Begin Source File

SOURCE=.\postproc.hpp
# End Source File
# Begin Source File

SOURCE=.\primitives.hpp
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\shader.hpp
# End Source File
# Begin Source File

SOURCE=.\trigger.hpp
# End Source File
# Begin Source File

SOURCE=.\writer.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\logo.bmp
# End Source File
# Begin Source File

SOURCE=.\resource.rc
# End Source File
# End Group
# Begin Group "doc"

# PROP Default_Filter ".txt"
# Begin Source File

SOURCE=.\shadowmapping.txt
# End Source File
# End Group
# Begin Source File

SOURCE=.\DemoTractor\objectmanager.hpp
# End Source File
# End Target
# End Project
