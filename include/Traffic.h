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
#include "Tokenize.h"

class Traffic{
	private:
	VecVector * pmat = nullptr;
	public:
	Traffic(TypeMatrix t);
	Traffic(TypeMatrix t,size_type rows, size_type cols);
	~Traffic();
	void tok_push_back(const std::string & line);
	void print() const;
	
	Row::const_iterator get_row_it(size_type index) const;
	DrVec::const_iterator get_vec_it_begin() const;
	DrVec::const_iterator get_vec_it_end() const;
	
	void move_from(const Traffic & from, Color cl);
	
	friend std::ostream & operator<<(std::ostream & os, const Traffic & traffic);
};

std::istream & operator>>(std::istream & is, Traffic & traffic);

#endif
