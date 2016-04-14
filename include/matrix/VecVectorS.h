#ifndef VECVECTORS_H
#define VECVECTORS_H
#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
#include <memory>

#include "Template.h"
#include "Color.h"
#include "Car.h"
#include "Row.h"
// #include "DynRow.h"
// #include "Col.h"

using Data = std::list< std::list<Car> >;

class VecVectorS;
class RowsVectorS;
class ColsVectorS;

class VecVectorS {
	protected:
	MatrixType type = None;
	Data vec;
	std::size_t vec_size = 0;
	std::size_t lin_size = 0;
//	DrVec::size_type size() const;
//	virtual void update_	counts() {}
//	virtual void print(std::ostream & os) {}
	public:
	VecVectorS();
	VecVectorS(MatrixType t);							// to inherited classes' constructors
	~VecVectorS();
	VecVectorS(const VecVectorS * p);				// to inherited classes' copy constructors
	VecVectorS(const VecVectorS & v) 				= delete;
	VecVectorS(VecVectorS && v) 						= delete;
	VecVectorS & operator=(const VecVectorS & v)	= delete;
	VecVectorS & operator=(VecVectorS && v)		= delete;

//	bool empty() const;
//	Row::size_type get_cMaxIndex() const {return cMaxIndex; }
//	size_type get_length() const { return drVec.size(); }
// //	DrVec::iterator begin();
//	DrVec::const_iterator begin() const;
// //	DrVec::const_iterator cbegin() const;
// //	DrVec::iterator end();
//	DrVec::const_iterator end() const;
// //	DrVec::const_iterator cend() const;
//	ColumnVec::iterator column_begin();
//	ColumnVec::iterator column_end();
// 
//	void push_back(const DynRow & dr);
//	void push_back(DynRow && dr);
//	void push_back(Row * r);
//	void push_back(std::unique_ptr<Row> r);
	void push_back(std::list<Car> & l2, const std::size_t & count);

//	void column_start();
//	void column_shift();
//	virtual size_type rows() const { return 0; }
//	virtual size_type cols() const { return 0; }
//	
//	Row::const_iterator get_it_from(size_type index) const;
// 
//	friend std::ostream & operator<<(std::ostream & os, VecVector & vecVec);
};


class RowsVectorS : public VecVectorS {
	std::size_t rowsCount = 0;
	std::size_t colsCount = 0;
//	protected:
//	void update_counts();
//	void print(std::ostream & os);
	public:
	RowsVectorS() : VecVectorS(ByRows) {}
	RowsVectorS(const RowsVectorS & v);
//	RowsVector() { rowsCount = 0; colsCount = 0; }
//	RowsVector(DrVec::size_type rows, Row::size_type cols);
//	virtual ~RowsVector() {}
	void move_forward(const Color & cl);
	void print() const;
	void transpose(ColsVectorS & colsvec);
	size_type rows() const { return rowsCount; }
	size_type cols() const { return colsCount; }
	friend std::ostream & operator<<(std::ostream & os, RowsVectorS & rowsvec);
	friend ColsVectorS;
};
class ColsVectorS : public VecVectorS {
	std::size_t rowsCount = 0;
	std::size_t colsCount = 0;
//	protected:
//	void update_counts();
//	void print(std::ostream & os);
	public:
	ColsVectorS() : VecVectorS(ByCols) {}
	ColsVectorS(const ColsVectorS & v);
//	ColsVector() { rowsCount = 0; colsCount = 0; }
//	ColsVector(DrVec::size_type cols, Row::size_type rows);
//	virtual ~ColsVector() {}
	void move_forward(const Color & cl);
	void print() const;
	void transpose(RowsVectorS & rowsvec);
	size_type rows() const { return rowsCount; }
	size_type cols() const { return colsCount; }
	friend std::ostream & operator<<(std::ostream & os, ColsVectorS & colsvec);
	friend RowsVectorS;
};
#endif
