# Scarlet-Series
C++ Framework written around Improved ECS Based Modular-Scriptable InterfaceComponentSystem

![Scarlet](/Scarlet-Resources/Scarlet.png?raw=true "Scarlet")

This Framework allows for developers to build and write classic applications such as Game Engines, CAD software and more.
The software is built around the idea of utilizing a EntityComponentSystem renamed to InterfaceComponentSystem
with modules that have scripting functionality wrapped around an interface layer that allows for dynamic run-time loading of
.DLL or .SO files that contain the code.

This achievement will allow for hotswappable Rendering API's for example: Loading OpenGL by dragging in Scarlet-OpenGL.dll into the modules folder,
anyone can make modules (plugins) and load them as the engine software is running (Without interruption). Also loads straight from the os kernel

## Modules
* Scarlet-Window
* Scarlet-GLFW
* Scarlet-Renderer
* Scarlet-OpenGL
* Scarlet-SceneGraph
* Scarlet-AudioFX
* Scarlet-OpenAL

* Scarlet-ImGui
* Scarlet-OpenGLImGui
* Scarlet-GLFWImGui

### Modules Todo
* Scarlet-Common
* Scarlet-Physics
* Scarlet-PhysX
* Scarlet-DirectX
* Scarlet-Vulkan

## Features
* Hot-swappable at runtime.
* Fast Startup

### Features Todo
* Multithreading
* Security
* Module Version Info
* Module Requirements Info

## APIs
* GLFW
* GLAD
* ImGui
* Yaml-cpp
* STB-Image
* Assimp
* OpenAL-Soft
* Minimp3
* Libogg 
* Vorbis
