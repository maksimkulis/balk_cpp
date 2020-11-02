CC = g++ --std=c++17
OBJS = main.o forces_and_moments.o balk.o parser.o lu_solver.o

COMPCOLOR = \033[0;32m
OKCOLOR = \033[1;32m
NOTOKCOLOR = \033[0;31m
NC= \033[0m

all: program

program: $(OBJS)
	@echo "$(COMPCOLOR)Linking...$(NC)"
	@$(CC) $(OBJS) -o program
	@echo "$(OKCOLOR)Compiled$(NC)"

main.o: main.cpp balk.h
	@echo "$(COMPCOLOR)Compiling main.cpp...$(NC)"
	@$(CC) -c main.cpp

forces_and_moments.o: forces_and_moments.cpp forces_and_moments.h balk.h
	@echo "$(COMPCOLOR)Compiling forces_and_moments.cpp...$(NC)"
	@$(CC) -c forces_and_moments.cpp

balk.o: balk.cpp balk.h forces_and_moments.h
	@echo "$(COMPCOLOR)Compiling balk.cpp...$(NC)"
	@$(CC) -c balk.cpp

parser.o: parser.cpp parser.h balk.h
	@echo "$(COMPCOLOR)Compiling parser.cpp...$(NC)"
	@$(CC) -c parser.cpp

lu_solver.o: lu_solver.cpp lu_solver.h
	@echo "$(COMPCOLOR)Compiling lu_solver.cpp...$(NC)"
	@$(CC) -c lu_solver.cpp

run: program
	@echo "$(COMPCOLOR)Running the program...$(NC)"
	@./program $(INPUT)
	@echo "$(OKCOLOR)Calculated!!!$(NC)"
	@echo "$(COMPCOLOR)Drawing...$(NC)"
	@python graphics.py
	@rm output.txt

clean:
	@echo "$(NOTOKCOLOR)delete object files$(NC)"
	@rm *.o program