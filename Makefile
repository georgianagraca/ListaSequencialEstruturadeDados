CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: list_test

list_test: lista_sequencial.c
	$(CC) $(CFLAGS) -o list_test lista_sequencial.c  
clean:
	rm -f list_test  