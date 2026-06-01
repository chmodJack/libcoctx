CROSS=

all:
	$(CROSS)gcc -c coctx.c
	$(CROSS)gcc -c main.c
	$(CROSS)gcc *.o
clean:
	rm -rf *.o a.out
