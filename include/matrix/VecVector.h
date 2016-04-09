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

using DrVec 		= std::vector< DynRow >;
using ColumnVec 	= std::vector< DynColor >;
enum TypeMatrix{ByRows, ByCols};

class VecVector {
	protected:
	DrVec 		drVec;
	ColumnVec 	cVec;
	Row::size_type cIndex = 0;	// column index
	Row::size_type cMaxIndex = 0;

	DrVec::size_type size() const;
	virtual void update_counts() {}
	virtual void print(std::ostream & os) {}
	public:
	VecVector() {cIndex = 0; cMaxIndex = 0;}
	VecVector(DrVec::size_type rows, Row::size_type cols);
	virtual ~VecVector() {}
	
	bool empty() const;
	
	DrVec::iterator begin();
	DrVec::const_iterator begin() const;
//	DrVec::const_iterator cbegin() const;
	DrVec::iterator end();
	DrVec::const_iterator end() const;
//	DrVec::const_iterator cend() const;

	void push_back(const DynRow & dr);
	void push_back(DynRow && dr);
	void push_back(Row * r);
	void push_back(std::unique_ptr<Row> r);

	void column_start();
	void column_shift();
	friend std::ostream & operator<<(std::ostream & os, VecVector & vecVec);
};

class RowsVector: public VecVector {
	DrVec::size_type rowsCount = 0;
	Row::size_type colsCount = 0;
	protected:
	void update_counts();
	void print(std::ostream & os);
	public:
	RowsVector() { rowsCount = 0; colsCount = 0; }
	RowsVector(DrVec::size_type rows, Row::size_type cols);
	virtual ~RowsVector() {}
	
	Row::size_type cols() const { return colsCount; }
	DrVec::size_type rows() const { return rowsCount; }
	friend std::ostream & operator<<(std::ostream & os, RowsVector & rowsvec);
};
class ColsVector: public VecVector {
	DrVec::size_type colsCount = 0;
	Row::size_type rowsCount = 0;
	protected:
	void update_counts();
	void print(std::ostream & os);
	public:
	ColsVector() { rowsCount = 0; colsCount = 0; }
	ColsVector(DrVec::size_type cols, Row::size_type rows);
	virtual ~ColsVector() {}
	
	Row::size_type rows() const { return rowsCount; }
	DrVec::size_type cols() const { return colsCount; }
	friend std::ostream & operator<<(std::ostream & os, ColsVector & colsVec);
};
#endif
