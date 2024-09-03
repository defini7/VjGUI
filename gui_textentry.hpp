#pragma once

#include <unordered_map>

#include "gui_label.hpp"
#include "gui_utils.hpp"

namespace def::gui
{
	class TextEntry : public Label
	{
	public:
		using KeyType = HardwareButton::KeyType;

		TextEntry(Panel* parent = nullptr);
		TextEntry(Panel* parent, const Vector2i& pos, const Vector2i& size, const std::string& text = "", const std::string& placeholder = "");
		virtual ~TextEntry();

	public:
		void SetPlaceholder(const std::string& placeholder);
		std::string GetPlaceholder() const;

		bool Update(Platform* platform) override;
		void Draw(Platform* platform, const Theme& theme) const override;

		void SetCursorPos(uint32_t pos);
		uint32_t GetCursorPos() const;

	public:
		static std::unordered_map<KeyType, std::pair<char, char>>& s_PickedKeyboard;

		// pair<char, char> - main, alternative chars
		static std::unordered_map<KeyType, std::pair<char, char>> s_KeyboardUS;

	private:
		std::string m_Placeholder;

		int m_CursorPos;
		float m_Ticks;

		static constexpr float CURSOR_HIDE_DELAY = 1.0f;

	};
}
