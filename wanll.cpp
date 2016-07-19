

/*int main(void)
{
  cout<<"totalram="<<menInfo.totalram<<endl;
  cout<<"totalswap="<<menInfo.totalswap<<endl;
  cout<<"mum unit="<<memInfo.mem_unit<<endl;
  string str[600];
  cout<<"input a string:";
  cin>>str;

  cout<<"totalram2="<<menInfo.totalram<<endl;
  cout<<"totalswap2="<<menInfo.totalswap<<endl;
  cout<<"mum unit2="<<memInfo.mem_unit<<endl;

  return 0;
}*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//Total Virtual Memory
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <iostream>

//struct sysinfo info;

//sysinfo(&info);
//long long totalVirtualMem = memInfo.totalram;
//Add other values in next statement to avoid int overflow on right hand side...
using namespace std;
int main()
{
  struct sysinfo info;
  sysinfo( &info );
//  return (size_t)info.totalram * (size_t)info.mem_unit;
  cout<<"totalram="<<info.totalram<<endl;
  cout<<"totalswap="<<info.totalswap<<endl;
  cout<<"mum unit="<<info.mem_unit<<endl;
  cout<<"freemem="<<info.freeram<<endl;
  string str;
  cout<<"input a string:";
  cin>>str;
//  gets(str);
  cout<<"totalram2="<<info.totalram<<endl;
  cout<<"totalswap2="<<info.totalswap<<endl;
  cout<<"mum unit2="<<info.mem_unit<<endl;
  cout<<"freemem="<<info.freeram<<endl;
  return 0;
}

