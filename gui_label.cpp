#include "gui_label.hpp"

#include <iostream>

namespace def::gui
{
	Label::Label(Panel* parent) : Component(parent)
	{
		SetTextAlign(Align::LEFT);
	}

	Label::Label(Panel* parent, const std::string& text, const Vector2i& pos, const Vector2i& size)
		: Component(parent, pos)
	{
		m_Text = text;
		SetTextAlign(Align::LEFT);
		SetSize(size);
	}

	Label::~Label()
	{
	}

	std::string Label::GetText() const
	{
		return m_Text;
	}

	void Label::SetText(const std::string& text)
	{
		m_Text = text;
		SetTextAlign(m_Align);
	}

	bool Label::Update(Platform* platform)
	{
		UpdateText();

		Vector2i mousePos = platform->GetMousePosition();
		HardwareButton mouse_leftButtonState = platform->GetMouseButton(HardwareButton::ButtonType::LEFT);

		if (IsPointInRect(mousePos, m_GlobalPosition, m_PhysicalSize))
		{
			HandleEvent(this, { Event::Type::Mouse_Hover });

			if (mouse_leftButtonState.pressed)
			{
				m_IsFocused = true;
				HandleEvent(this, { Event::Type::Component_Focused });
			}

			return true;
		}
		else
		{
			if (mouse_leftButtonState.pressed && m_IsFocused)
			{
				m_IsFocused = false;
				HandleEvent(this, { Event::Type::Component_Unfocused });
			}
		}
		
		return false;
	}

	void Label::Draw(Platform* platform, const Theme& theme) const
	{
		platform->FillRect(m_GlobalPosition, m_PhysicalSize, theme.componentBackground);
		platform->DrawRect(m_GlobalPosition, m_PhysicalSize, theme.border);

		size_t end = std::min((size_t)m_CharsSize.y, m_TextSplitted.size());

		for (size_t i = 0; i < end; i++)
		{
			auto& unit = m_TextSplitted[i];

			Vector2i pos = m_GlobalPosition + unit.offset;
			pos.y += 8 * i;

			platform->DrawText(pos, unit.text, theme.text);
		}
	}

	Vector2i Label::GetSize() const
	{
		return m_CharsSize;
	}

	void Label::SetSize(const Vector2i& size)
	{
		m_CharsSize = size;
		m_PhysicalSize = { size.x * 8 + 4, size.y * 8 + 2 };
	}

	Align Label::GetTextAlign() const
	{
		return m_TextAlign;
	}

	void Label::SetTextAlign(Align align)
	{
		m_TextAlign = align;
		m_ForceUpdateOffset = true;
	}

	void Label::UpdateTextPosition(const std::vector<std::string>& lines)
	{
		m_TextSplitted.clear();
		m_TextSplitted.resize(lines.size());

		for (size_t i = 0; i < lines.size(); i++)
		{
			auto& unit = m_TextSplitted[i];
			unit.text = lines[i];

			int length = lines[i].length();

			switch (m_TextAlign)
			{
			case Align::LEFT: unit.offset = { 0, 0 }; break;
			case Align::CENTRE: unit.offset = { m_PhysicalSize.x / 2 - length * 4 - 2, 0 }; break;
			case Align::RIGHT: unit.offset = { m_PhysicalSize.x - length * 8 - 2, 0 }; break;
			}

			unit.offset += 2;
		}
	}

	void Label::SplitTextIntoLines(std::vector<std::string>& lines)
	{
		if (m_Text.find('\n') == std::string::npos)
		{
			if (!m_Text.empty())
				lines.push_back(m_Text);
		}
		else
		{
			std::string buffer;

			for (auto c : m_Text)
			{
				if (c == '\n')
				{
					lines.push_back(buffer);

					if (lines.size() == m_CharsSize.y)
						return;

					buffer.clear();
				}
				else
					buffer += c;
			}

			if (!buffer.empty())
				lines.push_back(buffer);
		}
	}

	void Label::UpdateText()
	{
		if (m_ForceUpdateOffset)
		{
			std::vector<std::string> lines;

			SplitTextIntoLines(lines);
			UpdateTextPosition(lines);

			m_ForceUpdateOffset = false;
		}
	}
}
