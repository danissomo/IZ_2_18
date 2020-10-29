#include <iostream>
#include <random>
#include <time.h>
#include "neq_max_seq/lib.h"
#include <chrono>
class Timer
{
private:
	// Псевдонимы типов используются для удобного доступа к вложенным типам
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;
 
	std::chrono::time_point<clock_t> m_beg;
 
public:
	Timer() : m_beg(clock_t::now()){}
 
	void reset(){
		m_beg = clock_t::now();
	}
 
	double elapsed() const{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};
int main(){
    srand(time(0));
    auto size = 1024*1024*100;
    auto shmid = shmget(1234, size , IPC_CREAT|0666);
    auto shmptr  = (char*) shmat(shmid, nullptr, 0 );
    for (size_t i = 0; i < size; i++){
         shmptr[i] = rand() % 'Z';
    }
    neq_max_seq multiprocess(shmid, size);
    neq_max_seq singleprocess(shmid,size,false);
    int test_count= 10;
    Timer t;
      std::cout <<"--------------------multi--------------------"<< std::endl;
    for(int i =0; i < test_count; i++){
        auto start = t.elapsed();
        auto res = multiprocess.start();
        std:: cout << "max "<< res << " result "<< i <<": " <<t.elapsed() - start << '\n' ;
    }
    std::cout << "---------------------------------------------"<< std::endl;
    std:: cout << "result " <<t.elapsed()/double(test_count) << std::endl ;
    std::cout << "--------------------single-------------------"<< std::endl;
    t.reset();
     for(int i =0; i < test_count; i++){
        auto start = t.elapsed();
        auto res = singleprocess.start();
        std:: cout << "max "<< res << " result "<< i <<": " <<t.elapsed() - start << '\n' ;
    }
    std::cout << "---------------------------------------------"<< std::endl;
    std:: cout << "result " <<t.elapsed()/double(test_count) << std::endl ;
    shmctl(shmid,IPC_RMID,0);
}