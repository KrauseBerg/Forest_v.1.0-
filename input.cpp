#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

int inp(){
    int x;
    while(true){
        char* i=new char[20];
        cin>>i;
        int str=strlen(i);
        try{
            for(int j=0;j<str;j++){
                int b=atoi(&i[j]);
                if(b==0 && i[j]!='0'){
                    x=0;
                    throw b;
                    break;
                }
                else
                    x=atoi(&i[0]);
            }

        }
        catch(int i){
            cout<<"-- Error! Reinput number! -- : ";
        }

        if(x>0 && x<=100000){
            return x;
            break;
        }
    }
}
