#pragma once
#ifndef GUARD_Student_info
#define GUARD_Student_info

//Student_info.h
#include <iostream>
#include <string>
#include <vector>

#include "Vec.h"
#include "core.h"

using namespace std;

class Student_info {
private:
	Core* cp;

public:
	// ������
	Student_info() : cp(0) { }; // �� student_info() ��ü�� ����
	Student_info(istream& is) : cp(0) { read(is); } // ��Ʈ���� �о� student_info ��ü�� ����

	// Core ���� �߰�
	Student_info(const Student_info&);
	Student_info& operator=(const Student_info&);
	~Student_info() { delete cp; }

	string get_name() const { 
		if (cp) return cp->getName();
		else throw runtime_error("Uninitialized student!");
	}
	/*
	double get_midterm() const {
		if (cp) return cp->getMidterm();
		else throw runtime_error("Uninitialized student!");
	}
	double get_final() const {
		if (cp) return cp->getFinal();
		else throw runtime_error("Uninitialized student!");
	}
	*/
	//vector<double> get_hw() const { return homework; }

	//void set_name(string n) { name = n; } // ������ �����߰� �κ�


	istream& read(istream&);
	double grade() const {
		if (cp) return cp->grade();
		else throw runtime_error("Uninitialized student!");
	};

	static bool compare(const Student_info& s1,
		const Student_info& s2) {
		return s1.get_name() < s2.get_name();
	}
};

#endif