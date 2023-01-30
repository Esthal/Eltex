.PHONY: clean

source := client.c
obj := client.o
bin := client

client_header := client.h

edit: $(obj)
	gcc -o $(bin) $(obj) $(client_header) -lncurses -pthread

	gcc -o server server.c
	

client.o: $(source)
	gcc -c $(source)

clean:
	rm $(bin) server $(obj)

