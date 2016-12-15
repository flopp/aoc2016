PROGS=main
include ../../XX/Makefile.rules


test: main ../test.txt
	@echo "expected result: 5"
	@time ./main < ../test.txt

puzzle1: main ../puzzle1.txt
	@echo "puzzle result:"
	@time ./main < ../puzzle1.txt

puzzle2: main ../puzzle2.txt
	@echo "puzzle result:"
	@time ./main < ../puzzle2.txt
