# compilador
CC := g++
CFLAGS := -fpermissive -lpthread -ltiff

# direcciones
SRC_DIR := src
BUILD_DIR := build

# Compilacion manual 1 a 1
listing%:
	$(eval listing := $(@))
	@if [ "$(listing)" = "listing1.1" ]; then \
		mkdir -p build/Cap1/; \
		g++ -o ./build/Cap1/listing1.1 ./src/Cap1/listing1.1/* ./src/Cap1/listing1.2/* ./src/Cap1/listing1.3/*; \
	elif [ "$(listing)" = "listing1.2" ]; then \
		mkdir -p build/Cap1/; \
		g++ -o ./build/Cap1/listing1.2 ./src/Cap1/listing1.1/* ./src/Cap1/listing1.2/* ./src/Cap1/listing1.3/*; \
	elif [ "$(listing)" = "listing1.3" ]; then \
		mkdir -p build/Cap1/; \
		g++ -o ./build/Cap1/listing1.3 ./src/Cap1/listing1.1/* ./src/Cap1/listing1.2/* ./src/Cap1/listing1.3/*; \
	else \
		$(eval obj_dir := $(shell find $(SRC_DIR) -type d -name $(listing))) \
		$(eval arch_dest := $(shell echo $(obj_dir) | sed 's/$(SRC_DIR)/$(BUILD_DIR)/g')) \
		$(eval build_dir := $(shell dirname $(arch_dest))) \
		mkdir -p $(build_dir); \
		$(CC) $(CFLAGS) -o $(arch_dest) $(obj_dir)/*; \
	fi 
	
# Define a variable with the list of files in the source directory
$(eval FILES := $(shell basename -a $(shell find $(SRC_DIR) -type d -name "listing*")))

# Create a target that applies the rule to each file
all: $(FILES)
	@for file in $^; do \
		$(MAKE) "$$file"; \
		done

clean: 
	@rm $(BUILD_DIR) -rf

.PHONY: clean all
