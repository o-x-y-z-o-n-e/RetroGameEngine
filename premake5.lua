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

project "example"
    location ""
    language "C++"


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
		

------------------------------------------------------------------


project "CHIP-8"
	location "examples/chip8"
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