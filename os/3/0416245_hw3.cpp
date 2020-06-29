#include<iostream>
#include<fstream>
#include<vector>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include<algorithm>
using namespace std;
int* m_num=NULL ;
int* s_num=NULL ;
int num ;
sem_t up_down[15];
sem_t conver[8];
sem_t ok;
struct s_bound{
int left ;
int right;
};
s_bound bound[15];
int data[9];

void* q_sort(void* thread){
int t_use = *((int*)&thread);

if( t_use>=0 && t_use<=6){
    if(t_use==1)
            sem_wait(&up_down[0]);
    else if(t_use==2)
            sem_wait(&up_down[1]);
    else if(t_use==3)
            sem_wait(&up_down[2]);
    else if(t_use==4)
            sem_wait(&up_down[3]);
    else if(t_use==5)
            sem_wait(&up_down[4]);
    else if(t_use==6)
            sem_wait(&up_down[5]);

    int left = bound[t_use].left;
    int right = bound[t_use].right;
    int pivot = left;
    if(right > left)
        {
            int i = left, j = right+1;
            // choose left as pivot
            while(true){
                while(i+1 < right+1 && m_num[++i] < m_num[left]);
                while(j-1 > left-1 && m_num[--j] > m_num[left]);
                if(i >= j) break;
                swap(m_num[i],m_num[j]);
            }
            pivot = j;
            swap(m_num[left],m_num[pivot]);
        }
    bound[2*t_use+1].left = left;
    bound[2*t_use+1].right = pivot;
    bound[2*t_use+2].left = pivot+1;
    bound[2*t_use+2].right = right;
	if(t_use==0){
		sem_post(&up_down[0]);
		sem_post(&up_down[1]);
	}
	if(t_use==1){
		sem_post(&up_down[2]);
		sem_post(&up_down[3]);
	}
	if(t_use==2){
		sem_post(&up_down[4]);
		sem_post(&up_down[5]);
	}
	if(t_use==3){
		sem_post(&up_down[6]);
		sem_post(&up_down[7]);
	}
	if(t_use==4){
		sem_post(&up_down[8]);
		sem_post(&up_down[9]);
	}
	if(t_use==5){
		sem_post(&up_down[10]);
		sem_post(&up_down[11]);
	}
	if(t_use==6){
		sem_post(&up_down[12]);
		sem_post(&up_down[13]);
	}
	
}

else if(t_use >=7 && t_use<=14){
	if(t_use==7)
        sem_wait(&up_down[6]);
	else if(t_use==8)
        sem_wait(&up_down[7]);
	else if(t_use==9)
        sem_wait(&up_down[8]);
	else if(t_use==10)
        sem_wait(&up_down[9]);
	else if(t_use==11)
        sem_wait(&up_down[10]);
	else if(t_use==12)
        sem_wait(&up_down[11]);
	else if(t_use==13)
        sem_wait(&up_down[12]);
	else if(t_use==14)
        sem_wait(&up_down[13]);
	int left = bound[t_use].left;
    int right = bound[t_use].right;
	if(right > left)
        {
            for(int i=left; i<=right-1; i++)
                for (int j = i+1; j <= right; j++)
                    if(m_num[j] < m_num[i])
                        swap(m_num[j], m_num[i]);
        }
	if(t_use==7)
		sem_post(&conver[0]);
	else if(t_use==8)
		sem_post(&conver[1]);
	else if(t_use==9)
		sem_post(&conver[2]);
	else if(t_use==10)
		sem_post(&conver[3]);
	else if(t_use==11)
		sem_post(&conver[4]);
	else if(t_use==12)
		sem_post(&conver[5]);
	else if(t_use==13)
		sem_post(&conver[6]);
	else if(t_use==14)
		sem_post(&conver[7]);
	
}

pthread_exit(0);
}

void b_sort(int *a,int left,int right){
	if(right > left)
        {
            for(int i=left; i<right+1; i++)
                for (int j = i+1; j < right+1; j++)
                    if(a[j] < a[i])
                        swap(a[j], a[i]);
        }
	
	
}


