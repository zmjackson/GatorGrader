#include "stdafx.h"
#include "Instructor.h"
#include "Assignment.h"
#include "Student.h"
#include "Course.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

Instructor::Instructor() {
	instructorName = "Unkown Instructor";
}

Instructor::Instructor(string name) {
	this->instructorName = name;
}

void Instructor::setName(string name) {
	this->instructorName = name;
}

string Instructor::getName() {
	return instructorName;
}

//vector<Course*> &Instructor::getCourseList() {
//	return courseList;
//}

void Instructor::firstTimeInstructor() {
	cout << "Welcome to GatorGrader. Please enter your name:" << endl;
	getline(cin, instructorName);

	addCourse();
}

void Instructor::addCourse() {

	string addName;
	cout << "Enter the name of a course: " << endl;
	getline(cin, addName);

	vector<Course*>::iterator it;

	for (it = courseList.begin(); it != courseList.end(); it++) {

		if ((*it)->getCourseName == addName) {

			Course* course = new Course(addName);
			courseList.push_back(course);
			break;
		}
	}	
}

void Instructor::addCourse(string name) {
	Course *course = new Course(name);
	courseList.push_back(course);
	currentCourse = course;
}

void Instructor::removeCourse() {
	string removeName;
	cout << "Enter the name of the course you would like to delete:" << endl;
	getline(cin, removeName);
	
	vector<Course*>::iterator it;
	for (it = courseList.begin(); it != courseList.end();) {
		if ((*it)->getCourseName() == removeName) {
			delete *it;
			it = courseList.erase(it);
		}
		else {
			it++;
		}
	}
}

void Instructor::mainMenu() {
	cout << "Your Courses:" << endl;
	for (unsigned int i = 0; i < courseList.size(); i++) {
		cout << courseList[i]->getCourseName() << endl;
	}

	string courseChoice;

	while (true) {
		cout << "Enter a course name to view options for that course or choose an option below:" << endl;
		cout << "1. Add course" << endl;
		cout << "2. Remove course" << endl;

		getline(cin, courseChoice);

		bool courseFound = false;

		if (courseChoice == "1" || courseChoice == "Add course" || courseChoice == "add course" || courseChoice == "Add Course") {
			addCourse();
		}

		if (courseChoice == "2" || courseChoice == "Remove course" || courseChoice == "remove course" || courseChoice == "Remove Course") {
			removeCourse();
		}

		for (unsigned int i = 0; i < courseList.size(); i++) {
			if (courseList[i]->getCourseName() == courseChoice) {
				currentCourse = courseList[i];
				courseFound = true;
				currentCourse->courseMenu();
			}
		}

		if (courseFound == false) {
			cout << "You have no course '" << courseChoice << "'." << endl;
		}
	}
}

void Instructor::init() {
	ifstream file("courses.txt");

	if (!file) {
		firstTimeInstructor();
	}
	else {
		string foundCourseData;
		string foundCourseName;
		while (getline(file, foundCourseData)) {

			if (foundCourseData.front() == '#') {
				foundCourseData.erase(foundCourseData.begin());
				addCourse(foundCourseData);
				foundCourseName = foundCourseData;
				continue;
			}			

			if (foundCourseData.at(foundCourseName.size()) == '$') {
				foundCourseData.erase(0, foundCourseName.size() + 1);
				string foundFirstName, foundLastName;
				istringstream studentName(foundCourseData);
				studentName >> foundFirstName >> foundLastName;
				currentCourse->addStudent(foundFirstName, foundLastName);
				continue;
			}

			if (foundCourseData.at(foundCourseName.size()) == '@') {
				foundCourseData.erase(0, foundCourseName.size() + 1);
				string foundAssignmentName;
				double foundAssignmentPoints;
				istringstream assignmentAttributes(foundCourseData);
				assignmentAttributes >> foundAssignmentName >> foundAssignmentPoints;
				currentCourse->addAssignment(foundAssignmentName, foundAssignmentPoints);
				continue;
			}
		}
	}
}