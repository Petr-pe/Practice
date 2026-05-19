#include "Groups_Students.h"
#include "Menu.h"
#include "Files_func.h"
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

 string menu = {
	"========================================\n"
	"        STUDENT MANAGEMENT SYSTEM       \n"
	"========================================\n\n"
	"Please select an option:\n\n"
	"[1] Display information\n"
	"[2] Add new element\n"
	"[3] Delete element\n"
	"[4] Modify Element\n"
	"[5] Update Count.txt\n"
	"[0] Exit\n\n"
	"----------------------------------------\n"
	"Enter your choice: " };

void DisplayGroups(vector<Group>& groups) {
	int groupWidth = 6, specWidth = 15, discWidth = 12;
	for (int i = 0; i < groups.size(); i++)
	{
		groupWidth = max(groupWidth, (int)groups[i].gr_num.size());
		specWidth = max(specWidth, (int)groups[i].spec.size());
		discWidth = max(discWidth, (int)to_string(groups[i].disciplines).size());
	}
	cout << "\n\n";
	cout << left << setw(groupWidth) << "Group"
		<< "  | " << setw(specWidth) << "Specialization"
		<< "  | " << setw(discWidth) << "Disciplines" << "\n";

	cout << string(70, '-') << "\n";

	for (int i = 0; i < groups.size(); i++) 
		cout << left << setw(groupWidth) << groups[i].gr_num << "  | " << setw(specWidth) << groups[i].spec
			<< "  | " << setw(discWidth) << groups[i].disciplines << "\n";
}
void DisplayStudents(vector<Student>& students) {
	int nameWidth = 12, surnameWidth = 12, groupWidth = 8, notesWidth = 50, absenceWidth = 10;

	cout << "\n\n";

	cout << left
		<< setw(nameWidth) << "Name"
		<< "| " << setw(surnameWidth) << "Surname"
		<< "| " << setw(groupWidth) << "Group"
		<< "| " << setw(notesWidth) << "Notes"
		<< "| " << setw(absenceWidth) << "Absences" << "\n";

	cout << string(120, '-') << "\n";

	for (int i = 0; i < students.size(); i++)
	{
		cout << left
			<< setw(nameWidth) << students[i].name
			<< "| " << setw(surnameWidth) << students[i].surname
			<< "| " << setw(groupWidth) << students[i].gr_num
			<< "| ";

		string notesLine = "";
		for (int j = 0; j < students[i].notes.size(); j++)
		{
			notesLine += to_string(students[i].notes[j]) + " ";
		}

		cout << setw(notesWidth) << notesLine
			<< "| " << setw(absenceWidth) << students[i].absence << "\n";
	}
}
void DisplayStudentInfo(Student student) {
	cout << student.name << ' ' << student.surname << '\t' << student.gr_num << '\t';
	for (int j = 0; j < student.notes.size(); j++)
		cout << student.notes[j] << ' ';

	cout << '\t' << student.absence << endl;
}
void DisplayStudentsAverageFromGroup(vector<Student>& students, string groupNum) {

	int stW = 8;
	for (int i = 0; i < students.size(); i++)
		stW = max(stW, (int)students[i].name.size() + (int)students[i].surname.size() + 1);
	
	cout << "\n\n";
	cout << left << setw(stW) << "Students" << " | Average\n" << string(stW + 12, '-') << endl;

	bool isFound = false;
	for (int i = 0; i < students.size(); i++)
		if (students[i].gr_num == groupNum){
			isFound = true;
			string fullName = students[i].name + ' ' + students[i].surname;
			cout << left << setw(stW) << fullName << " | " << CountStudentAverage(students[i]) << endl;
		}
	
	if (!isFound)
		cout << "\n\nNo students found from group " << groupNum << endl;
}
void DisplayMaxAbsencesStudent(vector<Student>& students) {
	if (students.size() == 0) {
		cout << "\n\nNo students available!" << endl;
		return;
	}
	Student maxAbsenceStudent = students[0];
	for (int i = 1; i < students.size(); i++)
		if (students[i].absence > maxAbsenceStudent.absence)
			maxAbsenceStudent = students[i];
	
	cout << "\n\nStudent with maximum absences: ";
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
		cout << "\n\nNo students found from group " << groupName << endl;

	return studentsFromGroup;
}
float CountStudentAverage(Student student) {
	float average = 0;
	for (int j = 0; j < student.notes.size(); j++)
		average += student.notes[j];
	if (student.notes.size() != 0) average /= (float)student.notes.size();
	return average;
}

