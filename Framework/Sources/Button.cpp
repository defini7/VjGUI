#include "../Include/Button.hpp"

namespace def::gui
{
	Button::Button(Component* parent) : Label(parent)
	{
	}

	Button::Button(Component* parent, const std::string& text, const Vector2i& pos, const Vector2i& size)
		: Label(parent, text, pos, size)
	{
	}

	Button::~Button()
	{
	}

	bool Button::Update(Platform* platform)
	{
		return Label::Update(platform);
	}

	void Button::Draw(Platform* platform, const Theme& theme) const
	{
		if (!m_IsVisible)
			return;

		if (m_EnableLight)
		{
			platform->FillRect(m_GlobalPos, m_Size, theme.ApplyLight(theme.componentBackground));
			platform->DrawRect(m_GlobalPos, m_Size, theme.ApplyLight(theme.border));
		}
		else
		{
			platform->FillRect(m_GlobalPos, m_Size, theme.componentBackground);
			platform->DrawRect(m_GlobalPos, m_Size, theme.border);
		}

		for (size_t i = 0; i < m_TextSplitted.size(); i++)
		{
			auto& unit = m_TextSplitted[i];

			Vector2i pos = m_GlobalPos + unit.offset;
			pos.y += Platform::CHAR_SIZE.y * i;

			if (m_EnableLight)
				platform->DrawText(pos, unit.text, theme.ApplyLight(theme.textRegular));
			else
				platform->DrawText(pos, unit.text, theme.textRegular);
		}

		Component::Draw(platform, theme);
	}
}
