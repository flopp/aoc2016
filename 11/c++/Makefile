PROGS=main
include ../../XX/Makefile.rules


test1: main ../test.txt
	@echo "expected result: 11"
	@time ./main < ../test.txt

puzzle1: main ../puzzle.txt
	@echo "puzzle result:"
	@time ./main < ../puzzle.txt

puzzle2: main ../puzzle2.txt
	@echo "puzzle result:"
	@time ./main < ../puzzle2.txt

