#include "CellData.h"
void OwnerData_Old::empty_data() {
	white.clear();
	blue.clear();
	red.clear();
	cars.clear();
}
std::ostream & operator<<(std::ostream & os, const OwnerData_Old & d) {
	for(CarsData_Old::const_iterator it1 = d.cars.begin(); it1 != d.cars.end(); ++it1) {
		for(CarsDataIn_Old::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
			os << * it2 << Separator;
		}
		os << std::endl;
	}
	return os;
}
void OwnerData_Old::print() const {
	std::cout << "cars\n";
	for(CarsData_Old::const_iterator it1 = cars.begin(); it1 != cars.end(); ++it1) {
		for(CarsDataIn_Old::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
			std::cout << * it2 << Separator;
		}
		std::cout << std::endl;
	}
	std::cout << "White\n";
	for(OneColor_Old::const_iterator it = white.begin(); it != white.end(); ++it) {
		std::cout << **it << Separator;
	}
	std::cout << std::endl;
	std::cout << "Blue\n";
	for(OneColor_Old::const_iterator it = blue.begin(); it != blue.end(); ++it) {
		std::cout << **it << Separator;
	}
	std::cout << std::endl;
	std::cout << "Red\n";
	for(OneColor_Old::const_iterator it = red.begin(); it != red.end(); ++it) {
		std::cout << **it << Separator;
	}
	std::cout << std::endl;
	std::cout << "from right\n";
	for(CarsData_Old::const_iterator it1 = cars.begin(); it1 != cars.end(); ++it1) {
		for(CarsDataIn_Old::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
			Cell * c = it2->get_r();
			std::cout << * c << Separator;
		}
		std::cout << std::endl;
	}
	std::cout << "from left\n";
	for(CarsData_Old::const_iterator it1 = cars.begin(); it1 != cars.end(); ++it1) {
		for(CarsDataIn_Old::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
			Cell * c = it2->get_l();
			std::cout << * c << Separator;
		}
		std::cout << std::endl;
	}
	std::cout << "from up\n";
	for(CarsData_Old::const_iterator it1 = cars.begin(); it1 != cars.end(); ++it1) {
		for(CarsDataIn_Old::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
			Cell * c = it2->get_u();
			std::cout << * c << Separator;
		}
		std::cout << std::endl;
	}
	std::cout << "from down\n";
	for(CarsData_Old::const_iterator it1 = cars.begin(); it1 != cars.end(); ++it1) {
		for(CarsDataIn_Old::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
			Cell * c = it2->get_d();
			std::cout << * c << Separator;
		}
		std::cout << std::endl;
	}


	return;
}

bool OwnerData_Old::choose_white() const {
	if(2 * white.size() < red.size() + blue.size())
		return true;
	else 
		return false;
}

