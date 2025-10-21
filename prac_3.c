#include <stdio.h>
#include <sys/sysinfo.h>

void prac() {
    struct sysinfo sys_info;

    // Fill the sys_info struct
    if (sysinfo(&sys_info) != 0) {
        perror("sysinfo");
        return;
    }

    printf("===========================================\n");
    printf("Total Ram: %lu MB\n", sys_info.totalram / 1024 / 1024);
    printf("Total Free Ram: %lu MB\n", sys_info.freeram / 1024 / 1024);
    printf("Total shared Ram: %lu MB \n", sys_info.sharedram /1024 / 1024);
    printf("Total High Memory : %lu MB \n", sys_info.totalhigh / 1024 /1024);
    printf("===========================================\n");
}

int main() {
    prac();
    return 0;
}

/*
Output :
===========================================
Total Ram: 15665 MB
Total Free Ram: 5119 MB
Total shared Ram: 1335 MB 
Total High Memory : 0 MB 
===========================================
*/