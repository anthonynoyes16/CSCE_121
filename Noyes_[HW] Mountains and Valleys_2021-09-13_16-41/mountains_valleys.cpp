#include <iostream>
#include "functions.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
	int a = 0;
	int b = 0;
	cout << "Enter numbers 10 <= a <= b < 10000: ";
	cin >> a >> b;

	while (!is_valid_range(a, b))
	{
		cout << "Invalid Input" << endl;
		cout << "Enter numbers 10 <= a <= b < 10000: ";	
		cin >> a >> b;
	}

	count_valid_mv_numbers(a, b);

	return 0;
}