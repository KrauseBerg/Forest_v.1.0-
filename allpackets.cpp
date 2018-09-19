#include <iostream>
#include <fstream>
#include <cstring>

#include "protocol.h"
#include "allpackets.h"
#include "packet.h"

#include "eth.h"
#include "arp.h"
#include "tcp.h"
#include "ipv4.h"
#include "udp.h"
#include "icmp.h"
#include "other.h"

using namespace std;

allpackets::allpackets(){
    m_fname=NULL;
    pack=NULL;
    m_min=1514;
    m_max=0;
    m_aver=0;
    a_udp=0;
    a_icmp=0;
    a_arp=0;
    a_ipv4=0;
    a_tcp=0;
    a_other=0;
}

allpackets::~allpackets(){
    if(m_count > 0){
        delete [] pack;
        delete [] data;
        delete [] m_fname;
    }
}

allpackets::allpackets(const allpackets &allpack){
    m_fname=allpack.m_fname;  pack=allpack.pack;
    m_min=allpack.m_min;      m_max=allpack.m_max;
    m_aver=allpack.m_aver;    a_udp=allpack.a_udp;
    a_icmp=allpack.a_icmp;    a_arp=allpack.a_arp;
    a_ipv4=allpack.a_ipv4;    a_tcp=allpack.a_tcp;
    a_other=allpack.a_other;  data=allpack.data;
}

allpackets &allpackets::operator=(const allpackets & allpack){
    if(this != &allpack){
        delete [] m_fname;
        delete [] pack;
        delete [] data;
        m_fname=allpack.m_fname;  pack=allpack.pack;
        m_min=allpack.m_min;      m_max=allpack.m_max;
        m_aver=allpack.m_aver;    a_udp=allpack.a_udp;
        a_icmp=allpack.a_icmp;    a_arp=allpack.a_arp;
        a_ipv4=allpack.a_ipv4;    a_tcp=allpack.a_tcp;
        a_other=allpack.a_other;  data=allpack.data;
    }
    return *this;
}

void allpackets::read_pcap_fh(char *fname){
    while(true){
        try{
            ifstream file(fname, ios::in | ios::binary);
            if(!file)
                throw 1;
            else break;
        }
        catch(int i){
            cout<<"-- Error! Don't found file! --";
            cout<<"Input File's source: ";
            cin>>fname;
        }
    }
    ifstream file(fname, ios::in | ios::binary);
    m_fname=new char[strlen(fname)+1];
    strcpy(m_fname,fname);
    file.read((char*)&fh, sizeof(pcap_file_header));
    m_count = 0;

    while((file.read((char*)&ph, sizeof(pcap_packet_header)))!=0){
        file.seekg(ph.caplen,ios_base::cur);
        if(ph.caplen > m_max)
            m_max = ph.caplen;
        if(ph.caplen < m_min)
            m_min = ph.caplen;
        m_aver += ph.caplen;
        m_count++;
    }
    m_aver = m_aver / m_count;
    int count = 0;
    file.clear();
    file.seekg(sizeof(pcap_file_header),ios_base::beg);
    pack = new packet[m_count];

    while((file.read((char*)&pack[count].m_ph, sizeof(pcap_packet_header)))!=0){
        pack[count].m_data = new unsigned char[pack[count].m_ph.caplen];
        file.read((char*)pack[count].m_data, pack[count].m_ph.caplen);
        pack[count].prot.push_back(new eth);
        if(pack[count].m_data[12]==0x08){
            switch (pack[count].m_data[13]){
            case 0x00: a_ipv4++;
                pack[count].prot.push_back(new ipv4);
                break;
            case 0x06: a_arp++;
                pack[count].prot.push_back(new arp);
                break;
            }
        }
        switch(pack[count].m_data[23]){
        case 0x1: a_icmp+=1;
            pack[count].prot.push_back(new icmp);
            break;
        case 0x06: a_tcp+=1;
            pack[count].prot.push_back(new tcp);
            break;
        case 0x11: a_udp+=1;
            pack[count].prot.push_back(new udp);
            break;
        default :a_other++;
            pack[count].prot.push_back(new other);
            break;
        }
        obj_packet.push_back(pack[count]);
        count++;
    }
    file.close();
}
void allpackets::print_attr(){
    cout<<endl<<"Analiser Started...\n";
    cout<<endl<<"File: "<<m_fname<<endl
       <<"TOTAL :"<<endl<<dec
      <<"Number of packet:"<<m_count<<endl
     <<"length of max packet:"<<m_max<<endl
    <<"length of min packet:"<<m_min<<endl
    <<"average length of packet:"<<m_aver<<endl<<endl;
    cout<<"ipv4:"<<a_ipv4<<endl
       <<"arp:"<<a_arp<<endl<<endl
      <<"icmp:"<<a_icmp<<endl
     <<"tcp:"<<a_tcp<<endl
    <<"udp:"<<a_udp<<endl
    <<"other:"<<a_other<<endl;
    //   cout<<ss.str();
    //    ss.str( "" );
}
int allpackets::print_Data(int num){
    if(num > m_count)
        return -1;
    return obj_packet[num-1].print_data(num);
}

void allpackets::print_protocol(int num){
    obj_packet[num-1].prot[0]->print(pack[num-1].m_data, pack[num-1].m_ph.len);
    obj_packet[num-1].prot[1]->print(pack[num-1].m_data, pack[num-1].m_ph.len);
    obj_packet[num-1].prot[2]->print(pack[num-1].m_data, pack[num-1].m_ph.len);

}
