#include "ipv4.h"
#include <iostream>
#include <vector>


using namespace std;

ipv4::ipv4(){

}

void ipv4::print(unsigned char *data, int len){
    vector <int> byte;
    for(int i=0;i<len;i++){
        byte.push_back(data[i]);
    }
    cout<<endl<<"   Type:";
    cout<<"IPv4";
    cout<<" (0x";
    for(int i=12;i<14;i++){
        if(byte[i]<0x10)
            cout<<"0";
        cout<<byte[i];
    }
    cout<<")\n";
    cout<<"Ithernet Protocol Version 4, Src: "<<dec<<byte[26]<<"."<<byte[27]<<"."<<byte[28]<<"."<<byte[29];
    cout<<", Dst: "<<dec<<byte[30]<<"."<<byte[31]<<"."<<byte[32]<<"."<<byte[33];
    cout<<endl<<"   Version: 4";
    cout<<endl<<"   Header lenght: 20 (5)";
    cout<<endl<<"   Total lenght: ";
    int total_lenght;
    total_lenght=(byte[16]<<8)|byte[17];
    cout<<dec<<total_lenght;
    cout<<endl<<"   Identificator: "<<"0x"<<hex<<byte[18]<<byte[19]<<dec<<" (";
    int ident;
    ident=(byte[18]<<8)|byte[19];
    cout<<dec<<ident<<")";
    cout<<endl<<"   Flags: 0x"<<hex<<byte[20]<<byte[21];
    cout<<endl<<"   Fragment offset: "<<dec<<byte[21];
    cout<<endl<<"   Time to live: "<<dec<<byte[22];
    cout<<endl<<"   Protocol: ";
    switch(byte[23]){
    case 0x1:
        cout<<"Icmp (1)";
        break;
    case 0x06:
        cout<<"Tcp (6)";
        break;
    case 0x11:
        cout<<"Udp (17)";
        break;
    }
    cout<<endl<<"   Header checksum: 0x"<<hex<<byte[24]<<byte[25];
    cout<<endl<<"   Source: "<<dec<<byte[26]<<"."<<byte[27]<<"."<<byte[28]<<"."<<byte[29];
    cout<<endl<<"   Destination: "<<dec<<byte[30]<<"."<<byte[31]<<"."<<byte[32]<<"."<<byte[33];
}
