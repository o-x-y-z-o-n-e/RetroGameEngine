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


group "examples"
	include "examples/2d"
	include "examples/3d"
	include "examples/starship"
	include "examples/platformer"
group ""


------------------------------------------------------------------
