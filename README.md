# Course Manager
A simple C++ CLI program that helps students manage their courses and degree plans.

## Author

Craig Bodo

craigmbodo@gmail.com

## Description

This program is designed to help students map out the prerequisite courses needed to advance toward a CS degree. It uses a graph data structure to model the connections bewteen courses and their prerequisites. This program also implements both breadth first and depth first graph traversal algorithms.

## Running The Program:

The easiest way to run this program locally is to download or fork into the repository to your system. Then, from the top directory, enter the following command into your console:

```bash
$ ./course_manager
```

You can also compile the program yourself to run locally. From the top directory, enter the following into your console:

```bash
$ g++ -std=c++11 main.cpp course.cpp table.cpp -o course_manager
$ ./course_manager
```

The quickest way to see this program in action is to import the data provided in courses.txt and prerequisites.txt: Once the program has started, select menu item 3 and the data will be automatically imported.