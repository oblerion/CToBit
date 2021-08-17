#include "string2.hpp"

int string_find(string s,string f,int n)
{
	int nb=0;
	if(s[n]==f[0])
	{
		if(f.size()==1) return n;
		else
		{
			for(int i=0;i<(unsigned int)f.size();i++)
			{
				if(s[n+i]==f[i]) nb+=1;
				else break;
			}
			if(nb==(signed int)f.size()) return n;
		}
	}
	return -1;
}
int string_search(string s,string f,int n)
{
	if(string::npos!=s.find(f,n)) return s.find(f,n);
	return -1;
}
int string_find_list(string s,vector<string> list,int n)
{
	int i;
	for(i=0;i<(signed int)list.size();i++)
	{
		if(string_find(s,list[i],n)>-1)
				return i;
	}
	return -1;
	
}
