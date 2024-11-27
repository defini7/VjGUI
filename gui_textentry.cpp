#include "gui_textentry.hpp"

namespace def::gui
{
	TextEntry::TextEntry(Panel* parent)
		: Label(parent), m_CursorPos(0), m_Ticks(0.0f)
	{
	}

	TextEntry::TextEntry(Panel* parent, const Vector2i& pos, const Vector2i& size, const std::string& text, const std::string& placeholder)
		: Label(parent, text, pos, size), m_Placeholder(placeholder), m_CursorPos(0), m_Ticks(0.0f)
	{
	}

	TextEntry::~TextEntry()
	{
	}

	void TextEntry::SetPlaceholder(const std::string& placeholder)
	{
		m_Placeholder = placeholder;
	}

	std::string TextEntry::GetPlaceholder() const
	{
		return m_Placeholder;
	}

	bool TextEntry::Update(Platform* platform)
	{
		if (m_IsFocused)
		{
			using KeyType = HardwareButton::KeyType;

			bool isUp = platform->GetKey(KeyType::LEFT_SHIFT).held || platform->GetKey(KeyType::RIGHT_SHIFT).held || platform->IsCaps();

			if (m_Text.size() < m_CharsSize.x)
			{
				for (const auto& [key, chars] : s_PickedKeyboard)
					if (platform->GetKey(key).pressed)
					{
						m_Text.insert(m_CursorPos, 1, (platform->IsCaps() || isUp) ? chars.second : chars.first);
						m_CursorPos++;
					}
			}

			if (platform->GetKey(KeyType::BACKSPACE).pressed)
			{
				if (m_CursorPos > 0)
				{
					m_Text.erase(m_CursorPos - 1, 1);
					m_CursorPos--;
				}
			}

			if (platform->GetKey(KeyType::DEL).pressed)
			{
				if (m_CursorPos < m_Text.length())
					m_Text.erase(m_CursorPos, 1);
			}

			if (platform->GetKey(KeyType::LEFT).pressed)
			{
				if (m_CursorPos > 0)
					m_CursorPos--;
			}

			if (platform->GetKey(KeyType::RIGHT).pressed)
			{
				if (m_CursorPos < m_Text.length())
					m_CursorPos++;
			}

			if (platform->GetKey(KeyType::ENTER).pressed)
				HandleEvent(this, { Event::Type::Component_Confirm });

			SetText(m_Text);
			UpdateText();

			if (m_Ticks < 2.0f * CURSOR_HIDE_DELAY)
				m_Ticks += platform->GetDeltaTime();
			else if (m_Ticks >= 2.0f * CURSOR_HIDE_DELAY)
				m_Ticks = 0.0f;
		}

		return Component::Update(platform);
	}

	void TextEntry::Draw(Platform* platform, const Theme& theme) const
	{
		if (m_EnableLight)
		{
			platform->FillRect(m_GlobalPosition, m_Size, theme.ApplyLight(theme.componentBackground));
			platform->DrawRect(m_GlobalPosition, m_Size, theme.ApplyLight(theme.border));
		}
		else
		{
			platform->FillRect(m_GlobalPosition, m_Size, theme.componentBackground);
			platform->DrawRect(m_GlobalPosition, m_Size, theme.border);
		}

		if (m_TextSplitted.empty())
		{
			Vector2i pos = m_GlobalPosition + 2;

			if (m_EnableLight)
				platform->DrawText(pos, m_Placeholder, theme.ApplyLight(theme.placeholder));
			else
				platform->DrawText(pos, m_Placeholder, theme.placeholder);
		}
		else
		{
			for (size_t i = 0; i < m_TextSplitted.size(); i++)
			{
				auto& unit = m_TextSplitted[i];

				Vector2i pos = m_GlobalPosition + unit.offset;
				pos.y += Platform::CHAR_SIZE.y * i;

				if (m_EnableLight)
					platform->DrawText(pos, unit.text, theme.ApplyLight(theme.textRegular));
				else
					platform->DrawText(pos, unit.text, theme.textRegular);
			}
		}

		if (m_IsFocused && m_Ticks >= CURSOR_HIDE_DELAY)
		{
			Vector2i cursor = { m_GlobalPosition.x + m_CursorPos * Platform::CHAR_SIZE.x + 2, m_GlobalPosition.y + 1 };

			platform->DrawLine(cursor, { cursor.x, cursor.y + Platform::CHAR_SIZE.y }, theme.cursor);
		}

		Component::Draw(platform, theme);
	}

