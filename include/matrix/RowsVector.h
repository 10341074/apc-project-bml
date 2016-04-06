#ifndef ROWSVECTOR_H
#define ROWSVECTOR_H
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Template.h"
#include "Color.h"
#include "Row.h"
#include "DynRow.h"

class RowsVector {
	std::vector< DynRow > drVec;
	public:
//	RowsVector() {}
	void push_back(const DynRow & dr);
	void push_back(DynRow && dr);
	void push_back(Row * r);
};

#endif
