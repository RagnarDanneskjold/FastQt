; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "fastqt"
#define MyAppVersion "0.2-rc"
#define MyAppPublisher "labsquare"
#define MyAppURL "http://www.labsquare.org"
#define MyAppExeName "fastqt.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{2E6BDE27-73F1-46FD-A12A-274E254CC13B}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\labsquare\{#MyAppName}
DisableProgramGroupPage=yes
OutputBaseFilename=fastqt-0.2-rc
Compression=lzma
SolidCompression=yes


[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "release\fastqt.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\D3Dcompiler_47.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\fastqt.exe"; DestDir: "{app}"; Flags: ignoreversion
;Source: "release\libbz2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\libEGL.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\libGLESV2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\libKF5Archive.dll"; DestDir: "{app}"; Flags: ignoreversion
;Source: "release\liblzma-5.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\opengl32sw.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\Qt5Charts.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\Qt5Svg.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\zlib1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "release\iconengines\*"; DestDir: "{app}\iconengines"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "release\imageformats\*"; DestDir: "{app}\imageformats"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "release\platforms\*"; DestDir: "{app}\platforms"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "release\translations\*"; DestDir: "{app}\translations"; Flags: ignoreversion recursesubdirs createallsubdirs



; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{commonprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

