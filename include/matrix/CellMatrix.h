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

#include "CellData.h"

using CarsDataIn		= 				 std::vector< Cell >  ;			
using CarsData 		= std::vector< std::vector< Cell > >;
using CarsD 			= std::list< std::vector< Color > >;

// idea: per liste white,blue,red prima lista poi vector
using OneColor		= std::vector< Cell * >;

class CellMatrix;
class CellMatrixRows;
class CellMatrixCols;

void one_color_conv(const OneColor_Old & c_old, OneColor & c_new);
class OwnerData{
	private:
		CarsData			cars;

		OneColor white; 
		OneColor blue; 
		OneColor red;
	public:
		void load_data(const OwnerData_Old & d);
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
void two_lines_old(CarsData_Old::iterator it_ext, CarsData_Old::iterator it_ext2, OneColor_Old & white, OneColor_Old & blue, OneColor_Old & red);

/*
//*/
#endif

