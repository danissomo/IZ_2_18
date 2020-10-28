#include "neq_max_seq/lib.h"



neq_max_seq::neq_max_seq(char* external_memory , long long n , bool multi_process_flag ) {
    if (external_memory != nullptr){
        memory = external_memory;
        memory_len = n;
    }else{
        memory_len = 100*1024*1024;
        memory = new char[memory_len];
    }
        
    if (multi_process_flag)
        cores_count = sysconf(_SC_NPROCESSORS_ONLN);
    else 
        cores_count = 1;

    process_result = new long[cores_count];
    *process_take_task  = 0;

}

neq_max_seq::~neq_max_seq() {
    delete[] memory;
    delete[] process_result;
    delete process_take_task;
}

long neq_max_seq::start(){
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
            break;
        }
    }
    long max = -1;
    for (size_t i = 0; i < cores_count; i++){
        int status;
        wait(&status);
        if(max < process_result[i]) max = process_result[i];
        
    }
    
    return max;    
}


void neq_max_seq::child(){
    process_take_task++;
    std::cout << getpid()<<" "<< process_take_task << std::endl;
}
