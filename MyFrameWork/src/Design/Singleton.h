#pragma once

template<typename T>
class Singleton {
public:
	static T& Ins() {
		static T ins;
		return ins;
	}

	//ÉRÉsÅ[ã÷é~
	Singleton(const T&) = delete;
	T& operator =(const T&) = delete;
protected:
	Singleton() = default;
	~Singleton() = default;
};