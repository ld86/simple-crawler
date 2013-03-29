CC = g++
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror -pedantic
LDFLAGS = -pthread -lcurl -lboost_regex

main: parse_worker.o queue.o save_worker.o page.o curl_helper.o download_worker.o url_queue.o url.o crawler.o runner.o parameters.o runner.o main.o

clean:
	rm -f *.o main
