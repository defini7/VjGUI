#include "../Include/Theme.hpp"

namespace def::gui
{
//! START IMPLEMENTATION
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
//! END IMPLEMENTATION
}
