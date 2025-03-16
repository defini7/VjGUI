#ifndef DEF_GUI_THEME_HPP
#define DEF_GUI_THEME_HPP

#include "Utils.hpp"

namespace def::gui
{
	struct Theme
	{
		Colour ApplyLight(const Colour& colour) const;

		Colour border;
		Colour componentBackground;
		Colour panelBackground;
		Colour textRegular;
		Colour textTitle;
		Colour placeholder;
		Colour titleBar;
		Colour cursor;
		Colour slider;

		float focusedLightFactor = 0.0f;
		bool forceUsingPlaceholder = false;
	};
}

#endif
