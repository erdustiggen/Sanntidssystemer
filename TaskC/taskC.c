#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/times.h>
#include <x86intrin.h>
#include <string.h>
#include <sched.h>

int main()
{
  struct timespec t;
  int ns_max = 500;
  int histogram[ns_max];
  memset(histogram, 0, sizeof(int)*ns_max);

  for(int i = 0; i < 10*1000*100; ++i)
  {
    clock_gettime(CLOCK_MONOTONIC, &t);

    long ns_start = t.tv_nsec;
    int sucess = sched_yield();
    clock_gettime(CLOCK_MONOTONIC, &t);

    int ns = (int)(t.tv_nsec-ns_start);
    if(ns >= 0 && ns < ns_max)
    {
      histogram[ns]++;
    }
  }

  for(int i = 0; i < ns_max; i++){
    printf("%d\n", histogram[i]);
  }

  return 0;
}
