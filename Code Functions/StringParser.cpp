#include <iostream>
#include <string>

using namespace std;

class StringParser
{
public:

	StringParser(int x){}
	
	int numberOf(string base, string s)
	{
		int n = 0;
		for (int i = 0; i <= (int)base.length() - (int)s.length(); i++)
		{
			if (base.substr(i, s.length()).compare(s) == 0)
			{
				n++;
			}
		}
		return n;
	}
};