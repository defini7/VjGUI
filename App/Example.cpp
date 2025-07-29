#include "VjGUI.hpp"
#include "Platform_defGameEngine.hpp"

using namespace def::gui;

class GUI_Testing : public def::GameEngine
{
public:
	GUI_Testing()
	{
		GetWindow()->SetTitle("Testing GUI");
		UseOnlyTextures(true);
	}

	Platform_defGameEngine* platform = nullptr;
	std::unique_ptr<Manager> manager;
	Panel* panel1 = nullptr;

	Label* label = nullptr;
	Button* button = nullptr;
	TextEntry* textentry = nullptr;
	List* list = nullptr;

	Slider<int16_t>* sliderR = nullptr;
	Slider<int16_t>* sliderG = nullptr;
	Slider<int16_t>* sliderB = nullptr;

	Theme theme;

protected:
	static void Event_Button(Component* component, const Event& event, const std::any& userdata)
	{
		GUI_Testing* app = std::any_cast<GUI_Testing*>(userdata);

		if (event == Event::Mouse_Release)
			app->list->AddString(app->textentry->GetText());
	}

	static void Event_MenuNode(Component* component, const Event& event, const std::any& userData)
	{
		List* node = static_cast<List*>(component);
		GUI_Testing* app = std::any_cast<GUI_Testing*>(userData);
		
		if (event == Event::Component_Select)
			app->label->SetText(node->GetSelected()->GetText());
	}

	bool OnUserCreate() override
	{
		theme.panelBackground = { 0, 55, 150 };
		theme.componentBackground = { 0, 0, 150 };
		theme.titleBar = { 220, 220, 220 };
		theme.border = { 220, 220, 200 };
		theme.textRegular = { 200, 200, 0 };
		theme.textTitle = { 32, 32, 32 };
		theme.cursor = { 200, 200, 200 };
		theme.placeholder = { 100, 100, 0 };
		theme.slider = { 200, 250, 0 };
		theme.focusedLightFactor = 1.5f;

		platform = new Platform_defGameEngine(this);
		manager = std::make_unique<Manager>(platform);

		panel1 = manager->AddPanel("Some title 1", { 10, 10 }, { 500, 200 });

		label = new Label(panel1, "", { 20, 20 }, { 25, 1 });
		button = new Button(panel1, "Add", { 200, 50 }, { 8, 4 });
		textentry = new TextEntry(panel1, { 20, 50 }, { 20, 1 });

		button->SetTextAlign(ALIGN_CENTRE);

		textentry->SetPlaceholder("Write here...");
		button->SetEventHandler(Event_Button, this);

		list = new List(panel1, { 20, 80 }, { 20, 10 });
		list->SetEventHandler(Event_MenuNode, this);

		sliderR = new Slider<int16_t>(panel1, { 250, 60 }, { 300, 110 }, { 5, 5 }, 0, 255, 255);
		sliderG = new Slider<int16_t>(panel1, { 250, 70 }, { 300, 120 }, { 5, 5 }, 0, 255, 255);
		sliderB = new Slider<int16_t>(panel1, { 250, 80 }, { 300, 130 }, { 5, 5 }, 0, 255, 255);

		return true;
	}

	bool OnUserUpdate(float deltaTime) override
	{
		manager->Update();

		ClearTexture(def::BLACK);
		manager->Draw(theme);

		FillTextureRectangle({ 500, 250 }, { 100, 100 },
			{
				(uint8_t)sliderR->GetValue(),
				(uint8_t)sliderG->GetValue(),
				(uint8_t)sliderB->GetValue()
			});

		return true;
	}
};

int main()
{
	GUI_Testing app;

	if (app.Construct(640, 360, 2, 2, false, true))
		app.Run();

	return 0;
}
