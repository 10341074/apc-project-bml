#ifndef COORDINATES_H
#define COORDINATES_H
#include <iostream>
#include <stdexcept>

class Coordinates {
	private:
		std::size_t my_i = 0;
		std::size_t my_j = 0;
	public:
	Coordinates(std::size_t i, std::size_t j) : my_i(i), my_j(j) {}
	
	std::size_t & 			i()			{ return my_i; }
	const std::size_t & 	i() const	{ return my_i; }
	std::size_t & 			j()			{ return my_j; }
	const std::size_t & 	j() const	{ return my_j; }
};

#endif
