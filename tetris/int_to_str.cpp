#include "int_to_str.h"
std :: string int_to_str(int x)
{
	if (x == 0) return "0";
	std::string s;
	while (x > 0)
	{
		s += x % 10 + '0';
		x /= 10;
	}
	std::reverse(s.begin(), s.end());
	return s;
}
