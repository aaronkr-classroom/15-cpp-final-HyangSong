#include<algorithm>
#include<iomanip>
#include<iostream>
#include<ios>
#include<stdexcept>
#include<string>
#include<vector>

#include "core.h"
#include "Grad.h"
#include "Vec.h"
#include "Student_info.h"
#include "median.h"
#include "intl.h"

using namespace std;

int main() {
	vector<Core*> students; // 객체가 아닌 포인터를 저장
	//Core* record;
	char ch;
	string::size_type maxlen = 0;

	// 데이터 읽고 저장하기
	while (cin >> ch) { 
		if (cin.eof()) break;  // Check for end of input

		// Handle unexpected empty lines or malformed input
		if (ch != 'U' && ch != 'G' && ch != 'I') {
			// If the input is not a valid student type, skip it
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		Core* record = nullptr;

		if (ch == 'U')
			record = new Core;
		else if (ch == 'G')
			record = new Grad;
		else if (ch == 'I')  
			record = new International;
		record->read(cin);

		maxlen = max(maxlen, record->getName().size()); // 역참조
		students.push_back(record);
	}

	// 포인터로 동작하는 compare 함수를 전달
	sort(students.begin(), students.end(), compare_Core_ptrs);
	
	// 이름과 점수를 출력하기
	for (vector<Core*>::size_type i = 0;
		i != students.size(); ++i) {
		if (dynamic_cast<Grad*>(students[i])) {
			// It's a Grad student
			cout << "(G) ";
		}
		else if (dynamic_cast<International*>(students[i])) {
			// It's an International student
			cout << "(I) ";
		}
		else {
			// It's an Undergraduate student
			cout << "(U) ";
		}
		// 함수를 호출하려고 포인터인 student[i]를 역참조
		cout << students[i]->getName()
			<< string(maxlen + 1 - students[i]->getName().size(), ' ');

		try {
			double final_grade = students[i]->grade(); // 역참조
			streamsize prec = cout.precision();
			cout << setprecision(3) <<  final_grade
				<< setprecision(prec) << endl;
		}
		catch (domain_error e) {
			cout << e.what() << endl;
		}

		delete students[i]; // 읽어 들인 객체의 할당을 해제
	}
	return 0;
}