PROGS=main
include ../../XX/Makefile.rules


test1: main ../test.txt
	@echo "expected result: 42"
	@./main 0 < ../test.txt

puzzle1: main ../puzzle.txt
	@echo "puzzle result:"
	@./main 7 < ../puzzle.txt

puzzle2: main ../puzzle.txt
	@echo "puzzle result:"
	@./main 12 < ../puzzle.txt
