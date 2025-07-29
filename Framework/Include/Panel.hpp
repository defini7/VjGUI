#ifndef DEF_GUI_PANEL_HPP
#define DEF_GUI_PANEL_HPP

#include <list>
#include <string>
#include <memory>

#include "Platform.hpp"
#include "Theme.hpp"
#include "EventHandler.hpp"
#include "Component.hpp"

namespace def::gui
{
//! START DECLARATION
	class Panel : public Component
	{
	public:
		Panel(Component* parent = nullptr);
		Panel(Component* parent, const std::string& title, const Vector2i& pos, const Vector2i& size);
		~Panel();

	public:
		const std::string& GetTitle() const;
		void SetTitle(const std::string& title);

		bool Update(Platform* platform);
		void Draw(Platform* platform, const Theme& theme) const;

		void ShowTitleBar(bool enable);
		void ShowTitle(bool enable);

		void FixPos(bool enable);

	private:
		std::string m_Title;

		Vector2i m_DragOffset;
		bool m_Drag = false;

		bool m_FixedPos = false;

		bool m_ShowTitleBar = true;
		bool m_ShowTitle = true;

	public:
		static constexpr int TITLE_BAR_WIDTH = 20;

	};
//! END DECLARATION
}

#endif
