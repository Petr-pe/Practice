#pragma once
#include "Groups_Students.h"
#include <vector>

void ReadGroups(vector<Group>& groups);
void ReadStudents(vector<Student>& students, vector<Group>& groups);
void WriteGroups(vector<Group>& groups);
void WriteStudents(vector<Student>& students);
void WriteGeneralInfo(vector<GroupInfo>& groupInfos);
void DeleteExtraStudents(vector<Student>& students, vector<Group>& groups);