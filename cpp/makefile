C = clang++ -std=c++20 -Wall -g 
CH = clang++  -std=c++20 -c -x c++-system-header 
EXEC = test
ZIPNAME = test

INTERFACES = main.cpp
IMPLEMENTIONS = 

$(EXEC): $(INTERFACES) $(IMPLEMENTIONS) 
	$(C) $(INTERFACES) $(IMPLEMENTIONS) -o $(EXEC)


.PHONY: clean run mem debug 

clean: 
	rm -f *.o $(EXEC)

run:
	./$(EXEC)

mem:
	valgrind ./$(EXEC)

debug:
	gdb ./$(EXEC)