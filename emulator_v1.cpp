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

int MemoryUnit(string mem)//to identify KB, MB, GB
{
	cout<<"mem="<<mem<<endl;
	if(PostfixIsMatch(mem, "KB") == 1)return 1;
	else if(PostfixIsMatch(mem, "MB") == 1)return 1024;
 	else if(PostfixIsMatch(mem, "GB") == 1)return (1024 * 1024);
  	else{return 1;}//Error condition
}

int TimeUnit(string mem)//to identify KB, MB, GB
{
        cout<<"time="<<mem<<endl;
        if(PostfixIsMatch(mem, "ms") == 1)return 1;
        else if(PostfixIsMatch(mem, "s") == 1)return 1000;
        else if(PostfixIsMatch(mem, "min") == 1)return (1000 * 60);
	else if(PostfixIsMatch(mem, "h") == 1)return (1000 * 60 * 60);
        else{return 1;}//Error condition
}

int ConvertToInt(char* data_size)
{
	int unit = MemoryUnit(data_size);
	string temp = data_size;
 	int lenth = strlen(data_size);
 	const char* p = data_size;
	int i;
	for(i = 0; i < lenth; i++)
	{
		if(data_size[i] >= '0' && data_size[i] <= '9'){}
		else break;
	}
//	while (*p >='0' && *p <= '9') p++;
	data_size[i] = '\0';
	cout<<"num = "<<atoi(data_size) * unit<<endl;
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

int main(int argc, char* argv[])
{
	const int KB = 1024;
	const int unit_KB_size = 64;
	const int unit_B_size = 64 * KB;
	int input_file_num = atoi(argv[1]);
	int output_file_num = atoi(argv[2]);
	int memory_size = ConvertToInt(argv[3]);
//	int CPU_time = ;
	char** p_input_file = argv + 5;
        char** p_output_file = argv+5+input_file_num;
	char *p_start = NULL;
	p_start = (char*)malloc(memory_size * KB);
	char* p = p_start;//p will move while p_start never move
	int flag = 0;
	int start_position;
/*
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
*/
/*	cout<<argv[4]<<endl;
	ReadW(p, argv[4], 0, unit_B_size);
	for(int i = 0; i<10; i++)cout<<p[i];
		cout<<endl;
*/
	free(p);
	p = NULL;
	return 0;
}
