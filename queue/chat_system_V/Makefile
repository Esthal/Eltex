.PHONY: clean

dirScr := src
dirObj := obj

queue_file := queue

source_client := client.c
obj_client := client.o
bin_client := client

source_server := server.c
obj_server := server.o
bin_server := server

client_header := client.h
server_header := server.h


client_source = $(wildcard $(dirScr)/*.c)
client_obj = $(patsubst $(dirScr)/%.c, %.o, $(client_source))
client_objs = $(wildcard $(dirObj)/*.o)

server_obj = delete_user_from_list.o add_in_list.o connect_to_queue.o
server_objs = $(addprefix $(dirObj)/,$(server_obj))

edit: $(obj_client) $(client_obj) $(obj_server)
	gcc -o $(bin_client) $(obj_client) $(client_objs) $(client_header) -lncurses -pthread

	gcc -o $(bin_server) $(obj_server) $(server_objs) $(server_header)
	
$(obj_server): $(source_server)
	gcc -c $(source_server) 


client.o: $(source_client)
	gcc -c $(source_client)



%.o: $(dirScr)/%.c
	gcc -c $<
	@mv $@ $(dirObj)/$@

clean:
	rm $(bin_client) $(bin_server) $(obj_client) $(obj_server) $(client_objs) $(queue_file)
