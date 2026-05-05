#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Group {
	string gr_num;
	string spec;
	int disciplines = 0;
};
struct Student {
	string name;
	string surname;
	string gr_num;
	vector<int> notes{};
	int absente{};
};

void ReadGroups(vector<Group>& groups);
void ReadStudents(vector<Student>& students, vector<Group>& groups);
void WriteGroups(vector<Group>& groups);
void WriteStudents(vector<Student>& students);

bool cycle = true;
string menu =
	"========================================\n"
	"        STUDENT MANAGEMENT SYSTEM       \n"
	"========================================\n\n"
	"Please select an option:\n\n"
	"[1] Display all groups\n"
	"[2] Display all students\n"
	"[3] Search student by name\n"
	"[4] Show students by group\n"
	"[5] Add new student\n"
	"[6] Delete student\n"
	"[0] Exit\n\n"
	"----------------------------------------\n"
	"Enter your choice: ";

void ShowMenu(vector<Student>& students, vector<Group>& groups) {
	cout << menu;
	char choice; cin >> choice;
	switch (choice) {
		case '0':
		{
			cycle = false;
				break;
		}
		case '1':
		{
			ReadGroups(groups);
			WriteGroups(groups);
				break;
		}
		case '2':
		{
			ReadStudents(students, groups);
			WriteStudents(students);
				break;
		}
	}
}
		
void WriteGroups(vector<Group>& groups) {
	cout << "\nGROUPS LIST:\n\n";
	for (int i = 0; i < groups.size(); i++)
	{
		cout << groups[i].gr_num << "\t | " << groups[i].spec << "\t | " << groups[i].disciplines << '\n';
	}
}
void WriteStudents(vector<Student>& students) {
	cout << "\nSTUDENTS LIST:\n\n";
	for (int i = 0; i < students.size(); i++)
	{
		cout << students[i].name << ' ' << students[i].surname << '\t' << students[i].gr_num << '\t';
		for (int j = 0; j < students[i].notes.size(); j++)
		{
			cout << students[i].notes[j] << ' ';
		}
		cout <<'\t' << students[i].absente << endl;
	}
}
void ReadGroups(vector<Group>& groups) {
	ifstream gr("Group.txt");
	if (!gr.is_open())
		cout << "Error opening file!" << endl;
	while (!gr.eof()) {
		Group g;
		gr >> g.gr_num >> g.spec >> g.disciplines;
		if (g.gr_num.empty() || g.spec.empty() || g.disciplines == 0)
			continue;
		groups.push_back(g);
	}
	gr.close();
}
void ReadStudents(vector<Student>& students, vector<Group>& groups) {
	ifstream st("Student.txt");
	if (!st.is_open()) {
		cout << "Error opening file!" << endl;
		return;
	}
	Student s;
	while (st >> s.name >> s.surname >> s.gr_num) {
		bool groupFound = false;
		for (int i = 0; i < groups.size(); i++)
		{
			if (s.gr_num == groups[i].gr_num)
			{
				groupFound = true;

				s.notes.resize(groups[i].disciplines);

				for (int j = 0; j < groups[i].disciplines; j++)
				{
					st >> s.notes[j];
				}

				st >> s.absente;
				break;
			}
		}
		if (s.name.empty() || s.surname.empty()) {
			cout << "Invalid student name or surname!" << endl;
			continue;
		}
		else if (!groupFound) {
			cout << s.name << ' ' << s.surname << "has invalid student groupe: " << s.gr_num << endl;
			continue;
		}

		students.push_back(s);
	}
	st.close();
}


int main()
{
	while (cycle) {
		
		vector<Group> groups;
		ReadGroups(groups);
		vector<Student> students;


		ShowMenu(students, groups);
		menu = "\n[1] Display all groups\t"
			"[2] Display all students\t"
			"[3] Search student by name\n"
			"[4] Show students by group\t"
			"[5] Add new student\t"
			"[6] Delete student\n"
			"[0] Exit\n\n"
			"Enter your choice: ";
	}

	


	

	


}
