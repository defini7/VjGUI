#pragma once

#include "gui_utils.hpp"
#include "gui_platform.hpp"
#include "gui_theme.hpp"
#include "gui_eventhandler.hpp"

namespace def::gui
{
	class Component : public EventHandler<Component>
	{
	public:
		Component(Component* parent = nullptr);
		Component(Component* parent, const Vector2i& pos, const Vector2i& size);
		virtual ~Component();

	public:
		virtual bool Update(Platform* platform);
		virtual void Draw(Platform* platform, const Theme& theme) const;

		Vector2i GetPosition() const;
		void SetPosition(const Vector2i& pos);

		Vector2i GetSize() const;
		void SetSize(const Vector2i& size);

		void UpdatePosition();

		Component* GetParent() const;
		void SetParent(Component* parent);

		Align GetAlign() const;
		void SetAlign(Align align);

		void EnableLight(bool enable);

		template <class T>
		T* AddComponent(T* component)
		{
			component->SetParent(this);
			m_Children.push_back(component);

			return component;
		}

		std::list<Component*>& GetChildren();

	protected:
		// Relative to the panel
		Vector2i m_LocalPosition;

		// Relative to the screen
		Vector2i m_GlobalPosition;

		Vector2i m_Size;

		Component* m_Parent;
		std::list<Component*> m_Children;

		Align m_Align;

		bool m_EnableLight;
		bool m_IsFocused;

	};
}
