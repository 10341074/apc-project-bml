#include "RowsVector.h"
void RowsVector::push_back(const DynRow & dr) {
	drVec.push_back(dr);
	return;
}
void RowsVector::push_back(DynRow && dr) {
	drVec.push_back(dr);
	return;
}

