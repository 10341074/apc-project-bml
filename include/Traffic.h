#ifndef TRAFFIC_H
#define TRAFFIC_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

#include "Color.h"
#include "Row.h"
#include "DynRow.h"
#include "VecVector.h"
#include "VecVectorS.h"
#include "VecVectorD.h"
#include "Tokenize.h"

class Traffic{
	private:
	MatrixType type;
	VecVector * pmat = nullptr;
	public:
	Traffic(MatrixType t);
	Traffic(MatrixType t,size_type rows, size_type cols);
	~Traffic();
	void tok_push_back(const std::string & line);
	void print() const;
	
	Row::const_iterator get_row_it(size_type index) const;
	DataD::const_iterator get_vec_it_begin() const;
	DataD::const_iterator get_vec_it_end() const;
	Row::size_type get_lin_size() const;
	size_type rows() const;
	size_type cols() const;
	
	void move_from(const Traffic & from, Color cl);
	void transpose_from(const Traffic & from);
	
	friend std::ostream & operator<<(std::ostream & os, const Traffic & traffic);
};

std::istream & operator>>(std::istream & is, Traffic & traffic);

class TrafficS{
	private:
		MatrixType type = None;
		RowsVectorS * rmat = nullptr;
		ColsVectorS * cmat = nullptr;
	public:
		TrafficS();
		~TrafficS();
		void tok_push_back(const std::string & line, const std::size_t & rowsCount);
		friend std::ostream & operator<<(std::ostream & os, const TrafficS & traffic);
		friend std::istream & operator>>(std::istream & is, TrafficS & traffic);
		void move_forward(const MatrixType & t, const Color & cl);
		void transpose(const MatrixType & t);
		RowsVectorS * get_rmat() { return rmat; }
		ColsVectorS * get_cmat() { return cmat; }
};
class TrafficD{
	private:
		MatrixType type = None;
		OwnerDataD	data;
		RowsVectorD * rmat = nullptr;
		ColsVectorD * cmat = nullptr;
	public:
		TrafficD();
		~TrafficD();
		void tok_push_back(const std::string & line, const std::size_t & rowsCount);
		friend std::ostream & operator<<(std::ostream & os, const TrafficD & traffic);
		friend std::istream & operator>>(std::istream & is, TrafficD & traffic);
		void print() const;
		void move_forward(const MatrixType & t, const Color & cl);
//		void transpose(const MatrixType & t);
		RowsVectorD * get_rmat() { return rmat; }
		ColsVectorD * get_cmat() { return cmat; }
};
#endif

