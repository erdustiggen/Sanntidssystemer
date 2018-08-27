#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/times.h>

void busy_wait(struct timespec t);
struct timespec timespec_normalized(time_t sec, long nsec){
    while(nsec >= 1000000000){
        nsec -= 1000000000;
        ++sec;
    }
    while(nsec < 0){
        nsec += 1000000000;
        --sec;
    }
    return (struct timespec){sec, nsec};
}

struct timespec timespec_sub(struct timespec lhs, struct timespec rhs){
    return timespec_normalized(lhs.tv_sec - rhs.tv_sec, lhs.tv_nsec - rhs.tv_nsec);
}

struct timespec timespec_add(struct timespec lhs, struct timespec rhs){
    return timespec_normalized(lhs.tv_sec + rhs.tv_sec, lhs.tv_nsec + rhs.tv_nsec);
}

int timespec_cmp(struct timespec lhs, struct timespec rhs){
    if (lhs.tv_sec < rhs.tv_sec)
        return -1;
    if (lhs.tv_sec > rhs.tv_sec)
        return 1;
    return lhs.tv_nsec - rhs.tv_nsec;
}

void taskA_times(int seconds)
{
  int clock_ticks_per_second = sysconf(_SC_CLK_TCK);
  struct tms now;
  clock_t time_now = times(&now);

 while((time_now + seconds*clock_ticks_per_second) > times(&now)) {}

}

void busy_wait(struct timespec t){
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    struct timespec then = timespec_add(now, t);

    while(timespec_cmp(now, then) < 0){
        for(int i = 0; i < 10000; i++){}
        clock_gettime(CLOCK_MONOTONIC, &now);
    }
}


int main()
{
  // sleep(1);

  // struct timespec mytimer;
  // mytimer.tv_sec = 1;
  // mytimer.tv_nsec = 0;
  // busy_wait(mytimer);

  taskA_times(1);


  return 0;
}
