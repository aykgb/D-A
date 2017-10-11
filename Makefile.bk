INC_DIR=-I/usr/local/include
LIB_DIR=-L/usr/local/lib
LIB=-lboost_regex -lboost_thread -lboost_system

CC=g++ --std=c++11 -g
CFLAGS=-Wall
EXE=big_number

all:
	$(CC) $(CFLAGS) $(EXE).cpp -o $(EXE) $(INC_DIR) $(LIB_DIR) $(LIB)

clean:
	rm -rf *.o $(EXE)
