#pragma once
#include <vector>

void DisplayGroups(vector<Group>& groups);
void DisplayStudents(vector<Student>& students);
void AddGroup(vector<Group>& groups);
void AddStudent(vector<Student>& students, vector<Group>& groups);
void DeleteGroup(vector<Group>& groups, vector<Student>& students);
void DeleteStudent(vector<Student>& students);
void ModifyGroup(vector<Group>& groups);
void ModifyStudent(vector<Student>& students, vector<Group>& groups);
void DisplayStudentInfo(Student student);
void DisplayMaxAbsencesStudent(vector<Student>& students);
float CountStudentAverage(Student student);
void DisplayStudentsAverageFromGroup(vector<Student>& students, string groupNum);
vector<Student> FindStudentsFromGroup(vector<Student>& students, vector<Group>& groups, string groupName);
void UpdateGeneralInfo(vector<Group>& groups, vector<Student>& students, vector<GroupInfo>& groupInfos);
void SortStudentsByName(vector<Student>& students);
