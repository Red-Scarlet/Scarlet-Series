project "Scarlet-Editor"
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
		"SCARLET_INTERFACE_EXPORT"
	}

	includedirs
	{ 		
		"Source",
		"%{wks.location}/Scarlet-Interface/Source",
		"%{wks.location}/Scarlet-Interface/Vendor",
		"%{wks.location}/Scarlet-Interface/Vendor/spdlog/include",
		
		"%{wks.location}/Scarlet-Additions/Scarlet-SceneGraph/Source",
		"%{wks.location}/Scarlet-Additions/Scarlet-SceneGraph/Vendor",

		"%{wks.location}/Scarlet-Additions/Scarlet-Renderer/Source",
		"%{wks.location}/Scarlet-Additions/Scarlet-Renderer/Vendor",

		"%{wks.location}/Scarlet-Additions/Scarlet-AudioFX/Source",
		"%{wks.location}/Scarlet-Additions/Scarlet-AudioFX/Vendor",

		"%{wks.location}/Scarlet-Additions/Scarlet-Editor/Vendor/ImGui/include"
	}

	links
	{
		"Scarlet-Interface",
		"Scarlet-SceneGraph",
		"Scarlet-Renderer",
		"Scarlet-AudioFX",

		"ImGui"
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