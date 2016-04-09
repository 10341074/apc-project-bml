#ifndef DYNROW_H
#define DYNROW_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

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
	
//	danger: memory is owned by external
	DynRow(Row * r);
	DynRow(std::unique_ptr<Row> r);
	DynRow(Row::size_type s);
	
	Row::size_type size() const;
	bool empty() const;
	
	Row::iterator begin();
	Row::const_iterator begin() const;
//	Row::const_iterator cbegin() const;
	Row::iterator end();
	Row::const_iterator end() const;
//	Row::const_iterator cend() const;
	
	void push_back(const Color & col);
	void push_back(Color && col);
	const Row * const get_row_pointer() const { return row; }
};
#endif
