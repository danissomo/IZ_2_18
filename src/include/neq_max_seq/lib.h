
#include <iostream>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <set>
#include <unistd.h>
#include <algorithm>
#include <time.h>
#include <random>
class neq_max_seq{
    int shmid= -1;
    int result_shmid=-1;
    long long *result_ptr = nullptr;
    unsigned char cores_count;
    unsigned char process_take_task  = 0;
    long long memory_len;
    void child();
    public:
        neq_max_seq( int =-1, long long = 0, bool= true);
        int start();
        ~neq_max_seq();
};