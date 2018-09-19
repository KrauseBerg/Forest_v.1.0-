#include <iostream>
#include "packet.h"
#include "allpackets.h"

using namespace std;

int packet::print_data(int num){
    try{
        if(m_data == NULL)
            throw -1;
    }
    catch(int i){
        cout<<"--Error! Don't found DATA!--";
        return 0;
    }
    cout<<"Input packet #"<<num<<endl;
    cout<<"Captured lenght: "<<m_ph.caplen<<endl<<endl;
    cout<<hex<<uppercase;
    int count_str = m_ph.caplen / 16 + 1;
    int count_byte = 0;
    for(int i = 0; i < count_str; i++){
        cout<<"  ";
        for(int j = 0; j < 16; j++){
            if(j==8)
                cout<<" ";
            int byte = m_data[count_byte];
            if(byte < 0x10)
                cout<<"0";
            cout<<byte<<" ";
            count_byte++;
            if(count_byte ==m_ph.caplen)
                break;
        }
        cout<<endl;
    }
    cout<<dec<<endl;
    return 0;
}
