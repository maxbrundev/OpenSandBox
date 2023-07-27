workspace "OpenSandBox"
	configurations { "Debug", "Release" }
	platforms { "Win32", "x64" }
	startproject "OpenSandBox"

outputdir = "%{wks.location}/../Bin/"
objoutdir = "%{wks.location}/../Bin-Int/"
dependdir = "%{wks.location}/../Dependencies/"

project "OpenSandBox"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"

	defines { "OPENSANDBOX_EXPORT" }

	files { "**.h", "**.inl", "**.cpp" }

	pchheader "OpenSandBox.h"
	pchsource "OpenSandBox.cpp"

	includedirs { "%{wks.location}", "include", dependdir .. "glfw/include", dependdir .. "glew/include", dependdir .. "stb_image/include", dependdir .. "assimp/include", dependdir .. "glm/include" }
	libdirs { dependdir .. "glfw/lib/%{cfg.platform}", dependdir .. "glew/lib/%{cfg.platform}", dependdir .. "assimp/lib/%{cfg.platform}" }

	links { "assimp-vc141-mt", "glew32", "glfw3dll", "opengl32" }

	targetdir (outputdir .. "%{prj.name}/%{cfg.buildcfg}/%{cfg.platform}")
	objdir (objoutdir .. "%{prj.name}/%{cfg.buildcfg}/%{cfg.platform}")
	characterset ("MBCS")
	debugdir "%{wks.location}../Build/%{prj.name}/%{cfg.buildcfg}/%{cfg.platform}"

	postbuildcommands {
		"for /f \"delims=|\" %%i in ('dir /B /S \"%{wks.location}..\\Dependencies\\*.dll\"') do xcopy /Q /Y \"%%i\" \"%{wks.location}..\\Bin\\%{prj.name}\\%{cfg.buildcfg}\\%{cfg.platform}\\\"",

		"xcopy /Y /I /Q /D \"%{wks.location}..\\Bin\\%{prj.name}\\%{cfg.buildcfg}\\%{cfg.platform}\\*.dll\" \"%{wks.location}..\\Build\\%{prj.name}\\bin\\%{cfg.buildcfg}\\%{cfg.platform}\\\"",
		"xcopy /Y /I /Q /D \"%{wks.location}..\\Bin\\%{prj.name}\\%{cfg.buildcfg}\\%{cfg.platform}\\*.lib\" \"%{wks.location}..\\Build\\%{prj.name}\\lib\\%{cfg.buildcfg}\\%{cfg.platform}\\\"",

		"xcopy /e /y /i /r \"%{wks.location}..\\Dependencies\\glfw\\include\" \"%{wks.location}..\\Build\\%{prj.name}\\include\\\"",
		"xcopy /e /y /i /r \"%{wks.location}..\\Dependencies\\glew\\include\" \"%{wks.location}..\\Build\\%{prj.name}\\include\\\"",
		"xcopy /e /y /i /r \"%{wks.location}..\\Dependencies\\assimp\\include\" \"%{wks.location}..\\Build\\%{prj.name}\\include\\\"",
		"xcopy /e /y /i /r \"%{wks.location}..\\Dependencies\\glm\\include\" \"%{wks.location}..\\Build\\%{prj.name}\\include\\\"",
		"xcopy /e /y /i /r \"%{wks.location}..\\Dependencies\\stb_image\\include\" \"%{wks.location}..\\Build\\%{prj.name}\\include\\\"",

		"xcopy /e /y /i /r \"%{wks.location}\\include\\%{prj.name}\" \"%{wks.location}..\\Build\\%{prj.name}\\include\\%{prj.name}\\\"",


		"xcopy /e /y /i /r \"%{wks.location}..\\Dependencies\\glfw\\lib\\%{cfg.platform}\\*.lib\" \"%{wks.location}..\\Build\\%{prj.name}\\lib\\%{cfg.buildcfg}\\%{cfg.platform}\\\"",
		"xcopy /e /y /i /r \"%{wks.location}..\\Dependencies\\glew\\lib\\%{cfg.platform}\\*.lib\" \"%{wks.location}..\\Build\\%{prj.name}\\lib\\%{cfg.buildcfg}\\%{cfg.platform}\\\"",
		"xcopy /e /y /i /r \"%{wks.location}..\\Dependencies\\assimp\\lib\\%{cfg.platform}\\*.lib\" \"%{wks.location}..\\Build\\%{prj.name}\\lib\\%{cfg.buildcfg}\\%{cfg.platform}\\\"",

		"EXIT /B 0"
	}

	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"

	filter { "configurations:Release" }
		defines { "NDEBUG" }
		optimize "On"