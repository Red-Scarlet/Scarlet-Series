# Scarlet-Series
C++ Framework written around Module-ResourceComponentSystem

![Scarlet](/Scarlet-Resources/Scarlet.png =250x250))

### Scarlet-Series
This Framework allows developers to build classic applications such as GameEngines, CAD software and more.
This software is built around the idea of utilizing and EntityComponentSystem named (ResourceComponentSystem)
with modules that are scriptable systems wrapped around interface layer that allows for dynamic run-time loading of
.DLL or .SO Files that contain the interface.

This achievement will allow for hotswappable Rendering API's for example: Loading OpenGL by dragging in Scarlet-OpenGL.dll into the modules folder,
anyone can make modules (plugins) and load them whist the engine software is running (Without interruption).

### Features
* Module-ResourceComponentSystem [Near Complete]
* Swapping In/Out Modules at Runtime [Work In Progress]
* GLFW Window Library + OpenGL Window Library
