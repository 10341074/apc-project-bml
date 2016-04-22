#ifndef VECVECTORD_H
#define VECVECTORD_H
#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
// #include <memory>

#include "Template.h"
#include "Color.h"
#include "Row.h"
// #include "DynRow.h"
// #include "Col.h"

// using DataD 		= std::vector< DynRow >;
// using ColumnVec 	= std::vector< DynColor >;

class ColorP;
using ColorD		= std::vector< ColorP >::iterator;
using ColorDD		= std::list< ColorD >::iterator;

// ColumnD <-> RowD -> CarsD
using CarsD 		= std::list< std::vector< Color > >;
using RowD			= std::list< std::vector< ColorP > >;
using ColumnD		= std::list< std::list< ColorD > >;

class VecVectorD;
class RowsVectorD;
class ColsVectorD;

class ColorP {
	private:
		Color	*				my_c = nullptr;
		ColorDD 				my_p;
	public:
		ColorP()											{}
		ColorP(Color * c)			 				: my_c(c) {}
		ColorP(const ColorP & c)				: my_c(c.my_c), my_p(c.my_p) {}
		Color * & cp()								{ return my_c; }
		Color * const & cp() const 			{ return my_c; }
		Color & cl()								{ return * my_c; }
		Color & cl() const 						{ return * my_c; }
		ColorDD & p()								{ return my_p; }
		ColorDD const & p() const 				{ return my_p; }
		friend std::ostream & operator<<(std::ostream & os, const ColorP & o);
};
std::ostream & operator<<(std::ostream & os, const RowD & v);
class OwnerDataD{
	private:
		CarsD			cars;
		RowD 			vec;
		ColumnD 		cvec;
		std::list<ColorDD > white; 
		std::list<ColorDD > blue; 
		std::list<ColorDD > red; 
	public:
		void print() const;
		friend std::ostream & operator<<(std::ostream & os, const OwnerDataD & d);
		friend VecVectorD;
		friend RowsVectorD;
		friend ColsVectorD;
};

class VecVectorD {
	protected:
	MatrixType type = None;
//	DataD 		vec;
	OwnerDataD * 	pvec = nullptr;

//	ColumnVec 	cVec;
	
	std::size_t vec_size = 0;
//	std::size_t lin_ind = 0;	// column index
	std::size_t lin_size = 0;

//	DataD::size_type size() const;
//	virtual void update_counts() {}
//	virtual void print(std::ostream & os) {}
	public:
	VecVectorD() = delete; 
	VecVectorD(MatrixType t, OwnerDataD * d) : type(t), pvec(d) {}
//	VecVector(DataD::size_type rows, Row::size_type cols);
	~VecVectorD() {}
	
//	bool empty() const;
//	Row::size_type get_lin_size() const {return lin_size; }
//	size_type get_length() const { return vec.size(); }
//	DataD::iterator begin();
//	DataD::const_iterator begin() const;
//	DataD::const_iterator cbegin() const;
//	DataD::iterator end();
//	DataD::const_iterator end() const;
//	DataD::const_iterator cend() const;
//	ColumnVec::iterator column_begin();
//	ColumnVec::iterator column_end();

	void push_back(CarsD & l2, const std::size_t & count);
	void push_back_white(std::list<ColorDD > & l2);
	void push_back_blue(std::list<ColorDD > & l2);
	void push_back_red(std::list<ColorDD > & l2);
	void border_columns();
	
//	void push_back(const DynRow & dr);
//	void push_back(DynRow && dr);
//	void push_back(Row * r);
//	void push_back(std::unique_ptr<Row> r);

//	void column_start();
//	void column_shift();
//	virtual size_type rows() const { return 0; }
//	virtual size_type cols() const { return 0; }
	
//	Row::const_iterator get_it_from(size_type index) const;

//	friend std::ostream & operator<<(std::ostream & os, VecVector & vecVec);
};

class RowsVectorD: public VecVectorD {
	std::size_t rowsCount = 0;
	std::size_t colsCount = 0;
//	protected:
//	void update_counts();
//	void print(std::ostream & os);
	public:
	RowsVectorD() = delete;
	RowsVectorD(OwnerDataD * d) : VecVectorD(ByRows, d) {}
//	RowsVector(DataD::size_type rows, Row::size_type cols);
//	virtual ~RowsVector() {}
	void move_forward(const Color & cl);
	size_type cols() const { return colsCount; }
	size_type rows() const { return rowsCount; }
	friend std::ostream & operator<<(std::ostream & os, RowsVectorD & rowsvec);
};
class ColsVectorD: public VecVectorD {
	std::size_t colsCount = 0;
	std::size_t rowsCount = 0;
//	protected:
//	void update_counts();
//	void print(std::ostream & os);
	public:
	ColsVectorD() = delete;
	ColsVectorD(OwnerDataD * d) : VecVectorD(ByCols, d) {}
//	ColsVector(DataD::size_type cols, Row::size_type rows);
//	virtual ~ColsVector() {}
	void move_forward(const Color & cl);
	std::size_t rows() const { return rowsCount; }
	std::size_t cols() const { return colsCount; }
	friend std::ostream & operator<<(std::ostream & os, ColsVectorD & colsvec);
};
/*
//*/
#endif

