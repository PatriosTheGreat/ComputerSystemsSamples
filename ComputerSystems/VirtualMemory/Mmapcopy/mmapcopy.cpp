#include <unistd.h>
#include <sys/mman.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

long FdGetFileSize(int fd)
{
    struct stat stat_buf;
    int rc = fstat(fd, &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

int main() {
    std::string file_name;

    std::cout << "Write file name: " ;
    std::cin >> file_name;

    FILE * fp;
    fp = fopen(file_name.c_str(), "r");

    int fd = fileno(fp);
    long size = FdGetFileSize(fd);
    void* file_data = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    std::cout << (char*)file_data << std::endl;
    munmap(file_data, size);
}