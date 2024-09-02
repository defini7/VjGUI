#pragma once

#include <list>
#include <string>

#include "gui_platform.hpp"
#include "gui_theme.hpp"
#include "gui_eventhandler.hpp"

namespace def::gui
{
	class Component;

	class Panel : public EventHandler<Panel>
	{
	public:
		Panel();
		Panel(const std::string& title, const Vector2i& pos, const Vector2i& size);
		~Panel();

	public:
		std::list<Component*>& GetComponents();

		std::string GetTitle() const;
		void SetTitle(const std::string& title);

		Vector2i GetPosition() const;
		void SetPosition(const Vector2i& pos);

		Vector2i GetSize() const;
		void SetSize(const Vector2i& size);

		template <class T>
		T* AddComponent(T* component)
		{
			component->SetParent(this);
			m_Components.push_back(component);

			return component;
		}

		void Update(Platform* platform);
		void Draw(Platform* platform, const Theme& theme) const;

	private:
		std::list<Component*> m_Components;

		std::string m_Title;
		
		Vector2i m_Position;
		Vector2i m_Size;

		bool m_Drag;

		Vector2i m_DragOffset;

	};
}
