# compilador
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
	elif [ "$(listing)" = "listing2.7" ]; then \
		g++ $(CFLAGS) -c $(obj_dir)/listing2.7.c -o listing2.7.o; \
		ar cr libtest.a listing2.7.o; \
		g+ $(CFLAGS) $(obj_dir)/listing2.8.c -L. -ltest -o $(arch_dest); \
		rm *.o; \
	elif [ "$(listing)" = "listing2.9" ]; then \
		g++ $(CFLAGS) $(obj_dir)/listing2.9.c -o $(arch_dest); \
	elif [ "$(listing)" = "listing2.4"]; then \
		gcc $(CFLAGS) $(obj_dir)/listing2.4.c -o $(arch_dest); \
	elif [ "$(listing)" = "listing3.4" ]; then \
		mkdir -p build/Cap3/; \
		gcc -o ./build/Cap3/listing3.4 ./src/Cap3/listing3.4/*; \
	else \
		$(eval obj_dir := $(shell find $(SRC_DIR) -type d -name $(listing))) \
		$(eval arch_dest := $(shell echo $(obj_dir) | sed 's/$(SRC_DIR)/$(BUILD_DIR)/g')) \
		$(eval build_dir := $(shell dirname $(arch_dest))) \
		mkdir -p $(build_dir); \
		g++ $(CFLAGS) -o $(arch_dest) $(obj_dir)/*; \
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
