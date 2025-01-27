; Script for create installer
[Setup]

; App name
#define   Name       "Process Dependency Monitor"
; App short name
#define   NameShort  "ProcDepMonitor"
; App version
#define   Version    "1.0.1"
; Author        
#define   Publisher  "3dproger"
; Author URL
#define   URL        "https://github.com/3dproger"
; Exe name
#define   ExeName    "ProcDepMonitor.exe"

; Generated from Tools -> Generate GUID
AppId={{69CE5F3C-A869-4FA6-967A-C18E0A01578F}

; Uncomment if need x64 only
; ArchitecturesInstallIn64BitMode=x64

; Compression parameters
Compression=lzma2
SolidCompression=yes

WizardStyle=modern

; Disable or not the page for selecting the folder where to install. [auto, yes, on]
; auto - do not show if already installed
; no - always show
; yes - never show
DisableDirPage=auto

DisableProgramGroupPage=no

AppName={#Name}
AppVersion={#Version}
AppPublisher={#Publisher}
AppPublisherURL={#URL}
AppSupportURL={#URL}
AppUpdatesURL={#URL}

DefaultGroupName={#Name}
DefaultDirName={pf}\{#Name}
UninstallDisplayIcon={app}\{#ExeName}

WizardImageFile="big_image.bmp"
WizardSmallImageFile="small_image.bmp"
SetupIconFile="main_icon.ico"
DisableWelcomePage=false

; Output filename
OutputBaseFileName={#NameShort}-{#Version}-win32
                                                
[Languages]
Name: en; MessagesFile: "compiler:Default.isl"; LicenseFile: "../../../LICENSE" 
Name: am; MessagesFile: "compiler:Languages\Armenian.isl"; LicenseFile: "../../../LICENSE" 
Name: br; MessagesFile: "compiler:Languages\BrazilianPortuguese.isl"; LicenseFile: "../../../LICENSE" 
Name: ad; MessagesFile: "compiler:Languages\Catalan.isl"; LicenseFile: "../../../LICENSE"
Name: cz; MessagesFile: "compiler:Languages\Czech.isl"; LicenseFile: "../../../LICENSE"
Name: dk; MessagesFile: "compiler:Languages\Danish.isl"; LicenseFile: "../../../LICENSE"
Name: nl; MessagesFile: "compiler:Languages\Dutch.isl"; LicenseFile: "../../../LICENSE"
Name: fi; MessagesFile: "compiler:Languages\Finnish.isl"; LicenseFile: "../../../LICENSE"
Name: fr; MessagesFile: "compiler:Languages\French.isl"; LicenseFile: "../../../LICENSE" 
Name: de; MessagesFile: "compiler:Languages\German.isl"; LicenseFile: "../../../LICENSE" 
Name: il; MessagesFile: "compiler:Languages\Hebrew.isl"; LicenseFile: "../../../LICENSE"
Name: is; MessagesFile: "compiler:Languages\Icelandic.isl"; LicenseFile: "../../../LICENSE"
Name: it; MessagesFile: "compiler:Languages\Italian.isl"; LicenseFile: "../../../LICENSE"
Name: jp; MessagesFile: "compiler:Languages\Japanese.isl"; LicenseFile: "../../../LICENSE"  
Name: no; MessagesFile: "compiler:Languages\Norwegian.isl"; LicenseFile: "../../../LICENSE" 
Name: pl; MessagesFile: "compiler:Languages\Polish.isl"; LicenseFile: "../../../LICENSE"
Name: pt; MessagesFile: "compiler:Languages\Portuguese.isl"; LicenseFile: "../../../LICENSE"
Name: ru; MessagesFile: "compiler:Languages\Russian.isl"; LicenseFile: "../../../LICENSE" 
Name: si; MessagesFile: "compiler:Languages\Slovenian.isl"; LicenseFile: "../../../LICENSE" 
Name: es; MessagesFile: "compiler:Languages\Spanish.isl"; LicenseFile: "../../../LICENSE"
Name: tr; MessagesFile: "compiler:Languages\Turkish.isl"; LicenseFile: "../../../LICENSE"
Name: ua; MessagesFile: "compiler:Languages\Ukrainian.isl"; LicenseFile: "../../../LICENSE"

; what is this for?
;[Messages]
;ru.BeveledLabel=Russian
;en.BeveledLabel=English

[Icons]
Name: "{group}\{#Name}"; Filename: "{app}\{#ExeName}"
Name: "{group}\{cm:UninstallProgram,{#Name}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#Name}"; Filename: "{app}\{#ExeName}"; Tasks: desktopicon

[Tasks]
; Icon at desktop
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";

[Files]
;Input files
Source: "..\i386\appdir\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

