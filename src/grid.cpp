/***********************************************************************************
 * Design & Analysis of Algorithm - Project
 * File name 	: grid.cpp
 * Module 	: Maze.out
 * Description	: Actual Maze grid that creates and solves the MAZE for you.
***********************************************************************************/
#include "grid.h"

uint16_t Visit::time = -1; //Statis variable for printing o/p

/*
 * Constructor, creates a row x column grid and a graph for processing
 */
Grid::Grid (uint16_t rows, uint16_t columns) : _rows(rows), _columns(columns)
{
	int cell_id = 0;
	_total_cells = _rows * _columns;
	//Initializing graph and its corresponding graph
	for (int i = 0; i < _rows; i++)
	{
		vector <Cell> cell_row;
                for (int j = 0; j < _columns; j++)
		{
			Cell cell;
			cell_row.push_back (cell);

			vector <Node> out_edges;
			
			if (IS_VALID(i, j-1)) out_edges.push_back (Node (cell_id-1, on_left));
			if (IS_VALID(i, j+1)) out_edges.push_back (Node (cell_id+1, on_right));
			if (IS_VALID(i-1, j)) out_edges.push_back (Node (cell_id-_columns, on_top));
			if (IS_VALID(i+1, j)) out_edges.push_back (Node (cell_id+_columns, on_bottom));
			_cell_map [cell_id] = out_edges;
		        
			
			cell_row[j].set_edge (edge_all);
			cell_row[j].set_id (cell_id++);
		}
		
		_grid.push_back(cell_row);
	}
	
	_grid[0][0].unset_edge (edge_top);
        _grid[_rows-1][_columns-1].unset_edge (edge_bottom);
}

/*
 * Displays the current state of the grid
 */
void Grid::display_grid ()
{
	
	for (int i = 0; i < _rows; i++)
	{
		cerr << endl;
	        if (i == 0)
		{
			for (int j = 0; j < _columns; j++)
                        	cerr << "+", _grid[i][j].print_cell(edge_top);
			cerr << "+", cerr << endl;
		}
		
		for (int j = 0; j < _columns; j++)
                {
			if (!j)	
				_grid[i][j].print_cell(edge_left);
			
		//	cerr << " " << _grid[i][j].get_value() <<  "   ", _grid[i][j].print_cell(edge_right);
			cerr << std::setw(8) << _grid[i][j].get_value(), _grid[i][j].print_cell(edge_right);

		}
	
		cerr << endl;
                for (int j = 0; j < _columns; j++)
                         cerr << "+", _grid[i][j].print_cell(edge_bottom);
		cerr << "+"; 
	}	
        
	cerr << endl;
}

/*
 *  Entry Point to the game
 *  1. Creates the Maze
 *  2. Prints the solution
 *  3. Prints the DfS and BFS traversal
 */

void Grid::maze_it_up ()
{
	srand (time(0)); // use current time as seed for random generator
	
	clear_grid();	
	maze_it_up_rec (0);
	cout << endl << "Maze : " << endl;
	display_grid();

	clear_grid();
	Visit::time = 0; // To print solution
        cout << endl << "DFS Solution : " << endl;
        dfs_solution(0); //Print Solution
	display_grid();

	
	clear_grid();
	Visit::time = 1;	
	cout << endl << "DFS Traversal : " << endl;
	dfs_solution(0); 
	display_grid();

	clear_grid();
	Visit::time = 0; // To print solution
        cout << endl << "BFS Solution : " << endl;
        bfs_solution(); //Print Solution
        display_grid();

	clear_grid();
	Visit::time = 1;
	cout << endl << "BFS Traversal : " << endl;
	bfs_solution();
	display_grid();
}
/*
 * Most Important part of the program. This function recursively creats a maze
 */
void Grid::maze_it_up_rec (int current_node_id)
{
	bool path_found = false;
	//add the current node in visited list
	_visited_cells.push_back (current_node_id);
	
	if (current_node_id == _total_cells - 1)
	        return;

	//extract the outgoing edges	
	vector <Node> out_edges = _cell_map [current_node_id];

	set<int> unique_choices;
	while (1){ //till I make the all the choices 
	
		if (unique_choices.size() >= out_edges.size())
                        break;
	
		/*I am doing this to ensure unique path at every run*/
		int random_choice = rand() % out_edges.size();
		Node node = out_edges [random_choice];
		unique_choices.insert (node.cell_id);

		//if node already visited, explore next
		std::list <int>::iterator iter = std::find (_visited_cells.begin(), _visited_cells.end(), node.cell_id);
		if (iter != _visited_cells.end())
			continue;	
		out_edges [random_choice].open = true;
		_cell_map [current_node_id] = out_edges; //Save it back to the map	
		knock_wall (current_node_id, node);
		maze_it_up_rec (node.cell_id); //Recursice call
	}
}

