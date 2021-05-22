#pragma once

#include <vector>
#include <string>
#include <memory>
#include <cstddef>
#include <functional>
#include <optional>
#include <any>
#include <unordered_map>
#include <bitset>
#include <queue>
#include <array>
#include <ostream>
#include <map>
#include <tuple>
#include <set>
#include <variant>
#include <iterator>
#include <typeinfo>

#include "Utilities/Log.h"

#ifdef SCARLET_INTERFACE_EXPORT
#define SCARLET_INTERFACE_API __declspec(dllexport)
#else
#define SCARLET_INTERFACE_API __declspec(dllimport)
#endif

#define SCARLET_ERROR false
#define SCARLET_INTERFACE_ASSERTS
#ifdef SCARLET_INTERFACE_ASSERTS
#define SCARLET_INTERFACE_ASSERT(x, ...) { if(!(x)) { SCARLET_INTERFACE_ERROR(__VA_ARGS__); __debugbreak(); }}
#else
#define SCARLET_INTERFACE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define SCARLET_INTERFACE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace ScarletInterface {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{ return std::make_unique<T>(std::forward<Args>(args)...); }

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{ return std::make_shared<T>(std::forward<Args>(args)...); }

	template<typename T>
	using ParentRef = std::enable_shared_from_this<T>;
	
	template<typename T, typename ... Args>
	constexpr Ref<T> CastRef(Args&& ... args)
	{ return std::dynamic_pointer_cast<T>(std::forward<Args>(args)...); }

	using AnyData = std::any;
	template<typename T, typename... Args>
	constexpr T AnyCast(Args&&... args)
	{ 
		const char* typeName = typeid(T).name();
		return std::any_cast<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	constexpr inline T operator~ (T a) { return static_cast<T>(~static_cast<std::underlying_type<T>::type>(a)); }
	template<typename T>
	constexpr inline T operator| (T a, T b) { return static_cast<T>(static_cast<std::underlying_type<T>::type>(a) | static_cast<std::underlying_type<T>::type>(b)); }
	template<typename T>
	constexpr inline T operator& (T a, T b) { return static_cast<T>(static_cast<std::underlying_type<T>::type>(a) & static_cast<std::underlying_type<T>::type>(b)); }
	template<typename T>
	constexpr inline T operator^ (T a, T b) { return static_cast<T>(static_cast<std::underlying_type<T>::type>(a) ^ static_cast<std::underlying_type<T>::type>(b)); }
	template<typename T>
	constexpr inline T& operator|= (T& a, T b) { return reinterpret_cast<T&>(reinterpret_cast<std::underlying_type<T>::type&>(a) |= static_cast<std::underlying_type<T>::type>(b)); }
	template<typename T>
	constexpr inline T& operator&= (T& a, T b) { return reinterpret_cast<T&>(reinterpret_cast<std::underlying_type<T>::type&>(a) &= static_cast<std::underlying_type<T>::type>(b)); }
	template<typename T>
	constexpr inline T& operator^= (T& a, T b) { return reinterpret_cast<T&>(reinterpret_cast<std::underlying_type<T>::type&>(a) ^= static_cast<std::underlying_type<T>::type>(b)); }

	template<typename T>
	using Function = std::function<T>;
	template<typename T>
	using List = std::list<T>;
	template<typename T>
	using InitializerList = std::initializer_list<T>;
	template<typename T>
	using Vector = std::vector<T>;
	template<typename K, typename T>
	using Map = std::map<K, T>;

	template<typename... Types>
	using Tuple = std::tuple<Types...>;

	template<typename... Types>
	using Tuple = std::tuple<Types...>;

	template <typename T>
	Vector<T> operator+(const Vector<T>& A, const Vector<T>& B)
	{
		Vector<T> C;
		C.reserve(A.size() + B.size());
		C.insert(C.end(), A.begin(), A.end());
		C.insert(C.end(), B.begin(), B.end());
		return C;
	}

	template <typename T>
	Vector<T>& operator+=(Vector<T>& A, const Vector<T>& B)
	{
		A.reserve(A.size() + B.size());
		A.insert(A.end(), B.begin(), B.end());
		return A;
	}

	template<typename T, std::size_t length>
	using Array = std::array<T, length>;
	template<std::size_t S>
	using Bitset = std::bitset<S>;
	template<typename T>
	using Queue = std::queue<T>;
	template<typename T>
	using Vector2D = Vector<Vector<T>>;
	template<typename T>
	using Optional = std::optional<T>;
	template<typename T>
	using Variant = std::variant<T>;
	template<typename T, typename R>
	using Pair = std::pair<T, R>;
	template<typename T, typename R>
	using UnorderedMap = std::unordered_map<T, R>;
	template<typename T>
	using Set = std::set<T>;
	using String = std::string;
	using Ostream = std::ostream;

	template<typename... Args>
	constexpr String ToString(Args&&... args)
	{ return std::to_string(std::forward<Args>(args)...); }

	template<typename Args>
	constexpr String GetString(Args&& args)
	{ String str = args; return str; }

	typedef std::uint64_t uint64;
	typedef std::uint32_t uint32;
	typedef std::uint16_t uint16;
	typedef std::uint8_t uint8;

	typedef std::int64_t int64;
	typedef std::int32_t int32;
	typedef std::int16_t int16;
	typedef std::int8_t int8;

	typedef double float64;
	typedef float float32;

	typedef float64** pfloat64;
	typedef float32** pfloat32;

	typedef char* char_ptr;
	typedef const char* cchar_ptr;

	template<typename Args>
	constexpr String ReadAddress(Args&& args)
	{
		std::stringstream ReadStream;
		ReadStream << std::forward<Args>(args);
		return ReadStream.str();
	}

	template<typename T>
	constexpr const char* GetType()
	{
		return typeid(T).name();
	}

}

#define uint64_max std::numeric_limits<ScarletInterface::uint64>::max()
#define uint32_max std::numeric_limits<ScarletInterface::uint32>::max()
#define uint16_max std::numeric_limits<ScarletInterface::uint16>::max()
#define uint8_max std::numeric_limits<ScarletInterface::uint8>::max()

