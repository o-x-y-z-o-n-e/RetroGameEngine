workspace "RetroGameEngine"
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
externalsrc = {}
externalinc = {}

externalinc["miniaudio"] = "engine/vendor/miniaudio/include"
externalinc["stb"] = "engine/vendor/stb/include"
externalinc["lua"] = "engine/vendor/lua/include/lua"
externalsrc["lua"] = "engine/vendor/lua/src"


------------------------------------------------------------------


project "Engine"
    location "engine"
    kind "StaticLib"
    language "C"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("tmp/" .. outputdir .. "/%{prj.name}")


    files {
		"engine/include/**.h",
        "engine/src/**.c",
		externalsrc["lua"] .. "/**.c"
    }
	
	
    includedirs {
        "engine/include",
        "engine/include/**",
        
		externalinc["stb"],
		externalinc["lua"],
		externalinc["miniaudio"]
    }
	
	
	filter "system:windows"
		staticruntime "On"
		systemversion "latest"
		
		defines "SYS_WINDOWS"
		links "XInput"
	
	filter "system:macosx"
		defines "SYS_MACOSX"

        files "%{prj.name}/src/**.m"
        filter "files:**.m"
            compileas "Objective-C"
	
	
	filter "system:linux"
		defines "SYS_LINUX"
		

    filter "configurations:debug"
        defines "EXC_DEBUG"
        symbols "On"
    
    filter "configurations:release"
        defines "EXC_RELEASE"
        optimize "On"
	

------------------------------------------------------------------


project "Scenic"
    location "examples/scenic"
    language "C"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("tmp/" .. outputdir .. "/%{prj.name}")


    files {
        "%{prj.location}/include/**.h",
		"%{prj.location}/src/**.c"
    }


    includedirs {
		"%{prj.location}/include/",
        "engine/include/api"
    }
	
	
	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

        links {
            "Engine"
        }
	
	
	filter "system:macosx"
        buildoptions {
            "-F /Library/Frameworks"
        }
        linkoptions {
            "-F /Library/Frameworks",
            "-framework Cocoa",
            "-framework Foundation"
        }

        links {
            "Engine"
        }
	
	
	filter "system:linux"
		links {
            "Engine",
            "m"
        }
	

    filter "configurations:debug"
		kind "ConsoleApp"
        symbols "On"
    
    filter "configurations:release"
		kind "WindowedApp"
        optimize "On"


------------------------------------------------------------------


project "Starship"
	location "examples/starship"
	language "C"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("tmp/" .. outputdir .. "/%{prj.name}")


    files {
        "%{prj.location}/include/**.h",
		"%{prj.location}/src/**.c"
    }


    includedirs {
		"%{prj.location}/include/",
        "engine/include/api"
    }
	
	
	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

        links {
            "Engine"
        }
	
	
	filter "system:macosx"
        buildoptions {
            "-F /Library/Frameworks"
        }
        linkoptions {
            "-F /Library/Frameworks",
            "-framework Cocoa",
            "-framework Foundation"
        }

        links {
            "Engine"
        }
	
	
	filter "system:linux"
		links {
            "Engine",
            "m"
        }
	

    filter "configurations:debug"
		kind "ConsoleApp"
        symbols "On"
    
    filter "configurations:release"
		kind "WindowedApp"
        optimize "On"