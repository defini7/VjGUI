#pragma once

#include <list>
#include <any>

namespace def::gui
{
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
}
