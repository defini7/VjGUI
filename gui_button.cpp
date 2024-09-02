#include "gui_button.hpp"

namespace def::gui
{
	Button::Button(Panel* parent) : Label(parent), m_Pressed(false), m_Held(false), m_Released(false)
	{
	}

	Button::Button(Panel* parent, const std::string& text, const Vector2i& pos, const Vector2i& size)
		: Label(parent, text, pos, size), m_Pressed(false), m_Held(false), m_Released(false)
	{
	}

	Button::~Button()
	{
	}

	void Button::Update(Platform* platform)
	{
		Vector2i mousePos = platform->GetMousePosition();
		ButtonState mouse_leftButtonState = platform->GetMouseButton(0);

		if (IsPointInRect(mousePos, m_GlobalPosition, m_PhysicalSize))
		{
			m_EnableLight = true;

			auto HandleEvent = GetEventHandler();

			if (!HandleEvent)
				return;

			HandleEvent(this, { Event::Type::Mouse_Hover });

			Event mouseEvent;
			mouseEvent.type = Event::Type::None;

			if (mouse_leftButtonState.pressed)
				mouseEvent.type = Event::Type::Mouse_Pressed;
			else if (mouse_leftButtonState.held)
				mouseEvent.type = Event::Type::Mouse_Held;
			else if (mouse_leftButtonState.released)
				mouseEvent.type = Event::Type::Mouse_Released;

			if (mouseEvent.type != Event::Type::None)
				HandleEvent(this, mouseEvent);
		}
		else
			m_EnableLight = false;
	}

	void Button::Draw(Platform* platform, const Theme& theme) const
	{
		Label::Draw(platform, theme);
	}
}
