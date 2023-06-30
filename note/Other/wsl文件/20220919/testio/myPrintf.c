#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main ()
{
  int fd_save=dup(STDOUT_FILENO);
  
  int fd_aa =open("bb",O_RDWR);
  if(-1==fd_aa)
  {
    perror("open fail");
    return 1;
  }

  dup2(fd_aa,STDOUT_FILENO);

  printf("this is test.\n");

  close(fd_aa);
  close(fd_save);

  return 0;

}
