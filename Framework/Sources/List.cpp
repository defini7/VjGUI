#include "../Include/List.hpp"

namespace def::gui
{
//! START IMPLEMENTATION
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
		if (!m_TextSplitted.empty())
		{
			auto& unit = m_TextSplitted[0];

			m_GlobalPos.y += Platform::CHAR_SIZE.y * (m_Index - m_Offset) + unit.offset.y;
			m_GlobalPos.x += unit.offset.x;
		}

		return Label::Update(platform);
	}

	void ListNode::Draw(Platform* platform, const Theme& theme) const
	{
		if (!m_IsVisible)
			return;

		if (!m_TextSplitted.empty())
		{
			auto& unit = m_TextSplitted[0];

			if (m_EnableLight)
			{
				int sizeX = m_Size.x - 6;
				platform->FillRect(m_GlobalPos, { sizeX, m_Size.y }, theme.ApplyLight(theme.componentBackground));
			}

			platform->DrawText(m_GlobalPos, unit.text, theme.textRegular);
		}

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

	void ListNode::UpdatePos()
	{
		m_GlobalPos = m_LocalPos;
		m_GlobalPos.x++;

		if (m_Parent)
			m_GlobalPos += m_Parent->GetGlobalPos();
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
		FixPos(true);
		SetSize(size);

		if (constructSlider)
			ConstructSlider();
	}

	void List::AddString(const std::string& data)
	{
		m_Nodes.push_back(new ListNode(this, m_SizeInNodes.x, m_Nodes.size(), data));

		if (m_Slider && m_Resizable)
		{
			bool isOverflow = m_Nodes.size() + 1 > m_SizeInNodes.y;

			if (isOverflow)
				m_Slider->SetMaxValue(m_Nodes.size() - 1);

			m_Slider->Show(isOverflow);
		}
	}

	bool List::Update(Platform* platform)
	{
		if (!m_Update)
			return false;

		UpdateText();

		Vector2i itemSize = { m_Size.x, Platform::CHAR_SIZE.y };

		Vector2i mousePos = platform->GetMousePos();
		HardwareButton mouseLeft = platform->GetMouseButton(HardwareButton::ButtonType::LEFT);

		for (size_t i = 0; i < m_Nodes.size(); i++)
		{
			if (mouseLeft.released)
			{
				Vector2i pos = m_Nodes[i]->GetPos();
				pos.y += (int)i * Platform::CHAR_SIZE.y;

				if (IsPointInRect(mousePos, m_GlobalPos + pos, itemSize))
				{
					m_SelectedItem = i;

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

	ListNode* List::GetSelected()
	{
		return m_Nodes[m_SelectedItem];
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

	void List::Clear()
	{
		m_Nodes.clear();

		m_Slider->Show(false);
		m_Slider->SetMaxValue(1);

		m_Children.erase(std::next(m_Children.begin()), m_Children.end());
	}
//! END IMPLEMENTATION
}
