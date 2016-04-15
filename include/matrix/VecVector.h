#ifndef VECVECTOR_H
#define VECVECTOR_H
#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

#include "Template.h"
#include "Color.h"
#include "Row.h"
#include "DynRow.h"
#include "Col.h"

using DataD 		= std::vector< DynRow >;
using ColumnVec 	= std::vector< DynColor >;

class VecVector {
	protected:
	DataD 		vec;
	ColumnVec 	cVec;
	Row::size_type lin_ind = 0;	// column index
	Row::size_type lin_size = 0;

	DataD::size_type size() const;
	virtual void update_counts() {}
	virtual void print(std::ostream & os) {}
	public:
	VecVector() {lin_ind = 0; lin_size = 0;}
	VecVector(DataD::size_type rows, Row::size_type cols);
	virtual ~VecVector() {}
	
	bool empty() const;
	Row::size_type get_lin_size() const {return lin_size; }
	size_type get_length() const { return vec.size(); }
//	DataD::iterator begin();
	DataD::const_iterator begin() const;
//	DataD::const_iterator cbegin() const;
//	DataD::iterator end();
	DataD::const_iterator end() const;
//	DataD::const_iterator cend() const;
	ColumnVec::iterator column_begin();
	ColumnVec::iterator column_end();

	void push_back(const DynRow & dr);
	void push_back(DynRow && dr);
	void push_back(Row * r);
	void push_back(std::unique_ptr<Row> r);

	void column_start();
	void column_shift();
	virtual size_type rows() const { return 0; }
	virtual size_type cols() const { return 0; }
	
	Row::const_iterator get_it_from(size_type index) const;

	friend std::ostream & operator<<(std::ostream & os, VecVector & vecVec);
};

class RowsVector: public VecVector {
	DataD::size_type rowsCount = 0;
	Row::size_type colsCount = 0;
	protected:
	void update_counts();
	void print(std::ostream & os);
	public:
	RowsVector() { rowsCount = 0; colsCount = 0; }
	RowsVector(DataD::size_type rows, Row::size_type cols);
	virtual ~RowsVector() {}
	
	size_type cols() const { return colsCount; }
	size_type rows() const { return rowsCount; }
	friend std::ostream & operator<<(std::ostream & os, RowsVector & rowsvec);
};
class ColsVector: public VecVector {
	DataD::size_type colsCount = 0;
	Row::size_type rowsCount = 0;
	protected:
	void update_counts();
	void print(std::ostream & os);
	public:
	ColsVector() { rowsCount = 0; colsCount = 0; }
	ColsVector(DataD::size_type cols, Row::size_type rows);
	virtual ~ColsVector() {}
	
	size_type rows() const { return rowsCount; }
	size_type cols() const { return colsCount; }
	friend std::ostream & operator<<(std::ostream & os, ColsVector & colsVec);
};
#endif
