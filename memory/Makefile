dirScr := scr
dirObj := obj

bin := phone_book
header := phone_book.h
scrMain := phone_book.c
objMain := phone_book.o

source := $(wildcard $(dirScr)/*.c)
source := $(source) phone_book.c
obj := $(patsubst $(dirScr)/%.c, %.o, $(source))



.PHONY: clean

edit: $(obj)
	gcc -c $(scrMain)
	mv $(objMain) $(dirObj)/$(objMain)
	gcc -o $(bin) $(header) $(wildcard $(dirObj)/*.o)
	
%.o: $(dirScr)/%.c
	gcc -c $<
	mv $@ $(dirObj)/$@

clean:
	rm $(bin) obj/*