#include "intl.h"
#include <iostream>

using namespace std;
istream& read_hw(istream& in, vector<double>& hw);

istream& International::read(istream& in) {
	Core::read_common(in);
	in >> toeic;
	read_hw(in, Core::homework);
	return in;
}

double International::grade() const {
	return min(Core::grade(), toeic);
}