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

bool ReadW(char* str, string fname, int start_position, int size)//return 1:the file has been read off
{
        ifstream fin;
        fin.open(fname.c_str());
        if(!fin.is_open()) exit(1);
        fin.seekg(start_position, ios::beg);
        fin.read(str, size);
//	fread((void*)str, size, 1, fin);
//	for(int i=0; i<size; i++)cout<<*(str+i);
  //      cout<<endl;
        return fin.eof();
}


double GetTime()//return ms
{
        struct timeval tv;
        if(gettimeofday(&tv, 0) < 0) //the second parameter is timezone
        {
                perror("oops");//mistake output
        }
        return (double)tv.tv_sec*1000 + (0.001 * (double)tv.tv_usec);
}


int main()
{
	double t1 = GetTime();
	char *p;
	int size;
	int start;
	cout<<"size"<<":";
	cin>>size;
	cout<<"start:";
	cin>>start;
	p = (char*)malloc(long(1024*1024)*long(1024*6)); 
/*	ifstream fin;
        fin.open("100MB.txt");
        if(!fin.is_open()) exit(1);
        fin.seekg(start, ios::beg);
        fin.read(p, size);
	for(int i=0; i<size; i++)cout<<*(p+i);
	cout<<endl;
	cout<<fin.eof()<<endl;
*/
	ReadW(p, "100MB.txt", start, size);
	printf("exe time: %f\n", GetTime() - t1);
	return 0;
}
