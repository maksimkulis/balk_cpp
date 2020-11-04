COMPCOLOR = \033[0;32m
OKCOLOR = \033[1;32m
NOTOKCOLOR = \033[0;31m
NC= \033[0m

all: build

build:
	@mkdir -p build
	@cmake -B ./build/ -S ./
	@make -C build

run: build
	@echo "$(COMPCOLOR)Calculating...$(NC)"
	@./build/balka "$(INPUT)"
	@echo "$(OKCOLOR)Calculated!$(NC)"
	@echo "$(OKCOLOR)Drawing...$(NC)"
	@python scripts/graphics.py $(INPUT)

clean:
	@echo "$(COMPCOLOR)delete object files$(NC)"
	@rm -f *.o program
	@rm -rf outputs build