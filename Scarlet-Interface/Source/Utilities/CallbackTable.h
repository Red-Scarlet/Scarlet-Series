#pragma once
#include <ScarletInterface.h>
#include <typeindex>

namespace ScarletInterface {

	template<typename T>
	class SCARLET_INTERFACE_API CallbackWrapper
	{
	public:
		template<typename F, typename... Args>
		void Bind(F f)
		{
			m_Types.insert(m_Types.end(), { typeid(Args)... });

			Function<Ref<T>(AnyData _Any, Args&&... args)> function = [](AnyData _Any, Args&&... args) {
				F _f = AnyCast<F>(_Any);
				return _f(args...);
			};

			m_Data = f;
			m_Function = function;
		}

		template<typename... Args>
		AnyData Run(Args&&... args)
		{
			auto func = AnyCast<Function<Ref<T>(AnyData _Any, Args&&... args)>>(m_Function);
			return func(m_Data, args...);
		}

	public:
		Vector<std::type_index> m_Types;
		AnyData m_Data;
		AnyData m_Function;
	};

	template<typename T>
	struct SCARLET_INTERFACE_API CallbackTable
	{
	public:
		CallbackTable() = default;
		virtual ~CallbackTable() = default;

		bool Empty()
		{
			return m_Callbacks.empty();
		}

		template<typename... Args>
		Ref<T> Create(Args&&... args)
		{
			Vector<std::type_index> types;
			types.insert(types.end(), { typeid(Args)... });

			for (CallbackWrapper<T> wrapper : m_Callbacks)
			{
				if (wrapper.m_Types == types) {
					AnyData func = wrapper.Run<Args...>(std::forward<Args>(args)...);
					return AnyCast<Ref<T>>(func);
				}
			}

			return nullptr;
		}

		void Push(CallbackWrapper<T> _Callback)
		{
			m_Callbacks.push_back(_Callback);
		}

	private:
		Vector<CallbackWrapper<T>> m_Callbacks;

	public:
		static Ref<CallbackTable<T>> Create() { return CreateRef<CallbackTable<T>>(); }
	};

}