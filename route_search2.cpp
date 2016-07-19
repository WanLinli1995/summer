#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include<unistd.h>
#include <iostream>
#include <string.h>
using namespace std;

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
    cout<<"filename_size="<<all_name[num].size()<<endl;
    cout<<"suffix_pos="<<suffix_pos<<endl;
    cout<<"filename:"<<ptr->d_name<<endl<<endl;
    }

//    cout<<"last/="<<all_name[num].find("//")<<endl;
//    cout<<"size()="<<all_name[num].size()<<endl;
//    int s = all_name[num].size();
//    cout<<"the last charactor:"<<all_name[num][s-1]<<endl;
    else
    {
      cout<<"this is a direction, not a file"<<endl;
      cout<<"new_route="<<route_name+"/"+all_name[num]<<endl;
      search_filename(route_name+"/"+all_name[num], file_type);
//      cout<<"filename:"<<"/"+all_name[num]<<endl<<endl;
    }
/*
    else if(all_name[num].find(".")!=string::npos)
    {
    suffix_pos = all_name[num].find_last_of(".");
    cout<<"filename_size="<<all_name[num].size()<<endl;
    cout<<"suffix_pos="<<suffix_pos<<endl;
    cout<<"filename:"<<ptr->d_name<<endl<<endl;
    }
*/
    num++;
 //   cout<<"filename:"<<ptr->d_name<<endl<<endl;
  }
  closedir(pDir);
//  return 0;
}





int main()
{
  string route_name;
  string file_type;
  cout<<"Please input the route:";
  cin>>route_name;
  cout<<"Please input the file type you want:(.txt/.cpp and so on):";
  cin>>file_type;
  search_filename(route_name, file_type);
  return 0;
}
