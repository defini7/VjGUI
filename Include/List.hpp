#ifndef DEF_GUI_LIST_HPP
#define DEF_GUI_LIST_HPP

#include "Label.hpp"
#include "Slider.hpp"

namespace def::gui
{
	class ListNode : public Label
	{
	public:
		ListNode(Component* parent = nullptr);
		ListNode(Component* parent, int width, int index, const std::string& text = "");
		
	public:
		bool Update(Platform* platform) override;
		void Draw(Platform* platform, const Theme& theme) const override;

		void SetIndex(int index);
		int GetIndex() const;

		void UpdatePosition() override;
		void SetOffset(int offset);

	private:
		void Initialise();

	private:
		int m_Index = 0;
		int m_Offset = 0;

	};

	class List : public Panel
	{
	public:
		List(Component* parent = nullptr, bool constructSlider = true);
		List(Component* parent, const Vector2i& pos, const Vector2i& size, bool constructSlider = true);
		virtual ~List();

	public:
		bool AddString(const std::string& data);

		bool Update(Platform* platform) override;
		void Draw(Platform* platform, const Theme& theme) const override;

		void EnableResize(bool enable = true);
		void SetSize(const Vector2i& size);

		std::vector<ListNode*>::iterator GetSelected();

	private:
		void Initialise(bool constructSlider, const Vector2i& size = {});
		void ConstructSlider();
		void UpdateText();

	protected:
		std::vector<ListNode*> m_Nodes;
		std::vector<ListNode*>::iterator m_SelectedItem = m_Nodes.begin();

		Slider<int>* m_Slider = nullptr;
		bool m_Resizable = true;

		bool m_ForceUpdateOffset = false;
		Vector2i m_SizeInNodes;

	};
}

#endif
