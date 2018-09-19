#ifndef TCP_H
#define TCP_H
#include "protocol.h"

class tcp:public protocol{
public:
    void print(unsigned char* data, int len);
};

#endif // TCP_H
