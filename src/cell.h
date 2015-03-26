/***********************************************************************************
 * Design & Analysis of Algorithm - Project
 * File name 	: cell.h
 * Module 	: Maze.out
 * Description	: Header for the cell class that holds the attributes of individual cells in 
		  the grid.
***********************************************************************************/
#ifndef _CELL_
#define _CELL_

#include "common_includes.h"

class Cell{
    	/*Wall Data*/
	bool _top;
        bool _bottom;
        bool _right;
        bool _left;

	/*Unique Identifier for every cell*/
        uint16_t _id;

	/*Cell Value used for display of results*/
        std::string _value;
	
public:

        Cell();
		
	const char* get_value ();
        void set_value (std::string value);
	void unset_edge (edge_t type);
        void set_edge (edge_t edge_type);
	void set_id (int cell_id);
	void print_cell (edge_t edge_type);

};
#endif //_CELL_
