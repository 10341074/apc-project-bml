#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "Tokenize.h"

#define START '0'

std::vector<Color> tokenize(std::string & line){
	std::size_t len=line.length();
	std::vector<Color> v((len+1)/2);
	char * p2one = &line[0];
	
	for(std::vector<Color>::iterator it=v.begin(); it!=v.end(); ++it){
			*it = static_cast<Color>(*p2one -START);
//			std::cout<<"char= "<<(*p2one -START);
		p2one+=2;
	//        	std::string n=std::string(1,line[2*index]);
	//        	v[index]=(Color)std::stoul(n);
	}
			
	
	return v;
}
void tokenize_first_line(std::string & line, std::vector<std::size_t> & times){
	std::size_t pos1,pos2;
	
	pos2=line.find_first_of(SEPARATOR);
	if(pos2!=std::string::npos)
		times.push_back(std::stoul(line.substr(0,pos2)));

	pos1=pos2;
	pos2=line.find_first_of(SEPARATOR,pos1+1);
	while(pos2!=std::string::npos){
		times.push_back(std::stoul(line.substr(pos1+1,pos2-pos1-1)));
		pos1=pos2;
		pos2=line.find_first_of(SEPARATOR,pos1+1);
	}
	times.push_back(std::stoul(line.substr(pos1+1,pos2-pos1-1)));
	return;
}


void tokenize(std::string & line,std::vector<Color> & v){
//        std::size_t index=0;
//        std::size_t len=line.length();
// 
//        for(index=0; index<len; index+=2){
//        	v[index]=(Color)line[index];
//        }
//        while(pos=line.find_first_of(SEPARATOR,pos+1);)
//        
//        item=std::stoul(line.substr(pos+1,pos2-pos-1));
//        
//        r=std::stod(line.substr(pos2+1));
        return;
        }
        

