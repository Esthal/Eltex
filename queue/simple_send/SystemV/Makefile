objClient = client.o
objServer = server.o
objCon = connect_to_queue.o

srcClient = client.c
srcServer = server.c
srcCon = connect_to_queue.c

header = queue.h

binClient = client
binServer = server

.PHONY: clean

edit: $(objClient) $(objServer) $(objCon)
	@gcc -o $(binClient) $(objClient) $(objCon) $(header)
	@gcc -o $(binServer) $(objServer) $(objCon) $(header)

$(objClient): $(srcClient)
	@gcc -c $(srcClient)

$(objServer): $(srcServer)
	@gcc -c $(srcServer)

$(objCon): $(srcCon)
	@gcc -c $(srcCon)

clean:
	@rm $(binClient) $(binServer) $(objClient) $(objServer) $(objCon) queue