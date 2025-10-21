#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int main(int agrc , char *argv[]){
    int src_file , dest_file;
    ssize_t bytesRead, bytesWritten;
    char buffer[1024];

    src_file = open(argv[1], O_RDONLY);
    if (src_file < 0) {
        perror("Error opening source file");
        exit(1);
    }

    dest_file = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_file < 0) {
        perror("Error opening destination file");
        close(dest_file);
        exit(1);
    }

    while((bytesRead = read(src_file , buffer,1024)) > 0){
        bytesWritten =  write(dest_file , buffer , bytesRead);
            if (bytesWritten != bytesRead) {
            perror("Error writing to destination file");
            close(src_file);
            close(dest_file);
            exit(1);
        }
    }

    close(src_file);
    close(dest_file);

    printf("File copied successfully from '%s' to '%s'\n", argv[1], argv[2]);
    return 0;

}

/*
Output : 
./prac_5 my_text.txt new_text.txt 
File copied successfully from 'my_text.txt' to 'new_text.txt'
*/