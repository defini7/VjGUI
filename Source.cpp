#include "gui_manager.hpp"
#include "gui_elements.hpp"

#include "gui_platform_defGameEngine.hpp"

class GUI_Testing : public def::GameEngine
{
public:
	GUI_Testing()
	{
		SetTitle("Testing GUI");
		UseOnlyTextures(true);
	}

	def::gui::Platform_defGameEngine* platform;
	def::gui::Manager* manager;
	def::gui::Panel* panel;

	def::gui::Label* label;
	def::gui::Button* button;
	def::gui::TextEntry* textentry;

	def::gui::Theme theme;

protected:
	static void Event_TextEntry(def::gui::Component* component, const def::gui::Event& event)
	{
		def::gui::TextEntry* textentry = (def::gui::TextEntry*)component;

		switch (event.type)
		{
		case def::gui::Event::Type::Component_Focused:
			std::cout << "Text entry was focused!" << std::endl;
			break;

		case def::gui::Event::Type::Component_Unfocused:
			std::cout << "Text entry was unfocused!" << std::endl;
			break;

		case def::gui::Event::Type::Component_Confirm:
			std::cout << "Text entry text: " << textentry->GetText() << std::endl;
			break;

		}
	}

	bool OnUserCreate() override
	{
		theme.panelBackground = { 0, 55, 150 };
		theme.componentBackground = { 0, 0, 150 };
		theme.titleBar = { 220, 220, 220 };
		theme.border = { 220, 220, 200 };
		theme.text = { 200, 200, 0 };
		theme.cursor = { 200, 200, 200 };
		theme.placeholder = { 100, 100, 0 };
		theme.focusedLightFactor = 1.5f;

		platform = new def::gui::Platform_defGameEngine(this);
		manager = new def::gui::Manager(platform);

		panel = manager->AddPanel("Some title", { 10, 10 }, { 500, 400 });

		label = new def::gui::Label(panel, "some text", { 20, 20 }, { 30, 1 });
		button = new def::gui::Button(panel, "click me!", { 20, 50 }, { 30, 1 });
		textentry = new def::gui::TextEntry(panel, { 20, 80 }, { 20, 1 });

		textentry->SetPlaceholder("Write something...");

		textentry->SetEventHandler(Event_TextEntry);

		return true;
	}

	bool OnUserUpdate(float deltaTime) override
	{
		manager->Update();

		ClearTexture(def::BLACK);
		manager->Draw(theme);

		return true;
	}
};

int main()
{
	GUI_Testing app;

	if (app.Construct(1280, 720, 1, 1))
		app.Run();

	return 0;
}
