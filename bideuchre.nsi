;-------------------------------------------------------------------------------
; bideuchre.nsi
; NSIS Installer Script for Bid Euchre
;
; $Id: bideuchre.nsi,v 1.2 2005/08/06 11:03:53 technoplaza Exp $
;-------------------------------------------------------------------------------

!include "MUI.nsh"

Name "Bid Euchre"
OutFile "bideuchre-0.71.exe"
InstallDir "$PROGRAMFILES\Bid Euchre"

!define MUI_ABORTWARNING

;-------------------------------------------------------------------------------

Var SM_FOLDER

!insertmacro MUI_PAGE_LICENSE "docs\license.txt"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_STARTMENU Application $SM_FOLDER
!insertmacro MUI_PAGE_INSTFILES

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

;-------------------------------------------------------------------------------

Section "Bid Euchre"
    SetOutPath $INSTDIR
    File source\bideuchre.exe
    
    SetOutPath "$INSTDIR\images"
    File source\images\*.bmp
    
    SetOutPath "$INSTDIR\docs"
    File docs\*.html
    File docs\*.txt
    
    !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    CreateDirectory "$SMPROGRAMS\$SM_FOLDER"
    CreateShortCut "$SMPROGRAMS\$SM_FOLDER\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
    
    SetOutPath $INSTDIR
    CreateShortCut "$SMPROGRAMS\$SM_FOLDER\Bid Euchre.lnk" "$INSTDIR\bideuchre.exe" "" "$INSTDIR\bideuchre.exe" 0
    !insertmacro MUI_STARTMENU_WRITE_END
    
    WriteUninstaller "uninstall.exe"
SectionEnd

Section "Uninstall"
    !insertmacro MUI_STARTMENU_GETFOLDER Application $SM_FOLDER

    RMDir /r "$SMPROGRAMS\$SM_FOLDER"
    RMDir /r $INSTDIR
SectionEnd