	void TextEntry::SetCursorPos(uint32_t pos)
	{
		m_CursorPos = pos;
	}

	uint32_t TextEntry::GetCursorPos() const
	{
		return m_CursorPos;
	}
	
	std::unordered_map<TextEntry::KeyType, std::pair<char, char>> TextEntry::s_KeyboardUS =
	{
		{ KeyType::SPACE, { ' ', ' ' } }, { KeyType::APOSTROPHE, { '\'', '"' } },
		{ KeyType::COMMA, { ',', '<' } }, { KeyType::MINUS, { '-', '_' } },
		{ KeyType::PERIOD, { '.', '>' } }, { KeyType::SLASH, { '/', '?' } },
		{ KeyType::K0, { '0', ')' } }, { KeyType::K1, { '1', '!' } },
		{ KeyType::K2, { '2', '@' } }, { KeyType::K3, { '3', '#' } },
		{ KeyType::K4, { '4', '$' } }, { KeyType::K5, { '5', '%' } },
		{ KeyType::K6, { '6', '^' } }, { KeyType::K7, { '7', '&' } },
		{ KeyType::K8, { '8', '*' } }, { KeyType::K9, { '9', '(' } },
		{ KeyType::SEMICOLON, { ';', ':' } }, { KeyType::EQUAL, { '=', '+' } },
		{ KeyType::A, { 'a', 'A' } }, { KeyType::B, { 'b', 'B' } },
		{ KeyType::C, { 'c', 'C' } }, { KeyType::D, { 'd', 'D' } },
		{ KeyType::E, { 'e', 'E' } }, { KeyType::F, { 'f', 'F' } },
		{ KeyType::G, { 'g', 'G' } }, { KeyType::H, { 'h', 'H' } },
		{ KeyType::I, { 'i', 'I' } }, { KeyType::J, { 'j', 'J' } },
		{ KeyType::K, { 'k', 'K' } }, { KeyType::L, { 'l', 'L' } },
		{ KeyType::M, { 'm', 'M' } }, { KeyType::N, { 'n', 'N' } },
		{ KeyType::O, { 'o', 'O' } }, { KeyType::P, { 'p', 'P' } },
		{ KeyType::Q, { 'q', 'Q' } }, { KeyType::R, { 'r', 'R' } },
		{ KeyType::S, { 's', 'S' } }, { KeyType::T, { 't', 'T' } },
		{ KeyType::U, { 'u', 'U' } }, { KeyType::V, { 'v', 'V' } },
		{ KeyType::W, { 'w', 'W' } }, { KeyType::X, { 'x', 'X' } },
		{ KeyType::Y, { 'y', 'Y' } }, { KeyType::Z, { 'z', 'Z' } },
		{ KeyType::LEFT_BRACKET, { '[', '{' } }, { KeyType::BACKSLASH, { '\\', '|' } },
		{ KeyType::RIGHT_BRACKET, { ']', '}' } },
		{ KeyType::NP_0, { '0', '0' } }, { KeyType::NP_1, { '1', '1' } },
		{ KeyType::NP_2, { '2', '2' } }, { KeyType::NP_3, { '3', '3' } },
		{ KeyType::NP_4, { '4', '4' } }, { KeyType::NP_5, { '5', '5' } },
		{ KeyType::NP_6, { '6', '6' } }, { KeyType::NP_7, { '7', '7' } },
		{ KeyType::NP_8, { '8', '8' } }, { KeyType::NP_9, { '9', '9' } },
		{ KeyType::NP_DIVIDE, { '/', '/' } }, { KeyType::NP_MULTIPLY, { '*', '*' } },
		{ KeyType::NP_SUBTRACT, { '-', '-' } }, { KeyType::NP_ADD, { '+', '+' } },
		{ KeyType::NP_EQUAL, { '=', '+' } }
	};

	std::unordered_map<TextEntry::KeyType, std::pair<char, char>>& TextEntry::s_PickedKeyboard = TextEntry::s_KeyboardUS;
}
