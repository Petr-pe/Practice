#include "Groups_Students.h"
#include "Menu.h"
#include "Files_func.h"
#include <vector>
#include <iostream>
using namespace std;

void DisplayGroups(vector<Group>& groups) {
	cout << "\nGROUPS LIST:\n\n";
	for (int i = 0; i < groups.size(); i++)
	{
		cout << groups[i].gr_num << "\t" << groups[i].spec << "\t" << groups[i].disciplines << '\n';
	}
}
void DisplayStudents(vector<Student>& students) {
	if (students.empty())
		return;
	cout << "\nSTUDENTS LIST:\n\n";
	for (int i = 0; i < students.size(); i++)
	{
		DisplayStudentInfo(students[i]);
	}
}
void DisplayStudentInfo(Student student) {
	cout << student.name << ' ' << student.surname << '\t' << student.gr_num << '\t';
	for (int j = 0; j < student.notes.size(); j++)
	{
		cout << student.notes[j] << ' ';
	}
	cout << '\t' << student.absence << endl;
}
void DisplayStudentsAverageFromGroup(vector<Student>& students, string groupNum) {
	cout << "\nSTUDENTS AVERAGE FROM GROUP " << groupNum << ":\n\n";
	bool isFound = false;
	for (int i = 0; i < students.size(); i++)
	{
		if (students[i].gr_num == groupNum)
		{
			isFound = true;
			cout << students[i].name << ' ' << students[i].surname << "\tAverage: " << CountStudentAverage(students[i]) << endl;
		}
	}
	if (!isFound)
		cout << "No students found from group " << groupNum << endl;
}
void DisplayMaxAbsencesStudent(vector<Student>& students) {
	if (students.size() == 0) {
		cout << "No students available!" << endl;
		return;
	}
	Student maxAbsenceStudent = students[0];
	for (int i = 1; i < students.size(); i++)
	{
		if (students[i].absence > maxAbsenceStudent.absence)
			maxAbsenceStudent = students[i];
	}
	cout << "Student with maximum absences: ";
	DisplayStudentInfo(maxAbsenceStudent);
}

void UpdateGeneralInfo(vector<Group>& groups, vector<Student>& students, vector<GroupInfo>& groupInfos) {
	groupInfos.clear();
	GroupInfo gi;
	for (int i = 0; i < groups.size(); i++)
	{
		gi.gr_num = groups[i].gr_num;
		gi.studentCount = 0;
		gi.avgNotes = 0;
		gi.absencesCount = 0;
		for (int j = 0; j < students.size(); j++)
		{
			if (students[j].gr_num == groups[i].gr_num)
			{
				gi.studentCount++;
				gi.avgNotes += CountStudentAverage(students[j]);
				gi.absencesCount += students[j].absence;
			}
		}
		if (gi.studentCount > 0)
			gi.avgNotes /= gi.studentCount;

		groupInfos.push_back(gi);
	}
}

vector<Student> FindStudentsFromGroup(vector<Student>& students, vector<Group>& groups, string groupName) {
	vector<Student> studentsFromGroup;
	for (int j = 0; j < students.size(); j++)
		if (students[j].gr_num == groupName)
			studentsFromGroup.push_back(students[j]);

	if (studentsFromGroup.size() == 0)
		cout << "No students found from group " << groupName << endl;

	return studentsFromGroup;
}
float CountStudentAverage(Student student) {
	float average = 0;
	for (int j = 0; j < student.notes.size(); j++)
	{
		average += student.notes[j];
	}
	if (student.notes.size() != 0) average /= (float)student.notes.size();
	return average;
}

void SortStudentsByName(vector<Student>& students) {
	for (int i = 0; i < students.size() - 1; i++)
	{
		for (int j = 0; j < students.size() - i - 1; j++)
		{
			if (students[j].name > students[j + 1].name || (students[j].name == students[j + 1].name && students[j].surname > students[j + 1].surname))
			{
				swap(students[j], students[j + 1]);
			}
		}
	}
}

void AddGroup(vector<Group>& groups) {
	Group newGroup;
	cout << "Enter group number: "; cin >> newGroup.gr_num;
	bool groupfound = false;
	for (int i = 0; i < groups.size(); i++)
	{
		if (newGroup.gr_num == groups[i].gr_num) {
			cout << "Group with this number already exists: " << groups[i].gr_num << '\t' << groups[i].spec << '\t' << groups[i].disciplines << endl;
			groupfound = true;
		}
	}
	if (groupfound)
		return;
	cout << "Enter specialization: "; cin >> newGroup.spec;
	cout << "Enter number of disciplines: "; cin >> newGroup.disciplines;
	cout << newGroup.gr_num << "\t" << newGroup.spec << "\t" << newGroup.disciplines << " -- added";
	groups.push_back(newGroup);
	WriteGroups(groups);
}
void AddStudent(vector<Student>& students, vector<Group>& groups) {
	Student newStudent;
	cout << "Enter student name: "; cin >> newStudent.name;
	cout << "Enter student surname: "; cin >> newStudent.surname;
	cout << "Enter group number: "; cin >> newStudent.gr_num;
	bool groupFound = false;
	for (int i = 0; i < groups.size(); i++)
	{
		if (newStudent.gr_num == groups[i].gr_num)
		{
			groupFound = true;
			newStudent.notes.resize(groups[i].disciplines);
			for (int j = 0; j < groups[i].disciplines; j++)
			{
				cout << "Enter note for discipline " << j + 1 << ": ";
				cin >> newStudent.notes[j];
			}
			cout << "Enter number of absences: "; cin >> newStudent.absence;
			break;
		}
	}
	if (!groupFound) {
		cout << "Invalid student group: " << newStudent.gr_num << endl;
		return;
	}
	cout << newStudent.name << ' ' << newStudent.surname << '\t' << newStudent.gr_num << '\t';
	for (int j = 0; j < newStudent.notes.size(); j++)
		cout << newStudent.notes[j] << ' ';
	cout << '\t' << newStudent.absence << " -- added";
	students.push_back(newStudent);
	WriteStudents(students);
}

