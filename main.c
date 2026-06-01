#include<stdio.h>
#include<unistd.h>

#include"coctx.h"

void func_0(void)
{
	int i=0;
	while(1)
	{
		printf("%s: %d\n",__func__,i++);
		coctx_swap(0, 1);
	}
}

void func_1(void)
{
	int i=0;
	while(1)
	{
		printf("%s: %d\n",__func__,i++);
		coctx_swap(1, 2);
	}
}

int main(int argc,char* argv[])
{
	coctx_make(0, func_0);
	coctx_make(1, func_1);
	coctx_make(2, NULL  );

	int i=0;
	while(1)
	{
		//sleep(1);
		printf("%s: %d\n",__func__,i++);
		coctx_swap(2, 0);
	}

	return 0;
}
