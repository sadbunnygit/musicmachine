C = clang++ -std=c++20 -Wall -g 
CH = clang++  -std=c++20 -c -x c++-system-header 
EXEC = musicManager

INTERFACES = main.cpp
IMPLEMENTIONS = 

$(EXEC): $(INTERFACES) $(IMPLEMENTIONS) 
	$(C) $(INTERFACES) $(IMPLEMENTIONS) -o $(EXEC)


.PHONY: clean run mem debug 

clean: 
	rm -f *.o $(EXEC)
	rm -rf *.dSYM

run:
	./$(EXEC)

runNew:
	make
	./$(EXEC)

mem:
	valgrind ./$(EXEC)

debug:
	gdb ./$(EXEC)