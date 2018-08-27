#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/times.h>
#include <x86intrin.h>
#include <string.h>


int main()
{
//   int clock_ticks_per_second = sysconf(_SC_CLK_TCK);
//   clock_t t = clock();
//   struct tms now;
//   for(int i = 0; i < 10*1000*1000; i++){
//     times(&now);
//   }
//   t = clock() - t;
//   double access = (double)t/(CLOCKS_PER_SEC) * 100;
//   printf("Access time: %f\n", access);

  int ns_max = 50;
  int histogram[ns_max];
  int clock_ticks_per_second = sysconf(_SC_CLK_TCK);
  struct tms ts1;
  struct tms ts2;
  memset(histogram, 0, sizeof(int)*ns_max);

  for(int i = 0; i < 10*1000*100; ++i)
  {
    clock_t t1 = times(&ts1);

    clock_t t2 = times(&ts2);
    // TSC TICK AT 2.66 GHz

    printf("T2: %d \t T1: %d\n", (int)t2, (int)t1);
    int ns = (int)(t2-t1);
    //printf("t1: %d ,t2: %d ,Diff:%f \n",t1 , t2, (double)ns/2.66);
    if(ns >= 0 && ns < ns_max){
        histogram[ns]++;
    }
  }

  for(int i = 0; i < ns_max; i++){
    printf("%d\n", histogram[i]);
  }
  return 0;
}
