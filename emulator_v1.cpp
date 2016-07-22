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
using namespace std;

bool PostfixIsMatch(string dest, string postfix)
{
	int size_d = dest.size();
	int size_s = postfix.size();
	int j = size_s - 1;
	for(int i = size_d - 1; j >= 0; i--, j--)
	{
		if(dest[i] != postfix[j])break;
	}
	if(j == -1)return 1;
	else return 0;
}   

int Unit(string data)//to identify KB, MB, GB
{
//	cout<<"mem="<<data<<endl;
	if(PostfixIsMatch(data, "KB") == 1)return 1;
	else if(PostfixIsMatch(data, "MB") == 1)return 1024;
 	else if(PostfixIsMatch(data, "GB") == 1)return (1024 * 1024);
	else if(PostfixIsMatch(data, "ms") == 1)return 1;
        else if(PostfixIsMatch(data, "s") == 1)return 1000;
        else if(PostfixIsMatch(data, "min") == 1)return (1000 * 60);
        else if(PostfixIsMatch(data, "h") == 1)return (1000 * 60 * 60);
  	else{return 1;}//Error condition
}

/*
int TimeUnit(string time)//to identify KB, MB, GB
{
        cout<<"time="<<time<<endl;
        if(PostfixIsMatch(time, "ms") == 1)return 1;
        else if(PostfixIsMatch(time, "s") == 1)return 1000;
        else if(PostfixIsMatch(time, "min") == 1)return (1000 * 60);
	else if(PostfixIsMatch(time, "h") == 1)return (1000 * 60 * 60);
        else{return 1;}//Error condition
}
*/

int ConvertToInt(char* data_size)
{
	int unit = Unit(data_size);
	string temp = data_size;
 	int lenth = strlen(data_size);
 	const char* p = data_size;
	int i;
	for(i = 0; i < lenth; i++)
	{
		if(data_size[i] >= '0' && data_size[i] <= '9'){}
		else break;
	}
	data_size[i] = '\0';
//	cout<<"num = "<<atoi(data_size) * unit<<endl;
	return atoi(data_size) * unit;
}


void InputError()
{
	cout<<"Arguments should be './a.out <input_size>KB/MB/GB <output_size>KB/MB/GB '"<<endl;
}

bool ReadW(char* str, string fname, int start_position, int size)//return 1:the file has been read off
{
	ifstream fin(fname.c_str());
	if(!fin.is_open()) exit(1);
	int i = 0;
	cout<<"in_func"<<endl;
	fin.seekg(start_position, ios::beg);
	string temp;
	while(fin >> noskipws >> str[i] && i < size)//Don't egnore the space
	{
		i++;
	}
	cout<<"fin.efo()= "<<fin.eof()<<endl;
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

void RunCPU()//nearly and always less than 1ms
{
	int sum = 0;
	int n0 = (int)(rand() % 256);//Use random numbers to avoid loop unroll optimization
	int n1 = (int)(rand() % 256);
	int n2 = (int)(rand() % 256);
	int n3 = (int)(rand() % 256);
	int n4 = (int)(rand() % 256);
	int n5 = (int)(rand() % 256);
	int n6 = (int)(rand() % 256);
	int n7 = (int)(rand() % 256);
	int n8 = (int)(rand() % 256);
	int n9 = (int)(rand() % 256);
//	int n10 = (int)(rand() % 256);
//	int n11 = (int)(rand() % 256);

	for (int i = 0; i <20000; i++)
	{
		sum += n0;
		sum += n1;
		sum += n2;
		sum += n3;
		sum += n4;
		sum += n5;
		sum += n6;
		sum += n7;
		sum += n8;
		sum += n9;
	//	sum += n10;
	//	sum += n11;
	}
}

int main(int argc, char* argv[])
{
	time_t start = clock();
        double t1 = GetTime();
	time_t end;
	double cpu_time_used;
	double total_time_used;
	const int KB = 1024;
	int unit_KB_size = 64;
	int unit_B_size = unit_KB_size * KB;
	const int page_size = 4096;//bytes
	int input_file_num = atoi(argv[1]);
	int output_file_num = atoi(argv[2]);
	int memory_size = ConvertToInt(argv[3]);//return KB memory
	int CPU_time = ConvertToInt(argv[4]);
	char** p_input_file = argv + 5;
        char** p_output_file = argv+5+input_file_num;
	char *p_start = NULL;
	p_start = (char*)malloc(memory_size * KB);
	char* p = p_start;//p will move while p_start never move
	int flag = 0;
	int start_position;

	//Assume that the files are larger than 64KB
	//Assume memory is certainly larger than 64KB
	int interval = memory_size / unit_KB_size;//The interval to store the content into the memory
	while(interval > page_size)//To make sure every page is used
	{
		unit_KB_size *= 2;
		interval = memory_size / unit_KB_size;
	}

	do
	{
		cout<<"input_file_num="<<input_file_num<<endl;
		for(int i = 4; i < input_file_num + 4; i++)
		{
			cout<<" i= "<<i<<endl;
			start_position = unit_B_size * (i - 4) + 1;
			string name = argv[i];
			if(name.compare("finished") == 0)continue;
			if (ReadW(p, argv[i], start_position, unit_B_size) == 1)//Read 64KB for one time
			{
				flag++;
				cout<<argv[i]<<"has been read off"<<endl;
				argv[i]=(char*)"finished";
			}
			cout<<"flag="<<flag<<endl;
		}
		flag = 0;
		//then do some operations
		for(int i = 0; i<input_file_num * unit_B_size; i++)cout<<p[i];
		cout<<endl;
	}while(flag!=input_file_num);//only if all the files have been read off, flag = input_file_num 

/*	cout<<argv[4]<<endl;
	ReadW(p, argv[4], 0, unit_B_size);
	for(int i = 0; i<10; i++)cout<<p[i];
		cout<<endl;
*/
	free(p);
        p = NULL;
//	end = clock();
	cpu_time_used = double(clock() - start) * 1000 / CLOCKS_PER_SEC;
	while((cpu_time_used < CPU_time))
	{
		for(int i = 0; i < (CPU_time - cpu_time_used); i++)
		{
			RunCPU();
		}
		cpu_time_used = double(clock() - start) * 1000 / CLOCKS_PER_SEC;		
	}
	cout<<"CPU consumption time is:"<<cpu_time_used<<"ms"<<endl;
	return 0;
}
