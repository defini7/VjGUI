#pragma once

#include "gui_label.hpp"

namespace def::gui
{
	class Button : public Label
	{
	public:
		Button(Panel* parent = nullptr);
		Button(Panel* parent, const std::string& text, const Vector2i& pos, const Vector2i& size);
		virtual ~Button();

	public:
		bool Update(Platform* platform) override;
		void Draw(Platform* platform, const Theme& theme) const override;

	private:
		bool m_Pressed = false;
		bool m_Held = false;
		bool m_Released = false;

	};
}
