#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main(void){
	char *x;
	char y;
	x = (char*) malloc( 10*sizeof(char) );
	
	char buf[1024];
	sprintf(buf, "cat /proc/%d/smaps", getpid() );
	system(buf);
		
	printf("%p\n", x );
	for (int i=131*1024; i<=200000; i++ ){
		printf( "%d\n", i );
		y = x[i];
	}
	
	free(x);
}

