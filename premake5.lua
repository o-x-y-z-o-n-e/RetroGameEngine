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
externaldir = {}
externalinc = {}

externalinc["stb_image"] = "engine/vendor/stb_image/include"


project "Engine"
    location "engine"
    kind "StaticLib"
    language "C"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("tmp/" .. outputdir .. "/%{prj.name}")


    files {
		"%{prj.name}/include/**.h",
        "%{prj.name}/src/**.c"
    }


    includedirs {
        "%{prj.name}/include",
        "%{prj.name}/include/**",
        
		externalinc["stb_image"]
    }
	
	
	filter "system:windows"
		--cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines "SYS_WINDOWS"
	
	
	filter "system:macosx"
        buildoptions "-std=c++17"
		defines "SYS_MACOSX"
	
	
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
    language "C++"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("tmp/" .. outputdir .. "/%{prj.name}")


    files {
        "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp"
    }


    includedirs {
        "engine/include/api"
    }
	
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

        links {
            "Engine"
        }
	
	
	filter "system:macosx"
        buildoptions {
            "-std=c++17",
            "-F /Library/Frameworks"
        }
        linkoptions {"-F /Library/Frameworks"}

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