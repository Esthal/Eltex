obj = main.o
bin = main
source = main.c

edit: $(obj)
	@gcc -o $(bin) $(obj)

$(obj): $(source)
	@gcc -c $(source)

clean:
	rm $(bin) $(obj)