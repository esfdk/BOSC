#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	int c;
	FILE *fp;
	fp = fopen(argv[1],"r");
	c = getc(fp);
	while (c != EOF) {
		putchar(c);
		c = getc(fp);
	}
	exit(0);
}