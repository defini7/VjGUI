#ifndef VJGUI_HPP
#define VJGUI_HPP

#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <memory>
#include <list>
#include <any>
#include <unordered_map>

#ifdef VJGUI_PLATFORM_DEFGAMEENGINE
#include "defGameEngine.hpp"
#endif

namespace def::gui
{
		enum class Align
		{
			LEFT,
			CENTRE,
			RIGHT,
			TOP,
			BOTTOM
		};

		struct Colour
		{
			unsigned char r = 0;
			unsigned char g = 0;
			unsigned char b = 0;
			unsigned char a = 255;
		};

		template <class T>
		struct Vector2D
		{
			static_assert(std::is_arithmetic<T>::value, "Vector2D<T> must be numeric");

			Vector2D() = default;
			Vector2D(const T& x, const T& y) : x(x), y(y) {}

			Vector2D(const Vector2D&) = default;
			Vector2D& operator=(const Vector2D&) = default;

			T x = 0, y = 0;

			inline Vector2D Clamp(const Vector2D& start, const Vector2D& end) const;
			inline Vector2D Lerp(const Vector2D& v, const double t) const;

			inline T Distance(const Vector2D& v) const;
			inline T DotProduct(const Vector2D& v) const;
			inline T CrossProduct(const Vector2D& v) const;

			inline T Angle(const Vector2D& v) const;

			inline T Length2() const;
			inline T Length() const;

			inline T ManhattanDistance(const Vector2D& v) const;

			inline Vector2D Max(const Vector2D& v) const;
			inline Vector2D Min(const Vector2D& v) const;

			inline void Swap(Vector2D& v);

			inline Vector2D Normalise() const;
			inline Vector2D Abs() const;

			inline Vector2D Perpendicular() const;

			inline Vector2D Floor() const;
			inline Vector2D Ceil() const;
			inline Vector2D Round() const;

			inline Vector2D Cartesian() const;
			inline Vector2D Polar() const;

			inline std::string ToString() const;

			template <class F>
			inline operator Vector2D<F>() const
			{
				return { static_cast<F>(this->x), static_cast<F>(this->y) };
			}
		};

		typedef Vector2D<int> Vector2i;
		typedef Vector2D<float> Vector2f;
		typedef Vector2D<double> Vector2d;
	enum class Event
	{
		None,
		Mouse_Press,
		Mouse_Hold,
		Mouse_Release,
		Mouse_Hover,
		Component_Focus,
		Component_Unfocus,
		Component_Confirm,
		Component_Select
	};

	template <class T>
	using EventHandlerFunc = void (*)(T*, const Event&, const std::any&);

	template <class T>
	class EventHandler
	{
	public:
		inline virtual void SetEventHandler(EventHandlerFunc<T> func, const std::any& userData = nullptr)
		{
			m_EventHandlerFunc = func;
			m_UserData = userData;
		}

		inline void HandleEvent(T* component, const Event& event)
		{
			if (m_EventHandlerFunc)
				m_EventHandlerFunc(component, event, m_UserData);
		}

	private:
		EventHandlerFunc<T> m_EventHandlerFunc = nullptr;
		std::any m_UserData = nullptr;

	};
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

#ifdef VJGUI_PLATFORM_DEFGAMEENGINE
	class Platform_defGameEngine : public Platform
	{
	public:
		Platform_defGameEngine(GameEngine* engine = nullptr);

	public:
		void DrawRect(const Vector2i& pos, const Vector2i& size, const Colour& col) override;
		void FillRect(const Vector2i& pos, const Vector2i& size, const Colour& col) override;
		void DrawText(const Vector2i& pos, const std::string& text, const Colour& col) override;
		void DrawLine(const Vector2i& pos1, const Vector2i& pos2, const Colour& col) override;

		virtual Vector2i GetMousePos() const override;

		virtual HardwareButton GetMouseButton(HardwareButton::ButtonType id) const override;
		virtual HardwareButton GetKey(HardwareButton::KeyType id) const override;

		virtual float GetDeltaTime() const override;
		virtual bool IsCaps() const override;

		void Set(GameEngine* engine);

		static Pixel ColourToPixel(const Colour& col);

	private:
		GameEngine* m_Engine;

		std::unordered_map<HardwareButton::KeyType, Key> m_KeyLookup;
		std::unordered_map<HardwareButton::ButtonType, Button> m_ButtonLookup;

	};
#endif
    
	struct Theme
	{
		Colour ApplyLight(const Colour& colour) const;

		Colour border;
		Colour componentBackground;
		Colour panelBackground;
		Colour textRegular;
		Colour textTitle;
		Colour placeholder;
		Colour titleBar;
		Colour cursor;
		Colour slider;

		float focusedLightFactor = 0.0f;
		bool forceUsingPlaceholder = false;
	};
	class Component : public EventHandler<Component>
	{
	public:
		Component(Component* parent = nullptr);
		Component(Component* parent, const Vector2i& pos, const Vector2i& size);

		virtual ~Component();

	public:
		static Vector2i LocalToGlobalPos(Component* parent, const Vector2i& pos);

		// Only if visible flag is set to true: updates hover and focus events, then updates Pos
		// and calls itself on each child component
		virtual bool Update(Platform* platform);

		// Draws children components if visible flag is set to true
		virtual void Draw(Platform* platform, const Theme& theme) const;

		const Vector2i& GetGlobalPos();

		// Returns local Pos
		const Vector2i& GetPos() const;
		void SetPos(const Vector2i& pos);

		const Vector2i& GetSize() const;
		void SetSize(const Vector2i& size);

		// Updates global Pos of the component by applying an offset
		// of the title bar and the offset of the parent
		virtual void UpdatePos();

		Component* GetParent() const;
		void SetParent(Component* parent);

		Align GetAlign() const;
		void SetAlign(Align align);

		void EnableLight(bool enable);
		void EnableUpdate(bool enable);
		void Show(bool enable);
		void EnableAll(bool enable);

		bool IsVisible() const;

