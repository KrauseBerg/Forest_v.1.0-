#ifndef OTHER_H
#define OTHER_H
#include "protocol.h"

class other:public protocol
{
public:
    other();
    void print(unsigned char* data, int len);
};

#endif // OTHER_H