void SortStudentsByName(vector<Student>& students) {
	if (students.size() <= 1)
		return;
	for (int i = 0; i < students.size() - 1; i++)
		for (int j = 0; j < students.size() - i - 1; j++)
			if (students[j].name > students[j + 1].name || (students[j].name == students[j + 1].name && students[j].surname > students[j + 1].surname))
				swap(students[j], students[j + 1]);
}

void AddGroup(vector<Group>& groups) {
	Group newGroup;
	cout << "\n\nEnter group number: "; cin >> newGroup.gr_num;
	bool groupfound = false;
	for (int i = 0; i < groups.size(); i++)
		if (newGroup.gr_num == groups[i].gr_num) {
			cout << "\n\nGroup with this number already exists: " << groups[i].gr_num << '\t' << groups[i].spec << '\t' << groups[i].disciplines << endl;
			groupfound = true;
		}
	
	if (groupfound)
		return;

	cout << "\nEnter specialization: "; cin >> newGroup.spec;
	cout << "\nEnter number of disciplines: "; cin >> newGroup.disciplines;
	
	if (cin.fail())
	{
		cout << "Error: enter numbers only!\n";
		cin.clear();
		cin.ignore(10000, '\n');
		return;
	}

	cout << '\n\n' << newGroup.gr_num << "\t" << newGroup.spec << "\t" << newGroup.disciplines << " -- added";

	groups.push_back(newGroup);
	WriteGroups(groups);
}
void AddStudent(vector<Student>& students, vector<Group>& groups) {
	Student newStudent;

	cout << "\n\nEnter student name: "; cin >> newStudent.name;
	cout << "Enter student surname: "; cin >> newStudent.surname;
	bool studentFound = false;
	for (int i = 0; i < students.size(); i++)
		if (newStudent.name == students[i].name && newStudent.surname == students[i].surname) {
			cout << "\n\nStudent with this name and surname already exists: ";
			DisplayStudentInfo(students[i]);
			studentFound = true;
			return;
		}

	cout << "\nEnter group number: "; cin >> newStudent.gr_num;
	cout << '\n';

	bool groupFound = false;
	for (int i = 0; i < groups.size(); i++)
		if (newStudent.gr_num == groups[i].gr_num)
		{
			groupFound = true;
			newStudent.notes.resize(groups[i].disciplines);
			for (int j = 0; j < groups[i].disciplines; j++)
			{
				cout << "Enter note for discipline " << j + 1 << ": ";
				cin >> newStudent.notes[j];

				if (cin.fail())
				{
					cout << "Error: enter numbers only!\n";
					cin.clear();
					cin.ignore(10000, '\n');
					return;
				}

			}
			cout << "\nEnter number of absences: "; cin >> newStudent.absence;

			if (cin.fail())
			{
				cout << "Error: enter numbers only!\n";
				cin.clear();
				cin.ignore(10000, '\n');
				return;
			}

			break;
		}

	if (!groupFound) {
		cout << "\n\nInvalid student group: " << newStudent.gr_num << endl;
		return;
	}

	cout << newStudent.name << ' ' << newStudent.surname << '\t' << newStudent.gr_num << '\t';
	for (int j = 0; j < newStudent.notes.size(); j++)
		cout << newStudent.notes[j] << ' ';

	cout << '\t' << newStudent.absence << "\t--\tadded";

	students.push_back(newStudent);
	WriteStudents(students);
}

