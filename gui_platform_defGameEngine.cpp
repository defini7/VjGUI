#define DGE_APPLICATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "gui_platform_defGameEngine.hpp"

namespace def::gui
{
	Platform_defGameEngine::Platform_defGameEngine(GameEngine* engine) : m_Engine(engine)
	{
		using KeyType = HardwareButton::KeyType;
		using ButtonType = HardwareButton::ButtonType;

		m_KeyLookup =
		{
			{ KeyType::SPACE, Key::SPACE }, { KeyType::APOSTROPHE, Key::APOSTROPHE },
			{ KeyType::COMMA, Key::COMMA }, { KeyType::MINUS, Key::MINUS },
			{ KeyType::PERIOD, Key::PERIOD }, { KeyType::SLASH, Key::SLASH },
			{ KeyType::K0, Key::K0 }, { KeyType::K1, Key::K1 },
			{ KeyType::K2, Key::K2 }, { KeyType::K3, Key::K3 },
			{ KeyType::K4, Key::K4 }, { KeyType::K5, Key::K5 },
			{ KeyType::K6, Key::K6 }, { KeyType::K7, Key::K7 },
			{ KeyType::K8, Key::K8 }, { KeyType::K9, Key::K9 },
			{ KeyType::SEMICOLON, Key::SEMICOLON }, { KeyType::EQUAL, Key::EQUAL },
			{ KeyType::A, Key::A }, { KeyType::B, Key::B },
			{ KeyType::C, Key::C }, { KeyType::D, Key::D },
			{ KeyType::E, Key::E }, { KeyType::F, Key::F },
			{ KeyType::G, Key::G }, { KeyType::H, Key::H },
			{ KeyType::I, Key::I }, { KeyType::J, Key::J },
			{ KeyType::K, Key::K }, { KeyType::L, Key::L },
			{ KeyType::M, Key::M }, { KeyType::N, Key::N },
			{ KeyType::O, Key::O }, { KeyType::P, Key::P },
			{ KeyType::Q, Key::Q }, { KeyType::R, Key::R },
			{ KeyType::S, Key::S }, { KeyType::T, Key::T },
			{ KeyType::U, Key::U }, { KeyType::V, Key::V },
			{ KeyType::W, Key::W }, { KeyType::X, Key::X },
			{ KeyType::Y, Key::Y }, { KeyType::Z, Key::Z },
			{ KeyType::LEFT_BRACKET, Key::LEFT_BRACKET }, { KeyType::BACKSLASH, Key::BACKSLASH },
			{ KeyType::RIGHT_BRACKET, Key::RIGHT_BRACKET },
			{ KeyType::NP_0, Key::NP_0 }, { KeyType::NP_1, Key::NP_1 },
			{ KeyType::NP_2, Key::NP_2 }, { KeyType::NP_3, Key::NP_3 },
			{ KeyType::NP_4, Key::NP_4 }, { KeyType::NP_5, Key::NP_5 },
			{ KeyType::NP_6, Key::NP_6 }, { KeyType::NP_7, Key::NP_7 },
			{ KeyType::NP_8, Key::NP_8 }, { KeyType::NP_9, Key::NP_9 },
			{ KeyType::NP_DIVIDE, Key::NP_DIVIDE }, { KeyType::NP_MULTIPLY, Key::NP_MULTIPLY },
			{ KeyType::NP_SUBTRACT, Key::NP_SUBTRACT }, { KeyType::NP_ADD, Key::NP_ADD },
			{ KeyType::NP_EQUAL, Key::NP_EQUAL }, { KeyType::LEFT_SHIFT, Key::LEFT_SHIFT },
			{ KeyType::RIGHT_SHIFT, Key::RIGHT_SHIFT }, { KeyType::BACKSPACE, Key::BACKSPACE },
			{ KeyType::DEL, Key::DEL }, { KeyType::LEFT, Key::LEFT },
			{ KeyType::RIGHT, Key::RIGHT }, { KeyType::ENTER, Key::ENTER }
		};

		m_ButtonLookup =
		{
			{ ButtonType::LEFT, Button::LEFT },
			{ ButtonType::RIGHT, Button::RIGHT },
			{ ButtonType::WHEEL, Button::WHEEL },
			{ ButtonType::MOUSE4, Button::MOUSE4 },
			{ ButtonType::MOUSE5, Button::MOUSE5 },
			{ ButtonType::MOUSE6, Button::MOUSE6 },
			{ ButtonType::MOUSE7, Button::MOUSE7 },
			{ ButtonType::MOUSE8, Button::MOUSE8 }
		};

		CHAR_SIZE = { 8, 8 };
	}

	void Platform_defGameEngine::DrawRect(const Vector2i& pos, const Vector2i& size, const Colour& col)
	{
		m_Engine->DrawTextureRectangle({ pos.x, pos.y }, { size.x, size.y }, ColourToPixel(col));
	}

	void Platform_defGameEngine::FillRect(const Vector2i& pos, const Vector2i& size, const Colour& col)
	{
		m_Engine->FillTextureRectangle({ pos.x, pos.y }, { size.x, size.y }, ColourToPixel(col));
	}

	void Platform_defGameEngine::DrawText(const Vector2i& pos, const std::string& text, const Colour& col)
	{
		m_Engine->DrawTextureString({ pos.x, pos.y }, text, ColourToPixel(col));
	}

	void Platform_defGameEngine::DrawLine(const Vector2i& pos1, const Vector2i& pos2, const Colour& col)
	{
		m_Engine->DrawTextureLine({ pos1.x, pos1.y }, { pos2.x, pos2.y }, ColourToPixel(col));
	}

	Vector2i Platform_defGameEngine::GetMousePosition() const
	{
		return { m_Engine->GetMouseX(), m_Engine->GetMouseY() };
	}

	HardwareButton Platform_defGameEngine::GetMouseButton(HardwareButton::ButtonType id) const
	{
		auto state = m_Engine->GetMouse(m_ButtonLookup.at(id));
		return { state.pressed, state.held, state.released };
	}

	HardwareButton Platform_defGameEngine::GetKey(HardwareButton::KeyType id) const
	{
		auto state = m_Engine->GetKey(m_KeyLookup.at(id));
		return { state.pressed, state.held, state.released };
	}

	bool Platform_defGameEngine::IsCaps() const
	{
		return m_Engine->IsCaps();
	}

	float Platform_defGameEngine::GetDeltaTime() const
	{
		return m_Engine->GetDeltaTime();
	}

	void Platform_defGameEngine::Set(GameEngine* engine)
	{
		m_Engine = engine;
	}

	Pixel Platform_defGameEngine::ColourToPixel(const Colour& col)
	{
		return Pixel(col.r, col.g, col.b, col.a);
	}
}
