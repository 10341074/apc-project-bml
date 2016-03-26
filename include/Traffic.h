#ifndef TRAFFIC_H
#define TRAFFIC_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

#include "Color.h"

class Traffic{
	private:
//	std::vector<std::vector<Color>> * pmat;
	std::unique_ptr< std::vector<std::vector<Color>> > pmat;
	public:
	Traffic() : pmat(new std::vector<std::vector<Color>>) {}
	void push_back(std::vector<Color> & v);
	void tok_push_back(const std::string & line);
	void print() const;
	friend std::ostream & operator<<(std::ostream & os, Traffic & traffic);
};

std::istream & operator>>(std::istream & is, Traffic & traffic);

#endif
