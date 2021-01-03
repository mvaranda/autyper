@echo on
rem called from "root"
set ROOTDIR_3=%CD%

set MINGW_MAKE=D:\Qt\Tools\mingw810_64\bin\mingw32-make.exe
set QT_BIN_DIR=D:\Qt\5.15.2\mingw81_64\bin

IF %COMPUTERNAME% == MV-WIN10 (
  echo //////// Using Marcelo machine settings \\\\\\
	set MINGW_MAKE=D:\Qt\Tools\mingw810_64\bin\mingw32-make.exe
	set QT_BIN_DIR=D:\Qt\5.15.2\mingw81_64\bin
) ELSE IF "%COMPUTERNAME%" == "MV2" (
  echo //////// Using second machine settings \\\\\\
	set MINGW_MAKE="c:\Tools\Qt\Tools\mingw810_64\bin\mingw32-make.exe"
	set QT_BIN_DIR="c:\Tools\Qt\5.15.1\mingw81_64\bin"
)

rem set APP_DST=cproto\release

echo ****************************************
echo *      Build Qt App: AuTyper
echo ****************************************

CALL %QT_BIN_DIR%\\qtenv2.bat
cd %ROOTDIR_3%

echo ****************************************
echo *      Creating AuTyper Makefile
echo ****************************************

mkdir qtbuild
cd qtbuild
del /S /F /Q *.*
qmake ..\autyper.pro

echo ****************************************
echo *      Building AuTyper App
echo ****************************************

%MINGW_MAKE%

cd %ROOTDIR_3%




echo ****************************************
echo *      Build autyper Deploying package
echo ****************************************

set INNO_DIR="D:\Program Files (x86)\Inno Setup 6"

set EXEC_FILE=qtbuild\debug\autyper.exe
set APP_DST=..\release
rem set QT_BIN_DIR=C:\Qt\5.15.1\mingw81_64\bin


mkdir %APP_DST%
del /S /F /Q %APP_DST%

copy %EXEC_FILE% %APP_DST%\

cd %APP_DST%
"%QT_BIN_DIR%\windeployqt.exe" --no-translations autyper.exe

cd %ROOTDIR_3%
copy ..\deepspeech\lib\libdeepspeech.so ..\release\

echo ****************************************
echo *        Run Inno Installer Maker
echo ****************************************

IF EXIST "Output" rmdir /S /Q "Output"
%INNO_DIR%\ISCC.exe AuTyperInstallScript.iss

copy Output\* installers\
python renameInstaller.py

cd %ROOTDIR_3%

EXIT /B %ERRORLEVEL%
