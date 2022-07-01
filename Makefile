NAME=read_log_file
CC=g++ -std=c++20

all: $(NAME).cpp
	$(CC) -o $(NAME) $(NAME).cpp

clean:
	rm -rf $(NAME) $(NAME).o
#g++ -std=c++20 -o read_log_file read_log_file.cpp


