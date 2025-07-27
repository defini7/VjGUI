#ifndef DEF_GUI_SLIDER_HPP
#define DEF_GUI_SLIDER_HPP

#include "Component.hpp"
#include "Panel.hpp"

namespace def::gui
{
//! START DECLARATION
	template <class T>
	class Slider : public Component
	{
	public:
		Slider(Component* parent, const Vector2i& start, const Vector2i& end, const Vector2i& size, const T& min_value, const T& max_value, const T& value = 0);
		
		virtual ~Slider() = default;

	public:
		bool Update(Platform* platform) override;
		void Draw(Platform* platform, const Theme& theme) const override;

		T GetValue() const;
		T GetMaxValue() const;
		T GetMinValue() const;

		void SetValue(const T& value);
		void SetMaxValue(const T& value);
		void SetMinValue(const T& value);

	private:
		void UpdateSliderPos();
		void UpdatePos() override;

	private:
		Vector2i m_GlobalEndPos;
		Vector2i m_LocalEndPos;

		Vector2i m_SliderPos;

		T m_MaxValue;
		T m_MinValue;

		T m_Value;

		bool m_Held;

	};
//! END DECLARATION
}

#include "Slider.inl"

#endif
