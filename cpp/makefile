CXX = g++
CXXFLAGS = -std=c++20 -Wall -g

EXEC = musicManager

OBJS = main.o musiclibrary.o album.o 

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) -lsqlite3

main.o: main.cc musiclibrary.o album.o
	$(CXX) $(CXXFLAGS) -c main.cc

musiclibrary.o: musiclibrary.cc album.o
	$(CXX) $(CXXFLAGS) -c musiclibrary.cc

album.o: album.cc
	$(CXX) $(CXXFLAGS) -c album.cc


.PHONY: clean run mem debug

clean:
	rm -f *.o $(EXEC) gcm.cache

run: $(EXEC)
	./$(EXEC)

mem:
	valgrind ./$(EXEC)

debug:
	gdb ./$(EXEC)