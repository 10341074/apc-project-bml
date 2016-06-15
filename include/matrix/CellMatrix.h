#ifndef CELLMATRIX_H
#define CELLMATRIX_H
#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
// #include <memory>

#include "Template.h"
#include "Color.h"
#include "Row.h"
#include "Coordinates.h"
#include "Cell.h"
// #include "DynRow.h"
// #include "Col.h"

//using CarsDataIn		= 				 std::vector< Cell >  ;			
using CarsDataIn		= 				 std::vector< Color >  ;			
//using CarsData 		= std::list< std::vector< Cell > >;
using CarsData 		= std::list< std::vector< Color > >;
using CarsD 			= std::list< std::vector< Color > >;

// idea: per liste white,blue,red prima lista poi vector
//using OneColor		= std::list< Cell * >;
using OneColor		= std::list< Coordinates >;

class CellMatrix;
class CellMatrixRows;
class CellMatrixCols;


CarsDataIn::const_iterator find_cell(const CarsData & d, const std::size_t & i, const std::size_t & j);
CarsDataIn::iterator find_cell(CarsData & d, const std::size_t & i, const std::size_t & j);
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
		friend CellMatrixRows;
		friend CellMatrixCols;
};

class CellMatrix {
	protected:
		MatrixType 		type = None;
		OwnerData * 	pvec = nullptr;
	
		std::size_t ext_size = 0;
		std::size_t inn_size = 0;

	public:
		CellMatrix(MatrixType t, OwnerData * d) : type(t), pvec(d) {}
		~CellMatrix() {}
	
		void push_back(CarsData & l2, const std::size_t & count);
		void push_back_white(OneColor & l2);
		void push_back_blue(OneColor & l2);
		void push_back_red(OneColor & l2);
//		void border_columns();
		void update_data();
			
		friend std::ostream & operator<<(std::ostream & os, CellMatrix & mat);
};

class CellMatrixRows: public CellMatrix {
	public:
	CellMatrixRows() = delete;
	CellMatrixRows(OwnerData * d) : CellMatrix(ByRows, d) {}

	void move_forward(const Color & cl);
	void move_white(const Color & cl);
	friend std::ostream & operator<<(std::ostream & os, CellMatrixRows & mat);
};
class CellMatrixCols: public CellMatrix {
	public:
	CellMatrixCols() = delete;
	CellMatrixCols(OwnerData * d) : CellMatrix(ByCols, d) {}

	void move_forward(const Color & cl);
	void move_white(const Color & cl);
	friend std::ostream & operator<<(std::ostream & os, CellMatrixCols & mat);
};

/*
//*/
#endif

