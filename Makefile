all:
	gcc -c coctx_swap.S
	gcc -c coctx.c
	gcc -c main.c
	gcc *.o -z noexecstack
clean:
	rm -rf *.o a.out
