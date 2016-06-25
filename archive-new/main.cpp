#include<iostream>
#include<fstream>
#include<sstream>
#include<memory>
#include<string>
#include<cstring>
#include<Sparse.h>
#include<CSR.h>
#include<CSC.h>
#include<Car.h>
#include<Tokenize.h>

int main(int argc, char ** argv){
	std::ifstream f("problem.csv");
	std::unique_ptr<std::vector<Car>> p(new std::vector<Car>());
	
	std::vector<std::size_t> times(1,0);
	std::string first_line;
	if(std::getline(f,first_line))
		tokenize_first_line(first_line,times);
	
	CSR sRow(p);
	f>>sRow;	f.close();

	CSC sCol(sRow.give_rows(), sRow.give_cols(), sRow.give_cars(),p);
	
//	for(std::size_t k=0; k<times.size(); ++k)
//		std::cout<<times[k]<<SEPARATOR;
//	std::cout<<std::endl;
	
// 
// //	step dispari
//	sCol.transpose();
//	for(std::size_t k=0; k<sCol.give_cols(); ++k) sCol.move_line(k,Blue);
// 
// //	step pari
//	sRow.transpose();
// //	stampa step dispari
// //	std::cout<<sRow<<'\n'<<std::endl;
//	for(std::size_t k=0; k<sRow.give_rows(); ++k) sRow.move_line(k,Red);
//	
// //	stampa step pari
//	sCol.transpose();
//	sRow.transpose();
// //	std::cout<<sRow<<'\n'<<std::endl;

	Sparse * p1=&sCol;
	Sparse * p2=&sRow;
	Color colMove1 = Blue, colMove2 = Red;
	std::size_t n1=p1->give_cols(), n2=p1->give_rows();
	for(std::size_t itt=0; itt<times.size()-1; ++itt){
		for(std::size_t step=times[itt]; step<times[itt+1]; ++step){
			p1->transpose();
			for(std::size_t k=0; k<n1; ++k) p1->move_line(k,colMove1);
			std::swap(p1,p2);
			std::swap(colMove1,colMove2);
			std::swap(n1,n2);
		}
		
	
		std::stringstream convert;
		convert << times[itt+1];
		std::string ofname=convert.str();
		ofname.append(".csv");
		std::ofstream of(ofname);
		
		sCol.transpose();
		sRow.transpose();
//		std::cout<<sRow<<'\n'<<std::endl;
		of<<sRow;
		of.close();
	}
//	std::cout<<"Istante 2"<<std::endl<<sRow<<std::endl;

//	CSR s(p);
//	s.info();
//	f>>s;
//	s.print_vectors();
//	s.print_matrix();
//	std::cout<<"elem"<<s(0,3)<<std::endl;
//	s.info();
//	std::cout<<s;
//	f.close();
//	s.move_line(0,Blue);
//	std::cout<<s;
//	s.print_matrix();
//	s.print_vectors();
//	s.info();
//	
//	s.transpose();
//	s.print_vectors();
	return 0;
	
}
