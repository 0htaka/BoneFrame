#pragma once

#include<memory>

template<typename T>
// 参照先を変更可能な const*(new deleteができない)
class RefPtr {
public:
	template<typename ...Args>
	static RefPtr make_refptr(Args&& ...args) {
		RefPtr<T> rptr;
		rptr.p = new T(std::forward<Args>(args)...);
		return rptr;
	}
private:
	T * p;
public:
	RefPtr(T* ptr = nullptr) : p(ptr) {}
	RefPtr(std::unique_ptr<T> uptr) : p{ uptr.get() } {}
	// 代入演算子
	RefPtr<T>& operator = (std::nullptr_t null) {
		p = null;
		return *this;
	}
	RefPtr<T>& operator = (T* other) {
		p = other;
		return *this;
	}
	RefPtr<T>& operator = (std::unique_ptr<T>& uptr) {
		p = uptr.get();
		return *this;
	}

	//ポインタ取得
	T* get() const {
		return p;
	}
	T& operator * () const {
		return *p;
	}
	// アロー演算子
	T* operator -> () const {
		return p;
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
		return p == other;
	}
	bool operator != (T* other) {
		return p != other;
	}

};