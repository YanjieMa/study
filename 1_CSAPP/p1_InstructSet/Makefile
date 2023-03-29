CC=gcc
CFLAGS = -Wall -g -O2 -std=gnu99 -Werror -c
SOURCE = $(wildcard ./src/common/*.c)
SOURCE += $(wildcard ./src/hardware/cpu/*.c)
SOURCE += $(wildcard ./src/hardware/memory/*.c)
SOURCE += $(wildcard ./src/tests/*.c)

OBJ=$(patsubst %.c, %.o, $(SOURCE))

INCLUDES = -I /home/git/myStudyRespository/OS/CSAPP/c2_MachineLevelProgram/src/headers

TARGET=main

$(TARGET):$(OBJ)
	@mkdir -p build
	$(CC) $(OBJ) -o build/$(TARGET)
%.o:%.c
	$(CC) $(INCLUDES) $(CFLAGS) $< -o $@

.PHONY: run
run:
	./build/$(TARGET)

.PHONY: clean
clean:
	rm -rf $(OBJ) build/