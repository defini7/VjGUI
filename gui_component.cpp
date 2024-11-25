#include "gui_component.hpp"
#include "gui_panel.hpp"

namespace def::gui
{
	Component::Component(Component* parent)
		: m_EnableLight(false), m_IsFocused(false), m_Parent(parent), m_IsVisible(true), m_Align(Align::LEFT)
	{
		if (parent)
			parent->AddComponent(this);
	}

	Component::Component(Component* parent, const Vector2i& pos, const Vector2i& size)
		: m_EnableLight(false), m_IsFocused(false), m_Size(size), m_Parent(parent), m_IsVisible(true)
	{
		if (parent)
			parent->AddComponent(this);

		SetPosition(pos);
	}

	Component::~Component()
	{

	}

	Vector2i Component::LocalToGlobalPosition(Component* parent, const Vector2i& pos)
	{
		Vector2i output = pos;

		if (parent)
			output += parent->m_GlobalPosition;
		else
		{
			// TODO: Make title bar size as constant
			output += Vector2i(1, 20);
		}

		return output;
	}

	bool Component::Update(Platform* platform)
	{
		Vector2i mousePos = platform->GetMousePosition();
		HardwareButton mouse_leftButtonState = platform->GetMouseButton(HardwareButton::ButtonType::LEFT);

		bool light = false;

		if (IsPointInRect(mousePos, m_GlobalPosition, m_Size))
		{
			HandleEvent(this, { Event::Type::Mouse_Hover });

			if (mouse_leftButtonState.pressed)
			{
				m_IsFocused = true;
				HandleEvent(this, { Event::Type::Component_Focused });
			}

			light = true;
		}
		else
		{
			if (mouse_leftButtonState.pressed && m_IsFocused)
			{
				m_IsFocused = false;
				HandleEvent(this, { Event::Type::Component_Unfocused });
			}
		}

		for (auto& component : m_Children)
		{
			if (component->m_IsVisible)
			{
				component->UpdatePosition();
				component->m_EnableLight = component->Update(platform);
			}
		}

		return light;
	}

	void Component::Draw(Platform* platform, const Theme& theme) const
	{
		for (auto& component : m_Children)
		{
			if (component->m_IsVisible)
				component->Draw(platform, theme);
		}
	}

	Vector2i Component::GetPosition() const
	{
		return m_LocalPosition;
	}

	void Component::SetPosition(const Vector2i& pos)
	{
		m_GlobalPosition = LocalToGlobalPosition(m_Parent, pos);
		m_LocalPosition = pos;
	}

	Vector2i Component::GetSize() const
	{
		return m_Size;
	}

	void Component::SetSize(const Vector2i& size)
	{
		m_Size = size;
	}

	void Component::UpdatePosition()
	{
		// TODO: Make the title bar size as const
		m_GlobalPosition = Vector2i(1, 20) + m_LocalPosition;

		if (m_Parent)
			m_GlobalPosition += m_Parent->m_GlobalPosition;
	}

	void Component::SetParent(Component* parent)
	{
		m_Parent = parent;
	}

	Align Component::GetAlign() const
	{
		return m_Align;
	}

	void Component::SetAlign(Align align)
	{
		m_Align = align;
	}

	void Component::EnableLight(bool enable)
	{
		m_EnableLight = enable;
	}

	void Component::Show(bool enable)
	{
		m_IsVisible = enable;
	}

	bool Component::IsVisible() const
	{
		return m_IsVisible;
	}

	std::list<Component*>& Component::GetChildren()
	{
		return m_Children;
	}

	Component* Component::GetParent() const
	{
		return m_Parent;
	}
}
