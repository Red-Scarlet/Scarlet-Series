workspace "Scarlet-Series"
	architecture "x86_64"
	startproject "Scarlet-Sandbox"

	configurations
	{
		"Debug",
		"Profile",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Scarlet-Core"
include "Scarlet-Projects"
include "Scarlet-Additions"