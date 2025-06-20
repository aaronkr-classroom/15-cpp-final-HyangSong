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
	vector<Core*> students; // ��ü�� �ƴ� �����͸� ����
	//Core* record;
	char ch;
	string::size_type maxlen = 0;

	// ������ �а� �����ϱ�
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

		maxlen = max(maxlen, record->getName().size()); // ������
		students.push_back(record);
	}

	// �����ͷ� �����ϴ� compare �Լ��� ����
	sort(students.begin(), students.end(), compare_Core_ptrs);
	
	// �̸��� ������ ����ϱ�
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
		// �Լ��� ȣ���Ϸ��� �������� student[i]�� ������
		cout << students[i]->getName()
			<< string(maxlen + 1 - students[i]->getName().size(), ' ');

		try {
			double final_grade = students[i]->grade(); // ������
			streamsize prec = cout.precision();
			cout << setprecision(3) <<  final_grade
				<< setprecision(prec) << endl;
		}
		catch (domain_error e) {
			cout << e.what() << endl;
		}

		delete students[i]; // �о� ���� ��ü�� �Ҵ��� ����
	}
	return 0;
}