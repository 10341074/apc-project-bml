#ifndef ROWSVECTOR_H
#define ROWSVECTOR_H
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Template.h"
#include "Color.h"
#include "Row.h"
#include "DynRow.h"

using DrVec = std::vector<DynRow>;

class RowsVector {
	std::vector< DynRow > drVec;
	public:
//	RowsVector() {}

	DrVec::size_type size() const;
	bool empty() const;
	
	DrVec::iterator begin();
	DrVec::iterator begin() const;					// !! danger possible modifications due to dynamic vector
//	DrVec::const_iterator cbegin() const;
	DrVec::iterator end();
	DrVec::iterator end() const;						// !! danger possible modifications due to dynamic vector
//	DrVec::const_iterator cend() const;

	void push_back(const DynRow & dr);
	void push_back(DynRow && dr);
	void push_back(Row * r);
	
	friend std::ostream & operator<<(std::ostream & os, const RowsVector & rowsVec);
};

#endif
