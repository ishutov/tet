#include "random.h"

int random(int num1, int num2)
{	
	return (int)(num1 + ((double) rand() * (num2- num1) / RAND_MAX));
}