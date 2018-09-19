#ifndef ARP_H
#define ARP_H
#include "protocol.h"

class arp:public protocol{
public:
    arp();
    void print(unsigned char* data, int len);
};

#endif // ARP_H
