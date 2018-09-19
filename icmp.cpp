#include "icmp.h"
#include <iostream>
#include <vector>

using namespace std;

icmp::icmp(){

}

void icmp::print(unsigned char *data, int len){
    cout<<"It's Icmp!"<<endl;
    vector <int> byte;
    for(int i=0;i<len;i++){
        byte.push_back(data[i]);
    }
}