/*
 * Erases the wall between the current node and the node that we are about to visit
 */
void Grid::knock_wall(int current_node_id, Node node_to_visit)
{
//	display_grid();
	int grid_x, grid_y;
	cellid_to_index (current_node_id, grid_x, grid_y);

	switch (node_to_visit.location)
	{
		case on_left:
			_grid[grid_x][grid_y].unset_edge (edge_left);
			_grid[grid_x][grid_y - 1].unset_edge (edge_right);  //To visit
			break;
		case on_right:
			_grid[grid_x][grid_y].unset_edge (edge_right);
			 _grid[grid_x][grid_y + 1].unset_edge (edge_left);  //To visit
			break;
		case on_top:
			_grid[grid_x][grid_y].unset_edge (edge_top);
			 _grid[grid_x - 1][grid_y].unset_edge (edge_bottom);  //To visit
			break;
		case on_bottom:
			_grid[grid_x][grid_y].unset_edge (edge_bottom);
			_grid[grid_x + 1][grid_y].unset_edge (edge_top); //To visit
			break;
	}
}

/*
 * BSF traversal to the graph unless final target is found
 * returns true is reached the target
 */

bool Grid::dfs_solution (int current_node_id)
{
	//add the current node in visited list
	_visited_cells.push_back (current_node_id);
	
	if (current_node_id == _total_cells - 1)
        {
		set_cell_value_by_node(current_node_id, Visit::time);
	        return true;
	}
	
	if (Visit::time)
	{
		set_cell_value_by_node(current_node_id, Visit::time);
		Visit::time++;
	}
	
	//extract the outgoing edges	
	vector <Node> out_edges = _cell_map [current_node_id];
		
	for (int i = 0; i < out_edges.size(); i++) { //till I make the all the choices 
		std::list <int>::iterator iter = std::find (_visited_cells.begin(), _visited_cells.end(), out_edges[i].cell_id);
		if (iter != _visited_cells.end() || !out_edges[i].open)
			continue;
	
		if (dfs_solution (out_edges[i].cell_id))	
		{
			if (!Visit::time)
				set_cell_value_by_node(current_node_id, Visit::time);

			return true;
		}
		
	}
	
	return false;
}
/*
 * BSF traversal to the graph unless final target is found
 */
void Grid::bfs_solution ()
{
	list <int> nodes_to_visit; //List used as Queue ADT
	nodes_to_visit.push_back(0);	//first node pushed

	while (nodes_to_visit.size())
	{
		int current_node_id = nodes_to_visit.front();
		nodes_to_visit.pop_front(); //Pop the Queue
		
		if(Visit::time)
			set_cell_value_by_node(current_node_id, Visit::time++);

		//if node not visited and it is open, explore it
		if (current_node_id == _total_cells - 1)
			break;

		//extract the outgoing edges	
		vector <Node> out_edges = _cell_map [current_node_id];
		
		for (int i = 0; i < out_edges.size(); i++) { //till I make the all the choices 
			std::list <int>::iterator iter = std::find (_visited_cells.begin(), 
							 _visited_cells.end(), out_edges[i].cell_id);

			if (iter != _visited_cells.end() || !out_edges[i].open)
				continue;
			
			nodes_to_visit.push_back (out_edges[i].cell_id);
			_parent_map [out_edges[i].cell_id] = current_node_id;
		}
	}

	if (!Visit::time)
	{
		int current_node_id = _total_cells - 1;
		while (true)
		{
			set_cell_value_by_node(current_node_id, Visit::time);
			if (!current_node_id) //Reached cell 0 aka source
				break;
			current_node_id = _parent_map[current_node_id];			
		}
	}
}

void Grid::cellid_to_index (const int node_id, int& x, int& y)
{
	x = node_id / _columns; //max = _size - 1
        y = node_id % _columns; //max = _size - 1
}
/*
 * Clears the value for o/p of the grid
 */
void Grid::clear_grid()
{
	Visit::clear();
	_visited_cells.clear();
	for (int i = 0; i < _rows; i++)
                for (int j = 0; j < _columns; j++)
			_grid[i][j].set_value(string(""));
}

/*
 * Sets the cell value to the appropriate referenced by node id
 */
void Grid::set_cell_value_by_node (const int node_id, uint16_t visit_time)
{
	int grid_x, grid_y;
	cellid_to_index (node_id, grid_x, grid_y);
	
	if (visit_time <= 0)
		_grid[grid_x][grid_y].set_value("#");
	else
	{
		stringstream value;
		value << visit_time;
		_grid[grid_x][grid_y].set_value(value.str());
	}	
}

