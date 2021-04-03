project "Scarlet-Sandbox"
	kind "ConsoleApp"
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

		"%{wks.location}/Scarlet-Engine/Source",
		"%{wks.location}/Scarlet-Engine/Vendor",
		"%{wks.location}/Scarlet-Engine/Vendor/spdlog/include",

		"%{wks.location}/Scarlet-Interface/Source",
		"%{wks.location}/Scarlet-Interface/Vendor",

		"%{wks.location}/Scarlet-Additions/Scarlet-OpenGL/Source",
		"%{wks.location}/Scarlet-Additions/Scarlet-OpenGL/Vendor"
	}

	links
	{
		"Scarlet-Engine",
		"Scarlet-Interface",
		"Scarlet-OpenGL"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"		
		kind "ConsoleApp"
		runtime "Debug"
		symbols "on"
		defines "SCARLET_DEBUG"

	filter "configurations:Profile"
		kind "ConsoleApp"
		runtime "Debug"
		symbols "on"
		defines
		{ 
			"SCARLET_DEBUG",
			"SCARLET_PROFILE"
		}

	filter "configurations:Release"
		kind "ConsoleApp"
		runtime "Release"
		optimize "on"
		defines "SCARLET_RELEASE"

	filter "configurations:Dist"
		kind "WindowedApp"
		runtime "Release"
		optimize "on"		
		defines "SCARLET_DIST"