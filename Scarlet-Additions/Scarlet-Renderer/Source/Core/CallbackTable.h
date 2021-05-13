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

			std::function<void(std::any _any, Args&&... args)> function = [](std::any _any, Args&&... args) {
				T _t = std::any_cast<T>(_any);
				_t(args...);
			};

			m_RunFunc = function;
		}

		template<typename... Args>
		void Run(Args&&... args)
		{
			auto func = std::any_cast<std::function<void(std::any _any, Args&&... args)>>(m_RunFunc);
			func(m_Data, args...);
		}

	private:
		std::any m_Data;
		std::any m_RunFunc;
	};

	struct CallbackTable
	{
	public:
		//using EventCallbackFn = std::function<void()>;

		//template<typename... Types>
		//using Tuple = std::tuple<Types...>;

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