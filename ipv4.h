#ifndef IPV4_H
#define IPV4_H
#include "protocol.h"

class ipv4:public protocol{
public:
    ipv4();
    void print(unsigned char* data, int len);
};

#endif // IPV4_H