void* s_sort(void* thread){

	int p[9]={0};
	p[0]=0;
	p[8]=num-1;
	int left=p[0];
	int right=p[8];
	 if(right > left)
        {
            int i = left, j = right+1;
            while(1){
                while(i+1 < right+1 && s_num[++i] < s_num[left]);
                while(j-1 > left-1 && s_num[--j] > s_num[left]);
                if(i >= j) break;
                swap(s_num[i],s_num[j]);
            }
            p[4] = j;
            swap(s_num[left],s_num[p[4]]);
        }
		
		left=p[0];
		right=p[4]-1;
		 if(right > left)
        {
            int i = left, j = right+1;
            while(1){
                while(i+1 < right+1 && s_num[++i] < s_num[left]);
                while(j-1 > left-1 && s_num[--j] > s_num[left]);
                if(i >= j) break;
                swap(s_num[i],s_num[j]);
            }
            p[2] = j;
            swap(s_num[left],s_num[p[2]]);
        }
	
		left=p[4];
		right =p[8];
		if(right > left)
        {
            int i = left, j = right+1;
            while(1){
                while(i+1 < right+1 && s_num[++i] < s_num[left]);
                while(j-1 > left-1 && s_num[--j] > s_num[left]);
                if(i >= j) break;
                swap(s_num[i],s_num[j]);
            }
            p[6] = j;
            swap(s_num[left],s_num[p[6]]);
        }
		
		left=p[0];
		right =p[2]-1;
		if(right > left)
        {
            int i = left, j = right+1;
            while(1){
                while(i+1 < right+1 && s_num[++i] < s_num[left]);
                while(j-1 > left-1 && s_num[--j] > s_num[left]);
                if(i >= j) break;
                swap(s_num[i],s_num[j]);
            }
            p[1] = j;
            swap(s_num[left],s_num[p[1]]);
        }
		left =p[2];
		right =p[4]-1;
		if(right > left)
        {
            int i = left, j = right+1;
            while(1){
                while(i+1 < right+1 && s_num[++i] < s_num[left]);
                while(j-1 > left-1 && s_num[--j] > s_num[left]);
                if(i >= j) break;
                swap(s_num[i],s_num[j]);
            }
            p[3] = j;
            swap(s_num[left],s_num[p[3]]);
        }
		
		left =p[4];
		right=p[6]-1;
		if(right > left)
        {
            int i = left, j = right+1;
            while(1){
                while(i+1 < right+1 && s_num[++i] < s_num[left]);
                while(j-1 > left-1 && s_num[--j] > s_num[left]);
                if(i >= j) break;
                swap(s_num[i],s_num[j]);
            }
            p[5] = j;
            swap(s_num[left],s_num[p[5]]);
        }
		left=p[6];
		right=p[8];
		if(right > left)
        {
            int i = left, j = right+1;
            while(1){
                while(i+1 < right+1 && s_num[++i] < s_num[left]);
                while(j-1 > left-1 && s_num[--j] > s_num[left]);
                if(i >= j) break;
                swap(s_num[i],s_num[j]);
            }
            p[7] = j;
            swap(s_num[left],s_num[p[7]]);
        }
		
	b_sort(s_num,p[0],p[1]-1);
	b_sort(s_num,p[1],p[2]-1);
	b_sort(s_num,p[2],p[3]-1);
	b_sort(s_num,p[3],p[4]-1);
	b_sort(s_num,p[4],p[5]-1);
	b_sort(s_num,p[5],p[6]-1);
	b_sort(s_num,p[6],p[7]-1);
	b_sort(s_num,p[7],p[8]);	
	
	
    sem_post(&ok);
	pthread_exit(0);
}



int main(){

char path[100];
cout<<"Key the name of input file\n";
cin>>path;

ifstream in_file(path ,ifstream::in );
in_file>>num;
//s_num.clear();
//m_num.clear();
s_num =new int[num];
m_num =new int[num];
int dig =0;
for(int i=0;i< num ;i++){
    in_file>> s_num[i];
	m_num[i] = s_num[i];
}
in_file.close();
// finish read file
for(int i=0;i<15;i++){
    sem_init(&up_down[i], 0, 0);
}
for(int i=0;i<8;i++){
    sem_init(&conver[i], 0, 0);
}
struct timeval start, end;
gettimeofday(&start, 0);
// mt start
pthread_t thread[15];
bound[0].left = 0;
bound[0].right = (num-1);
for (int i = 0; i < 15; i++)
        pthread_create(&thread[i], NULL, q_sort, (void*)(intptr_t)i);
for(int i=0;i<8;i++){
	sem_wait(&conver[i]);
}
gettimeofday(&end, 0);

long sec = end.tv_sec - start.tv_sec;
long usec = end.tv_usec - start.tv_usec;
cout << "Elapsed time of MT sorting: " << (float)sec+(usec/1000000.0) << " sec\n";
ofstream outputMT("./output1.txt", std::ios::out); 
for(int i=0; i<num; i++)
        outputMT << m_num[i] << " ";
  outputMT.close();

gettimeofday(&start, 0);
//bubble_sort(s_num, num);
sem_init(&ok, 0, 0);
pthread_t s_thread;
pthread_create(&s_thread, NULL, s_sort, (void*)(intptr_t)0);
sem_wait(&ok);
gettimeofday(&end, 0);  
long sec2 = end.tv_sec - start.tv_sec;
long usec2 = end.tv_usec - start.tv_usec;
cout << "Elapsed time of ST sorting: " << (float)sec2+(usec2/1000000.0) << " sec\n";
ofstream outputST("./output2.txt", std::ios::out); 
    for(int i=0; i<num; i++)
        outputST << s_num[i] << " ";
	outputST.close();

    delete [] m_num;
    delete [] s_num;


return 0;
}
