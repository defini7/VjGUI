---@diagnostic disable: undefined-global
project "Engine"
    location ""
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    targetdir ("%{wks.location}/Build/Target/" .. OUTPUT_DIR .. "/%{prj.name}")
    objdir ("%{wks.location}/Build/Obj/" .. OUTPUT_DIR .. "/%{prj.name}")

    -- Linking with GLFW3

    links { "GLFW3" }

    -- Setting up precompiled headers

    pchheader "Pch.hpp"
    pchsource "Sources/Pch.cpp"

    -- Including all source and header files of the engine

    files
    {
        "Include/*.hpp",
        "Sources/*.cpp"
    }

    removefiles { "Sources/Utils.cpp" }

    filter { "system:windows or system:linux or system:macosx" }
        removefiles
        {
            "Include/PlatformEmscripten.hpp",
            "Sources/PlatformEmscripten.cpp"
        }

    filter "system:emscripten"
        removefiles
        {
            "Include/PlatformGLFW3.hpp",
            "Sources/PlatformGLFW3.cpp"
        }

    filter {}

    -- Including headers for libraries

    includedirs
    {
        "Vendor/glfw/include",
        "Vendor/stb",
        "Include",
        "Sources",
    }

    -- Linking with libraries

    filter "system:windows"
        links { "gdi32", "user32", "kernel32", "opengl32", "glu32" }

    filter "system:linux"
        links
        {
            "GL", "GLU", "glut", "GLEW", "X11",
            "Xxf86vm", "Xrandr", "pthread", "Xi", "dl",
            "Xinerama", "Xcursor"
        }

    filter "system:macosx"
        links
        {
            "Metal.framework", "QuartzCore.framework",
            "Cocoa.framework", "OpenGL.framework",
            "IOKit.framework", "CoreVideo.framework"
        }

    -- Platform specific flags

    filter "system:windows"
        warnings "Extra"
        staticruntime "On"
        systemversion "latest"

    filter {}

    -- Puts the engine's .dll file near the App executable

    postbuildcommands
    {
        "{COPY} %{cfg.buildtarget.relpath} \"%{wks.location}/Build/Target/" .. OUTPUT_DIR .. "/App/\""
    }

    -- Build configurations

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    filter {}
