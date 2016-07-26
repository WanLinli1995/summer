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


int main()
{
	char size_str[10];
	char temp;
	int size;
	string fname;
	cout << "filename: ";
	cin >> fname;
	ofstream fout(fname.c_str());
	if(!fout.is_open())
	{
		cout<<"Error opening file";
		exit(1);
	}

	cout << "size = ";
	cin >> size_str;
	size = ConvertToInt(size_str);
	srand((unsigned)time(NULL));
	for(int i = 0; i < 1024; i++)//the unit is KB
	{
		for(int j = 0; j < size; j++)
		{
			temp = 'a' + rand() % 26;
			fout << temp;
		}
	}
	fout << "\0";
	fout.close();
	return 0;
}
