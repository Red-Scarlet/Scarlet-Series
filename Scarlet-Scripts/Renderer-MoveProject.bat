@echo off
pushd ..\
xcopy /i /y /s Scarlet-Bin\Debug-windows-x86_64\Scarlet-Renderer Scarlet-Sandbox\Assets\Modules\Scarlet-Renderer
popd

IF %ERRORLEVEL% NEQ 0 (
	PAUSE
)

exit