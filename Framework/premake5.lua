---@diagnostic disable: undefined-global
project "Framework"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    targetdir ("%{wks.location}/Build/Target/" .. OUTPUT_DIR .. "/%{prj.name}")
    objdir ("%{wks.location}/Build/Obj/" .. OUTPUT_DIR .. "/%{prj.name}")

    links { "Engine" }

    includedirs
    {
        "../Engine/Vendor/glfw/include",
        "../Engine/Vendor/stb",
        "../Engine/Include"
    }

    files
    {
        "Include/*.hpp",
        "Sources/*.cpp",
        "Sources/*.inl"
    }

    filter "system:windows"
        warnings "Extra"
        staticruntime "On"
        systemversion "latest"

    filter {}

    -- Puts the framework's .dll file near the App executable

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
