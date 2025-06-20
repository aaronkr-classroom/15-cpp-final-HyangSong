#include <iostream>
#include <vector>

using namespace std;

istream& read_hw(istream& in, vector<double>& hw) {
	if (in) {
		hw.clear();

		double x;
		while (in >> x)
			hw.push_back(x);

		// 스트림 다시 삭제 (다음 학생 위해)
		in.clear();
	}
	return in;
}