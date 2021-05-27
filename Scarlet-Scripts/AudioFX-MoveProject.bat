@echo off
pushd ..\
xcopy /i /y /s Scarlet-Bin\Debug-windows-x86_64\Scarlet-AudioFX Scarlet-Projects\Scarlet-Sandbox\Assets\Modules\Scarlet-AudioFX
popd

IF %ERRORLEVEL% NEQ 0 (
	PAUSE
)

exit