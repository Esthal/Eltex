obj = pointer.o
bin = pointer
source = pointer.c

edit: $(obj)
	@gcc -o $(bin) $(obj)

$(obj): $(source)
	@gcc -c $(source)

clean:
	rm $(bin) $(obj)