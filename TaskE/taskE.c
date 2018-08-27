#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/times.h>
#include <x86intrin.h>
#include <string.h>
#include <sched.h>
#include "array.h"

int main()
{
  Array arr = array_new(6);

  for(int i = 0; i < 6; i++) {
    array_insertBack(&arr, i);
  }

  array_insertBack(&arr, 6);

  array_print(arr);

  return 0;
}
