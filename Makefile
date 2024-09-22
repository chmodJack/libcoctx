TARGET:=libcoctx
CROSS:=
CC:=$(CROSS)gcc
ECHO:=@

SSRC+=$(shell find . -name '*.S')
CSRC+=$(shell find . -name '*.c')
CPPSRC+=$(shell find . -name '*.cpp')
OBJS+=$(SSRC:%.S=%.o)
OBJS+=$(CSRC:%.c=%.o)
OBJS+=$(CPPSRC:%.cpp=%.o)

ALLPATHS:=$(shell ls -R | grep :)
CFLAGS+=$(ALLPATHS:%:=-I%)
CFLAGS+=-I.
CFLAGS+=-DDEBUG=1
CFLAGS+=-c -O0 -ggdb -fPIC

CSFLAGS+=$(CFLAGS)
CCFLAGS+=$(CFLAGS) -std=c2x
CCPPFLAGS+=$(CFLAGS) -std=c++23

LDFLAGS+=$(ALLPATHS:%:=-L%)
LDFLAGS+=-O0 -ggdb
LDFLAGS+=-L. -fPIC -shared
LDFLAGS+=-lpthread -lstdc++ -lm -lc
STATIC_LIBS+=

.PHONY:all clean
$(TARGET).so:$(OBJS) $(STATIC_LIBS)
	@echo -e '[33m[LD] [32m$@[0m'
	$(ECHO)$(CC) -o $@ $^ $(LDFLAGS)
%.o:%.S
	@echo -e '[33m[CC] [32m$@[0m'
	$(ECHO)$(CC) -o $@ $^ $(CSFLAGS)
%.o:%.c
	@echo -e '[33m[CC] [32m$@[0m'
	$(ECHO)$(CC) -o $@ $^ $(CCFLAGS)
%.o:%.cpp
	@echo -e '[33m[CC] [32m$@[0m'
	$(ECHO)$(CC) -o $@ $^ $(CCPPFLAGS)
clean:
	@echo -e '[33m[RM] [32m$(TARGET).elf $(OBJS)[0m'
	$(ECHO)rm -rf $(TARGET).so $(OBJS) tests
test:
	gcc main.cpp -O0 -ggdb -o tests -L. -Wl,-rpath=$(PWD) -lcoctx -lstdc++
	./tests
