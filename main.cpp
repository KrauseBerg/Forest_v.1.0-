#include "allpackets.h"
#include "input.cpp"

int main(){
    char que='y';
    char* source=new char[1000];
    cout<<"Input File's source: ";
    cin>> source;
    while(que=='y'){
        cout<<"Input number of packet: ";
        int Num=inp();
        allpackets allpack;
        allpack.read_pcap_fh(source);
        allpack.print_attr();
        allpack.print_Data(Num);
        allpack.print_protocol(Num);
        cout<<"\n\n\nDo yoy want to try again? (y,n): ";
        cin>>que;
    }
    cout<<"\n\nBest analiser is stopped...";
}


