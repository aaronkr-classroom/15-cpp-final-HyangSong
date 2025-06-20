#pragma once
#ifndef GUARD_grade_h
#define GUARD_grade_h

#include "Student_info.h"

// 오버로딩 함수
double grade(double, double, double);
double grade(double, double, const vector<double>&);
double grade(const Student_info&);

bool fgrade(const Student_info&);
bool pgrade(const Student_info&); // 필요 하지 않지만 ...

#endif // !GUARD_grade_h
