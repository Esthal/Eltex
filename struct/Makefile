obj = phone_book.o struct_packed.o

edit: $(obj)
	@gcc -o phone_book phone_book.o
	@gcc -o struct_packed struct_packed.o

phone_book.o:
	@gcc -c phone_book.c

struct_packed.o:
	@gcc -c struct_packed.c

clean:
	rm phone_book struct_packed $(obj)