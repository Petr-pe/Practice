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

void WriteGroups(vector<Group>& groups) {
	cout << "GROUPS LIST:\n\n";
	for (int i = 0; i < groups.size(); i++)
	{
		cout << groups[i].gr_num << "\t | " << groups[i].spec << "\t | " << groups[i].disciplines << '\n';
	}
}
void WriteStudents(vector<Student>& students) {
	cout << "STUDENTS LIST:\n\n";
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
	if (!st.is_open())
		cout << "Error opening file!" << endl;
	Student s;
	while (st >> s.name >> s.surname >> s.gr_num) {
		for (int i = 0; i < groups.size(); i++)
		{
			if (s.gr_num == groups[i].gr_num)
			{
				s.notes.resize(groups[i].disciplines);
				for (int j = 0; j < groups[i].disciplines; j++)
				{
					st >> s.notes[j];
				}
				break;
			}
		}
		st >> s.absente;
		if (s.gr_num.empty() || s.name.empty() || s.surname.empty())
			continue;
		students.push_back(s);
	}
	st.close();
}


int main()
{
	vector<Group> groups;
	ReadGroups(groups);
	
	WriteGroups(groups);

	cout << "\n\n//////////////////////////////////////////////////////////////////////////\n\n\n";

	vector<Student> students;
	ReadStudents(students, groups);

	WriteStudents(students);

}
