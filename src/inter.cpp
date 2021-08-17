#include "inter.hpp"
#include<stdio.h>


int vector_search(vector<string> data,string f,int n)
{
	int i;
	if(n<data.size())
	{
		for(i=n;i<data.size();i++)
		{
			if(string_find(data[i],f,0)!=-1)
				return i;
		}
	}
	return -1;
}

// a tester
vector<string> get_all_btw(vector<string> data,string s_begin,string s_end,int n_begin,int* n_end)
{
	int k=vector_search(data,s_end,n_begin+1);
	int d=n_begin;
	int i;
	vector<string> part;
	while(k>d && d > -1 && k > -1)
	{
		if(vector_search(data,s_end,k+1) == -1)
			break;
		else 
			k=vector_search(data,s_end,k+1);
			d=vector_search(data,s_begin,d+1);
	}
	if(k>-1 && d>-1)
	{
		for(i=d;i<k;i++)
		{
			part.push_back(data[i]); 
		}
		*n_end=k;
	}else *n_end=-1;

	return part;
}
int recettes_check(vector<string> pars,vector<vector<string>> pinitial, int n)
{
	int i,j,k=0;
	if(pars.size()>n)
	{
		for(i=0;i<pinitial.size();i++)
		{	
			for(j=0;j<pinitial[i].size();j++)
			{
				if(string_find_list(pinitial[i][j],{"<instruct>","<parameter>","<value>"},0)!=-1)
				{
					if(j+1 <initial[i].size()) return i;
					if(vector_search(pars,pinitial[i][j+1],n+k)!=-1)
					{
						k=(vector_search(pars,pinitial[i][j+1],n+k))-n;
					}
				}
				else if(string_find(pinitial[i][j],"<name>",0)!=-1)
				{
					if(j+1==initial[i].size())return i;
					k++;
				}
				else if(string_find(pinitial[i][j],pars[n+k],0)!=-1)
				{
					if(j+1==initial[i].size())return i;
					k++;
				}
				else 
				{
					k=0;
					break;
				}
			}
		}
	}
	return -1;
}

void draw_program(struct i_program sprog)
{
	unsigned int i,j,k;
	printf("program --- \n");
	printf("var %zu\n",sprog.lvar.size());
	printf("fun %zu\n",sprog.lfunc.size());
	for(i=0;i<sprog.lvar.size();i++)
	{
		printf("variable name: %s type: %s\n",sprog.lvar[i].name.c_str(),sprog.lvar[i].type.c_str());
	}
	for(i=0;i<sprog.lfunc.size();i++)
	{
		printf("function name: %s type: %s\n",sprog.lfunc[i].name.c_str(),sprog.lfunc[i].return_type.c_str());
		for(j=0;j<sprog.lfunc[i].linst.size();j++)
			printf("instru %d: %s\n",j,sprog.lfunc[i].linst[j].c_str());
		for(j=0;j<sprog.lfunc[i].lparameter.size();j++)
			printf("parameter %d: %s\n",j,sprog.lfunc[i].lparameter[j].c_str());
	}

}


struct i_program Analyse_init(string file)
{
	unsigned int i;
	int itmp;
	int itmp2;
	int id_recette=0;
	struct i_program prog;
	struct i_variable var;
	struct i_function fun;
	struct i_struct stru;
	const string reading = ReadFile(file);
	const vector<string> pars = Parser(reading);
	vector<string> vtmp;
	// printf("rec_chec %d",recettes_check(pars,initial,5));
	for(i=0;i<pars.size();i++)
	{
		id_recette = recettes_check(pars,initial,i);

		if(id_recette!=-1)
		{
			printf("id %d i %d\n",id_recette,i);
			vtmp=initial[id_recette];
			// printf("i %d size %zu\n",i,vtmp.size());
			if(vector_search(vtmp,"<value>",0)==-1 &&
				vector_search(vtmp,"<parameter>",0)==-1 &&
				vector_search(vtmp,"<instruct>",0)==-1 &&
				vector_search(vtmp,"<name>",0)!=-1)
			{
				var.type=pars[i];
				var.name=pars[i+1];
				prog.lvar.push_back(var);
				i+= vtmp.size()-1;
			}
			else if(vector_search(vtmp,"<value>",0)!=-1 &&
				vector_search(vtmp,"<parameter>",0)==-1 &&
				vector_search(vtmp,"<instruct>",0)==-1 &&
				vector_search(vtmp,"<name>",0)!=-1)
			{
				var.type=pars[i];
				var.name=pars[i+1];
				prog.lvar.push_back(var);
				i+= vtmp.size()-1;
			}
			else if(vector_search(vtmp,"<value>",0)==-1 &&
				vector_search(vtmp,"<parameter>",0)!=-1 &&
				vector_search(vtmp,"<instruct>",0)!=-1 &&
				vector_search(vtmp,"<name>",0)!=-1)
			{
				fun.return_type = pars[i];
				fun.name = pars[i+1];
				itmp = vector_search(vtmp,"<parameter>",0);
				fun.lparameter = get_all_btw(pars,vtmp[itmp-1],vtmp[itmp+1],vector_search(pars,vtmp[itmp-1],i)+1,&itmp2);
				itmp = vector_search(vtmp,"<instruct>",0);
				fun.linst = get_all_btw(pars,vtmp[itmp-1],vtmp[itmp+1],vector_search(pars,vtmp[itmp-1],i)+1,&itmp2);
				prog.lfunc.push_back(fun);
				i=itmp2;
			}
			else if(vector_search(vtmp,"<value>",0)==-1 &&
				vector_search(vtmp,"<parameter>",0)==-1 &&
				vector_search(vtmp,"<instruct>",0)!=-1 &&
				vector_search(vtmp,"<name>",0)!=-1)
			{
				stru.name = pars[i+1];
				itmp = vector_search(vtmp,"<instruct>",0);
				stru.linst = get_all_btw(pars,vtmp[itmp-1],vtmp[itmp+1],vector_search(pars,vtmp[itmp-1],i)+1,&itmp2);
				prog.lstruct.push_back(stru);
				i=itmp2;
			}
		}
		//else i++;
	}
	// synth_check(pars,initial,&prog);
	draw_program(prog);

	return prog;
	
}

