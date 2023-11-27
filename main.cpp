// Craig Bodo
// This program is designed to help students map out the prerequisite courses needed to advance toward a CS degree. 
// It uses a graph data structure to model the connections bewteen courses and their prerequisites.
// This program implements both breadth first and depth first graph traversal algorithms.

#include "course.h"

const int SIZE = 100;

// Welcome prompt
void welcome()
{
	cout << "Welcome to Course Manager.\n"
		<<"\nThis program is designed to allow you to add courses and their prerequisites to track your Computer Science path.\n";
}

// Menu prompt
void menu()
{
	cout << "\nMenu:\n"
		<< "\n1. Add a course"
		<< "\n2. Add prerequisite to exisiting course"
		<< "\n3. Import courses and prerequisites from file"
		<< "\n4. See all courses"
		<< "\n5. See a course's prerequisites"
		<< "\n6. See what's available after completing a course"
		<< "\n7. See your graduation path from a course"
		<< "\n8. Exit\n";
}

// Utility function that allows client program to prompt user to repeat an iterative process
bool again(int again)
{
	char response;
	bool repeat = false;

	if(again == 1)
		cout << "\nAdd another course? Y or N: ";
	if(again == 2)
		cout << "Add another prerequisite to this course? Y or N: ";
	if(again == 3)
		cout << "\nAdd prerequisites to another course? Y or N: ";
	if(again == 4)
		cout << "\nSearch a different course? Y or N: ";
	cin >> response;
	cin.ignore(100, '\n');

	if(toupper(response) == 'Y')
		repeat = true;
	else
		repeat = false;

	return repeat;
}

// Adds whitespace for client program readability
void whitespace() { cout << endl; }

// Converts char array to uppercase
void uppercase(char * string) {
	int i = 0;
	while(string[i] !='\0')
	{
		if(string[i]>='a' && string[i]<='z'){
            string[i]=string[i]-32;
        }
        ++i;
	}
}

// Option 1: Add course
int add_course(Table & course_path, Course to_add, char * course_designator, char * course_name, char * prerequisite)
{
	whitespace();

	cout << "\nNote: Add lowest level courses first (e.g. CS 162 before CS 163).\n";

	do
	{
		cout << "\nPlease enter course designator (e.g. CS 162): ";
		cin.get(course_designator, SIZE, '\n');
		cin.ignore(SIZE, '\n');
		uppercase(course_designator);

		cout << "Please enter course name: ";
		cin.get(course_name, SIZE, '\n');
		cin.ignore(SIZE, '\n');
	
		//add the course to course class
		to_add.add_course(course_designator, course_name);
		//insert the course into the table
		course_path.insert_vertex(to_add);

	} while(again(1));

	return 0;
}

// Option 2: Add prerequisite to existing course
int add_prerequisite(Table & course_path, char * course_designator, char * prerequisite) 
{
	whitespace();

	do
	{
		cout << "\nEnter a course designator to add its prerequisite (e.g. CS 162): ";
		cin.get(strdup(course_designator), SIZE, '\n');
		cin.ignore(SIZE, '\n');
		uppercase(course_designator);

		do
		{
			cout << "Adding prerequisite for " << course_designator << endl;
			cout << "Enter course designator for prerequisite (e.g. CS 162): ";
			cin.get(prerequisite, SIZE, '\n');
			cin.ignore(SIZE, '\n');
			uppercase(prerequisite);
			//connects a course with its prerequisite
			course_path.insert_edge(course_designator, prerequisite);	

		} while(again(2));

	} while(again(3));

	return 0;
}

