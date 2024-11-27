#pragma once

#include <list>
#include <string>
#include <memory>

#include "gui_platform.hpp"
#include "gui_theme.hpp"
#include "gui_eventhandler.hpp"
#include "gui_component.hpp"

namespace def::gui
{
	class Panel : public Component
	{
	public:
		Panel();
		Panel(const std::string& title, const Vector2i& pos, const Vector2i& size);
		~Panel();

	public:
		std::string GetTitle() const;
		void SetTitle(const std::string& title);

		bool Update(Platform* platform);
		void Draw(Platform* platform, const Theme& theme) const;

	private:
		std::string m_Title;

		Vector2i m_DragOffset;
		bool m_Drag = false;

	public:
		static constexpr int TITLE_BAR_WIDTH = 20;

	};
}
