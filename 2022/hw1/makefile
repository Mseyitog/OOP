all: clear compile run clean

compile: main.cpp util.cpp util.hpp
	@echo "Compilihg..."
	@echo "-------------------------------------------"
	@g++	-std=c++11 main.cpp util.cpp -o melike

run:
	@echo "Running tests..."
	@echo "-------------------------------------------"
	@./melike


clean:
	@rm -f *.o
	@rm -f melike
	
clear:
	clear