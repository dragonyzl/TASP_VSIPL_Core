#include <stdio.h>
int main()
{
  int sum=0;
  int i=0;
  #pragma omp parallel
  {
    char* str="Hello World!";
    printf("%s\n", str) ;
    for(i=0;i<8;i++){
      sum+=i;
      printf("%d sum: %d\n",i,sum);
    }
  }
}