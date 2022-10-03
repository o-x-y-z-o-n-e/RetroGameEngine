workspace "Starship"
    configurations {
        "debug",
        "release"
    }
	
	filter "system:windows"
		architecture "x86_64"
	
	filter "system:macosx"
		architecture "arm64"


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
externalsrc = {}
externalinc = {}

externalinc["miniaudio"] = "engine/vendor/miniaudio/include"
externalinc["stb"] = "engine/vendor/stb/include"
externalinc["lua"] = "engine/vendor/lua/include/lua"
externalsrc["lua"] = "engine/vendor/lua/src"


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
		--cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines "SYS_WINDOWS"
	
	
	filter "system:macosx"
        --buildoptions "-std=c++17"
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
	
	


project "Example"
    location "example"
    language "C"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("tmp/" .. outputdir .. "/%{prj.name}")


    files {
        "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c"
    }


    includedirs {
        "engine/include/api"
    }
	
	
	filter "system:windows"
		--cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

        links {
            "Engine"
        }
	
	
	filter "system:macosx"
        buildoptions {
            --"-std=c++17",
            --"-lobjc",
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
            "Engine"
        }
	

    filter "configurations:debug"
		kind "ConsoleApp"
        symbols "On"
    
    filter "configurations:release"
		kind "WindowedApp"
        optimize "On"