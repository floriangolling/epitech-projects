#ifndef COMMONUTILS
#define COMMONUTILS

#include <stdio.h>

enum type : char{
    INTTYPEENCODER = 1,
    STRINGTYPEENCODER,
    BOOLTYPEENCODER
};

#pragma pack(push, 1)
struct Header {
    int magicNumber;
    int code;
    int size;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MessageChar {
    char data[50];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MessageBinary {
    int binary;
};
#pragma pack(pop)

#endif