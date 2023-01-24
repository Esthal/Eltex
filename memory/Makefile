dirScr := src
dirObj := obj

bin := phone_book
header := phone_book.h
scrMain := phone_book.c
objMain := phone_book.o

source := $(wildcard $(dirScr)/*.c)
source := $(source) $(scrMain)
obj := $(patsubst $(dirScr)/%.c, %.o, $(source))


source := $(wildcard $(dirScr)/*.c) $(scrMain)
obj := $(patsubst $(dirScr)/%.c, %.o, $(source))
objs = $(wildcard $(dirObj)/*.o)

.PHONY: clean

edit: $(obj)
	gcc -c $(scrMain)
	gcc -o $(bin) $(header) $(objs) $(objMain) -lncurses	
	

%.o: $(dirScr)/%.c
	gcc -c $<
	mv $@ $(dirObj)/$@

clean:
	rm $(bin) obj/* $(objMain)