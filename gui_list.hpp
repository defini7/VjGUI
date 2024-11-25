#pragma once

#include "gui_label.hpp"
#include "gui_slider.hpp"

namespace def::gui
{
	class List : public Label
	{
	public:
		List(Panel* parent = nullptr);
		List(Panel* parent, const Vector2i& pos, const Vector2i& size);
		virtual ~List();

	public:
		void AddString(const std::string& data);

		bool Update(Platform* platform) override;
		void Draw(Platform* platform, const Theme& theme) const override;

	private:
		void ConstructSlider();

	private:
		std::vector<std::string> m_Items;

		Slider<int>* m_Slider;

	};
}
