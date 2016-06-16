#ifndef CELLDATA_H
#define CELLDATA_H
#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
// #include <memory>

#include "Template.h"
#include "Color.h"
#include "Row.h"
#include "Coordinates.h"
#include "Cell.h"
// #include "DynRow.h"
// #include "Col.h"

using CarsDataIn_Old		= 				 std::vector< Cell >  ;			
using CarsData_Old 		= std::list< std::vector< Cell > >;
using OneColor_Old		= std::list< Cell * >;


class CellTraffic;
class OwnerData;
class OwnerData_Old{
	private:
		std::size_t inn_size = 0;
		std::size_t ext_size = 0;
		CarsData_Old			cars;

		OneColor_Old white; 
		OneColor_Old blue; 
		OneColor_Old red; 
	public:
		void empty_data();
		void print() const;
		bool choose_white() const;
		friend std::ostream & operator<<(std::ostream & os, const OwnerData_Old & d);
		friend CellTraffic;
		friend OwnerData;
};

#endif

