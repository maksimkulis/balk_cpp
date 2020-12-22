COMPCOLOR = \033[0;32m
OKCOLOR = \033[1;32m
NOTOKCOLOR = \033[0;31m
NC= \033[0m

ifeq ($(strip $(OUTPUT)),)
OUTPUT = outputs
endif

all: program

program:
	@mkdir -p build
	@cmake -B ./build/ -S ./
	@make -C build

run: program
ifeq ($(strip $(INPUT)),)
	@echo "$(COMPCOLOR)Usage: make run INPUT=\"<input_file_name>\" [OUTPUT=\"<output_folder_name>\"]$(NC)"
	@exit 1
endif
	@mkdir -p $(OUTPUT)
	@echo "$(COMPCOLOR)Calculating...$(NC)"
	@./build/balka "$(INPUT)" "$(OUTPUT)"
	@echo "$(OKCOLOR)Calculated!$(NC)"
	@echo "$(OKCOLOR)Drawing...$(NC)"
	@python3 scripts/graphics.py $(INPUT) $(OUTPUT)

clean:
	@echo "$(COMPCOLOR)delete object files$(NC)"
	@rm -f *.o program
	@rm -rf outputs build