#pragma once

#include <type_traits>

struct if_rvalue_null {
	template<class T>
	static constexpr T* check(T& t) { return  &t; }
	template<class T>
	static constexpr T* check(T&& t) { return nullptr; }
};

//template<class T>
//struct if_rvalueT_T {
//	using type = typename std::conditional_t<std::is_rvalue_reference_v<T>, std::remove_reference_t<T>, T>;
//};
//template<class T>
//using if_rvalueT_T_t = typename if_rvalueT_T<T>::type;

template<class TFunc, class... Args>
struct result_of
{
	static constexpr auto check(TFunc f, Args... args)->decltype(f(std::forward<Args>(args)...));
	//static constexpr auto check(TFunc f, Args... args)->decltype(std::forward<decltype(f(std::forward<Args>(args)...))>(f(std::forward<Args>(args)...)));
	static constexpr std::false_type check(...);
	using type = decltype(check(std::declval<TFunc>(), (std::declval<Args...>())));
};