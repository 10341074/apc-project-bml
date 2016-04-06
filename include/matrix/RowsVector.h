#ifndef ROWSVECTOR_H
#define ROWSVECTOR_H
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Template.h"
#include "Color.h"
#include "Row.h"
#include "DynRow.h"
#include "Col.h"

using DrVec = std::vector< DynRow >;
using ColumnVec = std::vector< DynColor >;

class RowsVector {
	DrVec drVec;
	ColumnVec cVec;
	Row::size_type cIndex = 0;	// column index
	public:
//	RowsVector() {}

	DrVec::size_type size() const;
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
	
	void column_start();
	void column_shift();
	friend std::ostream & operator<<(std::ostream & os, const RowsVector & rowsVec);
	void push_function();
};

#endif
