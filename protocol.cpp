#include "protocol.h"
#include <iostream>
#include <vector>

using namespace std;

void protocol::print(unsigned char *data, int len){
    vector <int> byte;
    for(int i=0;i<len;i++){
        byte.push_back(data[i]);
    }
}
