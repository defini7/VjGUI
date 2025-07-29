---@diagnostic disable: undefined-global
project "App"
    location ""
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"

    -- e.g. minimum version is Catalina
    buildoptions { "-mmacosx-version-min=10.15" }

    targetdir ("%{wks.location}/Build/Target/" .. OUTPUT_DIR .. "/%{prj.name}")
    objdir ("%{wks.location}/Build/Obj/" .. OUTPUT_DIR .. "/%{prj.name}")

    -- Link projects

    links { "GLFW3", "Engine", "Framework" }

    files
    {
        "*.cpp"
    }

    -- Including headers for libraries

    includedirs
    {
        "../Engine/Vendor/glfw/include",
        "../Engine/Vendor/stb",
        "../Engine/Include",
        "../Framework/Include"
    }

    -- Linking with libraries

    --libdirs { "Engine/Vendor/glfw/%{cfg.architecture}" }

    filter "system:windows"
        links { "gdi32", "user32", "kernel32", "opengl32", "GLFW3", "glu32" }

    filter "system:linux"
        links
        {
            "GL", "GLU", "glut", "GLEW", "GLFW3", "X11",
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

    filter {}

    -- Build configurations

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    filter {}