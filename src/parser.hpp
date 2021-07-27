#ifndef parser_hpp 
#define parser_hpp
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include "string2.hpp"
#include "io.hpp"
#include <ctype.h>
using namespace std;

const vector<string> token = {
	"int","float","void","char","struct",
	"(",")","{","}",";",",",
	"=","-","+","/","*","&",
	"|","if","else",
	"for","while","do","return"
};
vector<string> Parser(string reading);

#endif
