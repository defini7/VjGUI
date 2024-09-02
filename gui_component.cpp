#include "gui_component.hpp"
#include "gui_panel.hpp"

namespace def::gui
{
	Component::Component(Panel* parent) : m_EnableLight(false)
	{
		if (parent)
			parent->AddComponent(this);
	}

	Component::Component(Panel* parent, const Vector2i& pos) : m_EnableLight(false)
	{
		if (parent)
			parent->AddComponent(this);

		SetPosition(pos);
	}

	Component::~Component()
	{

	}

	void Component::Update(Platform* platform)
	{

	}

	void Component::Draw(Platform* platform, const Theme& theme) const
	{

	}

	Vector2i Component::GetPosition() const
	{
		return m_LocalPosition;
	}

	void Component::SetPosition(const Vector2i& pos)
	{
		m_LocalPosition = pos;

		// TODO: Make title bar size as constant
		m_GlobalPosition = m_Parent->GetPosition() + Vector2i(1, 20) + pos;
	}

	void Component::UpdatePosition()
	{
		m_GlobalPosition = m_Parent->GetPosition() + Vector2i(1, 20) + m_LocalPosition;
	}

	void Component::SetParent(Panel* parent)
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

	Panel* Component::GetParent() const
	{
		return m_Parent;
	}
}
