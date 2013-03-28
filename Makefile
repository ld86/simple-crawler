CC = g++
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror -pedantic
LDFLAGS = -pthread -lcurl -lboost_regex

main: save_worker.o page.o curl_helper.o worker.o url_queue.o url.o crawler.o runner.o parameters.o runner.o main.o

clean:
	rm *.o main
