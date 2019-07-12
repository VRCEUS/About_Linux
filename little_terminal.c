#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <error.h>
char command[256]; 

char * exec_str[20];

void main() 
{ 
  int rtn; /*子进程的返回数值*/ 

  while(1) 
  { 
    printf( ">" );              //从终端读取要执行的命令 
    fgets(command, 256, stdin); //将命令数据存放到command中

    command[strlen(command)-1] = 0; 


	  char *p;
	  char *buff;
	  buff=command;
	  p = strtok(buff, " ");
	  int i=0;

	  while(p!=NULL)
	  {
      //exec_str中分别存放各个命令及其参数，以空格进行切割
	    exec_str[i] = p;
	    //printf(exec_str[i]);
	    //printf("\n");

	    i++;
	    p = strtok(NULL, " ");
	  }
	    //printf(exec_str[0]); 


    if (fork() == 0 )         //在创建的子进程中执行这个命令
    {  
      //执行命令
      execvp(command,exec_str); 
      //如果exec函数返回，表明没有正常执行命令，打印错误信息
      perror(command); 
      exit(1); 
    } 
    else  
    { 
      //在父进程中等待字进程结束，并且打印子进程的返回值
      wait( &rtn ); 
      printf("子进程返回%d\n",rtn); 
	//exec_str=NULL;
  //清空exec_str
	memset(exec_str,0,sizeof(exec_str));
      //exit(0);
    } 
  } 
  //exit(0);
}
