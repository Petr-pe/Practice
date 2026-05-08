#include "Files_func.h"
#include "Groups_Students.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void ReadGroups(vector<Group>& groups) {
	groups.clear();

	ifstream gr("Group.txt");
	if (!gr.is_open()) {
		cout << "Error opening file!" << endl;
		return;
	}
	Group g;
	while (gr >> g.gr_num >> g.spec >> g.disciplines)
		groups.push_back(g);

	gr.close();
}
void ReadStudents(vector<Student>& students, vector<Group>& groups) {
	students.clear();

	ifstream st("Student.txt");
	if (!st.is_open()) {
		cout << "Error opening file!" << endl;
		return;
	}
	Student s;
	bool isValid = true;
	while (st >> s.name >> s.surname >> s.gr_num) {
		bool groupFound = false;
		for (int i = 0; i < groups.size(); i++)
			if (s.gr_num == groups[i].gr_num)
			{
				groupFound = true;

				s.notes.resize(groups[i].disciplines);

				for (int j = 0; j < groups[i].disciplines; j++)
					st >> s.notes[j];

				st >> s.absence;
				break;
			}

		if (!groupFound) {
			cout << "Invalid student found in file\n";
			isValid = false;
			continue;
		}

		students.push_back(s);
	}
	if (!isValid) {
		cout << "[Any] Ignore\t[1] Delete\n";
		char choice; cin >> choice;
		if (choice == '1')
			DeleteExtraStudents(students, groups);
		else
			cout << "This student will be ignored. Please check the file for errors." << endl;

	}
	st.close();
}
void WriteGroups(vector<Group>& groups) {
	ofstream gr("Group.txt");
	if (!gr.is_open()) {
		cout << "Error opening file!" << endl;
		return;
	}
	for (int i = 0; i < groups.size(); i++)
	{
		gr << groups[i].gr_num << ' ' << groups[i].spec << ' ' << groups[i].disciplines << '\n';
	}
	gr.close();
}
void WriteStudents(vector<Student>& students) {
	ofstream st("Student.txt");
	if (!st.is_open()) {
		cout << "Error opening file!" << endl;
		return;
	}
	for (int i = 0; i < students.size(); i++)
	{
		st << students[i].name << ' ' << students[i].surname << '\t' << students[i].gr_num << '\t';
		for (int j = 0; j < students[i].notes.size(); j++)
		{
			st << students[i].notes[j] << ' ';
		}
		st << '\t' << students[i].absence << '\n';
	}
	st.close();
}
void WriteGeneralInfo(vector<GroupInfo>& groupInfos) {
	ofstream co("Count.txt");
	if (!co.is_open()) {
		cout << "Error opening file!" << endl;
		return;
	}
	for (int i = 0; i < groupInfos.size(); i++)
		co << groupInfos[i].gr_num << '\t' << groupInfos[i].studentCount << '\t' << groupInfos[i].avgNotes << '\t' << groupInfos[i].absencesCount << '\n';
	
	co.close();
}
void DeleteExtraStudents(vector<Student>& students, vector<Group>& groups) {
	for (int i = 0; i < students.size(); i++)
	{
		bool isFound = false;
		for (int j = 0; j < groups.size(); j++)
		{
			if (students[i].gr_num == groups[j].gr_num)
			{
				isFound = true;
				break;
			}
		}
		if (!isFound) {
			cout << "Deleting student " << students[i].name << ' ' << students[i].surname << " " << students[i].gr_num << endl;
			students.erase(students.begin() + i);
			i--;
		}
	}
	WriteStudents(students);
}