group "Dependencies"
	include "Scarlet-OpenGL/Vendor/GLAD"
	include "Scarlet-OpenAL/Vendor/OpenAL-Soft"
	include "Scarlet-OpenAL/Vendor/Libogg"
	include "Scarlet-OpenAL/Vendor/Vorbis"

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

group ""