#pragma once

#include <list>
#include <any>

namespace def::gui
{
	struct Event
	{
		enum class Type
		{
			None,
			Mouse_Pressed,
			Mouse_Held,
			Mouse_Released,
			Mouse_Hover,
			Component_Focused,
			Component_Unfocused,
			Component_Confirm
		} type;

		Event(const Type type = Type::None) : type(type)
		{

		}

		// TODO: Add more events and
		// some event specific stuff
	};

	template <class T>
	using EventHandlerFunc = void (*)(T*, const Event&, const std::any&);

	template <class T>
	class EventHandler
	{
	public:
		void SetEventHandler(EventHandlerFunc<T> func, const std::any& userData = nullptr)
		{
			m_EventHandlerFunc = func;
			m_UserData = userData;
		}

		void HandleEvent(T* component, const Event& event)
		{
			if (m_EventHandlerFunc)
				m_EventHandlerFunc(component, event, m_UserData);
		}
		
	private:
		EventHandlerFunc<T> m_EventHandlerFunc = nullptr;
		std::any m_UserData = nullptr;

	};
}
