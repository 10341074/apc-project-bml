#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
// #include <memory>

#include "Template.h"
#include "Color.h"
// #include "Row.h"

class Cell;

class CellNBHD {
	private:
		Cell * cell_u;	// up
		Cell * cell_d;	// down
		Cell * cell_l; // left
		Cell * cell_r; // right
	public:
		
	friend class Cell;
};

class Cell {
	private:
		Color 		color;
		CellNBHD 	nbhd;
	public:
	Cell(Color color);
	void print_color() const;
		
};

void f();
#endif
