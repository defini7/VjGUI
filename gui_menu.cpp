#include "gui_menu.hpp"

namespace def::gui
{
	Menu::Menu(Component* parent) : List(parent, false)
	{
		m_Resizable = false;
	}

	Menu::Menu(Component* parent, const Vector2i& pos, const Vector2i& size)
		: List(parent, pos, size, false)
	{
		m_Resizable = false;
	}

	Menu::~Menu()
	{
	}

	Menu* Menu::AddNode(const std::string& name, const Vector2i& size)
	{
		if (!AddString(name))
			return nullptr;

		Menu* node = new Menu(this, {}, size);
		node->EnableAll(false);
		node->Show(false);
		
		Vector2i offset = { m_Size.x + 2, 0 };
		
		node->SetPosition(m_LocalPosition + offset);

		m_MenuNodes.push_back(node);
		m_MenuNodesIndecies[name] = m_Nodes.size() - 1;

		return node;
	}

	Menu* Menu::GetNode(const std::string& name)
	{
		if (!m_MenuNodesIndecies.contains(name))
			return nullptr;

		return m_MenuNodes[m_MenuNodesIndecies[name]];
	}

	bool Menu::Update(Platform* platform)
	{
		if (!m_Update)
			return false;

		bool light = List::Update(platform);

		return light;
	}

	void Menu::Draw(Platform* platform, const Theme& theme) const
	{
		List::Draw(platform, theme);
	}
}
