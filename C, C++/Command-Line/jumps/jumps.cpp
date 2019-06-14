#include <stdio.h>
#include <setjmp.h>

jmp_buf go;

void helper(void)
{
  printf("two, ");
  // instead of a return we will jump back to main
  // using the buffer set up there
  longjmp(go,1);
}



int main(int argc, char *argv[])
{
  printf("One, ");
  // prepare for a future long jump
  // return of 0 means we just
  // set up the buffer
  if (setjmp(go) == 0)
    {
      helper();
// not reached unless helper returns
      printf("I got the flu!\n");
      return 1;
    }
  // the long jmp  will wind up here
  printf("buckle my shoe.\n");
  return 0;
}
