#ifndef CELLMATRIX_H
#define CELLMATRIX_H
#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
// #include <memory>

#include "Template.h"
#include "Color.h"
// #include "Row.h"
#include "Coordinates.h"
#include "Cell.h"
// #include "DynRow.h"
// #include "Col.h"

using CarsDataIn		= 				 std::vector< Cell >  ;			
using CarsData 		= std::list< std::vector< Cell > >;
using CarsD 			= std::list< std::vector< Color > >;

// idea: per liste white,blue,red prima lista poi vector
using OneColor		= std::list< Cell * >;

class CellMatrix;

class OwnerData{
	private:
		CarsData			cars;

		OneColor white; 
		OneColor blue; 
		OneColor red; 
	public:
		void print() const;
		bool choose_white() const;
		friend std::ostream & operator<<(std::ostream & os, const OwnerData & d);
		friend CellMatrix;
};

class CellMatrix {
	protected:
		OwnerData * 	pvec = nullptr;
	
		std::size_t ext_size = 0;
		std::size_t inn_size = 0;

	public:
		CellMatrix(OwnerData * d) : pvec(d) {}
		~CellMatrix() {}
	
		void push_back(CarsData & l2, const std::size_t & count);
		void push_back_white(OneColor & l2);
		void push_back_blue(OneColor & l2);
		void push_back_red(OneColor & l2);
//		void border_columns();
		void update_data();
			
		void move_forward(const Color & cl);
		void move_white(const Color & cl);

		friend std::ostream & operator<<(std::ostream & os, CellMatrix & mat);
};
/*
//*/
#endif

