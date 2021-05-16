// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// ResourceCallbackTable.h 10/05/2021 - Component Struct.
#pragma once

#include <ScarletInterface.h>

namespace Renderer {

	using namespace ScarletInterface;

	struct CallbackWrapper
	{
	public:
		template<typename T, typename... Args>
		void Bind(T t)
		{
			m_Data = t;

			Function<void(AnyData _Any, Args&&... args)> function = [](AnyData _Any, Args&&... args) {
				T _t = AnyCast<T>(_Any);
				_t(args...);
			};

			m_RunFunc = function;
		}

		template<typename... Args>
		void Run(Args&&... args)
		{
			auto func = AnyCast<Function<void(AnyData _Any, Args&&... args)>>(m_RunFunc);
			func(m_Data, args...);
		}

	private:
		AnyData m_Data;
		AnyData m_RunFunc;
	};

	struct CallbackTable
	{
	public:
		bool Empty()
		{
			return m_Callbacks.empty();
		}

		template<typename... Args>
		void Call(const String& _Name, Args&&... args)
		{
			if (m_Callbacks.empty())
			{
				std::cout << "Callback Error: Table is empty!" << std::endl;
				return;
			}
			
			for (auto Call : m_Callbacks)
			{
				if (std::get<0>(Call) == _Name)
				{
					CallbackWrapper wrapper = std::get<1>(Call);
					wrapper.Run<Args...>(std::forward<Args>(args)...);
					return;
				} 
			}
			
			std::cout << "Callback Error: Could not find " << _Name << " Call!" << std::endl;
		}

		void Push(const String& _Name, CallbackWrapper _Callback)
		{ 
			m_Callbacks.push_back({ _Name, _Callback });
		}

	private:
		Vector<Tuple<String, CallbackWrapper>> m_Callbacks;
	};

}