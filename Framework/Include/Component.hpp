#ifndef DEF_GUI_COMPONENT_HPP
#define DEF_GUI_COMPONENT_HPP

#include "Utils.hpp"
#include "Platform.hpp"
#include "Theme.hpp"
#include "Eventhandler.hpp"

namespace def::gui
{
	class Component : public EventHandler<Component>
	{
	public:
		Component(Component* parent = nullptr);
		Component(Component* parent, const Vector2i& pos, const Vector2i& size);

		virtual ~Component();

	public:
		static Vector2i LocalToGlobalPos(Component* parent, const Vector2i& pos);

		// Only if visible flag is set to true: updates hover and focus events, then updates Pos
		// and calls itself on each child component
		virtual bool Update(Platform* platform);

		// Draws children components if visible flag is set to true
		virtual void Draw(Platform* platform, const Theme& theme) const;

		const Vector2i& GetGlobalPos();

		// Returns local Pos
		const Vector2i& GetPos() const;
		void SetPos(const Vector2i& pos);

		const Vector2i& GetSize() const;
		void SetSize(const Vector2i& size);

		// Updates global Pos of the component by applying an offset
		// of the title bar and the offset of the parent
		virtual void UpdatePos();

		Component* GetParent() const;
		void SetParent(Component* parent);

		Align GetAlign() const;
		void SetAlign(Align align);

		void EnableLight(bool enable);
		void EnableUpdate(bool enable);
		void Show(bool enable);
		void EnableAll(bool enable);

		bool IsVisible() const;

		// !!! Add children components using ONLY that method !!!
		template <class T>
		T* AddComponent(T* component)
		{
			component->SetParent(this);
			m_Children.push_back(component);

			return component;
		}

		std::list<Component*>& GetChildren();

	protected:
		Vector2i m_LocalPos; // Relative to the panel
		Vector2i m_GlobalPos; // Relative to the screen
		Vector2i m_Size;

		Component* m_Parent = nullptr;
		std::list<Component*> m_Children;

		Align m_Align = Align::LEFT;

		bool m_EnableLight = false;
		bool m_IsFocused = false;
		bool m_IsVisible = true;
		bool m_Update = true;

	};
}

#endif
