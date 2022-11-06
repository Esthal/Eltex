obj = phone_book.o
bin = phone_book
source = phone_book.c

.PHONY: clean

edit: $(obj)
	@gcc -o $(bin) $(obj)

$(obj): $(source)
	@gcc -c $(source)

clean:
	rm $(bin) $(obj)