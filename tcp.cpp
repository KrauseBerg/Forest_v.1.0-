#include <iostream>
#include <vector>
#include "tcp.h"

using namespace std;

void tcp::print(unsigned char *data, int len){
    vector <int> byte;
    for(int i=0;i<len;i++){
        byte.push_back(data[i]);
    }
    cout<<endl<<"Transmission Control Protocol, ";
    cout<<"Src Port: ";
    int src_port;
    src_port=(byte[34]<<8)|byte[35];
    cout<<dec<<src_port;
    cout<<", Dst Port: ";
    int dst_port;
    dst_port=(byte[36]<<8)|byte[37];
    cout<<dec<<dst_port;
    cout<<", Seq: ";
    cout<<endl<<"   Windows size value: ";
    int ws;
    ws=(byte[48]<<8)|byte[49];
    cout<<dec<<ws;
    cout<<endl<<"   Checksum: 0x"<<hex<<byte[50]<<byte[51];
    cout<<endl<<"   Urgent pointer: ";
    int up;
    up=(byte[52]<<8)|byte[53];
    cout<<dec<<up;
}

