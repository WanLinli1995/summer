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


using namespace std;

int parseLine(char* line){//Convert the string "** Kb" to an number
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    cout<<"line_length0="<<i<<endl;
    const char* p = line;
    cout<<"p="<<*p<<" ";
    while (*p <'0' || *p > '9') p++;
    line[i-2] = '\0';
    cout<<"line2="<<line<<endl;
    cout<<"line_length1="<<i<<endl;
    i = atoi(p);
    return i;
}


//input the route and output all the files in the route(including its sub-route)
void search_filename(string route_name, string file_type)
{
  DIR* pDir = opendir(route_name.c_str());
  if (opendir(route_name.c_str())==NULL)return;
  struct dirent* ptr;
  int num = 0;
  string all_name[100];
  string des_type_name[100];
  size_t suffix_pos;

  while((ptr = readdir(pDir))!=0)
  {
    all_name[num] = ptr->d_name;

    if(all_name[num].find(".")!=string::npos)
    {
    suffix_pos = all_name[num].find_last_of(".");
 //   cout<<"filename_size="<<all_name[num].size()<<endl;
 //   cout<<"suffix_pos="<<suffix_pos<<endl;
//    cout<<"filename:"<<ptr->d_name<<endl<<endl;
    cout<<ptr->d_name<<endl;
    }

    else
    {
 //     cout<<"this is a direction, not a file"<<endl;
      cout<<endl<<"the following files are in the subroute: "<<route_name+"/"+all_name[num]<<endl;
      search_filename(route_name+"/"+all_name[num], file_type);
   }
    num++;
  }
  closedir(pDir);
//  return 0;
}



//IO finctions
const int Lenth = 6000;
//read from file (word by word)

void ReadWBW(string* str, string fname)
{
  ifstream fin(fname.c_str());
  if(!fin.is_open())
  {
    cout<<"Error opening file";
    exit(1);
  }

  int i = 0;
  while(fin >> str[i])
  {
//    cout<<"Read from file:"<<str[i]<<endl;
    i++;
  }
  fin.close();

}

//read from file(line by line)
void ReadLBL(string* str, string fname)
{
  ifstream fin(fname.c_str());
  if(!fin.is_open())
  {
    cout<<"Error opening file";
    exit(1);
  }

  int i = 0;
  while(getline(fin, str[i]))
  {
    cout<<"Read from file:"<<str[i]<<endl;
    i++;
  }
  fin.close();
}

//Write into file(Line by line)
void WriteLBL(string* str, string fname, int num)
{
  ofstream fout(fname.c_str(), ios::ate | ios::out);
  if(!fout.is_open())
  {
    cout<<"Error opening file";
    exit(1);
  }

  for(int i = 0; i < num; i++)
  {
    fout << str[i]<<"\n";
    cout<<"Write into file:"<<str[i]<<endl;
  }
  fout.close();
}

//Write into file(one time)
void WriteOT(string str, string fname)
{
  ofstream fout(fname.c_str());
  if(!fout.is_open())
  {
    cout<<"Error opening file";
    exit(1);
  }

  fout << str;
  cout<<"Write into file:"<<str<<endl;
  fout.close();
}

//from one file to another file for specific number of lines
void ReadAndWrite(string fname_in, string fname_out, int num_limit)
{
  ifstream fin(fname_in.c_str());
  if(!fin.is_open())
  {
    cout<<"Error opening source file";
    exit(1);
  }
  ofstream fout(fname_out.c_str());
  if(!fout.is_open())
  {
    cout<<"Error opening destinate file";
    exit(1);
  }

  string str;
  int i = 0;
  while(getline(fin, str))
  {
    cout<<"Write from file:"<<fname_in<<"to"<<fname_out<<":"<<str<<endl;
    fout << str <<"\n";
    i++;
    if(i == num_limit)break;
  }
  if(i < num_limit)cout<<"The input line number is larger than the source file, we can only write "<<i<<"lines"<<endl;
  fin.close();
  fout.close();
}






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
  for (size_t i = 0; i < 100000000; ++i) 
  {
    v += v0;//multiple operation to be stable
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
//  sleep(3);//
  time_t end = clock();//
  printf("%s add/sub CPU time: %f [%d]\n", name, double(end-start)*1000 / CLOCKS_PER_SEC, (int)v&1);
  printf("%s add/sub total time: %f [%d]\n", name, mygettime() - t1, (int)v&1);//the last parameter:odd is 1 while even is 0
}


template< typename Type >
void TestMul(const char* name)
{
  Type v  = 0;
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
  time_t end = clock();
  printf("%s mul CPU time: %f [%d]\n", name, double(end-start)*1000 / CLOCKS_PER_SEC, (int)v&1);
  printf("%s mul total time: %f [%d]\n", name, mygettime() - t1, (int)v&1);

}


template< typename Type >
void TestDiv(const char* name)
{
  Type v  = 0;
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
  time_t end = clock();
  printf("%s div CPU time: %f [%d]\n", name, double(end-start)*1000 / CLOCKS_PER_SEC, (int)v&1);
  printf("%s div total time: %f [%d]\n", name, mygettime() - t1, (int)v&1);

}

int main() {
  long long mem_amount;
  long long CPU_time;
  int num_r, num_p, num_f;
  cout<<"Welcome to the emulator!"<<endl;
  cout<<"Please input the memory amount(Kb):"<<endl;
  cin>>memory;
  cout<<"Please input the CPU time expected(ms):"<<endl;
  cin>>CPU_time;
  cout<<"How many file route do you want to access?"<<endl;
  cin>>num_r;
  if(num_r!=0)
  {
    string route_name;
    string file_type;
    for(int i = 0; i < num_r; i++)
    {
      cout<<"input route"<<i<<" name:";
      cin>>route_name;
      cout<<"What kind of files in this route do you want to access?(.txt for example)"<<endl;
      cin>>file_type;
      
    }
  }
//route search section
/*
  time_t start = clock();//
  double t1 = mygettime();//current tiem in seconds
  string route_name;
  string file_type;
  cout<<"Please input the route:";
  cin>>route_name;
  cout<<"Please input the file type you want:(.txt/.cpp and so on):";
  cin>>file_type;
  search_filename(route_name, file_type);
  time_t end = clock();
  printf("route search CPU time: %f\n",  double(end-start)*1000 / CLOCKS_PER_SEC);
  printf("route search total time: %f\n",  mygettime() - t1);
*/


//IO sections
const int Write_line_num = 5;
  string fname_in = "/home/home3/linliwan/benchmark/summer/in.txt";
  string fname_out = "out.txt";
  string str_in[Lenth];
  string str_out;
  ReadWBW(str_in, fname_in);
  cout<<str_in[0]<<endl;
//  ReadLBL(str_in, fname_in);
//  WriteLBL(str_in, fname_out, Write_line_num);
//  WriteOT(str_in[2], fname_out);
//  ReadAndWrite(fname_in, fname_out, 10);
//  vector<string>& files;
//  getFiles("/home/home3/linliwan/benchmark", files )
//  int res = FindFile("in.txt", "/home/home3/linliwan/benchmark");




//arithmatic section
/*
  time_t start = clock();//
  double t1 = mygettime();
  TestAddSub< short >("short");
  time_t end = clock();//
  printf("Add CPU time: %f\n", double(end-start)*1000 / CLOCKS_PER_SEC);
  printf("Add total time: %f\n", mygettime() - t1);

  TestMul< short >("short");
  TestDiv< short >("short");
//  my_test< long >("long");
//  my_test< long long >("long long");
//  my_test< float >("float");
//  my_test< double >("double");
*/
  return 0;
}

