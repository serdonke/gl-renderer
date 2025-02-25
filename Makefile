CC = gcc
CFLAGS = -Wall -Wextra -pedantic -MMD -MP -std=c11
LDFLAGS = -lm 
GLFW_DIR = external/glfw
GLFW_BUILD = $(GLFW_DIR)/build
BUILD_DIR = build

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)

all: main

$(GLFW_BUILD)/src/libglfw3.a: | $(GLFW_DIR)
	mkdir -p $(GLFW_BUILD)
	cd $(GLFW_BUILD) && cmake .. -DBUILD_SHARED_LIBS=OFF
	cmake --build $(GLFW_BUILD)

$(GLFW_DIR):
	@echo "Fetching GLFW..."
	git clone --depth=1 https://github.com/glfw/glfw.git $(GLFW_DIR)
	rm -rf $(GLFW_DIR)/.git

main: $(OBJ) $(GLFW_BUILD)/src/libglfw3.a
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJ) -I$(GLFW_DIR)/include -L$(GLFW_BUILD)/src -lglfw3 $(LDFLAGS) -o $(BUILD_DIR)/main

-include $(DEP)

%.o: %.c $(GLFW_BUILD)/src/libglfw3.a
	$(CC) $(CFLAGS) -Iinclude -I$(GLFW_DIR)/include -c $< -o $@

run: main
	cd src && ../build/main

clean:
	rm -f $(OBJ) $(DEP) main
	rm -rf $(GLFW_BUILD)
