#include "other.h"
#include <iostream>
#include <vector>

using namespace std;

other::other()
{

}

void other::print(unsigned char *data, int len){
    cout<<"It's other!"<<endl;
    vector <int> byte;
    for(int i=0;i<len;i++){
        byte.push_back(data[i]);
    }
}

