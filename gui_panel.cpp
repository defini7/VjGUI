#include "gui_panel.hpp"
#include "gui_component.hpp"

namespace def::gui
{
	Panel::Panel() : Component(), m_Drag(false)
	{
	}

	Panel::Panel(const std::string& title, const Vector2i& pos, const Vector2i& size)
		: Component(nullptr, pos, size), m_Drag(false), m_Title(title)
	{
	}

	Panel::~Panel()
	{
	}

	std::string Panel::GetTitle() const
	{
		return m_Title;
	}

	void Panel::SetTitle(const std::string& title)
	{
		m_Title = title;
	}

	bool Panel::Update(Platform* platform)
	{
		Vector2i mousePos = platform->GetMousePosition();
		HardwareButton mouseState = platform->GetMouseButton(HardwareButton::ButtonType::LEFT);

		if (IsPointInRect(mousePos, m_GlobalPosition, m_Size))
		{
			HandleEvent(this, { Event::Type::Mouse_Hover });

			if (mouseState.pressed)
			{
				// TODO: Make title bar size constant
				if (IsPointInRect(mousePos, m_GlobalPosition, Vector2i(m_Size.x, 20)))
				{
					m_Drag = true;
					m_DragOffset = mousePos - m_GlobalPosition;
				}
			}
		}

		if (m_Drag)
			m_GlobalPosition = mousePos - m_DragOffset;

		if (mouseState.released)
			m_Drag = false;

		for (auto& component : m_Children)
		{
			if (m_IsVisible)
			{
				component->UpdatePosition();
				component->EnableLight(component->Update(platform));
			}
		}

		return false;
	}

	void Panel::Draw(Platform* platform, const Theme& theme) const
	{
		// TODO: Make thickness of title bar customisable
		platform->FillRect(m_GlobalPosition, m_Size, theme.panelBackground);
		platform->DrawRect(m_GlobalPosition, m_Size, theme.border);
		platform->FillRect(m_GlobalPosition, { m_Size.x, 20 }, theme.titleBar);
		
		Component::Draw(platform, theme);
	}
}
