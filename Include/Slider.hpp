#ifndef DEF_GUI_SLIDER_HPP
#define DEF_GUI_SLIDER_HPP

#include "Component.hpp"
#include "Panel.hpp"

namespace def::gui
{
	template <class T>
	class Slider : public Component
	{
	public:
		Slider(Component* parent, const Vector2i& start, const Vector2i& end, const Vector2i& size, const T& min_value, const T& max_value, const T& value = 0)
			: Component(parent), m_MinValue(min_value), m_MaxValue(max_value), m_Value(value), m_LocalEndPosition(end), m_Held(false)
		{
			m_Size = size;
			SetPosition(start);

			m_GlobalEndPosition = LocalToGlobalPosition(parent, end);
			UpdateSliderPosition();
		}
		
		~Slider() = default;

	public:
		bool Update(Platform* platform) override
		{
			Vector2i mousePos = platform->GetMousePosition();
			HardwareButton mouse_leftButtonState = platform->GetMouseButton(HardwareButton::ButtonType::LEFT);

			bool light = false;

			if (IsPointInRect(mousePos, m_SliderPosition, m_Size))
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
					Vector2d diff = m_LocalEndPosition - m_LocalPosition;
					double t = diff.DotProduct(mousePos - m_GlobalPosition) / double(diff.Length2());

					m_Value = t * double(m_MaxValue - m_MinValue) + m_MinValue;

					if (m_Value < m_MinValue) m_Value = m_MinValue;
					if (m_Value > m_MaxValue) m_Value = m_MaxValue;
				}
			}

			return light;
		}

		void Draw(Platform* platform, const Theme& theme) const override
		{
			if (!m_IsVisible)
				return;

			platform->DrawLine(m_GlobalPosition, m_GlobalEndPosition, theme.slider);

			platform->FillRect(m_SliderPosition, m_Size, theme.componentBackground);
			platform->DrawRect(m_SliderPosition, m_Size, theme.border);

			Component::Draw(platform, theme);
		}

		T GetValue() const { return m_Value; }
		T GetMaxValue() const { return m_MaxValue; }
		T GetMinValue() const { return m_MinValue; }

		void SetValue(const T& value) { m_Value = value; }
		void SetMaxValue(const T& value) { m_MaxValue = value; }
		void SetMinValue(const T& value) { m_MinValue = value; }

	private:
		void UpdateSliderPosition()
		{
			const auto offset = (m_LocalEndPosition - m_LocalPosition) * (m_Value - m_MinValue) / (m_MaxValue - m_MinValue);
			m_SliderPosition = LocalToGlobalPosition(m_Parent, m_LocalPosition - m_Size / 2 + offset);
		}

		void UpdatePosition() override
		{
			Component::UpdatePosition();

			m_GlobalPosition = LocalToGlobalPosition(m_Parent, m_LocalPosition);
			m_GlobalEndPosition = LocalToGlobalPosition(m_Parent, m_LocalEndPosition);

			UpdateSliderPosition();
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

#endif
