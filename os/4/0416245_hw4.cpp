#include<iostream>
#include<fstream>
#include<vector>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include<algorithm>
#include<queue>
using namespace std;


struct s_bound{
int left ;
int right;
};

s_bound bound[15];
int num;
int *s_num;
int *n_use;
sem_t s_job;
sem_t up_down[15];
sem_t conver[8];
queue<int>jobqueue;

int j_count;

void b_sort(int left,int right){
    for(int i=left;i<=right;i++){
        for(int j=i+1;j<=right;j++)
        if(n_use[j]<n_use[i]){
            int temp = n_use[j];
            n_use[j] = n_use[i];
            n_use[i]= temp;
        }
    }


}

// func

void thr (int j_id){

if( j_id>=0 && j_id<=6){

    if(j_id==1)
            sem_wait(&up_down[0]);
    else if(j_id==2)
            sem_wait(&up_down[1]);
    else if(j_id==3)
            sem_wait(&up_down[2]);
    else if(j_id==4)
            sem_wait(&up_down[3]);
    else if(j_id==5)
            sem_wait(&up_down[4]);
    else if(j_id==6)
            sem_wait(&up_down[5]);

    int left = bound[j_id].left;
    int right = bound[j_id].right;
    int pivot = left;
    if(right > left)
        {
            int i = left, j = right+1;
            // choose left as pivot
            while(true){
                while(i+1 < right+1 && n_use[++i] < n_use[left]);
                while(j-1 > left-1 && n_use[--j] > n_use[left]);
                if(i >= j) break;
                swap(n_use[i],n_use[j]);
            }
            pivot = j;
            swap(n_use[left],n_use[pivot]);
        }

    bound[2*j_id+1].left = left;
    bound[2*j_id+1].right = pivot;
    bound[2*j_id+2].left = pivot+1;
    bound[2*j_id+2].right = right;
    j_count++;
    sem_wait(&s_job);
    jobqueue.push( 2*j_id+1 );
    jobqueue.push( 2*j_id+2 );
    sem_post(&s_job);

	if(j_id==0){
		sem_post(&up_down[0]);
		sem_post(&up_down[1]);
	}
	if(j_id==1){
		sem_post(&up_down[2]);
		sem_post(&up_down[3]);
	}
	if(j_id==2){
		sem_post(&up_down[4]);
		sem_post(&up_down[5]);
	}
	if(j_id==3){
		sem_post(&up_down[6]);
		sem_post(&up_down[7]);
	}
	if(j_id==4){
		sem_post(&up_down[8]);
		sem_post(&up_down[9]);
	}
	if(j_id==5){
		sem_post(&up_down[10]);
		sem_post(&up_down[11]);
	}
	if(j_id==6){
		sem_post(&up_down[12]);
		sem_post(&up_down[13]);
	}

}

else if(j_id >=7 && j_id<=14){
    j_count++;
    if(j_id==7)
        sem_wait(&up_down[6]);
	else if(j_id==8)
        sem_wait(&up_down[7]);
	else if(j_id==9)
        sem_wait(&up_down[8]);
	else if(j_id==10)
        sem_wait(&up_down[9]);
	else if(j_id==11)
        sem_wait(&up_down[10]);
	else if(j_id==12)
        sem_wait(&up_down[11]);
	else if(j_id==13)
        sem_wait(&up_down[12]);
	else if(j_id==14)
        sem_wait(&up_down[13]);

	int left = bound[j_id].left;
    int right = bound[j_id].right;

	if(right > left)
            b_sort(left,right);

    if(j_id==7)
		sem_post(&conver[0]);
	else if(j_id==8)
		sem_post(&conver[1]);
	else if(j_id==9)
		sem_post(&conver[2]);
	else if(j_id==10)
		sem_post(&conver[3]);
	else if(j_id==11)
		sem_post(&conver[4]);
	else if(j_id==12)
		sem_post(&conver[5]);
	else if(j_id==13)
		sem_post(&conver[6]);
	else if(j_id==14)
		sem_post(&conver[7]);

}



}

void* t_func(void* p){

    int j_id;

    while(j_count <15){

        sem_wait(&s_job);

        if( jobqueue.empty() ){
            j_id = -1;
        }
        else {
            j_id =jobqueue.front();
            jobqueue.pop();
        }

        sem_post(&s_job);

        if(j_id != -1){
            thr(j_id);
        }

    }

    pthread_exit(0);
}



int main(){
char path[100];
num =0;
cout<<"Key the name of input file\n";
cin>>path;
ifstream in_file(path ,ifstream::in );
in_file>>num;
s_num =new int[num];
n_use =new int [num];
for(int i=0;i<num;i++)
    in_file>>s_num[i];
in_file.close();
// create thread pool
pthread_t pool[8];

for(int t_size=1;t_size<=8;t_size++){
  //  int n_use[num];
    j_count = 0;
    for(int i=0;i<num;i++)
        n_use[i]=s_num[i];

    for(int i=0;i<15;i++)
        sem_init(&up_down[i],0,0);

    for(int i=0;i<8;i++)
        sem_init(&conver[i],0,0);

    //jobqueue.clear();
     while (!jobqueue.empty())
    {
        jobqueue.pop();
    }

    sem_init(&s_job,0,1) ; // job = 1
    jobqueue.push(0);
    // start cal
    bound[0].left = 0;
    bound[0].right = num-1;

    struct timeval start, end;
    gettimeofday(&start, 0);

    for(int i=0;i<t_size;i++){
        pthread_create(&pool[i],NULL,t_func,NULL);
    }

    for(int i=0;i<8;i++)
        sem_wait(&conver[i]);

    gettimeofday(&end, 0);
    //end

    long sec = end.tv_sec-start.tv_sec;
    long usec = end.tv_usec -start.tv_usec;
    cout << "Elapsed time of MT sorting with a thread pool of " << t_size <<" threads: "<<(float)sec+(usec/1000000.0) << " sec\n";
    if(t_size == 1){
        ofstream outputMT("./output1.txt", std::ios::out);
        for(int i=0;i<num;i++)
            outputMT<<n_use[i]<<" ";
        outputMT.close();
    }
    else if(t_size == 2){
        ofstream outputMT("./output2.txt", std::ios::out);
        for(int i=0;i<num;i++)
            outputMT<<n_use[i]<<" ";
        outputMT.close();
    }
    else if(t_size == 3){
        ofstream outputMT("./output3.txt", std::ios::out);
        for(int i=0;i<num;i++)
            outputMT<<n_use[i]<<" ";
        outputMT.close();
    }
    else if(t_size == 4){
        ofstream outputMT("./output4.txt", std::ios::out);
        for(int i=0;i<num;i++)
            outputMT<<n_use[i]<<" ";
        outputMT.close();
    }
    else if(t_size == 5){
        ofstream outputMT("./output5.txt", std::ios::out);
        for(int i=0;i<num;i++)
            outputMT<<n_use[i]<<" ";
        outputMT.close();
    }

    else if(t_size == 6){
        ofstream outputMT("./output6.txt", std::ios::out);
        for(int i=0;i<num;i++)
            outputMT<<n_use[i]<<" ";
        outputMT.close();
    }
    else if(t_size == 7){
        ofstream outputMT("./output7.txt", std::ios::out);
        for(int i=0;i<num;i++)
            outputMT<<n_use[i]<<" ";
        outputMT.close();
    }
    else if(t_size == 8){
        ofstream outputMT("./output8.txt", std::ios::out);
        for(int i=0;i<num;i++)
            outputMT<<n_use[i]<<" ";
        outputMT.close();
    }


}

delete []n_use;
delete []s_num;

return 0;
}
