#include "io.hpp"

string ReadFile(string file)
{
	stringstream buffer;
	ifstream fic(file.c_str());
	if(fic.good())
	{
		buffer<<fic.rdbuf();
		fic.close();
	}
	return buffer.str();
}
void WriteFile(string file,string data)
{
	ofstream fic(file.c_str());int i;
	if(fic.good() == 1)
	{
		
		for(i=0;i< (signed int) data.length();i++)
		{
			fic << data.substr(i,1);
		}
		
		fic.close();
	}
}
