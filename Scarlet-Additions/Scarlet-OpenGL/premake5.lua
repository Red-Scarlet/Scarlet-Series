project "Scarlet-OpenGL"
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

	includedirs
	{ 		
		"Source",
		"%{wks.location}/Scarlet-Interface/Source",
		"%{wks.location}/Scarlet-Interface/Vendor",
		"%{wks.location}/Scarlet-Interface/Vendor/spdlog/include",

		"%{wks.location}/Scarlet-Additions/Scarlet-GLFW/Source",
		"%{wks.location}/Scarlet-Additions/Scarlet-GLFW/Vendor",

		"%{wks.location}/Scarlet-Additions/Scarlet-OpenGL/Vendor/GLAD/include"
	}

	links
	{
		"Scarlet-Interface",
		"Scarlet-GLFW",

		"GLAD",
		"opengl32.lib"
	}

	defines
	{		
		"_CRT_SECURE_NO_WARNINGS",
		"SCARLET_INTERFACE_EXPORT"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"		
		runtime "Debug"
		symbols "on"
		defines "SCARLET_DEBUG"

	filter "configurations:Profile"
		runtime "Debug"
		symbols "on"
		defines
		{ 
			"SCARLET_DEBUG",
			"SCARLET_PROFILE"
		}

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines "SCARLET_RELEASE"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"		
		defines "SCARLET_DIST"