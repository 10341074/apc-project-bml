#include "RowsVector.h"
void RowsVector::push_back(const DynRow & dr) {
	std::cout << "RowsVector push_back &" << std::endl;
	drVec.push_back(dr);
	return;
}
void RowsVector::push_back(DynRow && dr) {
	std::cout << "RowsVector push_back &&" << std::endl;
	drVec.push_back(DynRow(dr));
	return;
}

