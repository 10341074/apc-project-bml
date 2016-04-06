#include "RowsVector.h"
DynRow g(){
	DynRow dr;
	return dr;
}

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
void RowsVector::push_function(){
	std::cout << "push function" <<std::endl;
	drVec.push_back(g());
	return;
}
