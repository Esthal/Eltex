objClient = client.o
objServer = server.o

srcClient = client.c
srcServer = server.c

header = queue.h

binClient = client
binServer = server

.PHONY: clean

edit: $(objClient) $(objServer)
	@gcc -o $(binClient) $(objClient) $(header) -lrt
	@gcc -o $(binServer) $(objServer) $(header) -lrt

$(objClient): $(srcClient)
	@gcc -c $(srcClient)

$(objServer): $(srcServer)
	@gcc -c $(srcServer)

clean:
	@rm $(binClient) $(binServer) $(objClient) $(objServer)