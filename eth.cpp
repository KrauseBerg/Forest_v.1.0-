#include <iostream>
#include <vector>
#include "eth.h"

using namespace std;

eth::eth(){

}

void eth::print(unsigned char* data, int len){
    vector <int> byte;
    for(int i=0;i<len;i++){
        byte.push_back(data[i]);
    }
    cout<<endl<<"\nEthernet II, Src";
    for(int i=6;i<12;i++){
        cout<<uppercase<<hex<<":";
        if(byte[i]<0x10)
            cout<<"0";
        cout<<byte[i];
    }
    cout<<", Dst";
    for(int i=0;i<6;i++){
        cout<<uppercase<<hex<<":";
        if(byte[i]<0x10)
            cout<<"0";
        cout<<byte[i];
    }
    cout<<endl<<"   Destination";
    for(int i=0;i<6;i++){
        cout<<uppercase<<hex<<":";
        if(byte[i]<0x10)
            cout<<"0";
        cout<<byte[i];
    }
    cout<<endl<<"   Source";
    for(int i=6;i<12;i++){
        cout<<uppercase<<hex<<":";
        if(byte[i]<0x10)
            cout<<"0";
        cout<<byte[i];
    }
}
