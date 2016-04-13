#ifndef TRAFFIC_H
#define TRAFFIC_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

#include "Color.h"
#include "Row.h"
#include "DynRow.h"
#include "VecVector.h"
#include "VecVectorS.h"
#include "Tokenize.h"

class Traffic{
	private:
	MatrixType type;
	VecVector * pmat = nullptr;
	public:
	Traffic(MatrixType t);
	Traffic(MatrixType t,size_type rows, size_type cols);
	~Traffic();
	void tok_push_back(const std::string & line);
	void print() const;
	
	Row::const_iterator get_row_it(size_type index) const;
	DrVec::const_iterator get_vec_it_begin() const;
	DrVec::const_iterator get_vec_it_end() const;
	Row::size_type get_cMaxIndex() const;
	size_type rows() const;
	size_type cols() const;
	
	void move_from(const Traffic & from, Color cl);
	void transpose_from(const Traffic & from);
	
	friend std::ostream & operator<<(std::ostream & os, const Traffic & traffic);
};

std::istream & operator>>(std::istream & is, Traffic & traffic);

class TrafficS{
	private:
		MatrixType type;
		RowsVectorS * rmat = nullptr;
		ColsVectorS * cmat = nullptr;
	public:
		TrafficS(MatrixType t);
		~TrafficS();
		void tok_push_back(const std::string & line, const std::size_t & rowsCount);
		friend std::ostream & operator<<(std::ostream & os, const TrafficS & traffic);
		RowsVectorS * get_rmat() { return rmat; }
		ColsVectorS * get_cmat() { return cmat; }
};
std::istream & operator>>(std::istream & is, TrafficS & traffic);
#endif

