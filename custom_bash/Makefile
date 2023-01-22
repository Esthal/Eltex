bin = main
header = bash.h
source = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(source))

.PHONY:clean

edit: $(obj)
	@gcc -o $(bin) $(header) $(obj)

%.o: %.c
	@gcc -c $<

clean:
	@rm $(bin) $(obj)