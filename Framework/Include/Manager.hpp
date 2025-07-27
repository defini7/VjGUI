#ifndef DEF_GUI_MANAGER_HPP
#define DEF_GUI_MANAGER_HPP

#include <list>

#include "Panel.hpp"
#include "Platform.hpp"
#include "Theme.hpp"
#include "Component.hpp"

namespace def::gui
{
//! START DECLARATION
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
//! END DECLARATION
}

#endif
