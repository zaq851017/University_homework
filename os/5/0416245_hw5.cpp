#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <deque>
#include <vector>
#include <list>
#include <iomanip>

using namespace std;
int main(){
// FIFO
FILE *trace=fopen("trace.txt","r");
cout<<"FIFO---\n";
cout<<"size      miss      hit      page fault ratio\n";
vector <unsigned int> in_file;
in_file.clear();
for(int i=64;i<=512;i=i*2){
   // struct timeval start, end;
    int index=0;
    cout<<i<<"      ";
  //  gettimeofday(&start, 0);
    int miss=0;
    int hit = 0;
    unsigned int address =0;
    unsigned int c_address=0;
    map <unsigned int,int> table;
    vector<unsigned int> d_table;
    table.clear();
    d_table.clear();
    if(i==64){
        fseek(trace, 0, SEEK_SET); // let file restart
        while ( fscanf(trace, "%*s %X,%*d", &address)!=EOF ){ //%X, 無正負號的十六進位整數
        c_address = address / 4096; //page size is 4kB
        in_file.push_back(c_address);
         map<unsigned int, int>::iterator it;
        it = table.find(c_address);
        if(it != table.end()){
            //hit
            hit = hit+1;
        }
        else{
            //miss
            if( table.size () >= i){
                unsigned int front_num=0;
                front_num=d_table.front();
                it=table.find(front_num);
                table.erase(it);
                //d_table.pop_front();
                d_table.erase(d_table.begin() );
            }
            miss = miss+1;
            table[c_address]=index;
            d_table.push_back(c_address);
            index++;
        }
      }

    }
    else{
        for(int j=0;j<in_file.size();j++){
        c_address = in_file[j]; //page size is 4kB
         map<unsigned int, int>::iterator it;
        it = table.find(c_address);
        if(it != table.end()){
            //hit
            hit = hit+1;
        }
        else{
            //miss
            if( table.size () >= i){
                unsigned int front_num=0;
                front_num=d_table.front();
                it=table.find(front_num);
                table.erase(it);
                //d_table.pop_front();
                d_table.erase(d_table.begin() );
            }
            miss = miss+1;
            table[c_address]=index;
            d_table.push_back(c_address);
            index++;
        }


        }


    }

    cout<<miss<<"      "<<hit<<"      "<< fixed << setprecision(9)<<(double)miss/(double)(miss+hit)<<"\n";

}

cout<<"LRU---\n";
cout<<"size      miss      hit      page fault ratio\n";

for(int i=64;i<=512;i=i*2){
    cout<<i<<"      ";
    int miss=0;
    int index=0;
    int  hit = 0;
    unsigned int address =0;
    unsigned int c_address=0;
    list<unsigned int> d_table;
    map <unsigned int,list<unsigned int>::iterator> table;
    table.clear();
    d_table.clear();

    for(int j=0;j<in_file.size();j++){
        c_address = in_file[j];
        map<unsigned int, list<unsigned int>::iterator >::iterator it;
        it = table.find(c_address);
        if(it != table.end()){ //hit
            d_table.erase( it->second );
            d_table.push_back(c_address);
            it->second = --d_table.end();
            hit=hit+1;
        }
        else{
            //miss
            if(d_table.size () >= i){
                unsigned int num = d_table.front();
                d_table.pop_front();
                table.erase(num);
            }

           miss = miss+1;
           d_table.push_back(c_address);
           table[c_address] = --d_table.end();
        }

    }
    cout<<miss<<"      "<<hit<<"      "<< fixed << setprecision(9)<<(double)miss/(double)(miss+hit)<<"\n";
}





return 0;
}
