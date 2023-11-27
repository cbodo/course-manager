// This file implements the operations available for the graph ADT.
#include "course.h"

// constructor
Table::Table(int size)
{
	prerequisite_list = new Vertex[size];
	for(int i = 0; i < size; ++i)
	{
		prerequisite_list[i].course = NULL;
		prerequisite_list[i].head = NULL;
	}

	list_size = size;
}

// destructor
Table::~Table()
{
	if(prerequisite_list)
	{
		for(int i = 0; i < list_size; ++i)
		{
			if(prerequisite_list[i].course)
			{
				delete prerequisite_list[i].course;
				prerequisite_list[i].course = NULL;
			}
			if(prerequisite_list[i].head)
			{
				delete prerequisite_list[i].head;
				prerequisite_list[i].head = NULL;
			}
		}
	}
}

// adds a course to the table
int Table::insert_vertex(const Course & to_add)
{
	for(int i = 0; i < list_size; ++i)
	{
		if(!prerequisite_list[i].course)
		{
			prerequisite_list[i].course = new Course;
			prerequisite_list[i].course->copy_course(to_add);
			return 1;
		}
	}
	return 0;
}

// finds the index of a given course in the table
int Table::find_location(char * course_designator)
{
	for(int i = 0; i < list_size; ++i)
	{
		if(prerequisite_list[i].course && prerequisite_list[i].course->compare(course_designator))
			return i;
	}
	return -1;
}

// connects course to prerequisite courses
int Table::insert_edge(char * current_vertex, char * to_attach)
{
	// assigns index of course that follows to variable
	int i = find_location(current_vertex);
	// assigns index of prerequisite course to variable	
	int j = find_location(to_attach);

	if(i == j) return 0;
	if(i == -1 || j == -1) return 0;

	Node * temp = new Node;
	temp->adjacent = prerequisite_list + j;
	temp->next = prerequisite_list[i].head;
	prerequisite_list[i].head = temp;
	return 1;
}

// displays prerequisite for course
int Table::display_adjacent(char * course_designator)
{
	int i = find_location(course_designator);
	if(i == -1) return 0;
	if(!prerequisite_list[i].head || !prerequisite_list->course) 
		return 0;

	Node * current = prerequisite_list[i].head;

	while(current)
	{
		if(current->adjacent->course)
			current->adjacent->course->display();
		current = current->next;
	}
	return 1;
}

// displays all courses in the table
int Table::display_all()
{
	if(!prerequisite_list) return 0;

	for(int i = 0; i < list_size; ++i)
	{
		if(prerequisite_list[i].course)
			prerequisite_list[i].course->display();
		else
			return 0;
	}

	return 1;

}

// calls private breadth_first_search function
int Table::breadth_first_search(char * course_designator)
{
	return breadth_first_search(course_designator, prerequisite_list);
}

// shows courses that can be taken after a given course
int Table::breadth_first_search(char * course_designator, Vertex * prerequisite_list)
{
	bool visited = false;
	int j = find_location(course_designator);
	if(j == -1) return 0;
	if(!prerequisite_list) return 0;

	for(int i = 0; i < list_size; ++i)
	{
		Node * current = prerequisite_list[i].head;
		while(current && !visited && i != j)
		{
			if(current->adjacent->course->compare(course_designator))
			{
				prerequisite_list[i].course->display();
				visited = true;
			}
			current = current->next;
		}
		visited = false;
	}

	return 1;
}

// calls private depth_first_search function
int Table::depth_first_search(char * course_designator)
{
	int index = find_location(course_designator);
	return depth_first_search(index, prerequisite_list);
}

// shows the path of each course to its prerequisites
int Table::depth_first_search(int index, Vertex * prerequisite_list)
{
	bool visited = false;
	if(index == -1 || !prerequisite_list) return 0;

	Node * current = prerequisite_list[index].head;	

	while(current && index < list_size)
	{
		if(!prerequisite_list[index].course->visit(visited))
		{
			current->adjacent->course->display();
			prerequisite_list[index].course->visit(visited=true);
		}
		current = current->next;
	} 
	
	if(index < list_size)
		depth_first_search(index + 1, prerequisite_list);
	else
		return 0;

	return 1;
}
