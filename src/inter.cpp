#include "inter.hpp"

struct i_program Analyse(string file)
{
	struct i_program prog;
	string reading = ReadFile(file);
	const vector<string> pars = Parser(reading);
	synth_check(pars,initial,&prog);
	draw_program(prog);

	return prog;
	
}

void synth_check(vector<string> pars,vector<vector<string>> dico,struct i_program* sprog)
{
	unsigned int i,j,k;
	int count,tmpcount;
	vector<int> lpos;
	vector<int> lpos_rec;
	struct i_variable var;
	struct i_function fun;

	// detect recette
	for(i=0;i<pars.size();i++)
	{
		if(string_find(pars[i]," ",0)==-1)
		{
			tmpcount=0;
			for(j=0;j<dico.size();j++)
			{
				if(string_find(pars[i],dico[j][0],0)!=-1 &&
					pars[i].size() == dico[j][0].size())
				{

					
					count=1;
					for(k=1;k<dico[j].size();k++)
					{
						if(pars.size() > i+k)
						{
							if(string_find("<name>",dico[j][k],0)!=-1)
							{
								count++;
							}
							else if(string_find("<value>",dico[j][k],0)!=-1)
							{
								count++;
							}
							else if(string_find("<parameter>",dico[j][k],0)!=-1)
							{
								if(string_search(pars[i+k],"#p",0)!=-1)
								count++;
							}
							else if(string_find("<instruct>",dico[j][k],0)!=-1)
							{
								if(string_search(pars[i+k],"#i",0)!=-1)
								count++;
							}
							else
							{
						
								if(string_find(pars[i+k],dico[j][k],0)!=-1)
									count++;
							}
						}
						
					}
					//printf("count %d tcount %d\n",count,tmpcount);
					if(tmpcount==0)
					{
						lpos.push_back(i);
						lpos_rec.push_back(j);
						tmpcount=count;
						//printf("find at %u i=%u\n",j,i);
					}
					else if(count>tmpcount)
					{
						lpos.pop_back();
						lpos_rec.pop_back();
						lpos.push_back(i);
						lpos_rec.push_back(j);
						tmpcount=count;
						//printf("find at %u i=%u\n",j,i);
					}
					printf("ok -- pars[%d] = %s dico[%d][0] = %s\n",i,pars[i].c_str(),j,dico[j][0].c_str());
						//break;
					printf("count = %d\n",count);
				}
				else 
				{
					//printf("nop -- pars[%d] = %s dico[%d][0] = %s\n",i,pars[i].c_str(),j,dico[j][0].c_str());
					//printf("count %d\n",count);
				}

			}
		
			vector<string> vs;
			//encodage 
			for(i=0;i<lpos.size();i++)
			{
				if(string_find_list("<name>",dico[lpos_rec[i]],0)!=-1 &&
					string_find_list("<value>",dico[lpos_rec[i]],0)==-1 &&
					string_find_list("<parameter>",dico[lpos_rec[i]],0)==-1 &&
					string_find_list("<instruct>",dico[lpos_rec[i]],0)==-1)
				{
					vs= dico[lpos_rec[i]];
					var.name =  pars[lpos[i]+string_find_list("<name>",vs,0)];
					var.type = pars[lpos[i]];
					sprog->lvar.push_back(var);

				}
				if(string_find_list("<name>",dico[lpos_rec[i]],0)!=-1 &&
					string_find_list("<value>",dico[lpos_rec[i]],0)!=-1 &&
					string_find_list("<parameter>",dico[lpos_rec[i]],0)==-1 &&
					string_find_list("<instruct>",dico[lpos_rec[i]],0)==-1)
				{
					vs= dico[lpos_rec[i]];
					var.name =  pars[lpos[i]+string_find_list("<name>",vs,0)];
					var.type = pars[lpos[i]];
					sprog->lvar.push_back(var);
				}
				if(string_find_list("<name>",dico[lpos_rec[i]],0)!=-1 &&
					string_find_list("<parameter>",dico[lpos_rec[i]],0)!=-1 &&
					string_find_list("<instruct>",dico[lpos_rec[i]],0)!=-1)
				{
					vs= dico[lpos_rec[i]];
					fun.name =  pars[lpos[i]+string_find_list("<name>",vs,0)];
					fun.return_type = pars[lpos[i]];
					sprog->lfunc.push_back(fun);
				}
			}
		}
		else break;
	}
}

void draw_program(struct i_program sprog)
{
	unsigned int i,j,k;
	printf("program --- \n");
	for(i=0;i<sprog.lvar.size();i++)
	{
		printf("variable name: %s type: %s\n",sprog.lvar[i].name.c_str(),sprog.lvar[i].type.c_str());
	}
	for(i=0;i<sprog.lfunc.size();i++)
	{
		printf("function name: %s type: %s\n",sprog.lfunc[i].name.c_str(),sprog.lfunc[i].return_type.c_str());
	}

}