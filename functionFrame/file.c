 #include <stdio.h>
 #include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#define N 28


 int main()
 {
    char input[N] = {0x74,0x65,0x73,0x74,0x74,0x65,0x73,0x74,0x74,0x65,0x73,0x74,
                    0x30,0xdf,0xff,0xff,0xff,0x7f, 0x00, 0x00,
                    0xd2,0x11,0x40,0x00,0x00,0x00, 0x00, 0x00};
    int fd = open("input.hex", O_CREAT | O_RDWR, 0666);
    printf("%s", input);
    write(fd, input, N);
	close(fd);
 }
