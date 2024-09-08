#include "gui_scrollbar.hpp"

namespace def::gui
{
	ScrollBar::ScrollBar(Component* parent, Align align)
		: Component(parent), m_Value(0.0f)
	{
		m_Align = align;

		ResolveAlign();
	}

	ScrollBar::~ScrollBar()
	{
	}

	bool ScrollBar::Update(Platform* platform)
	{
		

		return false;
	}

	void ScrollBar::Draw(Platform* platform, const Theme& theme) const
	{
	}

	void ScrollBar::SetWidth(uint32_t width)
	{
		m_Width = width;
	}

	void ScrollBar::ResolveAlign()
	{
		Vector2i size = m_Parent->GetSize();

		switch (m_Align)
		{
		case Align::LEFT:
		{
			SetPosition({ 0, 0 });
			m_Size = { (int)m_Width, size.y };
		}
		break;

		case Align::RIGHT:
		{
			SetPosition({ size.x - (int)m_Width, 0 });
			m_Size = { (int)m_Width, size.y };
		}
		break;

		case Align::TOP:
		{
			SetPosition({ 0, 0 });
			m_Size = { size.x, (int)m_Width };
		}
		break;

		case Align::BOTTOM:
		{
			SetPosition({ 0, size.y - (int)m_Width });
			m_Size = { size.x, (int)m_Width };
		}
		break;

		}
	}

	void ScrollBar::SetValue(float value)
	{
		m_Value = value;
	}

	float ScrollBar::GetValue() const
	{
		return m_Value;
	}
}
