---@diagnostic disable: undefined-global
workspace "VjGui"
    filter "system:windows or system:linux"
        architecture "x64"

    filter "system:macosx"
        architecture "ARM64"
        
    startproject "App"

    configurations
    {
        "Debug",
        "Release"
    }

OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Engine/Vendor/glfw"
include "Engine/"
include "Framework/"
include "App/"
