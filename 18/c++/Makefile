PROGS=main
include ../../XX/Makefile.rules


test1: main ../test1.txt
	@time ./main 3 < ../test1.txt
test2: main ../test2.txt
	@echo "expected result: 38 safe tiles"
	@time ./main 10 < ../test2.txt
puzzle1: main ../puzzle.txt
	@echo "puzzle result:"
	@time ./main 40 < ../puzzle.txt

puzzle2: main ../puzzle.txt
	@echo "puzzle result:"
	@time ./main 400000 < ../puzzle.txt
