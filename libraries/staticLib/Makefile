dir := libfiles
lib_name := calc
bin := calc

source := main.c
header := calc.h

src_list := calcD.c calcM.c calcMul.c calcP.c
objs := calcD.o calcM.o calcMul.o calcP.o
srcs := $(addprefix $(dir)/,$(src_list))


edit: $(srcs)
	@gcc -c $(srcs)
	@ar rc lib$(lib_name).a $(objs)
	@gcc $(source) $(header) -o $(bin) -L. -l$(lib_name)

start:
	@./$(bin)

.PHONY:clean

clean:
	@rm $(bin) $(objs) lib$(lib_name).a