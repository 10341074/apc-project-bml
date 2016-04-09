// remember try implement move with color already written
#ifndef CSC_H
#define CSC_H
#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

#include <Color.h>
#include <Scalar.h>
#include <Car.h>
#include <Sparse.h>

class CSC : public Sparse{

	public:
		
	CSC(std::vector<Car> * p);
	CSC(std::unique_ptr< std::vector<Car> > & p);
	CSC(std::size_t nr, std::size_t nc, std::size_t nz, std::vector<Car> * p);
	CSC(std::size_t nr, std::size_t nc, std::size_t nz, std::unique_ptr< std::vector<Car> > & p);
		
//	Sparse();
//	Sparse(std::vector<Car> * p);
//	Sparse(std::unique_ptr< std::vector<Car> > & p);
	
//	Sparse(size_type ni);
//	Sparse(size_type n, size_type ni);
//	Sparse(size_type m, size_type n, size_type ni);
//	Sparse(size_type ni, const Scalar & val);
//	Sparse(size_type n,size_type ni,const T & val);
//	Sparse(size_type m,size_type n,size_type ni,const T & val);

	virtual ~CSC();	//Destructor
	
	/*
	Sparse(const Sparse & v);	//copy constructor
	Sparse(Sparse && v);			//move constructor

	Sparse & operator=(const Sparse & v); 	//copy assignment
	Sparse & operator=(Sparse && v);			//move assigment
	*/

	void push_back(const std::vector<Color> & vec) override;

//	void info() const;
//	void print_matrix() const;
//	void print_vectors() const;
	Color 	operator()(const std::size_t i, const std::size_t j) const override;
//	Color & 	operator()(const std::size_t i, const std::size_t j);	// cannot modify empty cells
	
	void move_line(std::size_t line, Color cl) override;
	void ostream(std::ostream & os) const override{return;}

//	void ostream(std::ostream & os) const override;
//	friend std::ostream & operator<<(std::ostream & os, const Sparse & mat);	
//	friend std::istream & operator>>(std::istream & is, Sparse & mat);
	void transpose() override;
	};//finish class


#endif
