dirScr := src
dirObj := obj

bin := FileEditor
header := FileEditor.h
scrMain := FileEditor.c
objMain := FileEditor.o

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
