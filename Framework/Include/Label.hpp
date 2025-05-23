#ifndef DEF_GUI_LABEL_HPP
#define DEF_GUI_LABEL_HPP

#include <string>
#include <vector>

#include "Component.hpp"
#include "Utils.hpp"
#include "Panel.hpp"
#include "EventHandler.hpp"

namespace def::gui
{
	class Label : public Component
	{
	public:
		Label(Component* parent = nullptr);
		Label(Component* parent, const std::string& text, const Vector2i& pos, const Vector2i& size);
		
		virtual ~Label();

		friend class Button;
		friend class TextEntry;
		friend class List;

	public:
		const std::string& GetText() const;
		void SetText(const std::string& text);

		bool Update(Platform* platform) override;
		void Draw(Platform* platform, const Theme& theme) const override;

		Vector2i GetSize() const;
		void SetSize(const Vector2i& size);

		Align GetTextAlign() const;
		virtual void SetTextAlign(Align align);

	private:
		// For each string in line we calculate it's Pos and push it to the m_TextSplitted
		void UpdateTextPos(const std::vector<std::string>& lines);

		// Split the m_Text by '\n' symbol and push it to lines
		void SplitTextIntoLines(std::vector<std::string>& lines);

		// Perform SplitTextIntoLines and UpdateTextPos if m_ForceUpdateOffset flag was set to true
		void UpdateText();

	protected:
		std::string m_Text;
		Vector2i m_CharsSize;
		Align m_TextAlign = Align::LEFT;

		struct TextUnit
		{
			Vector2i offset;
			std::string text;
		};

		// Contains transformed text after calling UpdateTextPos function
		std::vector<TextUnit> m_TextSplitted;

		bool m_ForceUpdateOffset = true;

	};
}

#endif
