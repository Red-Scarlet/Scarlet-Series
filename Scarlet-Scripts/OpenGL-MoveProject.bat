@echo off
pushd ..\
xcopy /i /y /s Scarlet-Bin\Debug-windows-x86_64\Scarlet-OpenGL Scarlet-Sandbox\Assets\Modules\Scarlet-OpenGL
popd

IF %ERRORLEVEL% NEQ 0 (
	PAUSE
)

exit