//This file implements the operations available to the Course class.
#include "course.h"

// constructor
Course::Course()
{
	course_designator = NULL;
	course_name = NULL;
	visited = false;
}
	
// destructor
Course::~Course()
{
	if(course_designator)
	{
		delete course_designator;
		course_designator = NULL;
	}

	if(course_name)
	{
		delete course_name;
		course_name = NULL;
	}
}

// adds a new Course
int Course::add_course(char * course_designator, char * course_name)
{
	if(!course_designator) return 0;
	
	this->course_designator = new char[strlen(course_designator)+1];
	strcpy(this->course_designator, course_designator);

	this->course_name = new char[strlen(course_name)+1];
	strcpy(this->course_name, course_name);

	return 1;
}

// copies Course
int Course::copy_course(const Course & new_course)
{
	if(!new_course.course_designator) return 0;

	if(course_designator) delete [] course_designator;
	if(course_name) delete [] course_name;

	course_designator = new char[strlen(new_course.course_designator)+1];
	strcpy(course_designator, new_course.course_designator);

	course_name = new char[strlen(new_course.course_name)+1];
	strcpy(course_name, new_course.course_name);

	return 1;

}

// displays a Course
int Course::display()
{
	if(!course_designator) return 0;

	cout << course_designator
		 << " " 
		 << course_name
		 << '\n';

	return 1;
}

// compares Course to input
bool Course::compare(char * match)
{
	if(strcmp(match, this->course_designator)==0)
		return true;
	else
		return false;

}

// sets Course visited boolean flag
bool Course::visit(bool visited)
{
	if(visited == true)
		return true;
	else
		return false;
}
