#include "../Include/Label.hpp"

#include <iostream>

namespace def::gui
{
	Label::Label(Component* parent) : Component(parent)
	{
	}

	Label::Label(Component* parent, const std::string& text, const Vector2i& pos, const Vector2i& size)
		: Component(parent)
	{
		m_Text = text;

		SetPos(pos);
		SetSize(size);
	}

	Label::~Label()
	{
	}

	const std::string& Label::GetText() const
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
		if (!m_Update)
			return false;

		UpdateText();
		return Component::Update(platform);
	}

	void Label::Draw(Platform* platform, const Theme& theme) const
	{
		if (!m_IsVisible)
			return;

		platform->FillRect(m_GlobalPos, m_Size, theme.componentBackground);
		platform->DrawRect(m_GlobalPos, m_Size, theme.border);

		size_t end = std::min((size_t)m_CharsSize.y, m_TextSplitted.size());

		for (size_t i = 0; i < end; i++)
		{
			auto& unit = m_TextSplitted[i];

			Vector2i pos = m_GlobalPos + unit.offset;
			pos.y += Platform::CHAR_SIZE.y * i;

			platform->DrawText(pos, unit.text, theme.textRegular);
		}

		Component::Draw(platform, theme);
	}

	Vector2i Label::GetSize() const
	{
		return m_CharsSize;
	}

	void Label::SetSize(const Vector2i& size)
	{
		m_CharsSize = size;
		m_Size = { size.x * Platform::CHAR_SIZE.x + 4, size.y * Platform::CHAR_SIZE.y + 2 };
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

	void Label::UpdateTextPos(const std::vector<std::string>& lines)
	{
		m_TextSplitted.clear();
		m_TextSplitted.resize(lines.size());

		for (size_t i = 0; i < lines.size(); i++)
		{
			auto& unit = m_TextSplitted[i];

			unit.text = lines[i];

			int length = unit.text.length();

			switch (m_TextAlign)
			{
			case Align::LEFT:   unit.offset = { 0, 0 };                             break;
			case Align::CENTRE: unit.offset = { m_Size.x / 2 - length * 4 - 2, 0 }; break;
			case Align::RIGHT:  unit.offset = { m_Size.x - length * 8 - 2, 0 };     break;
			}

			unit.offset += 2;
		}
	}

	void Label::SplitTextIntoLines(std::vector<std::string>& lines)
	{
		if (m_Text.empty())
			return;

		if (m_Text.find('\n') == std::string::npos)
			lines.push_back(m_Text);
		else
		{
			std::string buffer;

			for (auto c : m_Text)
			{
				if (c == '\n')
				{
					lines.push_back(buffer);
					buffer.clear();
				}
				else
					buffer += c;
			}

			lines.push_back(buffer);
		}
	}

	void Label::UpdateText()
	{
		if (m_ForceUpdateOffset)
		{
			std::vector<std::string> lines;

			SplitTextIntoLines(lines);
			UpdateTextPos(lines);

			m_ForceUpdateOffset = false;
		}
	}
}
