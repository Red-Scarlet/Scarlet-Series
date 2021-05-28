project "ImGui"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs
	{
		"include"
	}

	files
	{
		"include/ImGui/imconfig.h",
		"include/ImGui/imgui.h",
		"include/ImGui/imgui.cpp",
		"include/ImGui/imgui_draw.cpp",
		"include/ImGui/imgui_internal.h",
		"include/ImGui/imgui_widgets.cpp",
		"include/ImGui/imstb_rectpack.h",
		"include/ImGui/imstb_textedit.h",
		"include/ImGui/imstb_truetype.h",
		"include/ImGui/imgui_demo.cpp"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Profile"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		symbols "on"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"