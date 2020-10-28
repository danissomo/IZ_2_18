
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <algorithm>
class neq_max_seq{
    unsigned char cores_count;
    unsigned char* process_take_task = new unsigned char;
    long* process_result;
    char* memory;
    long long memory_len;
    void child();
    public:
        neq_max_seq( char* = nullptr, long long = 0, bool= false);
        long start();
        ~neq_max_seq();
};