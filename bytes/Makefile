obj = byte.o
bin = byte
source = byte.c


edit: $(obj)
	@gcc -o $(bin) $(obj)

$(obj): $(source)
	@gcc -c $(source)

clean:
	rm $(bin) $(obj)