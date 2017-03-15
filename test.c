#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

#define MAXSZ (10*1000*1000)
#define DEFAULT (10)

static int s_len = DEFAULT;

void random_array(int array[], int len)
{
	srand(time(NULL));
	for(;len>0;len--)
		array[len-1] = rand()%MAXSZ;
}

void print_array(int array[], int len)
{
	if(getenv("P")==NULL) return;

	struct winsize wsz;
	if(ioctl(stdout,SIOCGWINSZ,&wsz,sizeof(wsz))<0)
		perror("ioctl error"),return;

	for(int i=0;i<len;i++)
	{
		printf("%9d",array[i]);
		if((i+1)%(wsz.ws_col/9) == 0)
			printf("\n");
	}
	printf("\n");
}

int main(int argc, char** argv)
{
	int array[MAXSZ];
	if(argc==2)
		s_len = atoi(argv[1]);
	if(s_len<1 || s_len>MAXSZ)
		printf("length scope is 0 ~ %d.\n",MAXSZ),exit(1);
	int len = s_len;
	
	int temp[len];
	random_array(array, len);
	print_array(array, len);
	return 0;
}

