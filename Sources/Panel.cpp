#include "../Include/Panel.hpp"
#include "../Include/Component.hpp"

namespace def::gui
{
	Panel::Panel(Component* parent) : Component(parent)
	{
	}

	Panel::Panel(Component* parent, const std::string& title, const Vector2i& pos, const Vector2i& size)
		: Component(parent, pos, size), m_Title(title)
	{
	}

	Panel::~Panel()
	{
	}

	const std::string& Panel::GetTitle() const
	{
		return m_Title;
	}

	void Panel::SetTitle(const std::string& title)
	{
		m_Title = title;
	}

	bool Panel::Update(Platform* platform)
	{
		if (!m_Update)
			return false;

		Vector2i mousePos = platform->GetMousePosition();
		HardwareButton mouseState = platform->GetMouseButton(HardwareButton::ButtonType::LEFT);

		if (IsPointInRect(mousePos, m_GlobalPosition, m_Size))
		{
			HandleEvent(this, Event::Mouse_Hover);

			if (!m_FixedPos)
			{
				if (mouseState.pressed && IsPointInRect(mousePos, m_GlobalPosition, Vector2i(m_Size.x, TITLE_BAR_WIDTH)))
				{
					m_Drag = true;
					m_DragOffset = mousePos - m_GlobalPosition;
				}
			}
		}

		if (!m_FixedPos)
		{
			if (m_Drag)
				m_GlobalPosition = mousePos - m_DragOffset;

			if (mouseState.released)
				m_Drag = false;
		}

		for (auto& component : m_Children)
		{
			component->UpdatePosition();
			component->EnableLight(component->Update(platform));
		}

		return false;
	}

	void Panel::Draw(Platform* platform, const Theme& theme) const
	{
		if (!m_IsVisible)
			return;

		platform->FillRect(m_GlobalPosition, m_Size, theme.panelBackground);
		platform->DrawRect(m_GlobalPosition, m_Size, theme.border);

		if (m_ShowTitleBar)
		{
			platform->FillRect(m_GlobalPosition, { m_Size.x, TITLE_BAR_WIDTH }, theme.titleBar);

			if (m_ShowTitle)
				platform->DrawText(m_GlobalPosition + Vector2i(2, TITLE_BAR_WIDTH / 2 - 2), m_Title, theme.textTitle);
		}

		Component::Draw(platform, theme);
	}

	void Panel::ShowTitleBar(bool enable)
	{
		m_ShowTitleBar = enable;
		if (!enable) m_ShowTitle = false;
	}

	void Panel::ShowTitle(bool enable)
	{
		m_ShowTitle = enable;
	}

	void Panel::FixPosition(bool enable)
	{
		m_FixedPos = enable;
	}
}
