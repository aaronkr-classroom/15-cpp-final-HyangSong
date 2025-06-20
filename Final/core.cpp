#include "core.h"
#include "grade.h"


using namespace std;

// core Ŭ������ ��� �Լ� ���ǹ�
istream& read_hw(istream& in, vector<double>& hw);

string Core::getName() const { return name; }

double Core::grade() const {
	return::grade(midterm, final, homework);
}

istream& Core::read_common(istream& in) {
	// �л� �̸��� ���� ������ �Է¹޾� ����
	in >> name >> midterm >> final;
	return in;
}

istream& Core::read(istream& in) {
	read_common(in);
	read_hw(in, homework); // Student_info.h �� ����
	return in;
}

// ���� �Լ� ����
bool compare(const Core& c1, const Core& c2) {
	return c1.getName() < c2.getName();
}
bool compare_grades(const Core& c1, const Core& c2) {
	return c1.grade() < c2.grade();
}

bool compare_Core_ptrs(const Core* cp1, const Core* cp2) {
	return compare(*cp1, *cp2);
}