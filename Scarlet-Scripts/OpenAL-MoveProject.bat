@echo off
pushd ..\
xcopy /i /y /s Scarlet-Bin\Debug-windows-x86_64\Scarlet-OpenAL Scarlet-Sandbox\Assets\Modules\Scarlet-OpenAL
popd

IF %ERRORLEVEL% NEQ 0 (
	PAUSE
)

exit