		// !!! Add children components using ONLY that method !!!
		template <class T>
		T* AddComponent(T* component)
		{
			component->SetParent(this);
			m_Children.push_back(component);

			return component;
		}

		std::list<Component*>& GetChildren();

	protected:
		Vector2i m_LocalPos; // Relative to the panel
		Vector2i m_GlobalPos; // Relative to the screen
		Vector2i m_Size;

		Component* m_Parent = nullptr;
		std::list<Component*> m_Children;

		Align m_Align = Align::LEFT;

		bool m_EnableLight = false;
		bool m_IsFocused = false;
		bool m_IsVisible = true;
		bool m_Update = true;

	};
	class Panel : public Component
	{
	public:
		Panel(Component* parent = nullptr);
		Panel(Component* parent, const std::string& title, const Vector2i& pos, const Vector2i& size);
		~Panel();

	public:
		const std::string& GetTitle() const;
		void SetTitle(const std::string& title);

		bool Update(Platform* platform);
		void Draw(Platform* platform, const Theme& theme) const;

		void ShowTitleBar(bool enable);
		void ShowTitle(bool enable);

		void FixPos(bool enable);

	private:
		std::string m_Title;

		Vector2i m_DragOffset;
		bool m_Drag = false;

		bool m_FixedPos = false;

		bool m_ShowTitleBar = true;
		bool m_ShowTitle = true;

	public:
		static constexpr int TITLE_BAR_WIDTH = 20;

	};
	class Manager
	{
	public:
		Manager();
		Manager(Platform* platform);
		~Manager();

	public:
		void Update();
		void Draw(const Theme& theme);

		Panel* AddPanel(const std::string& title, const Vector2i& pos, const Vector2i& size);

		void SetPlatform(Platform* platform);

	private:
		std::list<Panel> m_Panels;

		Platform* m_Platform;
		
	};
    
    class Button;

	class Label : public Component
	{
	public:
		Label(Component* parent = nullptr);
		Label(Component* parent, const std::string& text, const Vector2i& pos, const Vector2i& size);
		
		virtual ~Label();

		friend class Button;
		friend class TextEntry;
		friend class List;

	public:
		const std::string& GetText() const;
		void SetText(const std::string& text);

		bool Update(Platform* platform) override;
		void Draw(Platform* platform, const Theme& theme) const override;

		Vector2i GetSize() const;
		void SetSize(const Vector2i& size);

		Align GetTextAlign() const;
		virtual void SetTextAlign(Align align);

	private:
		// For each string in line we calculate it's Pos and push it to the m_TextSplitted
		void UpdateTextPos(const std::vector<std::string>& lines);

		// Split the m_Text by '\n' symbol and push it to lines
		void SplitTextIntoLines(std::vector<std::string>& lines);

		// Perform SplitTextIntoLines and UpdateTextPos if m_ForceUpdateOffset flag was set to true
		void UpdateText();

	protected:
		std::string m_Text;
		Vector2i m_CharsSize;
		Align m_TextAlign = Align::LEFT;

		struct TextUnit
		{
			Vector2i offset;
			std::string text;
		};

		// Contains transformed text after calling UpdateTextPos function
		std::vector<TextUnit> m_TextSplitted;

		bool m_ForceUpdateOffset = true;

	};
	class Button : public Label
	{
	public:
		Button(Component* parent = nullptr);
		Button(Component* parent, const std::string& text, const Vector2i& pos, const Vector2i& size);

		virtual ~Button();

	public:
		bool Update(Platform* platform) override;
		void Draw(Platform* platform, const Theme& theme) const override;

	private:
		bool m_Pressed = false;
		bool m_Held = false;
		bool m_Released = false;

	};
	class TextEntry : public Label
	{
	public:
		using KeyType = HardwareButton::KeyType;

		TextEntry(Component* parent = nullptr);
		TextEntry(Component* parent, const Vector2i& pos, const Vector2i& size, const std::string& text = "", const std::string& placeholder = "");
		virtual ~TextEntry();

	public:
		void SetPlaceholder(const std::string& placeholder);
		const std::string& GetPlaceholder() const;

		bool Update(Platform* platform) override;
		void Draw(Platform* platform, const Theme& theme) const override;

		void SetCursorPos(uint32_t pos);
		uint32_t GetCursorPos() const;

	public:
		static std::unordered_map<KeyType, std::pair<char, char>>& s_PickedKeyboard;

		// pair<char, char> - main, alternative chars
		static std::unordered_map<KeyType, std::pair<char, char>> s_KeyboardUS;

	private:
		std::string m_Placeholder;

		int m_CursorPos;
		float m_Ticks;

		static constexpr float CURSOR_HIDE_DELAY = 1.0f;

	};
	template <class T>
	class Slider : public Component
	{
	public:
		Slider(Component* parent, const Vector2i& start, const Vector2i& end, const Vector2i& size, const T& min_value, const T& max_value, const T& value = 0);
		
		virtual ~Slider() = default;

	public:
		bool Update(Platform* platform) override;
		void Draw(Platform* platform, const Theme& theme) const override;

		T GetValue() const;
		T GetMaxValue() const;
		T GetMinValue() const;

		void SetValue(const T& value);
		void SetMaxValue(const T& value);
		void SetMinValue(const T& value);

	private:
		void UpdateSliderPos();
		void UpdatePos() override;

	private:
		Vector2i m_GlobalEndPos;
		Vector2i m_LocalEndPos;

		Vector2i m_SliderPos;

		T m_MaxValue;
		T m_MinValue;

		T m_Value;

		bool m_Held;

	};
	class ListNode : public Label
	{
	public:
		ListNode(Component* parent = nullptr);
		ListNode(Component* parent, int width, int index, const std::string& text = "");

		friend class List;
		
	public:
		bool Update(Platform* platform) override;
		void Draw(Platform* platform, const Theme& theme) const override;

		void SetIndex(int index);
		int GetIndex() const;

		void UpdatePos() override;
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
		void AddString(const std::string& data);

		bool Update(Platform* platform) override;
		void Draw(Platform* platform, const Theme& theme) const override;

		void EnableResize(bool enable = true);
		void SetSize(const Vector2i& size);

