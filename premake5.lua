workspace "retro_game_engine"
    configurations {
        "debug",
        "release"
    }
	
	filter "system:windows"
		architecture "x86_64"
	
	filter "system:macosx"
		architecture "arm64"
    
    filter "system:linux"
		architecture "x86_64"
        toolset "clang"
		

------------------------------------------------------------------


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "example"
    language "C++"
    cppdialect "C++11"
    location "./"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("tmp/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/rge/rge.hpp",
        "%{prj.location}/rge/ecs.hpp",
        "%{prj.location}/rge/gl.hpp",
		"%{prj.location}/example.cpp"
    }

    includedirs {
        "%{prj.location}/",
        "%{prj.location}/vendor/"
    }
	
	filter "system:windows"
		defines "SYS_WINDOWS"
		staticruntime "On"
		systemversion "latest"
		entrypoint "mainCRTStartup"
	
	filter "system:macosx"
		defines "SYS_MACOSX"
        buildoptions {
            "-F /Library/Frameworks"
        }
        linkoptions {
            "-F /Library/Frameworks",
            "-framework Cocoa",
            "-framework Foundation"
        }
	
	filter "system:linux"
		defines "SYS_LINUX"
		links {
            "m"
        }
	
    filter "configurations:debug"
		kind "ConsoleApp"
        symbols "On"
    
    filter "configurations:release"
		kind "WindowedApp"
        optimize "On"