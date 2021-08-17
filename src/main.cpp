#include <cstdlib>
#include <cstdio>
#include "parser.hpp"
#include "inter.hpp"
using namespace std;


int main()
{
	// string reading = ReadFile("test/main.c");
	// const vector<string> pars = Parser(reading);
	// string outline;
	// int i;
	// for(i=0;i<(signed int)pars.size();i++)
	// {
	// 	outline+= "|"+pars[i] +"|\n";
	// }
	Analyse_init("test/main.c");
	//printf("vect_search %d",vector_search(initial[0],"0",0));
	// WriteFile("out.txt",outline);
	return 0;
}
