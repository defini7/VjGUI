#include "gui_list.hpp"

namespace def::gui
{
	ListNode::ListNode(Component* parent) : Label(parent)
	{
		Initialise();
	}

	ListNode::ListNode(Component* parent, int width, int index, const std::string& text)
		: Label(parent, text, {}, { width, 1 })
	{
		m_Index = index;
		Initialise();
	}

	bool ListNode::Update(Platform* platform)
	{
		return Label::Update(platform);
	}

	void ListNode::Draw(Platform* platform, const Theme& theme) const
	{
		if (!m_IsVisible)
			return;

		auto& unit = m_TextSplitted[0];

		Vector2i pos = m_GlobalPosition + unit.offset;
		pos.y += Platform::CHAR_SIZE.y * (m_Index - m_Offset);

		platform->DrawText(pos, unit.text, theme.textRegular);

		Component::Draw(platform, theme);
	}

	void ListNode::SetIndex(int index)
	{
		m_Index = index;
	}

	int ListNode::GetIndex() const
	{
		return m_Index;
	}

	void ListNode::UpdatePosition()
	{
		m_GlobalPosition = m_LocalPosition;
		m_GlobalPosition.x++;

		if (m_Parent)
			m_GlobalPosition += m_Parent->GetGlobalPosition();
	}

	void ListNode::SetOffset(int offset)
	{
		m_Offset = offset;
	}

	void ListNode::Initialise()
	{
		m_ForceUpdateOffset = true;
	}

	List::List(Component* parent, bool constructSlider) : Panel(parent)
	{
		Initialise(constructSlider);
	}

	List::List(Component* parent, const Vector2i& pos, const Vector2i& size, bool constructSlider)
		: Panel(parent, "", pos, {})
	{
		Initialise(constructSlider, size);
	}

	List::~List()
	{
	}

	void List::Initialise(bool constructSlider, const Vector2i& size)
	{
		ShowTitleBar(false);
		FixPosition(true);
		SetSize(size);

		if (constructSlider)
			ConstructSlider();
	}

	bool List::AddString(const std::string& data)
	{
		bool isOverflow = m_Nodes.size() + 1 > m_SizeInNodes.y;

		if (isOverflow)
			return false;

		m_Nodes.push_back(new ListNode(this, m_SizeInNodes.x, m_Nodes.size(), data));

		if (m_Slider && m_Resizable)
		{
			if (isOverflow)
				m_Slider->SetMaxValue(m_Nodes.size() - 1);

			m_Slider->Show(isOverflow);
		}

		return true;
	}

	bool List::Update(Platform* platform)
	{
		if (!m_Update)
			return false;

		UpdateText();

		Vector2i itemSize = { m_Size.x, Platform::CHAR_SIZE.y };

		Vector2i mousePos = platform->GetMousePosition();
		HardwareButton mouseLeft = platform->GetMouseButton(HardwareButton::ButtonType::LEFT);

		for (int i = 0; i < m_Nodes.size(); i++)
		{
			if (mouseLeft.pressed)
			{
				Vector2i pos = m_Nodes[i]->GetPosition();
				pos.y += i * Platform::CHAR_SIZE.y;

				if (IsPointInRect(mousePos, m_GlobalPosition + pos, itemSize))
				{
					m_SelectedItem = m_Nodes.begin() + i;
					HandleEvent(this, Event::Component_Select);
					break;
				}
			}
		}
		
		return Panel::Update(platform);
	}

	void List::Draw(Platform* platform, const Theme& theme) const
	{
		Panel::Draw(platform, theme);
	}

	void List::EnableResize(bool enable)
	{
		m_Resizable = enable;

		if (m_Slider)
		{
			m_Slider->Show(enable);
			m_Slider->EnableUpdate(enable);
		}
	}

	void List::SetSize(const Vector2i& size)
	{
		m_Size = { size.x * Platform::CHAR_SIZE.x + 4, size.y * Platform::CHAR_SIZE.y + 2 };
		m_SizeInNodes = size;
	}

	void List::ConstructSlider()
	{
		int width = (float)m_Size.x * 0.05f;
		int x = m_Size.x - width;

		m_Slider = new Slider<int>(this, { x, 1 + width / 2 }, { x, m_Size.y - width / 2 - 1 }, { width, width }, 0, m_SizeInNodes.y);
		m_Slider->Show(false);
	}

	void List::UpdateText()
	{
		if (m_Slider)
		{
			int offset = m_Slider->GetValue();
			
			for (auto node : m_Nodes)
			{
				int pos = node->GetIndex() - offset;

				node->SetOffset(offset);
				node->Show(pos >= 0 && pos < m_SizeInNodes.y);
			}
		}
	}
}
