#include "gui_manager.hpp"
#include "gui_elements.hpp"

#include "gui_platform_defGameEngine.hpp"

class GUI_Testing : public def::GameEngine
{
public:
	GUI_Testing()
	{
		SetTitle("Testing GUI");
	}

	def::gui::Theme theme;

	def::gui::Platform_defGameEngine* platform_DGE;
	def::gui::Manager* manager;

	def::gui::Panel* panel;
	def::gui::Label* label;
	def::gui::Button* button;

protected:
	static void Event_Button(def::gui::Component* component, const def::gui::Event& event)
	{
		def::gui::Button* button = (def::gui::Button*)component;

		switch (event.type)
		{
		/*case def::gui::Event::Type::Mouse_Hover:
			std::cout << "Button was hovered!" << std::endl;
			break;*/

		case def::gui::Event::Type::Mouse_Pressed:
			std::cout << "Button " << button->GetText() << " was pressed!" << std::endl;
			break;

		case def::gui::Event::Type::Mouse_Held:
			std::cout << "Button " << button->GetText() << " was held!" << std::endl;
			break;

		case def::gui::Event::Type::Mouse_Released:
			std::cout << "Button " << button->GetText() << " was released!" << std::endl;
			break;

		}
	}

	static void Event_Label(def::gui::Component* component, const def::gui::Event& event)
	{
		def::gui::Label* label = (def::gui::Label*)component;

		if (event.type == def::gui::Event::Type::Mouse_Hover)
			std::cout << "Label " << label->GetText() << " was hovered!" << std::endl;
	}

	bool OnUserCreate() override
	{
		theme.panelBackground = { 0, 55, 150 };
		theme.componentBackground = { 0, 0, 125 };
		theme.titleBar = { 200, 200, 200 };
		theme.border = { 200, 200, 200 };
		theme.text = { 200, 200, 0 };
		theme.focusedLightFactor = 1.5f;

		platform_DGE = new def::gui::Platform_defGameEngine(this);
		manager = new def::gui::Manager(platform_DGE);

		panel = manager->AddPanel("Some title", { 100, 100 }, { 800, 600 });
		
		label = new def::gui::Label(panel, "Some text\nAnd another text", { 20, 20 }, { 30, 2 });
		button = new def::gui::Button(panel, "Click me!", { 20, 100 }, { 30, 1 });

		button->SetEventHandler(Event_Button);
		label->SetEventHandler(Event_Label);

		return true;
	}

	bool OnUserUpdate(float deltaTime) override
	{
		if (GetKey(def::Key::K1).pressed)
			label->SetTextAlign(def::gui::Align::LEFT);

		if (GetKey(def::Key::K2).pressed)
			label->SetTextAlign(def::gui::Align::CENTRE);

		if (GetKey(def::Key::K3).pressed)
			label->SetTextAlign(def::gui::Align::RIGHT);

		manager->Update();

		Clear(def::BLACK);
		manager->Draw(theme);

		return true;
	}
};

int main()
{
	GUI_Testing app;

	if (app.Construct(1280, 768, 1, 1))
		app.Run();

	return 0;
}
