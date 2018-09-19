#include "arp.h"
#include <vector>
#include <iostream>

using namespace std;

arp::arp(){

}

void arp::print(unsigned char *data, int len){
    vector <int> byte;
    for(int i=0;i<len;i++){
        byte.push_back(data[i]);
    }
    cout<<" ARP (0x"<<hex;
    if(byte[12]<0x10)
        cout<<"0";
    cout<<byte[12];
    if(byte[13]<0x10)
        cout<<"0";
    cout<<byte[13]<<")";
    cout<<endl<<"Padding: ";
    for (int i=42;i<60; i++){
        if(byte[i]<0x10)
            cout<<"0";
        cout<<hex<<byte[i];
    }
    int opcode;
    opcode=(byte[20]<<8)|byte[21];
    cout<<endl<<"Address Resolution Protocol (";
    switch (opcode) {
    case 1:
        cout<<"request) ";
        break;
    case 2:
        cout<<"reply) ";
    }
    cout<<endl<<"   Hardware type: Ethernet (1)";
    cout<<endl<<"   Protocol type: ";
    if(byte[16]==0x08 ){
        switch (byte[17]){
        case 0x00: cout<<"IPv4(0x0800)";break;
        case 0x06: cout<<"ARP (0x0806)";break;
        }
    }
    cout<<endl<<dec<<"   Hardware size: "<<byte[18];
    cout<<endl<<dec<<"   Protocol size: "<<byte[19];
    cout<<endl<<dec<<"   Opcode: ";
    switch (opcode) {
    case 1:
        cout<<"request ";
        break;
    case 2:
        cout<<"reply ";
    }
    cout<<"("<<opcode<<")";
    cout<<endl<<"   Sender MAC address: ("<<byte[22]<<":"<<byte[23]<<":"<<
        byte[24]<<":"<<byte[25]<<":"<<byte[26]<<":"<<byte[27]<<")";
    cout<<endl<<"   Sender IP address: "<<dec<<byte[28]<<"."<<byte[29]<<"."
     <<byte[30]<<"."<<byte[31];
    cout<<endl<<"   Target MAC address: ("<<byte[32]<<":"<<byte[33]<<":"<<
        byte[34]<<":"<<byte[35]<<":"<<byte[36]<<":"<<byte[37]<<")";
    cout<<endl<<"   Target IP address: "<<dec<<byte[38]<<"."<<byte[39]<<"."
        <<byte[40]<<"."<<byte[41];
}

