#ifndef CELLTRAFFIC_H
#define CELLTRAFFIC_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

#include "Color.h"
#include "Row.h"
#include "DynRow.h"
#include "VecVector.h"
#include "VecVectorS.h"
#include "VecVectorD.h"
#include "Tokenize.h"
#include "CellMatrix.h"
#include "CellData.h"
class CellTraffic{
	private:
		MatrixType type = None;
		OwnerData_Old	data_old;
		OwnerData	data;
		
		CellMatrixRows * rmat = nullptr;
		CellMatrixCols * cmat = nullptr;
		CellMatrix 		* mat = nullptr;
		CellMatrix 		* mat_inactive = nullptr;
	public:
		CellTraffic();
		~CellTraffic();
		void tok_push_back(const std::string & line, const std::size_t & rowsCount);
		friend std::ostream & operator<<(std::ostream & os, const CellTraffic & traffic);
		friend std::istream & operator>>(std::istream & is, CellTraffic & traffic);
		void print() const;
		void move_forward(const MatrixType & t, const Color & cl);
		void move_white(const MatrixType & t, const Color & cl);
		bool choose_white() const { return data.choose_white(); }
//		void transpose(const MatrixType & t);
		CellMatrixRows * get_rmat() { return rmat; }
		CellMatrixCols * get_cmat() { return cmat; }
		void update_data();
};
#endif

