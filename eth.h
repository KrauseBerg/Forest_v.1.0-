#ifndef ETH_H
#define ETH_H
#include "protocol.h"

class eth:public protocol{
public:
    eth();
    void print(unsigned char* data, int len);
};

#endif // ETH_H
