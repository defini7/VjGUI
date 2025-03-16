---@diagnostic disable: undefined-global
workspace "VjGui"
    architecture "x64"
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
