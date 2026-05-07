#pragma once
#include <string>
#include <vector>
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
	int absence{};
};
struct GroupInfo {
	string gr_num;
	int studentCount{};
	float avgNotes{};
	int absencesCount{};
};