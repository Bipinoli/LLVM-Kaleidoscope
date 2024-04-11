CC = clang++
CFLAGS = -std=c++11 -Wall
INC = 

BUILD_DIR = ./build
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))

all: $(BUILD_DIR) main

main: $(OBJS)
	$(CC) -o $(BUILD_DIR)/main $^

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(INC) -o $@ $< $(CFLAGS)

$(BUILD_DIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
