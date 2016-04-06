#ifndef DYNROW_H
#define DYNROW_H

#include <iostream>
#include <stdexcept>
#include <vector>

#include "Template.h"
#include "Color.h"
#include "Row.h"

class DynRow{
	Row * row = nullptr;
	public:
	DynRow();
	~DynRow();
	DynRow(const DynRow & dr);
	DynRow & operator=(const DynRow & dr);
	DynRow(DynRow && dr);
	DynRow & operator=(DynRow && dr);
	
	Row::size_type size() const;
	bool empty() const;
	
	Row::iterator begin();
	Row::iterator begin() const;					// !! danger possible modifications due to dynamic vector
//	Row::const_iterator cbegin() const;
	Row::iterator end();
	Row::iterator end() const;						// !! danger possible modifications due to dynamic vector
//	Row::const_iterator cend() const;
	
	void push_back(const Color & col);
	void push_back(Color && col);
};
#endif
