#define DGE_APPLICATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "gui_platform_defGameEngine.hpp"

namespace def::gui
{
	Platform_defGameEngine::Platform_defGameEngine(GameEngine* engine) : m_Engine(engine)
	{
	}

	void Platform_defGameEngine::DrawRect(const Vector2i& pos, const Vector2i& size, const Colour& col)
	{
		m_Engine->DrawRectangle(pos.x, pos.y, size.x, size.y, { col.r, col.g, col.b, col.a });
	}

	void Platform_defGameEngine::FillRect(const Vector2i& pos, const Vector2i& size, const Colour& col)
	{
		m_Engine->FillRectangle(pos.x, pos.y, size.x, size.y, { col.r, col.g, col.b, col.a });
	}

	void Platform_defGameEngine::DrawText(const Vector2i& pos, const std::string& text, const Colour& col)
	{
		m_Engine->DrawString(pos.x, pos.y, text, { col.r, col.g, col.b, col.a });
	}

	Vector2i Platform_defGameEngine::GetMousePosition() const
	{
		return { m_Engine->GetMouseX(), m_Engine->GetMouseY() };
	}

	ButtonState Platform_defGameEngine::GetMouseButton(int id) const
	{
		auto state = m_Engine->GetMouse((def::Button)id);
		return { state.pressed, state.held, state.released };
	}

	float Platform_defGameEngine::GetDeltaTime() const
	{
		return m_Engine->GetDeltaTime();
	}

	void Platform_defGameEngine::Set(GameEngine* engine)
	{
		m_Engine = engine;
	}
}
