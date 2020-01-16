CC=clang
CCX=clang++

LIBS=glfw3

OPTS=-I$(shell pwd)/thirdparty/include/ -I$(shell pwd)/thirdparty/

CFLAGS=$(shell pkg-config --cflags $(LIBS)) -g $(OPTS)
CXXFLAGS=$(CFLAGS)
LDFLAGS=$(shell pkg-config --libs $(LIBS)) -g $(OPTS) -framework Cocoa -framework IOKit -framework CoreFoundation -lstdc++
OBJS=./thirdparty/glad/glad.o image.o tex.o


.SILENT:

all: main.o $(OBJS)
	$(CC) $(LDFLAGS) -o main $^ 

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.o
	rm -rf ./main