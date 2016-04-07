#ifndef TRAFFIC_H
#define TRAFFIC_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

#include "Color.h"
#include "Row.h"
#include "DynRow.h"
#include "RowsVector.h"
#include "Tokenize.h"

class Traffic{
	private:
	RowsVector * pmat;
//	std::vector<std::vector<Color>> * pmat;
//	std::unique_ptr< std::vector<std::vector<Color>> > pmat;
	public:
//	Traffic() : pmat(new std::vector<std::vector<Color>>) {}
	Traffic();
//	Traffic(std::unique_ptr<std::vector<std::vector<Color>>> & p) : pmat(&*p) {}
	Traffic(RowsVector * p);
	~Traffic();
//	void push_back(std::vector<Color> & v);
	void tok_push_back(const std::string & line);
	void print() const;
	friend std::ostream & operator<<(std::ostream & os, const Traffic & traffic);
};

std::istream & operator>>(std::istream & is, Traffic & traffic);

#endif
