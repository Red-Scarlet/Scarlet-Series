# Scarlet-Series
C++ Framework written around Improved ECS Based Modular-Scriptable InterfaceComponentSystem

![Scarlet](/Scarlet-Resources/Scarlet.png?raw=true "Scarlet")

### Scarlet-Series
This Framework allows for developers to build and write classic applications such as Game Engines, CAD software and more.
The software is built around the idea of utilizing a EntityComponentSystem renamed to ResourceComponentSystem
with modules that have scripting functionality wrapped around an interface layer that allows for dynamic run-time loading of
.DLL or .SO Files that contain the interface code.

This achievement will allow for hotswappable Rendering API's for example: Loading OpenGL by dragging in Scarlet-OpenGL.dll into the modules folder,
anyone can make modules (plugins) and load them as the engine software is running (Without interruption).

### Modules
* Scarlet-Window
* Scarlet-GLFW
* Scarlet-Renderer
* Scarlet-OpenGL
* Scarlet-SceneGraph
* Scarlet-AudioFX
* Scarlet-OpenAL
