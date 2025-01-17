#pragma once

#include "gui_component.hpp"
#include "gui_panel.hpp"
#include "gui_list.hpp"

#include <unordered_map>

namespace def::gui
{
	class Menu : public List
	{
	public:
		Menu(Component* parent = nullptr);
		Menu(Component* parent, const Vector2i& pos, const Vector2i& size);
		virtual ~Menu();

	public:
		Menu* AddNode(const std::string& name, const Vector2i& size = {});
		Menu* GetNode(const std::string& name);

	private:
		bool Update(Platform* platform) override;
		void Draw(Platform* platform, const Theme& theme) const override;

	private:
		// Save pointers to each child node so we have easy access to them
		std::unordered_map<std::string, size_t> m_MenuNodesIndecies;
		std::vector<Menu*> m_MenuNodes;

	};
}
