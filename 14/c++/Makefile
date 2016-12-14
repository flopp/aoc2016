PROGS=main
include ../../XX/Makefile.rules


test1: main ../test1.txt
	@echo "expected result: 22728"
	@time ./main < ../test1.txt

puzzle1: main ../puzzle1.txt
	@echo "puzzle result:"
	@time ./main < ../puzzle1.txt


test2: main ../test2.txt
	@echo "expected result: XXX"
	@time ./main < ../test2.txt

puzzle2: main ../puzzle2.txt
	@echo "puzzle result:"
	@time ./main < ../puzzle2.txt
