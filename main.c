#include<stdio.h>
#include<unistd.h>

#include"coctx.h"

struct coctx_t ctx[3];

unsigned char s[3][40960];

void* func_0(void* arg)
{
	int i=0;
	while(1)
	{
		sleep(1);
		printf("%s: %d\n",__func__,i++);
		coctx_swap(ctx + 0, ctx + 1);
	}
}

void* func_1(void* arg)
{
	int i=0;
	while(1)
	{
		sleep(1);
		printf("%s: %d\n",__func__,i++);
		coctx_swap(ctx + 1, ctx + 2);
	}
}

int main(int argc,char* argv[])
{
	ctx[0].sp = s[0];
	ctx[0].size = 40960;

	ctx[1].sp = s[1];
	ctx[1].size = 40960;

	ctx[2].sp = s[2];
	ctx[2].size = 40960;

	coctx_make(ctx + 0,func_0,0);
	coctx_make(ctx + 1,func_1,0);

	int i=0;
	while(1)
	{
		sleep(1);
		printf("%s: %d\n",__func__,i++);
		coctx_swap(ctx + 2, ctx + 0);
	}

    return 0;
}

