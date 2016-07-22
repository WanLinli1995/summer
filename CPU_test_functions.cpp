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
#include <unistd.h>
#include <fstream>
using namespace std;

double mygettime(void) {//return ms of the local time(ms accuraccy)
  struct timeval tv;
  if(gettimeofday(&tv, 0) < 0) {//the second parameter is timezone
    perror("oops");//mistake output
  }
  return (double)tv.tv_sec*1000 + (0.001 * (double)tv.tv_usec);
}

template< typename Type >
void TestAddSub(const char* name)
{
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
  time_t start = clock();//
  double t1 = mygettime();//current tiem in ms
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
  sleep(3);//
  time_t end = clock();//
//  cout<<"time_t="<<double(end-start)*1000 / CLOCKS_PER_SEC<<endl;//
 // Pretend we make use of v so compiler doesn't optimize out
  //  the loop completely
  printf("%s add/sub CPU time: %f [%d]\n", name, double(end-start)*1000 / CLOCKS_PER_SEC, (int)v&1);
  printf("%s add/sub total time: %f [%d]\n", name, mygettime() - t1, (int)v&1);//the last parameter:odd is 1 while even is 0
}

template< typename Type >
void TestDiv(const char* name) 
{
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
  time_t start = clock();//
  double t1 = mygettime();//current tiem in seconds
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
/*  char str[6000];
  cout<<"input a string:";

  cin>>str;
  cout<<"the first three charactor you input is:"<<str[0]<<str[1]<<str[2]<<endl;
*/
  // Pretend we make use of v so compiler doesn't optimize out
  //  the loop completely
  time_t end = clock();//
//printf is much more efficient than cout
  printf("%s div CPU time: %f [%d]\n", name, double(end-start)*1000 / CLOCKS_PER_SEC, (int)v&1);
  printf("%s div total time: %f [%d]\n", name, mygettime() - t1, (int)v&1);
}



template< typename Type >
void TestMul(const char* name) 
{
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
  time_t start = clock();//
  double t1 = mygettime();//current tiem in seconds

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
  time_t end = clock();//
 // cout<<"time_t="<<double(end-start)*1000 / CLOCKS_PER_SEC<<endl;//
  printf("%s mul CPU time: %f [%d]\n", name, double(end-start)*1000 / CLOCKS_PER_SEC, (int)v&1);
  printf("%s mul total time: %f [%d]\n", name, mygettime() - t1, (int)v&1);
 
}

int main() {
  time_t start = clock();//
  double t1 = mygettime();
  TestAddSub< int >("int");
  time_t end = clock();//
  printf("Add CPU time: %f\n", double(end-start)*1000 / CLOCKS_PER_SEC);
  printf("Add total time: %f\n", mygettime() - t1);

  TestMul< int >("int");
  TestDiv< int >("int");
//  my_test< long >("long");
//  my_test< long long >("long long");
//  my_test< float >("float");
//  my_test< double >("double");

  return 0;
}
