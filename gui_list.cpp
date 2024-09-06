#include "gui_list.hpp"

namespace def::gui
{
	List::List(Panel* parent) : Label(parent)
	{
	}

	List::List(Panel* parent, const Vector2i& pos, const Vector2i& size)
		: Label(parent, "", pos, size)
	{
	}

	List::~List()
	{
	}

	void List::AddString(const std::string& data)
	{
		m_ForceUpdateOffset = true;
		m_Items.push_back(data);
	}

	bool List::Update(Platform* platform)
	{
		if (m_ForceUpdateOffset)
		{
			UpdateTextPosition(m_Items);

			m_ForceUpdateOffset = false;
		}

		return Label::Update(platform);
	}

	void List::Draw(Platform* platform, const Theme& theme) const
	{
		Label::Draw(platform, theme);
	}
}
