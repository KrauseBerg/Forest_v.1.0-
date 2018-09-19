#include "udp.h"
#include <iostream>
#include <vector>

using namespace std;

void udp::print(unsigned char *data, int len){
    vector <int> byte;
    for(int i=0;i<len;i++){
        byte.push_back(data[i]);
    }
    cout<<endl<<"User Datagram Protocol, ";
    cout<<"Src Port: ";
    int src_port;
    src_port=(byte[34]<<8)|byte[35];
    cout<<dec<<src_port;
    cout<<", Dst Port: ";
    int dst_port;
    dst_port=(byte[36]<<8)|byte[37];
    cout<<dec<<dst_port;
    cout<<endl<<"   Source port: "<<dec<<src_port;
    cout<<endl<<"   Destination port: "<<dec<<dst_port;
    int lgt;
    lgt=(byte[38]<<8)|byte[39];
    cout<<endl<<"   Lenght: "<<dec<<lgt;
    cout<<endl<<"   Checksum: 0x"<<hex<<byte[40]<<byte[41];
}

