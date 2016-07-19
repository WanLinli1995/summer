#include <stdio.h>
#ifdef _WIN32
#include <sys/timeb.h>
#else
#include <sys/time.h>
#endif
#include <time.h>
#include <iostream>
#include <cmath>
#include <cstdlib>

double
mygettime(void) {//return seconds of the local time(ms accuraccy)
# ifdef _WIN32
  struct _timeb tb;
  _ftime(&tb);
  return (double)tb.time + (0.001 * (double)tb.millitm);//return local time in seconds
# else
  struct timeval tv;//timeval structure:long tv_sec(second);tv_usec(ms)
  if(gettimeofday(&tv, 0) < 0) {//the second parameter is timezone
    perror("oops");//mistake output
  }
  return (double)tv.tv_sec + (0.000001 * (double)tv.tv_usec);
# endif
}

template< typename Type >
void my_test(const char* name) {
  Type v  = 0;
  // Do not use constants or repeating values
  //  to avoid loop unroll optimizations.
  // All values >0 to avoid division by 0
  // Perform ten ops/iteration to reduce
  //  impact of ++i below on measurements
  Type v0 = (Type)(rand() % 256)/16 + 1;
  Type v1 = (Type)(rand() % 256)/16 + 1;
  Type v2 = (Type)(rand() % 256)/16 + 1;
  Type v3 = (Type)(rand() % 256)/16 + 1;
  Type v4 = (Type)(rand() % 256)/16 + 1;
  Type v5 = (Type)(rand() % 256)/16 + 1;
  Type v6 = (Type)(rand() % 256)/16 + 1;
  Type v7 = (Type)(rand() % 256)/16 + 1;
  Type v8 = (Type)(rand() % 256)/16 + 1;
  Type v9 = (Type)(rand() % 256)/16 + 1;

  double t1 = mygettime();//current tiem in seconds
  for (size_t i = 0; i < 100000000; ++i) {
    v += v0;//multiple operation to be stable?
    v -= v1;
    v += v2;
    v -= v3;
    v += v4;
    v -= v5;
    v += v6;
    v -= v7;
    v += v8;
    v -= v9;
  }
  // Pretend we make use of v so compiler doesn't optimize out
  //  the loop completely
  printf("%s add/sub: %f [%d]\n", name, mygettime() - t1, (int)v&1);//the last parameter:odd is 1 while even is 0

  t1 = mygettime();
  for (size_t i = 0; i < 100000000; ++i) {
    v /= v0;
    v /= v1;
    v /= v2;
    v /= v3;
    v /= v4;
    v /= v5;
    v /= v6;
    v /= v7;
    v /= v8;
    v /= v9;
  }
  // Pretend we make use of v so compiler doesn't optimize out
  //  the loop completely
  printf("%s div: %f [%d]\n", name, mygettime() - t1, (int)v&1);

  t1 = mygettime();
  for (size_t i = 0; i < 100000000; ++i) {
    v *= v0;
    v *= v1;
    v *= v2;
    v *= v3;
    v *= v4;
    v *= v5;
    v *= v6;
    v *= v7;
    v *= v8;
    v *= v9;
  }
  // Pretend we make use of v so compiler doesn't optimize out
  //  the loop completely
  printf("%s mul: %f [%d]\n", name, mygettime() - t1, (int)v&1);
}



int main() {
  my_test< short >("short");
  my_test< long >("long");
  my_test< long long >("long long");
  my_test< float >("float");
  my_test< double >("double");
  readmemory();
  return 0;
}
