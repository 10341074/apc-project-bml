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
	~Traffic();
	void tok_push_back(const std::string & line);
	void print() const;
	friend std::ostream & operator<<(std::ostream & os, const Traffic & traffic);
};

std::istream & operator>>(std::istream & is, Traffic & traffic);

#endif
