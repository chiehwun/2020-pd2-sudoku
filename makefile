all: generate transform solve solve2

generate: sudoku.o generate.o
	g++ -o generate sudoku.o generate.o
generate.o: generate.cpp sudoku.h
	g++ -c generate.cpp

transform: sudoku.o transform.o
	g++ -o transform sudoku.o transform.o
transform.o: transform.cpp sudoku.h
	g++ -c transform.cpp

solve: sudoku.o solve.o
	g++ -o solve sudoku.o solve.o
solve.o: solve.cpp sudoku.h
	g++ -c solve.cpp

solve2: sudoku.o solve2.o
	g++ -o solve2 sudoku.o solve2.o
solve2.o: solve2.cpp sudoku.h
	g++ -c solve2.cpp

sudoku.o: sudoku.cpp sudoku.h
	g++ -c sudoku.cpp

clean:
	rm generate transform solve solve2 *.o -v
