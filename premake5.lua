

workspace "bqengine"
architecture "x64"
startproject "sandbox"

configurations
{
    "Debug",
    "Release"
}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["GLFW"] = "deps/glfw/include"
IncludeDir["GLEW"] = "deps/glew/include"
IncludeDir["STB"] = "deps/stb/include"
IncludeDir["GLM"] = "deps/glm"
project "bq"
	location "bq"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	libdirs 
	{ 
		"deps/glfw/libs",
		"deps/glew/lib"
 	}	

	files
	{
		"%{prj.name}/include/**.hpp",
		"%{prj.name}/source/**.cpp",
    }
    includedirs
	{
        "%{prj.name}/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.STB}",
		"%{IncludeDir.GLM}"
	}
	links
	{	
		"glfw3_mt",
		"opengl32",
		"glew32s"
	}
	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
	filter "configurations:Release"
		defines "NDEBUG"
		runtime "Release"
		optimize "on"
	filter "configurations:*"
		defines "GLEW_STATIC"
		defines "BQ_BUILD"

project "sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.hpp",
		"%{prj.name}/source/**.cpp",
		"%{prj.name}/res/shaders/**.shader",
		"%{prj.name}/res/textures/**.png",
    }
	libdirs 
	{ 
		"deps/glfw/libs",
		"deps/glew/lib"
 	}	
	links
	{
		"glfw3_mt",
		"opengl32",
		"glew32s",
		"bq"
	}
	includedirs
	{
        "%{prj.name}/include",
		"bq/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.STB}",
		"%{IncludeDir.GLM}"
	}

	filter "system:windows"
		systemversion "latest"
		defines{ "PLATFORM_WINDOWS" }

	
	filter "configurations:*"
		libdirs { "gamelib/deps/SFML/lib" }	


	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	