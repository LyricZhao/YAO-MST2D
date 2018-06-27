/*
 * 2018 OOP Team Project - 2D MST
 * Zhao Chenggang & Zhou Yunshuo
 * This file is for timing, which could support different systems.
 */

# include "time.h"

# ifdef _WIN32

/* for Windows platform */
# include <windows.h>

unsigned long long get_wall_time() {
  LARGE_INTEGER ti, fq;
  QueryPerformanceFrequency(&fq);
  QueryPerformanceCounter(&ti);
  double tp = (double)ti.QuadPart / fq.QuadPart;
  return (unsigned long long) (tp * 1e6);
}

# else

/* for Linux or Unix */
# include <sys/time.h>

unsigned long long get_wall_time() {
  timeval ti;
  gettimeofday(&ti, NULL);
  return ti.tv_sec * 1000000ull + ti.tv_usec;
}

# endif

double getTimeDiff(unsigned long long t0, unsigned long long t1) {
  return double((t1 - t0) / 1e6);
}
