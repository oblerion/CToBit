
#include "parser.hpp"
vector<string> Parser(string reading)
{
	int i=0,j=0,k=0,d=0;
	//string reading;
	vector<string> vdata;
	vector<vector<string>> vpara;
	vector<vector<string>> vinstru;
	int tmp;
	string stmp;
	int i_ins=0,i_para=0;
	//reading = ReadFile(file);
	//puts(reading.c_str());
	while(i<(signed int)reading.size())
	{
		if(reading[i]==' ' ||
		   reading[i]=='\t' ||
		   reading[i]=='\n') i+=1;
		else
		{
			
			if(string_find_list(reading,token,i)>-1)
			{
				j=string_find_list(reading,token,i);
				if(token[j].size()==1)
				{
					vdata.push_back(token[j]);

					if(token[j][0]=='(')
					{
						stmp= "#p"+ to_string(i_para);
						vdata.push_back(stmp);
						printf("parentese ( en %d\n",i);
						k=string_search(reading,")",i+1);
						d=i;
						while(k>d && d > -1 && k > -1)
						{
							if(string_search(reading,")",k+1) == -1)
								break;
							else 
								k=string_search(reading,")",k+1);
								d=string_search(reading,"(",d+1);
						}
						stmp=reading.substr(i+1,k-i-1);
						puts(stmp.c_str());
						vpara.push_back(Parser(stmp));
						i=k;
						i_para++;
					}
					else if(token[j][0]=='{')
					{
						stmp= "#i" + to_string(i_ins);
						vdata.push_back(stmp);
						//k=string_find(reading,"}",i);
						k=string_search(reading,"}",i+1);
						d=i;
						printf("%d %d\n",k,d);
						while(k>d && d > -1 && k > -1)
						{
							if(string_search(reading,"}",k+1) == -1)
								break;
							else 
							k=string_search(reading,"}",k+1);
							d=string_search(reading,"{",d+1);
						}
						vinstru.push_back(Parser(reading.substr(i+1,k-i-1)));
						i=k;
						i_ins++;
					}
					else i+= token[j].size();
				}
				else if(reading[i+token[j].size()]==' ')
				{
					vdata.push_back(token[j]);
					i+= token[j].size();
				}
				else
				{
					tmp=i+token[j].size();
					stmp = token[j];
					while(reading[tmp]!=' ' && 
						reading[tmp]!='=' && 
						reading[tmp]!='(' &&
						reading[tmp]!=')' &&
						reading[tmp]!=';' &&
						reading[tmp]!='*' &&
						reading[tmp]!='\n' &&
						reading[tmp]!=',')
					{
						stmp += reading[tmp];
						tmp+=1;
					}
					vdata.push_back(stmp);
					i=tmp;
				}
			}
			
			else 
			{
				tmp=i;
				stmp = "";
				while(reading[tmp]!=' ' && 
					reading[tmp]!='=' && 
					reading[tmp]!='(' &&
					reading[tmp]!=')' &&
					reading[tmp]!=';' &&
					reading[tmp]!='*' &&
					reading[tmp]!='\n' &&
					reading[tmp]!=',')
				{
					stmp += reading[tmp];
					tmp+=1;
				}
				vdata.push_back(stmp);
				i=tmp;
			}
		}
	}
	if(vpara.size()>0)
	{
		vdata.push_back(" ");
		for(i=0;i<vpara.size();i++)
		{
			for(j=0;j<vpara[i].size();j++)
			{
				vdata.push_back(vpara[i][j]);
			}
		}
		printf("para %zu\n",vpara.size());
	}
	if(vinstru.size()>0)
	{
		vdata.push_back(" ");
		for(i=0;i<vinstru.size();i++)
		{
			for(j=0;j<vinstru[i].size();j++)
			{
				vdata.push_back(vinstru[i][j]);
			}
		}
		printf("instru %zu\n",vinstru.size());
	}
	return vdata;
}
// vector<vector<string>> Parser_2(string file)
// {
// 	vector<vector<string>> vdata_2;
// 		string_find(reading,")")
				

// }
