#pragma once

#include "gui_utils.hpp"
#include "gui_platform.hpp"
#include "gui_theme.hpp"
#include "gui_eventhandler.hpp"

namespace def::gui
{
	class Panel;

	class Component : public EventHandler<Component>
	{
	public:
		Component(Panel* parent = nullptr);
		Component(Panel* parent, const Vector2i& pos);
		virtual ~Component();

	public:
		virtual void Update(Platform* platform);
		virtual void Draw(Platform* platform, const Theme& theme) const;

		Vector2i GetPosition() const;
		void SetPosition(const Vector2i& pos);
		void UpdatePosition();

		Panel* GetParent() const;
		void SetParent(Panel* parent);

		Align GetAlign() const;
		void SetAlign(Align align);

	protected:
		// Relative to the panel
		Vector2i m_LocalPosition;

		// Relative to the screen
		Vector2i m_GlobalPosition;

		Panel* m_Parent;

		Align m_Align;

		bool m_EnableLight;

	};
}
