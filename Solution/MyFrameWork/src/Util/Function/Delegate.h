#pragma once

#include <functional>
#include <vector>
#include <algorithm>

#include "Util/Type/TypeTraits.h"

template<class TFunc>
class Delegate;

template<class Ret, class... Args>
class Delegate<Ret(Args...)> {
	using Func = std::function<Ret(Args...)>;
	struct FuncObj {
		using Key = std::pair<void*, void*>;
		Func _func;
		Key _key;
		// emplace back利用
		FuncObj(const Func& func, void* k1 = nullptr, void* k2 = nullptr)
			: _func(func), _key(k1, k2) {}
		Ret operator () (Args&&... args) const {
			return _func(args...);
		}
	};
public:
	Delegate() = default;

	// 非メンバ関数
	template<class F>
	void Add(F* f) {
		auto&& lambda = [f](Args... args) -> Ret {
			return (*f)(std::forward<Args>(args)...);
		};
		_funcs.emplace_back(lambda, f);
	}

	// メンバ関数
	template <class F, class Ins>
	void Add(Ins& i, F f) {
		auto&& lambda = [f, &i](Args... args) -> Ret {
			return (i.*f)(args...);
		};
		_funcs.emplace_back(lambda, &f, &i);
	}

	// 関数オブジェクト
	template <class FObj>
	void Add(FObj&& f) {
		using f_Ret = typename ::result_of<FObj, Args...>::type;
		f_Ret fr;
		static_assert(std::is_same<Ret, f_Ret>::value, "faild delegate.add(FObj)");
		void* fp = if_rvalue_null::check(std::forward<FObj>(f));
		_funcs.emplace_back(std::forward<FObj>(f), fp);
	}

	Ret operator ()(Args&&... args) const {
		int size = _funcs.size();
		int loop = size - 1;
		for (int i = 0; i < loop; ++i)
		{
			_funcs[i](args...);
		}
		return _funcs[loop](std::forward<Args...>(args...));
	}
private:
	std::vector<FuncObj> _funcs;
};

using TFunc = std::string(std::string&);