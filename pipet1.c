#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

// program for IPC communication in Linux

int main (int arc, char* argv[]) {
  // 5 => 5 *4  = 20 =>
 int p1[2];
if (pipe(p1) == -1) {return 1;}
int pid = fork();
if (pid == -1) {return 2;}
if (pid == 0) {
//child process
 int x;
if (read (p1[0], &x, sizeof(x)) == -1) { return 3; }
printf ("Received %d\n", x);
x +=4;
if (write(p1[1], &x, sizeof(x)) == -1) {return 4;}
printf("wrote %d\n", x);
} else {
//parent process
srand (time(NULL));
int y= rand() % 10;
if (write(p1[1], &y, sizeof(y)) == -1) {return 5;} 
printf("wrote %d\n", y);
if (read(p1[0], &y, sizeof(y)) == -1) {return 6;}
printf("result is %d\n", y);
wait(NULL);
}
close(p1[0]);
close(p1[1]);
return 0;
}
