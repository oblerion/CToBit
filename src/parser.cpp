
#include "parser.hpp"

vector<string> Parser(string reading)
{
	int i=0,j=0,k=0,d=0;
	//string reading;
	vector<string> vdata;

	int tmp;
	string stmp;
	
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
				//si token  
				if(token[j].size()==1 || reading[i+token[j].size()]==' ')
				{
					vdata.push_back(token[j]);
					i+= token[j].size();
				}
				// si false token
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
			// si not token
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
