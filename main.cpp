#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Groups_Students.h"
#include "Files_func.h"
#include "Menu.h"
using namespace std;

bool cycle = true;

int main()
{
	vector<Group> groups;
	vector<Student> students;
	vector<GroupInfo> groupInfos;

	ReadGroups(groups);
	ReadStudents(students, groups);

	while (cycle) {
		ShowMenu(students, groups, groupInfos, cycle);
		menu = "\n\n\n[1] Display information\t"
			"[2] Add new element\t"
			"[3] Delete element\t"
			"[4] Modify Element\n"
			"[5] Update Count.txt\t"
			"[0] Exit\n\n"
			"Enter your choice: ";
	}
}
