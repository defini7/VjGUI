#pragma once

#include <string>

#include "Platform.hpp"
#include "Utils.hpp"
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
		void DrawLine(const Vector2i& pos1, const Vector2i& pos2, const Colour& col) override;

		virtual Vector2i GetMousePosition() const override;

		virtual HardwareButton GetMouseButton(HardwareButton::ButtonType id) const override;
		virtual HardwareButton GetKey(HardwareButton::KeyType id) const override;

		virtual float GetDeltaTime() const override;
		virtual bool IsCaps() const override;

		void Set(GameEngine* engine);

		static Pixel ColourToPixel(const Colour& col);

	private:
		GameEngine* m_Engine;

		std::unordered_map<HardwareButton::KeyType, Key> m_KeyLookup;
		std::unordered_map<HardwareButton::ButtonType, Button> m_ButtonLookup;

	};
}

