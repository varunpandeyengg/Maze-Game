/***********************************************************************************
 * Design & Analysis of Algorithm - Project
 * File name 	: cell.cpp
 * Module 	: Maze.out
 * Description	: Instance of this class holds the attributes of individual cells in 
		  the grid.
***********************************************************************************/


#include "cell.h"


Cell::Cell() : _top(1), _bottom(1), _right(1), _left(1), _value(" ")
{
}

void Cell::unset_edge (edge_t edge_type)
{
        switch (edge_type)
        {
                case edge_top:
                        _top = false;
                break;
                case edge_bottom:
                        _bottom = false;
                break;
                case edge_right:
                        _right = false;
                break;
                case edge_left:
                        _left = false;
		break;
                case edge_all:
                        _top = false;
                        _bottom = false;
                        _left = false;
                        _right = false;
                break;
        }
}

void Cell::set_edge (edge_t edge_type)
{
        switch (edge_type)
        {
                case edge_top:
                        _top = true;
                break;
                case edge_bottom:
                        _bottom = true;
                break;
                case edge_right:
                        _right = true;
                break;
                case edge_left:
                        _left = true;
                break;
                case edge_all:
                        _top = true;
                        _bottom = true;
                        _left = true;
                        _right = true;
                break;
        }
}

void Cell::set_id (int cell_id)
{
	_id = cell_id;
}

void Cell::print_cell (edge_t edge_type)
{
        switch (edge_type)
        {
                case edge_top:
                         _top ?  cerr << "--------" : cerr << "        ";
                break;
                case edge_bottom:
                         _bottom ? cerr << "--------" : cerr << "        ";
                break;
                case edge_right:
                         _right ? cerr << "|" : cerr << " ";

                break;
                case edge_left:
			 _left ? cerr << "|" : cerr << "  ";
                break;
                case edge_all:
			if (_top) cerr << endl << "--------";
        		if (_left) cerr << endl << "|"; if (_right) cout << "       |";
        		if (_bottom) cerr << endl << "--------";
                break;
        }
}

const char* Cell::get_value ()
{
	return _value.size() ? _value.c_str() : " ";
}
void Cell::set_value (string value)
{
	_value = value + "   ";
}

