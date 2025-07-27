#ifndef VJGUI_HPP
#define VJGUI_HPP

#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <memory>
#include <list>
#include <any>
#include <unordered_map>

#ifdef VJGUI_PLATFORM_DEFGAMEENGINE
#include "defGameEngine.hpp"
#endif

namespace def::gui
{
    //! GRAB ../Include/Utils.hpp DECLARATION
    //! GRAB ../Include/Eventhandler.hpp DECLARATION
    //! GRAB ../Include/Platform.hpp DECLARATION

#ifdef VJGUI_PLATFORM_DEFGAMEENGINE
    //! GRAB ../Include/Platform_defGameEngine.hpp DECLARATION
#endif
    
    //! GRAB ../Include/Theme.hpp DECLARATION
    //! GRAB ../Include/Component.hpp DECLARATION
    //! GRAB ../Include/Panel.hpp DECLARATION
    //! GRAB ../Include/Manager.hpp DECLARATION
    
    class Button;

    //! GRAB ../Include/Label.hpp DECLARATION
    //! GRAB ../Include/Button.hpp DECLARATION
    //! GRAB ../Include/TextEntry.hpp DECLARATION
    //! GRAB ../Include/Slider.hpp DECLARATION
    //! GRAB ../Include/List.hpp DECLARATION

#ifdef VJGUI_IMPL
#undef VJGUI_IMPL

    //! GRAB ../Include/Utils.hpp IMPLEMENTATION
    
#ifdef VJGUI_PLATFORM_DEFGAMEENGINE
    //! GRAB ../Sources/Platform_defGameEngine.cpp IMPLEMENTATION
#endif

    //! GRAB ../Sources/Theme.cpp IMPLEMENTATION
    //! GRAB ../Sources/Component.cpp IMPLEMENTATION
    //! GRAB ../Sources/Panel.cpp IMPLEMENTATION
    //! GRAB ../Sources/Manager.cpp IMPLEMENTATION
    //! GRAB ../Sources/Label.cpp IMPLEMENTATION
    //! GRAB ../Sources/Button.cpp IMPLEMENTATION
    //! GRAB ../Sources/TextEntry.cpp IMPLEMENTATION
    //! GRAB ../Sources/Slider.inl IMPLEMENTATION
    //! GRAB ../Sources/List.cpp IMPLEMENTATION
#endif
}

#endif
