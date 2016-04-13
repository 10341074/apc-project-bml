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
	Traffic tr_rows(ByRows);
	Traffic tr_cols(ByCols);
	
	TrafficS trs(ByRows);
	ColsVectorS c;
	if_stream >> trs;
	RowsVectorS * rmat = trs.get_rmat();
	std::cout << *rmat;
	c.transpose(*rmat	);
	std::cout << c;
	if_stream.close();

/*
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
