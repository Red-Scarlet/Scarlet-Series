@echo off

start GLFW-MoveProject.bat
start OpenGL-MoveProject.bat
start Renderer-MoveProject.bat
start SceneGraph-MoveProject.bat

IF %ERRORLEVEL% NEQ 0 (
	PAUSE
)

exit