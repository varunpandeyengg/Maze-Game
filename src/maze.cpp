/***********************************************************************************
 * Design & Analysis of Algorithm - Project
 * File name 	: maze.cpp
 * Module 	: Maze.out
 * Description	: Entry point to the project. Just takes user parameter and gets the 
		  value.
***********************************************************************************/

#include "grid.h"
#include "common_includes.h"

int main (int argc, char * const * argv)
{
	uint16_t rows = 0, columns = 0;
	
	char arg;
        while ((arg = getopt (argc, argv, STR_GETOPT)) != -1) {
                switch(arg)
                {
                        case 'r':
				rows = strtol (optarg, NULL, 10); //Base 10
                                break;
			case 'c':
				columns = strtol (optarg, NULL, 10); //Base 10
                                break;
                        default:                //redundant
                                break;
                }
        }

	if (rows <= 0 || columns <= 0 || rows > 10000 || columns  > 1000)
        {
		cout << endl << "\tRows should not be too small or too large.";
                USAGE_EXIT (argv[0]);
        }

	cout << endl << "################Welcome to the maze game################";

	Grid grid(rows, columns);
	grid.maze_it_up ();
	
	cout << endl;

	return 0;
}
