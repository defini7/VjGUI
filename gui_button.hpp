#pragma once

#include "gui_label.hpp"
#include "gui_eventhandler.hpp"

namespace def::gui
{
	class Button : public Label, public EventHandler<Button>
	{
	public:
		Button(Panel* parent = nullptr);
		Button(Panel* parent, const std::string& text, const Vector2i& pos, const Vector2i& size);
		virtual ~Button();

	public:
		void Update(Platform* platform) override;
		void Draw(Platform* platform, const Theme& theme) const override;

	private:
		bool m_Pressed;
		bool m_Held;
		bool m_Released;

	};
}
