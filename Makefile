CC:=gcc

SRC_DIR:=src
SRC:=$(wildcard $(SRC_DIR)/*.c)

.PHONY: debug clean

INCL:=-Isrc -Imosaic/src

GLFW_LINK=$(shell pkg-config --libs --static glfw3)
GLEW_LINK=$(shell pkg-config --libs --static glew)

DEBUG_DIR:=debug
DEBUG_CFLAGS:=-Wall -g -O0 -fsanitize=address -s
DEBUG_OBJ:=$(SRC:$(SRC_DIR)/%.c=$(DEBUG_DIR)/obj/%.o)
DEBUG_LINK_DIRS:=-Ldebug -Lmosaic/debug
DEBUG_LINK:=-lasan $(GLFW_LINK) $(GLEW_LINK) -lmosaic

test: $(SRC_DIR)/test/test.c debug
	$(CC) $(INCL) -o test $< $(DEBUG_LINK_DIRS) -lglue $(DEBUG_LINK)

$(DEBUG_OBJ): $(DEBUG_DIR)/obj/%.o : $(SRC_DIR)/%.c
	$(CC) $(DEBUG_CFLAGS) $(INCL) -c $< -o $@
	@echo "Built debug objs"

debug: $(DEBUG_OBJ)
	ar rcs $(DEBUG_DIR)/libglue.a $(DEBUG_OBJ)


clean:
	--	rm ${DEBUG_OBJ}
