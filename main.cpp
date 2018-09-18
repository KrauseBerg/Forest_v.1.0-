#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <sstream>

using namespace std;



struct pcap_file_header {
    int magic;
    short version_major;
    short version_minor;
    int thiszone;
    int sigfigs;
    int snaplen;
    int linktype;
};

struct timeval {
    int tv_sec;
    int tv_usec;
};

struct pcap_pkthdr{
    timeval hea;
    int caplen;
    int len;
};


class packet
{
public:
    //int mas;
    vector<int>mas;                             //
}a;


class  allpacet{
public:
    allpacet ();
    ~allpacet();
    vector <packet> obj_packet;
    void readpacket (char *fname);
    void printatr();
    void printdata(int n);
    void fillstack();
    void printstack(int n);
    virtual void print();
    void printokno(int n);
    stringstream ss;
protected:
    allpacet* stack[6];                       //
    int col, max, min, average,
    ipv4, arp, icmp, tcp, udp ,other;
    FILE *fin;                            //
    pcap_file_header hd;

    pcap_pkthdr head[100000];                  //

};

class Eth:public allpacet{
public:
    void print();
};
void Eth::print(){
    ss<<"\nEthernet...";
    cout<<ss.str();
    ss.str( "" );
}

class Ipv4:public allpacet{
public:
    void print();
};
void Ipv4::print(){
    ss<<"\n-Ipv4";
    cout<<ss.str();
    ss.str( "" );
}

class Arp:public allpacet{
public:
    void print();
};
void Arp::print(){
    ss<<"\n-Arp";
    cout<<ss.str();
    ss.str( "" );
}

class Tcp:public allpacet{
public:
    void print();
};
void Tcp::print(){
    ss<<"\n-Tcp";
    cout<<ss.str();
    ss.str( "" );
}

class Udp:public allpacet{
public:
    void print();
};
void Udp::print(){
    ss<<"\n-Udp";
    cout<<ss.str();
    ss.str( "" );
}

class Icmp:public allpacet{
public:
    void print();
};
void Icmp::print(){
    ss<<"\n-Icmp";
    cout<<ss.str();
    ss.str( "" );
}
class Other:public allpacet{
public:
    void print();
};
void Other::print(){
    ss<<"\n-Other protocol";
    cout<<ss.str();
    ss.str( "" );
}

allpacet ::allpacet(){
    col=0;
    min=0xFFFFF;
    max=0;
    average=0;
    ipv4=0;
    arp=0;
    icmp=0;
    tcp=0;
    udp=0;
    other=0;
}


allpacet ::~allpacet(){
    fclose(fin);
}

void allpacet::fillstack(){
    Eth* eth=new Eth();
    Ipv4* ip=new Ipv4();
    Arp* ar_p=new Arp();
    Udp* ud_p=new Udp();
    Tcp* tc_p=new Tcp();                                    //
    Icmp* icm_p=new Icmp();
    Other* oth_r=new Other();

    stack[0]=eth;
    stack[1]=ip;
    stack[2]=ar_p;
    stack[3]=ud_p;
    stack[4]=tc_p;
    stack[5]=icm_p;
    stack[6]=oth_r;
}
void  allpacet::readpacket(char *fname){
    try{
        if ( (fin = fopen(fname, "rb")) == NULL ){
                throw "Can't open file\n";
        }
    }
    catch(const char *p){
        system("cls");
        ss<<p<<ends;                                               //
        cout<<ss.str();
        ss.str( "" );
    }

    fread(&hd,1,sizeof(pcap_file_header),fin);



    for(int i=0;i<100000;i++){                                      //

        fread(&head[i],1,sizeof(pcap_pkthdr),fin);
        if (head[i].len>max)
            max=head[i].len;
        if(head[i].len<min)
            min=head[i].len;
        average+=head[i].len;
        obj_packet.push_back(a);
        col++;
        fseek(fin,head[i].len,SEEK_CUR);
    }

    fseek(fin,sizeof(pcap_file_header),SEEK_SET);
    int c=0;
    for(vector<packet>::iterator i=obj_packet.begin();i!=obj_packet.end();i++){
        fseek(fin,16,SEEK_CUR);
        for(int j=0;j<head[c].len;j++){
          //  i->mas[j]=getc(fin);
            i->mas.push_back(getc(fin));
        }
        if(i->mas[12]==0x08 ){
            switch (i->mas[13]){
            case 0x00: ipv4++;break;
            case 0x06: arp++;break;
            }
        }

        switch(i->mas[23]){
        case 0x1: icmp+=1;break;
        case 0x06: tcp+=1;break;
        case 0x11: udp+=1;break;
        default :other++;break;
        }
        c++;
    }
}

