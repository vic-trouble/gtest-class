#include "leap.h"

bool isLeap(unsigned year)
{
	return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}
