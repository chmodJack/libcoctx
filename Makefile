all:
	gcc -c coctx_swap.S
	gcc -c coctx.c
	gcc -c main.c
	gcc *.o
clean:
	rm -rf *.o a.out
