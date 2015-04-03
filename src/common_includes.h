/***********************************************************************************
 * Design & Analysis of Algorithm - Project
 * File name 	: common_includes.cpp
 * Module 	: Maze.out
 * Description	: Common Includes and MACROs
***********************************************************************************/
#ifndef _COMMON_
#define _COMMON_

/*For randomization*/
#include <stdlib.h>
#include <time.h>

/*for uint16_t*/
#include <stdint.h>
#include <stdlib.h>/* strtol */
#include <unistd.h>/* getopt */

#include <iostream>
#include <vector>
#include <string.h>
#include <map>
#include <list>
#include <set>
#include <algorithm>
#include <iomanip> /*for std::stew*/
#include <sstream> /*To avoid strtol*/
using namespace std;

typedef enum {
        edge_top = 0,
        edge_bottom,
        edge_right,
        edge_left,
        edge_all
} edge_t;

typedef struct __position{
        short _x;
        short _y;
        __position (): _x(0), _y(0)
        {}
} position;

typedef enum {
        not_set,
        on_left,
        on_right,
        on_top,
        on_bottom
} Location;

typedef enum {
        value_solution,
        value_traverse
} ValueType;


typedef struct __Node{
        int cell_id;
        bool open;

        Location location;
        __Node() : location(not_set), open(false) {}
        __Node(int id, Location loc) : cell_id(id), location(loc), open(false) {}

} Node;

typedef struct __Visit{
        static uint16_t time;

        static void clear() { time = 0; }
} Visit;

#define EDGE_MAX 4
#define STR_GETOPT "r:c:"
#define IS_VALID_INDEX(index, size) (index >= 0 && index < size) //Check if row is valid
#define IS_VALID(x,y) IS_VALID_INDEX(x, _rows) && IS_VALID_INDEX(y, _columns) //Check if column is valid

#define USAGE_EXIT(process)\
		cout << endl << "\tIllegal Usage. Expected option <-r> <-c>. Correct usage for the this utility is:\n"; \
		cout << endl << "\t" << process << " -r <num_rows> <num_columns>\n";\
		cout << endl << "\t \t \t @Maze utility...\n"; \
		exit(-1);


#endif
