C = g++-15 -std=c++20 -fmodules-ts -Wall -g 
CH = g++-15 -std=c++20 -fmodules-ts -c -x c++-system-header 
EXEC = test
ZIPNAME = test

INTERFACES = main.cpp
IMPLEMENTIONS = 

$(EXEC): $(INTERFACES) $(IMPLEMENTIONS) gcm.cache
	$(C) $(INTERFACES) $(IMPLEMENTIONS) -o $(EXEC)


.PHONY: clean run mem debug 

gcm.cache: 
	$(CH) iostream filesystem

clean: 
	rm -f *.o $(EXEC)
	rm -rf gcm.cache

run:
	./$(EXEC)

mem:
	valgrind ./$(EXEC)

debug:
	gdb ./$(EXEC)