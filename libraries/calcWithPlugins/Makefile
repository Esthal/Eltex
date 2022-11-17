bin := calc
source := main.c

dir := libfiles
plug := plug

src := $(wildcard $(dir)/*.c)
obj := $(patsubst $(dir)/%.c, %.so, $(src))


edit : $(obj)
	gcc $(source) -o $(bin) -ldl 


%.so: $(dir)/%.c
	gcc -shared -fPIC $< -o $@
	mv $@ $(plug)/$@

start:
	@LD_LIBRARY_PATH=$(PWD):LD_LIBRARY_PATH ./$(bin)


.PHONY:clean

clean:
	rm $(plug)/*.so $(bin)