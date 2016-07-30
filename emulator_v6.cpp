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
	if(PostfixIsMatch(data, "KB") == 1)return 1024;
	else if(PostfixIsMatch(data, "MB") == 1)return (1024 * 1024);
 	else if(PostfixIsMatch(data, "GB") == 1)return (1024 * 1024 * 1024);
	else if(PostfixIsMatch(data, "ms") == 1)return 1;
        else if(PostfixIsMatch(data, "s") == 1)return 1000;
        else if(PostfixIsMatch(data, "min") == 1)return (1000 * 60);
        else if(PostfixIsMatch(data, "h") == 1)return (1000 * 60 * 60);
  	else{return 1;}//Error condition
}

long ConvertToInt(char* data_size)
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
	return (long)atoi(data_size) * (long)unit;
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

void WriteFromEnd(string fname, int size)
{
	char temp;
	ofstream fout(fname.c_str(), ios::app);
	if(!fout.is_open())
	{
		cout<<"Error opening file";
		exit(1);
	}
	
	srand((unsigned)time(NULL));
	for(int i = 0; i < size; i++)
	{
		temp = 'a' + rand() % 26;
                fout << temp;
	}
	fout.close();
}

void Function(){}//To expend


int main(int argc, char* argv[])
{
	struct rusage rused;
//	getrusage(RUSAGE_SELF, &rused);
//        printf("mem usage before time_t: %ld KB\n", rused.ru_maxrss);
	time_t start = clock();
//	getrusage(RUSAGE_SELF, &rused);
//        printf("mem usage after time_t: %ld KB\n", rused.ru_maxrss);
        double t1 = GetTime();
	double cpu_time_used;
	double total_time_used;
	const int B = 1;
	const int KB = 1024 * B;
	const int MB = 1024 * KB;
	const int w_unit = 64 * KB;
	int unit_KB_size = 64;
	int unit_B_size = unit_KB_size * KB;
	const int page_size = 4 * KB;//bytes
	int input_file_num = atoi(argv[1]);
	int output_file_num = atoi(argv[2]);
	long memory_size = ConvertToInt(argv[3]);//return KB memory
//	int file_size_total = ConvertToInt(argv[4]);//KB
	int file_size_max = ConvertToInt(argv[5]);
//	int file_size_min = ConvertToInt(argv[6]);
	int exe_time = ConvertToInt(argv[7]);
	int CPU_time = ConvertToInt(argv[8]);
	char** p_input_file = argv + 9;
        char** p_output_file = argv+ 9 +input_file_num;
	char *p_start = NULL;
	p_start = (char*)malloc(memory_size * (long)B);
	char* p = p_start;//p will move while p_start never move
	int flag = 0;
	int start_position = 0;
	//Assume that the files are larger than 64KB
	//Assume memory is certainly larger than 64KB
	int interval = memory_size / unit_B_size / input_file_num;//The interval to store the content into the memory
	getrusage(RUSAGE_SELF, &rused);
	long start_mem = rused.ru_maxrss;
	long offset = start_mem;
	long input_mem = memory_size;
	cout<<"mem input="<<(memory_size / 1024)<<endl;
	if(memory_size > 1188*KB)
        {
//                memory_size -= 1160*KB;//To adjust memory offset
                interval = memory_size / unit_B_size / input_file_num;
        }

        else {cout << "Memory is not enough to run the process" << endl;return 0;}
//	cout<<"mem="<<(memory_size / 1024)<<endl;

//	getrusage(RUSAGE_SELF, &rused);
//        printf("mem usage before a: %ld KB\n", rused.ru_maxrss);
	for(long i = 0; i <= memory_size;)
                {
                        *(p_start + i) = 'a';//fill all the page with minimum cost
                        i += page_size;
                }
//	getrusage(RUSAGE_SELF, &rused);
//        printf("mem usage after a: %ld KB\n", rused.ru_maxrss);
//	printf("offset: %ld KB\n", rused.ru_maxrss - input_mem / 1024);

	if(memory_size < unit_B_size)unit_B_size = memory_size;	

	while(file_size_max / unit_B_size > 400)//To control total time(avoid low reading efficiency)
	{
		unit_KB_size *= 2;
		unit_B_size *= 2;
		interval = memory_size / unit_B_size / input_file_num;
	}
	getrusage(RUSAGE_SELF, &rused);
        printf("mem usage before loop: %ld KB\n", rused.ru_maxrss);
	int j = 0;
	do
	{
		j++;
		p = p_start;
//		getrusage(RUSAGE_SELF, &rused);
//        	printf("mem usage %d0: %ld KB\n",j, rused.ru_maxrss);
		for(int i = 9; i < input_file_num + 9; i++)
		{
			string name = argv[i];
			if(name.compare("finished") == 0)continue;//If a file has been read off, dont't open it any more
//			getrusage(RUSAGE_SELF, &rused);
//     			printf("mem usage %d1: %ld KB\n",j, rused.ru_maxrss);
			if (ReadW(p, argv[i], start_position, unit_B_size, 1) == 1)//Read 64KB for one time
			{
				flag = flag + 1;
				cout<<argv[i]<<" has been read off"<<endl;
				argv[i]=(char*)"finished";
				
			}
			p = p + unit_B_size * interval;
		}
		start_position += unit_B_size;
//	getrusage(RUSAGE_SELF, &rused);
//        printf("mem usage for %d: %ld KB\n",j, rused.ru_maxrss);	
		//then do some operations:
		Function();
	}while(flag!=input_file_num);//only if all the files have been read off, flag = input_file_num 

	free(p_start);
        p_start = NULL;
	p = NULL;


	//output files
	int j2 = 0;//To record the times of writing the files
	int left;//To record the amount of data left each file
	int flag2 = 0;//To record how many files have been finished
	int out_file_size[output_file_num];
	int z = 0;//to match the file size and file name
	for(int i = 9 + input_file_num; i < argc; i = i+2)
	{
		out_file_size[z++] = ConvertToInt(argv[i+1]);
	}
	do
	{
		int t = 0;
		for(int i = 9 + input_file_num; i < argc; i = i+2)
		{
			string name2 = argv[i];
			if(name2.compare("finished") == 0)continue;//If a file is finished , don't open it any more	
			left = out_file_size[t++] - j2 * w_unit;
			if(left < w_unit)
			{
				WriteFromEnd(argv[i], left);
                                flag2 = flag2 + 1;
                                cout<<argv[i]<<" finished writing"<<endl;
                                argv[i]=(char*)"finished";
			}
			else WriteFromEnd(argv[i], w_unit);
		}
		j2++;
	}while(flag2 != output_file_num);

	
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
	printf("CPU time: %fms\n", cpu_time_used);
	getrusage(RUSAGE_SELF, &rused);
	printf("mem usage: %ld KB\n", rused.ru_maxrss);
//	int memory_usage = rused.ru_minflt * ( page_size / 1024 );
//        printf("Memory used: %d KB \n", memory_usage);
	int s_time = exe_time - GetTime() + t1;
	if(s_time > 0)sleep(s_time);
	printf("exe time: %f\n", GetTime() - t1);
	return 0;
}
