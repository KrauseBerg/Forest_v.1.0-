#ifndef UDP_H
#define UDP_H
#include "protocol.h"

class udp:public protocol{
public:
    void print(unsigned char* data, int len);
};

#endif // UDP_H
