#pragma once

#include "gui_component.hpp"
#include "gui_panel.hpp"

namespace def::gui
{
	template <class T>
	class Slider : public Component
	{
	public:
		Slider(Component* parent, const Vector2i& start, const Vector2i& end, const Vector2i& size, const T& min_value, const T& max_value, const T& value = 0.0f)
			: Component(parent), m_MinValue(min_value), m_MaxValue(max_value), m_Value(value), m_LocalEndPosition(end), m_Held(false)
		{
			SetSize(size);
			SetPosition(start);

			m_GlobalEndPosition = LocalToGlobalPosition(parent, end);
			m_SliderPosition = m_GlobalPosition - m_Size / 2;
		}
		
		~Slider() = default;

	public:
		bool Update(Platform* platform) override
		{
			m_GlobalEndPosition = LocalToGlobalPosition(m_Parent, m_LocalEndPosition);

			Vector2i mousePos = platform->GetMousePosition();
			HardwareButton mouse_leftButtonState = platform->GetMouseButton(HardwareButton::ButtonType::LEFT);

			bool light = false;

			if (IsPointInRect(mousePos, m_SliderPosition, m_Size))
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

			if (m_IsFocused)
			{
				if (mouse_leftButtonState.held)
				{
					Vector2d diff = m_LocalEndPosition - m_LocalPosition;
					double t = diff.dot(mousePos - m_GlobalPosition) / double(diff.mag2());

					m_Value = t * double(m_MaxValue - m_MinValue) + m_MinValue;

					if (m_Value < m_MinValue) m_Value = m_MinValue;
					if (m_Value > m_MaxValue) m_Value = m_MaxValue;

					auto offset = (m_LocalEndPosition - m_LocalPosition) * (m_Value - m_MinValue) / (m_MaxValue - m_MinValue);
					m_SliderPosition = LocalToGlobalPosition(m_Parent, m_LocalPosition - m_Size / 2 + offset);
				}
			}

			return light;
		}

		void Draw(Platform* platform, const Theme& theme) const override
		{
			platform->DrawLine(m_GlobalPosition, m_GlobalEndPosition, theme.slider);

			platform->FillRect(m_SliderPosition, m_Size, theme.componentBackground);
			platform->DrawRect(m_SliderPosition, m_Size, theme.border);
		}

		void SetValue(const T& value)
		{
			m_Value = value;
		}

		T GetValue() const
		{
			return m_Value;
		}

	private:
		Vector2i m_GlobalEndPosition;
		Vector2i m_LocalEndPosition;

		Vector2i m_SliderPosition;

		T m_MaxValue;
		T m_MinValue;

		T m_Value;

		bool m_Held;

	};
}
