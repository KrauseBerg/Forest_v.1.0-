#ifndef ICMP_H
#define ICMP_H
#include "protocol.h"

class icmp:public protocol{
public:
    icmp();
    void print(unsigned char* data, int len);
};

#endif // ICMP_H
