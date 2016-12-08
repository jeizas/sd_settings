#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int main() {
	int a = 100000, b=999999;
	//[a,b] rnadom integer
	srand(time(0));
	int x = (rand() % (b-a+1))+ a;
	printf("%d\n", x);
	return 0;
}
