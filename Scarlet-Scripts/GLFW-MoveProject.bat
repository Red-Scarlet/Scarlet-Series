@echo off
pushd ..\
xcopy /i /y /s Scarlet-Bin\Debug-windows-x86_64\Scarlet-GLFW Scarlet-Sandbox\Assets\Modules\Scarlet-GLFW
popd

IF %ERRORLEVEL% NEQ 0 (
	PAUSE
)

exit