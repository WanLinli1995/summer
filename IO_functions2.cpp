#include <stdio.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <assert.h>
#include <sys/io.h>
using namespace std;
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
    cout<<"Read from file:"<<str[i]<<endl;
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

/*
void getFiles(string path, vector<string>& files )   

{   
  long hFile = 0;   
  //document imformation   
  struct _finddata_t fileinfo;   
  string p;   

  //搜索与指定的文件名称匹配的第一个实例,若成功则返回第一个实例的句柄,否则返回-1    
  if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)   
  {   
    do  //循环整个文件夹搜索    
    {   
        //如果是目录,迭代之   
        //如果是文件,加入列表   
      if((fileinfo.attrib &  _A_SUBDIR))  //目录    
      {   
        if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)   
          getFiles( p.assign(path).append("\\").append(fileinfo.name), files );
//迭调用自身迭代搜索找到的目录   
      }  
      else   //文件   
      {  
      //files.push_back(p.assign(path).append("\\").append(fileinfo.name) );   
        files.push_back(fileinfo.name);   
      }   
    }while(_findnext(hFile, &fileinfo)== 0); // 查找下一个    

    //释放由FindFirst分配的内存   

    _findclose(hFile);   
    }   

}  

*/

/***************************************************************
 2 函数名称：FindFile
 3 查找指定目录下指定文件
 4 输入：fileName：指定文件名，fileNath：指定查找路径
 5 输出：打印文件路径
 6 ***************************************************************/
/*
 int FindFile(string fileName, string filePath)
 {
     assert(fileName != "" && filePath != "");
     string exeName = fileName.substr(fileName.find_last_of('.'));
     string strPath = filePath;
     string filiterName = "*.*";
     if ( strPath[strPath.length() - 1] != '\\')
     {
         strPath = strPath + "\\";
     }
     struct _finddata_t fileInfo;
     long handle = _findfirst((strPath + filiterName).c_str(), &fileInfo);
     if (handle == -1L)
     {
         cout<<"Cannot Open The Path!"<<endl;
         return 0;
     }
     do
     {
         string path = fileInfo.name;
         if (fileInfo.attrib & _A_SUBDIR)
         {
             if (strcmp(fileInfo.name, ".") != 0 && strcmp(fileInfo.name, "..") != 0)
             {
                 FindFile(fileName, strPath + path + "\\");
             }
         }
         else if (fileInfo.attrib & _A_ARCH && path.substr(path.find_last_of('.')) == exeName)
         {
             cout<<strPath + fileInfo.name<<endl;
         }
     }while (_findnext(handle, &fileInfo) == 0);
     _findclose(handle);
     return 0;
 }
*/





int main(void)
{
  const int Write_line_num = 5;
  string fname_in = "in.txt";
  string fname_out = "out.txt";
  string str_in[Lenth];
  string str_out;
//  ReadWBW(str_in, fname_in);
//  ReadLBL(str_in, fname_in);
//  WriteLBL(str_in, fname_out, Write_line_num);
//  WriteOT(str_in[2], fname_out);
  ReadAndWrite(fname_in, fname_out, 10);
//  vector<string>& files;
//  getFiles("/home/home3/linliwan/benchmark", files )
  int res = FindFile("in.txt", "/home/home3/linliwan/benchmark");
  return 0;
}
