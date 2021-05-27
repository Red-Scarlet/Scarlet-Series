project "Scarlet-OpenGLImGui"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/Scarlet-Bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/Scarlet-Bin-Int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLAD_GLAPI_EXPORT",
		"SCARLET_INTERFACE_EXPORT"
	}

	includedirs
	{ 		
		"Source",
		"%{wks.location}/Scarlet-Core/Scarlet-Interface/Source",
		"%{wks.location}/Scarlet-Core/Scarlet-Interface/Vendor",
		"%{wks.location}/Scarlet-Core/Scarlet-Interface/Vendor/spdlog/include",

		"%{wks.location}/Scarlet-Additions/Scarlet-ImGui/Source",
		"%{wks.location}/Scarlet-Additions/Scarlet-ImGui/Vendor",

		"%{wks.location}/Scarlet-Additions/Scarlet-Renderer/Source",
		"%{wks.location}/Scarlet-Additions/Scarlet-Renderer/Vendor",

		"%{wks.location}/Scarlet-Additions/Scarlet-OpenGL/Source",
		"%{wks.location}/Scarlet-Additions/Scarlet-OpenGL/Vendor",

		"%{wks.location}/Scarlet-Additions/Scarlet-Window/Source",
		"%{wks.location}/Scarlet-Additions/Scarlet-Window/Vendor",

		"%{wks.location}/Scarlet-Additions/Scarlet-ImGui/Vendor/ImGui/include",
		"%{wks.location}/Scarlet-Additions/Scarlet-OpenGL/Vendor/GLAD/include"
	}

	libdirs 
	{ 
		"%{wks.location}/Scarlet-Additions/Scarlet-OpenGL/Vendor/GLAD/lib"
	}

	links
	{
		"Scarlet-Interface",
		"Scarlet-ImGui",
		"Scarlet-Renderer",
		"Scarlet-OpenGL",
		"Scarlet-Window",
		"ImGui",
		"GLAD",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"		
		runtime "Debug"
		symbols "on"
		defines "SCARLET_DEBUG"
		buildoptions "/MDd"

	filter "configurations:Profile"
		runtime "Debug"
		symbols "on"
		buildoptions "/MDd"
		defines
		{ 
			"SCARLET_DEBUG",
			"SCARLET_PROFILE"
		}

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines "SCARLET_RELEASE"
		buildoptions "/MDd"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"		
		defines "SCARLET_DIST"
		buildoptions "/MDd"