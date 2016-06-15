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
		Cell() {}
		Cell(Color color);
	
		void update_u(Cell * p);
		void update_d(Cell * p);
		void update_l(Cell * p);
		void update_r(Cell * p);
		
		Color & 				get_color();
		const Color & 		get_color() const;
		
		Cell * get_u();		// now non-const can return non-const (possible modifications)
		Cell * get_d();		// put const versiion ?? or more time in construction?
		Cell * get_l();
		Cell * get_r();
		
		// to print -> const version
		Cell * const get_u() const;
		Cell * const get_d() const;
		Cell * const get_l() const;
		Cell * const get_r() const;
	

		void print_color() const;
		friend std::ostream & operator<<(std::ostream & os, const Cell & c);
};

void f();
#endif
