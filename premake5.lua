workspace "retro_game_engine"
    configurations {
        "debug",
        "release"
    }
	
	filter "system:windows"
        defines "SYS_WINDOWS"
		architecture "x86_64"
	
	filter "system:macosx"
        defines "SYS_MACOSX"
		architecture "arm64"
    
    filter "system:linux"
        defines "SYS_LINUX"
		architecture "x86_64"
        toolset "clang"
		

------------------------------------------------------------------


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


------------------------------------------------------------------


project "2d"
    language "C++"
    cppdialect "C++11"
    location "examples/2d"

    -- defines "SYS_SOFTWARE_GL"
    defines "SYS_OPENGL_1_0"
    -- defines "SYS_OPENGL_3_3"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("tmp/" .. outputdir .. "/%{prj.name}")

    files {
        "include/rge.hpp",
		"%{prj.location}/**.cpp",
		"%{prj.location}/**.hpp",
		"%{prj.location}/**.h"
    }

    includedirs {
		"include/",
        "ext/",
		"vendor/",
        "%{prj.location}/"
    }
	
	filter "system:windows"
		staticruntime "On"
		systemversion "latest"
		entrypoint "mainCRTStartup"
	
	filter "system:macosx"
        buildoptions {
            "-F /Library/Frameworks"
        }
        linkoptions {
            "-F /Library/Frameworks",
            "-framework Foundation",
            "-framework Cocoa",
            "-framework OpenGL"
        }
        files {
            "ext/macosx.mm"
        }
	
	filter "system:linux"
		links {
            "m"
        }
	
    filter "configurations:debug"
		kind "ConsoleApp"
        symbols "On"
    
    filter "configurations:release"
		kind "WindowedApp"
        optimize "On"


------------------------------------------------------------------


project "3d"
    language "C++"
    cppdialect "C++11"
    location "examples/3d"

    defines "SYS_SOFTWARE_GL"
    -- defines "SYS_OPENGL_1_0"
    -- defines "SYS_OPENGL_3_3"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("tmp/" .. outputdir .. "/%{prj.name}")

    files {
        "include/rge.hpp",
		"%{prj.location}/**.cpp",
		"%{prj.location}/**.hpp",
		"%{prj.location}/**.h"
    }

    includedirs {
		"include/",
        "ext/",
		"vendor/",
        "%{prj.location}/"
    }
	
	filter "system:windows"
		staticruntime "On"
		systemversion "latest"
		entrypoint "mainCRTStartup"
	
	filter "system:macosx"
        buildoptions {
            "-F /Library/Frameworks"
        }
        linkoptions {
            "-F /Library/Frameworks",
            "-framework Foundation",
            "-framework Cocoa",
            "-framework OpenGL"
        }
        files {
            "ext/macosx.mm"
        }
	
	filter "system:linux"
		links {
            "m"
        }
	
    filter "configurations:debug"
		kind "ConsoleApp"
        symbols "On"
    
    filter "configurations:release"
		kind "WindowedApp"
        optimize "On"


------------------------------------------------------------------


project "starship"
    language "C++"
    cppdialect "C++11"
    location "examples/starship"

    -- defines "SYS_SOFTWARE_GL"
    defines "SYS_OPENGL_1_0"
    -- defines "SYS_OPENGL_3_3"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("tmp/" .. outputdir .. "/%{prj.name}")

    files {
        "include/rge.hpp",
		"%{prj.location}/**.cpp",
		"%{prj.location}/**.hpp",
		"%{prj.location}/**.h"
    }

    includedirs {
		"include/",
        "ext/",
		"vendor/",
        "%{prj.location}/"
    }
	
	filter "system:windows"
		staticruntime "On"
		systemversion "latest"
		entrypoint "mainCRTStartup"
	
	filter "system:macosx"
        buildoptions {
            "-F /Library/Frameworks"
        }
        linkoptions {
            "-F /Library/Frameworks",
            "-framework Foundation",
            "-framework Cocoa",
            "-framework OpenGL"
        }
        files {
            "ext/macosx.mm"
        }
	
	filter "system:linux"
		links {
            "m"
        }
	
    filter "configurations:debug"
		kind "ConsoleApp"
        symbols "On"
    
    filter "configurations:release"
		kind "WindowedApp"
        optimize "On"