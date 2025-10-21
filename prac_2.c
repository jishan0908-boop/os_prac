#include<stdio.h>
#include<stdlib.h>
#include<sys/utsname.h>

// Practical 2 
void prac(){

    struct utsname sys_info;

    if(uname(&sys_info)  == -1){
        perror("Initalization of system info is null. \n");
    }

    printf("=============================================\n");
    printf("The System  : %s \n",sys_info.sysname);
    printf("The Version : %s \n",sys_info.version);
    printf("The Release : %s \n ", sys_info.release);
    printf("The Machine  : %s \n",sys_info.machine);
    printf("The NodeName : %s \n",sys_info.nodename);
    printf("=============================================\n");    
}


int main(){
    prac();
    return 0;
}

/*
Output:
=============================================
The System  : Linux 
The Version : #85~22.04.1-Ubuntu SMP PREEMPT_DYNAMIC Fri Sep 19 16:18:59 UTC 2 
The Release : 6.8.0-85-generic 
 The Machine  : x86_64 
The NodeName : jishan-HP-Laptop 
=============================================
*/