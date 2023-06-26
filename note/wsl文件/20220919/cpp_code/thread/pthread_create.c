#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
struct Test {
  /* data */
  int num;
  int age;
};

void *callback(void *arg) {
  for (int i = 0; i < 5; ++i) {
    printf("子线程：%d\n", i);
  }
  printf("子线程：%ld\n", pthread_self());

  //线程退出
  pthread_exit(t);
  return NULL;
}

int main() {
  struct Test t;
  pthread_t tid;
  pthread_create(&tid, NULL, callback, &t);
  // {
  //   printf("主线程：i=%d\n",i);
  // }
  printf("主线程：%ld\n", pthread_self());
  // sleep(3);
  //线程退出函数，一般是对主线程使用，让主线程退出但是不回收进程空间
  // pthread_exit(NULL);

  //线程回收
  void *ptr;
  pthread_join(tid, &ptr);
  printf("num :%d,age :%d\n", t.num, t.age);
  return 0;
}
