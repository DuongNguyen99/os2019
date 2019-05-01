#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main()
{
  int pid1, pid2;
  printf("Main before fork()\n");
  pid1 = fork();
  if(pid1 == 0)
    {
    printf("\First child is running \"ps -ef\"\n");
    char* args[] = {"/bin/ps", "-ef", NULL};
    if(execvp("/bin/ps", args) < 0)
      {
      printf("Can not fork, finished running \"ps -ef\"\n");
      }
    }
  else 
  {
     waitpid(pid1, NULL, 0);
     printf("Parent after fork, child is %d\n\tCreate another child\n", pid1);
     pid2 = fork();
     if(pid2 == 0)
       {
       printf("Second child is running \"free -h\"\n");
       char* args[] = {"/usr/bin/free", "-h", NULL};
       if(execvp("/usr/bin/free", args) < 0)
         {
         printf("Can not fork, finished running \"free -h\"\n");
         }
       }
     else 
     {
      printf("Parent after 2 forks, the second child is %d\nDone.\n", pid2);
      waitpid(pid2, NULL, 0);
     }
   }
  return 0;
}