		ListNode* GetSelected();

		void Clear();

	private:
		void Initialise(bool constructSlider, const Vector2i& size = {});
		void ConstructSlider();
		void UpdateText();

	protected:
		std::vector<ListNode*> m_Nodes;
		size_t m_SelectedItem = size_t(-1);

		Slider<int>* m_Slider = nullptr;

		Vector2i m_SizeInNodes;

		bool m_Resizable = true;
		bool m_ForceUpdateOffset = false;

	};

#ifdef VJGUI_IMPL
#undef VJGUI_IMPL

		template <class T>
		inline Vector2D<T> Vector2D<T>::Clamp(const Vector2D& start, const Vector2D& end) const
		{
			return { std::clamp(x, start.x, end.x), std::clamp(y, start.y, end.y) };
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Lerp(const Vector2D& v, const double t) const
		{
			return { (T)std::lerp(x, v.x, t), (T)std::lerp(y, v.y, t) };
		}

		template <class T>
		inline T Vector2D<T>::Distance(const Vector2D& v) const
		{
			return (*this - v).Length();
		}

		template <class T>
		inline T Vector2D<T>::DotProduct(const Vector2D& v) const
		{
			return x * v.x + y * v.y;
		}

		template <class T>
		inline T Vector2D<T>::CrossProduct(const Vector2D& v) const
		{
			return x * v.y - y * v.x;
		}

		template <class T>
		inline T Vector2D<T>::Angle(const Vector2D& v) const
		{
			return acos(DotProduct(v) / (Length() + v.Length()));
		}

		template <class T>
		inline T Vector2D<T>::Length2() const
		{
			return x * x + y * y;
		}

		template <class T>
		inline T Vector2D<T>::Length() const
		{
			return std::sqrt(x * x + y * y);
		}

		template <class T>
		inline T Vector2D<T>::ManhattanDistance(const Vector2D& v) const
		{
			return std::abs(x - v.x) + std::abs(y - v.y);
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Max(const Vector2D& v) const
		{
			return Vector2D(std::max(x, v.x), std::max(y, v.y));
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Min(const Vector2D& v) const
		{
			return Vector2D(std::min(x, v.x), std::min(y, v.y));
		}

		template <class T>
		inline void Vector2D<T>::Swap(Vector2D& v)
		{
			std::swap(x, v.x);
			std::swap(y, v.y);
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Normalise() const
		{
			const T n = (T)1 / Length();
			return Vector2D(x * n, y * n);
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Abs() const
		{
			return Vector2D(std::abs(x), std::abs(y));
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Perpendicular() const
		{
			return Vector2D(-y, x);
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Floor() const
		{
			return Vector2D(std::floor(x), std::floor(y));
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Ceil() const
		{
			return Vector2D(std::ceil(x), std::ceil(y));
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Round() const
		{
			return Vector2D(std::round(x), std::round(y));
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Cartesian() const
		{
			return Vector2D(std::cos(y) * x, std::sin(y) * x);
		}

		template <class T>
		inline Vector2D<T> Vector2D<T>::Polar() const
		{
			return Vector2D(Length(), atan2(y, x));
		}

		template <class T>
		inline std::string Vector2D<T>::ToString() const
		{
			return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
		}

		template <class T1, class T2>
		Vector2D<T1>& operator+=(Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			v1.x += v2.x;
			v1.y += v2.y;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<T1>& operator-=(Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			v1.x -= v2.x;
			v1.y -= v2.y;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<T1>& operator*=(Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			v1.x *= v2.x;
			v1.y *= v2.y;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<T1>& operator/=(Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			v1.x /= v2.x;
			v1.y /= v2.y;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<T1>& operator%=(Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			v1.x %= v2.x;
			v1.y %= v2.y;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<T1>& operator+=(Vector2D<T1>& v1, const T2& v2)
		{
			v1.x += v2;
			v1.y += v2;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<T1>& operator-=(Vector2D<T1>& v1, const T2& v2)
		{
			v1.x -= v2;
			v1.y -= v2;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<T1>& operator*=(Vector2D<T1>& v1, const T2& v2)
		{
			v1.x *= v2;
			v1.y *= v2;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<T1>& operator/=(Vector2D<T1>& v1, const T2& v2)
		{
			v1.x /= v2;
			v1.y /= v2;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<T1>& operator%=(Vector2D<T1>& v1, const T2& v2)
		{
			v1.x %= v2;
			v1.y %= v2;
			return v1;
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator+(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1.x + v2.x, v1.y + v2.y);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator-(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1.x - v2.x, v1.y - v2.y);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator*(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1.x * v2.x, v1.y * v2.y);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator/(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1.x / v2.x, v1.y / v2.y);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator%(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1.x % v2.x, v1.y % v2.y);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator+(const Vector2D<T1>& v1, const T2& v2)
		{
			return Vector2D(v1.x + v2, v1.y + v2);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator-(const Vector2D<T1>& v1, const T2& v2)
		{
			return Vector2D(v1.x - v2, v1.y - v2);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator*(const Vector2D<T1>& v1, const T2& v2)
		{
			return Vector2D(v1.x * v2, v1.y * v2);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator/(const Vector2D<T1>& v1, const T2& v2)
		{
			return Vector2D(v1.x / v2, v1.y / v2);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator+(const T1& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1 + v2.x, v1 + v2.y);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator-(const T1& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1 - v2.x, v1 - v2.y);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator*(const T1& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1 * v2.x, v1 * v2.y);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator/(const T1& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1 / v2.x, v1 / v2.y);
		}

		template <class T1, class T2>
		Vector2D<decltype(T1(1) + T2(1))> operator%(const T1& v1, const Vector2D<T2>& v2)
		{
			return Vector2D(v1 % v2.x, v1 % v2.y);
		}

		template <class T>
		Vector2D<T> operator-(const Vector2D<T>& v)
		{
			return Vector2D(-v.x, -v.y);
		}

		template <class T1, class T2>
		bool operator==(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return v1.x == v2.x && v1.y == v2.y;
		}

		template <class T1, class T2>
		bool operator<=(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return v1.x <= v2.x && v1.y <= v2.y;
		}

		template <class T1, class T2>
		bool operator>=(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return v1.x >= v2.x && v1.y >= v2.y;
		}

		template <class T1, class T2>
		bool operator<(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return v1.x < v2.x && v1.y < v2.y;
		}

		template <class T1, class T2>
		bool operator>(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return v1.x > v2.x && v1.y > v2.y;
		}

		template <class T1, class T2>
		bool operator!=(const Vector2D<T1>& v1, const Vector2D<T2>& v2)
		{
			return v1.x != v2.x || v1.y != v2.y;
		}

		bool IsPointInRect(const Vector2i& point, const Vector2i& rect_pos, const Vector2i& rect_size)
		{
			return point >= rect_pos && point < rect_pos + rect_size;
		}
    
#ifdef VJGUI_PLATFORM_DEFGAMEENGINE
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
#endif

	Colour Theme::ApplyLight(const Colour& colour) const
	{
		return Colour
		(
			std::clamp((float)colour.r * focusedLightFactor, 0.0f, 255.0f),
			std::clamp((float)colour.g * focusedLightFactor, 0.0f, 255.0f),
			std::clamp((float)colour.b * focusedLightFactor, 0.0f, 255.0f),
			std::clamp((float)colour.a * focusedLightFactor, 0.0f, 255.0f)
		);
	}
	Component::Component(Component* parent)
		: m_Parent(parent)
	{
		if (parent)
			parent->AddComponent(this);
	}

	Component::Component(Component* parent, const Vector2i& pos, const Vector2i& size)
		: m_Size(size), m_Parent(parent)
	{
		if (parent)
			parent->AddComponent(this);

		SetPos(pos);
	}

	Component::~Component()
	{
		for (auto child : m_Children)
		{
			if (child)
				delete child;
		}
	}

	Vector2i Component::LocalToGlobalPos(Component* parent, const Vector2i& pos)
	{
		Vector2i output = pos;

		// If there is no parent then we assume that we are on panel
		// so let's take into account the title bar width

		if (parent)
			output += parent->m_GlobalPos;
		else
			output += Vector2i(1, Panel::TITLE_BAR_WIDTH);

		return output;
	}

	bool Component::Update(Platform* platform)
	{
		if (!m_Update)
			return false;

		Vector2i mousePos = platform->GetMousePos();
		HardwareButton mouseLeft = platform->GetMouseButton(HardwareButton::ButtonType::LEFT);

		bool light = false;

		if (IsPointInRect(mousePos, m_GlobalPos, m_Size))
		{
			HandleEvent(this, Event::Mouse_Hover);

			if (mouseLeft.pressed)
			{
				m_IsFocused = true;

				HandleEvent(this, Event::Mouse_Press);
				HandleEvent(this, Event::Component_Focus);
			}

			if (mouseLeft.held)     HandleEvent(this, Event::Mouse_Hold);
			if (mouseLeft.released) HandleEvent(this, Event::Mouse_Release);

			light = true;
		}
		else
		{
			if (mouseLeft.pressed && m_IsFocused)
			{
				m_IsFocused = false;

				HandleEvent(this, Event::Mouse_Press);
				HandleEvent(this, Event::Component_Unfocus);
			}
		}

		for (auto& component : m_Children)
		{
			if (m_IsVisible)
				component->UpdatePos();

			component->m_EnableLight = component->Update(platform);
		}

		return light;
	}

	void Component::Draw(Platform* platform, const Theme& theme) const
	{
		if (!m_IsVisible)
			return;

		for (auto& component : m_Children)
			component->Draw(platform, theme);
	}

	const Vector2i& Component::GetGlobalPos()
	{
		return m_GlobalPos;
	}

	const Vector2i& Component::GetPos() const
	{
		return m_LocalPos;
	}

	void Component::SetPos(const Vector2i& pos)
	{
		m_GlobalPos = LocalToGlobalPos(m_Parent, pos);
		m_LocalPos = pos;
	}

	const Vector2i& Component::GetSize() const
	{
		return m_Size;
	}

	void Component::SetSize(const Vector2i& size)
	{
		m_Size = size;
	}

	void Component::UpdatePos()
	{
		m_GlobalPos = Vector2i(1, Panel::TITLE_BAR_WIDTH) + m_LocalPos;

		if (m_Parent)
			m_GlobalPos += m_Parent->m_GlobalPos;
	}

	void Component::SetParent(Component* parent)
	{
		m_Parent = parent;
	}

	Align Component::GetAlign() const
	{
		return m_Align;
	}

	void Component::SetAlign(Align align)
	{
		m_Align = align;
	}

	void Component::EnableLight(bool enable)
	{
		m_EnableLight = enable;
	}

	void Component::EnableUpdate(bool enable)
	{
		m_Update = enable;
	}

	void Component::Show(bool enable)
	{
		m_IsVisible = enable;
	}

	void Component::EnableAll(bool enable)
	{
		Show(enable);
		EnableUpdate(enable);
		EnableLight(enable);
	}

	bool Component::IsVisible() const
	{
		return m_IsVisible;
	}

	std::list<Component*>& Component::GetChildren()
	{
		return m_Children;
	}

	Component* Component::GetParent() const
	{
		return m_Parent;
	}
	Panel::Panel(Component* parent) : Component(parent)
	{
	}

	Panel::Panel(Component* parent, const std::string& title, const Vector2i& pos, const Vector2i& size)
		: Component(parent, pos, size), m_Title(title)
	{
	}

	Panel::~Panel()
	{
	}

	const std::string& Panel::GetTitle() const
	{
		return m_Title;
	}

	void Panel::SetTitle(const std::string& title)
	{
		m_Title = title;
	}

	bool Panel::Update(Platform* platform)
	{
		if (!m_Update)
			return false;

		Vector2i mousePos = platform->GetMousePos();
		HardwareButton mouseState = platform->GetMouseButton(HardwareButton::ButtonType::LEFT);

		if (IsPointInRect(mousePos, m_GlobalPos, m_Size))
		{
			HandleEvent(this, Event::Mouse_Hover);

			if (!m_FixedPos)
			{
				if (mouseState.pressed && IsPointInRect(mousePos, m_GlobalPos, Vector2i(m_Size.x, TITLE_BAR_WIDTH)))
				{
					m_Drag = true;
					m_DragOffset = mousePos - m_GlobalPos;
				}
			}
		}

		if (!m_FixedPos)
		{
			if (m_Drag)
				m_GlobalPos = mousePos - m_DragOffset;

			if (mouseState.released)
				m_Drag = false;
		}

		for (auto& component : m_Children)
		{
			component->UpdatePos();
			component->EnableLight(component->Update(platform));
		}

		return false;
	}

	void Panel::Draw(Platform* platform, const Theme& theme) const
	{
		if (!m_IsVisible)
			return;

		platform->FillRect(m_GlobalPos, m_Size, theme.panelBackground);
		platform->DrawRect(m_GlobalPos, m_Size, theme.border);

		if (m_ShowTitleBar)
		{
			platform->FillRect(m_GlobalPos, { m_Size.x, TITLE_BAR_WIDTH }, theme.titleBar);

			if (m_ShowTitle)
				platform->DrawText(m_GlobalPos + Vector2i(2, TITLE_BAR_WIDTH / 2 - 2), m_Title, theme.textTitle);
		}

		Component::Draw(platform, theme);
	}

	void Panel::ShowTitleBar(bool enable)
	{
		m_ShowTitleBar = enable;
		if (!enable) m_ShowTitle = false;
	}

	void Panel::ShowTitle(bool enable)
	{
		m_ShowTitle = enable;
	}

	void Panel::FixPos(bool enable)
	{
		m_FixedPos = enable;
	}
	Manager::Manager() : m_Platform(nullptr)
	{}

	Manager::Manager(Platform* platform) : m_Platform(platform)
	{}

	Manager::~Manager()
	{
		delete m_Platform;
	}

	void Manager::Update()
	{
		for (auto& panel : m_Panels)
			panel.Update(m_Platform);
	}

	void Manager::Draw(const Theme& theme)
	{
		for (auto& panel : m_Panels)
			panel.Draw(m_Platform, theme);
	}

	Panel* Manager::AddPanel(const std::string& title, const Vector2i& pos, const Vector2i& size)
	{
		m_Panels.push_back(Panel(nullptr, title, pos, size));
		return &m_Panels.back();
	}

	void Manager::SetPlatform(Platform* platform)
	{
		m_Platform = platform;
	}
	Label::Label(Component* parent) : Component(parent)
	{
	}

	Label::Label(Component* parent, const std::string& text, const Vector2i& pos, const Vector2i& size)
		: Component(parent)
	{
		m_Text = text;

		SetPos(pos);
		SetSize(size);
	}

	Label::~Label()
	{
	}

	const std::string& Label::GetText() const
	{
		return m_Text;
	}

	void Label::SetText(const std::string& text)
	{
		m_Text = text;
		SetTextAlign(m_Align);
	}

	bool Label::Update(Platform* platform)
	{
		if (!m_Update)
			return false;

		UpdateText();
		return Component::Update(platform);
	}

	void Label::Draw(Platform* platform, const Theme& theme) const
	{
		if (!m_IsVisible)
			return;

		platform->FillRect(m_GlobalPos, m_Size, theme.componentBackground);
		platform->DrawRect(m_GlobalPos, m_Size, theme.border);

		size_t end = std::min((size_t)m_CharsSize.y, m_TextSplitted.size());

		for (size_t i = 0; i < end; i++)
		{
			auto& unit = m_TextSplitted[i];

			Vector2i pos = m_GlobalPos + unit.offset;
			pos.y += Platform::CHAR_SIZE.y * i;

			platform->DrawText(pos, unit.text, theme.textRegular);
		}

		Component::Draw(platform, theme);
	}

	Vector2i Label::GetSize() const
	{
		return m_CharsSize;
	}

	void Label::SetSize(const Vector2i& size)
	{
		m_CharsSize = size;
		m_Size = { size.x * Platform::CHAR_SIZE.x + 4, size.y * Platform::CHAR_SIZE.y + 2 };
	}

	Align Label::GetTextAlign() const
	{
		return m_TextAlign;
	}

	void Label::SetTextAlign(Align align)
	{
		m_TextAlign = align;
		m_ForceUpdateOffset = true;
	}

	void Label::UpdateTextPos(const std::vector<std::string>& lines)
	{
		m_TextSplitted.clear();
		m_TextSplitted.resize(lines.size());

		for (size_t i = 0; i < lines.size(); i++)
		{
			auto& unit = m_TextSplitted[i];

			unit.text = lines[i];

			int length = unit.text.length();

			switch (m_TextAlign)
			{
			case Align::LEFT:   unit.offset = { 0, 0 };                             break;
			case Align::CENTRE: unit.offset = { m_Size.x / 2 - length * 4 - 2, 0 }; break;
			case Align::RIGHT:  unit.offset = { m_Size.x - length * 8 - 2, 0 };     break;
			}

			unit.offset += 2;
		}
	}

	void Label::SplitTextIntoLines(std::vector<std::string>& lines)
	{
		if (m_Text.empty())
			return;

		if (m_Text.find('\n') == std::string::npos)
			lines.push_back(m_Text);
		else
		{
			std::string buffer;

			for (auto c : m_Text)
			{
				if (c == '\n')
				{
					lines.push_back(buffer);
					buffer.clear();
				}
				else
					buffer += c;
			}

			lines.push_back(buffer);
		}
	}

	void Label::UpdateText()
	{
		if (m_ForceUpdateOffset)
		{
			std::vector<std::string> lines;

			SplitTextIntoLines(lines);
			UpdateTextPos(lines);

			m_ForceUpdateOffset = false;
		}
	}
	Button::Button(Component* parent) : Label(parent)
	{
	}

	Button::Button(Component* parent, const std::string& text, const Vector2i& pos, const Vector2i& size)
		: Label(parent, text, pos, size)
	{
	}

	Button::~Button()
	{
	}

	bool Button::Update(Platform* platform)
	{
		return Label::Update(platform);
	}

	void Button::Draw(Platform* platform, const Theme& theme) const
	{
		if (!m_IsVisible)
			return;

		if (m_EnableLight)
		{
			platform->FillRect(m_GlobalPos, m_Size, theme.ApplyLight(theme.componentBackground));
			platform->DrawRect(m_GlobalPos, m_Size, theme.ApplyLight(theme.border));
		}
		else
		{
			platform->FillRect(m_GlobalPos, m_Size, theme.componentBackground);
			platform->DrawRect(m_GlobalPos, m_Size, theme.border);
		}

		for (size_t i = 0; i < m_TextSplitted.size(); i++)
		{
			auto& unit = m_TextSplitted[i];

			Vector2i pos = m_GlobalPos + unit.offset;
			pos.y += Platform::CHAR_SIZE.y * i;

			if (m_EnableLight)
				platform->DrawText(pos, unit.text, theme.ApplyLight(theme.textRegular));
			else
				platform->DrawText(pos, unit.text, theme.textRegular);
		}

		Component::Draw(platform, theme);
	}
	TextEntry::TextEntry(Component* parent)
		: Label(parent), m_CursorPos(0), m_Ticks(0.0f)
	{
	}

	TextEntry::TextEntry(Component* parent, const Vector2i& pos, const Vector2i& size, const std::string& text, const std::string& placeholder)
		: Label(parent, text, pos, size), m_Placeholder(placeholder), m_CursorPos(0), m_Ticks(0.0f)
	{
	}

	TextEntry::~TextEntry()
	{
	}

	void TextEntry::SetPlaceholder(const std::string& placeholder)
	{
		m_Placeholder = placeholder;
	}

	const std::string& TextEntry::GetPlaceholder() const
	{
		return m_Placeholder;
	}

	bool TextEntry::Update(Platform* platform)
	{
		if (!m_Update)
			return false;

		if (m_IsFocused)
		{
			using KeyType = HardwareButton::KeyType;

			bool isUp = platform->GetKey(KeyType::LEFT_SHIFT).held || platform->GetKey(KeyType::RIGHT_SHIFT).held || platform->IsCaps();

			if (m_Text.size() < m_CharsSize.x)
			{
				for (const auto& [key, chars] : s_PickedKeyboard)
					if (platform->GetKey(key).pressed)
					{
						m_Text.insert(m_CursorPos, 1, (platform->IsCaps() || isUp) ? chars.second : chars.first);
						m_CursorPos++;
					}
			}

			if (platform->GetKey(KeyType::BACKSPACE).pressed)
			{
				if (m_CursorPos > 0)
				{
					m_Text.erase(m_CursorPos - 1, 1);
					m_CursorPos--;
				}
			}

			if (platform->GetKey(KeyType::DEL).pressed)
			{
				if (m_CursorPos < m_Text.length())
					m_Text.erase(m_CursorPos, 1);
			}

			if (platform->GetKey(KeyType::LEFT).pressed)
			{
				if (m_CursorPos > 0)
					m_CursorPos--;
			}

			if (platform->GetKey(KeyType::RIGHT).pressed)
			{
				if (m_CursorPos < m_Text.length())
					m_CursorPos++;
			}

			if (platform->GetKey(KeyType::ENTER).pressed)
				HandleEvent(this, { Event::Component_Confirm });

			SetText(m_Text);
			UpdateText();

			if (m_Ticks < 2.0f * CURSOR_HIDE_DELAY)
				m_Ticks += platform->GetDeltaTime();
			else if (m_Ticks >= 2.0f * CURSOR_HIDE_DELAY)
				m_Ticks = 0.0f;
		}

		return Component::Update(platform);
	}

	void TextEntry::Draw(Platform* platform, const Theme& theme) const
	{
		if (!m_IsVisible)
			return;

		if (m_EnableLight)
		{
			platform->FillRect(m_GlobalPos, m_Size, theme.ApplyLight(theme.componentBackground));
			platform->DrawRect(m_GlobalPos, m_Size, theme.ApplyLight(theme.border));
		}
		else
		{
			platform->FillRect(m_GlobalPos, m_Size, theme.componentBackground);
			platform->DrawRect(m_GlobalPos, m_Size, theme.border);
		}

		if (m_TextSplitted.empty())
		{
			Vector2i pos = m_GlobalPos + 2;

			if (m_EnableLight)
				platform->DrawText(pos, m_Placeholder, theme.ApplyLight(theme.placeholder));
			else
				platform->DrawText(pos, m_Placeholder, theme.placeholder);
		}
		else
		{
			for (size_t i = 0; i < m_TextSplitted.size(); i++)
			{
				auto& unit = m_TextSplitted[i];

				Vector2i pos = m_GlobalPos + unit.offset;
				pos.y += Platform::CHAR_SIZE.y * i;

				if (m_EnableLight)
					platform->DrawText(pos, unit.text, theme.ApplyLight(theme.textRegular));
				else
					platform->DrawText(pos, unit.text, theme.textRegular);
			}
		}

		if (m_IsFocused && m_Ticks >= CURSOR_HIDE_DELAY)
		{
			Vector2i cursor = { m_GlobalPos.x + m_CursorPos * Platform::CHAR_SIZE.x + 2, m_GlobalPos.y + 1 };

			platform->DrawLine(cursor, { cursor.x, cursor.y + Platform::CHAR_SIZE.y }, theme.cursor);
		}

		Component::Draw(platform, theme);
	}

	void TextEntry::SetCursorPos(uint32_t pos)
	{
		m_CursorPos = pos;
	}

	uint32_t TextEntry::GetCursorPos() const
	{
		return m_CursorPos;
	}
	
	std::unordered_map<TextEntry::KeyType, std::pair<char, char>> TextEntry::s_KeyboardUS =
	{
		{ KeyType::SPACE, { ' ', ' ' } }, { KeyType::APOSTROPHE, { '\'', '"' } },
		{ KeyType::COMMA, { ',', '<' } }, { KeyType::MINUS, { '-', '_' } },
		{ KeyType::PERIOD, { '.', '>' } }, { KeyType::SLASH, { '/', '?' } },
		{ KeyType::K0, { '0', ')' } }, { KeyType::K1, { '1', '!' } },
		{ KeyType::K2, { '2', '@' } }, { KeyType::K3, { '3', '#' } },
		{ KeyType::K4, { '4', '$' } }, { KeyType::K5, { '5', '%' } },
		{ KeyType::K6, { '6', '^' } }, { KeyType::K7, { '7', '&' } },
		{ KeyType::K8, { '8', '*' } }, { KeyType::K9, { '9', '(' } },
		{ KeyType::SEMICOLON, { ';', ':' } }, { KeyType::EQUAL, { '=', '+' } },
		{ KeyType::A, { 'a', 'A' } }, { KeyType::B, { 'b', 'B' } },
		{ KeyType::C, { 'c', 'C' } }, { KeyType::D, { 'd', 'D' } },
		{ KeyType::E, { 'e', 'E' } }, { KeyType::F, { 'f', 'F' } },
		{ KeyType::G, { 'g', 'G' } }, { KeyType::H, { 'h', 'H' } },
		{ KeyType::I, { 'i', 'I' } }, { KeyType::J, { 'j', 'J' } },
		{ KeyType::K, { 'k', 'K' } }, { KeyType::L, { 'l', 'L' } },
		{ KeyType::M, { 'm', 'M' } }, { KeyType::N, { 'n', 'N' } },
		{ KeyType::O, { 'o', 'O' } }, { KeyType::P, { 'p', 'P' } },
		{ KeyType::Q, { 'q', 'Q' } }, { KeyType::R, { 'r', 'R' } },
		{ KeyType::S, { 's', 'S' } }, { KeyType::T, { 't', 'T' } },
		{ KeyType::U, { 'u', 'U' } }, { KeyType::V, { 'v', 'V' } },
		{ KeyType::W, { 'w', 'W' } }, { KeyType::X, { 'x', 'X' } },
		{ KeyType::Y, { 'y', 'Y' } }, { KeyType::Z, { 'z', 'Z' } },
		{ KeyType::LEFT_BRACKET, { '[', '{' } }, { KeyType::BACKSLASH, { '\\', '|' } },
		{ KeyType::RIGHT_BRACKET, { ']', '}' } },
		{ KeyType::NP_0, { '0', '0' } }, { KeyType::NP_1, { '1', '1' } },
		{ KeyType::NP_2, { '2', '2' } }, { KeyType::NP_3, { '3', '3' } },
		{ KeyType::NP_4, { '4', '4' } }, { KeyType::NP_5, { '5', '5' } },
		{ KeyType::NP_6, { '6', '6' } }, { KeyType::NP_7, { '7', '7' } },
		{ KeyType::NP_8, { '8', '8' } }, { KeyType::NP_9, { '9', '9' } },
		{ KeyType::NP_DIVIDE, { '/', '/' } }, { KeyType::NP_MULTIPLY, { '*', '*' } },
		{ KeyType::NP_SUBTRACT, { '-', '-' } }, { KeyType::NP_ADD, { '+', '+' } },
		{ KeyType::NP_EQUAL, { '=', '+' } }
	};

	std::unordered_map<TextEntry::KeyType, std::pair<char, char>>& TextEntry::s_PickedKeyboard = TextEntry::s_KeyboardUS;
	template <class T>
	Slider<T>::Slider(Component* parent, const Vector2i& start, const Vector2i& end, const Vector2i& size, const T& min_value, const T& max_value, const T& value)
		: Component(parent), m_MinValue(min_value), m_MaxValue(max_value), m_Value(value), m_LocalEndPos(end), m_Held(false)
	{
		m_Size = size;
		SetPos(start);

		m_GlobalEndPos = LocalToGlobalPos(parent, end);
		UpdateSliderPos();
	}

	template <class T>
	bool Slider<T>::Update(Platform* platform)
	{
		Vector2i mousePos = platform->GetMousePos();
		HardwareButton mouse_leftButtonState = platform->GetMouseButton(HardwareButton::ButtonType::LEFT);

		bool light = false;

		if (IsPointInRect(mousePos, m_SliderPos, m_Size))
		{
			HandleEvent(this, { Event::Mouse_Hover });

			if (mouse_leftButtonState.pressed)
			{
				m_IsFocused = true;
				HandleEvent(this, { Event::Component_Focus });
			}

			light = true;
		}
		else
		{
			if (mouse_leftButtonState.pressed && m_IsFocused)
			{
				m_IsFocused = false;
				HandleEvent(this, { Event::Component_Unfocus });
			}
		}

		if (m_IsFocused)
		{
			if (mouse_leftButtonState.held)
			{
				Vector2d diff = m_LocalEndPos - m_LocalPos;
				double t = diff.DotProduct(mousePos - m_GlobalPos) / double(diff.Length2());

				m_Value = t * double(m_MaxValue - m_MinValue) + m_MinValue;

				if (m_Value < m_MinValue) m_Value = m_MinValue;
				if (m_Value > m_MaxValue) m_Value = m_MaxValue;
			}
		}

		return light;
	}

	template <class T>
	void Slider<T>::Draw(Platform* platform, const Theme& theme) const
	{
		if (!m_IsVisible)
			return;

		platform->DrawLine(m_GlobalPos, m_GlobalEndPos, theme.slider);

		platform->FillRect(m_SliderPos, m_Size, theme.componentBackground);
		platform->DrawRect(m_SliderPos, m_Size, theme.border);

		Component::Draw(platform, theme);
	}

	template <class T>
	T Slider<T>::GetValue() const { return m_Value; }

	template <class T>
	T Slider<T>::GetMaxValue() const { return m_MaxValue; }

	template <class T>
	T Slider<T>::GetMinValue() const { return m_MinValue; }

	template <class T>
	void Slider<T>::SetValue(const T& value) { m_Value = value; }
	
	template <class T>
	void Slider<T>::SetMaxValue(const T& value) { m_MaxValue = value; }
	
	template <class T>
	void Slider<T>::SetMinValue(const T& value) { m_MinValue = value; }

	template <class T>
	void Slider<T>::UpdateSliderPos()
	{
		const Vector2i offset =
			(m_LocalEndPos - m_LocalPos) * (m_Value - m_MinValue) / (m_MaxValue - m_MinValue);

		m_SliderPos = LocalToGlobalPos(m_Parent, m_LocalPos - m_Size / 2 + offset);
	}

	template <class T>
	void Slider<T>::UpdatePos()
	{
		Component::UpdatePos();

		m_GlobalPos = LocalToGlobalPos(m_Parent, m_LocalPos);
		m_GlobalEndPos = LocalToGlobalPos(m_Parent, m_LocalEndPos);

		UpdateSliderPos();
	}
	ListNode::ListNode(Component* parent) : Label(parent)
	{
		Initialise();
	}

	ListNode::ListNode(Component* parent, int width, int index, const std::string& text)
		: Label(parent, text, {}, { width, 1 })
	{
		m_Index = index;
		Initialise();
	}

	bool ListNode::Update(Platform* platform)
	{
		if (!m_TextSplitted.empty())
		{
			auto& unit = m_TextSplitted[0];

			m_GlobalPos.y += Platform::CHAR_SIZE.y * (m_Index - m_Offset) + unit.offset.y;
			m_GlobalPos.x += unit.offset.x;
		}

		return Label::Update(platform);
	}

	void ListNode::Draw(Platform* platform, const Theme& theme) const
	{
		if (!m_IsVisible)
			return;

		if (!m_TextSplitted.empty())
		{
			auto& unit = m_TextSplitted[0];

			if (m_EnableLight)
			{
				int sizeX = m_Size.x - 6;
				platform->FillRect(m_GlobalPos, { sizeX, m_Size.y }, theme.ApplyLight(theme.componentBackground));
			}

			platform->DrawText(m_GlobalPos, unit.text, theme.textRegular);
		}

		Component::Draw(platform, theme);
	}

	void ListNode::SetIndex(int index)
	{
		m_Index = index;
	}

	int ListNode::GetIndex() const
	{
		return m_Index;
	}

	void ListNode::UpdatePos()
	{
		m_GlobalPos = m_LocalPos;
		m_GlobalPos.x++;

		if (m_Parent)
			m_GlobalPos += m_Parent->GetGlobalPos();
	}

	void ListNode::SetOffset(int offset)
	{
		m_Offset = offset;
	}

	void ListNode::Initialise()
	{
		m_ForceUpdateOffset = true;
	}

	List::List(Component* parent, bool constructSlider) : Panel(parent)
	{
		Initialise(constructSlider);
	}

	List::List(Component* parent, const Vector2i& pos, const Vector2i& size, bool constructSlider)
		: Panel(parent, "", pos, {})
	{
		Initialise(constructSlider, size);
	}

	List::~List()
	{
	}

	void List::Initialise(bool constructSlider, const Vector2i& size)
	{
		ShowTitleBar(false);
		FixPos(true);
		SetSize(size);

		if (constructSlider)
			ConstructSlider();
	}

	void List::AddString(const std::string& data)
	{
		m_Nodes.push_back(new ListNode(this, m_SizeInNodes.x, m_Nodes.size(), data));

		if (m_Slider && m_Resizable)
		{
			bool isOverflow = m_Nodes.size() + 1 > m_SizeInNodes.y;

			if (isOverflow)
				m_Slider->SetMaxValue(m_Nodes.size() - 1);

			m_Slider->Show(isOverflow);
		}
	}

	bool List::Update(Platform* platform)
	{
		if (!m_Update)
			return false;

		UpdateText();

		Vector2i itemSize = { m_Size.x, Platform::CHAR_SIZE.y };

		Vector2i mousePos = platform->GetMousePos();
		HardwareButton mouseLeft = platform->GetMouseButton(HardwareButton::ButtonType::LEFT);

		for (size_t i = 0; i < m_Nodes.size(); i++)
		{
			if (mouseLeft.released)
			{
				Vector2i pos = m_Nodes[i]->GetPos();
				pos.y += (int)i * Platform::CHAR_SIZE.y;

				if (IsPointInRect(mousePos, m_GlobalPos + pos, itemSize))
				{
					m_SelectedItem = i;

					HandleEvent(this, Event::Component_Select);
					break;
				}
			}
		}
		
		return Panel::Update(platform);
	}

	void List::Draw(Platform* platform, const Theme& theme) const
	{
		Panel::Draw(platform, theme);
	}

	void List::EnableResize(bool enable)
	{
		m_Resizable = enable;

		if (m_Slider)
		{
			m_Slider->Show(enable);
			m_Slider->EnableUpdate(enable);
		}
	}

	void List::SetSize(const Vector2i& size)
	{
		m_Size = { size.x * Platform::CHAR_SIZE.x + 4, size.y * Platform::CHAR_SIZE.y + 2 };
		m_SizeInNodes = size;
	}

	ListNode* List::GetSelected()
	{
		return m_Nodes[m_SelectedItem];
	}

	void List::ConstructSlider()
	{
		int width = (float)m_Size.x * 0.05f;
		int x = m_Size.x - width;

		m_Slider = new Slider<int>(this, { x, 1 + width / 2 }, { x, m_Size.y - width / 2 - 1 }, { width, width }, 0, m_SizeInNodes.y);
		m_Slider->Show(false);
	}

	void List::UpdateText()
	{
		if (m_Slider)
		{
			int offset = m_Slider->GetValue();
			
			for (auto node : m_Nodes)
			{
				int pos = node->GetIndex() - offset;

				node->SetOffset(offset);
				node->Show(pos >= 0 && pos < m_SizeInNodes.y);
			}
		}
	}

	void List::Clear()
	{
		m_Nodes.clear();

		m_Slider->Show(false);
		m_Slider->SetMaxValue(1);

		m_Children.erase(std::next(m_Children.begin()), m_Children.end());
	}
#endif
}

#endif
