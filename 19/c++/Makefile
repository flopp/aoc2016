PROGS=main1 main2
include ../../XX/Makefile.rules


test1: main1
	@echo "expected: 3"
	@time ./main1 5
puzzle1: main1
	@echo "puzzle result:"
	@time ./main1 3018458


test2: main2
	@echo "expected: 2"
	@time ./main2 5
puzzle2: main2
	@echo "puzzle result:"
	@time ./main2 3018458
