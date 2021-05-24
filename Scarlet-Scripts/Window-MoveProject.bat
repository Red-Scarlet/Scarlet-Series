@echo off
pushd ..\
xcopy /i /y /s Scarlet-Bin\Debug-windows-x86_64\Scarlet-Window Scarlet-Sandbox\Assets\Modules\Scarlet-Window
popd

IF %ERRORLEVEL% NEQ 0 (
	PAUSE
)

exit