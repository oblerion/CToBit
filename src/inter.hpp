#ifndef inter_hpp
#define inter_hpp
#include "parser.hpp"

// interpreter struct

const vector<vector<string>> initial{
	{"int","<name>",";"},
	{"char","<name>",";"},
	{"int","<name>","=","<value>",";"},
	{"char","<name>","=","<value>",";"},
	{"int","<name>","(","<parameter>",")","{","<instruct>","}"},
	{"char","<name>","(","<parameter>",")","{","<instruct>","}"},
	{"void","<name>","(","<parameter>",")","{","<instruct>","}"},
	{"struct","<name>","{","<instruct>","}",";"}
};
const vector<vector<string>> initial_re{
	{"#i1","<name>"},
	{"#c1","<name>"},
	{"#i2","<name>","#v","<value>"},
	{"#c2","<name>","#v","<value>"},
	{"#i3","<name>","#p","<parameter","#i","<instruct>"},
	{"#c3","<name>","#p","<parameter","#i","<instruct>"},
	{"#v1","<name>","#p","<parameter","#i","<instruct>"},
	{"#s1","<name>","#i","<instruct>"}
};
const vector<vector<string>> logic{
	{"if","(","<parameter>",")","{","<instruct>","}"},
	{"else","if","(","<parameter>",")","{","<instruct>","}"},
	{"else","{","<instruct>","}"},
	{"for","(","<parameter>",")","{","<instruct>","}"}
	
};

struct i_variable
{
	string name;
	string type;
};
struct i_function
{
	string name;
	string return_type;
	vector<string> lparameter;
	vector<string> linst;
};
struct i_struct
{
	string name;
	//vector<struct i_variable> lvar;
	vector<string> linst;
};

struct i_program
{
	string name;
	vector<struct i_variable> lvar;
	vector<struct i_function> lfunc;
	vector<struct i_struct> lstruct; 
};

struct i_program Analyse_init(string file);
void synth_check(vector<string> pars,vector<vector<string>> init,struct i_program* sprog);
void draw_program(struct i_program sprog);
int vector_search(vector<string> data,string f,int n);
int recettes_check(vector<string> pars,vector<vector<string>> initial, int n);
vector<string> get_all_btw(vector<string> data,string s_begin,string s_end,int n_begin,int* n_end);

#endif