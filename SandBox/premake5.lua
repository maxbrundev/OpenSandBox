workspace "SandBox"
	configurations { "Debug", "Release" }
	platforms { "Win32", "x64" }
	startproject "SandBox"

outputdir = "%{wks.location}/../Bin/"
objoutdir = "%{wks.location}/../Bin-Int/"
dependdir = "%{wks.location}/../Build/OpenSandBox/"

project "SandBox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	files { "**.h", "**.inl", "**.cpp" }

	pchheader "pch.h"
	pchsource "pch.cpp"

	includedirs { "%{wks.location}", "include", dependdir .. "include/" }
	libdirs { dependdir .. "lib/%{cfg.buildcfg}/%{cfg.platform}/" }

	links { "assimp-vc141-mt", "glew32", "glfw3dll", "opengl32", "OpenSandBox" }

	targetdir (outputdir .. "%{prj.name}/%{cfg.buildcfg}/%{cfg.platform}")
	objdir (objoutdir .. "%{prj.name}/%{cfg.buildcfg}/%{cfg.platform}")
	characterset ("MBCS")
	debugdir "%{wks.location}../Bin/%{prj.name}/%{cfg.buildcfg}/%{cfg.platform}"

	postbuildcommands {
		"xcopy /e /y /i /r \"%{wks.location}..\\Build\\OpenSandBox\\bin\\%{cfg.buildcfg}\\%{cfg.platform}\\*.dll\" \"%{wks.location}..\\Bin\\%{prj.name}\\%{cfg.buildcfg}\\%{cfg.platform}\\\"",
		"xcopy /e /y /i /r \"%{wks.location}\\res\" \"%{wks.location}..\\Bin\\%{prj.name}\\%{cfg.buildcfg}\\%{cfg.platform}\\\"",

		"EXIT /B 0"
	}

	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"

	filter { "configurations:Release" }
		defines { "NDEBUG" }
		optimize "On"