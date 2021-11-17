default: build
build:
	g++ -o a.out main.cpp nation.cpp -lncurses
clean:
	rm *.o a.out