void DeleteGroup(vector<Group>& groups, vector<Student>& students) {
	string groupNum;

	cout << "\n\nEnter group number to delete: "; cin >> groupNum;

	bool groupFound = false;
	for (int i = 0; i < groups.size(); i++)
		if (groups[i].gr_num == groupNum)
		{
			groupFound = true;
			groups.erase(groups.begin() + i);
			WriteGroups(groups);
			break;
		}
	
	if (!groupFound) {
		cout << "\n\nGroup not found: " << groupNum << endl;
		return;
	}
	cout << "\n\nGroup " << groupNum << " deleted. Deleting students from this group..." << endl;
	DeleteExtraStudents(students, groups);
}
void DeleteStudent(vector<Student>& students) {
	string studentName, studentSurname;

	cout << "\n\nEnter student name to delete: "; cin >> studentName;

	cout << "Enter student surname to delete: "; cin >> studentSurname;
	bool studentFound = false;
	for (int i = 0; i < students.size(); i++)
		if (students[i].name == studentName && students[i].surname == studentSurname)
		{
			studentFound = true;
			students.erase(students.begin() + i);
			WriteStudents(students);
			break;
		}
	
	if (!studentFound) {

		cout << "\n\nStudent not found: " << studentName << ' ' << studentSurname << endl;
		return;
	}
	cout << "\n\nStudent " << studentName << ' ' << studentSurname << " deleted." << endl;

}

