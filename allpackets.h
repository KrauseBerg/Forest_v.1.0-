#ifndef ALLPACKETS_H
#define ALLPACKETS_H
#include "packet.h"
#include <vector>

using namespace std;

struct pcap_file_header {
    int magic;
    short version_major;
    short version_minor;
    int thiszone;
    int sigfigs;
    int snaplen;
    int linktype;
};

class allpackets{
public:
    allpackets();
    allpackets(const allpackets &allpack);
    allpackets & operator=(const allpackets & allpack);
    ~allpackets();
    void read_pcap_fh(char *fname);
    void print_attr();
    int print_Data(int num);
    void print_protocol(int num);
    //private:
    packet* pack;
    vector <packet> obj_packet;
    pcap_file_header fh;
    pcap_packet_header ph;
    char* m_fname;
    unsigned char* data;
    int m_count, m_aver, m_min,
    m_max, a_tcp, a_udp, a_icmp,
    a_ipv4, a_arp, a_other;
};

#endif // ALLPACKETS_H
