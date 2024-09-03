#include "gui_manager.hpp"

namespace def::gui
{
	Manager::Manager()
	{
		m_Platform = nullptr;
	}

	Manager::Manager(Platform* platform) : m_Platform(platform)
	{
	}

	Manager::~Manager()
	{

	}

	void Manager::Update()
	{
		for (auto& panel : m_Panels)
			panel.Update(m_Platform);
	}

	void Manager::Draw(const Theme& theme)
	{
		for (auto& panel : m_Panels)
			panel.Draw(m_Platform, theme);
	}

	Panel* Manager::AddPanel(const std::string& title, const Vector2i& pos, const Vector2i& size)
	{
		m_Panels.push_back(Panel(title, pos, size));
		return &m_Panels.back();
	}

	void Manager::SetPlatform(Platform* platform)
	{
		m_Platform = platform;
	}
}
