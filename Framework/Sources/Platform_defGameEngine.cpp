#define DGE_APPLICATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../Include/Platform_defGameEngine.hpp"

namespace def::gui
{
//! START IMPLEMENTATION
	Platform_defGameEngine::Platform_defGameEngine(GameEngine* engine) : m_Engine(engine)
	{
		using KeyType = HardwareButton::KeyType;
		using ButtonType = HardwareButton::ButtonType;

		m_KeyLookup =
		{
			{ KeyType::SPACE, def::Key::SPACE }, { KeyType::APOSTROPHE, def::Key::APOSTROPHE },
			{ KeyType::COMMA, def::Key::COMMA }, { KeyType::MINUS, def::Key::MINUS },
			{ KeyType::PERIOD, def::Key::PERIOD }, { KeyType::SLASH, def::Key::SLASH },
			{ KeyType::K0, def::Key::K0 }, { KeyType::K1, def::Key::K1 },
			{ KeyType::K2, def::Key::K2 }, { KeyType::K3, def::Key::K3 },
			{ KeyType::K4, def::Key::K4 }, { KeyType::K5, def::Key::K5 },
			{ KeyType::K6, def::Key::K6 }, { KeyType::K7, def::Key::K7 },
			{ KeyType::K8, def::Key::K8 }, { KeyType::K9, def::Key::K9 },
			{ KeyType::SEMICOLON, def::Key::SEMICOLON }, { KeyType::EQUAL, def::Key::EQUAL },
			{ KeyType::A, def::Key::A }, { KeyType::B, def::Key::B },
			{ KeyType::C, def::Key::C }, { KeyType::D, def::Key::D },
			{ KeyType::E, def::Key::E }, { KeyType::F, def::Key::F },
			{ KeyType::G, def::Key::G }, { KeyType::H, def::Key::H },
			{ KeyType::I, def::Key::I }, { KeyType::J, def::Key::J },
			{ KeyType::K, def::Key::K }, { KeyType::L, def::Key::L },
			{ KeyType::M, def::Key::M }, { KeyType::N, def::Key::N },
			{ KeyType::O, def::Key::O }, { KeyType::P, def::Key::P },
			{ KeyType::Q, def::Key::Q }, { KeyType::R, def::Key::R },
			{ KeyType::S, def::Key::S }, { KeyType::T, def::Key::T },
			{ KeyType::U, def::Key::U }, { KeyType::V, def::Key::V },
			{ KeyType::W, def::Key::W }, { KeyType::X, def::Key::X },
			{ KeyType::Y, def::Key::Y }, { KeyType::Z, def::Key::Z },
			{ KeyType::LEFT_BRACKET, def::Key::LEFT_BRACKET }, { KeyType::BACKSLASH, def::Key::BACKSLASH },
			{ KeyType::RIGHT_BRACKET, def::Key::RIGHT_BRACKET },
			{ KeyType::NP_0, def::Key::NP_0 }, { KeyType::NP_1, def::Key::NP_1 },
			{ KeyType::NP_2, def::Key::NP_2 }, { KeyType::NP_3, def::Key::NP_3 },
			{ KeyType::NP_4, def::Key::NP_4 }, { KeyType::NP_5, def::Key::NP_5 },
			{ KeyType::NP_6, def::Key::NP_6 }, { KeyType::NP_7, def::Key::NP_7 },
			{ KeyType::NP_8, def::Key::NP_8 }, { KeyType::NP_9, def::Key::NP_9 },
			{ KeyType::NP_DIVIDE, def::Key::NP_DIVIDE }, { KeyType::NP_MULTIPLY, def::Key::NP_MULTIPLY },
			{ KeyType::NP_SUBTRACT, def::Key::NP_SUBTRACT }, { KeyType::NP_ADD, def::Key::NP_ADD },
			{ KeyType::NP_EQUAL, def::Key::NP_EQUAL }, { KeyType::LEFT_SHIFT, def::Key::LEFT_SHIFT },
			{ KeyType::RIGHT_SHIFT, def::Key::RIGHT_SHIFT }, { KeyType::BACKSPACE, def::Key::BACKSPACE },
			{ KeyType::DEL, def::Key::DEL }, { KeyType::LEFT, def::Key::LEFT },
			{ KeyType::RIGHT, def::Key::RIGHT }, { KeyType::ENTER, def::Key::ENTER }
		};

		m_ButtonLookup =
		{
			{ ButtonType::LEFT, def::Button::LEFT },
			{ ButtonType::RIGHT, def::Button::RIGHT },
			{ ButtonType::WHEEL, def::Button::WHEEL },
			{ ButtonType::MOUSE4, def::Button::MOUSE4 },
			{ ButtonType::MOUSE5, def::Button::MOUSE5 },
			{ ButtonType::MOUSE6, def::Button::MOUSE6 },
			{ ButtonType::MOUSE7, def::Button::MOUSE7 },
			{ ButtonType::MOUSE8, def::Button::MOUSE8 }
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

	Vector2i Platform_defGameEngine::GetMousePos() const
	{
		return { m_Engine->GetInput()->GetMouseX(), m_Engine->GetInput()->GetMouseY() };
	}

	HardwareButton Platform_defGameEngine::GetMouseButton(HardwareButton::ButtonType id) const
	{
		auto state = m_Engine->GetInput()->GetButtonState(m_ButtonLookup.at(id));
		return { state.pressed, state.held, state.released };
	}

	HardwareButton Platform_defGameEngine::GetKey(HardwareButton::KeyType id) const
	{
		auto state = m_Engine->GetInput()->GetKeyState(m_KeyLookup.at(id));
		return { state.pressed, state.held, state.released };
	}

	bool Platform_defGameEngine::IsCaps() const
	{
		return m_Engine->GetInput()->IsCaps();
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
//! END IMPLEMENTATION
}
