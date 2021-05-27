@echo off
pushd ..\
xcopy /i /y /s Scarlet-Bin\Debug-windows-x86_64\Scarlet-GLFWImGui Scarlet-Projects\Scarlet-Sandbox\Assets\Modules\Scarlet-GLFWImGui
popd

IF %ERRORLEVEL% NEQ 0 (
	PAUSE
)

exit