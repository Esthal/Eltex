dir := libfiles
lib_name := calc
bin := calc

source := main.c
header := calc.h

src_list := calcD.c calcM.c calcMul.c calcP.c
srcs := $(addprefix $(dir)/,$(src_list))


edit: $(srcs)
	@gcc -shared $(srcs) -o lib$(lib_name).so
	@gcc $(source) $(header) -o $(bin) -L. -l$(lib_name)

start:
	@LD_LIBRARY_PATH=$(PWD):LD_LIBRARY_PATH ./$(bin)

.PHONY:clean

clean:
	@rm $(bin) lib$(lib_name).so