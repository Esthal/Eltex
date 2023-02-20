SRC_FILES := $(wildcard *.c)
BIN_FILES := $(patsubst %.c,%,$(SRC_FILES))

.PHONY: edit clean

edit: $(BIN_FILES)

$(BIN_FILES): %: %.c
	gcc $< -o $@ -lpthread

clean:
	rm $(BIN_FILES)