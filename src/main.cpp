#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>
#include <fstream>
#include <string>
#include <sstream>

#include "Template.h"
#include "Color.h"
#include "Row.h"
#include "DynRow.h"
#include "VecVector.h"
#include "VecVectorS.h"
#include "VecVectorD.h"
#include "Col.h"

#include "Traffic.h"
#include "Tokenize.h"

int main(int argc, char ** argv){
	std::string if_string(argv[1]);
	std::ifstream if_stream(if_string);
	
	std::string first_line;
	std::vector<std::size_t> times(1,0);
	if(std::getline(if_stream, first_line))
		tokenize_first_line(first_line,times);
	
	std::cout << times ;
	
//	std::unique_ptr< std::vector<std::vector<Color>> > p(new std::vector<std::vector<Color>>);
//	VecVector * p = new VecVector(ByRows);
///*
	TrafficD trd;
	if_stream >> trd;
	if_stream.close();
	std::cout << trd;
//	trd.print();
//*/
/*
	TrafficS trs;
//	ColsVectorS c;
	if_stream >> trs;
	if_stream.close();

	Color col_cols = Blue, col_rows = Red;
	MatrixType t1 = ByCols, t2 = ByRows;
	
	MatrixType * pYes = &t1;
	MatrixType * pNo = &t2;
	Color cYes = col_cols;
	Color cNo = col_rows;
	
//	for(std::size_t interval=0; interval<1; ++interval){
	for(std::size_t interval=0; interval<times.size()-1; ++interval){
		for(std::size_t timeCount=times[interval]; timeCount<times[interval+1]; ++timeCount){
			// prendi e muovi
//			std::cout << trs;
			trs.transpose(*pYes);
			trs.move_forward(*pYes, cYes);
			std::swap(pYes,pNo);
			std::swap(cYes,cNo);
//			std::cout << "time "<< timeCount << '\n' << trs;
		}
		std::stringstream convert;
		convert << times[interval+1];
		std::string ofname=convert.str();
		ofname.append(".csv");
		std::ofstream of(ofname);
		
		of << trs ;
		of.close();
	}

//*/
/*
	Traffic tr_rows(ByRows);
	Traffic tr_cols(ByCols);
	if_stream >> tr_rows;
	if_stream.close();
	tr_cols.transpose_from(tr_rows);
	
	Color col_cols = Blue, col_rows = Red;
	Traffic * pYes = &tr_cols;
	Traffic * pNo = &tr_rows;
	Color cYes = col_cols;
	Color cNo = col_rows;
	
	for(std::size_t interval=0; interval<times.size()-1; ++interval){
		for(std::size_t timeCount=times[interval]; timeCount<times[interval+1]; ++timeCount){
			(* pNo).move_from(* pYes, cYes);
			std::swap(pYes,pNo);
			std::swap(cYes,cNo);
		}
		std::stringstream convert;
		convert << times[interval+1];
		std::string ofname=convert.str();
		ofname.append(".csv");
		std::ofstream of(ofname);
		
		of << *pYes ;
		of.close();
	}
//*/

// //	Row r;
//	std::cout << &r <<std::endl;
	return 0;
}
