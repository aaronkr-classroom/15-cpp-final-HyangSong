#pragma once

#ifndef GUARD_Vec_H
#define GUARD_Vec_H

#include <algorithm>
#include <cstddef>
#include <memory>

using namespace std;

template<class T> class Vec {
public:
	// �������̽�

	// Ÿ�����ǹ�
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef size_t size_type;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T& reference;
	typedef const T& const_reference;

	// ������
	Vec() { create(); }
	explicit Vec(size_type n, const T& val = T())
	{
		create(n, val);
	}

	// ���� ������
	Vec(const Vec& v) { create(v.begin(), v.end()); }
	Vec& operator=(const Vec&); // ����
	~Vec() { uncreate(); } // �Ҹ���

	// ���� ũ��� �ε����� ���� ���ο� �Լ���
	size_type size() const { return avail - data; }
	T& operator[](size_type i) { return data[i]; }
	const T& operator[](size_type i) const { return data[i]; }

	// �ݺ��ڸ� ��ȯ�ϴ� ���ο� �Լ�
	iterator begin() { return data; }
	const_iterator begin() const { return data; }

	iterator end() { return avail; }
	const_iterator end() const { return avail; }

	// ��� �߰��ϴ� �Լ� (�޸𸮸� ä���, ���� Ȯ��)
	void push_back(const T& val) {
		if (avail == limit) { // �ʿ��ϴٸ� ���� ���� Ȯ��
			grow();
		}
		unchecked_append(val); // ���ο� ��� �߰�
	}

	// �߰��Լ� (Student_info Ŭ���� vector���� �� �� �Լ� ���)
	void clear() { uncreate(); }
	bool empty() const { return data == avail; }

private:
	iterator data; // Vec�� ù ��° ��Ҹ� ����Ű�� ������
	iterator avail; // ���������θ� ���� ����� ������ ����Ű�� ������
	iterator limit; // ����� �� �ִ� ������ ��ҿ� ������ ����Ű�� ������

	allocator<T> alloc; // �޸𸮸� �Ҵ��ϴ� ��ü

	// ��� �Լ� ����
	void create();
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);

	void uncreate();
	void grow();
	void unchecked_append(const T&);
};

// �ǿ����� ���ǹ�
template<class T> Vec<T>& Vec<T>::operator=(const Vec& rhs) {
	// �ڰ� �Ҵ� ���� Ȯ��
	if (&rhs != this) {
		// �º��� ���� �迭�� �����ϴ� �޸𸮸� ����
		uncreate();

		// �캯�� ���� ��Ҹ� �º����� ����
		create(rhs.begin(), rhs.end());
	}
	return *this;
}

// ������ ��� �Լ��� 3��
// 1. �޸𸮸� �Ҵ��ϰ� ��Ҹ� �ʱ�ȭ�մϴ�.
template<class T> void Vec<T>::create() {
	data = avail = limit = 0;
}

// 2. �پ��� ������ �����ϸ�, �� �Լ���
// �Ҵ�� �޸𸮸� �ʱ�ȭ�ϰ�
// �����͸� ������ �����մϴ�.
template<class T> void Vec<T>::create(size_type n, const T& val) {
	data = alloc.allocate(n);
	limit = avail = data + n;
	uninitialize_fill(data, limit, val);
}

// 3. limit�� avail�� �׻� ���� �޸� �ּҸ�
// ����Ű�� �˴ϴ�.
template<class T> void Vec<T>::create(const_iterator i, const_iterator j) {
	data = alloc.allocate(j - i);
	limit = avail = uninitialized_copy(i, j, data);
}

// �Ҹ��� ��� �Լ�
template<class T> void Vec<T>::uncreate() {
	if (data) {
		// ������ ��ҵ��� �������� �Ҹ�
		iterator it = avail; // ������ ��ҿ� ����Ű�� ������
		while (it != data) {
			alloc.destroy(--it);
		}

		// �Ҵ�� ��� ���� ������ ��ȯ
		alloc.deallocate(data, limit - data);
	}
	// ��� �ִ� Vec�� ����Ű���� �����͸� �缳��
	data = avail = limit = 0;
}

// �޸� ������ �ø��� �Լ�
template<class T> void Vec<T>::grow() {
	// ���� ������ �ø� ���� ���� ����ϴ� 
	// ���� ������ 2��� �Ҵ�
	size_type new_size = max(2 * (limit - data), ptrdiff_t(1));

	// ���ο� ���� ������ �Ҵ��ϰ� 
	// ���� ��ҵ��� ���ο� ���� ������ ����
	iterator new_data = alloc.allocate(new_size);
	iterator new_avail = uninitialized_copy(data, avail, new_data);

	// ���� ���� ������ ����
	uncreate();

	// ���Ӱ� �Ҵ��� ���� ������ ����Ű���� ������ �缳��
	data = new_data;
	avail = new_avail;
	limit = data + new_size;
}

template<class T> void Vec<T>::unchecked_append(const T& val) {
	alloc.construct(avail++, val);
}
#endif