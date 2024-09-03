#pragma once

#include <string>

#include "gui_utils.hpp"

namespace def::gui
{
	struct HardwareButton
	{
		bool pressed = false;
		bool held = false;
		bool released = false;

		enum class KeyType
		{
			SPACE,
			APOSTROPHE,
			COMMA,
			MINUS,
			PERIOD,
			SLASH,
			K0, K1,
			K2, K3,
			K4, K5,
			K6, K7,
			K8, K9,
			SEMICOLON,
			EQUAL,
			A, B, C, D, E, F, G, H, I, J, K, L, M,
			N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			LEFT_BRACKET, BACKSLASH,
			RIGHT_BRACKET, GRAVE_ACCENT,
			NP_0, NP_1,
			NP_2, NP_3,
			NP_4, NP_5,
			NP_6, NP_7,
			NP_8, NP_9,
			NP_DIVIDE, NP_MULTIPLY,
			NP_SUBTRACT, NP_ADD, NP_EQUAL,
			LEFT_SHIFT, RIGHT_SHIFT, BACKSPACE,
			DELETE, LEFT_ARROW, RIGHT_ARROW, ENTER
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
		virtual void DrawRect(const Vector2i& pos, const Vector2i& size, const Colour& col) = 0;
		virtual void FillRect(const Vector2i& pos, const Vector2i& size, const Colour& col) = 0;
		virtual void DrawText(const Vector2i& pos, const std::string& text, const Colour& col) = 0;
		virtual void DrawLine(const Vector2i& pos1, const Vector2i& pos2, const Colour& col) = 0;

		virtual Vector2i GetMousePosition() const = 0;

		virtual HardwareButton GetMouseButton(HardwareButton::ButtonType id) const = 0;
		virtual HardwareButton GetKey(HardwareButton::KeyType id) const = 0;

		virtual bool IsCaps() const = 0;

		virtual float GetDeltaTime() const = 0;

	};
}
