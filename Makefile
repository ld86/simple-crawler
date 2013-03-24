CC = g++
CXX = g++
CXXFLAGS = -std=c++11
LDFLAGS = -pthread -lcurl -lboost_regex

main: main.o

clean:
	rm *.o main
