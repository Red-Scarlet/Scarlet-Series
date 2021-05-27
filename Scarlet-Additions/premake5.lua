group "Dependencies"
	include "Scarlet-SceneGraph/Vendor/Yaml-cpp"
	include "Scarlet-Renderer/Vendor/Assimp"

	include "Scarlet-GLFW/Vendor/GLFW"

	include "Scarlet-OpenGL/Vendor/GLAD"
	include "Scarlet-OpenAL/Vendor/OpenAL-Soft"
	include "Scarlet-OpenAL/Vendor/Libogg"
	include "Scarlet-OpenAL/Vendor/Vorbis"

	include "Scarlet-ImGui/Vendor/ImGui"

group ""

group "Scarlet-Additions"
	include "Scarlet-Window"
	include "Scarlet-GLFW"

	include "Scarlet-OpenGL"
	include "Scarlet-Vulkan"
	include "Scarlet-DirectX"

	include "Scarlet-AudioFX"
	include "Scarlet-OpenAL"

	include "Scarlet-Renderer"
	include "Scarlet-Physics"
	include "Scarlet-SceneGraph"

	include "Scarlet-PhysX"
	include "Scarlet-ImGui"
	include "Scarlet-GLFWImGui"
	include "Scarlet-OpenGLImGui"

group ""