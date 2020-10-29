#include "neq_max_seq/lib.h"



neq_max_seq::neq_max_seq(int shm, long long n , bool multi_process_flag ) {
    srand(time(0));
    shmid = shm;
    memory_len = n;

    if (multi_process_flag)
        cores_count = sysconf(_SC_NPROCESSORS_ONLN);
    else 
        cores_count = 1;

   
    
    
}
neq_max_seq::~neq_max_seq() {
    shmdt(result_ptr);
}

int  neq_max_seq::start(){
    result_shmid =  shmget(rand(), cores_count*sizeof(cores_count) , IPC_CREAT|0666);
    if(result_shmid == -1) exit(1);
    pid_t pid;
    for (size_t i = 0; i < cores_count; i++){
       
        switch (pid = fork()){
        case -1:
            std::cerr << "fork error";
            exit(1);
            break;
        case 0:
            child();
            exit(0);
            break;
        case 1:
            process_take_task++;
            break;
        }
    }
    int status;
    for(int i = 0; i < cores_count; i++)
        wait(&status);
    result_ptr = (long long*) shmat(result_shmid, 0, 0);
    auto r = result_ptr[0];
    shmctl(result_shmid, IPC_RMID, nullptr);
    process_take_task = 0;
    
    return r;    
}


void neq_max_seq::child(){
    char *memory;
    if(shmid!=-1)  memory = (char*)shmat(shmid, nullptr, 0);    
    else{
        memory_len = 100*1024*1024;
        memory = new char[memory_len];
    }
    
    
    long long max = 0;
    long long seq =1;
    for (size_t i = 1; i < memory_len; i++){
        
        if( seq > max) 
            max= seq;
    
        if(memory[i] != memory[i-1]) seq++;
        else
            seq =1;
    }
   
    result_ptr = (long long*)shmat(result_shmid, 0,0);
    result_ptr[process_take_task] =max;
    std::cout << int(memory[3]);
    shmdt(result_ptr);
    if(shmid != -1) shmdt(memory);
    else delete[] memory;
}
