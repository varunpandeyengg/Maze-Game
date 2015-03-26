/***********************************************************************************
 * Design & Analysis of Algorithm - Project
 * File name 	: grid.h
 * Module 	: Maze.out
 * Description	: Header of the actual maze grid that creates and solves the MAZE for you.
 
***********************************************************************************/
#ifndef _GRID_
#define _GRID_
#include "common_includes.h"
#include "cell.h"
#include <sstream>


class Grid{
	//Rows and Column count of the grid 
	uint16_t _rows; 
	uint16_t _columns;
	
	//Total number of cells
	int _total_cells;
	//Acual Grid
	vector < vector <Cell> > _grid;

	//Maze graph
	map <int, vector <Node> > _cell_map;
	
	//Nodes alraedy visited, used for DFS
	list <int> _visited_cells;

	//Parent list for BFS solution
	map <int, int> _parent_map;
	
	//Private function, check cpp for details
	void display_grid();
	void cellid_to_index (const int node_id, int& x, int& y);
	void maze_it_up_rec (int current_node_id);
	void knock_wall(int current_node_id, Node node_to_visit);
	void bfs_solution ();	
	void clear_grid();
	bool dfs_solution (int current_node_id = 0);
	void set_cell_value_by_node (const int node_id, uint16_t visit_time);
	
public:
		
	Grid(uint16_t rows, uint16_t column);
	void maze_it_up ();
};

#endif
