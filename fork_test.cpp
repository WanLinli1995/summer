#include <cstdio>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/wait.h>
 
int main(){
	pid_t executive = fork();
	if( executive < 0 )
	{
		printf("fork failed\n");
		return 0;
	}
	else if( executive == 0 )
	{
	//child process
	//	execl("/home/home3/linliwan/benchmark/summer/result", "./result", "2", "1", "128KB", "0ms", "large.txt", "in.txt", NULL);
		execl("/home/home3/linliwan/benchmark/summer/result", "./result", "2", "1", "200MB", "0ms", "input1.txt", "input2.txt", NULL);
	}
	else
	{
		struct rusage rused;
		int status = 0;
		if( wait4( executive, &status, 0, &rused  ) < 0 )
		{
			printf("wait4 failed\n");
			return 0;
        	}	
 
		if( WIFEXITED(status) )
		{	
			int time_usage = (rused.ru_utime.tv_sec * 1000 + rused.ru_utime.tv_usec / 1000);
			time_usage += ( rused.ru_stime.tv_sec * 1000 + rused.ru_stime.tv_usec / 1000 );
//			int memory_usage = rused.ru_minflt * ( getpagesize() / 1024 );
			int memory_usage = rused.ru_maxrss;
	/*i		if(memory_usage < 1024)*/ printf("CPU Time used: %d ms Memory used: %d KB \n", time_usage, memory_usage);
		//	else printf("Time used: %d ms Memory used: %d MB \n", time_usage, memory_usage / 1);
 
		}
	}
	return 0;
}
