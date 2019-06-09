#ifndef IEEE32BITCONVERTER_H
#define IEEE32BITCONVERTER_H

#include <iostream>
#include <limits.h>
#include <iomanip>
#include <bitset>
#include <math.h>

using namespace std;

class IEEE32BitConverter
{
public:
    IEEE32BitConverter();
    int binaryToHexadecimal(string binary);
    float rConvert(string binary);
    string convert(float value);
};

#endif // IEEE32BITCONVERTER_H
