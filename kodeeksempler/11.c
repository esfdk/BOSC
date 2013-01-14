#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	const char pathname[] = "newFile.txt";
	char readbuffer[20];
	char writebuffer[] = "1234567890ABCDEFG\n\0";

	int filedesc = open(pathname, O_RDWR);
	
	// If file does not exist, create it
	if(filedesc == -1)
	{
		filedesc = creat(pathname, O_RDWR);
	}
	else // Remove file and create anew
	{
		remove(pathname);
		filedesc = creat(pathname, O_RDWR);
	}
	
	// Read the empty file
	read(filedesc, readbuffer, 20);
	printf("%s \n", readbuffer);

	// Write to file and reaquire file descriptor
	write(filedesc, writebuffer, 20);
	filedesc = open(pathname, O_RDWR);
	
	// Read file with text
	read(filedesc, readbuffer, 20);
	printf("%s", readbuffer);

	return 0;
}
