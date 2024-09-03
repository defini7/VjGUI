#pragma once

#include "gui_utils.hpp"

namespace def::gui
{
	struct Theme
	{
		Colour ApplyLight(const Colour& colour) const;

		Colour border;
		Colour componentBackground;
		Colour panelBackground;
		Colour text;
		Colour titleBar;
		Colour cursor;

		float focusedLightFactor;
	};
}
