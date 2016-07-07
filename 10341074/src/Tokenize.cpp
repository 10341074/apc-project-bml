#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "Tokenize.h"

#define START '0'

std::vector<Color> tokenize(const std::string & line){
	std::size_t len=line.length();
	std::vector<Color> v((len+1)/2);
	const char * p2one = &line[0];
	
	for(std::vector<Color>::iterator it=v.begin(); it!=v.end(); ++it){
			*it = static_cast<Color>(*p2one -START);
		p2one+=2;
	}
	return v;
}
// extract times numbers from line	
void tokenize_first_line(const std::string & line, std::vector<std::size_t> & times){
	std::size_t pos1,pos2;

	if(line.empty())
		return;
	
	pos1 = 0;
	pos2=line.find_first_of(Separator);
	if(pos2!=std::string::npos){
		times.push_back(std::stoul(line.substr(0,pos2)));
		pos1=pos2 + 1;
		pos2=line.find_first_of(Separator,pos1);
	}
	while(pos2!=std::string::npos){
		times.push_back(std::stoul(line.substr(pos1,pos2-pos1)));
		pos1=pos2 + 1;
		pos2=line.find_first_of(Separator,pos1);
	}
	times.push_back(std::stoul(line.substr(pos1,std::string::npos)));
	return;
}

