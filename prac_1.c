#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

// Practical 1 Part a.

void prac_a(){
    printf("Before Fork !! \n");

    int process_id = fork();

    if (process_id < 0){
        perror("fork failed \n");
    }

    printf("The Process ID is : %d \n", getpid());
}

// Practical 1 Part b.
void prac_b(){
    printf("Prac 1 part b \n");
    int new_proc_id = fork();

    if(new_proc_id < 0){
        perror("fork failed \n");
    }

    if (new_proc_id == 0){
        printf("The Process Id of Child : %d \n",getpid());
    }

    else {
        printf("The Process Id of Parent : %d \n",getpid());
    }

}
// Practical 1 Part c.

void prac_c(){
    printf("Prac 1 part c \n");

    int new_pid = fork();
    
    if(new_pid < 0){
        perror("fork failed \n");
    }

    if(new_pid == 0 ){
        printf("The Process Id of Child started : %d \n", getpid());
        sleep(3);
        printf("The Process Id of Child finshed : %d \n", getpid());

    }
    else{
        printf("The Process Id of Parent started : %d \n", getpid());
        wait(NULL);
        printf("The Process Id of Parent finshed : %d \n", getpid());
    }
}



int main(){
    prac_a();
    prac_b();
    prac_c();
    return 0;

}

/*
Output :
Before Fork !! 
The Process ID is : 6988 
Prac 1 part b 
The Process ID is : 6989 
Prac 1 part b 
The Process Id of Parent : 6988 
Prac 1 part c 
The Process Id of Child : 6990 
Prac 1 part c 
The Process Id of Parent started : 6988 
The Process Id of Parent : 6989 
Prac 1 part c 
The Process Id of Child started : 6991 
The Process Id of Child : 6992 
Prac 1 part c 
The Process Id of Parent started : 6990 
The Process Id of Parent started : 6989 
The Process Id of Child started : 6993 
The Process Id of Parent started : 6992 
The Process Id of Child started : 6994 
The Process Id of Child started : 6995 
The Process Id of Child finshed : 6991 
The Process Id of Child finshed : 6995 
The Process Id of Child finshed : 6993 
The Process Id of Child finshed : 6994 
The Process Id of Parent finshed : 6988 
The Process Id of Parent finshed : 6992 
The Process Id of Parent finshed : 6989 
The Process Id of Parent finshed : 6990 
*/