#pragma once

#include<memory>

template<typename T>
// �Q�Ɛ��ύX�\�� const*(new delete���ł��Ȃ�)
class RefPtr {
public:
	template<typename ...Args>
	static RefPtr& make_refptr(Args&& ...args) {
		p = new T(std::forward<Args>(args)...);
	}
public:
	RefPtr(T* ptr = nullptr) : p(ptr) {
	}
	// ������Z�q
	RefPtr<T>& operator = (T*& other) {
		p = other;
		return *this;
	}
	//�|�C���^�擾
	T* get() const {
		return p;
	}
	T& operator * () {
		return *p;
	}
	// �A���[���Z�q
	T& operator -> () {
		return *p;
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
		p == other;
	}
	bool operator != (T* other) {
		p != other;
	}	
private:
	T* p;
};