void DeleteGroup(vector<Group>& groups, vector<Student>& students) {
	string groupNum;
	cout << "Enter group number to delete: "; cin >> groupNum;
	bool groupFound = false;
	for (int i = 0; i < groups.size(); i++)
	{
		if (groups[i].gr_num == groupNum)
		{
			groupFound = true;
			groups.erase(groups.begin() + i);
			WriteGroups(groups);
			break;
		}
	}
	if (!groupFound) {
		cout << "Group not found: " << groupNum << endl;
		return;
	}
	cout << "Group " << groupNum << " deleted. Deleting students from this group..." << endl;
	DeleteExtraStudents(students, groups);
}
void DeleteStudent(vector<Student>& students) {
	string studentName, studentSurname;
	cout << "Enter student name to delete: "; cin >> studentName;
	cout << "Enter student surname to delete: "; cin >> studentSurname;
	bool studentFound = false;
	for (int i = 0; i < students.size(); i++)
	{
		if (students[i].name == studentName && students[i].surname == studentSurname)
		{
			studentFound = true;
			students.erase(students.begin() + i);
			WriteStudents(students);
			break;
		}
	}
	if (!studentFound) {
		cout << "Student not found: " << studentName << ' ' << studentSurname << endl;
		return;
	}
	cout << "Student " << studentName << ' ' << studentSurname << " deleted." << endl;
}

void ModifyGroup(vector<Group>& groups) {
	string groupNum;
	cout << "Enter group number to modify: "; cin >> groupNum;

	bool groupFound = false;

	for (int i = 0; i < groups.size(); i++)
	{
		if (groups[i].gr_num == groupNum)
		{
			groupFound = true;

			bool cycl = true;
			while (cycl) {
				cout << "Choose what to modify: \n[1] Specialization\t[2] Number of disciplines\t[0] Save and exit\nEnter your choice: ";
				char modifyChoice; cin >> modifyChoice;
				switch (modifyChoice) {
				case '1':
				{
					cout << "Enter new specialization: "; cin >> groups[i].spec;
					break;
				}
				case '2':
				{
					cout << "Enter new number of disciplines: "; cin >> groups[i].disciplines;
					break;
				}
				case '0':
				{
					cout << groups[i].gr_num << "\t" << groups[i].spec << "\t" << groups[i].disciplines << " -- saved";
					cycl = false;
					break;
				}
				}
			}
			WriteGroups(groups);
			break;
		}
	}
	if (!groupFound) {
		cout << "Group not found: " << groupNum << endl;
		return;
	}
	cout << "Group " << groupNum << " modified. It is recommended to check students from this group for correct number of notes." << endl;
}
void ModifyStudent(vector<Student>& students, vector<Group>& groups) {
	string studentName, studentSurname;
	cout << "Enter student name to modify: "; cin >> studentName;
	cout << "Enter student surname to modify: "; cin >> studentSurname;
	bool studentFound = false;

	for (int i = 0; i < students.size(); i++)
	{
		if (students[i].name == studentName && students[i].surname == studentSurname)
		{
			studentFound = true;
			bool cycl = true;
			while (cycl) {
				cout << "Choose what to modify: \n[1] Group number\t[2] Notes\t[3] Absences\t[0] Save and exit\nEnter your choice: ";
				char modifyChoice; cin >> modifyChoice;
				switch (modifyChoice)
				{
				case '1':
				{
					cout << "Enter new group number: "; cin >> students[i].gr_num;
					bool groupFound = false;
					for (int j = 0; j < groups.size(); j++)
					{
						if (students[i].gr_num == groups[j].gr_num)
						{
							groupFound = true;
							students[i].notes.resize(groups[j].disciplines);
							cout << "It is recommended to change the student's notes";
							break;
						}
					}
					if (!groupFound) {
						cout << "Invalid group: " << students[i].gr_num << endl;
						break;
					}
					break;
				}
				case '2':
				{
					cout << "Which modification do you want to make? \n[1] Change all notes\t[2] Change note for specific discipline\nEnter your choice: ";
					char noteModifyChoice; cin >> noteModifyChoice;
					switch (noteModifyChoice)
					{
					case '1':
					{
						for (int j = 0; j < students[i].notes.size(); j++)
						{
							cout << "Enter new note for discipline " << j + 1 << ": ";
							cin >> students[i].notes[j];
						}
						break;
					}
					case '2':
					{
						cout << "Which discipline's notes do you want to change? Enter discipline number (1 - " << students[i].notes.size() << ") : ";
						int discNum; cin >> discNum; discNum--;
						if (discNum < 0 || discNum >= students[i].notes.size())
							cout << "Invalid discipline number!" << endl;
						else
						{
							cout << "Enter new note for discipline " << discNum + 1 << ": ";
							cin >> students[i].notes[discNum];
						}
						break;
					}
					}
					break;
				}
				case '3':
				{
					cout << "Enter new number of absences: "; cin >> students[i].absence;
					break;
				}
				case '0':
				{
					cout << students[i].name << ' ' << students[i].surname << '\t' << students[i].gr_num << '\t';
					for (int j = 0; j < students[i].notes.size(); j++)
						cout << students[i].notes[j] << ' ';

					cout << '\t' << students[i].absence << "\t--\tsaved";
					cycl = false;
					break;
				}
				}
			}
			WriteStudents(students);
			break;
		}
	}
	if (!studentFound)
		cout << "Student not found: " << studentName << ' ' << studentSurname << endl;
}