// This file defines the course class and the graph ADT
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
using namespace std;

class Table;
class Course
{
	public:
		Course();
		~Course();
		int add_course(char * course_designator, char * course_name);
		int copy_course(const Course & new_course);
		bool compare(char * match);
		int display();
		void get_designator();
		bool visit(bool visited);
	private:
		char * course_designator;
		char * course_name;
		bool visited;
};

struct Vertex
{
	Course * course;
	struct  Node * head;
};

struct Node
{
	Vertex * adjacent;
	Node * next;
};

class Table
{
	public:
		Table(int size = 20);
		~Table();
		int insert_vertex(const Course & to_add);
		int find_location(char * course_designator);
		int insert_edge(char * current_vertex, char * to_attach);
		int display_adjacent(char * course_designator);
		int display_all();
		int breadth_first_search(char * course_designator);
		int depth_first_search(char * course_designator);
	private:
		Vertex * prerequisite_list;
		int list_size;
		int breadth_first_search(char * course_designator, Vertex * prerequisite_list);
		int depth_first_search(int index, Vertex * prerequisite_list);
};

