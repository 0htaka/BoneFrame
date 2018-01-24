#pragma once

#include<memory>

template<typename T>
// 参照先を変更可能な const*(new deleteができない)
class RefPtr {
public:
	template<typename ...Args>
	static RefPtr& make_refptr(Args&& ...args) {
		p = new T(std::forward<Args>(args)...);
	}
public:
	RefPtr(T* ptr = nullptr) : p(ptr) {
	}
	// 代入演算子
	RefPtr<T>& operator = (T*& other) {
		p = other;
		return *this;
	}
	//ポインタ取得
	T* get() const {
		return p;
	}
	T& operator * () {
		return *p;
	}
	// アロー演算子
	T& operator -> () {
		return *p;
	}
	//ポインタ操作	
	T& operator ++ () {
		return ++p;
	}
	T& operator -- () {
		return --p;
	}
	T& operator ++ (int) {
		return p++;
	}
	T& operator -- (int) {
		return p--;
	}
	//配列操作
	T& operator[](const int i) {
		return p[i]
	}
	// bool
	operator bool() {
		return p;
	}
	bool operator ! () {
		return !p;
	}
	bool operator == (T* other) {
		p == other;
	}
	bool operator != (T* other) {
		p != other;
	}	
private:
	T* p;
};