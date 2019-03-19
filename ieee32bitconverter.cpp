#include "ieee32bitconverter.h"

IEEE32BitConverter::IEEE32BitConverter()
{

}

int IEEE32BitConverter::binaryToHexadecimal(string binary) {
    bitset<32> bits(binary);
    int hex = bits.to_ulong();
    return hex;
}

float IEEE32BitConverter::rConvert(string binary) {
    int hexNumber = binaryToHexadecimal(binary);
        bool negative  = !!(hexNumber & 0x80000000);
        int  exponent  = (hexNumber & 0x7f800000) >> 23;
        int sign = negative ? -1 : 1;
        exponent -= 127;
        int power = -1;
        float total = 0.0;
        for ( int i = 0; i < 23; i++ ) {
            int c = binary[ i + 9 ] - '0';
            total += (float) c * (float) pow( 2.0, power );
            power--;
        }
        total += 1.0;
        float value = sign * (float) pow( 2.0, exponent ) * total;
        return value;
}

string IEEE32BitConverter::convert(float value) {
        union {
             float input;
             int   output;
        }   data;

        data.input = value;
        bitset<sizeof(float) * CHAR_BIT>   bits(data.output);
        string mystring = bits.to_string<char,char_traits<char>,allocator<char> >();
        return mystring;
}
