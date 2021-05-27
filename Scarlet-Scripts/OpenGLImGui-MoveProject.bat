@echo off
pushd ..\
xcopy /i /y /s Scarlet-Bin\Debug-windows-x86_64\Scarlet-OpenGLImGui Scarlet-Projects\Scarlet-Sandbox\Assets\Modules\Scarlet-OpenGLImGui
popd

IF %ERRORLEVEL% NEQ 0 (
	PAUSE
)

exit