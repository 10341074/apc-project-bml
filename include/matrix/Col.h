#ifndef COL_H
#define COL_H

#include <iostream>
#include <stdexcept>
#include <vector>

#include "Color.h"

class DynColor{											// no memory menagement: no new - no delete
	Color * item = nullptr;
	public:
	DynColor();
	~DynColor();											// no deallocation
	DynColor(const DynColor & dc);
	DynColor & operator=(const DynColor & dc);	// shallow copy
	DynColor(DynColor && dc);
	DynColor & operator=(DynColor && dc);			// shallow 
};
#endif
