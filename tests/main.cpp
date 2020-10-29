#include "gtest/gtest.h"
#include <time.h>
#include <random>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "neq_max_seq/lib.h"
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  
}
TEST(lib_test__neq_max_seq, hardcore_seq_singlecore){
  char payload1[] = {1, 1};
  char payload2[] = {1, 2, 1};
  char payload3[] = {1, 2, 3, 1};
  auto size = 100;
  auto shmid = shmget(1234, size , IPC_CREAT|0666);
  auto shmptr  = (char*) shmat(shmid, nullptr, 0 );
  for (size_t i = 0; i < size; i++){
        shmptr[i] = payload1[i%2];
  }
  
  neq_max_seq lib(shmid, size);
  ASSERT_EQ(lib.start(), 1);

  for (size_t i = 0; i < size; i++)
        shmptr[i] = payload2[i%3];
  neq_max_seq lib2(shmid, size);
  ASSERT_EQ(lib2.start(), 3);

  for (size_t i = 0; i < size; i++)
        shmptr[i] = payload3[i%4];
  neq_max_seq lib3(shmid, size);
  ASSERT_EQ(lib3.start(), 4);

  shmctl(shmid, 0,0);
}