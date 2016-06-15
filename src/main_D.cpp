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

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))
    
int main(int argc, char ** argv){
	std::string if_string(argv[1]);
	std::ifstream if_stream(if_string);
	
	std::string first_line;
	std::vector<std::size_t> times(1,0);
	if(std::getline(if_stream, first_line))
		tokenize_first_line(first_line,times);
	
	std::cout << times ;
	
	clock_t time = clock();
///*
	Color col_cols = Blue, col_rows = Red;
	MatrixType t1 = ByCols, t2 = ByRows;
	
	MatrixType * pYes = &t1;
	MatrixType * pNo = &t2;
	Color cYes = col_cols;
	Color cNo = col_rows;

	void (TrafficD:: * move)(const MatrixType & t, const Color & cl);
	move = & TrafficD::move_forward;
	
	TrafficD trd;
	if_stream >> trd;
	if_stream.close();
	if(trd.choose_white()) {
		move = & TrafficD::move_white;
		std::cout << "Choosen white\n";
	} else {
		std::cout << "Choosen coloured\n";
	}
	for(std::size_t interval=0; interval<times.size()-1; ++interval){
		for(std::size_t timeCount=times[interval]; timeCount<times[interval+1]; ++timeCount){
			CALL_MEMBER_FN(trd,move)(*pYes,cYes);
//			(trd).*(move(*pYes, cYes));
			std::swap(pYes,pNo);
			std::swap(cYes,cNo);
		}
		std::stringstream convert;
		convert << times[interval+1];
		std::string ofname=convert.str();
		ofname.append(".csv");
		std::ofstream of(ofname);
		
		of << trd ;
		of.close();
	}
		time=clock()-time;	std::cout<<"time =\n"<<((float)time)/CLOCKS_PER_SEC<<std::endl;	time=clock();

//*/
//	std::unique_ptr< std::vector<std::vector<Color>> > p(new std::vector<std::vector<Color>>);
//	VecVector * p = new VecVector(ByRows);
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