void allpacet::printatr(){
    ss<<endl<<"TOTAL :"<<endl
     <<"Number of packet:"<<col<<endl
    <<"length of max packet:"<<max<<endl
    <<"length of min packet:"<<min<<endl
    <<"average length of packet:"<<average/col<<endl<<endl
    <<"ipv4:"<<ipv4<<endl
    <<"arp:"<<arp<<endl<<endl
    <<"icmp:"<<icmp<<endl
    <<"tcp:"<<tcp<<endl
    <<"udp:"<<udp<<endl
    <<"other:"<<other<<ends;
    cout<<ss.str();
    ss.str( "" );
}

void allpacet::print(){
    cout<<"\n\nETHERNET:";
}
void allpacet::printdata(int n){
    packet m=obj_packet[n-1];
    ss<<endl<<"\n\nInput packet #"<<dec<<n<<endl<<"Capture lenght: "<<dec<<head[n-1].len<<endl;
    for(int i=0;i<head[n-1].caplen;i++){
        if (i%16==0) ss<<endl;
        if(i%8==0) ss<<"  ";
        if(m.mas[i]<0x10)
            ss<< "0";
        ss<<hex<<uppercase<<m.mas[i]<<" ";
        cout<<ss.str();
        ss.str( "" );
    }
    print();
}


