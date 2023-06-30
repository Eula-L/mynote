#include <stdio.h>
#include "common.h"

int main()
{
  int c =add(2,3);
  #ifdef _DEF_LOG
  printf("这是一个测试");
  printf("\n");
  #endif //_DEF_LOG
  printf("2 + 3 = %d\n",c);
  return 0;
}
