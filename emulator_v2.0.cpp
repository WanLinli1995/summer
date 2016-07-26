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
	if(PostfixIsMatch(data, "KB") == 1)return 1;
	else if(PostfixIsMatch(data, "MB") == 1)return 1024;
 	else if(PostfixIsMatch(data, "GB") == 1)return (1024 * 1024);
	else if(PostfixIsMatch(data, "ms") == 1)return 1;
        else if(PostfixIsMatch(data, "s") == 1)return 1000;
        else if(PostfixIsMatch(data, "min") == 1)return (1000 * 60);
        else if(PostfixIsMatch(data, "h") == 1)return (1000 * 60 * 60);
  	else{return 1;}//Error condition
}

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
	return atoi(data_size) * unit;
}


void InputError()
{
	cout<<"Arguments should be './a.out <input_size>KB/MB/GB <output_size>KB/MB/GB '"<<endl;
}

bool ReadW(char* str, string fname, int start_position, int size, int interval)//return 1:the file has been read off
{
	ifstream fin(fname.c_str());
	if(!fin.is_open()) exit(1);
	int i = 0;
	char* head = str;
	fin.seekg(start_position, ios::beg);
	string temp;

	while((fin >> noskipws >> (*str)) && (i < size))
	{
		str = str + interval;
		i++;
	}
//	cout<<"fin.efo()= "<<fin.eof()<<endl;
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
	}
}

//void TakeUpMem(int mem_KB_size)

void Function(){}//To expend


int main(int argc, char* argv[])
{
	time_t start = clock();
        double t1 = GetTime();
	double cpu_time_used;
	double total_time_used;
	const int KB = 1024;
	const int Mb = 1024 * KB;

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
	int start_position = 0;
	int file_size_max, file_size_min, file_size_total;//KB
	//Assume that the files are larger than 64KB
	//Assume memory is certainly larger than 64KB
	int interval = memory_size / unit_KB_size / input_file_num;//The interval to store the content into the memory
/*	
	if(file_size_min < 64)//cases that cannot take up all the pages after reading all files once
	{
		for(int i = 0; i < memory_size * KB; i++)
		{
			*(p_start + i) = 'a';//fill all the page with minimum cost
			i += page_size;
		}
	}

*/	while(interval > page_size)//To make sure every page is used
	{
		unit_KB_size *= 2;
		interval = memory_size / unit_KB_size / input_file_num;
	}

/*	while(file_size_max / unit_KB_size > 400)//To control total time(avoid low reading efficiency)
	{
		unit_KB_size *= 2;
		interval = memory_size / unit_KB_size / input_file_num;
	}
*/
	int j = 0;
	cout << "mem = "<<memory_size;
	if(memory_size > 1100) 
        { 
                memory_size -= 1100;//To adjust memory offset
                interval = memory_size / unit_KB_size / input_file_num;
        }
        else {cout << "Memory is not enough to run the process" << endl;return 0;}

	do
	{
		j++;
		p = p_start;
		for(int i = 5; i < input_file_num + 5; i++)
		{
			string name = argv[i];
			if(name.compare("finished") == 0)continue;//If a file has been read off, dont't open it any more
			if (ReadW(p, argv[i], start_position, unit_B_size, interval) == 1)//Read 64KB for one time
			{
				flag = flag + 1;
				cout<<argv[i]<<" has been read off"<<endl;
				argv[i]=(char*)"finished";
				
			}
			p = p + unit_B_size * interval;
		}
		start_position += unit_B_size;
		
		//then do some operations:
		Function();
	}while(flag!=input_file_num);//only if all the files have been read off, flag = input_file_num 

	free(p_start);
        p_start = NULL;
	p = NULL;
	
	//Consume CPU
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
//	struct rusage rused;
 //       int status = 0;
//	int memory_usage = rused.ru_minflt * ( page_size / 1024 );
//        printf("Memory used: %d KB \n", memory_usage);
	printf("total time: %f\n", GetTime() - t1);
	return 0;
}
