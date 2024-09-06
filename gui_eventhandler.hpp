#pragma once

#include <list>

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

		// TODO: Add more events and
		// some event specific stuff
	};

	template <class T>
	using EventHandlerFunc = void (*)(T*, const Event&, void*);

	template <class T>
	class EventHandler
	{
	public:
		void SetEventHandler(EventHandlerFunc<T> func, void* userData = nullptr)
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
		void* m_UserData = nullptr;

	};
}
