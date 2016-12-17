PROGS=main
include ../../XX/Makefile.rules

test: main
	@echo "expected result: 01100"
	@time ./main 20 10000

puzzle1: main
	@time ./main 272 10111100110001111

puzzle2: main
	@time ./main 35651584 10111100110001111
