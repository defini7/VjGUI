#pragma once

#include <string>

#include "gui_platform.hpp"
#include "gui_utils.hpp"
#include "defGameEngine.hpp"

namespace def::gui
{
	class Platform_defGameEngine : public Platform
	{
	public:
		Platform_defGameEngine(GameEngine* engine = nullptr);

	public:
		void DrawRect(const Vector2i& pos, const Vector2i& size, const Colour& col) override;
		void FillRect(const Vector2i& pos, const Vector2i& size, const Colour& col) override;
		void DrawText(const Vector2i& pos, const std::string& text, const Colour& col) override;

		virtual Vector2i GetMousePosition() const override;

		virtual ButtonState GetMouseButton(int id) const override;

		virtual float GetDeltaTime() const override;

		void Set(GameEngine* engine);

	private:
		GameEngine* m_Engine;

	};
}

