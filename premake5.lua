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

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("tmp/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/**.hpp",
		"%{prj.location}/**.cpp"
    }

    includedirs {
		"%{prj.location}/"
    }
	
	filter "system:windows"
		defines "SYS_WINDOWS"
		staticruntime "On"
		systemversion "latest"
	
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