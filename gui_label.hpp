#pragma once

#include <string>
#include <vector>

#include "gui_component.hpp"
#include "gui_utils.hpp"
#include "gui_panel.hpp"
#include "gui_eventhandler.hpp"

namespace def::gui
{
	class Label : public Component
	{
	public:
		Label(Panel* parent = nullptr);
		Label(Panel* parent, const std::string& text, const Vector2i& pos, const Vector2i& size);
		virtual ~Label();

		friend class Button;
		friend class TextEntry;
		friend class List;

	public:
		std::string GetText() const;
		void SetText(const std::string& text);

		bool Update(Platform* platform) override;
		void Draw(Platform* platform, const Theme& theme) const override;

		Vector2i GetSize() const;
		void SetSize(const Vector2i& size);

		Align GetTextAlign() const;
		virtual void SetTextAlign(Align align);

	private:
		// For each string in line we calculate it's position and push it to the m_TextSplitted
		void UpdateTextPosition(const std::vector<std::string>& lines);

		// Split the m_Text by '\n' symbol and push it to lines
		void SplitTextIntoLines(std::vector<std::string>& lines);

		// Perform SplitTextIntoLines and UpdateTextPosition if m_ForceUpdateOffset flag was set to true
		void UpdateText();

	private:
		std::string m_Text;

		Vector2i m_CharsSize;

		Align m_TextAlign;

		struct TextUnit
		{
			Vector2i offset;
			std::string text;
		};

		std::vector<TextUnit> m_TextSplitted;

		bool m_ForceUpdateOffset;

		// Index that we start rendering text from
		size_t m_ViewStart;

	};
}