// Option 3: Import courses and prerequisites from file
int add_from_file(Table & course_path, Course to_add, char * course_designator, char * course_name, char * prerequisite)
{
	//imports courses from file into table
	cout << "\nImporting courses from file...\n";
	ifstream course_file;
	course_file.open("courses.txt");

	if(!course_file)
	{
		cout << "Error: No file.";
		return 0;
	}

	course_file.get(course_designator, SIZE, '\n');
	course_file.ignore(SIZE, '\n');

	while(course_file && !course_file.eof())
	{
		course_file.get(course_name, SIZE, '\n');
		course_file.ignore(SIZE, '\n');
		//adds imported course to graph

		if(to_add.add_course(course_designator, course_name)) {
			course_path.insert_vertex(to_add);
			cout << "Importing ... ";
			to_add.display();
		}
		else
			cout << "\nCould not import courses.\n";

		course_file.get(course_designator, SIZE, '\n');
		course_file.ignore(SIZE, '\n');
	}

	course_file.close();

	//imports prerequisites from file
	cout << "Importing prerequisites from file...\n";
	ifstream prerequisite_file;
	prerequisite_file.open("prerequisites.txt");
	
	if(!prerequisite_file)
	{
		cout << "Error: No file.";
		return 0;
	}

	prerequisite_file.get(course_designator, SIZE, '\n');
	prerequisite_file.ignore(SIZE, '\n');

	while(prerequisite_file && !prerequisite_file.eof())
	{
		prerequisite_file.get(prerequisite, SIZE, '\n');
		prerequisite_file.ignore(SIZE, '\n');

		//creates edge between course and prerequisite
		if(!course_path.insert_edge(course_designator, prerequisite))
			cout << "\nCould not import prerequisites.\n";

		prerequisite_file.get(course_designator, SIZE, '\n');
		prerequisite_file.ignore(SIZE, '\n');
	}

	prerequisite_file.close();

	cout << "Data imported successfully.\n";

	return 0;
}

// Option 4: See all courses
int show_courses(Table & course_path)
{
	whitespace();

	cout << "\nAll courses:\n\n";

	course_path.display_all();

	return 0;
}

// Option 5: See a course's prerequisites
int show_prerequisites(Table & course_path, char * course_designator)
{
	whitespace();

	do
	{
		cout << "\nEnter a course to see its prerequisites.\n"
			<< "\nCourse designator (e.g. CS 162): ";
		cin.get(course_designator, SIZE, '\n');
		cin.ignore(SIZE, '\n');
		uppercase(course_designator);

		// displays courses available after completing a course

		cout << "\nCourses available after taking " << course_designator << ":\n";

		if(!course_path.display_adjacent(course_designator))
			cout << "\nNo prerequisites.\n";

	} while(again(4));

	return 0;
}

// Option 6: See what's available after completing a course
int show_next(Table & course_path, char * course_designator)
{
	whitespace();

	do
	{
		cout << "\nWhat comes next? Enter a course to see what you can take after completing it.\n"
			<< "\nCourse designator (e.g. CS 162): ";
		cin.get(course_designator, SIZE, '\n');
		cin.ignore(SIZE, '\n');
		uppercase(course_designator);

		cout << "\nCourses available after " << course_designator << ":\n";

		if(!course_path.breadth_first_search(course_designator))
			cout << "\nNothing to display.";

	} while(again(4));

	return 0;
}

// Option 7: See your graduation path from a course
int show_graduation_path(Table & course_path, char * course_designator)
{
	whitespace();

	do
	{
		cout << "\nHow do I get my degree? Enter a course to see all the courses you need to take after it to graduate\n"
			<< "\nCourse designator (e.g. CS 162): ";
		cin.get(course_designator, SIZE, '\n');
		cin.ignore(SIZE, '\n');
		uppercase(course_designator);
		
		cout << "\nDegree path for " << course_designator << ":\n";

		if(!course_path.depth_first_search(course_designator))
			cout << "\nNothing to display.";

	} while(again(4));

	return 0;
}

bool is_valid_response(int response)
{
	return response > 0 || response < 9;
}

// Get user response
int menu_response()
{
	int response = 0;
	do
	{
		cout << "\nChoose a menu option: ";
		cin  >> response;
		cin.ignore(SIZE, '\n');
	} while(!is_valid_response(response));

	return response;
}

int press_to_return()
{
	cout << endl << "Press enter to return to menu...";
	cin.get();
	return 0;
}

int main()
{
	Table course_path;
	Course to_add;
	char course_designator[SIZE];
	char course_name[SIZE];
	char prerequisite[SIZE];
	int response = 0;

	whitespace();
	welcome();
	do
	{
		menu();	
		response = menu_response();

		switch (response)
		{
		case 1:
			add_course(course_path, to_add, course_designator, course_name, prerequisite);
			press_to_return();
			break;
		case 2:
			add_prerequisite(course_path, course_designator, prerequisite);
			press_to_return();
			break;
		case 3:
			add_from_file(course_path, to_add, course_designator, course_name, prerequisite);
			press_to_return();
			break;
		case 4:
			show_courses(course_path);
			press_to_return();
			break;
		case 5:
			show_prerequisites(course_path, course_designator);
			press_to_return();
			break;
		case 6:
			show_next(course_path, course_designator);
			press_to_return();
			break;
		case 7:
			show_graduation_path(course_path, course_designator);
			press_to_return();
			break;
		default:
			break;
		}

	} while (response != 8);

	return 0;
}
