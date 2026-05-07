#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Groups_Students.h"
#include "Files_func.h"
#include "Menu.h"
using namespace std;

bool cycle = true;
string menu {
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

void ShowMenu(vector<Student>& students, vector<Group>& groups, vector<GroupInfo>& groupInfos) {
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
			cout << "\nWhat do you want to display?"
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
					cout << "Enter group number: "; 
					string groupNum; cin >> groupNum;
					vector<Student> studentsFromGroup = FindStudentsFromGroup(students, groups, groupNum);
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
					cout << "Enter group number: "; cin >> groupNum;
					DisplayStudentsAverageFromGroup(students, groupNum);
					break;
				}
			}
			break;
		}
		case '2':
		{
			cout << "What do you want to add? \n[1] Group\t[2] Student\nEnter your choice: ";
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
			}
			break;
		}
		case '3':
		{
			cout << "What do you want to delete? \n[1] Group\t[2] Student\nEnter your choice: ";
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
			}
			break;
		}
		case '4':
		{
			cout << "What do you want to modify? \n[1] Group\t[2] Student\nEnter your choice: ";
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
			}
			break;
		}
		case '5': {
			UpdateGeneralInfo(groups, students, groupInfos);
			WriteGeneralInfo(groupInfos);
			cout << "\n Count.txt updated\n";
			break;
		}
	}
}

int main()
{
	vector<Group> groups;
	vector<Student> students;
	vector<GroupInfo> groupInfos;

	ReadGroups(groups);
	ReadStudents(students, groups);

	while (cycle) {
		ShowMenu(students, groups, groupInfos);
		menu = "\n[1] Display information\t"
			"[2] Add new element\t"
			"[3] Delete element\t"
			"[4] Modify Element\n"
			"[5] Update Count.txt\t"
			"[0] Exit\n\n"
			"Enter your choice: ";
	}
}
