#ifndef DEF_GUI_PLATFORM_HPP
#define DEF_GUI_PLATFORM_HPP

#include <string>

#include "Utils.hpp"

namespace def::gui
{
	struct HardwareButton
	{
		bool pressed = false;
		bool held = false;
		bool released = false;

		enum class KeyType
		{
			SPACE, APOSTROPHE, COMMA, MINUS, PERIOD, SLASH,
			K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
			SEMICOLON, EQUAL,

			A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S,
			T, U, V, W, X, Y, Z,

			LEFT_BRACKET, BACKSLASH, RIGHT_BRACKET,

			ESCAPE, ENTER, TAB, BACKSPACE, INSERT, DEL, RIGHT, LEFT,
			DOWN, UP, PAGE_UP, PAGE_DOWN, HOME, END,
			CAPS_LOCK, SCROLL_LOCK, NUM_LOCK, PRINT_SCREEN, PAUSE,

			F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13,
			F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,

			NP_0, NP_1, NP_2, NP_3, NP_4, NP_5, NP_6, NP_7, NP_8,
			NP_9, NP_DECIMAL, NP_DIVIDE, NP_MULTIPLY, NP_SUBTRACT, NP_ADD,
			NP_ENTER, NP_EQUAL,

			LEFT_SHIFT, LEFT_CONTROL, LEFT_ALT, LEFT_SUPER, RIGHT_SHIFT,
			RIGHT_CONTROL, RIGHT_ALT, RIGHT_SUPER, MENU,
		};

		enum class ButtonType
		{
			LEFT, RIGHT, WHEEL,
			MOUSE4, MOUSE5, MOUSE6,
			MOUSE7, MOUSE8
		};
	};

	class Platform
	{
	public:
		virtual ~Platform() {}

		virtual void DrawRect(const Vector2i& pos, const Vector2i& size, const Colour& col) = 0;
		virtual void FillRect(const Vector2i& pos, const Vector2i& size, const Colour& col) = 0;
		virtual void DrawText(const Vector2i& pos, const std::string& text, const Colour& col) = 0;
		virtual void DrawLine(const Vector2i& pos1, const Vector2i& pos2, const Colour& col) = 0;

		virtual Vector2i GetMousePos() const = 0;

		virtual HardwareButton GetMouseButton(HardwareButton::ButtonType id) const = 0;
		virtual HardwareButton GetKey(HardwareButton::KeyType id) const = 0;

		virtual bool IsCaps() const = 0;
		virtual float GetDeltaTime() const = 0;

	public:
		inline static Vector2i CHAR_SIZE;

	};
}

#endif
