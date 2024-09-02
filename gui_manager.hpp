#pragma once

#include <list>

#include "gui_panel.hpp"
#include "gui_platform.hpp"
#include "gui_theme.hpp"
#include "gui_component.hpp"

namespace def::gui
{
	class Manager
	{
	public:
		Manager();
		Manager(Platform* platform);
		~Manager();

	public:
		void Update();
		void Draw(const Theme& theme);

		Panel* AddPanel(const std::string& title, const Vector2i& pos, const Vector2i& size);

		void SetPlatform(Platform* platform);

	private:
		std::list<Panel> m_Panels;

		Platform* m_Platform;
	};
}
