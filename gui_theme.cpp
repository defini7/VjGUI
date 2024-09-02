#include "gui_theme.hpp"

namespace def::gui
{
	Colour Theme::ApplyLight(const Colour& colour) const
	{
		return Colour
		(
			std::clamp((float)colour.r * focusedLightFactor, 0.0f, 255.0f),
			std::clamp((float)colour.g * focusedLightFactor, 0.0f, 255.0f),
			std::clamp((float)colour.b * focusedLightFactor, 0.0f, 255.0f),
			std::clamp((float)colour.a * focusedLightFactor, 0.0f, 255.0f)
		);
	}
}
