project "Scarlet-Editor"
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

		"%{wks.location}/Scarlet-Core/Scarlet-Engine/Source",
		"%{wks.location}/Scarlet-Core/Scarlet-Engine/Vendor",
		"%{wks.location}/Scarlet-Core/Scarlet-Engine/Vendor/spdlog/include",

		"%{wks.location}/Scarlet-Core/Scarlet-Interface/Source",
		"%{wks.location}/Scarlet-Core/Scarlet-Interface/Vendor"
	}

	links
	{
		"Scarlet-Engine",
		"Scarlet-Interface"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		kind "ConsoleApp"	
		runtime "Debug"
		symbols "on"
		defines "SCARLET_DEBUG"
		buildoptions "/MDd"

	filter "configurations:Profile"
		kind "ConsoleApp"
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
		buildoptions "/MD"

	filter "configurations:Dist"
		kind "WindowedApp"
		runtime "Release"
		optimize "on"		
		defines "SCARLET_DIST"
		buildoptions "/MD"