bin = main
src = main.c
obj = main.o


edit: $(obj)
	@gcc -o $(bin) $(obj) -pthread

$(obj):
	@gcc -c $(src)

clean:
	rm $(bin) $(obj)
