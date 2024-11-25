#include "gui_list.hpp"

namespace def::gui
{
	List::List(Panel* parent) : Label(parent)
	{
		ConstructSlider();
	}

	List::List(Panel* parent, const Vector2i& pos, const Vector2i& size)
		: Label(parent, "", pos, size)
	{
		ConstructSlider();
	}

	List::~List()
	{
		delete m_Slider;
	}

	void List::AddString(const std::string& data)
	{
		m_ForceUpdateOffset = true;
		m_Items.push_back(data);

		bool isOverflow = m_Items.size() > m_CharsSize.y;

		if (isOverflow)
			m_Slider->SetMaxValue(m_Items.size() - 1);

		m_Slider->Show(isOverflow);
	}

	bool List::Update(Platform* platform)
	{
		if (m_ForceUpdateOffset)
		{
			UpdateTextPosition(m_Items);
			m_ForceUpdateOffset = false;
		}

		int start = m_Slider->GetValue();

		if (m_ViewStart != start)
		{
			m_ViewStart = start;
			Label::UpdateTextPosition(m_Items);
		}
		
		return Label::Update(platform);
	}

	void List::Draw(Platform* platform, const Theme& theme) const
	{
		Label::Draw(platform, theme);
		Component::Draw(platform, theme);
	}

	void List::ConstructSlider()
	{
		int width = (float)m_Size.x * 0.05f;
		int x = m_Size.x - width;

		m_Slider = new Slider<int>(this, { x, 1 + width / 2 }, { x, m_Size.y - width / 2 - 1 }, { width, width }, 0, m_Size.y);
		m_Slider->Show(false);
	}
}
