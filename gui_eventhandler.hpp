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
			Mouse_Hover
		} type;

		// TODO: Add more events and
		// some event specific stuff
	};

	template <class T>
	using EventHandlerFunc = void (*)(T*, const Event&);

	template <class T>
	class EventHandler
	{
	public:
		void SetEventHandler(EventHandlerFunc<T> func)
		{
			m_EventHandlerFunc = func;
		}

		EventHandlerFunc<T> GetEventHandler() const
		{
			return m_EventHandlerFunc;
		}
		
	private:
		EventHandlerFunc<T> m_EventHandlerFunc = nullptr;

	};
}
