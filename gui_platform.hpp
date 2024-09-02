#pragma once

#include <string>

#include "gui_utils.hpp"

namespace def::gui
{
	struct ButtonState
	{
		bool pressed = false;
		bool held = false;
		bool released = false;
	};

	class Platform
	{
	public:
		virtual void DrawRect(const Vector2i& pos, const Vector2i& size, const Colour& col) = 0;
		virtual void FillRect(const Vector2i& pos, const Vector2i& size, const Colour& col) = 0;
		virtual void DrawText(const Vector2i& pos, const std::string& text, const Colour& col) = 0;

		virtual Vector2i GetMousePosition() const = 0;

		virtual ButtonState GetMouseButton(int id) const = 0;

		virtual float GetDeltaTime() const = 0;
	};
}
