#pragma once

#include "gui_component.hpp"

namespace def::gui
{
	class ScrollBar : public Component
	{
	public:
		ScrollBar(Component* parent, Align align = Align::RIGHT);
		~ScrollBar();

	public:
		bool Update(Platform* platform) override;
		void Draw(Platform* platform, const Theme& theme) const override;

		void SetWidth(uint32_t width);
		void ResolveAlign();

		void SetValue(float value);
		float GetValue() const;

	private:
		Vector2i m_Size;

		uint32_t m_Width;
		float m_Value;

	};
}
