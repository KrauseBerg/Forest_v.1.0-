#ifndef PACKET_H
#define PACKET_H
#include <vector>
#include "protocol.h"

using namespace std;

struct timeval {
    int tv_sec;
    int tv_usec;
};

struct pcap_packet_header{
    timeval hea;
    int caplen;
    int len;
};

class packet{
public:
    int print_data(int num);
    unsigned char *m_data;
    pcap_packet_header m_ph;
    vector <protocol*> prot;
};

#endif // PACKET_H
