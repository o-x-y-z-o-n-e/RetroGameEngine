project "starship"
    language "C++"
    cppdialect "C++11"

    -- defines "SYS_SOFTWARE_GL"
    -- defines "SYS_OPENGL_1_0"
    defines "SYS_OPENGL_3_3"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/tmp/" .. outputdir .. "/%{prj.name}")

    files {
		"src/**.cpp",
		"src/**.hpp",
		"src/**.c",
		"src/**.h"
    }

    includedirs {
		"%{wks.location}/include",
		"%{wks.location}/vendor"
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
		runtime "Debug"
        symbols "On"
    
    filter "configurations:release"
		kind "WindowedApp"
		runtime "Release"
        optimize "On"