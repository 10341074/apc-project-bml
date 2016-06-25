// remember try implement move with color already written
#ifndef SPARSE_H
#define SPARSE_H
#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

#include <Color.h>
#include <Scalar.h>
#include <Car.h>

class Sparse{
	protected:
	std::size_t nz;//number of items
	std::size_t nr;//number of rows
	std::size_t nc;//number of cols
//	std::vector<std::size_t * > I;
//	std::vector<std::size_t> I;
//	std::vector<std::size_t> J;
//	std::vector<Scalar> A;

	std::vector<std::size_t> P;
	std::vector<Car> * V;
	
	virtual void ostream(std::ostream & os) const = 0;
	public:
//	Sparse();
	Sparse(std::vector<Car> * p);
	Sparse(std::unique_ptr< std::vector<Car> > & p);
	Sparse(std::size_t nr, std::size_t nc, std::size_t nz, std::vector<Car> * p);
	Sparse(std::size_t nr, std::size_t nc, std::size_t nz, std::unique_ptr< std::vector<Car> > & p);
	
//	Sparse(size_type ni);
//	Sparse(size_type n, size_type ni);
//	Sparse(size_type m, size_type n, size_type ni);
//	Sparse(size_type ni, const Scalar & val);
//	Sparse(size_type n,size_type ni,const T & val);
//	Sparse(size_type m,size_type n,size_type ni,const T & val);
	virtual ~Sparse();	//Destructor
	
	/*
	Sparse(const Sparse & v);	//copy constructor
	Sparse(Sparse && v);			//move constructor

	Sparse & operator=(const Sparse & v); 	//copy assignment
	Sparse & operator=(Sparse && v);			//move assigment
	*/
	std::size_t give_rows() const {return nr; }
	std::size_t give_cols() const {return nc; }
	std::size_t give_cars() const {return nz; }
	
	virtual void push_back(const std::vector<Color> & vec) = 0;

	void info() const;
	void print_matrix() const;
	void print_vectors() const;
	virtual Color 	operator()(const std::size_t i, const std::size_t j) const = 0;
//	Color & 	operator()(const std::size_t i, const std::size_t j);	// cannot modify empty cells
	
	virtual void move_line(std::size_t line, Color cl) = 0;
	friend std::ostream & operator<<(std::ostream & os, const Sparse & mat);	
	friend std::istream & operator>>(std::istream & is, Sparse & mat);
	virtual void transpose() = 0;
	};//finish class

#endif