void allpacet::printstack(int n){
    packet m=obj_packet[n-1];
    if(m.mas[12]==0x08 ){
        switch (m.mas[13]){
        case 0x00:stack[1]->print();break;
        case 0x06:stack[2]->print();break;
        }
    }                                                                       //

    switch(m.mas[23]){
    case 0x1: stack[5]->print();break;
    case 0x06:stack[4]->print();break;
    case 0x11:stack[3]->print();break;
    default :stack[6]->print();break;
    }
    printokno(n);
}
void allpacet::printokno(int n){
    packet m=obj_packet[n-1];
    ss<<endl<<"\nEthernet II, Src";
    for(int i=6;i<12;i++){
        ss<<uppercase<<hex<<":";
        if(m.mas[i]<0x10)
            ss<<"0";
        ss<<m.mas[i];
    }
    ss<<", Dst";
    for(int i=0;i<6;i++){
        ss<<uppercase<<hex<<":";
        if(m.mas[i]<0x10)
            ss<<"0";
        ss<<m.mas[i];
    }
    ss<<endl<<"   Destination";
    for(int i=0;i<6;i++){
        ss<<uppercase<<hex<<":";
        if(m.mas[i]<0x10)
            ss<<"0";
        ss<<m.mas[i];
    }
    ss<<endl<<"   Source";
    for(int i=6;i<12;i++){
        ss<<uppercase<<hex<<":";
        if(m.mas[i]<0x10)
            ss<<"0";
        ss<<m.mas[i];
    }
    ss<<endl<<"   Type:";
    if(m.mas[12]==0x08 ){
        switch (m.mas[13]){
        case 0x00:                              //ipv4
            ss<<"IPv4";
            ss<<" (0x";
            for(int i=12;i<14;i++){
                if(m.mas[i]<0x10)
                    ss<<"0";
                ss<<m.mas[i];}
            ss<<")\n";
            ss<<"Ithernet Protocol Version 4, Src: "<<dec<<m.mas[26]<<"."<<m.mas[27]<<"."<<m.mas[28]<<"."<<m.mas[29];
            ss<<", Dst: "<<dec<<m.mas[30]<<"."<<m.mas[31]<<"."<<m.mas[32]<<"."<<m.mas[33];
            ss<<endl<<"   Version: 4";
            ss<<endl<<"   Header lenght: 20 (5)";
            ss<<endl<<"   Total lenght: ";
            int total_lenght;
            total_lenght=(m.mas[16]<<8)|m.mas[17];
            ss<<dec<<total_lenght;
            ss<<endl<<"   Identificator: "<<"0x"<<hex<<m.mas[18]<<m.mas[19]<<dec<<" (";
            int ident;
            ident=(m.mas[18]<<8)|m.mas[19];
            ss<<dec<<ident<<")";
            ss<<endl<<"   Flags: 0x";
            switch(m.mas[20]){
            case 0x40:
                ss<<"02";
                break;
            case 0x00:
                ss<<"00";
                break;
            }
            ss<<endl<<"   Fragment offset: "<<dec<<m.mas[21];
            ss<<endl<<"   Time to live: "<<dec<<m.mas[22];
            ss<<endl<<"   Protocol: ";
            switch(m.mas[23]){
            case 0x1:
                ss<<"Icmp (1)";
                break;
            case 0x06:
                ss<<"Tcp (6)";
                break;
            case 0x11:
                ss<<"Udp (17)";
                break;
            }
            ss<<endl<<"   Header checksum: 0x"<<hex<<m.mas[24]<<m.mas[25];
            ss<<endl<<"   Source: "<<dec<<m.mas[26]<<"."<<m.mas[27]<<"."<<m.mas[28]<<"."<<m.mas[29];
            ss<<endl<<"   Destination: "<<dec<<m.mas[30]<<"."<<m.mas[31]<<"."<<m.mas[32]<<"."<<m.mas[33];
            switch(m.mas[23]){
            case 0x06:
                ss<<endl<<"Transmission Control Protocol, ";
                ss<<"Src Port: ";
                int src_port;
                src_port=(m.mas[34]<<8)|m.mas[35];
                ss<<dec<<src_port;
                ss<<", Dst Port: ";
                int dst_port;
                dst_port=(m.mas[36]<<8)|m.mas[37];
                ss<<dec<<dst_port;
                ss<<", Seq: ";
                ss<<endl<<"   Windows size value: ";
                int ws;
                ws=(m.mas[48]<<8)|m.mas[49];
                ss<<dec<<ws;
                ss<<endl<<"   Checksum: 0x"<<hex<<m.mas[50]<<m.mas[51];
                ss<<endl<<"   Urgent pointer: ";
                int up;
                up=(m.mas[52]<<8)|m.mas[53];
                ss<<dec<<up<<ends;
                break;
            case 0x11:
                ss<<endl<<"User Datagram Protocol, ";
                ss<<"Src Port: ";
                src_port=(m.mas[34]<<8)|m.mas[35];
                ss<<dec<<src_port;
                ss<<", Dst Port: ";
                dst_port=(m.mas[36]<<8)|m.mas[37];
                ss<<dec<<dst_port;
                ss<<endl<<"   Source port: "<<dec<<src_port;
                ss<<endl<<"   Destination port: "<<dec<<dst_port;
                int lgt;
                lgt=(m.mas[38]<<8)|m.mas[39];
                ss<<endl<<"   Lenght: "<<dec<<lgt;
                ss<<endl<<"   Checksum: 0x"<<hex<<m.mas[40]<<m.mas[41]<<ends;
                break;
            }
            break;
        case 0x06:                         //arp
            ss<<" ARP (0x"<<hex;
            if(m.mas[12]<0x10)
                ss<<"0";
            ss<<m.mas[12];
            if(m.mas[13]<0x10)
                ss<<"0";
            ss<<m.mas[13]<<")";
            ss<<endl<<"Padding: ";
            for (int i=42;i<60; i++){
                if(m.mas[i]<0x10)
                    ss<<"0";
                ss<<hex<<m.mas[i];
            }
            int opcode;
            opcode=(m.mas[20]<<8)|m.mas[21];
            ss<<endl<<"Address Resolution Protocol (";
            switch (opcode) {
            case 1:
                ss<<"request) ";
                break;
            case 2:
                ss<<"reply) ";
            }
            ss<<endl<<"   Hardware type: Ethernet (1)";
            ss<<endl<<"   Protocol type: ";
            if(m.mas[16]==0x08 ){
                switch (m.mas[17]){
                case 0x00: ss<<"IPv4(0x0800)";break;
                case 0x06: ss<<"ARP (0x0806)";break;
                }
            }
            ss<<endl<<dec<<"   Hardware size: "<<m.mas[18];
            ss<<endl<<dec<<"   Protocol size: "<<m.mas[19];
            ss<<endl<<dec<<"   Opcode: ";
            switch (opcode) {
            case 1:
                ss<<"request ";
                break;
            case 2:
                ss<<"reply ";
            }
            ss<<"("<<opcode<<")";
            ss<<endl<<"   Sender MAC address: ("<<m.mas[22]<<":"<<m.mas[23]<<":"<<
                m.mas[24]<<":"<<m.mas[25]<<":"<<m.mas[26]<<":"<<m.mas[27]<<")";
            ss<<endl<<"   Sender IP address: "<<dec<<m.mas[28]<<"."<<m.mas[29]<<"."
             <<m.mas[30]<<"."<<m.mas[31];
            ss<<endl<<"   Target MAC address: ("<<m.mas[32]<<":"<<m.mas[33]<<":"<<
                m.mas[34]<<":"<<m.mas[35]<<":"<<m.mas[36]<<":"<<m.mas[37]<<")";
            ss<<endl<<"   Target IP address: "<<dec<<m.mas[38]<<"."<<m.mas[39]<<"."
             <<m.mas[40]<<"."<<m.mas[41]<<ends;
            break;
        }
    }
    cout<<ss.str();
    ss.str( "" );
}

