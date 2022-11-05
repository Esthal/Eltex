obj = array.o
bin = array
source = array.c

edit: $(obj)
	@gcc -o $(bin) $(obj)

$(obj): $(source)
	@gcc -c $(source)

clean:
	rm $(bin) $(obj)