void ModifyGroup(vector<Group>& groups) {
	string groupNum;

	cout << "\n\nEnter group number to modify: "; cin >> groupNum;


	bool groupFound = false;

	for (int i = 0; i < groups.size(); i++)
		if (groups[i].gr_num == groupNum)
		{
			groupFound = true;

			bool cycl = true;
			while (cycl) {
				cout << "\nChoose what to modify: \n\n[1] Specialization\t[2] Number of disciplines\t[0] Save and exit\n\nEnter your choice: ";

				char modifyChoice; cin >> modifyChoice;
				switch (modifyChoice) {
				case '1':
				{
					cout << "\nEnter new specialization: "; cin >> groups[i].spec;
					break;
				}
				case '2':
				{
					cout << "\nEnter new number of disciplines: "; cin >> groups[i].disciplines;

					if (cin.fail())
					{
						cout << "Error: enter numbers only!\n";
						cin.clear();
						cin.ignore(10000, '\n');
						return;
					}

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
	
	if (!groupFound) {
		cout << "\n\nGroup not found: " << groupNum << endl;
		return;
	}
	cout << "\n\nGroup " << groupNum << " modified.\n\n\tIt is recommended to check students from this group for correct number of notes." << endl;
}
void ModifyStudent(vector<Student>& students, vector<Group>& groups) {
	string studentName, studentSurname;
	cout << "\n\nEnter student name to modify: "; cin >> studentName;
	cout << "Enter student surname to modify: "; cin >> studentSurname;
	bool studentFound = false;

	for (int i = 0; i < students.size(); i++)
		if (students[i].name == studentName && students[i].surname == studentSurname)
		{
			studentFound = true;
			bool cycl = true;
			while (cycl) {

				cout << "\n\nChoose what to modify: \n[1] Group number\t[2] Notes\t[3] Absences\t[0] Save and exit\nEnter your choice: ";

				char modifyChoice; cin >> modifyChoice;
				switch (modifyChoice)
				{
				case '1':
				{

					cout << "\nEnter new group number: "; cin >> students[i].gr_num;

					bool groupFound = false;
					for (int j = 0; j < groups.size(); j++)
					{
						if (students[i].gr_num == groups[j].gr_num)
						{
							groupFound = true;
							students[i].notes.resize(groups[j].disciplines);
							cout << "\nIt is recommended to change the student's notes\n";
							break;
						}
					}
					if (!groupFound) {
						cout << "\n\nInvalid group: " << students[i].gr_num << endl;
						break;
					}
					break;
				}
				case '2':
				{
					cout << "\n\nWhich modification do you want to make? \n[1] Change all notes\t[2] Change note for specific discipline\n\nEnter your choice: ";
					char noteModifyChoice; cin >> noteModifyChoice;
					cout << '\n';
					switch (noteModifyChoice)
					{
					case '1':
					{
						for (int j = 0; j < students[i].notes.size(); j++)
						{
							cout << "\nEnter new note for discipline " << j + 1 << ": ";
							cin >> students[i].notes[j];

							if (cin.fail())
							{
								cout << "Error: enter numbers only!\n";
								cin.clear();
								cin.ignore(10000, '\n');
								return;
							}

						}
						break;
					}
					case '2':
					{
						cout << "\n\nWhich discipline's notes do you want to change?\n\nEnter discipline number (1 - " << students[i].notes.size() << ") : ";
						int discNum; cin >> discNum; discNum--;
						cout << '\n';
						if (discNum < 0 || discNum >= students[i].notes.size())
							cout << "\n\nInvalid discipline number!" << endl;
						else
						{
							cout << "\nEnter new note for discipline " << discNum + 1 << ": ";
							cin >> students[i].notes[discNum];

							if (cin.fail())
							{
								cout << "Error: enter numbers only!\n";
								cin.clear();
								cin.ignore(10000, '\n');
								return;
							}

						}
						break;
					}
					}
					break;
				}
				case '3':
				{
					cout << "\nEnter new number of absences: "; cin >> students[i].absence;
					break;
				}
				case '0':
				{
					cout <<'\n\n' << students[i].name << ' ' << students[i].surname << '\t' << students[i].gr_num << '\t';
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
	
	if (!studentFound)
		cout << "\n\nStudent not found: " << studentName << ' ' << studentSurname << endl;
}

void ShowMenu(vector<Student>& students, vector<Group>& groups, vector<GroupInfo>& groupInfos, bool& cycle) {
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
		cout << "\n\nWhat do you want to display?"
			"\n[1] All Groups\n"
			"[2] All Students\n"
			"[3] Students From a group\n"
			"[4] Student with maximum absences\n"
			"[5] Students average from a group"
			"\n\nEnter your choice : ";

		char displayChoice; cin >> displayChoice;
		switch (displayChoice)
		{
		case '1':
		{
			DisplayGroups(groups);
			break;
		}
		case '2':
		{
			DisplayStudents(students);
			break;
		}
		case '3':
		{
			cout << "\nEnter group number: ";
			string groupNum; cin >> groupNum;
			vector<Student> studentsFromGroup = FindStudentsFromGroup(students, groups, groupNum);
			if (studentsFromGroup.size() > 1)
				SortStudentsByName(studentsFromGroup);
			DisplayStudents(studentsFromGroup);
			break;
		}
		case '4': {
			DisplayMaxAbsencesStudent(students);
			break;
		}
		case '5': {
			string groupNum;
			cout << "\nEnter group number: "; cin >> groupNum;
			DisplayStudentsAverageFromGroup(students, groupNum);
			break;
		}
		default:
			cout << "\nRead what is written above";
			break;
		}
		break;
	}
	case '2':
	{
		cout << "\n\nWhat do you want to add? \n[1] Group\t[2] Student\n\nEnter your choice: ";
		char addChoice; cin >> addChoice;
		switch (addChoice)
		{
		case '1':
		{
			AddGroup(groups);
			break;
		}
		case '2':
		{
			AddStudent(students, groups);
			break;
		}
		default:
			cout << "\nRead what is written above";
			break;
		}
		break;
	}
	case '3':
	{
		cout << "\n\nWhat do you want to delete? \n[1] Group\t[2] Student\n\nEnter your choice: ";
		char deleteChoice; cin >> deleteChoice;
		switch (deleteChoice)
		{
		case '1':
		{
			DeleteGroup(groups, students);
			break;
		}
		case '2':
		{
			DeleteStudent(students);
			break;
		}
		default:
			cout << "\nRead what is written above";
			break;
		}
		break;
	}
	case '4':
	{
		cout << "\n\nWhat do you want to modify? \n[1] Group\t[2] Student\n\nEnter your choice: ";
		char modifyChoice; cin >> modifyChoice;
		switch (modifyChoice)
			{
			case '1':
			{
				ModifyGroup(groups);
				break;
			}
			case '2':
			{
				ModifyStudent(students, groups);
				break;
			}
			default:
				cout << "\nRead what is written above";
				break;
		}
		break;
	}
	case '5': {
		UpdateGeneralInfo(groups, students, groupInfos);
		WriteGeneralInfo(groupInfos);
		cout << "\n Count.txt updated\n";
		break;
	}
	default:
		cout << "\nRead what is written above";
		break;
	}

}