#ifndef COL_H
#define COL_H

#include <iostream>
#include <stdexcept>
#include <vector>

#include "Color.h"
#include "Row.h"

class DynColor{											// no memory menagement: no new - no delete
	Row::iterator item;
	public:
	DynColor() 												= default;
	~DynColor() {}											// no deallocation
	DynColor(const DynColor & dc) 					= delete;
	DynColor & operator=(const DynColor & dc) 	= delete;
	DynColor(DynColor && dc)							= default;
	DynColor & operator=(DynColor && dc)			= default;
	
	DynColor(const Row::iterator & it) : item(it) {}
	DynColor(Row::iterator && it) : item(it) {}
	DynColor & operator=(const Row::iterator & it);
	DynColor & operator=(Row::iterator && it);
	
//	up to now only to write
	DynColor & operator=(const Color & c);
	DynColor & operator=(Color && c);
	DynColor & operator++();
	friend std::ostream & operator<<(std::ostream & os, const DynColor & dc);
};
std::ostream & operator<<(std::ostream & os, const std::vector< DynColor> & cVec);

class Col{
	std::vector< DynColor > column;
	public:
	Col() {}
	~Col() {}
};
#endif
