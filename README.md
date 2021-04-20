# Scarlet-Series
C++ Framework written around Module-ResourceComponentSystem

![Scarlet](/Scarlet-Resources/Scarlet.png?raw=true "Scarlet")

### Scarlet-Series
This Framework allows for developers to build and write classic applications such as Game Engines, CAD software and more.
The software is built around the idea of utilizing a EntityComponentSystem renamed to ResourceComponentSystem
with modules that have scripting functionality wrapped around an interface layer that allows for dynamic run-time loading of
.DLL or .SO Files that contain the interface code.

This achievement will allow for hotswappable Rendering API's for example: Loading OpenGL by dragging in Scarlet-OpenGL.dll into the modules folder,
anyone can make modules (plugins) and load them as the engine software is running (Without interruption).

### Features
* Module-ResourceComponentSystem [Near Complete]
* Swapping In/Out Modules at Runtime [Work In Progress]
* GLFW Window Library + OpenGL Window Library
