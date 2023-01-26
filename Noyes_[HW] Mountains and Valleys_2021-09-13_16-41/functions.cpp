#include <iostream>
#include "functions.h"

using std::cout;
using std::endl;

bool is_valid_range(int a, int b)
{
    // test for positive a + a in correct range
    if (a >= 10 && a <= b && b < 10000)
    {
        return true;
    }
    else
    {
        return false;
    }
}

char classify_mv_range_type(int number)
{
    int temp1;
    int temp2;
    temp1 = 0;
    temp2 = 0;
    char out;
    int hold;
    hold = number;
    out = '-';
    while (hold >= 10)
    {
        if (hold == number)
        {
            temp1 = hold % 10;
        }
        else
        {
            temp1 = temp2;
        }
        hold /= 10;
        temp2 = hold % 10;
        if (temp1 > temp2 && (out == 'V' || out == '-'))
        {
            out = 'M';
        }
        else if (temp1 < temp2 && (out == 'M' || out == '-'))
        {
            out = 'V';
        }
        else
        {
            return 'N';
        }
    }
    return out;
}

void count_valid_mv_numbers(int a, int b)
{
    int count_m = 0;
    int count_v = 0;
    for (int i = a; i <= b; i++)
    {
        char x = classify_mv_range_type(i);
        if (x == 'M')
        {
            count_m += 1;
        }
        if (x == 'V')
        {
            count_v += 1;
        }
    }
    cout << "There are " << count_m << " mountain ranges and " << count_v << " valley ranges between " << a << " and " << b << "." << endl;
}