#include<iostream>
#include<functional>

#include"coctx.h"
#include<unistd.h>
using namespace std;

coctx_t ctx[3];

char s[3][40960];

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

class thread_t
{
public:
	coctx_t ctx;
	char s[65536];
	void* _func(void)
	{
		return nullptr;
	}
public:
	thread_t()
	{
		coctx_init(&ctx);
		ctx.ss_sp = s;
		ctx.ss_size = 65536;

		//void* ptr = &_func;
		//coctx_make(&ctx,(void*(*)(void*))(ptr),this);
	}
};


void test_func(int a)
{
}

int main(int argc,char* argv[])
{
	coctx_init(ctx + 0);
	coctx_init(ctx + 1);
	coctx_init(ctx + 2);

	ctx[0].ss_sp = s[0];
	ctx[0].ss_size = 40960;

	ctx[1].ss_sp = s[1];
	ctx[1].ss_size = 40960;

	ctx[2].ss_sp = s[2];
	ctx[2].ss_size = 40960;


	coctx_make(ctx + 0,func_0,0);
	coctx_make(ctx + 1,func_1,0);

	function<void()> temp;

	temp = bind(&test_func,3);

	int i=0;
	while(1)
	{
		sleep(1);
		printf("%s: %d\n",__func__,i++);
		coctx_swap(ctx + 2, ctx + 0);
	}

    return 0;
}