int main()
{
    char* fname;
    char* fname1;
    cout<<"Input File's source: ";
    cin>> fname1;
    char que;
    strcpy(fname, fname1);
    int n, l=0;
    allpacet b;
    b.ss<<"File: "<<fname;
    for(;;){
        b.ss<<endl<<"Input number of packet:"<<ends;
        cout<<b.ss.str();
        b.ss.str( "" );
        char q;
        try
        {
            cin>>n;
            char a='p';
            if(n>100000){
                while (n>100000){
                    system("cls");
                    cout<<"Incorrect input. Do you want to try again?(press y or n)";
                    cin>>q;
                    if(q=='y'){
                        cout<<"Input number of packet again:";
                        cin>>n;}
                    else if (q!='y'){
                        throw a;return 0;
                    }
                }
            }
            else if(n<=0){
                while (n<=0){
                    system("cls");
                    cout<<"Incorrect input. Do you want to try again?(press y or n)";
                    cin>>q;
                    if(q=='y'){
                        cout<<"Input number of packet again:";
                        cin>>n;}
                    else if (q!='y'){
                        throw a;return 0;
                    }
                }
            }
        }
        catch(char a){
            system("cls");
            cout<<"Incjjorrect input!!!";
            return 0;
        }
        system("cls");
        if(l==0){
            b.ss<<"Best protocol analyser started."<<ends;
            cout<<b.ss.str();
            b.ss.str( "" );
            b.readpacket(fname);
            system("cls");
            b.ss<<"\t\t\t\t\t\tMade By _IMBA-nG_ in -Lextucy- "<<endl<<endl<<ends;
            cout<<b.ss.str();
            b.ss.str( "" );
            b.printatr();
            b.fillstack();
        }
        b.printdata(n);
        b.printstack(n);
        l++;
        cout<<endl<<"\n\nDo you want to try again?";
        cin>>que;
        if(que!='y'){system("cls");break;}
        else {system("cls");continue;}
        system("cls");
    }
    cout<<"\nBest protocol analyser stopped...";
    return 0;
}

