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
#include <sys/types.h>
#include <dirent.h>
#include<unistd.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <malloc.h>
#include <sys/resource.h>
using namespace std;

int main()
{
	struct rusage rused;
        getrusage(RUSAGE_SELF, &rused);
        printf("mem usage start: %ld KB\n", rused.ru_maxrss);
	const int KB = 1024;
	int size = 3072;
	char *p = (char*)malloc(size*KB);
	char a = 'a';
	int page_size = 4 * KB;
	int interval;
//	struct rusage rused;
	getrusage(RUSAGE_SELF, &rused);
        printf("mem usage start: %ld KB\n", rused.ru_maxrss);
	cout<<"interval = ";
        cin >> interval;
//	char *p = (char*)malloc(size*KB);
	for(int i = 0; i < size * KB;)
	{
		*(p + i) = a;
	//	i += page_size;
	//	i += 2 * page_size;
		i += interval;
		

//		i++;
	}
        getrusage(RUSAGE_SELF, &rused);
        printf("mem usage end: %ld KB\n", rused.ru_maxrss);
	return 0;
}

