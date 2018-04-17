#pragma once
//#include "Assignment.h"
//#include "Student.h"
//#include "Instructor.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Assignment;
class Student;

class Course {
private:
	std::string courseName;
	std::vector<Student*> studentList;
	std::vector<Assignment*> assignmentList;
public:
	enum saveType {courseSave, studentSave, assignmentSave, masterAssignmentSave};
	Course(std::string name);
	~Course();
	void setCourseName(std::string name);
	std::string getCourseName();
	std::string tag(saveType type);
	void addStudent();
	void addStudent(std::string first, std::string last);
	void save(std::string newItem, double numPoints, saveType addItem);
	void addAssignment();
	void addAssignment(std::string name, double points);
	void print();
	void courseMenu();
	void refresh();
};