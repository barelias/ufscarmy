all: ufsh

CFLAGS = -W -m64 -Wall -std=c++1z

ufsh: makedir/main.o makedir/interpreter.o makedir/table.o makedir/registry_worker.o makedir/table_worker.o makedir/index_worker.o makedir/file.o
	g++ -o ufsh makedir/main.o makedir/file.o makedir/interpreter.o makedir/table.o makedir/registry_worker.o makedir/table_worker.o makedir/index_worker.o $(CFLAGS)
makedir/main.o: main.cpp
	g++ -o makedir/main.o -c main.cpp $(CFLAGS)
makedir/interpreter.o: src/interpreter.cpp
	g++ -o makedir/interpreter.o -c src/interpreter.cpp $(CFLAGS)
makedir/registry_worker.o: src/registry_worker.cpp
	g++ -o makedir/registry_worker.o -c src/registry_worker.cpp $(CFLAGS)
makedir/table_worker.o: src/table_worker.cpp
	g++ -o makedir/table_worker.o -c src/table_worker.cpp $(CFLAGS)
makedir/index_worker.o: src/index_worker.cpp
	g++ -o makedir/index_worker.o -c src/index_worker.cpp $(CFLAGS)
makedir/file.o: src/file.cpp
	g++ -o makedir/file.o -c src/file.cpp $(FLAGS)
makedir/table.o: src/table.cpp
	g++ -o makedir/table.o -c src/table.cpp $(CFLAGS)
clean:
	rm -rf makedir/*.o
rmmeta:
	rm -rf meta/*.meta
mrproper: clean
	rm -rf ufsh