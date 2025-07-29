#include "../Include/Component.hpp"
#include "../Include/Panel.hpp"

namespace def::gui
{
//! START IMPLEMENTATION
	Component::Component(Component* parent)
		: m_Parent(parent)
	{
		if (parent)
			parent->AddComponent(this);
	}

	Component::Component(Component* parent, const Vector2i& pos, const Vector2i& size)
		: m_Size(size), m_Parent(parent)
	{
		if (parent)
			parent->AddComponent(this);

		SetPos(pos);
	}

	Component::~Component()
	{
		for (auto child : m_Children)
		{
			if (child)
				delete child;
		}
	}

	Vector2i Component::LocalToGlobalPos(Component* parent, const Vector2i& pos)
	{
		Vector2i output = pos;

		// If there is no parent then we assume that we are on panel
		// so let's take into account the title bar width

		if (parent)
			output += parent->m_GlobalPos;
		else
			output += Vector2i(1, Panel::TITLE_BAR_WIDTH);

		return output;
	}

	bool Component::Update(Platform* platform)
	{
		if (!m_Update)
			return false;

		Vector2i mousePos = platform->GetMousePos();
		HardwareButton mouseLeft = platform->GetMouseButton(HardwareButton::ButtonType::LEFT);

		bool light = false;

		if (IsPointInRect(mousePos, m_GlobalPos, m_Size))
		{
			HandleEvent(this, Event::Mouse_Hover);

			if (mouseLeft.pressed)
			{
				m_IsFocused = true;

				HandleEvent(this, Event::Mouse_Press);
				HandleEvent(this, Event::Component_Focus);
			}

			if (mouseLeft.held)     HandleEvent(this, Event::Mouse_Hold);
			if (mouseLeft.released) HandleEvent(this, Event::Mouse_Release);

			light = true;
		}
		else
		{
			if (mouseLeft.pressed && m_IsFocused)
			{
				m_IsFocused = false;

				HandleEvent(this, Event::Mouse_Press);
				HandleEvent(this, Event::Component_Unfocus);
			}
		}

		for (auto& component : m_Children)
		{
			if (m_IsVisible)
				component->UpdatePos();

			component->m_EnableLight = component->Update(platform);
		}

		return light;
	}

	void Component::Draw(Platform* platform, const Theme& theme) const
	{
		if (!m_IsVisible)
			return;

		for (auto& component : m_Children)
			component->Draw(platform, theme);
	}

	const Vector2i& Component::GetGlobalPos()
	{
		return m_GlobalPos;
	}

	const Vector2i& Component::GetPos() const
	{
		return m_LocalPos;
	}

	void Component::SetPos(const Vector2i& pos)
	{
		m_GlobalPos = LocalToGlobalPos(m_Parent, pos);
		m_LocalPos = pos;
	}

	const Vector2i& Component::GetSize() const
	{
		return m_Size;
	}

	void Component::SetSize(const Vector2i& size)
	{
		m_Size = size;
	}

	void Component::UpdatePos()
	{
		m_GlobalPos = Vector2i(1, Panel::TITLE_BAR_WIDTH) + m_LocalPos;

		if (m_Parent)
			m_GlobalPos += m_Parent->m_GlobalPos;
	}

	void Component::SetParent(Component* parent)
	{
		m_Parent = parent;
	}

	int Component::GetAlign() const
	{
		return m_Align;
	}

	void Component::SetAlign(int align)
	{
		m_Align = align;
	}

	void Component::EnableLight(bool enable)
	{
		m_EnableLight = enable;
	}

	void Component::EnableUpdate(bool enable)
	{
		m_Update = enable;
	}

	void Component::Show(bool enable)
	{
		m_IsVisible = enable;
	}

	void Component::EnableAll(bool enable)
	{
		Show(enable);
		EnableUpdate(enable);
		EnableLight(enable);
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
//! END IMPLEMENTATION
}
