all:
	gcc -c coctx_swap.S
	gcc -c coctx.cpp
	gcc -c main.cpp
	gcc *.o -z noexecstack -lstdc++
clean:
	rm -rf *.o a.out
