.PHONY: clean

dirScr := src
dirObj := obj


scrMain := $(wildcard *.c)
header := $(patsubst %.c, %.h, $(scrMain))
objMain := $(patsubst %.c, %.o, $(scrMain))
bin := $(patsubst %.c, %, $(scrMain))

source := $(wildcard $(dirScr)/*.c) $(scrMain)
obj := $(patsubst $(dirScr)/%.c, %.o, $(source))
objs = $(wildcard $(dirObj)/*.o)


edit: $(obj)
	gcc -c $(scrMain)
	gcc -o $(bin) $(header) $(objs) $(objMain) -lncurses	
	

%.o: $(dirScr)/%.c
	gcc -c $<
	mv $@ $(dirObj)/$@

clean:
	rm $(bin) obj/* $(objMain)