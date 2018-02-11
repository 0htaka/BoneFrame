#pragma once

#include<memory>

template<typename T>
// �Q�Ɛ��ύX�\�� const*(new delete���ł��Ȃ�)
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
	// ������Z�q
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

	//�|�C���^�擾
	T* get() const {
		return p;
	}
	T& operator * () const {
		return *p;
	}
	// �A���[���Z�q
	T* operator -> () const {
		return p;
	}
	//�|�C���^����	
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
	//�z�񑀍�
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