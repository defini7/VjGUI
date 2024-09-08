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
	def::gui::List* list;

	def::gui::Theme theme;

protected:
	static void Event_Button(def::gui::Component* component, const def::gui::Event& event, void* userdata)
	{
		def::gui::Button* button = static_cast<def::gui::Button*>(component);
		GUI_Testing* app = static_cast<GUI_Testing*>(userdata);

		if (event.type == def::gui::Event::Type::Mouse_Released)
			app->list->AddString(app->textentry->GetText());
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
		theme.slider = { 200, 250, 0 };
		theme.focusedLightFactor = 1.5f;

		platform = new def::gui::Platform_defGameEngine(this);
		manager = new def::gui::Manager(platform);

		panel = manager->AddPanel("Some title", { 10, 10 }, { 500, 200 });

		label = new def::gui::Label(panel, "Some text", { 20, 20 }, { 20, 1 });
		button = new def::gui::Button(panel, "Add", { 200, 50 }, { 3, 1 });
		textentry = new def::gui::TextEntry(panel, { 20, 50 }, { 20, 1 });

		textentry->SetPlaceholder("Write here...");
		button->SetEventHandler(Event_Button, this);

		list = new def::gui::List(panel, { 20, 80 }, { 20, 10 });

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

	if (app.Construct(640, 360, 2, 2))
		app.Run();

	return 0;
}
