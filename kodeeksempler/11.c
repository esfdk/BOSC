#include <fcntl.h>

int main(int argc, char *argv[]){
	const char pathname[] = "newFile.txt";
	int filedesc = open(pathname, O_RDWR);
	return 0;
}