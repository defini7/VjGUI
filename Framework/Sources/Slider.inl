#include "../Include/Slider.hpp"

namespace def::gui
{
	template <class T>
	Slider<T>::Slider(Component* parent, const Vector2i& start, const Vector2i& end, const Vector2i& size, const T& min_value, const T& max_value, const T& value)
		: Component(parent), m_MinValue(min_value), m_MaxValue(max_value), m_Value(value), m_LocalEndPos(end), m_Held(false)
	{
		m_Size = size;
		SetPos(start);

		m_GlobalEndPos = LocalToGlobalPos(parent, end);
		UpdateSliderPos();
	}

	template <class T>
	bool Slider<T>::Update(Platform* platform)
	{
		Vector2i mousePos = platform->GetMousePos();
		HardwareButton mouse_leftButtonState = platform->GetMouseButton(HardwareButton::ButtonType::LEFT);

		bool light = false;

		if (IsPointInRect(mousePos, m_SliderPos, m_Size))
		{
			HandleEvent(this, { Event::Mouse_Hover });

			if (mouse_leftButtonState.pressed)
			{
				m_IsFocused = true;
				HandleEvent(this, { Event::Component_Focus });
			}

			light = true;
		}
		else
		{
			if (mouse_leftButtonState.pressed && m_IsFocused)
			{
				m_IsFocused = false;
				HandleEvent(this, { Event::Component_Unfocus });
			}
		}

		if (m_IsFocused)
		{
			if (mouse_leftButtonState.held)
			{
				Vector2d diff = m_LocalEndPos - m_LocalPos;
				double t = diff.DotProduct(mousePos - m_GlobalPos) / double(diff.Length2());

				m_Value = t * double(m_MaxValue - m_MinValue) + m_MinValue;

				if (m_Value < m_MinValue) m_Value = m_MinValue;
				if (m_Value > m_MaxValue) m_Value = m_MaxValue;
			}
		}

		return light;
	}

	template <class T>
	void Slider<T>::Draw(Platform* platform, const Theme& theme) const
	{
		if (!m_IsVisible)
			return;

		platform->DrawLine(m_GlobalPos, m_GlobalEndPos, theme.slider);

		platform->FillRect(m_SliderPos, m_Size, theme.componentBackground);
		platform->DrawRect(m_SliderPos, m_Size, theme.border);

		Component::Draw(platform, theme);
	}

	template <class T>
	T Slider<T>::GetValue() const { return m_Value; }

	template <class T>
	T Slider<T>::GetMaxValue() const { return m_MaxValue; }

	template <class T>
	T Slider<T>::GetMinValue() const { return m_MinValue; }

	template <class T>
	void Slider<T>::SetValue(const T& value) { m_Value = value; }
	
	template <class T>
	void Slider<T>::SetMaxValue(const T& value) { m_MaxValue = value; }
	
	template <class T>
	void Slider<T>::SetMinValue(const T& value) { m_MinValue = value; }

	template <class T>
	void Slider<T>::UpdateSliderPos()
	{
		const Vector2i offset =
			(m_LocalEndPos - m_LocalPos) * (m_Value - m_MinValue) / (m_MaxValue - m_MinValue);

		m_SliderPos = LocalToGlobalPos(m_Parent, m_LocalPos - m_Size / 2 + offset);
	}

	template <class T>
	void Slider<T>::UpdatePos()
	{
		Component::UpdatePos();

		m_GlobalPos = LocalToGlobalPos(m_Parent, m_LocalPos);
		m_GlobalEndPos = LocalToGlobalPos(m_Parent, m_LocalEndPos);

		UpdateSliderPos();
	}
}
