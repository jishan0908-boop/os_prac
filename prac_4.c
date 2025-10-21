#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void file_detail(const char *filename)
{
    struct stat filestat;

    if (stat(filename, &filestat) < 0) {
        perror("stat");
        return;
    }
    printf("=============================================\n");
    printf("File: %s\n", filename);
    
    printf("Type: ");
    if (S_ISREG(filestat.st_mode))  printf("Regular file\n");
    else if (S_ISDIR(filestat.st_mode)) printf("Directory\n");
    else if (S_ISLNK(filestat.st_mode)) printf("Symbolic link\n");
    else if (S_ISCHR(filestat.st_mode)) printf("Character device\n");
    else if (S_ISBLK(filestat.st_mode)) printf("Block device\n");
    else if (S_ISFIFO(filestat.st_mode)) printf("FIFO/pipe\n");
    else if (S_ISSOCK(filestat.st_mode)) printf("Socket\n");
    else printf("Unknown\n");


    printf("Permissions: ");
    printf((filestat.st_mode & S_IRUSR) ? "r" : "-");
    printf((filestat.st_mode & S_IWUSR) ? "w" : "-");
    printf((filestat.st_mode & S_IXUSR) ? "x" : "-");
    printf((filestat.st_mode & S_IRGRP) ? "r" : "-");
    printf((filestat.st_mode & S_IWGRP) ? "w" : "-");
    printf((filestat.st_mode & S_IXGRP) ? "x" : "-");
    printf((filestat.st_mode & S_IROTH) ? "r" : "-");
    printf((filestat.st_mode & S_IWOTH) ? "w" : "-");
    printf((filestat.st_mode & S_IXOTH) ? "x\n" : "-\n");

    struct passwd *pw = getpwuid(filestat.st_uid);
    struct group  *gr = getgrgid(filestat.st_gid);

    printf("Owner: %s\n", pw ? pw->pw_name : "Unknown");
    printf("Group: %s\n", gr ? gr->gr_name : "Unknown");


    printf("Size: %ld bytes\n", filestat.st_size);

    printf("Last Access: %s", ctime(&filestat.st_atime));
    printf("Last Modification: %s", ctime(&filestat.st_mtime));
    printf("Last Status Change: %s", ctime(&filestat.st_ctime));

    printf("=============================================\n");

}
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    file_detail(argv[1]);
    return 0;
}



/*
Output :
=============================================
File: my_text.txt
Type: Regular file
Permissions: rw-rw-r--
Owner: jishan
Group: jishan
Size: 1537 bytes
Last Access: Tue Oct 21 16:34:20 2025
Last Modification: Tue Oct 21 16:34:21 2025
Last Status Change: Tue Oct 21 16:34:21 2025
=============================================

*/