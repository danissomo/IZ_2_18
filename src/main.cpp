#include <iostream>
#include "neq_max_seq/lib.h"
int main(){
    auto buf = new char[4];
    neq_max_seq m(buf, 4);
    std::cout << m.start();
}