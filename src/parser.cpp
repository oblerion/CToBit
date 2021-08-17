
#include "parser.hpp"

vector<string> Parser(string reading)
{
	int i=0,j=0,k=0,d=0;
	//string reading;
	vector<string> vdata;

	int tmp;
	string stmp;
	int i_ins=0,i_para=0;
	
	while(i<(signed int)reading.size())
	{
		//printf("%d\n",i);
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

					// if(token[j][0]=='(')
					// {
					// stmp= "#p"+ to_string(i_para);
					// 	vdata.push_back(stmp);
					// 	printf("parentese ( en %d\n",i);
					// 	stmp = get_all_btw(reading,"(",")",i);
					// 	puts(stmp.c_str());
					// 	vpara.push_back(stmp);
					// 	i=i+stmp.size();
					// 	i_para++;
					// }
					// else if(token[j][0]=='{')
					// {
					// 	stmp= "#i" + to_string(i_ins);
					// 	vdata.push_back(stmp);
					// 	stmp=get_all_btw(reading,"{","}",i);
					// 	if(stmp[0]=='\n') stmp.erase(0,1);
					// 	vinstru.push_back(stmp);
					// 	i=i+stmp.size();
					// 	i_ins++;
					// }
					// else 
					i+= token[j].size();
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
	return vdata;
}
